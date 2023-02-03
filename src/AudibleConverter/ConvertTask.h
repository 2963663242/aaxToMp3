#ifndef CONVERTTASK
#define CONVERTTASK



#include "IAudibleConvert.h"
#include <qDebug>

class TaskCellWidget;

class ConvertSTATECALLBACK :public QObject ,public STATECALLBACK {
	Q_OBJECT
public:
	virtual void stateInform(ItemTable item); 
signals:
	void updateProgress(double rate);
	void convertFinished();
};

class ConvertTask :public QObject {
	Q_OBJECT
public:
	ConvertTask(QString filename);
	~ConvertTask();
	void connectWidget(TaskCellWidget* parent);
	
public slots:
	void start(QString format, convparam splitway);
	void stop();
	
public:
	AudibleMeta meta;
	QString filename;
	IAudibleConvert* converter;
	ConvertSTATECALLBACK* cb;

};

#endif // !CONVERTTASK