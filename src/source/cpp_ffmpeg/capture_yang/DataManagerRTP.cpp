#include "DataManagerRTP.h"



CDataManagerRTP::CDataManagerRTP()
{
}


CDataManagerRTP::~CDataManagerRTP()
{
}

long CDataManagerRTP::PushData(const char * pData, const long lDataLen)
{
	if ((pData == nullptr) || (lDataLen == 0))
	{
		return -1;
	}

	STRU_DATA objData;
	objData.pData = (char *)pData;
	objData.lDataLen = lDataLen;
	std::lock_guard<std::mutex> lock(m_mutexData);
	m_vData.push(objData);

	return 0;
}
