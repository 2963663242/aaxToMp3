#pragma once
#include <mutex>
#include <QString>
class Settings
{
private:
	static Settings* instance;
	QString savePath;
	std::mutex s_mutex;
public:
	 void setSavePath(QString savePath);
	 QString getSavePath();
public:
	static Settings* getInstance();
private:
	Settings();

};

bool toMove(QString srcPath, QString desPath);
QString choosename(QString filepath);
QString mkdir(QString path);
