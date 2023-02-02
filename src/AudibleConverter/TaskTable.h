#include <QTableWidget>
#include <QPushButton>
#include "IAudibleConvert.h"
#include <qDebug>

class QLabel;
class QStackedWidget;
class QPushButton;
class QComboBox;
class QStackedWidget;
class QProgressBar;


const int TaskCellHeight = 100;

class ConvertSTATECALLBACK :public STATECALLBACK {
public:
	virtual void stateInform(ItemTable item) {
		if (item.st == status::downloading)
			qDebug() << item.rate;
		else if (item.st == status::finished) {
			qDebug() << "convert finished . filepath: " << item.filepath;
		}
	}
};

class ConvertTask {
public:
	ConvertTask(QString filename);
public:
	AudibleMeta meta;
	QString filename;
	IAudibleConvert* converter;
	STATECALLBACK* cb; 
	
};


class TaskTableWidget:public QTableWidget {
	Q_OBJECT
public:
	TaskTableWidget(QWidget* parent = nullptr);
	void addTask(ConvertTask* task);


};



class TaskCellWidget :public QWidget {
	Q_OBJECT
public:
	TaskCellWidget(ConvertTask* task,QWidget* parent = nullptr);
public:
	static int cellHeight();
private:
	QLabel* thumbnail;
	QStackedWidget* buttonCheck;
	QPushButton* btnStart;
	QPushButton* btnStop;
	ConvertTask* task;
	QStackedWidget* deepChange;
	QComboBox* comboFormat;
	QComboBox* comboSplit;
	QProgressBar* progress;
};

