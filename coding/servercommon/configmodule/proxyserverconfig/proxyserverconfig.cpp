#include "proxyserverconfig.h"

#include <servercommon/logmodule/logdef.h>
#include <servercommon/commontool/commontool.h>

ProxyServerConfig::ProxyServerConfig()
{
}

ProxyServerConfig::~ProxyServerConfig()
{
}

int ProxyServerConfig::init(const std::string& path)
{
	LOAD_NODE("config.proxyserver", initInfoCfg);
	return INIT_OK;
}

int ProxyServerConfig::initInfoCfg(CommonBoost::PTree& rootNode)
{
	CommonBoost::PTree::iterator it = rootNode.begin();
	
	for(; it != rootNode.end(); ++it)
	{
		CommonBoost::PTree dataNode = it->second;

		m_info.ip = dataNode.get_child("ip").data();
		m_info.port = CAST_TO(ushort, dataNode.get_child("port").data());

		if(!CommonTool::isIpFormat(m_info.ip))
		{
			LOG_PROXYSERVER.printLog("ip read error");
			return ERROR_IP;
		}
		if(m_info.port <= 0 || m_info.port > 65535)
		{
			LOG_PROXYSERVER.printLog("port read error");
			return ERROR_PORT;
		}
	}

	return INIT_OK;
}
