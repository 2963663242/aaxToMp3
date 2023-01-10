#include "AudibleConvert.h"
#include <QDir>
#include <qdebug.h>
#include <iostream>
#include <fstream>
#include "functions.h"
#include <QJsonDocument>
#include <QProcess>
#include "settings.h"

using namespace std;
QString get_meta_one(QString info, QString meta, QString endstr="\n");


AudibleConvert::AudibleConvert(QString settingsPath)
{
    
    this->settingsPath = settingsPath;
    this->EXE = QDir::separator() == '\\' ? "plugins/win" : "plugins/mac";
    this->EXE = os_sep(getExeDirectory() + QDir::separator() + this->EXE);
    this->CFGFILE = this->settingsPath + QDir::separator() + "audible.cfg";
    QFileInfo fileInfo(CFGFILE);
    if (!fileInfo.isFile()) {
        QJsonDocument jsonDoc;
        QJsonObject obj;
        jsonDoc.setObject(obj);
        
        QFile data(this->CFGFILE);
        if (data.open(QFile::WriteOnly | QIODevice::Truncate)) {
            QTextStream out(&data);
            out << jsonDoc.toJson();
        }
        data.close();
    }
}
AudibleMeta AudibleConvert::getMeta(QString filepath)
{
    AudibleMeta meta;
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
    else {
        QString author = get_meta_one(output, "author          : ");
        if (!author.isEmpty())
            meta.artist = author;
        else 
            meta.artist = get_meta_one(output, "artist          : ");
    }

    QString cpright = get_meta_one(output, "copyright       : ");
    if (!cpright.isEmpty())
        meta.copyright = cpright;
    
    QString date = get_meta_one(output, "date            : ");
    if (!date.isEmpty())
        meta.year = date;

    QString pubdate = get_meta_one(output, "pubdate         : ");
    if (!pubdate.isEmpty())
        meta.year = pubdate;
    else {
        meta.genre = "Audiobook";
        QString comment = get_meta_one(output, "comment         : ");
        if (!comment.isEmpty())
            meta.comments = comment;

        QString coverpath = QDir(setting.coverpath).absoluteFilePath(getmd5(filepath) + ".jpg");
        qDebug() << coverpath;
        
        QString typ = this->check_type(filepath);
        QByteArray cover_data = "";
        if (typ == "aax")
        {
            cover_data = get_cover_from_aax(filepath);
        }
        else if (typ == "aa") {

        }
        
    }

    

    return meta;
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


QString get_meta_one(QString info, QString meta, QString endstr) {
    if (info.indexOf(meta) > 0) {
        int start = info.indexOf(meta) + meta.length();
        int end = info.indexOf(endstr, start);
        if (end > start) {
            if (info[end - 1] == '\r') {
                end -= 1;
                return info.mid(start, end-start);
            }
        }
    }
    return "";
}



