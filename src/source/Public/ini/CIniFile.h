#ifndef _C_INIFILE_
#define _C_INIFILE_

class CIniFile
{
public:
	CIniFile();
	~CIniFile();

public:
	//ini文件结构 示例：
	//
	//	[student]
	//	name="XiaoMing"
	//
	//参数说明
	//  pKeyName  指的是 [student]
	//  pItemName 指的是 name
	//写ini文件
	bool WriteIni(const char * pKeyName, const char * pItemName, const char * pParam);
	bool WriteIni(const char * pKeyName, const char * pItemName, const int iParam);
	bool WriteIni(const char * pKeyName, const char * pItemName, const float iParam);
	bool WriteIni(const char * pKeyName, const char * pItemName, const double iParam);
	//读ini文件
	bool ReadIni(const char * pKeyName, const char * pItemName, char * pParam, const int iParamLen);
	bool ReadIni(const char * pKeyName, const char * pItemName, int & iParam);
	bool ReadIni(const char * pKeyName, const char * pItemName, float & iParam);
	bool ReadIni(const char * pKeyName, const char * pItemName, double & iParam);

	//pFileName仅为 ini文件名称 不带路径
	//ini文件路径有两种：1.从环境变量读取,安装整套系统的时候,写环境变量  2.固定路径
	//使用者 不需要关心ini 路径问题 有ini配置库自己判断完成
	bool SetIniFileName(const char * pFileName);

private:
	//保存ini文件名称 不带路径
	char * m_fileName;
};

#endif