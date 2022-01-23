#include "configmanager.h"
#include "configinterface.h"
#include "sysinfomodule/sysinfo.h"
#include <logmodule/logdef.h>
#include <gateserver/export/export.h>
#include <proxyserver/export/export.h>

ConfigManager::ConfigManager()
{
	// ����config�ĵ����ӿ�
	loadGateServerConfig();
	loadProxyServerConfig();

	// config path
	m_cfgPath[DENUM(GateServerConfig)] = "server/server.xml";
	m_cfgPath[DENUM(ProxyServerConfig)] = "server/server.xml";

	// check
	for (int i = 0; i < TYPE_MAX; ++i)
	{
		if (m_pArrConfigs[i] == NULL)
		{
			/*
				����Ҳ�п���ʱ��Ӧ�Ľ���û������������gateserver��proxyserver���õ��������ļ���
				gateserver����������ʼ�������ļ�������proxyserverû������loadProxyServerConfigʱ����
				�����ӿ�new Config��ʧ��
				proxyserver ������Ҳ�����

				ֻ��ʼ�������̵�����
			*/
			LOG_SERVER_COMMON_CONFIG.printLog("m_pArrConfigs[%d] is NULL", i);
		}
	}

	initAllConfig();
}

ConfigManager::~ConfigManager()
{
	for (int i = 0; i < TYPE_MAX; ++i)
	{
		if (m_pArrConfigs[i])
		{
			delete m_pArrConfigs[i];
			m_pArrConfigs[i] = NULL;
			LOG_SERVER_COMMON_CONFIG.printLog("m_pArrConfigs[%d] has delete", i);
		}
	}
}

ConfigManager* ConfigManager::instance()
{
	static ConfigManager cm;
	return &cm;
}

void ConfigManager::initAllConfig()
{
	for (int i = 0; i < TYPE_MAX; ++i)
	{
		if (!m_pArrConfigs[i])
		{
			continue;
		}

		if (m_pArrConfigs[i]->init(m_cfgPath[i]) != ConfigInterface::INIT_OK)
		{
			LOG_SERVER_COMMON_CONFIG.printLog("m_pArrConfigs[%d] init error,path[%s]", i, m_cfgPath[i].data());
		}

	}

	LOG_SERVER_COMMON_CONFIG.printLog("all config has been init!!!!");
}

void ConfigManager::loadGateServerConfig()
{
	if(SystemInfo::isProcessRuning("gateserver.exe") && 
		SystemInfoNS::g_strCurProcessName == "gateserver.exe")
	{
		m_libGateServerConfig.load(EXE_DIR"/gateserver.exe");
		if(m_libGateServerConfig.has("getGateServerConfig"))
		{
			auto& funGetGateServerConfig = m_libGateServerConfig.get<GateServerConfig* (void)>("getGateServerConfig");
			m_pArrConfigs[DENUM(GateServerConfig)] = funGetGateServerConfig();
		}
	}
	
}

void ConfigManager::loadProxyServerConfig()
{
	if(SystemInfo::isProcessRuning("proxyserver.exe") &&
		SystemInfoNS::g_strCurProcessName == "proxyserver.exe")
	{
		m_libProxyServerConfig.load(EXE_DIR"/proxyserver.exe");
		if(m_libProxyServerConfig.has("getProxyServerConfig"))
		{
			auto& funGetProxyServerConfig = m_libProxyServerConfig.get<ProxyServerConfig* (void)>("getProxyServerConfig");
			m_pArrConfigs[DENUM(ProxyServerConfig)] = funGetProxyServerConfig();
		}
	}
}
