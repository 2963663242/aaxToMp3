#include <AudibleConvert.h>





IAudibleConvert::IAudibleConvert()
{
}

IAudibleConvert::~IAudibleConvert()
{
}

QString IAudibleConvert::convert(AudibleMeta meta, QString filepath, convparam convp, QString ext)
{
	this->setStartState();
	std::thread obj([=]() {
		return this->process(meta, filepath, convp, ext);
		
	});
	obj.detach();
	return "";
}

QString IAudibleConvert::check_type(QString filepath)
{
	return AudibleConvert::check_type(filepath);
}

IAudibleConvert* IAudibleConvert::Create()
{
	return new AudibleConvert("C:\\Users\\Administrator\\AppData\\Roaming\\.EpuborAudible");
}

void IAudibleConvert::Release(IAudibleConvert* converter)
{
	delete converter;
}
