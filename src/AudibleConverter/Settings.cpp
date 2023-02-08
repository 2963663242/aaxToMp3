#include "Settings.h"
#include <QDir>
#include <QDateTime>
Settings* Settings::instance = nullptr;

Settings::Settings() {
	savePath = QDir::homePath() + QDir::separator() + "AAXConverter";
	if (!QDir(savePath).exists())
		QDir().mkpath(savePath);
  
}

void Settings::setSavePath(QString savePath)
{
	std::lock_guard<std::mutex> lockGuard(s_mutex);
	Settings::savePath = savePath;
}

QString Settings::getSavePath()
{
	std::lock_guard<std::mutex> lockGuard(s_mutex);
	return Settings::savePath;
}

std::ofstream& Settings::getLogFile()
{
    return g_OutputDebug;
}

Settings* Settings::getInstance()
{
	if(instance == nullptr)
		instance = new Settings();
	return instance;
}

bool delDir(const QString& path)
{
    if (path.isEmpty()) {
        return false;
    }
    QDir dir(path);
    if (!dir.exists()) {
        return true;
    }
    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot); //���ù���
    QFileInfoList fileList = dir.entryInfoList(); // ��ȡ���е��ļ���Ϣ
    foreach(QFileInfo file, fileList) { //�����ļ���Ϣ
        if (file.isFile()) { // ���ļ���ɾ��
            file.dir().remove(file.fileName());
        }
        else { // �ݹ�ɾ��
            delDir(file.absoluteFilePath());
        }
    }
    return dir.rmdir(dir.absolutePath()); // ɾ���ļ���
}
QStringList getFileNames(const QString& path)
{
    QDir dir(path);
    QStringList nameFilters;
    nameFilters << "*.mp3" << "*.m4b";
    QStringList files = dir.entryList(nameFilters, QDir::Files | QDir::Readable, QDir::Name);
    return files;
}
bool toMove( QString srcPath,  QString desPath) {

    QStringList fileNames = getFileNames(srcPath);
    QString src = QDir(srcPath).path();
    src = src.mid(src.lastIndexOf("/"));
    desPath = mkdir(desPath + src);
    foreach(const QString & filename, fileNames) {
       
        QString filepath = srcPath + QDir::separator() + filename;
        QString temp = filepath;
        QString suffix = temp.remove(0, srcPath.length());
        QString desFileName = desPath  +suffix;


        QFileInfo fileInfo(desFileName);
        if (fileInfo.exists())
        {
            QFile::remove(desFileName);
        }
        else
        {
            if (!fileInfo.dir().exists())
            {
                fileInfo.dir().mkpath(fileInfo.absolutePath());
            }
        }
        QFile::rename(filepath, desFileName);
    }
    return delDir(srcPath);
}
QString choosename(QString filepath) {
    int i = 1;
    while (true) {
        if (!QFileInfo(filepath).exists())
            return filepath;
        QString tmppath = filepath.mid(0, filepath.length() - 4) + " (" + QString::asprintf("%d", i) + ")" + filepath.mid(filepath.length() - 4);
        if (!QFileInfo(tmppath).exists())
            return tmppath;
        i += 1;
    }
}
/*
    ��ֵ�����Ĵ���Ŀ¼�����Ŀ¼�Ѿ����ڣ�
*/
QString mkdir(QString path) {
    int i = 1;
    while (true) {
        if (!QDir(path).exists()) {
            QDir().mkpath(path);
            return path;
        }
        QString tmpdirname = path + " (" + QString::asprintf("%d", i) + ")";
        if (!QDir(tmpdirname).exists()) {
            QDir().mkpath(tmpdirname);
            return tmpdirname;
        }
        i += 1;
    }
}


