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
};

class ConvertTask {
public:
	ConvertTask(QString filename);
	~ConvertTask();
	void connectWidget(TaskCellWidget* parent);
public:
	AudibleMeta meta;
	QString filename;
	IAudibleConvert* converter;
	ConvertSTATECALLBACK* cb;

};

#endif // !CONVERTTASK