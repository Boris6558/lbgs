#include "configmanager.h"
#include "configinterface.h"
#include "sysinfomodule/sysinfo.h"
#include "gateserverconfig/gateserverconfig.h"
#include "proxyserverconfig/proxyserverconfig.h"
#include <logmodule/logdef.h>


#define NEW_CONFIG(className)	m_pArrConfigs[DENUM(className)] = new className

ConfigManager::ConfigManager()
{
	NEW_CONFIG(GateServerConfig);
	NEW_CONFIG(ProxyServerConfig);
	BOOST_STATIC_ASSERT(TYPE_MAX == 2);

	// config path
	m_cfgPath[DENUM(GateServerConfig)] = "server/server.xml";
	m_cfgPath[DENUM(ProxyServerConfig)] = "server/server.xml";
	BOOST_STATIC_ASSERT(TYPE_MAX == 2);

	// check
	for (int i = 0; i < TYPE_MAX; ++i)
	{
		if (m_pArrConfigs[i] == NULL)
		{
			LOG_SERVER_COMMON_CONFIG.printLog("m_pArrConfigs[%d] is NULL", i);
			BOOST_ASSERT(0);
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

