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
    this->_postInit();
}

PushButton::PushButton(QString text, QWidget *parent = nullptr, QVariant *icon = nullptr) : QPushButton(parent)
{

    //this->_postInit();
    this->initialize(parent);
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