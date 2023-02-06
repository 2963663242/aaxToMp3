#ifndef CONVERTTASK
#define CONVERTTASK



#include "IAudibleConvert.h"
#include <qDebug>
#include <QString>
class TaskCellWidget;
class QTemporaryDir;


class ConvertSTATECALLBACK :public QObject ,public STATECALLBACK {
	Q_OBJECT
public:
	virtual void stateInform(ItemTable item); 
signals:
	void updateProgress(double rate);
	void convertFinished(QString);
};

class ConvertTask :public QObject {
	Q_OBJECT
public:
	ConvertTask(QString filename,QString  savePath);
	~ConvertTask();
	void connectWidget(TaskCellWidget* parent);
	void setSavePath(QString);
	QString getSavePath();
public slots:
	void start(QString format, convparam splitway);
	void stop();
	
public:
	AudibleMeta meta;
	QString filename;
	QString savePath;
	IAudibleConvert* converter;
	ConvertSTATECALLBACK* cb;
	QTemporaryDir* tmp;
	

};

#endif // !CONVERTTASK