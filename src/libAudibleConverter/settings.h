#include <QString>
#include <fstream>
#include <plog/Log.h> // Step1: include the headers
#include <plog/Initializers/RollingFileInitializer.h>
using namespace std;
class settings {
public:

	settings();


public:
	 QString coverpath;
	 QString outputPath;
	 std::ofstream g_OutputDebug;
};
void myMessageOutput(QtMsgType type, const QMessageLogContext& context, const QString& msg);

extern  settings setting;

class FuncPrint
{
public:
	FuncPrint(string func)
	{
		func_name = func;
		PLOGD << "<<<<<<Enter function: " << func_name ;
		
	}

	~FuncPrint()
	{
		PLOGD << ">>>>>>Exit function: " << func_name;
		
	}

private:
	string func_name;
};

#define FUNCTINLOG FuncPrint logger(std::string(__FUNCSIG__));
