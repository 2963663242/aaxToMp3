
#include "settings.h"
#include <QtGlobal>
#include <QProcessEnvironment>
#include <qDebug>
#include <QDir>


settings setting;

settings::settings()
{

	
#ifdef Q_OS_MAC
	QString confpath = QDir::homePath();
	QString homepath = confpath;
	this->coverpath = confpath + "/.EpuborAudible/cover/";
#endif

#ifdef Q_OS_WIN32
// win
	QString confpath =  QProcessEnvironment::systemEnvironment().value("APPDATA");
	QString homepath = QDir::homePath();
	this->coverpath = confpath + "\\EpuborAudible\\cover\\";
#endif
	qDebug() << confpath;
}
