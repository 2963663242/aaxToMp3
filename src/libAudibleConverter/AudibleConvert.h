#include <QString>
#include <QJsonObject>
#include <AudibleMeta.h>

class AudibleConvert {
	
public:
	AudibleConvert(QString usrPath);
	AudibleMeta getMeta(QString filepath);
public:
	static QString check_type(QString filepath);
private:
	QString settingsPath;
	QString EXE;
	QString CFGFILE;
	QJsonObject d;
};