#ifndef __GATESERVER_H__
#define __GATESERVER_H__

#include "user.h"

#include <boostmodule/basedef.h>
#include <boost/atomic.hpp>

struct GateServerConfigInfo;
class GateServer
{
public:
	enum EnUserStatus
	{
		LOGOUT = 2,
	};

public:
	GateServer();
	GateServer(int port);
	~GateServer();

	void start();

SLOTS:
	void onUserError(
		boost::shared_ptr<User> user,
		const CommonBoost::ErrorCode& ec);

HANDLER:
	void onAcceptHandler(
		const CommonBoost::ErrorCode& err,
		const boost::shared_ptr<User>& user
		);
	void onThreadRunAcceptorIOServer();

	// inner client 
	void onConnectInnerServer(const CommonBoost::ErrorCode& err);

private:
	void accept();
	void initData();
	void initInnerClient();
	void connectInnerServer();
	void runInnnerIOServerOnce();
	void sendServerInfo(const boost::shared_ptr<User>& user);	// ÿ���ͻ������Ӻ���һ����Ϣ�����߿ͻ��˷������Ϣ��Ŀǰ�����ֽ���洢��ʽ���ɿͻ�����װ����
	bool isConnectProxySrvSucc() { return m_bConnectProxySrv; }

private:
	CommonBoost::IOServer m_server;
	CommonBoost::Acceptor* m_pAcceptor;
	boost::atomic<int> m_nConnectCount;
	int m_nPort;

	// �ڲ��ͻ��˲��֣����������ڲ�������
	bool m_bInnerRunOnce;
	bool m_bConnectProxySrv;
	CommonBoost::IOServer m_innerServer;
	CommonBoost::SocketPtr m_pInnerSocket;
	CommonBoost::Endpoint m_innerEndpoint;
};

#endif
