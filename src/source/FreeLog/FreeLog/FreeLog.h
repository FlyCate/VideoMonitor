#pragma once
#include "log.h"
#include "log4cpp/Category.hh"
#include <string>

class CFreeLog : public CFreeLogBase
{
public:
	CFreeLog();
	~CFreeLog();

public:
	virtual void SetLogFileName(const char * pLogFileName);
	virtual void SetLogLevel(const LOG_LEVEL levelType);
	virtual void LogMessage(const LOG_LEVEL levelType, const char * pMsg, ...);

private:
	bool m_bInit;
	std::string m_strLogFileName;
	log4cpp::Category &category_ref_;

public:
	bool m_bExit;
};

