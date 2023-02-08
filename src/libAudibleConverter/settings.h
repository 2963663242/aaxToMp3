#include <QString>
#include <fstream>
#include <mutex>
#include <plog/Log.h> // Step1: include the headers
#include <plog/Initializers/RollingFileInitializer.h>
#include <QDir>
using namespace std;

#define LOGNAME QDir::separator() + "AudibleConverter_info.txt"

class settings {
public:

	settings();


public:
	 QString coverpath;
	 QString outputPath; 
	plog::RollingFileAppender<plog::TxtFormatter> fileAppender;
};


extern  settings setting;

class FuncPrint
{
public:
	FuncPrint(string func, void * Audible=0)
	{
		func_name = func;
		this->Audible = Audible;
		PLOGD << Audible << "<<<<<<Enter function: " << func_name ;
		
	}

	~FuncPrint()
	{
		PLOGD << Audible << ">>>>>>Exit function: " << func_name;
		
	}

private:
	string func_name;
	void* Audible;
};


#define FUNCTINLOG FuncPrint logger(__FUNCSIG__,this);
#define FUNCLOG FuncPrint logger(__FUNCSIG__);

#define THREADSAFE static std::mutex mtx;std::lock_guard<std::mutex> lockGuard(mtx);
