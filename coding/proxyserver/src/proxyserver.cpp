#include "proxyserver.h"

#include <configmodule/proxyserverconfig/proxyserverconfig.h>
#include <servercommon/logmodule/logdef.h>
#include <servercommon/configmodule/configmanager.h>


ProxyServer::ProxyServer()
{
	initData();
	const ProxyServerConfigInfo* pCfgInfo = CONFIG_MGR->GetProxyServerConfig()->getConfigInfo();
	if(CONFIG_MGR->GetProxyServerConfig() && pCfgInfo)
	{
		m_nPort = pCfgInfo->port;
		m_pAcceptor = new CommonBoost::Acceptor(
			m_server,
			CommonBoost::Endpoint(CommonBoost::TCP::v4(), m_nPort));
		accept();
		LOG_PROXYSERVER.printLog("has run gateserver succ");
	}
}

ProxyServer::ProxyServer(int port)
{
	initData();
	m_nPort = port;
	m_pAcceptor = new CommonBoost::Acceptor(
		m_server,
		CommonBoost::Endpoint(CommonBoost::TCP::v4(), m_nPort));
	accept();
	LOG_PROXYSERVER.printLog("has run gateserver succ");
}

ProxyServer::~ProxyServer()
{
}

void ProxyServer::start()
{
	LOG_PROXYSERVER.printLog("ProxyServer has start,run sub thread count[%d]", CPU_MAX_THREAD);
	LOG_GATESERVER.printLog("ProxyServer has start,port[%d]", m_nPort);
	for(int i = 0; i < CPU_MAX_THREAD; ++i)
	{
		boost::thread tAccServer(BIND(&ProxyServer::onThreadRunAcceptorIOServer, this));
		tAccServer.detach();
	}
	while(1);
}

void ProxyServer::initData()
{
	m_pAcceptor = NULL;
	m_nPort = 0;
}

void ProxyServer::accept()
{
	if(!m_pAcceptor)
	{
		LOG_PROXYSERVER.printLog("m_pAcceptor is NULL");		// ���ﶼ���ܵ�����дʲô���룬����ȥ��ש
		return;
	}

	boost::shared_ptr<ServerLinker> linker = boost::make_shared<ServerLinker>(m_server);
	if(linker->getSocket().get() == NULL)
	{
		LOG_PROXYSERVER.printLog("linker->getSocket().get() == NULL");			// ���ܵ������ˣ��������ǲ���������
		return;
	}
	m_pAcceptor->async_accept(*(linker->getSocket()), BIND(&ProxyServer::onAcceptHandler, this, boost::placeholders::_1, linker));
}

void ProxyServer::onThreadRunAcceptorIOServer()
{
	LOG_PROXYSERVER.printLog("server has run");
	CommonBoost::WorkPtr work(new CommonBoost::IOServer::work(m_server));

	/*
	�����쳣�����ܻ����һ��������������ԭ�����ڿͻ��˽��������Ժ�һ˲�䣬����˵���remote_endpointǰ���ͶϿ������ӣ����·���ʧ��
	������Ϣ���£�
		terminate called after throwing an instance of 'boost::wrapexcept<boost::system::system_error>'
		what():  remote_endpoint: Transport endpoint is not connected
		Aborted
	*/
	while(1)
	{
		try
		{
			m_server.run();
		}
		catch(std::exception& e)
		{
			LOG_PROXYSERVER.printLog("m_server run exception!! info[%s] server will re-start!!", e.what());
		}
	}
}

void ProxyServer::onAcceptHandler(
	const CommonBoost::ErrorCode& err,
	const boost::shared_ptr<ServerLinker>& linker
)
{

	if(err)
	{
		LOG_PROXYSERVER.printLog("connect error value[%d],message[%s]", err.value(), err.message().data());
		accept();
		return;
	}
	if(!linker)
	{
		LOG_PROXYSERVER.printLog("linking linker is NULL");
		accept();
		return;
	}

	linker->ayncRead();
}