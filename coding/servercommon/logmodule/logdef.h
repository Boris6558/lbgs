#ifndef __LOG_DEF_H__
#define __LOG_DEF_H__

#include "log.h"

#define LOG_GATESERVER					CommonLog::g_logGateServer.setLogHeader(__FUNCTION__, __FILE__, __LINE__)
#define LOG_SERVER_COMMON_CONFIG		CommonLog::g_logServerCommonConfig.setLogHeader(__FUNCTION__, __FILE__, __LINE__)
#define LOG_PROXYSERVER					CommonLog::g_logProxyServer.setLogHeader(__FUNCTION__, __FILE__, __LINE__)

#endif // !__LOG_DEF_H__
