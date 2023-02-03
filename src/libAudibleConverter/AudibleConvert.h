#include <QString>
#include <QJsonObject>
#include <mutex>
#include <IAudibleConvert.h>
using namespace std;
class ItemSender {
public:
	ItemSender(ItemTable* item,STATECALLBACK * callback) {
		this->item = item;
		this->callback = callback;
	}

	~ItemSender() {
		item->st = status::finished;
		callback->stateInform(*item);
	}
public:
	ItemTable* item;
	STATECALLBACK* callback;
};

class AudibleConvert : public QObject ,public IAudibleConvert {
	Q_OBJECT
public:
	AudibleConvert(QString usrPath);
	virtual ~AudibleConvert();
	AudibleMeta getMeta(QString filepath);
	QString seek_code(QString checksum);
	QString compute(QString checksum);
	QList<QList<float>> get_chapters(QString filepath);
	bool set_mp3_meta(QString filepath, AudibleMeta meta);
	bool set_m4b_meta(QString filepath, AudibleMeta meta);
	bool set_mp3_cover(QString filepath, QString cover);
	bool set_m4b_cover(QString filepath, QString cover);
	QString process(AudibleMeta meta, QString filepath, convparam convp = convparam::SINGLE, QString ext = ".mp3");
	void setCallback(STATECALLBACK* callback);
	void stop();
	void setStartState();
	bool isStop();
public:
	static QString check_type(QString filepath);
	static bool verify_code(QString code);
	static QString validate_title(QString title);
	static int timestamp(QString output);
	
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


