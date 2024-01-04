#include "button.h"
#include "../../common/style_sheet.h"
#include "../../common/font.h"
#include "../../common/icon.h"

#include <QApplication>

void PushButton::initialize(QWidget *parent = nullptr)
{   
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("BUTTON"), Theme::AUTO);
    this->isPressed = false;
    this->isHover = false;
    setIconSize(QSize(16, 16));
    Font().setFont(this, 13, QFont::Normal);
    //this->_postInit();
}

PushButton::PushButton(QString text, QWidget *parent = nullptr, QVariant *icon = nullptr) : QPushButton(parent)
{
    this->initialize(parent);
    //this->_postInit();
    this->setText(text);
    this->setIcon(icon);
}

PushButton::PushButton(QIcon *icon, QString text, QWidget *parent) : QPushButton(parent)
{
    this->initialize(parent);
    this->setText(text);
    QVariant _icon = QVariant::fromValue<QIcon>(*icon);
    this->setIcon(&_icon);
}

PushButton::PushButton(FluentIcon *icon, QString text, QWidget *parent) : QPushButton(parent)
{
    this->initialize(parent);
    this->setText(text);
    //QVariant *_icon = new QVariant(QVariant::fromValue<FluentIcon>(*icon));
    QVariant *_icon = new QVariant();
    _icon->setValue<FluentIcon>(*icon);
    this->setIcon(_icon);
}

void PushButton::setIcon(QVariant *icon)
{
    if(icon != nullptr){
        QVariant hasIcon = QVariant::fromValue<bool>(true);
        this->setProperty("hasIcon", &hasIcon);
    }else{
        QVariant hasIcon = QVariant::fromValue<bool>(false);
        this->setProperty("hasIcon", &hasIcon);
    }
    setStyle(QApplication::style());
    if(icon != nullptr)
    {
        this->_icon = icon;
    }else{
        QVariant icon = QVariant::fromValue<QIcon>(QIcon());
        this->_icon = &icon;
    }
    QPushButton::update();
}


bool PushButton::setProperty(QString name, QVariant *value)
{
    if(name != "icon")
    {
        return QPushButton::setProperty(name.toLatin1().data(), *value);
    }

    this->setIcon(value);
    return true;

}

QIcon PushButton::icon()
{
    return MIcon().toQIcon(this->_icon);
}

void PushButton::mousePressEvent(QMouseEvent *e)
{
    this->isPressed = true;
    QPushButton::mousePressEvent(e);
}

void PushButton::mouseReleaseEvent(QMouseEvent *e)
{
    this->isPressed = false;
    QPushButton::mouseReleaseEvent(e);
}

void PushButton::enterEvent(QEvent *event)
{
    this->isHover = true;
    QPushButton::update();
}

void PushButton::leaveEvent(QEvent *event)
{
    this->isHover = false;
    QPushButton::update();
}

void PushButton::_drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state = QIcon::State::Off)
{
    MIcon().drawIcon(icon, painter, rect, nullptr, state);
}

void PushButton::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);
    if(this->icon().isNull())
    {
        return;
    }

    QPainter *painter = new QPainter(this);
    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    if(!isEnabled()){
        painter->setOpacity(0.3628);
    }else if(this->isPressed){
        painter->setOpacity(0.786);
    }

    int w = iconSize().width();
    int h = iconSize().height();
    int y = (height() - h) / 2;
    int mw = minimumSizeHint().width();
    if(mw > 0)
    {
        //TODO:self._drawIcon(self._icon, painter, QRectF(12+(self.width()-mw)//2, y, w, h))
        this->_drawIcon(this->_icon, painter, QRect(12 + (width() - mw)/2, y, w, h));
    }else{
        this->_drawIcon(this->_icon, painter, QRect(12, y, w, h));
    }

    painter->end();
}

PrimaryPushButton::PrimaryPushButton(QString text, QWidget *parent, QVariant *icon) : PushButton(text, parent, icon)
{

}

PrimaryPushButton::PrimaryPushButton(FluentIcon *icon, QString text, QWidget *parent) : PushButton(icon, text, parent)
{
    
}

void PrimaryPushButton::_drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state = QIcon::State::Off)
{
    QVariant qi;

    if(icon->canConvert<FluentIcon>() && isEnabled()) 
    {
        Theme theme;
        if(!isDarkTheme()){
            theme = Theme::DARK;
        }else{
            theme = Theme::LIGHT;
        }
        FluentIcon i = icon->value<FluentIcon>();
        qi = QVariant::fromValue<QIcon>(*(i.icon(theme, QColor())));
    }else if(!isEnabled()){
        painter->setOpacity(isDarkTheme() ? 0.786 : 0.9);
        if(icon->canConvert<FluentIcon>()){
            FluentIcon i = icon->value<FluentIcon>();
            qi = QVariant::fromValue<QIcon *>(i.icon(Theme::DARK, nullptr));
        }
    }else{
        qi = *icon;
    }
    PushButton::_drawIcon(&qi, painter, rect, state);
}

void ToggleButton::_postInit()
{
    setCheckable(true);
    setChecked(false);
}

void ToggleButton::_drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state = QIcon::State::Off)
{
    if(!isChecked()){
        return PushButton::_drawIcon(icon, painter, rect);
    }
    PrimaryPushButton *p = new PrimaryPushButton();
    p->_drawIcon(icon, painter, rect, QIcon::State::On);
}

void HyperlinkButton::initialize(QWidget *parent)
{
    PushButton::initialize(parent);
    this->_url = new QUrl();
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("BUTTON"), Theme::AUTO);
    this->setCursor(Qt::PointingHandCursor);
    Font().setFont(this, 14, QFont::Normal);
    connect(this, &QPushButton::clicked, this, &HyperlinkButton::_onClicked);
}

HyperlinkButton::HyperlinkButton(QVariant *url, QString text, QWidget *parent, QVariant *icon)
{
    this->initialize(parent);
    setText(text);
    setUrl(url);
    setIcon(icon);
}

HyperlinkButton::HyperlinkButton(QIcon *icon, QVariant *url, QString text, QWidget *parent)
{
    this->initialize(parent);
    setText(text);
    setUrl(url);
    QVariant _icon = QVariant::fromValue<QIcon>(*icon);
    this->setIcon(&_icon);
}

HyperlinkButton::HyperlinkButton(FluentIcon *icon, QVariant *url, QString text, QWidget *parent)
{
    this->initialize(parent);
    setText(text);
    setUrl(url);
    QVariant *_icon = new QVariant();
    _icon->setValue<FluentIcon>(*icon);
    this->setIcon(_icon);
}

QUrl *HyperlinkButton::getUrl()
{
    return this->_url;
}

void HyperlinkButton::setUrl(QVariant *url)
{
    if(url->canConvert<QString>()){
        QString s = url->value<QString>();
        this->_url = new QUrl(s);
    }else if(url->canConvert<QUrl>()){
        QUrl qu = url->value<QUrl>();
        this->_url = new QUrl(qu);
    }
}

void HyperlinkButton::_onClicked()
{
    if(this->getUrl()->isValid())
    {
        QDesktopServices::openUrl(*(this->getUrl()));
    }
}

void HyperlinkButton::_drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state = QIcon::State::Off)
{
    QVariant qi;

    if(icon->canConvert<FluentIcon>() && isEnabled()) 
    {
        ThemeColor *t = new ThemeColor();
        FluentIcon i = icon->value<FluentIcon>();
        qi = QVariant::fromValue<QIcon>(*(i.icon(Theme::AUTO, *(t->themeColor()))));
    }else if(!isEnabled()){
        painter->setOpacity(isDarkTheme() ? 0.786 : 0.9);
        if(icon->canConvert<FluentIcon>()){
            FluentIcon i = icon->value<FluentIcon>();
            qi = QVariant::fromValue<QIcon *>(i.icon(Theme::DARK, nullptr));
        }
    }else{
        qi = *icon;
    }
    
    MIcon().drawIcon(&qi, painter, rect, nullptr, state);
    
}

void RadioButton::initialize(QWidget *parent)
{
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("BUTTON"), Theme::AUTO);
}

RadioButton::RadioButton(QString text, QWidget *parent) : QRadioButton(parent)
{
    this->initialize(parent);
    setText(text);
}

void ToolButton::initialize(QWidget *parent)
{
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("BUTTON"), Theme::AUTO);
    this->isPressed = false;
    this->isHover = false;
    setIconSize(QSize(16, 16));
    QVariant _icon = QVariant::fromValue<QIcon>(QIcon());
    this->setIcon(&_icon);
    Font().setFont(this, 14, QFont::Normal);
    this->_postInit();
}

ToolButton::ToolButton(FluentIcon *icon, QWidget *parent) : QToolButton(parent)
{
    this->initialize(parent);
    QVariant *__icon = new QVariant();
    __icon->setValue<FluentIcon>(*icon);
    this->setIcon(__icon);
}

ToolButton::ToolButton(QIcon *icon, QWidget *parent) : QToolButton(parent)
{
    this->initialize(parent);
    QVariant __icon = QVariant::fromValue<QIcon>(*icon);
    this->setIcon(&__icon);
}

ToolButton::ToolButton(QString icon, QWidget *parent) : QToolButton(parent)
{
    this->initialize(parent);
    QVariant __icon = QVariant::fromValue<QString>(icon);
    this->setIcon(&__icon);
}

void ToolButton::_postInit(){}

void ToolButton::setIcon(QVariant *icon)
{
    this->_icon = icon;
    this->update();
}

QIcon ToolButton::icon()
{
    return MIcon().toQIcon(this->_icon);
}

bool ToolButton::setProperty(QString name, QVariant *value)
{
    if(name != "icon")
    {
        return QToolButton::setProperty(name.toLatin1().data(), *value);
    }

    this->setIcon(value);
    return true;
}

void ToolButton::mousePressEvent(QMouseEvent *e)
{
    this->isPressed = true;
    QToolButton::mousePressEvent(e);
}

void ToolButton::mouseReleaseEvent(QMouseEvent *e)
{
    this->isPressed = false;
    QToolButton::mouseReleaseEvent(e);
}

void ToolButton::enterEvent(QEvent *event)
{
    this->isHover = true;
    QToolButton::update();
}

void ToolButton::leaveEvent(QEvent *event)
{
    this->isHover = false;
    QToolButton::update();
}

void ToolButton::_drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state = QIcon::State::Off)
{
    MIcon().drawIcon(icon, painter, rect, nullptr, state);
}

void ToolButton::paintEvent(QPaintEvent *event)
{
    QToolButton::paintEvent(event);
    if(this->icon().isNull())
    {
        return;
    }

    QPainter *painter = new QPainter(this);
    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    if(!isEnabled()){
        painter->setOpacity(0.43);
    }else if(this->isPressed){
        painter->setOpacity(0.63);
    }

    int w = iconSize().width();
    int h = iconSize().height();
    int y = (height() - h) / 2;
    int x = (width() - w) / 2;
    
    this->_drawIcon(this->_icon, painter, QRect(x, y, w, h));
    painter->end();
}

TransparentToolButton::TransparentToolButton(FluentIcon *icon, QWidget *parent) : ToolButton(icon, parent){}

TransparentToolButton::TransparentToolButton(QIcon *icon, QWidget *parent) : ToolButton(icon, parent){}

TransparentToolButton::TransparentToolButton(QString icon, QWidget *parent) : ToolButton(icon, parent){}


PrimaryToolButton::PrimaryToolButton(FluentIcon *icon, QWidget *parent) : ToolButton(icon, parent){}

PrimaryToolButton::PrimaryToolButton(QIcon *icon, QWidget *parent) : ToolButton(icon, parent){}

PrimaryToolButton::PrimaryToolButton(QString icon, QWidget *parent) : ToolButton(icon, parent){}

void PrimaryToolButton::_drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state = QIcon::State::Off)
{
    QVariant qi;

    if(icon->canConvert<FluentIcon>() && isEnabled()) 
    {
        Theme theme;
        if(!isDarkTheme()){
            theme = Theme::DARK;
        }else{
            theme = Theme::LIGHT;
        }
        FluentIcon i = icon->value<FluentIcon>();
        qi = QVariant::fromValue<QIcon>(*(i.icon(theme, QColor())));
    }else if(!isEnabled()){
        painter->setOpacity(isDarkTheme() ? 0.786 : 0.9);
        if(icon->canConvert<FluentIcon>()){
            FluentIcon i = icon->value<FluentIcon>();
            qi = QVariant::fromValue<QIcon *>(i.icon(Theme::DARK, nullptr));
        }
    }else{
        qi = *icon;
    }
    ToolButton::_drawIcon(&qi, painter, rect, state);
}