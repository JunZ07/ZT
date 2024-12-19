/*
	自定义控件：
		PushButtonA	: QPushButton		可更改颜色圆角开关按钮，		事件绘图存在问题
		PushButtonB : QPushButton		单次点击按钮，用作一次性界面的进入按钮
		PushButtonC : QPushButton		圆角开关按钮，用作开关控制按钮
		SideBarMenu : QWidget			可绑定stackedWidget和tabWidget窗口切换的侧边栏菜单
		StateLight	: QLabel			状态指示灯，包括无信号-开-关 三种状态，还可持续闪烁
		StateTextLight : QWidget		带文字的状态指示灯
		LabelTimer : QWidget			简易label计时器
		TabMenu : QTabWidget			可更改样式的横向菜单
		SingleInputDialog : QDialog		单个输入框的提示弹窗
		LCDTimer : QLCDNumber			LCD计时器

	2024-12-18 朱均正
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
	/* 自定义按钮A，可自定义文本和显示颜色，作为开关使用 */
	class PushButtonA : public QPushButton
	{
		Q_OBJECT

	public:
		/*	@function	获取按钮状态
			@return		true-按下
		*/
		bool getStatus();
		/*	@function	设置按钮背景颜色
			@param		开状态背景颜色
			@param		关状态背景颜色
		*/
		void setBackgroundColor(QString bcOn, QString bcOff);
		/*	@function	设置字体颜色和大小
			@param		字体大小
			@param		字体颜色
		*/
		void setFont(QString fontSize, QString fontColor = "white");
		/*	@function	设置按钮状态
			@param		true-按下或者打开
		*/
		void setStatus(bool status);
		/*	@function	设置使能状态
			@param		true-使能
		*/
		void setEnable(bool enable);
		/*	@function	设置按钮文本
			@param		按下或者打开状态文本
			@param		关闭状态文本
		*/
		void setButtonText(QString onText, QString offText);

		explicit PushButtonA(unsigned int width=200, unsigned int height=30, QWidget* parent = nullptr);
		~PushButtonA();

	protected:
		void paintEvent(QPaintEvent* event) override;

	private:
		void init(unsigned int width, unsigned int height);				//初始化
		void update();				//更新状态
		QString getStyleOn();		//开状态样式
		QString getStyleOff();		//关状态样式

	signals:
		void sigButtonStatusChanged(bool status);		//按钮状态改变信号
		void sigButtonEnableChanged(bool enable);		//按钮使能改变信号

	private:
		const QString RADIUS = "20";							//按钮外观边缘圆角
		QString m_fontSize = "20";								//字体大小
		QString m_fontColor = "white";							//字体颜色
		const QColor COLOR_DISABLE = Qt::black;					//失能蒙层颜色
		QString m_backColorOff = "#387F39";						//按钮关背景颜色
		QString m_backColorOn = "#A04747";						//按钮开背景颜色
		QString m_onText = "打开";								//按钮开状态文本
		QString m_offText = "关闭";								//按钮关状态文本
		bool m_statusFlag = false;								//按钮状态 开-true
		bool m_enableFlag = true;								//使能状态 使能-true
	};


	/* 自定义按钮B */
	class PushButtonB : public QPushButton
	{
		Q_OBJECT

	public:
		/*	@brief:	设置按钮大小
			@param:	字体大小
			@param:	长度
			@param:	宽度
		*/
		void setBtnSize(unsigned int fontSize, unsigned int lenth = 200, unsigned int width = 40);
		/*	@brief:	设置按钮颜色
			@param:	背景色
			@param:	鼠标悬挂色
			@param:	字体色
		*/
		void setBtnColor(QString back, QString hover, QString font = "white");
		/*	@brief:	设置按钮使能
			@param:	bool true-使能
		*/
		void setBtnEnable(bool enable);

		explicit PushButtonB(QWidget* parent = nullptr);
		~PushButtonB();
	private:
		void init();			//默认初始化
		void update();			//更新UI
		QString getStyle();		//获取样式
	private:
		bool m_enableFlag = true;				//使能状态
		QString m_backGround = "#4E6C50";		//底色
		QString m_backGroundEnable = "#4E6C50";	//使能时底色
		QString m_hover = "#395144";			//悬挂时颜色
		QString m_fontColor = "#F0EBCE";		//字体颜色
		QString COLOR_DISABLE = "gray";			//失能时颜色
		unsigned int m_width = 40;				//宽度
		unsigned int m_fontSize = 15;			//字体大小
	};


	/* 自定义按钮C 
		On状态为按下状态 Off状态视为弹起状态
	*/
	class PushButtonC : public QPushButton
	{
		Q_OBJECT
	public:
		/*	@brief	获取按钮状态
			@ret	true-按下
		*/
		bool getStatus();
		/*	@brief	设置按钮背景颜色
			@param	开状态背景颜色
			@param	关状态背景颜色
			@param	开状态悬浮颜色
			@param	关状态悬浮颜色
		*/
		void setBtnColor(QString bcOn, QString bcOff, QString hoverOn, QString hoverOff);
		/*	@brief	设置字体颜色和大小
			@param	字体大小
			@param	字体颜色
			@param	字体样式
		*/
		void setFontStyle(unsigned int size, QString fontColor = "white", QString font = "微软雅黑");
		/*	@brief	设置按钮状态
			@param	true-按下或者打开
		*/
		void setStatus(bool status);
		/*	@brief	设置按钮使能状态
			@param	true-使能
		*/
		void setBtnEnable(bool status);
		/*	@brief	设置按钮文本
			@param	按下或者打开状态文本
			@param	关闭状态文本
		*/
		void setBtnText(QString onText, QString offText);
		/*	@brief	设置按钮大小
			@param	宽
			@param	高
		*/
		void setBtnSize(int width, int height);
		explicit PushButtonC(QWidget* parent = nullptr);
	private:
		void init();
		void update();
	signals:
		void sigButtonStatusChanged(bool status);		//按钮状态改变信号
	private:
		QString m_fontSize = "20";						//字体大小
		QString m_fontColor = "white";					//字体颜色
		QString m_fontFamily = "微软雅黑";				//字体样式
		QString m_backColorOff = "#387F39";				//按钮关背景颜色
		QString m_backColorOn = "#A04747";				//按钮开背景颜色
		QString m_backColorEnable = "gray";				//按钮不使能颜色
		QString m_hoverOn = "#AA5151";					//hover颜色1
		QString m_hoverOff = "#428943";					//hover颜色2
		QString m_onText = "打开";						//按钮开状态文本
		QString m_offText = "关闭";						//按钮关状态文本
		bool m_statusFlag = false;						//按钮状态 开-true
		bool m_enableFlag = true;						//按钮使能状态 使能-true	
		int m_width = 200;								//宽度
		int m_height = 30;								//高度

		QMutex m_updateMutex;
	};


	/*	侧边栏菜单 
		setContentWidget绑定显示的窗口，随后createItemButton创建按钮
	*/
	class SideBarMenu : public QWidget
	{
		Q_OBJECT

	public:
		/*	@brief:	初始化UI
		*/
		void init();
		/*	@brief:	新增按钮
			@param:	QString 菜单上显示的选项名字
			@param:	QWidget* 绑定的选项窗口指针
		*/
		bool createItemButton(QString name, QWidget* widgetPtr);
		/*	@brief:	设置要进行显示的stackedWidget或tabWidget
			@param:	QWidget* 目标窗口指针
		*/
		void setContentWidget(QWidget* widgetPtr);
		/*	@brief:	设置颜色
			@param:	QString 菜单背景颜色
			@param:	QString 按钮选中颜色
			@param:	QString 按钮滑过颜色
		*/
		void setColor(QString backGround, QString buttonSelected, QString buttonHover);
		/*	@brief:	设置表单宽度
			@param:	unsigned int 宽度
		*/
		void setWidth(unsigned int width);
		/*	@brief:	设置图标
			@param:	unsigned int 按钮序号
			@param:	QString 图标资源路径
		*/
		void setButtonIcon(unsigned int btnNo, QString url);

		explicit SideBarMenu(QWidget* parent = nullptr);
		~SideBarMenu();
	private:
		void menuSelected();								//菜单发生选择切换
	private:
		unsigned char m_btnCnt = 0;							//按钮数量
		QWidget* m_contentWidget;							//内容窗口指针
		QList<QToolButton*> m_buttonList;					//菜单按钮列表
		
		QVBoxLayout* m_menuLayout = new QVBoxLayout(this);	//菜单垂直布局
		QToolButton* m_lastButton = new QToolButton(this);	//最后点击按钮

		QString m_backGround = "#526D82";					//背景色
		QString m_buttonSelected = "#27374D";				//按钮选中背景颜色
		QString m_buttonHover = "#9DB2BF";					//按钮指针悬挂背景颜色

		unsigned int m_width = 200;							//菜单和按钮宽度
	};


	/* 状态灯 */
	class StateLight : public QLabel
	{
		Q_OBJECT
	public:
		/*	@brief:	设置颜色
			@param:	QString 灯开状态颜色
			@param:	QString 灯关状态颜色
			@param:	QString 灯无信号状态颜色
		*/
		void setColor(QString lightOn, QString lightOff, QString lightNull);
		/*	@brief:	设置大小
			@param:	unsigned int 直径大小
		*/
		void setSize(unsigned int diameter);
		/*	@brief:	设置状态
			@param:	0-无信号 1-开 2-灭
		*/
		void setStatus(unsigned char status);
		/*	@brief:	获取状态
			@ret:	unsigned char 0-无信号 1-开 2-灭
		*/
		unsigned char getStatus();
		/*	@brief:	闪烁设置
			@param: bool true-继续闪烁
			@param: unsigned int 闪烁时间间隔
		*/
		void setFlicker(bool flag, unsigned int gap = 500);

		explicit StateLight(QWidget* parent = nullptr);
		~StateLight();

	private:
		void doFlickerWork();	//闪烁线程工作函数
		void update();			//更新状态
		void init();			//初始化

	private:
		unsigned char m_stateFlag = 0;				//灯状态 0-无信号 1-开 2-灭
		int m_size = 20;							//灯尺寸
		QString m_lightOn = "#609966";				//开颜色
		QString m_lightOff = "#E84545";				//关颜色
		QString m_lightNull = "#BDCDD6";			//无信号颜色
			
		QTimer m_timer;								//闪烁任务定时器
		bool m_flickerFlag = false;					//闪烁继续标志
		unsigned int m_flickerGap = 500;			//闪烁时间间隔
	};


	/* 状态灯-带文字 */
	class StateTextLight : public QWidget
	{
		Q_OBJECT
	public:
		/*	@brief:	设置状态
			@param:	unsigned char 灯状态 0-空 1-开 2-关
			@param:	QString 文本内容
		*/
		void setState(unsigned char status, QString info);
		/*	@brief:	闪烁控制
			@param:	bool 闪烁状态 true-继续闪烁
			@param:	QString 文本
		*/
		void setFlicker(bool status, QString info);
		/*	@brief:	设置样式
			@param:	unsigned int 直径大小
			@param:	unsigned int 文本字号
			@param:	QString 文本颜色
			@param: QString 文本字体
		*/
		void setStyles(unsigned int diameter, unsigned int size, QString textColor = "black", QString font = "微软雅黑");
		/*	@brief:	设置状态灯颜色
			@param:	QString 灯开状态颜色
			@param:	QString 灯关状态颜色
			@param:	QString 灯无信号状态颜色
		*/
		void setColor(QString lightOn, QString lightOff, QString lightNull);

		explicit StateTextLight(QWidget* parent = nullptr);
		~StateTextLight();
	private:
		void init();	//初始化

		StateLight m_light;						//状态灯
		QLabel m_label;							//状态文本
		bool m_flickerFlag = false;				//灯闪标志
	};


	/* 简易Label计时器 */
	class LabelTimer : public QWidget {
		Q_OBJECT

	public:
		/*	@brief:	设置样式
			@param:	文本字号
			@param:	文本颜色
		*/
		void setTextStyle(int size, QString font = "微软雅黑", QString color = "white");
		/*	@brief:	设置当前秒数
			@param:	unsigned long long 时间秒数
		*/
		void setTime(unsigned long long seconds);
		/*	@brief:	获取当前经过秒数
			@return:unsigned long long 当前时间秒数
		*/
		unsigned long long getTime();
		/*	@brief:	暂停或继续计时
			@param:	bool true-继续
			@param:	bool true-正向计时 false-反向计时
		*/
		void setContinue(bool flag, bool dire = true);
		/*	@brief:	设置计时终点
			@param:	unsigned long long 计时结束时间秒数
		*/
		void setEndTime(unsigned long long seconds);

		explicit LabelTimer(QWidget* parent = nullptr);

	private slots:
		void updateTime();

	signals:
		void sigTimeOut(unsigned long long seconds);		//计时结束 seconds-当前秒数

	private:
		QLabel m_timeLabel;					//显示时间标签
		QTimer m_timer;						//计时器
		unsigned long long m_seconds = 0;	//经过秒数
		unsigned long long m_endSeconds = 24 * 60 * 60;	//计时结束时间，默认1天
		bool m_direction;					//计时方向 true-正向
	};


	/* 横向菜单 */
	class TabMenu : public QTabWidget {
		Q_OBJECT

	public:
		/*	@brief	:设置样式
			@param	:QString 基础颜色，包括边框，选中tab色  字体大小 字体样式
			@param	:int 字体大小
			@param	:QString 字体样式
		*/
		void setTabStyle(QString color, int size = 12, QString font = "微软雅黑");
		/*	@brief	:设置图标
			@param	:int tab的序号，需要自行注意范围，从0开始
			@param	:QString 图标文件的路径
		*/
		void setIcon(int index, QString iconPath);
		/*	@brief	:设置内容区字体大小和样式。需要在添加完Tab窗口之后再调用
			@param	:int 内容区字体大小
			@param	:QString 字体样式
		*/
		void setContentFont(int size, QString font = "微软雅黑");

		explicit TabMenu(QWidget* parent = nullptr);

	private:
		void update();

	private:
		QString m_basicColor = "#4169E1";
		int m_fontSize = 12;
		QString m_fontFamily = "微软雅黑";
	};


	/* 单输入弹窗 */
	/* 调用模板
		if (dialog.exec() == QDialog::Accepted)
			QString input = dialog.getInput();
		else;
	*/
	class singleInputDialog : public QDialog 
	{
		Q_OBJECT
	public:
		explicit singleInputDialog(QWidget* parent = nullptr);
		//设置文本 标题、提示、输入框默认文本、确定按钮、取消按钮、文本字号、文本字体
		void setText(QString title, QString info = "请输入", QString input = "", QString okBtn = "确认", QString quitBtn = "取消", int size = 15, QString font = "微软雅黑");
		//获取输入内容
		QString getInput();
	private:
		void init();
		void slotConfirm();
		void slotCancel();

		QLabel m_info;
		QPushButton m_okBtn, m_quitBtn;
		QLineEdit m_input;
	};


	/* LCD计时器 */
	class LCDTimer : public QLCDNumber
	{
		Q_OBJECT
	public:
		/*	@brief:	设置大小
			@param:	unsigned char 宽
			@param:	unsigned char 高
		*/
		void setSize(unsigned char width, unsigned char height);
		/*	@brief:	设置样式
			@param:	unsigned char 显示格式 0 - 00:00:00；1 - 00:00；2 - 00:00:00:00；3 - 000
			@param:	unsigned char 最高位位数 1~4
			@param:	QString 数字颜色
			@param: QString 底色
		*/
		void setLCDStyle(unsigned char mode, unsigned char high = 2, QString num = "black", QString back = "white");
		/*	@brief:	设置当前秒数
			@param:	unsigned long long 时间秒数
		*/
		void setTime(unsigned long long seconds);
		/*	@brief:	获取当前经过秒数
			@return:unsigned long long 当前时间秒数
		*/
		unsigned long long getTime();
		/*	@brief:	暂停或继续计时
			@param:	bool true-继续
			@param:	bool true-正向计时 false-反向计时
		*/
		void setContinue(bool flag, bool dire = true);
		/*	@brief:	设置计时终点
			@param:	unsigned long long 计时结束时间秒数
		*/
		void setEndTime(unsigned long long seconds);

		explicit LCDTimer(QWidget* parent = nullptr);
	private slots:
		void slotUpdateTime();								//更新显示
	signals:
		void sigTimeOut(unsigned long long seconds);		//计时结束 seconds-当前秒数
	private:
		QTimer m_timer;
		unsigned char m_mode = 0;									//显示格式
		unsigned char m_high = 2;									//最高位位数
		unsigned long long m_sec = 0;								//秒数
		unsigned long long m_endSeconds = 24 * 60 * 60 * 365;		//正向计时结束时间，默认1年
		bool m_bDirection = true;									//计时方向 true-正向计时
	};
}