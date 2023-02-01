#include "ConvertWidget.h"
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
ConvertWidget::ConvertWidget(QWidget* parent) :QWidget(parent) {
	
	addFile = new QPushButton(QString::fromLocal8Bit("添加文件"));
	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	QHBoxLayout* headerLayout = new QHBoxLayout;
	headerLayout->addItem(new QSpacerItem(10,0, QSizePolicy::Fixed));
	headerLayout->addWidget(addFile);
	headerLayout->addItem(new QSpacerItem(20, 0, QSizePolicy::Expanding));
	TaskContainer = new QGroupBox;
	TaskContainer->setContentsMargins(0, 0, 0, 0);
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
	
}