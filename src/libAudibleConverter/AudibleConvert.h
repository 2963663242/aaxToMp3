#include <QString>
#include <QJsonObject>
#include <AudibleMeta.h>
#include <mutex>

using namespace std;

enum status {
	downloading
};
struct ItemTable {
	status st;
	double rate;
};

class STATECALLBACK {
public:
	virtual void stateInform(ItemTable item) = 0;
};



enum convparam {
	SINGLE,
	CHAPTERS,
};
class AudibleConvert : public QObject {
	Q_OBJECT
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
	void setCallback(STATECALLBACK* callback);
	void stop();
public:
	static QString check_type(QString filepath);
	static bool verify_code(QString code);
	static QString validate_title(QString title);
	static int timestamp(QString output);
	static bool set_m4b_cover(QString filepath, QString cover);
signals:
	void killProcess();
private:
	QString settingsPath;
	QString EXE;
	QString CFGFILE;
	QJsonObject d;
	STATECALLBACK* callback = 0;
	bool isConverting = false;
	mutex mtx;
};


