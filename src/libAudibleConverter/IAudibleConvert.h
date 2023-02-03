
#ifndef IAUDIBLECONVERT
#define IAUDIBLECONVERT
#ifndef  DLL_EXPORT
#ifdef _WIN32
#define  DLL_EXPORT __declspec(dllexport)
#elif defined __APPLE__
#define  DLL_EXPORT 
#endif 
#endif 

#include <QString>
#include <memory>
using namespace std;
enum status {
	downloading,
	finished
};
struct ItemTable {
	status st;
	double rate;
	QString filepath;
};

class STATECALLBACK {
public:
	virtual void stateInform(ItemTable item) = 0;
};



enum convparam {
	SINGLE,
	CHAPTERS,
};

class DLL_EXPORT AudibleMeta
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



class DLL_EXPORT IAudibleConvert {
public :
	IAudibleConvert();
	~IAudibleConvert();
	virtual AudibleMeta getMeta(QString filepath) = 0;
	virtual void setCallback(STATECALLBACK* callback) = 0;
	QString convert(AudibleMeta meta, QString filepath, convparam convp = convparam::SINGLE, QString ext = ".mp3");
	virtual void stop() = 0;
private:
	virtual QString process(AudibleMeta meta, QString filepath, convparam convp = convparam::SINGLE, QString ext = ".mp3") = 0;
	virtual void setStartState() = 0;
public:
	static QString check_type(QString filepath);
	static IAudibleConvert* Create();
	static void Release(IAudibleConvert*);
};


#endif