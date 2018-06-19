#include "DataManagerBase.h"

CDataManagerBase::CDataManagerBase()
{
}

CDataManagerBase::~CDataManagerBase()
{
}

long CDataManagerBase::GetDataSize()
{
	std::lock_guard<std::mutex> lock(m_mutexData);
	return m_vData.size();
}

long CDataManagerBase::GetData(char ** pData, long & lDataLen)
{
	if (GetDataSize() <= 0)
	{
		return -1;
	}

	std::lock_guard<std::mutex> lock(m_mutexData);
	*pData = m_vData.front().pData;
	lDataLen = m_vData.front().lDataLen;
	m_vData.pop();

	return 0;
}

