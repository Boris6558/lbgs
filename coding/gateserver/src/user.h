#ifndef __USER_H__
#define __USER_H__

#include <servercommon/boostcommondef/basedef.h>

namespace UserBuffer
{
	/*
		4M ���� ���ڿ����������ڴ�ֻ�м���G�����Բ���socketֻ��2000�࣬ ���buffer size�ʵ����ͣ��ɴﵽ�򼶲�����д��ѹ�����Ѳ��Թ���
	*/
	const int g_nReadBufferSize = 1024 * 1024 * 4;		
}

class User : public boost::enable_shared_from_this<User>
{
public:
	User(CommonBoost::IOServer& ioserver);
	~User();

	void ayncRead();
	void ayncSend(const char* str, unsigned int size);
	CommonBoost::SocketPtr& getSocket();

HANDLER:
	void onAyncRead(
		const CommonBoost::ErrorCode& ec,
		unsigned int readSize
	);
	void onAyncSend(
		const CommonBoost::ErrorCode& ec,
		unsigned int readSize
	);

private:
	CommonBoost::SocketPtr m_pSocket;
	char m_readBuffer[UserBuffer::g_nReadBufferSize];
};

#endif // !__USER_H__
