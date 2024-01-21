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
    Font().setFont(this, 14, QFont::Normal);
    this->_postInit();
}

PushButton::PushButton(QWidget *parent = nullptr) : QPushButton(parent)
{
    this->initialize(parent);
}

PushButton::PushButton(QString text, QWidget *parent = nullptr, QVariant *icon = nullptr) : QPushButton(parent)
{
    this->initialize(parent);
    this->_postInit();
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
        QVariant *hasIcon = new QVariant(QVariant::fromValue<bool>(true));
        this->setProperty("hasIcon", hasIcon);
    }else{
        QVariant *hasIcon = new QVariant(QVariant::fromValue<bool>(false));
        this->setProperty("hasIcon", hasIcon);
    }
    setStyle(QApplication::style());
    if(icon != nullptr)
    {
        this->_icon = new QVariant(*icon);
    }else{
        QVariant *icon = new QVariant(QVariant::fromValue<QIcon>(QIcon()));
        this->_icon = icon;
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

HyperlinkButton::HyperlinkButton(QVariant *url, QString text, QWidget *parent, QVariant *icon) : PushButton(parent)
{
    this->initialize(parent);
    setText(text);
    setUrl(url);
    setIcon(icon);
}

HyperlinkButton::HyperlinkButton(QIcon *icon, QVariant *url, QString text, QWidget *parent): PushButton(parent)
{
    this->initialize(parent);
    setText(text);
    setUrl(url);
    QVariant _icon = QVariant::fromValue<QIcon>(*icon);
    this->setIcon(&_icon);
}

HyperlinkButton::HyperlinkButton(FluentIcon *icon, QVariant *url, QString text, QWidget *parent): PushButton(parent)
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

ToolButton::ToolButton(QWidget *parent) : QToolButton(parent)
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
    this->_icon = new QVariant(*icon);
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

ToggleToolButton::ToggleToolButton(FluentIcon *icon, QWidget *parent) : ToolButton(icon, parent){
    this->_postInit();
}

ToggleToolButton::ToggleToolButton(QIcon *icon, QWidget *parent) : ToolButton(icon, parent){
    this->_postInit();
}

ToggleToolButton::ToggleToolButton(QString icon, QWidget *parent) : ToolButton(icon, parent){
    this->_postInit();
}

void ToggleToolButton::_postInit()
{
    setCheckable(true);
    setChecked(false);
}

void ToggleToolButton::_drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state = QIcon::State::Off)
{
    if(!isChecked()){
        return ToolButton::_drawIcon(icon, painter, rect);
    }
    PrimaryToolButton *p = new PrimaryToolButton(this);
    p->_drawIcon(icon, painter, rect, QIcon::State::On);
}


DropDownButtonBase::DropDownButtonBase(){
    this->_menu = nullptr;
    //this->arrowAni = new TranslateYAnimation(this, 2);
}


void DropDownButtonBase::setMenu(RoundMenu *menu)
{
    this->_menu = menu;
}

RoundMenu *DropDownButtonBase::menu()
{
    return this->_menu;
}

void DropDownButtonBase::_showMenu()
{
    if(!this->menu()){
        return;
    }

    RoundMenu *menu = this->menu();
    menu->view->setMinimumWidth(((QWidget *)this)->width());
    menu->view->adjustSize(nullptr, MenuAnimationType::NONE);
    menu->adjustSize();

    int x = -menu->width() / 2 + menu->layout()->contentsMargins().left() + ((QWidget *)this)->width() / 2;
    QPoint pd = ((QWidget *)this)->mapToGlobal(QPoint(x, ((QWidget *)this)->height()));
    int hd = menu->view->heightForAnimation(&pd, MenuAnimationType::DROP_DOWN);

    QPoint pu = ((QWidget *)this)->mapToGlobal(QPoint(x, 0));
    int hu = menu->view->heightForAnimation(&pu, MenuAnimationType::PULL_UP);

    if(hd >= hu){
        menu->view->adjustSize(&pd, MenuAnimationType::DROP_DOWN);
        menu->exec(&pd, true, MenuAnimationType::DROP_DOWN);
    }else{
        menu->view->adjustSize(&pu, MenuAnimationType::PULL_UP);
        menu->exec(&pu, true, MenuAnimationType::PULL_UP);
    }
}

void DropDownButtonBase::_hideMenu()
{
    if(this->menu())
        this->menu()->hide();
}

void DropDownButtonBase::_drawDropDownIcon(QPainter *painter, QRect rect)
{
    if(isDarkTheme()){
        FluentIcon *icon = new FluentIcon();
        icon->setIconName(QString("ARROW_DOWN"));
        icon->render(painter, rect, Theme::AUTO, 0, nullptr);
    }else{
        FluentIcon *icon = new FluentIcon();
        icon->setIconName(QString("ARROW_DOWN"));

        /*
        std::map<QString, QString> attributes = {
            {QString("fill"), QString("#646464")}
        };
        */
        std::map<QString, QString> attributes;
        attributes[QString("fill")] = QString("#646464");
        
        icon->render(painter, rect, Theme::AUTO, 0, &attributes);
        //icon->render(painter, rect, Theme::AUTO, 0, nullptr);
    }
}

void DropDownButtonBase::paintEvent(QPaintEvent *event)
{
    QPainter *painter = new QPainter((QWidget *)this);
    painter->setRenderHints(QPainter::Antialiasing);
    if(this->isHover){
        painter->setOpacity(0.8);
    }else if(this->isPressed){
        painter->setOpacity(0.7);
    }

    QRect rect = QRect(((QWidget *)this)->width() - 22, ((QWidget *)this)->height() / 2 - 5 + this->arrowAni->y(), 10, 10);
    this->_drawDropDownIcon(painter, rect);
    painter->end();
}


void DropDownPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    PushButton::mouseReleaseEvent(e);
    this->_showMenu();
}

void DropDownPushButton::paintEvent(QPaintEvent *event)
{
    PushButton::paintEvent(event);
    QPainter *painter = new QPainter((QWidget *)this);
    painter->setRenderHints(QPainter::Antialiasing);
    if(this->isHover){
        painter->setOpacity(0.8);
    }else if(this->isPressed){
        painter->setOpacity(0.7);
    }

    QRect rect = QRect(((QWidget *)this)->width() - 22, ((QWidget *)this)->height() / 2 - 5 + this->arrowAni->y(), 10, 10);
    this->_drawDropDownIcon(painter, rect);
    painter->end();
}


void DropDownPushButton::setMenu(RoundMenu *menu)
{
    this->_menu = menu;
}

RoundMenu *DropDownPushButton::menu()
{
    return this->_menu;
}

void DropDownPushButton::_showMenu()
{
    if(!this->menu()){
        return;
    }

    RoundMenu *menu = this->menu();
    menu->view->setMinimumWidth(this->width());
    menu->view->adjustSize(nullptr, MenuAnimationType::NONE);
    menu->adjustSize();

    int x = -menu->width() / 2 + menu->layout()->contentsMargins().left() + this->width() / 2;
    QPoint pd = this->mapToGlobal(QPoint(x, this->height()));
    int hd = menu->view->heightForAnimation(&pd, MenuAnimationType::DROP_DOWN);

    QPoint pu = this->mapToGlobal(QPoint(x, 0));
    int hu = menu->view->heightForAnimation(&pu, MenuAnimationType::PULL_UP);

    if(hd >= hu){
        menu->view->adjustSize(&pd, MenuAnimationType::DROP_DOWN);
        menu->exec(&pd, true, MenuAnimationType::DROP_DOWN);
    }else{
        menu->view->adjustSize(&pu, MenuAnimationType::PULL_UP);
        menu->exec(&pu, true, MenuAnimationType::PULL_UP);
    }
}

void DropDownPushButton::_hideMenu()
{
    if(this->menu())
        this->menu()->hide();
}

void DropDownPushButton::_drawDropDownIcon(QPainter *painter, QRect rect)
{
    if(isDarkTheme()){
        FluentIcon *icon = new FluentIcon();
        icon->setIconName(QString("ARROW_DOWN"));
        icon->render(painter, rect, Theme::AUTO, 0, nullptr);
    }else{
        FluentIcon *icon = new FluentIcon();
        icon->setIconName(QString("ARROW_DOWN"));

        /*
        std::map<QString, QString> attributes = {
            {QString("fill"), QString("#646464")}
        };
        */
        std::map<QString, QString> attributes;
        attributes[QString("fill")] = QString("#646464");
        
        icon->render(painter, rect, Theme::AUTO, 0, &attributes);
        //icon->render(painter, rect, Theme::AUTO, 0, nullptr);
    }
}




void DropDownToolButton::mouseReleaseEvent(QMouseEvent *e)
{
    ToolButton::mouseReleaseEvent(e);
    this->_showMenu();
}

void DropDownToolButton::_drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state)
{
    //rect.moveLeft(12);
    QRect *r = new QRect(rect);
    r->moveLeft(12);
    //r->moveRight(25);
    return ToolButton::_drawIcon(icon, painter, *r);
}

void DropDownToolButton::paintEvent(QPaintEvent *event)
{
    ToolButton::paintEvent(event);

    QPainter *painter = new QPainter(this);
    painter->setRenderHints(QPainter::Antialiasing);
    if(this->isHover){
        painter->setOpacity(0.8);
    }else if(this->isPressed){
        painter->setOpacity(0.7);
    }

    QRect rect = QRect(this->width() - 22, this->height() / 2 - 5 + this->arrowAni->y(), 10, 10);
    this->_drawDropDownIcon(painter, rect);
    painter->end();

}


void DropDownToolButton::setMenu(RoundMenu *menu)
{
    this->_menu = menu;
}

RoundMenu *DropDownToolButton::menu()
{
    return this->_menu;
}

void DropDownToolButton::_showMenu()
{
    if(!this->menu()){
        return;
    }

    RoundMenu *menu = this->menu();
    menu->view->setMinimumWidth(this->width());
    menu->view->adjustSize(nullptr, MenuAnimationType::NONE);
    menu->adjustSize();

    int x = -menu->width() / 2 + menu->layout()->contentsMargins().left() + this->width() / 2;
    QPoint pd = this->mapToGlobal(QPoint(x, this->height()));
    int hd = menu->view->heightForAnimation(&pd, MenuAnimationType::DROP_DOWN);

    QPoint pu = this->mapToGlobal(QPoint(x, 0));
    int hu = menu->view->heightForAnimation(&pu, MenuAnimationType::PULL_UP);

    if(hd >= hu){
        menu->view->adjustSize(&pd, MenuAnimationType::DROP_DOWN);
        menu->exec(&pd, true, MenuAnimationType::DROP_DOWN);
    }else{
        menu->view->adjustSize(&pu, MenuAnimationType::PULL_UP);
        menu->exec(&pu, true, MenuAnimationType::PULL_UP);
    }
}

void DropDownToolButton::_hideMenu()
{
    if(this->menu())
        this->menu()->hide();
}

void DropDownToolButton::_drawDropDownIcon(QPainter *painter, QRect rect)
{
    if(isDarkTheme()){
        FluentIcon *icon = new FluentIcon();
        icon->setIconName(QString("ARROW_DOWN"));
        icon->render(painter, rect, Theme::AUTO, 0, nullptr);
    }else{
        FluentIcon *icon = new FluentIcon();
        icon->setIconName(QString("ARROW_DOWN"));

        /*
        std::map<QString, QString> attributes = {
            {QString("fill"), QString("#646464")}
        };
        */
        std::map<QString, QString> attributes;
        attributes[QString("fill")] = QString("#646464");
        
        icon->render(painter, rect, Theme::AUTO, 0, &attributes);
        //icon->render(painter, rect, Theme::AUTO, 0, nullptr);
    }
}





////////////////////////////////////////////////////////
void PrimaryDropDownPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    PrimaryPushButton::mouseReleaseEvent(e);
    this->_showMenu();
}

void PrimaryDropDownPushButton::paintEvent(QPaintEvent *event)
{
    PrimaryPushButton::paintEvent(event);
    QPainter *painter = new QPainter((QWidget *)this);
    painter->setRenderHints(QPainter::Antialiasing);
    if(this->isHover){
        painter->setOpacity(0.8);
    }else if(this->isPressed){
        painter->setOpacity(0.7);
    }

    QRect rect = QRect(((QWidget *)this)->width() - 22, ((QWidget *)this)->height() / 2 - 5 + this->arrowAni->y(), 10, 10);
    this->_drawDropDownIcon(painter, rect);
    painter->end();
}


void PrimaryDropDownPushButton::setMenu(RoundMenu *menu)
{
    this->_menu = menu;
}

RoundMenu *PrimaryDropDownPushButton::menu()
{
    return this->_menu;
}

void PrimaryDropDownPushButton::_showMenu()
{
    if(!this->menu()){
        return;
    }

    RoundMenu *menu = this->menu();
    menu->view->setMinimumWidth(this->width());
    menu->view->adjustSize(nullptr, MenuAnimationType::NONE);
    menu->adjustSize();

    int x = -menu->width() / 2 + menu->layout()->contentsMargins().left() + this->width() / 2;
    QPoint pd = this->mapToGlobal(QPoint(x, this->height()));
    int hd = menu->view->heightForAnimation(&pd, MenuAnimationType::DROP_DOWN);

    QPoint pu = this->mapToGlobal(QPoint(x, 0));
    int hu = menu->view->heightForAnimation(&pu, MenuAnimationType::PULL_UP);

    if(hd >= hu){
        menu->view->adjustSize(&pd, MenuAnimationType::DROP_DOWN);
        menu->exec(&pd, true, MenuAnimationType::DROP_DOWN);
    }else{
        menu->view->adjustSize(&pu, MenuAnimationType::PULL_UP);
        menu->exec(&pu, true, MenuAnimationType::PULL_UP);
    }
}

void PrimaryDropDownPushButton::_hideMenu()
{
    if(this->menu())
        this->menu()->hide();
}

void PrimaryDropDownPushButton::_drawDropDownIcon(QPainter *painter, QRect rect)
{
    Theme theme = !isDarkTheme() ? Theme::DARK : Theme::LIGHT;
    FluentIcon *icon = new FluentIcon();
    icon->setIconName(QString("ARROW_DOWN"));
    icon->render(painter, rect, theme, 0, nullptr);
}


////////////////////////////////////////////////////////
void PrimaryDropDownToolButton::mouseReleaseEvent(QMouseEvent *e)
{
    PrimaryToolButton::mouseReleaseEvent(e);
    this->_showMenu();
}

void PrimaryDropDownToolButton::paintEvent(QPaintEvent *event)
{
    PrimaryToolButton::paintEvent(event);
    QPainter *painter = new QPainter((QWidget *)this);
    painter->setRenderHints(QPainter::Antialiasing);
    if(this->isHover){
        painter->setOpacity(0.8);
    }else if(this->isPressed){
        painter->setOpacity(0.7);
    }

    QRect rect = QRect(((QWidget *)this)->width() - 22, ((QWidget *)this)->height() / 2 - 5 + this->arrowAni->y(), 10, 10);
    this->_drawDropDownIcon(painter, rect);
    painter->end();
}


void PrimaryDropDownToolButton::setMenu(RoundMenu *menu)
{
    this->_menu = menu;
}

RoundMenu *PrimaryDropDownToolButton::menu()
{
    return this->_menu;
}

void PrimaryDropDownToolButton::_showMenu()
{
    if(!this->menu()){
        return;
    }

    RoundMenu *menu = this->menu();
    menu->view->setMinimumWidth(this->width());
    menu->view->adjustSize(nullptr, MenuAnimationType::NONE);
    menu->adjustSize();

    int x = -menu->width() / 2 + menu->layout()->contentsMargins().left() + this->width() / 2;
    QPoint pd = this->mapToGlobal(QPoint(x, this->height()));
    int hd = menu->view->heightForAnimation(&pd, MenuAnimationType::DROP_DOWN);

    QPoint pu = this->mapToGlobal(QPoint(x, 0));
    int hu = menu->view->heightForAnimation(&pu, MenuAnimationType::PULL_UP);

    if(hd >= hu){
        menu->view->adjustSize(&pd, MenuAnimationType::DROP_DOWN);
        menu->exec(&pd, true, MenuAnimationType::DROP_DOWN);
    }else{
        menu->view->adjustSize(&pu, MenuAnimationType::PULL_UP);
        menu->exec(&pu, true, MenuAnimationType::PULL_UP);
    }
}

void PrimaryDropDownToolButton::_hideMenu()
{
    if(this->menu())
        this->menu()->hide();
}

void PrimaryDropDownToolButton::_drawDropDownIcon(QPainter *painter, QRect rect)
{
    Theme theme = !isDarkTheme() ? Theme::DARK : Theme::LIGHT;
    FluentIcon *icon = new FluentIcon();
    icon->setIconName(QString("ARROW_DOWN"));
    icon->render(painter, rect, theme, 0, nullptr);
}


void PrimaryDropDownToolButton::_drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state)
{
    QRect *r = new QRect(rect);
    r->moveLeft(12);
    return PrimaryToolButton::_drawIcon(icon, painter, *r);
}


void SplitDropButton::_postInit()
{
    this->arrowAni = new TranslateYAnimation(this, 2);
    FluentIcon *icon = new FluentIcon();
    icon->setIconName(QString("ARROW_DOWN"));
    QVariant __icon = QVariant::fromValue<FluentIcon>(*icon);
    this->setIcon(&__icon);
}

void SplitDropButton::_drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state)
{
    rect.translate(0, this->arrowAni->y());
    if(this->isPressed){
        painter->setOpacity(0.5);
    }else if(this->isHover){
        painter->setOpacity(1);
    }else{
        painter->setOpacity(0.63);
    }
    ToolButton::_drawIcon(icon, painter, rect);
}



/////////////////////////////////////////////////

////////////////////////////////////////////////////////
void PrimarySplitDropButton::mouseReleaseEvent(QMouseEvent *e)
{
    PrimaryToolButton::mouseReleaseEvent(e);
    this->_showMenu();
}

void PrimarySplitDropButton::paintEvent(QPaintEvent *event)
{
    PrimaryToolButton::paintEvent(event);
    QPainter *painter = new QPainter((QWidget *)this);
    painter->setRenderHints(QPainter::Antialiasing);
    if(this->isHover){
        painter->setOpacity(0.8);
    }else if(this->isPressed){
        painter->setOpacity(0.7);
    }

    QRect rect = QRect(((QWidget *)this)->width() - 22, ((QWidget *)this)->height() / 2 - 5 + this->arrowAni->y(), 10, 10);
    this->_drawDropDownIcon(painter, rect);
    painter->end();
}


void PrimarySplitDropButton::setMenu(RoundMenu *menu)
{
    this->_menu = menu;
}

RoundMenu *PrimarySplitDropButton::menu()
{
    return this->_menu;
}

void PrimarySplitDropButton::_showMenu()
{
    if(!this->menu()){
        return;
    }

    RoundMenu *menu = this->menu();
    menu->view->setMinimumWidth(this->width());
    menu->view->adjustSize(nullptr, MenuAnimationType::NONE);
    menu->adjustSize();

    int x = -menu->width() / 2 + menu->layout()->contentsMargins().left() + this->width() / 2;
    QPoint pd = this->mapToGlobal(QPoint(x, this->height()));
    int hd = menu->view->heightForAnimation(&pd, MenuAnimationType::DROP_DOWN);

    QPoint pu = this->mapToGlobal(QPoint(x, 0));
    int hu = menu->view->heightForAnimation(&pu, MenuAnimationType::PULL_UP);

    if(hd >= hu){
        menu->view->adjustSize(&pd, MenuAnimationType::DROP_DOWN);
        menu->exec(&pd, true, MenuAnimationType::DROP_DOWN);
    }else{
        menu->view->adjustSize(&pu, MenuAnimationType::PULL_UP);
        menu->exec(&pu, true, MenuAnimationType::PULL_UP);
    }
}

void PrimarySplitDropButton::_hideMenu()
{
    if(this->menu())
        this->menu()->hide();
}

void PrimarySplitDropButton::_drawDropDownIcon(QPainter *painter, QRect rect)
{
    Theme theme = !isDarkTheme() ? Theme::DARK : Theme::LIGHT;
    FluentIcon *icon = new FluentIcon();
    icon->setIconName(QString("ARROW_DOWN"));
    icon->render(painter, rect, theme, 0, nullptr);
}


void PrimarySplitDropButton::_drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state)
{
    rect.translate(0, this->arrowAni->y());
    if(this->isPressed){
        painter->setOpacity(0.7);
    }else if(this->isHover){
        painter->setOpacity(0.9);
    }else{
        painter->setOpacity(1);
    }

    QVariant *__icon;
    if(icon->canConvert<FluentIcon>()){
        QIcon *temp_icon = icon->value<FluentIcon>().icon(!isDarkTheme() ? Theme::DARK : Theme::LIGHT, nullptr);
        __icon == new QVariant(QVariant::fromValue<QIcon>(*temp_icon));
    }else{
        __icon = icon;
    }

    PrimaryToolButton::_drawIcon(__icon, painter, rect);
}

void PrimarySplitDropButton::_postInit()
{
    this->arrowAni = new TranslateYAnimation(this, 2);
    FluentIcon *icon = new FluentIcon();
    icon->setIconName(QString("ARROW_DOWN"));
    QVariant __icon = QVariant::fromValue<FluentIcon>(*icon);
    this->setIcon(&__icon);
    this->setIconSize(QSize(10, 10));
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
}


SplitWidgetBase::SplitWidgetBase(QWidget *parent) : QWidget(parent)
{
    
    this->flyout = nullptr;
    this->dropButton = new SplitDropButton(this);

    this->hBoxLayout = new QHBoxLayout(this);
    this->hBoxLayout->setSpacing(0);
    this->hBoxLayout->setContentsMargins(0, 0, 0, 0);
    this->hBoxLayout->addWidget(this->dropButton);

    connect(this->dropButton, &SplitDropButton::clicked, this, &SplitWidgetBase::dropDownClicked);
    connect(this->dropButton, &SplitDropButton::clicked, this, &SplitWidgetBase::showFlyout);

    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    
}

void SplitWidgetBase::setWidget(QWidget *widget)
{
    this->hBoxLayout->insertWidget(0, widget, 1, Qt::AlignLeft);
}

void SplitWidgetBase::setDropButton(SplitDropButton *button)
{
    this->hBoxLayout->removeWidget(this->dropButton);
    this->dropButton->deleteLater();

    this->dropButton = button;
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->hBoxLayout->addWidget(button);
}

void SplitWidgetBase::setDropIcon(QVariant *icon)
{
    this->dropButton->setIcon(icon);
    this->dropButton->removeEventFilter(this->dropButton->arrowAni);
}

void SplitWidgetBase::setDropIconSize(QSize *size)
{
    this->dropButton->setIconSize(*size);
    //this->dropButton->adjustSize();
}

void SplitWidgetBase::setFlyout(QWidget *flyout)
{
    this->flyout = flyout;
}

void SplitWidgetBase::showFlyout()
{
    if(this->flyout == nullptr){
        return;
    }

    QWidget *w = this->flyout;
    RoundMenu *_w = qobject_cast<RoundMenu *>(w);
    if(_w != nullptr){
        _w->view->setMinimumWidth(this->width());
        _w->view->adjustSize(nullptr, MenuAnimationType::NONE);
        _w->adjustSize();

        int dx = _w->layout()->contentsMargins().left();
        int x = -_w->width() / 2 + dx + this->width() /2;
        int y = this->height();
        QPoint point = this->mapToGlobal(QPoint(x, y));
        _w->exec(&point, true, MenuAnimationType::DROP_DOWN);
    }else{
        int dx = 0;
        int x = -w->width() / 2 + dx + this->width() /2;
        int y = this->height();
        QPoint point = this->mapToGlobal(QPoint(x, y));
        _w->exec(&point, true, MenuAnimationType::DROP_DOWN);
    }

}


SplitPushButton::SplitPushButton(QWidget *parent) : SplitWidgetBase(parent)
{
    this->button = new PushButton(this);
    this->button->setObjectName(QString("splitPushButton"));
    connect(this->button, &PushButton::clicked, this, &SplitPushButton::clicked);
    this->setWidget(this->button);
    this->_postInit();
}

SplitPushButton::SplitPushButton(QString text, QWidget *parent, QVariant *icon) : SplitWidgetBase(parent)
{
    this->button = new PushButton(this);
    this->button->setObjectName(QString("splitPushButton"));
    connect(this->button, &PushButton::clicked, this, &SplitPushButton::clicked);
    this->setWidget(this->button);
    this->_postInit();
    this->setText(text);
    this->setIcon(icon);
}

SplitPushButton::SplitPushButton(QIcon *icon, QString text, QWidget *parent) : SplitWidgetBase(parent)
{
    this->button = new PushButton(this);
    this->button->setObjectName(QString("splitPushButton"));
    connect(this->button, &PushButton::clicked, this, &SplitPushButton::clicked);
    this->setWidget(this->button);
    this->_postInit();
    this->setText(text);
    QVariant _icon = QVariant::fromValue<QIcon>(*icon);
    this->setIcon(&_icon);
}

SplitPushButton::SplitPushButton(FluentIcon *icon, QString text, QWidget *parent) : SplitWidgetBase(parent)
{
    this->button = new PushButton(this);
    this->button->setObjectName(QString("splitPushButton"));
    connect(this->button, &PushButton::clicked, this, &SplitPushButton::clicked);
    this->setWidget(this->button);
    this->_postInit();
    this->setText(text);
    QVariant _icon = QVariant::fromValue<FluentIcon>(*icon);
    this->setIcon(&_icon);
}


QString SplitPushButton::text(){
    return this->button->text();
}

void SplitPushButton::setText(QString text)
{
    this->button->setText(text);
    this->adjustSize();
}

QIcon *SplitPushButton::icon()
{
    QIcon icon = this->button->icon();
    return &icon;
}

void SplitPushButton::setIcon(QVariant *icon)
{
    this->button->setIcon(icon);
}

void SplitPushButton::setIconSize(QSize *size)
{
    this->button->setIconSize(*size);
}




//////////////////////////////////////////////////////////////////////////////////
SplitWidgetBase2PrimaryButton::SplitWidgetBase2PrimaryButton(QWidget *parent) : QWidget(parent)
{
    
    this->flyout = nullptr;
    this->dropButton = new PrimarySplitDropButton(this);

    this->hBoxLayout = new QHBoxLayout(this);
    this->hBoxLayout->setSpacing(0);
    this->hBoxLayout->setContentsMargins(0, 0, 0, 0);
    this->hBoxLayout->addWidget(this->dropButton);

    connect(this->dropButton, &PrimarySplitDropButton::clicked, this, &SplitWidgetBase2PrimaryButton::dropDownClicked);
    connect(this->dropButton, &PrimarySplitDropButton::clicked, this, &SplitWidgetBase2PrimaryButton::showFlyout);

    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    
}

void SplitWidgetBase2PrimaryButton::setWidget(QWidget *widget)
{
    this->hBoxLayout->insertWidget(0, widget, 1, Qt::AlignLeft);
}

void SplitWidgetBase2PrimaryButton::setDropButton(PrimarySplitDropButton *button)
{
    this->hBoxLayout->removeWidget(this->dropButton);
    this->dropButton->deleteLater();

    this->dropButton = button;
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->hBoxLayout->addWidget(button);
}

void SplitWidgetBase2PrimaryButton::setDropIcon(QVariant *icon)
{
    this->dropButton->setIcon(icon);
    this->dropButton->removeEventFilter(this->dropButton->arrowAni);
}

void SplitWidgetBase2PrimaryButton::setDropIconSize(QSize *size)
{
    this->dropButton->setIconSize(*size);
    //this->dropButton->adjustSize();
}

void SplitWidgetBase2PrimaryButton::setFlyout(QWidget *flyout)
{
    this->flyout = flyout;
}

void SplitWidgetBase2PrimaryButton::showFlyout()
{
    if(this->flyout == nullptr){
        return;
    }

    QWidget *w = this->flyout;
    RoundMenu *_w = qobject_cast<RoundMenu *>(w);
    if(_w != nullptr){
        _w->view->setMinimumWidth(this->width());
        _w->view->adjustSize(nullptr, MenuAnimationType::NONE);
        _w->adjustSize();

        int dx = _w->layout()->contentsMargins().left();
        int x = -_w->width() / 2 + dx + this->width() /2;
        int y = this->height();
        QPoint point = this->mapToGlobal(QPoint(x, y));
        _w->exec(&point, true, MenuAnimationType::DROP_DOWN);
    }else{
        int dx = 0;
        int x = -w->width() / 2 + dx + this->width() /2;
        int y = this->height();
        QPoint point = this->mapToGlobal(QPoint(x, y));
        _w->exec(&point, true, MenuAnimationType::DROP_DOWN);
    }

}



PrimarySplitPushButton::PrimarySplitPushButton(QWidget *parent) : SplitWidgetBase2PrimaryButton(parent)
{
    this->button = new PrimaryPushButton(this);
    this->button->setObjectName(QString("primarySplitPushButton"));
    connect(this->button, &PushButton::clicked, this, &PrimarySplitPushButton::clicked);
    this->setWidget(this->button);
    this->_postInit();
}

PrimarySplitPushButton::PrimarySplitPushButton(QString text, QWidget *parent, QVariant *icon) : SplitWidgetBase2PrimaryButton(parent)
{
    this->button = new PrimaryPushButton(this);
    this->button->setObjectName(QString("primarySplitPushButton"));
    connect(this->button, &PushButton::clicked, this, &PrimarySplitPushButton::clicked);
    this->setWidget(this->button);
    this->_postInit();
    this->setText(text);
    this->setIcon(icon);
}

PrimarySplitPushButton::PrimarySplitPushButton(QIcon *icon, QString text, QWidget *parent) : SplitWidgetBase2PrimaryButton(parent)
{
    this->button = new PrimaryPushButton(this);
    this->button->setObjectName(QString("primarySplitPushButton"));
    connect(this->button, &PushButton::clicked, this, &PrimarySplitPushButton::clicked);
    this->setWidget(this->button);
    this->_postInit();
    this->setText(text);
    QVariant _icon = QVariant::fromValue<QIcon>(*icon);
    this->setIcon(&_icon);
}

PrimarySplitPushButton::PrimarySplitPushButton(FluentIcon *icon, QString text, QWidget *parent) : SplitWidgetBase2PrimaryButton(parent)
{
    this->button = new PrimaryPushButton(this);
    this->button->setObjectName(QString("primarySplitPushButton"));
    connect(this->button, &PushButton::clicked, this, &PrimarySplitPushButton::clicked);
    this->setWidget(this->button);
    this->_postInit();
    this->setText(text);
    QVariant _icon = QVariant::fromValue<FluentIcon>(*icon);
    this->setIcon(&_icon);
}


QString PrimarySplitPushButton::text(){
    return this->button->text();
}

void PrimarySplitPushButton::setText(QString text)
{
    this->button->setText(text);
    this->adjustSize();
}

QIcon *PrimarySplitPushButton::icon()
{
    QIcon icon = this->button->icon();
    return &icon;
}

void PrimarySplitPushButton::setIcon(QVariant *icon)
{
    this->button->setIcon(icon);
}

void PrimarySplitPushButton::setIconSize(QSize *size)
{
    this->button->setIconSize(*size);
}

///////////////////////////////////////////////////////////
SplitToolButton::SplitToolButton(QWidget *parent) : SplitWidgetBase(parent)
{
    this->button = new ToolButton(this);
    this->button->setObjectName(QString("splitToolButton"));
    connect(this->button, &ToolButton::clicked, this, &SplitToolButton::clicked);
    this->setWidget(this->button);
    this->_postInit();
}

SplitToolButton::SplitToolButton(QWidget *parent, QVariant *icon) : SplitWidgetBase(parent)
{
    this->button = new ToolButton(this);
    this->button->setObjectName(QString("splitToolButton"));
    connect(this->button, &ToolButton::clicked, this, &SplitToolButton::clicked);
    this->setWidget(this->button);
    this->_postInit();
    this->setIcon(icon);
}

SplitToolButton::SplitToolButton(QIcon *icon, QWidget *parent) : SplitWidgetBase(parent)
{
    this->button = new ToolButton(this);
    this->button->setObjectName(QString("splitToolButton"));
    connect(this->button, &ToolButton::clicked, this, &SplitToolButton::clicked);
    this->setWidget(this->button);
    this->_postInit();
    QVariant _icon = QVariant::fromValue<QIcon>(*icon);
    this->setIcon(&_icon);
}

SplitToolButton::SplitToolButton(FluentIcon *icon, QWidget *parent) : SplitWidgetBase(parent)
{
    this->button = new ToolButton(this);
    this->button->setObjectName(QString("splitToolButton"));
    connect(this->button, &ToolButton::clicked, this, &SplitToolButton::clicked);
    this->setWidget(this->button);
    QVariant _icon = QVariant::fromValue<FluentIcon>(*icon);
    this->setIcon(&_icon);
}


QString SplitToolButton::text(){
    return this->button->text();
}

void SplitToolButton::setText(QString text)
{
    this->button->setText(text);
    this->adjustSize();
}

QIcon *SplitToolButton::icon()
{
    QIcon icon = this->button->icon();
    return &icon;
}

void SplitToolButton::setIcon(QVariant *icon)
{
    this->button->setIcon(icon);
}

void SplitToolButton::setIconSize(QSize *size)
{
    this->button->setIconSize(*size);
}


///////////////////////////////////////////////////////////
PrimarySplitToolButton::PrimarySplitToolButton(QWidget *parent) : SplitWidgetBase2PrimaryButton(parent)
{
    this->button = new PrimaryToolButton(this);
    this->button->setObjectName(QString("primarySplitToolButton"));
    connect(this->button, &ToolButton::clicked, this, &PrimarySplitToolButton::clicked);
    this->setWidget(this->button);
    this->_postInit();
}

PrimarySplitToolButton::PrimarySplitToolButton(QWidget *parent, QVariant *icon) : SplitWidgetBase2PrimaryButton(parent)
{
    this->button = new PrimaryToolButton(this);
    this->button->setObjectName(QString("primarySplitToolButton"));
    connect(this->button, &ToolButton::clicked, this, &PrimarySplitToolButton::clicked);
    this->setWidget(this->button);
    this->_postInit();
    this->setIcon(icon);
}

PrimarySplitToolButton::PrimarySplitToolButton(QIcon *icon, QWidget *parent) : SplitWidgetBase2PrimaryButton(parent)
{
    this->button = new PrimaryToolButton(this);
    this->button->setObjectName(QString("primarySplitToolButton"));
    connect(this->button, &ToolButton::clicked, this, &PrimarySplitToolButton::clicked);
    this->setWidget(this->button);
    this->_postInit();
    QVariant _icon = QVariant::fromValue<QIcon>(*icon);
    this->setIcon(&_icon);
}

PrimarySplitToolButton::PrimarySplitToolButton(FluentIcon *icon, QWidget *parent) : SplitWidgetBase2PrimaryButton(parent)
{
    this->button = new PrimaryToolButton(this);
    this->button->setObjectName(QString("primarySplitToolButton"));
    connect(this->button, &ToolButton::clicked, this, &PrimarySplitToolButton::clicked);
    this->setWidget(this->button);
    QVariant _icon = QVariant::fromValue<FluentIcon>(*icon);
    this->setIcon(&_icon);
}


QString PrimarySplitToolButton::text(){
    return this->button->text();
}

void PrimarySplitToolButton::setText(QString text)
{
    this->button->setText(text);
    this->adjustSize();
}

QIcon *PrimarySplitToolButton::icon()
{
    QIcon icon = this->button->icon();
    return &icon;
}

void PrimarySplitToolButton::setIcon(QVariant *icon)
{
    this->button->setIcon(icon);
}

void PrimarySplitToolButton::setIconSize(QSize *size)
{
    this->button->setIconSize(*size);
}

