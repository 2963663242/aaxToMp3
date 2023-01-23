#include <AudibleConvert.h>





IAudibleConvert::IAudibleConvert()
{
}

QString IAudibleConvert::check_type(QString filepath)
{
	return AudibleConvert::check_type(filepath);
}

IAudibleConvert* IAudibleConvert::Create()
{
	return new AudibleConvert("C:\\Users\\Administrator\\AppData\\Roaming\\.EpuborAudible");
}
