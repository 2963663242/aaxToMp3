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
signals:
	void startAll();
	void stopAll();
public slots:
	void onCellTaskFinished(QString);
private:
	int rowOfCell(TaskCellWidget* cell) const;
	TaskCellWidget* cellWidget(int row) const;
};



class TaskCellWidget :public QWidget {
	Q_OBJECT
public:
	TaskCellWidget(ConvertTask* task,QWidget* parent = nullptr);
	~TaskCellWidget();
public:
	static int cellHeight();
signals:
	void startClicked(QString format, convparam splitway);
	void stopClicked();
	void taskFinished(QString);
	void startAll();
	void stopAll();
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

