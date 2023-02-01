#include "ConvertWidget.h"
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
ConvertWidget::ConvertWidget(QWidget* parent) :QWidget(parent) {
	
	addFile = new QPushButton(QString::fromLocal8Bit("Ìí¼ÓÎÄ¼þ"));
	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	QHBoxLayout* headerLayout = new QHBoxLayout;
	headerLayout->addItem(new QSpacerItem(20,0));
	headerLayout->addWidget(addFile);
	headerLayout->addItem(new QSpacerItem(20, 0));

	TaskContainer = new QGroupBox;
	mainLayout->addLayout(headerLayout);
	mainLayout->addWidget(TaskContainer);

}