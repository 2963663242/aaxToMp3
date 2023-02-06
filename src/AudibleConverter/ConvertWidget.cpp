#include "ConvertWidget.h"
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include "TaskTable.h"
#include <QtWidgets>
#include "IAudibleConvert.h"
ConvertWidget::ConvertWidget(QWidget* parent) :QWidget(parent) {
	
	addFile = new QPushButton(QString::fromLocal8Bit("����ļ�"));
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
	allStart = new QPushButton(QString::fromLocal8Bit("ȫ����ʼ"));
	allStop = new QPushButton(QString::fromLocal8Bit("ȫ��ֹͣ"));

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
		QString::fromLocal8Bit("��һ��Audible�ļ�"),
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
		
		QMessageBox msgBox(QString::fromLocal8Bit("����"),		///--������������Ϣ�����
			QString::fromLocal8Bit("������Ч��Audible�ļ�"),						///--������������Ϣ����ʾ������
			QMessageBox::Critical,							///--����������Ϣ����ʾ��ͼ��
			QMessageBox::Ok | QMessageBox::Default,		///---��������ʾ��Ϣ���ϵİ�ť���
			QMessageBox::Cancel | QMessageBox::Escape,	///---������ �����ϵ� escape ����ϡ����û����¸ü�����Ϣ��ִ��cancel��ť�¼�
			0);
		msgBox.exec();
	}
}