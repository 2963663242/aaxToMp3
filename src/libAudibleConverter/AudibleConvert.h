#include <QString>
#include <QJsonObject>
#include <AudibleMeta.h>

class AudibleConvert {
	
public:
	AudibleConvert(QString usrPath);
	AudibleMeta getMeta(QString filepath);
	QString seek_code(QString checksum);
	QString compute(QString checksum);
public:
	static QString check_type(QString filepath);
	static bool verify_code(QString code);
private:
	QString settingsPath;
	QString EXE;
	QString CFGFILE;
	QJsonObject d;
};