#include "AudibleConvert.h"
#include <QDir>
#include <qdebug.h>
#include <iostream>
#include <fstream>
#include "functions.h"
#include <QJsonDocument>
#include <QProcess>
#include "settings.h"
#include <qmath.h>
using namespace std;
QString get_meta_one(QString info, QString meta, QString endstr="\n");
float sum(QList<float> list);

AudibleConvert::AudibleConvert(QString settingsPath)
{
    
    this->settingsPath = settingsPath;
    this->EXE = QDir::separator() == '\\' ? "plugins/win" : "plugins/mac";
    this->EXE = os_sep(getExeDirectory() + QDir::separator() + this->EXE);
    this->CFGFILE = this->settingsPath + QDir::separator() + "audible.cfg";
    this->savePath = setting.outputPath;
    QFileInfo fileInfo(CFGFILE);
    if (!fileInfo.isFile()) {
        QJsonDocument jsonDoc;
        QJsonObject obj;
        jsonDoc.setObject(obj);
        
        QFile data(this->CFGFILE);
        if (data.open(QFile::WriteOnly | QIODevice::Truncate)) {
            QTextStream out(&data);
            out << jsonDoc.toJson();
            data.close();
        }
        
    }
}
AudibleConvert::~AudibleConvert()
{
}
AudibleMeta AudibleConvert::getMeta(QString filepath)
{
    AudibleMeta meta;
    QByteArray cover_data = "";
    QString coverpath = "";
    QProcess process;
    process.start(this->EXE, { "-i", filepath, "-hide_banner" });
    process.waitForFinished();
    process.waitForFinished(-1);
    QString output = process.readAllStandardError().data();
    QString title = get_meta_one(output, "title           : ");
    meta.title = title;
    QString album = get_meta_one(output, "album           : ");

    if (!album.isEmpty()) {
        meta.album = album;
    }
  
    QString author = get_meta_one(output, "author          : ");
    if (!author.isEmpty())
        meta.artist = author;
    else 
        meta.artist = get_meta_one(output, "artist          : ");
    

    QString cpright = get_meta_one(output, "copyright       : ");
    if (!cpright.isEmpty())
        meta.copyright = cpright;
    
    QString date = get_meta_one(output, "date            : ");
    if (!date.isEmpty())
        meta.year = date;

    QString pubdate = get_meta_one(output, "pubdate         : ");
    if (!pubdate.isEmpty())
        meta.year = pubdate;
    
    meta.genre = "Audiobook";
    QString comment = get_meta_one(output, "comment         : ");
    if (!comment.isEmpty())
        meta.comments = comment;

    coverpath = QDir(setting.coverpath).absoluteFilePath(getmd5(filepath) + ".jpg");
    qDebug() << coverpath;
        
    QString typ = this->check_type(filepath);
        
    if (typ == "aax")
    {
        cover_data = get_cover_from_aax(filepath);
    }
    else if (typ == "aa") {
        cover_data = get_cover_from_aa(filepath);
    }
        
    

    if (!cover_data.isEmpty()) {
        QFile f(coverpath);
        f.open(QIODevice::WriteOnly);
        f.write(cover_data);
        meta._AudibleMeta__cover = coverpath;
    }

    QString duration = get_meta_one(output, "Duration: ", ",");
    meta.duration = duration;
    QString checksum = get_meta_one(output, "checksum == ");
    meta.checksum = checksum;
    
    return meta;
}
QString AudibleConvert::seek_code(QString checksum)
{
    QByteArray data;
    if (this->d.isEmpty()) {
        QFile file(this->CFGFILE);
        if (file.open(QIODevice::ReadOnly)) {
            data = file.readAll();
            file.close();
        }
        QJsonParseError jError;
        QJsonDocument jDoc = QJsonDocument::fromJson(data, &jError);
        if (jError.error == QJsonParseError::NoError) {
            this->d = jDoc.object();
        }
    }
    
    if (d.contains(checksum)) {
        if (!d[checksum].toString().isEmpty()) {
            if (this->verify_code(d[checksum].toString()))
                return d[checksum].toString();
        }
    }

    QString code = "";
#ifdef _WIN64
    code = this->compute(checksum);
#endif
    if (!code.isEmpty()) {
        this->d[checksum] = code;
        QJsonDocument jsonDoc;
        
        jsonDoc.setObject(this->d);

        QFile data(this->CFGFILE);
        if (data.open(QFile::WriteOnly | QIODevice::Truncate)) {
            QTextStream out(&data);
            out << jsonDoc.toJson();
        }
        data.close();
        return code;
    }
    return "";
}
QString AudibleConvert::compute(QString checksum)
{
    
    if (QDir::separator() == '\\') {
        QProcess process;
        connect(this, &AudibleConvert::killProcess, &process, &QProcess::kill, Qt::DirectConnection);
        process.start("bin\\win_rcrack.exe", { "bin\\tables" , "-h", checksum });
        process.waitForStarted();
        process.waitForFinished(-1);
        QString output = process.readAllStandardOutput().data();
        output = output.simplified();
        QString code = output.mid(output.length() - 8);
        qDebug() << "compute finished";
        if (this->verify_code(code))
            return code;
        return "";
    }
    else {
        QProcess process;
        connect(this, &AudibleConvert::killProcess, &process, &QProcess::kill, Qt::DirectConnection);
        process.start("bin/mac_rcrack", { 
            "bin/tables/audible_byte#4-4_0_10000x1362345_0.rt",
            "bin/tables/audible_byte#4-4_1_10000x1362345_0.rt",
            "bin/tables/audible_byte#4-4_2_10000x1362345_0.rt",
            "bin/tables/audible_byte#4-4_3_10000x1362345_0.rt",
           "-h",checksum});
        process.waitForStarted();
        process.waitForFinished(-1);
        QString output = process.readAllStandardOutput().data();
        output = output.simplified();
        QString code = output.mid(output.length() - 8);
        if (this->verify_code(code))
            return code;
        return "";
    }
    
}
QList<QList<float>> AudibleConvert::get_chapters(QString filepath)
{
    QString typ = this->check_type(filepath);
    if (typ == "aa") {
        int one_k = 100;
        QRegExp rx("bitrate: (\\d{1,3})");
        QProcess process;
        connect(this, &AudibleConvert::killProcess, &process, &QProcess::kill, Qt::DirectConnection);
        process.start(this->EXE, { "-i", filepath });
        process.waitForFinished(-1);
        QString output = process.readAllStandardError().data();
        float bitrate = 0;
        int pos = 0;
        while ((pos = rx.indexIn(output, pos)) != -1) {
            pos += rx.matchedLength();
            bitrate = rx.cap(1).toFloat();
        }
        float bytes_per_second = bitrate / 8 * one_k;
        QByteArray MAGIC = "\xff\xff\xff\xff\xff\xff\xff\xff";
        QFile fp(filepath);
        if (fp.open(QIODevice::ReadOnly)) {
            QByteArray contents = fp.readAll();
            QList<int> idxs;
            int index = 0;
            int pos = 0;
            while ((pos = contents.indexOf(MAGIC, pos))!=-1) {
                pos += MAGIC.length();
                idxs.append(pos);
            }
            QList<int> points;
            for each (int idx in idxs) {
                fp.seek(idx + MAGIC.length());
                QByteArray packed_data = fp.read(4);
                bool ok;
                int point = packed_data.toInt(&ok, 16);
                points.append(point);
            }
            QList<float> fPoints;
            for each (int p in points) {
                fPoints.append((float)p / bytes_per_second);
            }
            QList<QList<float>> rs;
            for (int i = 0; i < fPoints.length(); i++) {
                QList<float> result;
                result.append(sum(fPoints.mid(0, i)));
                result.append(sum(fPoints.mid(0, i + 1)) + 1);
                rs.append(result);
            }
            return rs;
        }

        return QList<QList<float>>();
    }
    else {
        QRegExp rx("(\\d+\\.\\d{6})");
        QProcess process;
        connect(this, &AudibleConvert::killProcess, &process, &QProcess::kill, Qt::DirectConnection);
        process.start(this->EXE, { "-i", filepath });
        process.waitForFinished(-1);
        QString output = process.readAllStandardError().data();
        QList<QList<float>> rs;
        for each (QString line in output.split("\n")) {
            if (line.simplified().startsWith("Chapter #")) {
                int pos = 0;
                QList<float> result;
                while ((pos = rx.indexIn(line, pos)) != -1) {
                    result.append(rx.cap(1).toFloat());
                    pos += rx.matchedLength();
                }
                rs.append(result);
            }


        }
        return rs;
    }


   
}
bool AudibleConvert::set_mp3_meta(QString filepath, AudibleMeta meta)
{
    QString name = QFileInfo(filepath).fileName();
    QString tmpfile = QDir::tempPath() + QDir::separator() + name;
    QProcess process;
    connect(this, &AudibleConvert::killProcess, &process, &QProcess::kill, Qt::DirectConnection);
   process.start(this->EXE, { "-i", filepath, "-c", "copy", "-id3v2_version", "3",
        "-metadata", "title=" + meta.title,
        "-metadata", "album=" + meta.album,
        "-metadata", "artist=" + meta.artist,
        "-metadata", "copyright=" + meta.copyright,
        "-metadata", "date=" + meta.year,
        "-metadata", "genre=" + meta.genre,
        "-metadata", "comment=" + meta.comments,
        tmpfile });
 
    process.waitForStarted();
    process.waitForFinished(-1);
    if (process.exitCode() == 0) {
        QFile::remove(filepath);
        QFile::rename(tmpfile, filepath);
        QFile::remove(tmpfile);
        return true;
    }
    return false;
}

bool AudibleConvert::set_m4b_meta(QString filepath, AudibleMeta meta)
{
    QString name = QFileInfo(filepath).fileName();
    QString tmpfile = QDir::tempPath() + QDir::separator() + name;
    QProcess process;
    connect(this, &AudibleConvert::killProcess, &process, &QProcess::kill, Qt::DirectConnection);
    process.start(this->EXE, { "-i", filepath, "-c:a", "copy",
         "-metadata", "title=" + meta.title,
         "-metadata", "album=" + meta.album,
         "-metadata", "artist=" + meta.artist,
         "-metadata", "copyright=" + meta.copyright,
         "-metadata", "date=" + meta.year,
         "-metadata", "genre=" + meta.genre,
         "-metadata", "comment=" + meta.comments,
         tmpfile });

    process.waitForStarted();
    process.waitForFinished(-1);
    if (process.exitCode() == 0) {
        QFile::remove(filepath);
        QFile::rename(tmpfile, filepath);
        QFile::remove(tmpfile);
        return true;
    }
    return false;
}

bool AudibleConvert::set_mp3_cover(QString filepath, QString cover)
{
    QString name = QFileInfo(filepath).fileName();
    QString tmpfile = QDir::tempPath() + QDir::separator() + name;
    QProcess process;
    connect(this, &AudibleConvert::killProcess, &process, &QProcess::kill, Qt::DirectConnection);
    process.start(this->EXE, { "-i", filepath, "-i", cover, "-map", "0:0", "-map", "1:0", "-c", "copy", "-id3v2_version", "3",
         tmpfile });

    process.waitForStarted();
    process.waitForFinished(-1);
    if (process.exitCode() == 0) {
        QFile::remove(filepath);
        QFile::rename(tmpfile, filepath);
        QFile::remove(tmpfile);
        return true;
    }
    return false;
   
}

QString AudibleConvert::process(AudibleMeta meta,QString filepath,convparam convp, QString ext)
{
   
    ItemTable item;
    ItemSender sender(&item,this->callback);
    double progress = 0.0;
    float hours = 0, mins = 0, secs = 0;
    QString strDuration = meta.duration;
    QStringList timeList = strDuration.split(":");
    if (timeList.length() == 3)
    {
        hours = timeList[0].toFloat();
        mins = timeList[1].toFloat();
        secs = timeList[2].toFloat();
    }
    float duration = secs + 60 * mins + 3600 * hours;
    QList<QList<float>> split_points;
    if (convp == convparam::SINGLE) {
        split_points.append(QList<float>({0,duration}));
    }
    else {
        split_points = this->get_chapters(filepath);
    }

    QString mime = this->check_type(filepath);
    if (split_points.length() == 1) {
        QString  outname = this->validate_title(meta.title) + ext;
        QString outpath = this->savePath + QDir::separator() + outname;
        if (outpath.length() > 240)
            outpath = outpath.mid(0, 240) + ext;
        outpath = choosename(outpath);
        QStringList args;
        if (mime == "aa") {
            args += { "-y", "-i", filepath, outpath};
        }
        else {
            QString act_code = this->seek_code(meta.checksum);
            if(ext.toLower() == ".m4b")
                args += { "-y", "-activation_bytes", act_code, "-i", filepath, "-vn", "-c:a", "copy", outpath };
            else
                args += { "-y", "-activation_bytes", act_code, "-i", filepath, "-vn", outpath };
        }

        if (isStop())
            return "";
        QProcess process;
        connect(this, &AudibleConvert::killProcess, &process, &QProcess::kill,Qt::DirectConnection);
        QObject::connect(&process, &QProcess::readyReadStandardError, [&]() {
            QString content = process.readAllStandardError().data();
            if (content.indexOf("size=") == -1) return;
            double _progress = this->timestamp(content) / duration * 100;
            if (_progress < progress) return;
            progress = _progress;
      
            item.st = status::downloading;
            item.rate = progress;
            if (this->callback != 0)
                callback->stateInform(item);
            });
        process.start(this->EXE, args);
        process.waitForFinished();
        int code = process.exitCode();
        if (code != 0)
            return "";

        if (ext == ".mp3") {
            this->set_mp3_meta(outpath, meta);
            this->set_mp3_cover(outpath, meta.cover());
        }
        else {
            this->set_m4b_meta(outpath, meta);
            this->set_m4b_cover(outpath, meta.cover());
        }
        if (this->isStop())
            return "";

        item.filepath = outpath;
        return outpath;
    }
    QString name = this->validate_title(meta.title);
    QString outdir = this->savePath + QDir::separator() + name.mid(0, 20);
    outdir = mkdir(outdir);
    QList<QList<QString>> cmds;
    if (mime == "aa") {
        int idx = 0;
        for each (QList<float> item_ in split_points) {
            QString secure_outpath = outdir + QDir::separator() + name + QString::asprintf("--%04d", (idx + 1)) + ext;
            QString title = "title=\"" + name + QString::asprintf("--%04d", (idx + 1)) + "\"";
            int path_length = secure_outpath.length();
            if (path_length > 245)
                secure_outpath = outdir + QDir::separator() +
                name.mid(0, 245) + QString::asprintf("--%04d", (idx + 1)) + ext;
            cmds.append({ "-y", "-i", filepath, "-ss", QString::asprintf("%f",item_[0]), "-t",QString::asprintf("%f", item_[1] - item_[0]), "-metadata",
                QString::asprintf("title=%s",title), secure_outpath });
            idx++;
        }

    }
    else {
        QString act_code = this->seek_code(meta.checksum);
        if (ext.toLower() == ".m4b") {
            int idx = 0;
            for each (QList<float> item_ in split_points) {
                QString secure_outpath = outdir + QDir::separator() + name + QString::asprintf("--%04d", (idx + 1)) + ext;
                QString title = "title=\"" + name + QString::asprintf("--%04d", (idx + 1)) + "\"";
                int path_length = secure_outpath.length();
                if (path_length > 245)
                    secure_outpath = outdir + QDir::separator() +
                    name.mid(0, 245) + QString::asprintf("--%04d", (idx + 1)) + ext;
                cmds.append({"-y", "-activation_bytes", act_code, "-i", filepath, "-ss", QString::asprintf("%f", item_[0]), "-t", QString::asprintf("%f", item_[1] - item_[0]), "-vn", "-c:a", "copy", "-metadata",
                    title, "-metadata", "album=" + meta.album, "-metadata", "artist=" + meta.artist, "-metadata", "copyright=" + meta.copyright, "-metadata", "date=" + meta.year, "-metadata", "genre=" + meta.genre, "-metadata", "comment=" + meta.comments, secure_outpath});
                idx++;
            };
                
         }
        else {
            int idx = 0;
            for each (QList<float> item_ in split_points) {
                QString secure_outpath = outdir + QDir::separator() + name + QString::asprintf("--%04d", (idx + 1)) + ext;
                QString title = "title=\"" + name + QString::asprintf("--%04d", (idx + 1)) + "\"";
                int path_length = secure_outpath.length();
                if (path_length > 245)
                    secure_outpath = outdir + QDir::separator() +
                    name.mid(0, 245) + QString::asprintf("--%04d", (idx + 1)) + ext;
                cmds.append({"-y", "-activation_bytes", act_code, "-i", filepath, "-ss", QString::asprintf("%f", item_[0]), "-t",
                    QString::asprintf("%f", item_[1] - item_[0]), "-vn", "-id3v2_version", "3", "-metadata", title,
                    "-metadata", "album=" + meta.album, "-metadata", "artist=" + meta.artist,
                    "-metadata", "copyright=" + meta.copyright, "-metadata", "date=" + meta.year,
                    "-metadata", "genre=" + meta.genre, "-metadata", "comment=" + meta.comments,
                    secure_outpath});
                idx++;
            };

        }
        
    }

    if (isStop())
        return "";
    int idx = 0;
    for each (QList<QString> cmd in cmds) {
        QProcess process;
        connect(this, &AudibleConvert::killProcess, &process, &QProcess::kill,Qt::DirectConnection);
        QObject::connect(&process, &QProcess::readyReadStandardError, [&]() {
            QString content = process.readAllStandardError().data();
            if (content.indexOf("size=") == -1) return;
            double _progress = (this->timestamp(content) + split_points[idx][0]) / duration * 100;
            if (_progress < progress) return;
            progress = _progress;
           
            item.st = status::downloading;
            item.rate = progress;
            if (this->callback != 0)
                callback->stateInform(item);
            });
        process.start(this->EXE,cmd);
        process.waitForFinished();
        int code = process.exitCode();
        if (code != 0)
            return "";
        idx++;
    }
    QStringList files = QDir(outdir).entryList(QDir::Files);
    for each (QString f in files) {
       
        if (ext == ".mp3")
            this->set_mp3_cover(outdir + QDir::separator() + f, meta.cover());
        else
            this->set_m4b_cover(outdir + QDir::separator() + f, meta.cover());
        if (this->isStop())
            return "";
    }
    item.filepath = outdir;
    return outdir;
}

void AudibleConvert::setCallback(STATECALLBACK* callback)
{
    this->callback = callback;
}

void AudibleConvert::stop()
{
    this->mtx.lock();
    this->isConverting = false;
    this->mtx.unlock();
    emit this->killProcess();
}

void AudibleConvert::setStartState()
{
    this->mtx.lock();
    this->isConverting = true;
    this->mtx.unlock();
}

bool AudibleConvert::isStop()
{
    bool stop =  false;
    this->mtx.lock();
    stop =  !this->isConverting;
    this->mtx.unlock();
    return stop;
}

QString AudibleConvert::check_type(QString filepath) {
    
    char bs[12] = {0,};
    ifstream infile;
    infile.open(filepath.toStdString());
    infile.read(bs, 12);
    if (memcmp(bs+4, "W\x90u6", 4) == 0)
        return "aa";
    else {
        if (memcmp(bs + 3, "$ftypaax ", 9) == 0) {
            return "aax";
        }
        return "";
    }
}

bool AudibleConvert::verify_code(QString code)
{
    QString str = "0123456789abcdefabcdef";
    
    for each (QChar c in code)
    {
        if (str.indexOf(c)==-1)
            return false;
    }
    return true;
}

QString AudibleConvert::validate_title(QString title)
{
    QRegExp rx("[\\/\\\\\\:\\*\\?\\\"\\<\\>\\|]");
    return title.replace(rx, "_");
}

int AudibleConvert::timestamp(QString output)
{
    QList<QString>resultSet;
    QRegExp rx("time=(\\d{2,}):(\\d{2})+:(\\d{2})+\\.");
    int pos = 0;
   
    while ((pos = rx.indexIn(output, pos)) != -1)
    {
        pos += rx.matchedLength();
        resultSet.append(rx.cap(1));
        resultSet.append(rx.cap(2));
        resultSet.append(rx.cap(3));
    }
    if (resultSet.count() >= 3) {
        return resultSet[0].toInt() * 3600 + resultSet[1].toInt() * 60 + resultSet[2].toInt();
    }

    return 0;
}

bool AudibleConvert::set_m4b_cover(QString filepath, QString cover)
{
    QString name = QFileInfo(filepath).fileName();
    QString tmpfile = QDir::tempPath() + QDir::separator() + name;
    QFile aaxFile(filepath), covFile(cover);
    if (aaxFile.open(QIODevice::ReadOnly) && covFile.open(QIODevice::ReadOnly)) {
        
        bool ok;
        QByteArray out = aaxFile.readAll();
        QByteArray cov = covFile.readAll();
        int cov_len = cov.length();
        
        int idx_moov = out.lastIndexOf("moov");
        QByteArray old_moov_bytes = out.mid(idx_moov - 4, 4);
        int old_moov_size = old_moov_bytes.toHex().toInt(&ok, 16);
        int new_moov_size = old_moov_size + cov_len + 24;
        QByteArray new_moov_bytes = QByteArray::fromHex(QString::asprintf("%08x", new_moov_size).toUtf8());
        out = out.mid(0, idx_moov - 4) + new_moov_bytes + out.mid(idx_moov);
        int idx_meta = out.indexOf("meta", idx_moov);
        QByteArray old_meta_bytes = out.mid(idx_meta - 4, 4);
        int old_meta_size = old_meta_bytes.toHex().toInt(&ok, 16);
        int new_meta_size = old_meta_size + cov_len + 24;
        QByteArray new_meta_bytes = QByteArray::fromHex(QString::asprintf("%08x", new_meta_size).toUtf8());
        out = out.mid(0, idx_meta - 4) + new_meta_bytes + out.mid(idx_meta);

        int idx_udta = out.indexOf("udta", idx_moov);
        QByteArray old_udta_bytes = out.mid(idx_udta - 4, 4);
        int old_udta_size = old_udta_bytes.toHex().toInt(&ok, 16);
        int new_udta_size = old_udta_size + cov_len + 24;
        QByteArray new_udta_bytes = QByteArray::fromHex(QString::asprintf("%08x", new_udta_size).toUtf8());
        out = out.mid(0, idx_udta - 4) + new_udta_bytes + out.mid(idx_udta);

        int idx_ilst = out.indexOf("ilst", idx_udta);
        QByteArray old_ilst_bytes = out.mid(idx_ilst - 4, 4);
        int old_ilst_size = old_ilst_bytes.toHex().toInt(&ok, 16);
        int new_ilst_size = old_ilst_size + cov_len + 24;
        QByteArray new_ilst_bytes = QByteArray::fromHex(QString::asprintf("%08x", new_ilst_size).toUtf8());
        out = out.mid(0, idx_ilst - 4) + new_ilst_bytes + out.mid(idx_ilst);

        int idx_chpl = out.indexOf("chpl", idx_ilst);
        if (idx_chpl != -1) {
            QByteArray covr_len_bytes = QByteArray::fromHex(QString::asprintf("%08x", cov_len + 24).toUtf8());
            QByteArray data_len_bytes = QByteArray::fromHex(QString::asprintf("%08x", cov_len + 24 - 8).toUtf8());
            QByteArray covr_box_bytes = covr_len_bytes + "covr" + data_len_bytes + "data" + QByteArray("\x00\x00\x00\r\x00\x00\x00\x00", 8) + cov;

            out = out.mid(0, idx_chpl - 4) + covr_box_bytes + out.mid(idx_chpl - 4);

            QFile data(tmpfile);
            if (data.open(QFile::WriteOnly | QIODevice::Truncate)) {
                int pos = 0;
                int length = 4096;
                while (pos < out.size()) {
                    data.write(out.mid(pos,4096));
                    if (this->isStop())
                        break;
                    pos += length;
                }
                
                data.close();
                aaxFile.close();
                covFile.close();
                QFile::remove(filepath);
                if (!this->isStop()) {
                    QFile::rename(tmpfile, filepath);
                    QFile::remove(tmpfile);
                }
                return true;
            }
           
        }
    }

    return false;
}

void AudibleConvert::setSavePath(QString savePath)
{
    this->savePath = savePath;
    return ;
}


QString get_meta_one(QString info, QString meta, QString endstr) {
    if (info.indexOf(meta) > 0) {
        int start = info.indexOf(meta) + meta.length();
        int end = info.indexOf(endstr, start);
        if (end > start) {
            if (info[end - 1] == '\r') {
                end -= 1;
            }
            return info.mid(start, end - start);
        }
    }
    return "";
}

float sum(QList<float> list) {
    float sum(0);
    for each (float one in list) {
        sum += one;
    }
    return sum;
}

