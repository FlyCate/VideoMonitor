#pragma once
#include "log.h"
#include <string>

//ý������
enum MONITOR_MEDIA_TYPE
{
	MONITOR_MEDIA_TYPE_VIDEO = 1,
	MONITOR_MEDIA_TYPE_AUDIO = 2,
	MONITOR_MEDIA_TYPE_OTHER = 99
};

//ý�����ص�����
typedef void(*MediaCallBack) (const char * pBuf, const long & lBuflen, const MONITOR_MEDIA_TYPE & type);

//����һ������־����� �ļ��� ������ �к� �ĺ궨��
#ifndef suffix
#define suffix(msg)  std::string(msg).append("  //")\
        .append(__FILENAME__).append(":").append(__func__)\
        .append("()#").append(std::to_string(__LINE__))\
        .append(".").c_str()
#endif