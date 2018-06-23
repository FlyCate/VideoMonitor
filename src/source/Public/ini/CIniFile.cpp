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

//pFileName��Ϊ ini�ļ����� ����·��
//ini�ļ�·�������֣�1.�ӻ���������ȡ,��װ����ϵͳ��ʱ��,д��������  2.�̶�·��
//ʹ���� ����Ҫ����ini ·������ ��ini���ÿ��Լ��ж����
bool CIniFile::SetIniFileName(const char * pFileName)
{
	if ((pFileName == NULL)||(strlen(pFileName) > 256))
	{
		return false;
	}
	ZeroMemory(m_fileName, 4096);
	int ret = GetEnvironmentVariable("SystemConfig", m_fileName, 4096);//���������� QWconfiguration
	if (ret != 0)
	{
		printf("SystemConfig: %s\n", m_fileName);
		if ((m_fileName[ret-1] != '\\')&&(m_fileName[ret-1] != '/'))
		{
			m_fileName[ret] = '\\';
		}
	}
	else//��ʧ��  �ù̶�·�� C:/QWconfig/
	{
		printf("Read SystemConfig Error!\n");
		printf("SystemConfig: C:\\SystemConfig\\\n");
		sprintf(m_fileName, "C:\\SystemConfig\\");
	}

	strcat(m_fileName, pFileName);
	return true;
}

//дini�ļ�
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

//��ini�ļ�
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