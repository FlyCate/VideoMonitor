#ifndef _C_INIFILE_
#define _C_INIFILE_

class CIniFile
{
public:
	CIniFile();
	~CIniFile();

public:
	//ini�ļ��ṹ ʾ����
	//
	//	[student]
	//	name="XiaoMing"
	//
	//����˵��
	//  pKeyName  ָ���� [student]
	//  pItemName ָ���� name
	//дini�ļ�
	bool WriteIni(const char * pKeyName, const char * pItemName, const char * pParam);
	bool WriteIni(const char * pKeyName, const char * pItemName, const int iParam);
	bool WriteIni(const char * pKeyName, const char * pItemName, const float iParam);
	bool WriteIni(const char * pKeyName, const char * pItemName, const double iParam);
	//��ini�ļ�
	bool ReadIni(const char * pKeyName, const char * pItemName, char * pParam, const int iParamLen);
	bool ReadIni(const char * pKeyName, const char * pItemName, int & iParam);
	bool ReadIni(const char * pKeyName, const char * pItemName, float & iParam);
	bool ReadIni(const char * pKeyName, const char * pItemName, double & iParam);

	//pFileName��Ϊ ini�ļ����� ����·��
	//ini�ļ�·�������֣�1.�ӻ���������ȡ,��װ����ϵͳ��ʱ��,д��������  2.�̶�·��
	//ʹ���� ����Ҫ����ini ·������ ��ini���ÿ��Լ��ж����
	bool SetIniFileName(const char * pFileName);

private:
	//����ini�ļ����� ����·��
	char * m_fileName;
};

#endif