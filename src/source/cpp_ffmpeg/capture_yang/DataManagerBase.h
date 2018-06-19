#pragma once
#include <Queue>
#include <mutex>

typedef struct STRU_Data
{
	char * pData;
	long   lDataLen;

	void Reset()
	{
		pData = nullptr;
		lDataLen = 0;
	}

	STRU_Data()
	{
		Reset();
	}

	~STRU_Data()
	{
		Reset();
	}
}STRU_DATA;

class CDataManagerBase
{
public:
	CDataManagerBase();
	virtual ~CDataManagerBase();

public:
	long GetDataSize();
	long GetData(char ** pData, long & lDataLen);
	virtual long PushData(const char * pData, const long lDataLen) = 0;
	
protected:
	std::mutex			m_mutexData;
	std::queue<STRU_DATA>	m_vData;
};

