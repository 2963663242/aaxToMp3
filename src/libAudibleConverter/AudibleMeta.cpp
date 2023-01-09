#include "AudibleMeta.h"
#include <QFileInfo>
AudibleMeta::AudibleMeta(QString title, QString album, QString artist, QString copyright, QString year, QString genre, QString comments, QString cover)
{
	this->title = title;
	this->album = album;
	this->artist = artist;
	this->copyright = copyright;
	this->year = year;
	this->genre = genre;
	this->comments = comments;
	this->duration = "";
	this->checksum = "";
	this->_AudibleMeta__cover = cover;
}

QString AudibleMeta::cover()
{
	QFileInfo fileInfo(_AudibleMeta__cover);
	if (fileInfo.exists()) {
		return _AudibleMeta__cover;
	}
	return 0;
}

void AudibleMeta::setCover(QString cover)
{
	_AudibleMeta__cover = cover;
}
