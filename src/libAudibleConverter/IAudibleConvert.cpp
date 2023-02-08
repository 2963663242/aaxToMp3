#include <AudibleConvert.h>
#include "settings.h"




IAudibleConvert::IAudibleConvert()
{
	FUNCTINLOG
}

IAudibleConvert::~IAudibleConvert()
{
	FUNCTINLOG
}

QString IAudibleConvert::convert(AudibleMeta meta, QString filepath, convparam convp, QString ext)
{
	FUNCTINLOG
	this->setStartState();
	std::thread obj([=]() {
		return this->process(meta, filepath, convp, ext);
		
	});
	obj.detach();
	return "";
}

QString IAudibleConvert::check_type(QString filepath)
{
	FUNCLOG
	return AudibleConvert::check_type(filepath);
}

IAudibleConvert* IAudibleConvert::Create()
{
	FUNCLOG
	return new AudibleConvert("C:\\Users\\Administrator\\AppData\\Roaming\\.AAXConverter");
}

void IAudibleConvert::Release(IAudibleConvert* converter)
{
	FUNCLOG
	delete converter;
}

void IAudibleConvert::setLogPath(QString logPath)
{
	setting.fileAppender.setFileName((logPath + LOGNAME).toUtf8());
}


