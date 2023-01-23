#include <QString>

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

class AudibleMeta
{
public:
	AudibleMeta(QString title = "", QString album = "", QString artist = "", QString copyright = "", QString year = "", QString genre = "", QString comments = "", QString cover = "");
	QString cover();
	void  setCover(QString cover);
public:
	QString title;
	QString album;
	QString artist;
	QString copyright;
	QString year;
	QString genre;
	QString comments;
	QString duration;
	QString checksum;
	QString _AudibleMeta__cover;
};



class IAudibleConvert {
public :
	IAudibleConvert();
	virtual AudibleMeta getMeta(QString filepath) = 0;
	virtual void setCallback(STATECALLBACK* callback) = 0;
	virtual QString process(AudibleMeta meta, QString filepath, convparam convp = convparam::SINGLE, QString ext = ".mp3") = 0;
	virtual void stop() = 0;
public :
	static QString check_type(QString filepath);
	static IAudibleConvert* Create();
};


