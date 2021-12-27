#ifndef __USER_H__
#define __USER_H__

#include <servercommon/boostmodule/basedef.h>
#include <servercommon/boostmodule/signalcommunication.h>
#include <servercommon/basedef.h>
#include <logmodule/logdef.h>


namespace UserBuffer
{
	const int g_nReadBufferSize = 1024 * 50;	// ÿ�ζ�ȡ���50K	
}

class GateServer;
class User : public boost::enable_shared_from_this<User>
{
public:
	enum EnSignalConnectStatus
	{
		CONNECT_ERROR,
		CONNECT_OK,
	};

public:
	User(CommonBoost::IOServer& ioserver);
	~User();

	void ayncRead();
	void ayncSend(const char* str, uint size);
	CommonBoost::SocketPtr& getSocket();
	void getLinkIP(std::string& outIp);
	void getLinkPort(ushort& outPort);
	void closeSocket();

	int slotConnect(GateServer* gateServer);

SIGNALS:
	DEFINE_SIGNAL(void(
		boost::shared_ptr<User>,
		const CommonBoost::ErrorCode&), sigError);

HANDLER:
	void onAyncRead(
		const CommonBoost::ErrorCode& ec,
		uint readSize
	);
	void onAyncSend(
		const CommonBoost::ErrorCode& ec,
		uint readSize
	);

private:
	CommonBoost::SocketPtr m_pSocket;
	char m_readBuffer[UserBuffer::g_nReadBufferSize];
};

#endif // !__USER_H__
