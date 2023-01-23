#include <AudibleConvert.h>





IAudibleConvert::IAudibleConvert()
{
}

QString IAudibleConvert::check_type(QString filepath)
{
	return AudibleConvert::check_type(filepath);
}

shared_ptr<IAudibleConvert> IAudibleConvert::Create()
{
	return make_shared<AudibleConvert>("C:\\Users\\Administrator\\AppData\\Roaming\\.EpuborAudible");
}
