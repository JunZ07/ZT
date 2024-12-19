/*
	�Զ��幦�ܿ�
		SimpleThreadMangar	���׵����̹߳�����
		cmdProcess			���׿���̨����ִ���࣬�̰߳�ȫ

	2024-10-22 junker
*/

#pragma once
#pragma execution_character_set("utf-8")

#include <QObject>
#include <qstring.h>
#include <qthread.h>
#include <qmutex.h>
#include <qtimer.h>
#include <qprocess.h>
#include <qbytearray.h>
#include <qdebug.h>
#include <QtNetwork/qtcpserver.h>
#include <QtNetwork/qtcpsocket.h>
#include <QtNetwork/qudpsocket.h>

namespace NS_ZSLib {
	/* �����߳��й� */
	class SimpleThreadMangar : public QObject
	{
		Q_OBJECT

	public:
		explicit SimpleThreadMangar(QObject* obj, QObject* parent = nullptr);
		~SimpleThreadMangar();
	signals:

	private:
		QThread* m_thread;
	};


	/*	����̨����
		�ⲿ�źŰ󶨵�slotExcuteCmd���������sigExcuteResult�źŴ������
	*/
	class cmdProcess : public QObject {
		Q_OBJECT

	public:
		explicit cmdProcess(QObject* parent = nullptr);
		~cmdProcess();

		QString blockExcute(QString cmd);		//ֱ��ִ�з�ʽ�����������̣߳�
	signals:
		void sigExcuteResult(QString result);	//ִ�н�������ź�

	public slots:
		void slotExcuteCmd(QString cmd);		//cmdִ�в�

	private:
		QThread* m_thread;
		QMutex m_excuteMutex;
	};


	/* �̸߳��������� */

	/* ���Tcp����ͨ���� */
	class TcpClientThread : public QObject 
	{
		Q_OBJECT
	public:
		void slotConnectToHost(QString IP, int port);	//�������ӵ�������
		void slotSend(QByteArray data);					//��������
		void slotDisconnect();							//�����Ͽ�����
		bool getConnectState();				//��ȡ����״̬

		explicit TcpClientThread(QObject* parent = nullptr);
		~TcpClientThread();

	signals:
		void sigConnectState(bool status);			//��������״̬
		void sigRecv();								//��������
		void sigDisconnect();						//�ܷ���˶Ͽ�����

	private:
		QMutex m_mutex;				
		QTcpSocket* m_client;				//���ͻ���
		QThread* m_thread;					//ִ���߳�
		bool m_connectFlag = false;			//���ӱ�־
	};

	/* ���UDPͨ���� */
	class UDPThread : public QObject
	{
		Q_OBJECT
	public:
		UDPThread(int port = 8180, QObject* parent = nullptr);
		~UDPThread();
		void send(const QString& aimIp, quint16 aimPort, const QByteArray& data);	//��������
	private:
		void slotReadData();

	signals:
		void sigDataReady(QByteArray data);		//���յ������ź�

	private:
		QMutex m_mutex;
		QUdpSocket m_socket;
	};
}
