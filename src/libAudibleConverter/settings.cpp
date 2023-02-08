
#include "settings.h"
#include <QtGlobal>
#include <QProcessEnvironment>
#include <qDebug>
#include <QDir>
#include <QDateTime>
#include <mutex>

#define CLASSNAME "AAXConverter"

settings setting;

settings::settings()
{

	
#ifdef Q_OS_MAC
	QString confpath = QDir::homePath();
	QString homepath = confpath;
	this->coverpath = confpath + "/."+ CLASSNAME + "/cover/";
#endif

#ifdef Q_OS_WIN32
// win
	QString confpath =  QProcessEnvironment::systemEnvironment().value("APPDATA");
	QString homepath = QDir::homePath();
	this->coverpath = confpath + "\\"+ CLASSNAME +"\\cover\\";
#endif
	outputPath = homepath + QDir::separator() + CLASSNAME;
	if (!QDir(coverpath).exists())
		QDir().mkpath(coverpath);
	if (!QDir(outputPath).exists())
		QDir().mkpath(outputPath);

	//qInstallMessageHandler(myMessageOutput);  
	//g_OutputDebug.open(qPrintable(QString(QString(QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss").append("-log.txt")))), std::ios::out | std::ios::trunc);
    plog::init(plog::debug, ".\\aaxConverter.txt", 1000000, 1);
}

void myMessageOutput(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
    static std::mutex mtx;
    std::lock_guard<std::mutex> lockGuard(mtx);

    QString text;
    switch (type) {
    case QtDebugMsg:
        text = QString("Debug: ");
        break;
    case QtWarningMsg:
        text = QString("Warning: ");
        break;
    case QtCriticalMsg:
        text = QString("Critical:");
        break;
    case QtFatalMsg:
        text = QString("Fatal: ");
        break;
    default:
        text = QString("Debug: ");
    }
    std::ofstream& g_OutputDebug =  setting.g_OutputDebug;
    QString context_info = QString("F:(%1) L:(%2)").arg(QString(context.file)).arg(context.line); // F文件信息L行数
    QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString current_date = QString("(%1)").arg(current_date_time);
    std::string message = qPrintable(QString("%1 %2 \t%3 \t%4").arg(text).arg(context_info).arg(current_date).arg(msg));
    g_OutputDebug << message << "\r\n"; // std::ofstream

}