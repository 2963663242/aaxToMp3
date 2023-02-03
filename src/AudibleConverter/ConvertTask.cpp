#include "ConvertTask.h"
#include "TaskTable.h"


void ConvertSTATECALLBACK::stateInform(ItemTable item) {
	if (item.st == status::downloading)
		emit this->updateProgress(item.rate);
	else if (item.st == status::finished && !item.filepath.isEmpty()) {
		emit this->convertFinished();
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
	IAudibleConvert::Release(converter);
	delete cb;
}

void ConvertTask::connectWidget(TaskCellWidget* parent)
{
	QObject::connect(this->cb, &ConvertSTATECALLBACK::updateProgress, parent, &TaskCellWidget::setProgress);
	QObject::connect(parent, &TaskCellWidget::startClicked, this, &ConvertTask::start);
	QObject::connect(parent, &TaskCellWidget::stopClicked, this, &ConvertTask::stop);
	connect(cb, &ConvertSTATECALLBACK::convertFinished, parent, &TaskCellWidget::taskFinished);
}

void ConvertTask::stop()
{
	this->converter->stop();
}


void ConvertTask::start(QString format, convparam splitway) {
	this->converter->convert(meta,filename, splitway,format);
}