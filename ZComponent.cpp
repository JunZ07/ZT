#include "ZComponent.h"

namespace NS_ZCOMPONENT{

//��ɫ��ť
PushButtonA::PushButtonA(unsigned int width, unsigned int height, QWidget* parent)
	: QPushButton(parent)
{
	init(width, height);
	update();
}

PushButtonA::~PushButtonA()
{
}

void PushButtonA::setStatus(bool status)
{
	m_statusFlag = status;
	update();
}

void PushButtonA::setEnable(bool enable)
{
	QPushButton::setEnabled(enable);	//����QPushButtonʹ�ܻ�ʧ��
	m_enableFlag = enable;
	emit sigButtonEnableChanged(m_enableFlag);
	update();
}

void PushButtonA::init(unsigned int width, unsigned int height)
{
	//Ĭ�ϴ�С����
	this->setFixedSize(width, height);
	this->setCursor(Qt::PointingHandCursor);

	//����ź����ӵ�״̬�ı��Լ����ݳ�״̬�ı��ź�
	connect(this, &QPushButton::clicked, [=]() {
		m_statusFlag = !m_statusFlag;
		update();
		emit sigButtonStatusChanged(m_statusFlag);
		});
}
 
void PushButtonA::update()
{	
	if (true == this->getStatus()) {
		this->setText(m_onText);
		QPushButton::setStyleSheet(getStyleOn());	//ʹ�ø����stylesheet
	}
	else {
		this->setText(m_offText);
		QPushButton::setStyleSheet(getStyleOff());
	}
}

QString PushButtonA::getStyleOn()
{
	QString styleSheet = QString("QPushButton{background-color: %1;border-radius: %2px; color: %3 ;font: %4px;}").arg(m_backColorOn, RADIUS, m_fontColor, m_fontSize);
	return styleSheet;
}

QString PushButtonA::getStyleOff()
{
	QString styleSheet = QString("QPushButton{background-color: %1;border-radius: %2px; color: %3 ;font: %4px;}").arg(m_backColorOff, RADIUS, m_fontColor, m_fontSize);
	return styleSheet;
}

bool PushButtonA::getStatus()
{
	return m_statusFlag;
}

void PushButtonA::setBackgroundColor(QString bcOn, QString bcOff)
{
	m_backColorOff = bcOff;
	m_backColorOn = bcOn;
	update();
}

void PushButtonA::setFont(QString fontSize, QString fontColor)
{
	m_fontColor = fontColor;
	m_fontSize = fontSize;
	update();
}

void PushButtonA::setButtonText(QString onText, QString offText)
{
	m_onText = onText;
	m_offText = offText;
	update();
}

void PushButtonA::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event)

	// �����ť�����ã�����һ����͸���ɲ㣬�ָ�Ϊ��״̬
	QPushButton::paintEvent(event);
	if (!m_enableFlag) {
		setStatus(false);
		update();

		QPainter painter(this);
		QColor disable(COLOR_DISABLE);
		disable.setAlphaF(0.3);
		painter.setBrush(disable);
		painter.drawRoundedRect(this->rect(), RADIUS.toInt(), RADIUS.toInt());
	}
}



#pragma region ������˵�
void SideBarMenu::setWidth(unsigned int width)
{
	m_width = width;
	this->setFixedWidth(width);
	for (int i = 0; i < m_menuLayout->count(); i++) {
		QWidget* widget = m_menuLayout->itemAt(i)->widget();
		if (widget) {
			QToolButton* toolButton = qobject_cast<QToolButton*>(widget); //���QToolButton
			if (toolButton) {
				toolButton->setFixedWidth(width);
			}
		}
	}
}
void SideBarMenu::setButtonIcon(unsigned int btnNo, QString url)
{
	if (btnNo >= m_buttonList.count())
		return;
	QIcon icon(url);
	m_buttonList.at(btnNo)->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	m_buttonList.at(btnNo)->setIcon(icon);
}
SideBarMenu::SideBarMenu(QWidget* parent)
	: QWidget(parent)
{
	init();
}
SideBarMenu::~SideBarMenu()
{
}
void SideBarMenu::init() {
	//������ʽ
	this->setLayout(m_menuLayout);					
	m_menuLayout->addStretch();							//�ײ�����
	m_menuLayout->setContentsMargins(0, 0, 0, 0);		//ȡ���ڱ߾�
	m_menuLayout->setSpacing(0);						//�ؼ����ȡ��
	this->setFixedWidth(m_width);						//���
	this->setAttribute(Qt::WA_StyledBackground);		//�ײ���͸��
	QString styleSheet = QString("background-color: %1; font-size: 14pt; font-family: '΢���ź�';").arg(m_backGround);
	this->setStyleSheet(styleSheet);					//��ɫ������
}
void SideBarMenu::setColor(QString backGround, QString buttonSelected, QString buttonHover)
{
	m_backGround = backGround;
	m_buttonSelected = buttonSelected;
	m_buttonHover = buttonHover;

	//���µ�ɫ����
	QString styleSheet = QString("background-color: %1; font-size: 14pt; font-family: '΢���ź�';").arg(m_backGround);
	this->setStyleSheet(styleSheet);
	//���°�ť
	for (int i = 0; i < m_menuLayout->count(); i++) {
		QWidget* widget = m_menuLayout->itemAt(i)->widget();
		if (widget) {
			QToolButton* toolButton = qobject_cast<QToolButton*>(widget); //���QToolButton
			if (toolButton) {
				QString buttonStyle = QString("QToolButton{border-radius:0px;color:#FFFFFF;}QToolButton:hover{background-color:%1;};").arg(m_buttonHover);
				toolButton->setStyleSheet(buttonStyle);
			}
		}
	}
	//���µ�ǰ��ť
	QString buttonStyle = QString("border-radius:0px;background-color:%1;color:#FFFFFF;").arg(m_buttonSelected);
	m_lastButton->setStyleSheet(buttonStyle);
}

bool SideBarMenu::createItemButton(QString name, QWidget* widgetPtr)
{
	if (m_btnCnt >= 30)	//����20��
		return false;
	if (m_btnCnt == 0)//��ӵĵ�1����ť�����⴦��
	{
		QString buttonStyle = QString("border-radius:0px;background-color:%1;color:#FFFFFF;").arg(m_buttonSelected);
		QToolButton* toolButton = new QToolButton();
		toolButton->setCursor(Qt::PointingHandCursor);
		toolButton->setStyleSheet(buttonStyle);
		toolButton->setFixedSize(QSize(m_width, 60));
		toolButton->setText(name);
		toolButton->setProperty("widget", QVariant::fromValue((void*)widgetPtr));

		//����ź����ӵ��л���
		connect(toolButton, &QToolButton::clicked, this, &SideBarMenu::menuSelected);
		m_menuLayout->insertWidget(m_menuLayout->count() - 1, toolButton);		//���뵽ĩβ����ǰ
		m_lastButton = toolButton;
		m_buttonList.append(toolButton);
	}
	else
	{
		QString buttonStyle = QString("QToolButton{border-radius:0px;color:#FFFFFF;}QToolButton:hover{background-color:%1;};").arg(m_buttonHover);
		QToolButton* toolButton = new QToolButton();
		toolButton->setCursor(Qt::PointingHandCursor);
		toolButton->setStyleSheet(buttonStyle);
		toolButton->setFixedSize(QSize(m_width, 60));
		toolButton->setText(name);
		toolButton->setProperty("widget", QVariant::fromValue((void*)widgetPtr));

		//����ź����ӵ��л���
		connect(toolButton, &QToolButton::clicked, this, &SideBarMenu::menuSelected);
		m_menuLayout->insertWidget(m_menuLayout->count() - 1, toolButton);
		m_buttonList.append(toolButton);
	}
	m_btnCnt++;
	return true;
}
void SideBarMenu::setContentWidget(QWidget* widgetPtr)
{
	m_contentWidget = widgetPtr;
}
void SideBarMenu::menuSelected()
{
	QToolButton* senderButton = (QToolButton*)sender();
	if (m_lastButton != senderButton)
	{
		//��ȡ
		QWidget* widget = (QWidget*)senderButton->property("widget").value<void*>();
		
		if (QStackedWidget* stackedWidget = qobject_cast<QStackedWidget*>(m_contentWidget)) {	//��������������
			stackedWidget->setCurrentWidget(widget);
		}
		else if (QTabWidget* tabWidget = qobject_cast<QTabWidget*>(m_contentWidget)) {
			tabWidget->setCurrentWidget(widget);
		}

		//��ť��ʽ�л�
		m_lastButton->setStyleSheet(QString("QToolButton{border-radius:0px;color:#FFFFFF;}QToolButton:hover{background-color:%1;};").arg(m_buttonHover));
		senderButton->setStyleSheet(QString("border-radius:0px;background-color:%1;color:#FFFFFF;").arg(m_buttonSelected));
		m_lastButton = senderButton;
	}
}
#pragma endregion



#pragma region ״̬��
void StateLight::setSize(unsigned int diameter)
{
	m_size = diameter;
	this->setFixedSize(diameter, diameter);
	this->setStyleSheet(QString("background-color:%1;border-radius:%2px;").arg(m_lightNull, QString::number(diameter/2, 10)));	//Բ��
}
void StateLight::setStatus(unsigned char status)
{
	m_stateFlag = status;
	update();
}
unsigned char StateLight::getStatus()
{
	return m_stateFlag;
}
void StateLight::doFlickerWork()
{
	if (true == m_flickerFlag) {	//������˸
		if (0 == m_stateFlag || 2 == m_stateFlag)
			setStatus(1);
		else
			setStatus(0);
	}
}
void StateLight::setFlicker(bool flag, unsigned int gap)
{
	m_flickerGap = gap;
	m_flickerFlag = flag;

	if (m_flickerFlag) {
		if (!m_timer.isActive())	//������ʱ
			m_timer.start(m_flickerGap);
	}
	else {
		setStatus(0);
		m_timer.stop();
	}
}
StateLight::StateLight(QWidget* parent)
	: QLabel(parent)
{
	init();					//��ʼUI
	update();				//����UI
	setFlicker(false);		//��ͣ��˸
}
StateLight::~StateLight()
{
	setFlicker(false);
}
void StateLight::update()
{
	switch (m_stateFlag)
	{
	case 0:
		this->setStyleSheet(QString("background-color:%1;border-radius:%2px;").arg(m_lightNull, QString::number(m_size / 2, 10)));
		break;
	case 1:
		this->setStyleSheet(QString("background-color:%1;border-radius:%2px;").arg(m_lightOn, QString::number(m_size / 2, 10)));
		break;
	case 2:
		this->setStyleSheet(QString("background-color:%1;border-radius:%2px;").arg(m_lightOff, QString::number(m_size / 2, 10)));
		break;
	default:
		break;
	}
}
void StateLight::init()
{
	this->setFixedSize(m_size, m_size);
	this->setStyleSheet(QString("background-color:%1;border-radius:10px;").arg(m_lightNull));	//Բ��
	connect(&m_timer, &QTimer::timeout, this, &StateLight::doFlickerWork);						//��ʱ����
}
void StateLight::setColor(QString lightOn, QString lightOff, QString lightNull) {
	m_lightOn = lightOn;
	m_lightOff = lightOff;
	m_lightNull = lightNull;
	update();
}
#pragma endregion 



#pragma region ��ťB
PushButtonB::~PushButtonB()
{
}
void PushButtonB::init()
{
	this->setCursor(Qt::PointingHandCursor);
	this->setMinimumSize(200, 40);
	this->setStyleSheet(getStyle());
}
void PushButtonB::update()
{
	if (m_enableFlag)
		m_backGround = m_backGroundEnable;
	else
		m_backGround = COLOR_DISABLE;
	this->setStyleSheet(getStyle());
}
QString PushButtonB::getStyle()
{
	QString style1 = QString("QPushButton{color:%1; font-family: '΢���ź�'; font-size: %2px; border:2px solid #000000; border-radius:%3px; background-color:%4;}").arg(m_fontColor, QString::number(m_fontSize), QString::number(m_width/2), m_backGround);
	QString style2 = QString("QPushButton:hover{border:0px solid #000000;background-color:%1;color:%2;}").arg(m_hover, m_fontColor);
	style1 += style2;
	return style1;
}
void PushButtonB::setBtnColor(QString back, QString hover, QString font)
{
	m_backGroundEnable = back;
	m_hover = hover;
	m_fontColor = font;
}
void PushButtonB::setBtnEnable(bool enable)
{
	this->setEnabled(enable);
	m_enableFlag = enable;
	update();
}
PushButtonB::PushButtonB(QWidget* parent)
	: QPushButton(parent)
{
	init();
}
void PushButtonB::setBtnSize(unsigned int fontSize, unsigned int lenth, unsigned int width) {
	this->setFixedSize(lenth, width);
	m_width = width;
	m_fontSize = fontSize;
	update();
}
#pragma endregion


#pragma region ������״̬��
void StateTextLight::setColor(QString lightOn, QString lightOff, QString lightNull)
{
	m_light.setColor(lightOn, lightOff, lightNull);
}
StateTextLight::StateTextLight(QWidget* parent)
	: QWidget(parent)
{
	init();
}
StateTextLight::~StateTextLight()
{
}
void StateTextLight::setState(unsigned char status, QString info)
{
	setFlicker(false, info);
	m_light.setStatus(status);
	m_label.setText(info);
}
void StateTextLight::setFlicker(bool status, QString info)
{
	m_flickerFlag = status;
	m_light.setFlicker(m_flickerFlag);
	m_label.setText(info);
}
void StateTextLight::setStyles(unsigned int diameter, unsigned int size, QString textColor, QString font)
{
	m_light.setSize(diameter);
	m_label.setStyleSheet( QString("font-size: %1px; color: %2; font-family: %3;").arg(QString::number(size), textColor, font));
}
void StateTextLight::init()
{
	QHBoxLayout* layout = new QHBoxLayout;
	layout->addWidget(&m_light);
	layout->addWidget(&m_label);
	this->setLayout(layout);
}
#pragma endregion


#pragma region ���׼�ʱ��
void LabelTimer::setTime(unsigned long long seconds)
{
	m_seconds = seconds;
}

unsigned long long LabelTimer::getTime()
{
	return m_seconds;
}

void LabelTimer::setContinue(bool flag, bool dire)
{
	m_direction = dire;
	if (true == flag)
		m_timer.start();
	else
		m_timer.stop();
}
void LabelTimer::setEndTime(unsigned long long seconds)
{
	m_endSeconds = seconds;
}
LabelTimer::LabelTimer(QWidget* parent)
	: QWidget(parent)
{
	m_timeLabel.setAlignment(Qt::AlignCenter);
	m_timeLabel.setStyleSheet(QString("QLabel { font-size: 15px; font-family: '΢���ź�'; font-weight:bold; color: white;}"));

	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->addStretch();
	layout->addWidget(&m_timeLabel);
	layout->addStretch();
	this->layout()->setSpacing(0);
	this->layout()->setContentsMargins(0, 0, 0, 0);
	this->setLayout(layout);

	m_timer.setInterval(1000);
	m_timer.start();
	connect(&m_timer, &QTimer::timeout, this, &LabelTimer::updateTime);
}

void LabelTimer::updateTime() {
	if (m_direction) m_seconds++;			//���Ӿ���ʱ�䣬�����ʱ
	else m_seconds--;
	if (m_seconds == m_endSeconds) {
		m_timer.stop();
		emit sigTimeOut(m_seconds);			//��ʱ����
	}
	if (m_seconds == 0) {
		m_timer.stop();
		emit sigTimeOut(m_seconds);
	}
	QString timeString = QString("%1 : %2 : %3")
		.arg(m_seconds / 3600, 2, 10, QLatin1Char('0'))
		.arg((m_seconds % 3600) / 60, 2, 10, QLatin1Char('0')) 
		.arg(m_seconds % 60, 2, 10, QLatin1Char('0')); 
	m_timeLabel.setText(timeString);
}
void LabelTimer::setTextStyle(int size, QString font, QString color) {
	m_timeLabel.setStyleSheet(QString("QLabel { font-size: %1px; font-family: %2; font-weight:bold; color: %3;}").arg(QString::number(size), font, color));
}
#pragma endregion


#pragma region ��ťC
PushButtonC::PushButtonC(QWidget* parent) 
	: QPushButton(parent)
{
	init();
}
bool PushButtonC::getStatus()
{
	return m_statusFlag;
}
void PushButtonC::setBtnColor(QString bcOn, QString bcOff, QString hoverOn, QString hoverOff)
{
	m_backColorOn = bcOn;
	m_backColorOff = bcOff;
	m_hoverOff = hoverOff;
	m_hoverOn = hoverOn;
	update();
}
void PushButtonC::setFontStyle(unsigned int size, QString fontColor, QString font)
{
	m_fontSize = QString::number(size);
	m_fontColor = fontColor;
	m_fontFamily = font;
	update();
}
void PushButtonC::setStatus(bool status)
{
	m_statusFlag = status;
	update();
}
void PushButtonC::setBtnEnable(bool status)
{
	m_enableFlag = status;
	this->setEnabled(status);
	update();
}
void PushButtonC::setBtnText(QString onText, QString offText)
{
	m_onText = onText;
	m_offText = offText;
	update();
}
void PushButtonC::setBtnSize(int width, int height)
{
	m_width = width;
	m_height = height;
	update();
}
void PushButtonC::init()
{
	this->setCursor(Qt::PointingHandCursor);
	
	update();

	connect(this, &QPushButton::clicked, [=]() {//����ź����ӵ�״̬�ı��Լ����ݳ�״̬�ı��ź�
		setStatus(!m_statusFlag);
		update();
		emit sigButtonStatusChanged(m_statusFlag);
		});
}
void PushButtonC::update()
{
	QMutexLocker locker(&m_updateMutex);
	this->setFixedSize(m_width, m_height);
	if (m_statusFlag) {
		this->setText(m_onText);
		QString styleSheet = QString("QPushButton{background-color: %1; border-radius: %2px; color: %3 ;font-size: %4px; font-family: %5;} "
									"QPushButton::hover{background-color: %6; border-radius: %2px; color: %3 ;font-size: %4px; font-family: %5;}")
									.arg(m_backColorOn, QString::number(m_height / 2), m_fontColor, m_fontSize, m_hoverOn, m_fontFamily);
		QPushButton::setStyleSheet(styleSheet);
	}
	else {
		this->setText(m_offText);
		QString styleSheet = QString("QPushButton{background-color: %1; border-radius: %2px; color: %3 ;font-size: %4px; font-family: %5;} "
									"QPushButton::hover{background-color: %6; border-radius: %2px; color: %3 ;font-size: %4px; font-family: %5;}")
									.arg(m_backColorOff, QString::number(m_height / 2), m_fontColor, m_fontSize, m_hoverOff, m_fontFamily);
		QPushButton::setStyleSheet(styleSheet);
	}
	if (!m_enableFlag) {		//��ʹ��
		QString styleSheet = QString("QPushButton{background-color: %1; border-radius: %2px; color: %3 ;font-size: %4px; font-family: %5;} "
									"QPushButton::hover{background-color: %6; border-radius: %2px; color: %3 ;font-size: %4px; font-family: %5;}")
									.arg(m_backColorEnable, QString::number(m_height / 2), m_fontColor, m_fontSize, m_hoverOn, m_fontFamily);
		QPushButton::setStyleSheet(styleSheet);
	}
	QFont font = QPushButton::font();
	font.setFamily(m_fontFamily);
	font.setBold(true);
	font.setPointSize(m_fontSize.toInt());
	QPushButton::setFont(font);
	this->setFont(font);
}
#pragma endregion


#pragma region ����˵�
void TabMenu::setContentFont(int size, QString font)
{
	for (int i = 0; i < this->count(); ++i) {
		this->widget(i)->setStyleSheet(QString("font-size: %1px; font-family: %2;").arg(QString::number(size), font));
	}
}
TabMenu::TabMenu(QWidget* parent) 
	: QTabWidget(parent)
{
	update();
}
void TabMenu::setIcon(int index, QString iconPath)
{
	QTabBar* tabBar = this->tabBar();
	QIcon icon(iconPath);
	tabBar->setTabIcon(index, icon);
}
void TabMenu::setTabStyle(QString color, int size, QString font) {
	m_basicColor = color;
	m_fontSize = size;
	m_fontFamily = font;
	update();
}
void TabMenu::update() {
	this->setStyleSheet(QString("QTabWidget::pane{border: 1px solid %1}").arg(m_basicColor));
	this->setStyleSheet(this->styleSheet() + "QTabWidget::tab-bar{alignment: left; }");
	this->setStyleSheet(this->styleSheet() + "QTabBar::tab{background: #D3D3D3;border: 1px solid #FFFFFF;border-top-left-radius: 4px;border-top-right-radius:4px;min-width:100px;padding:5px;color:#000000;}");
	this->setStyleSheet(this->styleSheet() + QString("QTabBar::tab:selected, QTabBar::tab:hover{background:%1;color:#DDDDDD;}").arg(m_basicColor));
	this->setStyleSheet(this->styleSheet() + QString("QTabBar::tab:selected{border:2px solid %1;}").arg(m_basicColor));
	QFont font = this->tabBar()->font();
	font.setPointSize(m_fontSize); 
	font.setFamily(m_fontFamily);
	font.setWeight(QFont::Bold);
	this->tabBar()->setFont(font);
	this->tabBar()->setCursor(Qt::PointingHandCursor);
}
#pragma endregion


#pragma region �����뵯��
singleInputDialog::singleInputDialog(QWidget* parent) 
	: QDialog(parent)
{
	init();

	connect(&m_okBtn, &QPushButton::clicked, this, &singleInputDialog::slotConfirm);	//ȷ��
	connect(&m_quitBtn, &QPushButton::clicked, this, &singleInputDialog::slotCancel);	//ȡ��
}
void singleInputDialog::setText(QString title, QString info, QString input, QString okBtn, QString quitBtn, int size, QString font)
{
	this->setWindowTitle(title);
	m_info.setText(info);
	m_input.setText(input);
	m_okBtn.setText(okBtn);
	m_quitBtn.setText(quitBtn);
	this->setStyleSheet(QString("font-size: %1pt; font-family: %2;").arg(QString::number(size), font));
}
QString singleInputDialog::getInput()
{
	return m_input.text();
}
void singleInputDialog::init()
{
	this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);		//�Ƴ�������ť
	QHBoxLayout* hLayout = new QHBoxLayout(this);
	hLayout->addWidget(&m_okBtn);
	hLayout->addWidget(&m_quitBtn);
	QWidget* hWdg = new QWidget(this);
	hWdg->setLayout(hLayout);

	QVBoxLayout* vLayout = new QVBoxLayout(this);
	vLayout->addWidget(&m_info);
	vLayout->addWidget(&m_input);
	vLayout->addWidget(hWdg);
	this->setLayout(vLayout);
}

void singleInputDialog::slotConfirm()
{
	accept();
}

void singleInputDialog::slotCancel()
{
	reject();
}
#pragma endregion


#pragma region LCD��ʱ��
void LCDTimer::setSize(unsigned char width, unsigned char height)
{
	this->setFixedSize(width, height);
}
void LCDTimer::setLCDStyle(unsigned char mode, unsigned char high, QString num, QString back)
{
	m_mode = mode;
	m_high = high;
	if (m_high < 1) m_high = 1;
	if (m_high > 4) m_high = 4;
	this->setStyleSheet(QString("color: %1; background-color; %2;").arg(num, back));
	this->setSegmentStyle(QLCDNumber::Flat);
	switch (m_mode)
	{
	case 0:
		this->setDigitCount(6 + m_high);	//HHH:MM:SS
		break;
	case 1:
		this->setDigitCount(3 + m_high);	//MMM:SS
		break;
	case 2:
		this->setDigitCount(9 + m_high);	//DDD:HH:MM:SS
		break;
	case 3:
		this->setDigitCount(m_high);		//SSSS
		break;
	default:
		break;
	}
	slotUpdateTime();
}
void LCDTimer::setTime(unsigned long long seconds)
{
	m_sec = seconds;
}

unsigned long long LCDTimer::getTime()
{
	return m_sec;
}

void LCDTimer::setContinue(bool flag, bool dire)
{
	m_bDirection = dire;
	if (true == flag)
		m_timer.start();
	else
		m_timer.stop();
}

void LCDTimer::setEndTime(unsigned long long seconds)
{
	m_endSeconds = seconds;
}
LCDTimer::LCDTimer(QWidget* parent)
{
	this->setStyleSheet("color: white; background-color; black;");
	this->setSegmentStyle(QLCDNumber::Flat);
	this->setDigitCount(8);
	this->display("00:00:00");
	this->setFixedSize(180, 30);

	m_timer.setInterval(1000);
	m_timer.start();
	connect(&m_timer, &QTimer::timeout, this, &LCDTimer::slotUpdateTime);
}
void LCDTimer::slotUpdateTime() 
{
	if (m_bDirection) m_sec++;			//���Ӿ���ʱ�䣬�����ʱ
	else m_sec--;
	if (m_sec == m_endSeconds) {
		m_timer.stop();
		emit sigTimeOut(m_sec);			//��ʱ����
	}
	if (m_sec == 0) {
		m_timer.stop();
		emit sigTimeOut(m_sec);
	}

	QString timeString;
	switch (m_mode)
	{
	case 0:
		 timeString = QString("%1:%2:%3")
			.arg(m_sec / 3600, m_high, 10, QLatin1Char('0'))
			.arg((m_sec % 3600) / 60, 2, 10, QLatin1Char('0'))
			.arg(m_sec % 60, 2, 10, QLatin1Char('0'));
		break;
	case 1:
		timeString = QString("%1:%2")
			.arg(m_sec / 60, m_high, 10, QLatin1Char('0'))
			.arg(m_sec % 60, 2, 10, QLatin1Char('0'));
		break;
	case 2:
		timeString = QString("%1:%2:%3:%4")
			.arg(m_sec / (3600*24), m_high, 10, QLatin1Char('0'))
			.arg((m_sec % (3600*24)) / 3600, 2, 10, QLatin1Char('0'))
			.arg((m_sec % 3600) / 60, 2, 10, QLatin1Char('0'))
			.arg(m_sec % 60, 2, 10, QLatin1Char('0'));
		break;
	case 3:
		timeString = QString("%1")
			.arg(m_sec, m_high, 10, QLatin1Char('0'));
		break;
	default:
		break;
	}
	this->display(timeString);
}
#pragma endregion


}

