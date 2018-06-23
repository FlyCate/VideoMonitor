#pragma once
#include "log.h"
#include <string>

//媒体类型
enum MONITOR_MEDIA_TYPE
{
	MONITOR_MEDIA_TYPE_VIDEO = 1,
	MONITOR_MEDIA_TYPE_AUDIO = 2,
	MONITOR_MEDIA_TYPE_OTHER = 99
};

//媒体流回调函数
typedef void(*MediaCallBack) (const char * pBuf, const long & lBuflen, const MONITOR_MEDIA_TYPE & type);

//定义一个在日志后添加 文件名 函数名 行号 的宏定义
#ifndef suffix
#define suffix(msg)  std::string(msg).append("  //")\
        .append(__FILENAME__).append(":").append(__func__)\
        .append("()#").append(std::to_string(__LINE__))\
        .append(".").c_str()
#endif