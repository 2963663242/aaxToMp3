
#include "settings.h"
#include <QtGlobal>
#include <QProcessEnvironment>
#include <qDebug>
#include <QDir>
#include <QDateTime>
#include <mutex>

#define CLASSNAME "AAXConverter"

settings setting;

settings::settings(): fileAppender((QString(".")+ LOGNAME).toUtf8())
{

	
#ifdef Q_OS_MAC
	confpath = QDir::homePath();
	QString homepath = confpath;
	this->coverpath = confpath + "/."+ CLASSNAME + "/cover/";
#endif

#ifdef Q_OS_WIN32
// win
	confpath =  QProcessEnvironment::systemEnvironment().value("APPDATA");
	QString homepath = QDir::homePath();
	this->coverpath = confpath + "\\"+ CLASSNAME +"\\cover\\";
#endif
	outputPath = homepath + QDir::separator() + CLASSNAME;
	if (!QDir(coverpath).exists())
		QDir().mkpath(coverpath);
	if (!QDir(outputPath).exists())
		QDir().mkpath(outputPath);

   
    fileAppender.setMaxFiles(1);
    fileAppender.setMaxFileSize(1000000);
    plog::init(plog::verbose,&fileAppender);

}

