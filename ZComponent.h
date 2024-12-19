/*
	�Զ���ؼ���
		PushButtonA	: QPushButton		�ɸ�����ɫԲ�ǿ��ذ�ť��		�¼���ͼ��������
		PushButtonB : QPushButton		���ε����ť������һ���Խ���Ľ��밴ť
		PushButtonC : QPushButton		Բ�ǿ��ذ�ť���������ؿ��ư�ť
		SideBarMenu : QWidget			�ɰ�stackedWidget��tabWidget�����л��Ĳ�����˵�
		StateLight	: QLabel			״ָ̬ʾ�ƣ��������ź�-��-�� ����״̬�����ɳ�����˸
		StateTextLight : QWidget		�����ֵ�״ָ̬ʾ��
		LabelTimer : QWidget			����label��ʱ��
		TabMenu : QTabWidget			�ɸ�����ʽ�ĺ���˵�
		SingleInputDialog : QDialog		������������ʾ����
		LCDTimer : QLCDNumber			LCD��ʱ��

	2024-12-18 �����
*/

#pragma once
#pragma execution_character_set("utf-8")

#include <QWidget>
#include <QStyle>
#include <QPushButton>
#include <qlineedit.h>
#include <QStackedWidget>
#include <QToolButton>
#include <QLabel>
#include <QTabWidget>
#include <QTabBar>
#include <QPainter>
#include <QLayout>
#include <QVariant>
#include <QEvent>
#include <QDebug>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QTimer>
#include <QDockWidget>
#include <QPropertyAnimation>
#include <QDatetime>
#include <QFont>
#include <QDialog>
#include <QLCDNumber>

namespace NS_ZCOMPONENT{
	/* �Զ��尴ťA�����Զ����ı�����ʾ��ɫ����Ϊ����ʹ�� */
	class PushButtonA : public QPushButton
	{
		Q_OBJECT

	public:
		/*	@function	��ȡ��ť״̬
			@return		true-����
		*/
		bool getStatus();
		/*	@function	���ð�ť������ɫ
			@param		��״̬������ɫ
			@param		��״̬������ɫ
		*/
		void setBackgroundColor(QString bcOn, QString bcOff);
		/*	@function	����������ɫ�ʹ�С
			@param		�����С
			@param		������ɫ
		*/
		void setFont(QString fontSize, QString fontColor = "white");
		/*	@function	���ð�ť״̬
			@param		true-���»��ߴ�
		*/
		void setStatus(bool status);
		/*	@function	����ʹ��״̬
			@param		true-ʹ��
		*/
		void setEnable(bool enable);
		/*	@function	���ð�ť�ı�
			@param		���»��ߴ�״̬�ı�
			@param		�ر�״̬�ı�
		*/
		void setButtonText(QString onText, QString offText);

		explicit PushButtonA(unsigned int width=200, unsigned int height=30, QWidget* parent = nullptr);
		~PushButtonA();

	protected:
		void paintEvent(QPaintEvent* event) override;

	private:
		void init(unsigned int width, unsigned int height);				//��ʼ��
		void update();				//����״̬
		QString getStyleOn();		//��״̬��ʽ
		QString getStyleOff();		//��״̬��ʽ

	signals:
		void sigButtonStatusChanged(bool status);		//��ť״̬�ı��ź�
		void sigButtonEnableChanged(bool enable);		//��ťʹ�ܸı��ź�

	private:
		const QString RADIUS = "20";							//��ť��۱�ԵԲ��
		QString m_fontSize = "20";								//�����С
		QString m_fontColor = "white";							//������ɫ
		const QColor COLOR_DISABLE = Qt::black;					//ʧ���ɲ���ɫ
		QString m_backColorOff = "#387F39";						//��ť�ر�����ɫ
		QString m_backColorOn = "#A04747";						//��ť��������ɫ
		QString m_onText = "��";								//��ť��״̬�ı�
		QString m_offText = "�ر�";								//��ť��״̬�ı�
		bool m_statusFlag = false;								//��ť״̬ ��-true
		bool m_enableFlag = true;								//ʹ��״̬ ʹ��-true
	};


	/* �Զ��尴ťB */
	class PushButtonB : public QPushButton
	{
		Q_OBJECT

	public:
		/*	@brief:	���ð�ť��С
			@param:	�����С
			@param:	����
			@param:	���
		*/
		void setBtnSize(unsigned int fontSize, unsigned int lenth = 200, unsigned int width = 40);
		/*	@brief:	���ð�ť��ɫ
			@param:	����ɫ
			@param:	�������ɫ
			@param:	����ɫ
		*/
		void setBtnColor(QString back, QString hover, QString font = "white");
		/*	@brief:	���ð�ťʹ��
			@param:	bool true-ʹ��
		*/
		void setBtnEnable(bool enable);

		explicit PushButtonB(QWidget* parent = nullptr);
		~PushButtonB();
	private:
		void init();			//Ĭ�ϳ�ʼ��
		void update();			//����UI
		QString getStyle();		//��ȡ��ʽ
	private:
		bool m_enableFlag = true;				//ʹ��״̬
		QString m_backGround = "#4E6C50";		//��ɫ
		QString m_backGroundEnable = "#4E6C50";	//ʹ��ʱ��ɫ
		QString m_hover = "#395144";			//����ʱ��ɫ
		QString m_fontColor = "#F0EBCE";		//������ɫ
		QString COLOR_DISABLE = "gray";			//ʧ��ʱ��ɫ
		unsigned int m_width = 40;				//���
		unsigned int m_fontSize = 15;			//�����С
	};


	/* �Զ��尴ťC 
		On״̬Ϊ����״̬ Off״̬��Ϊ����״̬
	*/
	class PushButtonC : public QPushButton
	{
		Q_OBJECT
	public:
		/*	@brief	��ȡ��ť״̬
			@ret	true-����
		*/
		bool getStatus();
		/*	@brief	���ð�ť������ɫ
			@param	��״̬������ɫ
			@param	��״̬������ɫ
			@param	��״̬������ɫ
			@param	��״̬������ɫ
		*/
		void setBtnColor(QString bcOn, QString bcOff, QString hoverOn, QString hoverOff);
		/*	@brief	����������ɫ�ʹ�С
			@param	�����С
			@param	������ɫ
			@param	������ʽ
		*/
		void setFontStyle(unsigned int size, QString fontColor = "white", QString font = "΢���ź�");
		/*	@brief	���ð�ť״̬
			@param	true-���»��ߴ�
		*/
		void setStatus(bool status);
		/*	@brief	���ð�ťʹ��״̬
			@param	true-ʹ��
		*/
		void setBtnEnable(bool status);
		/*	@brief	���ð�ť�ı�
			@param	���»��ߴ�״̬�ı�
			@param	�ر�״̬�ı�
		*/
		void setBtnText(QString onText, QString offText);
		/*	@brief	���ð�ť��С
			@param	��
			@param	��
		*/
		void setBtnSize(int width, int height);
		explicit PushButtonC(QWidget* parent = nullptr);
	private:
		void init();
		void update();
	signals:
		void sigButtonStatusChanged(bool status);		//��ť״̬�ı��ź�
	private:
		QString m_fontSize = "20";						//�����С
		QString m_fontColor = "white";					//������ɫ
		QString m_fontFamily = "΢���ź�";				//������ʽ
		QString m_backColorOff = "#387F39";				//��ť�ر�����ɫ
		QString m_backColorOn = "#A04747";				//��ť��������ɫ
		QString m_backColorEnable = "gray";				//��ť��ʹ����ɫ
		QString m_hoverOn = "#AA5151";					//hover��ɫ1
		QString m_hoverOff = "#428943";					//hover��ɫ2
		QString m_onText = "��";						//��ť��״̬�ı�
		QString m_offText = "�ر�";						//��ť��״̬�ı�
		bool m_statusFlag = false;						//��ť״̬ ��-true
		bool m_enableFlag = true;						//��ťʹ��״̬ ʹ��-true	
		int m_width = 200;								//���
		int m_height = 30;								//�߶�

		QMutex m_updateMutex;
	};


	/*	������˵� 
		setContentWidget����ʾ�Ĵ��ڣ����createItemButton������ť
	*/
	class SideBarMenu : public QWidget
	{
		Q_OBJECT

	public:
		/*	@brief:	��ʼ��UI
		*/
		void init();
		/*	@brief:	������ť
			@param:	QString �˵�����ʾ��ѡ������
			@param:	QWidget* �󶨵�ѡ���ָ��
		*/
		bool createItemButton(QString name, QWidget* widgetPtr);
		/*	@brief:	����Ҫ������ʾ��stackedWidget��tabWidget
			@param:	QWidget* Ŀ�괰��ָ��
		*/
		void setContentWidget(QWidget* widgetPtr);
		/*	@brief:	������ɫ
			@param:	QString �˵�������ɫ
			@param:	QString ��ťѡ����ɫ
			@param:	QString ��ť������ɫ
		*/
		void setColor(QString backGround, QString buttonSelected, QString buttonHover);
		/*	@brief:	���ñ����
			@param:	unsigned int ���
		*/
		void setWidth(unsigned int width);
		/*	@brief:	����ͼ��
			@param:	unsigned int ��ť���
			@param:	QString ͼ����Դ·��
		*/
		void setButtonIcon(unsigned int btnNo, QString url);

		explicit SideBarMenu(QWidget* parent = nullptr);
		~SideBarMenu();
	private:
		void menuSelected();								//�˵�����ѡ���л�
	private:
		unsigned char m_btnCnt = 0;							//��ť����
		QWidget* m_contentWidget;							//���ݴ���ָ��
		QList<QToolButton*> m_buttonList;					//�˵���ť�б�
		
		QVBoxLayout* m_menuLayout = new QVBoxLayout(this);	//�˵���ֱ����
		QToolButton* m_lastButton = new QToolButton(this);	//�������ť

		QString m_backGround = "#526D82";					//����ɫ
		QString m_buttonSelected = "#27374D";				//��ťѡ�б�����ɫ
		QString m_buttonHover = "#9DB2BF";					//��ťָ�����ұ�����ɫ

		unsigned int m_width = 200;							//�˵��Ͱ�ť���
	};


	/* ״̬�� */
	class StateLight : public QLabel
	{
		Q_OBJECT
	public:
		/*	@brief:	������ɫ
			@param:	QString �ƿ�״̬��ɫ
			@param:	QString �ƹ�״̬��ɫ
			@param:	QString �����ź�״̬��ɫ
		*/
		void setColor(QString lightOn, QString lightOff, QString lightNull);
		/*	@brief:	���ô�С
			@param:	unsigned int ֱ����С
		*/
		void setSize(unsigned int diameter);
		/*	@brief:	����״̬
			@param:	0-���ź� 1-�� 2-��
		*/
		void setStatus(unsigned char status);
		/*	@brief:	��ȡ״̬
			@ret:	unsigned char 0-���ź� 1-�� 2-��
		*/
		unsigned char getStatus();
		/*	@brief:	��˸����
			@param: bool true-������˸
			@param: unsigned int ��˸ʱ����
		*/
		void setFlicker(bool flag, unsigned int gap = 500);

		explicit StateLight(QWidget* parent = nullptr);
		~StateLight();

	private:
		void doFlickerWork();	//��˸�̹߳�������
		void update();			//����״̬
		void init();			//��ʼ��

	private:
		unsigned char m_stateFlag = 0;				//��״̬ 0-���ź� 1-�� 2-��
		int m_size = 20;							//�Ƴߴ�
		QString m_lightOn = "#609966";				//����ɫ
		QString m_lightOff = "#E84545";				//����ɫ
		QString m_lightNull = "#BDCDD6";			//���ź���ɫ
			
		QTimer m_timer;								//��˸����ʱ��
		bool m_flickerFlag = false;					//��˸������־
		unsigned int m_flickerGap = 500;			//��˸ʱ����
	};


	/* ״̬��-������ */
	class StateTextLight : public QWidget
	{
		Q_OBJECT
	public:
		/*	@brief:	����״̬
			@param:	unsigned char ��״̬ 0-�� 1-�� 2-��
			@param:	QString �ı�����
		*/
		void setState(unsigned char status, QString info);
		/*	@brief:	��˸����
			@param:	bool ��˸״̬ true-������˸
			@param:	QString �ı�
		*/
		void setFlicker(bool status, QString info);
		/*	@brief:	������ʽ
			@param:	unsigned int ֱ����С
			@param:	unsigned int �ı��ֺ�
			@param:	QString �ı���ɫ
			@param: QString �ı�����
		*/
		void setStyles(unsigned int diameter, unsigned int size, QString textColor = "black", QString font = "΢���ź�");
		/*	@brief:	����״̬����ɫ
			@param:	QString �ƿ�״̬��ɫ
			@param:	QString �ƹ�״̬��ɫ
			@param:	QString �����ź�״̬��ɫ
		*/
		void setColor(QString lightOn, QString lightOff, QString lightNull);

		explicit StateTextLight(QWidget* parent = nullptr);
		~StateTextLight();
	private:
		void init();	//��ʼ��

		StateLight m_light;						//״̬��
		QLabel m_label;							//״̬�ı�
		bool m_flickerFlag = false;				//������־
	};


	/* ����Label��ʱ�� */
	class LabelTimer : public QWidget {
		Q_OBJECT

	public:
		/*	@brief:	������ʽ
			@param:	�ı��ֺ�
			@param:	�ı���ɫ
		*/
		void setTextStyle(int size, QString font = "΢���ź�", QString color = "white");
		/*	@brief:	���õ�ǰ����
			@param:	unsigned long long ʱ������
		*/
		void setTime(unsigned long long seconds);
		/*	@brief:	��ȡ��ǰ��������
			@return:unsigned long long ��ǰʱ������
		*/
		unsigned long long getTime();
		/*	@brief:	��ͣ�������ʱ
			@param:	bool true-����
			@param:	bool true-�����ʱ false-�����ʱ
		*/
		void setContinue(bool flag, bool dire = true);
		/*	@brief:	���ü�ʱ�յ�
			@param:	unsigned long long ��ʱ����ʱ������
		*/
		void setEndTime(unsigned long long seconds);

		explicit LabelTimer(QWidget* parent = nullptr);

	private slots:
		void updateTime();

	signals:
		void sigTimeOut(unsigned long long seconds);		//��ʱ���� seconds-��ǰ����

	private:
		QLabel m_timeLabel;					//��ʾʱ���ǩ
		QTimer m_timer;						//��ʱ��
		unsigned long long m_seconds = 0;	//��������
		unsigned long long m_endSeconds = 24 * 60 * 60;	//��ʱ����ʱ�䣬Ĭ��1��
		bool m_direction;					//��ʱ���� true-����
	};


	/* ����˵� */
	class TabMenu : public QTabWidget {
		Q_OBJECT

	public:
		/*	@brief	:������ʽ
			@param	:QString ������ɫ�������߿�ѡ��tabɫ  �����С ������ʽ
			@param	:int �����С
			@param	:QString ������ʽ
		*/
		void setTabStyle(QString color, int size = 12, QString font = "΢���ź�");
		/*	@brief	:����ͼ��
			@param	:int tab����ţ���Ҫ����ע�ⷶΧ����0��ʼ
			@param	:QString ͼ���ļ���·��
		*/
		void setIcon(int index, QString iconPath);
		/*	@brief	:���������������С����ʽ����Ҫ�������Tab����֮���ٵ���
			@param	:int �����������С
			@param	:QString ������ʽ
		*/
		void setContentFont(int size, QString font = "΢���ź�");

		explicit TabMenu(QWidget* parent = nullptr);

	private:
		void update();

	private:
		QString m_basicColor = "#4169E1";
		int m_fontSize = 12;
		QString m_fontFamily = "΢���ź�";
	};


	/* �����뵯�� */
	/* ����ģ��
		if (dialog.exec() == QDialog::Accepted)
			QString input = dialog.getInput();
		else;
	*/
	class singleInputDialog : public QDialog 
	{
		Q_OBJECT
	public:
		explicit singleInputDialog(QWidget* parent = nullptr);
		//�����ı� ���⡢��ʾ�������Ĭ���ı���ȷ����ť��ȡ����ť���ı��ֺš��ı�����
		void setText(QString title, QString info = "������", QString input = "", QString okBtn = "ȷ��", QString quitBtn = "ȡ��", int size = 15, QString font = "΢���ź�");
		//��ȡ��������
		QString getInput();
	private:
		void init();
		void slotConfirm();
		void slotCancel();

		QLabel m_info;
		QPushButton m_okBtn, m_quitBtn;
		QLineEdit m_input;
	};


	/* LCD��ʱ�� */
	class LCDTimer : public QLCDNumber
	{
		Q_OBJECT
	public:
		/*	@brief:	���ô�С
			@param:	unsigned char ��
			@param:	unsigned char ��
		*/
		void setSize(unsigned char width, unsigned char height);
		/*	@brief:	������ʽ
			@param:	unsigned char ��ʾ��ʽ 0 - 00:00:00��1 - 00:00��2 - 00:00:00:00��3 - 000
			@param:	unsigned char ���λλ�� 1~4
			@param:	QString ������ɫ
			@param: QString ��ɫ
		*/
		void setLCDStyle(unsigned char mode, unsigned char high = 2, QString num = "black", QString back = "white");
		/*	@brief:	���õ�ǰ����
			@param:	unsigned long long ʱ������
		*/
		void setTime(unsigned long long seconds);
		/*	@brief:	��ȡ��ǰ��������
			@return:unsigned long long ��ǰʱ������
		*/
		unsigned long long getTime();
		/*	@brief:	��ͣ�������ʱ
			@param:	bool true-����
			@param:	bool true-�����ʱ false-�����ʱ
		*/
		void setContinue(bool flag, bool dire = true);
		/*	@brief:	���ü�ʱ�յ�
			@param:	unsigned long long ��ʱ����ʱ������
		*/
		void setEndTime(unsigned long long seconds);

		explicit LCDTimer(QWidget* parent = nullptr);
	private slots:
		void slotUpdateTime();								//������ʾ
	signals:
		void sigTimeOut(unsigned long long seconds);		//��ʱ���� seconds-��ǰ����
	private:
		QTimer m_timer;
		unsigned char m_mode = 0;									//��ʾ��ʽ
		unsigned char m_high = 2;									//���λλ��
		unsigned long long m_sec = 0;								//����
		unsigned long long m_endSeconds = 24 * 60 * 60 * 365;		//�����ʱ����ʱ�䣬Ĭ��1��
		bool m_bDirection = true;									//��ʱ���� true-�����ʱ
	};
}