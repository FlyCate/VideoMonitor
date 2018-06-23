#ifndef _CHECK_DIR_
#define _CHECK_DIR_

#ifdef FREELOG_EXPORTS
#define FREELOG_API __declspec(dllexport)
#else
#define FREELOG_API __declspec(dllimport)
#pragma comment(lib,"FreeLog.lib")
#endif

enum LOG_LEVEL
{
	LOG_LEVEL_DEBUG = 1,
	LOG_LEVEL_INFO = 2,
	LOG_LEVEL_WARNING = 3,
	LOG_LEVEL_ERROR = 4,
	LOG_LEVEL_CRITICLE = 5,
	LOG_LEVEL_ALERT = 6
};

//日志类，先调用 SetLogFileName
class FREELOG_API CFreeLogBase
{
public:
	virtual ~CFreeLogBase() {};

public:
	static CFreeLogBase * CreateFreeLogObject();
	virtual void SetLogFileName(const char * pLogFileName) = 0;
	virtual void SetLogLevel(const LOG_LEVEL levelType) = 0;
	virtual void LogMessage(const LOG_LEVEL levelType, const char * pMsg, ...) = 0;
};

#endif