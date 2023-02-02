#include <QTableWidget>
#include <QPushButton>
#include <qDebug>
#include "ConvertTask.h"

class QLabel;
class QStackedWidget;
class QPushButton;
class QComboBox;
class QStackedWidget;
class QProgressBar;


const int TaskCellHeight = 100;




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
public slots:
	void setProgress(double rate);
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

