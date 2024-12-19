#include "ZSimpleLibrary.h"

namespace NS_ZSLib {
	//�����߳��й���
	SimpleThreadMangar::SimpleThreadMangar(QObject* obj, QObject* parent)
		: QObject(parent)
	{
		m_thread = new QThread;
		if (obj) {
			obj->moveToThread(m_thread);
			connect(m_thread, &QThread::finished, obj, &QObject::deleteLater);
			m_thread->start();
		}
	}
	SimpleThreadMangar::~SimpleThreadMangar()
	{
		m_thread->quit();
		m_thread->wait();
		delete m_thread;
	}


	//����̨����ִ����
	cmdProcess::cmdProcess(QObject* parent) 
		: QObject(parent)
	{
		m_thread = new QThread;
		this->moveToThread(m_thread);
		m_thread->start();
	}

	cmdProcess::~cmdProcess()
	{
		m_thread->quit();
		m_thread->wait();
		delete m_thread;
	}

	QString cmdProcess::blockExcute(QString cmd)
	{
		QMutexLocker locker(&m_excuteMutex);
		QProcess process;
		process.start(cmd);
		if (!process.waitForFinished())		//�޷�ִ��
			emit sigExcuteResult("excute error");
		QByteArray output = process.readAll();
		if (output.isEmpty()) {
			output = process.readAllStandardOutput();
			if (output.isEmpty()) {
				output = process.readAllStandardError();
			}
		}
		QString result = QString::fromLocal8Bit(output.data());
		return result;
	}

	void cmdProcess::slotExcuteCmd(QString cmd) {
		QMutexLocker locker(&m_excuteMutex);
		QProcess process;
		process.start(cmd);
		if (!process.waitForFinished())		//�޷�ִ��
			emit sigExcuteResult("excute error");
		QByteArray output = process.readAll();
		if (output.isEmpty()) {
			output = process.readAllStandardOutput();
			if (output.isEmpty()) {
				output = process.readAllStandardError();
			}
		}
		QString result = QString::fromLocal8Bit(output.data());
		emit sigExcuteResult(result);
	}


	void TcpClientThread::slotSend(QByteArray data)
	{
		QMutexLocker locker(&m_mutex);
		if (m_client->state() == QAbstractSocket::ConnectedState) {
			m_client->write(data);
			m_client->flush();
		}
	}

	void TcpClientThread::slotDisconnect()
	{
		QMutexLocker locker(&m_mutex);
		if (m_client->state() == QAbstractSocket::ConnectedState) {
			m_client->disconnectFromHost();
			m_connectFlag = false;
		}
	}

	bool TcpClientThread::getConnectState()
	{
		QMutexLocker locker(&m_mutex);
		return m_connectFlag;
	}

	//TCP��ͨ����
	TcpClientThread::TcpClientThread(QObject* parent)
		: QObject(parent) {
		m_thread = new QThread;
		m_client = new QTcpSocket;
		this->moveToThread(m_thread);		//��ŵ��߳�ִ�У��ٵ���client�Ľӿڣ��������߳��е���
		m_thread->start();

		connect(m_client, &QTcpSocket::disconnected, this, [=]() {
			emit sigDisconnect();
			m_connectFlag = false;
			});
	}

	TcpClientThread::~TcpClientThread()
	{
		m_client->disconnectFromHost();
		m_thread->quit();
		m_thread->wait();
		delete m_thread;
		delete m_client;
	}
	void TcpClientThread::slotConnectToHost(QString IP, int port) {
		QMutexLocker locker(&m_mutex);
		m_client->connectToHost(IP, port);
		m_client->waitForConnected(3000);
		if (m_client->state() == QAbstractSocket::ConnectedState) {		//�ɹ�����
			m_connectFlag = true;
		}
		else {
			m_connectFlag = false;
		}
		emit sigConnectState(m_connectFlag);		//����״̬
	}

	UDPThread::UDPThread(int port, QObject* parent) 
	{
		m_socket.bind(QHostAddress::Any, port);	//�󶨶˿�
		connect(&m_socket, &QUdpSocket::readyRead, this, &UDPThread::slotReadData);
	}
	UDPThread::~UDPThread()
	{
		m_socket.abort();
	}
	void UDPThread::send(const QString& serverIp, quint16 serverPort, const QByteArray& data)
	{
		QMutexLocker locker(&m_mutex);
		QHostAddress serverAddress(serverIp);
		m_socket.writeDatagram(data, serverAddress, serverPort);
	}
	void UDPThread::slotReadData()
	{
		while (m_socket.hasPendingDatagrams()) {
			QByteArray datagram;
			datagram.resize(m_socket.hasPendingDatagrams());
			QHostAddress senderAddress;
			quint16 senderPort;
			m_socket.readDatagram(datagram.data(), datagram.size(), &senderAddress, &senderPort);
			emit sigDataReady(datagram);
		}
	}
}