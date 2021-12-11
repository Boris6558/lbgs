#ifndef __LOG_H__
#define __LOG_H__

#include "boostcommondef/basedef.h"
#include "basedef.h"

/************************************************************************/
/* ��־ģ��
/* ע�⣺ÿ�ε���ǰ���ȵ���setLogHeader()��������֤��¼���ֲ���Ϣ���ļ�������������������

������־����:
	1.����log.cpp namespace CommonLog�ﶨ��LogModule����
	2.��logdef.h ����Զ��������

/************************************************************************/

namespace
{
const int g_nPrintMaxSize = 1024;
const int g_nPrintHeaderMaxSize = 128;
}

class LogModule
{
public:
	enum Level
	{
		LV_INFO,
		LV_WARNING,
		LV_ERROR,
	};

	enum LogType
	{
		TYPE_DAILY,
		TYPE_ROTATING,
	};

public:
	LogModule(const std::string& logFilePath, int level = LogModule::LV_INFO, int logType = LogModule::TYPE_DAILY);
	~LogModule();

	void setLogDir(const std::string dir);
	LogModule& setLevel(int level);
	LogModule& setLogHeader(
		const char* function,
		const char* file,
		int line,
		int threadId = THREAD_ID
	);
	void printLog(const char* format, ...);

private:
	int m_level;
	int m_logType;
	int m_lastLevel;
	bool m_isTemporaryEffect;

	// daily ����ʱ��
	int m_nHours;
	int m_nMin;

	// rotating ��������
	int m_rotatingLogMaxSize;
	int g_rotatingLogMaxFiles;

	// header ��Ϣ
	std::string m_fileName;
	int m_line;
	std::string m_functionName;
	int m_threadId;

	std::string m_logDir;
	std::string m_logFilePath;

	char m_strPrintHeader[g_nPrintHeaderMaxSize];
	char m_strPrintCont[g_nPrintMaxSize];

	Common::LoggerPtr m_pLog;
	std::string m_logString;

	CommonBoost::Mutex m_contentMutex;
	CommonBoost::Mutex m_headerMutex;
};

namespace CommonLog
{
extern 	std::vector<LogModule*> g_vecLogModule;

extern LogModule g_logGateServer;
extern LogModule g_logServerCommonConfig;
}

#endif // !__LOG_H__
