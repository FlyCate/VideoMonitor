#pragma once

#include "common.h"

class CCommunicationBase
{
public:
	CCommunicationBase();
	virtual ~CCommunicationBase();

public:
	virtual int Init(MediaCallBack pCallBack) = 0;
	virtual int Fini() = 0;
	virtual int StartPlay() = 0;
	virtual int StopPlay() = 0;

protected:
	MediaCallBack m_VideoCallBack;
};

