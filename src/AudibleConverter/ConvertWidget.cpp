#include "ConvertWidget.h"
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include "TaskTable.h"
#include <QtWidgets>
#include "IAudibleConvert.h"
ConvertWidget::ConvertWidget(QWidget* parent) :QWidget(parent) {
	
	addFile = new QPushButton(QString::fromLocal8Bit("添加文件"));
	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	QHBoxLayout* headerLayout = new QHBoxLayout;
	headerLayout->addItem(new QSpacerItem(10,0, QSizePolicy::Fixed));
	headerLayout->addWidget(addFile);
	headerLayout->addItem(new QSpacerItem(20, 0, QSizePolicy::Expanding));
	connect(addFile, &QPushButton::clicked, this, &ConvertWidget::importFile);
	
	TaskContainer = new TaskTableWidget;

	QHBoxLayout* footLayout = new QHBoxLayout;
	footLayout->setSpacing(0);
	
	footLayout->setContentsMargins(0, 0, 0, 0);
	allStart = new QPushButton(QString::fromLocal8Bit("全部开始"));
	allStop = new QPushButton(QString::fromLocal8Bit("全部停止"));

	footLayout->addItem(new QSpacerItem(20, 0, QSizePolicy::Expanding));
	footLayout->addWidget(allStart);
	footLayout->addWidget(allStop);
	footLayout->addItem(new QSpacerItem(10, 0, QSizePolicy::Fixed));
	
	footLayout->setMargin(0);
	mainLayout->addLayout(headerLayout);
	mainLayout->addWidget(TaskContainer);
	mainLayout->addLayout(footLayout);
	mainLayout->setContentsMargins(0, 0, 0, 0);
	/*QTimer::singleShot(0, [this]() {
		QString filePath = R"(D:\Users\Documents\WXWork\1688850575211706\Cache\File\2022-11\1.FabiFuchsundderverloreneNuss-SchatzFabiFuchs_ep7.aax)";
		ConvertTask* task = new ConvertTask(filePath);
		TaskContainer->addTask(task);
		});*/
	connect(allStart, &QPushButton::clicked, TaskContainer, &TaskTableWidget::startAll);
	connect(allStop, &QPushButton::clicked, TaskContainer, &TaskTableWidget::stopAll);
	
}

void ConvertWidget::importFile() {
	QString fileName = QFileDialog::getOpenFileName(this,
		QString::fromLocal8Bit("打开一个Audible文件"),
		"C:/",
		"Audible(*.aax *.aa)");
	if (fileName.isEmpty())
		return;
	QString type = IAudibleConvert::check_type(fileName);
	if (type == "aax" || type == "aa") {
		QTimer::singleShot(0, [this,filePath=fileName]() {
			ConvertTask * task = new ConvertTask(filePath);
			TaskContainer->addTask(task);
			});
	}
	else {
		
		QMessageBox msgBox(QString::fromLocal8Bit("错误"),		///--这里是设置消息框标题
			QString::fromLocal8Bit("不是有效的Audible文件"),						///--这里是设置消息框显示的内容
			QMessageBox::Critical,							///--这里是在消息框显示的图标
			QMessageBox::Ok | QMessageBox::Default,		///---这里是显示消息框上的按钮情况
			QMessageBox::Cancel | QMessageBox::Escape,	///---这里与 键盘上的 escape 键结合。当用户按下该键，消息框将执行cancel按钮事件
			0);
		msgBox.exec();
	}
}