#ifndef __USER_H__
#define __USER_H__

#include <servercommon/boostmodule/basedef.h>
#include <servercommon/boostmodule/signalcommunication.h>
#include <servercommon/basedef.h>

namespace UserBuffer
{
	const int g_nReadBufferSize = 1024 * 50;	// ÿ�ζ�ȡ���50K	
}

class GateServer;
class User : public boost::enable_shared_from_this<User> ,public SignalSender
{
public:
	User(CommonBoost::IOServer& ioserver);
	~User();

	void ayncRead();
	void ayncSend(const char* str, uint size);
	CommonBoost::SocketPtr& getSocket();
	const std::string getLinkIP();
	ushort getLinkPort();

SIGNALS:
	virtual int slotConnect(void* receiver, const std::string& className);

	DEFINE_SIGNAL(void(const std::string&, ushort), sigError);

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
