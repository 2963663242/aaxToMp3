#pragma once
#include <mutex>
#include <QString>
#include <fstream>
class Settings
{
private:
	static Settings* instance;
	QString savePath;
	std::mutex s_mutex;
	std::ofstream g_OutputDebug;
public:
	 void setSavePath(QString savePath);
	 QString getSavePath();
	 std::ofstream& getLogFile();
public:
	static Settings* getInstance();
private:
	Settings();

};

bool toMove(QString srcPath, QString desPath);
QString choosename(QString filepath);
QString mkdir(QString path);
