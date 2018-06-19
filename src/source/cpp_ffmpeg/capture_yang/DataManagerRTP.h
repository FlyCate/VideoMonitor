#pragma once
#include "DataManagerBase.h"
class CDataManagerRTP :
	public CDataManagerBase
{
public:
	CDataManagerRTP();
	~CDataManagerRTP();

	virtual long PushData(const char * pData, const long lDataLen);
};

