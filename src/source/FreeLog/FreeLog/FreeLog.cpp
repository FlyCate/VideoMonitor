#include "FreeLog.h"

#include <io.h>
#include <direct.h>
#include <thread>
#include <string>
#include "CIniFile.h"
#include <stdarg.h>
#include <iostream>

#include<log4cpp/PatternLayout.hh>
#include<log4cpp/OstreamAppender.hh>
#include<log4cpp/RollingFileAppender.hh>
#include<log4cpp/Priority.hh>

//整数类型文件行号 ->转换为string类型  std::to_string 处理
#ifdef _WIN32
#define __FILENAME__ (strrchr(__FILE__, '\\') ? (strrchr(__FILE__, '\\') + 1):__FILE__)
#else
#define __FILENAME__ (strrchr(__FILE__, '/') ? (strrchr(__FILE__, '/') + 1):__FILE__)
#endif

//读取配置文件回调函数
void ReadCfgThread(void * pUser)
{
	CFreeLog * pThis = (CFreeLog *)pUser;
	int nCount = 0;
	char szLogLevel[64] = { 0 };
	CIniFile ini;
	ini.SetIniFileName("LogConfig.ini");

	while (pThis->m_bExit == false)
	{
		if (nCount++ >= 10)
		{
			nCount = 0;
			//读取日志等级
			memset(szLogLevel, 0, 64);
			if (ini.ReadIni("FreeLog", "LogLevel", szLogLevel, 64) == true)
			{
				printf("loglevel : %s\n", szLogLevel);
			}
		}
		Sleep(1000);
	}
}

static bool check_dir(const char* dir)
{
	if (_access(dir, 0) == -1)
	{
		int flag = _mkdir(dir);
		return (flag == 0);
	}
	return true;
};

CFreeLog::CFreeLog():category_ref_(log4cpp::Category::getRoot())
{
	m_bInit = false;
	m_bExit = false;
	
	if (check_dir("logs") == false)
	{
		throw "创建日志文件目录logs 错误！";
	}
}


CFreeLog::~CFreeLog()
{
	m_bInit = false;
	m_bExit = true;
}

CFreeLogBase * CFreeLogBase::CreateFreeLogObject()
{
	return new CFreeLog();
}

void CFreeLog::SetLogFileName(const char * pLogFileName)
{
	if (m_bInit == true)
	{
		return;
	}

	m_strLogFileName = "logs/";
	m_strLogFileName.append(pLogFileName);
	
	//自定义输出格式
	log4cpp::PatternLayout *pattern_one =
		new log4cpp::PatternLayout;
	pattern_one->setConversionPattern("%d [%p] %m%n");

	log4cpp::PatternLayout *pattern_two =
		new log4cpp::PatternLayout;
	pattern_two->setConversionPattern("%d [%p] %m%n");

	//获取屏幕输出
	log4cpp::OstreamAppender *os_appender =
		new log4cpp::OstreamAppender("osAppender", &std::cout);
	os_appender->setLayout(pattern_one);

	//获取文件日志输出
	log4cpp::RollingFileAppender *file_appender =
		new log4cpp::RollingFileAppender("fileAppender", m_strLogFileName, 1024 * 1024 * 10, 30);
	file_appender->setLayout(pattern_two);

	category_ref_.setPriority(log4cpp::Priority::DEBUG);
	category_ref_.addAppender(os_appender);
	category_ref_.addAppender(file_appender);

	category_ref_.info("CFreeLog created!");

	m_bExit = false;
	std::thread tReadCfgThread(ReadCfgThread, this);
	tReadCfgThread.detach();

	m_bInit = true;
}

void CFreeLog::SetLogLevel(const LOG_LEVEL levelType)
{
	if (m_bInit == false)
	{
		return;
	}

	switch (levelType)
	{
	case LOG_LEVEL_ALERT:
		category_ref_.setPriority(log4cpp::Priority::ALERT);
		break;
	case LOG_LEVEL_DEBUG:
		category_ref_.setPriority(log4cpp::Priority::DEBUG);
		break; 
	case LOG_LEVEL_INFO:
		category_ref_.setPriority(log4cpp::Priority::INFO);
		break;
	case LOG_LEVEL_WARNING:
		category_ref_.setPriority(log4cpp::Priority::WARN);
		break;
	case LOG_LEVEL_ERROR:
		category_ref_.setPriority(log4cpp::Priority::ERROR);
		break;
	case LOG_LEVEL_CRITICLE:
		category_ref_.setPriority(log4cpp::Priority::CRIT);
		break;
	default:
		break;
	}
}

void CFreeLog::LogMessage(const LOG_LEVEL levelType, const char * pMsg, ...)
{
	if (m_bInit == false)
	{
		return;
	}

	char tmp[2048] = { 0 };
	va_list args;
	va_start(args, pMsg);
	vsprintf_s(tmp, pMsg, args);
	va_end(args);

	switch (levelType)
	{
	case LOG_LEVEL_ALERT:
		category_ref_.alert(tmp);
		break;
	case LOG_LEVEL_DEBUG:
		category_ref_.debug(tmp);
		break;
	case LOG_LEVEL_INFO:
		category_ref_.info(tmp);
		break;
	case LOG_LEVEL_WARNING:
		category_ref_.warn(tmp);
		break;
	case LOG_LEVEL_ERROR:
		category_ref_.error(tmp);
		break;
	case LOG_LEVEL_CRITICLE:
		category_ref_.crit(tmp);
		break;
	default:
		break;
	}
}
