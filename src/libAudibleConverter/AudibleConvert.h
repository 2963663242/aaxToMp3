#include <QString>
#include <QJsonObject>
#include <AudibleMeta.h>


enum convparam {
	SINGLE,
	CHAPTERS,
};
class AudibleConvert {
	
public:
	AudibleConvert(QString usrPath);
	AudibleMeta getMeta(QString filepath);
	QString seek_code(QString checksum);
	QString compute(QString checksum);
	QList<QList<float>> get_chapters(QString filepath);
	bool set_mp3_meta(QString filepath, AudibleMeta meta);
	bool set_m4b_meta(QString filepath, AudibleMeta meta);
	bool set_mp3_cover(QString filepath, QString cover);
	QString process(AudibleMeta meta, QString filepath, convparam convp = convparam::SINGLE, QString ext = ".mp3");
public:
	static QString check_type(QString filepath);
	static bool verify_code(QString code);
	static QString validate_title(QString title);
	static int timestamp(QString output);
	static bool set_m4b_cover(QString filepath, QString cover);
private:
	QString settingsPath;
	QString EXE;
	QString CFGFILE;
	QJsonObject d;
};


