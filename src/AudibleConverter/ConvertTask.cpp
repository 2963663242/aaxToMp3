#include "ConvertTask.h"
#include "TaskTable.h"


void ConvertSTATECALLBACK::stateInform(ItemTable item) {
	if (item.st == status::downloading)
		qDebug() << item.rate;
	else if (item.st == status::finished) {
		qDebug() << "convert finished . filepath: " << item.filepath;
	}

}

ConvertTask::ConvertTask(QString filename) :filename(filename) {
	cb = new ConvertSTATECALLBACK;
	this->converter = IAudibleConvert::Create();
	converter->setCallback(cb);
	meta = this->converter->getMeta(filename);
}

ConvertTask::~ConvertTask()
{
	delete converter;
	delete cb;
}

void ConvertTask::connectWidget(TaskCellWidget* parent)
{
	QObject::connect(this->cb, &ConvertSTATECALLBACK::updateProgress, parent, &TaskCellWidget::setProgress);
}
