#ifndef __USER_H__
#define __USER_H__

#include <QtCore/QObject>
#include <QtNetwork/QTcpSocket>

class QPlainTextEdit;

class User : public QObject
{
	Q_OBJECT

public:
	User(
		const QString& ip,
		uint port,
		QObject* parent = NULL
		);
	~User();
	const QByteArray& getReadData() { return m_bytesMsg; }
	void setUserId(uint id) { m_nUserId = id; }
	uint getUserId() { return m_nUserId; }

	void sendData(const char* data, uint dataSize);		// ����dataǰ�Ȱ��ֽ�������ת����Ŵ�
	void sendData(const QByteArray& msg);
	void setBigEndian(bool b) { m_bServerBigEndian = b; }
	bool isServerBigEndian() { return m_bServerBigEndian; }

signals:
	void sigConnect(uint userId);
	void sigError(uint userId, int eCode);
	void sigReadData(uint userId, const QByteArray& data);

private slots:
	void onConnected();
	void onError(QAbstractSocket::SocketError eCode);
	void onReadData();

private:
	void sendHeartInfo();

private:
	QTcpSocket* m_pTcpSoc;
	QByteArray m_bytesMsg;
	uint m_nUserId;
	bool m_bServerBigEndian;		// �������ֽ��� false-С�� true-���
};

#endif // !__USER_H__
