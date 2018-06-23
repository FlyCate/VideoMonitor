#include "CIniFile.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

CIniFile::CIniFile()
{
	m_fileName = new char[4096];
}

CIniFile::~CIniFile()
{
	delete[] m_fileName;
}

//pFileName仅为 ini文件名称 不带路径
//ini文件路径有两种：1.从环境变量读取,安装整套系统的时候,写环境变量  2.固定路径
//使用者 不需要关心ini 路径问题 有ini配置库自己判断完成
bool CIniFile::SetIniFileName(const char * pFileName)
{
	if ((pFileName == NULL)||(strlen(pFileName) > 256))
	{
		return false;
	}
	ZeroMemory(m_fileName, 4096);
	int ret = GetEnvironmentVariable("SystemConfig", m_fileName, 4096);//读环境变量 QWconfiguration
	if (ret != 0)
	{
		printf("SystemConfig: %s\n", m_fileName);
		if ((m_fileName[ret-1] != '\\')&&(m_fileName[ret-1] != '/'))
		{
			m_fileName[ret] = '\\';
		}
	}
	else//读失败  用固定路径 C:/QWconfig/
	{
		printf("Read SystemConfig Error!\n");
		printf("SystemConfig: C:\\SystemConfig\\\n");
		sprintf(m_fileName, "C:\\SystemConfig\\");
	}

	strcat(m_fileName, pFileName);
	return true;
}

//写ini文件
bool CIniFile::WriteIni(const char * pKeyName, const char * pItemName, const char * pParam)
{
	if(TRUE == WritePrivateProfileString(pKeyName, pItemName, pParam, m_fileName))
		return true;
	else
		return false;
}

bool CIniFile::WriteIni(const char * pKeyName, const char * pItemName, const int iParam)
{
	char tmp[64] = {0};
	sprintf(tmp, "%d", iParam);
	if(TRUE == WritePrivateProfileString(pKeyName, pItemName, tmp, m_fileName))
		return true;
	else
		return false;
}

bool CIniFile::WriteIni(const char * pKeyName, const char * pItemName, const float iParam)
{
	char tmp[64] = {0};
	sprintf(tmp, "%f", iParam);
	if(TRUE == WritePrivateProfileString(pKeyName, pItemName, tmp, m_fileName))
		return true;
	else
		return false;
}

bool CIniFile::WriteIni(const char * pKeyName, const char * pItemName, const double iParam)
{
	char tmp[64] = {0};
	sprintf(tmp, "%lf", iParam);
	if(TRUE == WritePrivateProfileString(pKeyName, pItemName, tmp, m_fileName))
		return true;
	else
		return false;
}

//读ini文件
bool CIniFile::ReadIni(const char * pKeyName, const char * pItemName, char * pParam, const int iParamLen)
{
	int ret = GetPrivateProfileString(pKeyName, pItemName, NULL, pParam, iParamLen, m_fileName);
	if (ret > 0)
		return true;
	else
		return false;
}

bool CIniFile::ReadIni(const char * pKeyName, const char * pItemName, int & iParam)
{
	char tmp[64] = {0};
	int ret = GetPrivateProfileString(pKeyName, pItemName, NULL, tmp, 64, m_fileName);
	if (ret > 0)
	{
		iParam = atoi(tmp);
		return true;
	}
	else
		return false;
}

bool CIniFile::ReadIni(const char * pKeyName, const char * pItemName, float & iParam)
{
	char tmp[64] = {0};
	int ret = GetPrivateProfileString(pKeyName, pItemName, NULL, tmp, 64, m_fileName);
	if (ret > 0)
	{
		iParam = (float)atof(tmp);
		return true;
	}
	else
		return false;
}

bool CIniFile::ReadIni(const char * pKeyName, const char * pItemName, double & iParam)
{
	char tmp[64] = {0};
	int ret = GetPrivateProfileString(pKeyName, pItemName, NULL, tmp, 64, m_fileName);
	if (ret > 0)
	{
		iParam = strtod (tmp, NULL);
		return true;
	}
	else
		return false;
}