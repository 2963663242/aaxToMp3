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

bool toMove(const QString& srcPath, const QString& desPath);