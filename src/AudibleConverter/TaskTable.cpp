#include "TaskTable.h"
#include <QtWidgets>


TaskTableWidget::TaskTableWidget(QWidget* parent):QTableWidget(parent) {
	horizontalHeader()->hide();
	verticalHeader()->hide();
	setColumnCount(1);
	horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	setStyleSheet("QTableWidget {"
		"selection-background-color: rgb(227, 227, 229);"
		"}");
	/*for (int i = 0; i < 3; i++) {
		
		QString filePath = QString::fromLocal8Bit(R"(D:\Users\Downloads\TheGreatestMenaceInsidetheGayPrisonExperiment_ep7.aax)");
		ConvertTask task(filePath);
		addTask(task);
	}*/
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
	auto btnset = [](QPushButton * btn) {
		btn->setFixedSize(TaskCellHeight - 10, 50);
		QWidget* w = new QWidget();
		QVBoxLayout* lay1 = new QVBoxLayout(w);
		lay1->addWidget(btn, 1, Qt::AlignHCenter);
		return w;
	};
	
	buttonCheck->addWidget(btnset(btnStart));
	buttonCheck->addWidget(btnset(btnStop));
	
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

}

void TaskTableWidget::addTask(ConvertTask* task)
{
	auto rowHt = TaskCellWidget::cellHeight();
	int idx = rowCount();
	insertRow(idx);
	setRowHeight(idx,rowHt);
	setCellWidget(idx, 0, new TaskCellWidget(task));
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

ConvertTask::ConvertTask(QString filenamet) :filename(filename){
	cb = new ConvertSTATECALLBACK;
	this->converter = IAudibleConvert::Create();
	converter->setCallback(cb);
	meta = this->converter->getMeta(filename);
}

