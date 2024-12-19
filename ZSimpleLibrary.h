/*
	自定义功能库
		SimpleThreadMangar	简易单个线程管理类
		cmdProcess			简易控制台命令执行类，线程安全

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
	/* 单个线程托管 */
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


	/*	控制台命令
		外部信号绑定到slotExcuteCmd传入命令。由sigExcuteResult信号传出结果
	*/
	class cmdProcess : public QObject {
		Q_OBJECT

	public:
		explicit cmdProcess(QObject* parent = nullptr);
		~cmdProcess();

		QString blockExcute(QString cmd);		//直接执行方式（阻塞所在线程）
	signals:
		void sigExcuteResult(QString result);	//执行结果返回信号

	public slots:
		void slotExcuteCmd(QString cmd);		//cmd执行槽

	private:
		QThread* m_thread;
		QMutex m_excuteMutex;
	};


	/* 线程辅助工作类 */

	/* 最简Tcp连接通信类 */
	class TcpClientThread : public QObject 
	{
		Q_OBJECT
	public:
		void slotConnectToHost(QString IP, int port);	//主动连接到服务器
		void slotSend(QByteArray data);					//发送数据
		void slotDisconnect();							//主动断开连接
		bool getConnectState();				//获取连接状态

		explicit TcpClientThread(QObject* parent = nullptr);
		~TcpClientThread();

	signals:
		void sigConnectState(bool status);			//发送连接状态
		void sigRecv();								//接收数据
		void sigDisconnect();						//受服务端断开连接

	private:
		QMutex m_mutex;				
		QTcpSocket* m_client;				//本客户端
		QThread* m_thread;					//执行线程
		bool m_connectFlag = false;			//连接标志
	};

	/* 最简UDP通信类 */
	class UDPThread : public QObject
	{
		Q_OBJECT
	public:
		UDPThread(int port = 8180, QObject* parent = nullptr);
		~UDPThread();
		void send(const QString& aimIp, quint16 aimPort, const QByteArray& data);	//发送数据
	private:
		void slotReadData();

	signals:
		void sigDataReady(QByteArray data);		//接收到数据信号

	private:
		QMutex m_mutex;
		QUdpSocket m_socket;
	};
}
