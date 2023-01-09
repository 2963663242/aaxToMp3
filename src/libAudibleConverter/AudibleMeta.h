#pragma once
#include <QString>
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

