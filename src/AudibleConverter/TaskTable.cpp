#include "TaskTable.h"
#include <QtWidgets>
#include "Settings.h"

TaskTableWidget::TaskTableWidget(QWidget* parent):QTableWidget(parent) {
	horizontalHeader()->hide();
	verticalHeader()->hide();
	setColumnCount(1);
	horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	setStyleSheet("QTableWidget {"
		"selection-background-color: rgb(227, 227, 229);"
		"}");
	for (int i = 0; i < 3; i++) {
		
		QString filePath = QString::fromLocal8Bit(R"(C:\1.FabiFuchsundderverloreneNuss-SchatzFabiFuchs_ep7.aax)");
		ConvertTask *task = new ConvertTask(filePath, Settings::getInstance()->getSavePath());
		addTask(task);
	}
}

TaskCellWidget::TaskCellWidget(ConvertTask* task,QWidget* parent):QWidget(parent), task(task) {
	AudibleMeta meta = task->meta;
	QHBoxLayout* topLayout = new QHBoxLayout(this);
	
	 thumbnail = new QLabel;
	thumbnail->resize(TaskCellHeight, TaskCellHeight);
	thumbnail->setFixedWidth(TaskCellHeight);
	QPixmap pix(meta.cover());
	QPixmap dest = pix.scaled(thumbnail->size(), Qt::KeepAspectRatio);
	thumbnail->setPixmap(dest);

	QVBoxLayout* midLayout = new QVBoxLayout;
	QVBoxLayout* titleLayout = new QVBoxLayout;
	QLabel * title = new QLabel(meta.title);
	titleLayout->addWidget(title);

	QHBoxLayout* artistLayout = new QHBoxLayout;
	QLabel* artist = new QLabel(meta.artist);
	QLabel* duration = new QLabel(meta.duration);
	artistLayout->addWidget(artist);
	artistLayout->addItem(new QSpacerItem(10, 0, QSizePolicy::Expanding));
	artistLayout->addWidget(duration);
	
	deepChange = new QStackedWidget;

	comboFormat = new QComboBox;
	comboSplit = new QComboBox;

	auto setChoice = [comboFormat = comboFormat, comboSplit= comboSplit]() {
		QWidget* w = new QWidget();
		QHBoxLayout* choiceLayout = new QHBoxLayout;

		comboFormat->addItem("mp3");
		comboFormat->addItem("m4b");
		comboSplit->addItem(QString::fromLocal8Bit("按单文件拆分"));
		comboSplit->addItem(QString::fromLocal8Bit("按章节拆分"));
		choiceLayout->addWidget(comboFormat);
		choiceLayout->addItem(new QSpacerItem(50, 0, QSizePolicy::Expanding));
		choiceLayout->addWidget(comboSplit);
		w->setLayout(choiceLayout);
		return w;
	};
	progress = new QProgressBar;
	
	auto setProgress = [progress = progress]() {
		progress->setValue(0);
		QWidget* w = new QWidget();
		QHBoxLayout* choiceLayout = new QHBoxLayout;
		choiceLayout->addWidget(progress);
		w->setLayout(choiceLayout);
		return w;
	};
	
	deepChange->addWidget(setChoice());
	deepChange->addWidget(setProgress());
	//deepChange->setCurrentIndex(1);
	midLayout->addItem(new QSpacerItem(0, 20));
	midLayout->addLayout(titleLayout);
	midLayout->addItem(new QSpacerItem(0, 20));
	midLayout->addLayout(artistLayout);
	midLayout->addWidget(deepChange);
	//midLayout->addItem(new QSpacerItem(0, 10, QSizePolicy::Minimum, QSizePolicy::Expanding));

	buttonCheck = new QStackedWidget;
	buttonCheck->setFixedWidth(TaskCellHeight);
	
	btnStart = new QPushButton(QString::fromLocal8Bit("开始"));
	btnStop = new QPushButton(QString::fromLocal8Bit("停止"));
	btnReTry = new QPushButton(QString::fromLocal8Bit("重试"));
	auto btnset = [](QPushButton * btn) {
		btn->setFixedSize(TaskCellHeight - 10, 50);
		QWidget* w = new QWidget();
		QVBoxLayout* lay1 = new QVBoxLayout(w);
		lay1->addWidget(btn, 1, Qt::AlignHCenter);
		return w;
	};
	auto reTrybtnset = [](QPushButton* btn) {
		btn->setFixedSize(TaskCellHeight - 10, 50);
		QWidget* w = new QWidget();
		QLabel *LabFail = new QLabel(QString::fromLocal8Bit("失败"));
		LabFail->setStyleSheet("color:rgb(255,0,0)");
		QVBoxLayout* lay1 = new QVBoxLayout(w);
		lay1->addItem(new QSpacerItem(0,25));
		lay1->addWidget(btn, 1, Qt::AlignHCenter);
		lay1->addWidget(LabFail);
		return w;
	};
	buttonCheck->addWidget(btnset(btnStart));
	buttonCheck->addWidget(btnset(btnStop));
	buttonCheck->addWidget(reTrybtnset(btnReTry));
	//buttonCheck->setCurrentIndex(2);
	topLayout->addWidget(thumbnail);
	
	topLayout->addLayout(midLayout);
	topLayout->addWidget(buttonCheck);
	//topLayout->addItem(new QSpacerItem(10,0,QSizePolicy::Expanding));
	connect(btnStart, &QPushButton::clicked, this, [deepChange=deepChange, buttonCheck= buttonCheck]() {
		deepChange->setCurrentIndex(1);
		buttonCheck->setCurrentIndex(1);
		});
	connect(btnStop, &QPushButton::clicked, this, [this,deepChange = deepChange, buttonCheck = buttonCheck]() {
		deepChange->setCurrentIndex(0);
		buttonCheck->setCurrentIndex(0);
		});
	connect(btnReTry, &QPushButton::clicked, btnStart, &QPushButton::clicked);
	task->connectWidget(this);
	connect(btnStart, &QPushButton::clicked, [this]() {
		QString format = comboFormat->currentText();
		int splitWay = comboSplit->currentIndex();
		format = "." + format;
		convparam conv = convparam::SINGLE;
		if (splitWay == 1) {
			conv = convparam::CHAPTERS;
		}
		emit this->startClicked(format, conv);
		});
	connect(btnStop, &QPushButton::clicked, [this]() {
		emit this->stopClicked();
		});
	connect(this, &TaskCellWidget::startAll, [this]() {
		if(this->buttonCheck->currentIndex() == 0 || this->buttonCheck->currentIndex() == 2)
			emit this->btnStart->clicked();
		});
	connect(this, &TaskCellWidget::stopAll, [this]() {
		if (this->buttonCheck->currentIndex() == 1)
			emit this->btnStop->clicked();
		});
	
}



void TaskTableWidget::addTask(ConvertTask* task)
{
	auto rowHt = TaskCellWidget::cellHeight();
	int idx = rowCount();
	insertRow(idx);
	setRowHeight(idx,rowHt);
	TaskCellWidget* cell = new TaskCellWidget(task);
	setCellWidget(idx, 0, cell);
	connect(cell, &TaskCellWidget::taskFinished, this, &TaskTableWidget::onCellTaskFinished);
	connect(this, &TaskTableWidget::startAll, cell, &TaskCellWidget::startAll);
	connect(this, &TaskTableWidget::stopAll, cell, &TaskCellWidget::stopAll);
}

int TaskTableWidget::rowOfCell(TaskCellWidget* cell) const
{
	int rowCnt = rowCount();
	for (int row = 0; row < rowCnt; row++) {
		if (cellWidget(row) == cell) {
			return row;
		}
	}
	return -1;
}
TaskCellWidget* TaskTableWidget::cellWidget(int row) const
{
	return static_cast<TaskCellWidget*>(QTableWidget::cellWidget(row, 0));
}

void TaskTableWidget::onCellTaskFinished(QString filepath)
{
	auto cell = static_cast<TaskCellWidget*>(sender());

	QFileInfo fileInfo = QFileInfo(filepath);
	if (fileInfo.isFile())
		QDir().rename(filepath, Settings::getInstance()->getSavePath() + QDir::separator() + fileInfo.fileName());
	else
		toMove(filepath, Settings::getInstance()->getSavePath());
	QTimer::singleShot(0, this, [=] {
		
		removeRow(this->rowOfCell(cell));
		});
}



TaskCellWidget::~TaskCellWidget()
{
	delete task;
}

int TaskCellWidget::cellHeight()
{
	auto lineSpacing = QFontMetrics(QApplication::font()).lineSpacing();
	auto style = QApplication::style();
	auto layoutTopMargin = style->pixelMetric(QStyle::PM_LayoutTopMargin);
	auto layoutBtmMargin = style->pixelMetric(QStyle::PM_LayoutBottomMargin);
	auto layoutSpacing = style->pixelMetric(QStyle::PM_LayoutVerticalSpacing);
	return lineSpacing * 2 + layoutTopMargin + layoutSpacing + layoutBtmMargin + 2+ TaskCellHeight;
}


void TaskCellWidget::setProgress(double rate) {
	this->progress->setValue(rate);

}
void TaskCellWidget::convertError() {
	this->buttonCheck->setCurrentIndex(2);
}


