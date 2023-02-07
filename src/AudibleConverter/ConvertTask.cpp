#include "ConvertTask.h"
#include "TaskTable.h"
#include <QTemporaryDir>

void ConvertSTATECALLBACK::stateInform(ItemTable item) {
	if (item.st == status::downloading)
		emit this->updateProgress(item.rate);
	else if (item.st == status::finished) {
		emit this->convertFinished(item.filepath);
	}
	else if(item.st == status::error){
		emit this->convertError();
	}

}

ConvertTask::ConvertTask(QString filename,QString  savePath) :filename(filename) {
	this->tmp = nullptr;
	
	cb = new ConvertSTATECALLBACK;
	this->converter = IAudibleConvert::Create();
	setSavePath(savePath);
	converter->setCallback(cb);
	meta = this->converter->getMeta(filename);
	
	
}

ConvertTask::~ConvertTask()
{
	IAudibleConvert::Release(converter);
	delete cb;
	delete tmp;
}

void ConvertTask::connectWidget(TaskCellWidget* parent)
{
	QObject::connect(this->cb, &ConvertSTATECALLBACK::updateProgress, parent, &TaskCellWidget::setProgress);
	QObject::connect(parent, &TaskCellWidget::startClicked, this, &ConvertTask::start);
	QObject::connect(parent, &TaskCellWidget::stopClicked, this, &ConvertTask::stop);
	connect(cb, &ConvertSTATECALLBACK::convertFinished, parent, &TaskCellWidget::taskFinished);
	connect(cb, &ConvertSTATECALLBACK::convertError, parent, &TaskCellWidget::convertError);

}

void ConvertTask::setSavePath(QString savePath)
{
	if (tmp != nullptr)
	{
		delete tmp;
		tmp = nullptr;
	}
	 this->tmp = new QTemporaryDir(savePath+"/");
	this->savePath = tmp->path();
	this->converter->setSavePath(this->savePath);
}

QString ConvertTask::getSavePath()
{
	return this->savePath;
}

void ConvertTask::stop()
{
	this->converter->stop();
}


void ConvertTask::start(QString format, convparam splitway) {
	this->converter->convert(meta,filename, splitway,format);
}