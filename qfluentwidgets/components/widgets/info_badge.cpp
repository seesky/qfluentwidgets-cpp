#include "info_badge.h"

InfoBadge::InfoBadge(QWidget *parent, QString level) : QLabel(parent)
{
    this->level = InfoLevel.value(QString("INFOAMTION"));
    this->lightBackgroundColor = QColor();
    this->darkBackgroundColor = QColor();
    this->manager = nullptr;
    this->setLevel(level);

    Font().setFont(this, 11, QFont::Normal);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("INFO_BADGE"), Theme::AUTO);
}

InfoBadge::InfoBadge(QString text, QWidget *parent, QString level) : QLabel(parent)
{
    this->level = InfoLevel.value(QString("INFOAMTION"));
    this->lightBackgroundColor = QColor();
    this->darkBackgroundColor = QColor();
    this->manager = nullptr;
    this->setLevel(level);

    Font().setFont(this, 11, QFont::Normal);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("INFO_BADGE"), Theme::AUTO);
    this->setText(text);
}

InfoBadge::InfoBadge(int num, QWidget *parent, QString level) : QLabel(parent)
{
    this->level = InfoLevel.value(QString("INFOAMTION"));
    this->lightBackgroundColor = QColor();
    this->darkBackgroundColor = QColor();
    this->manager = nullptr;
    this->setLevel(level);

    Font().setFont(this, 11, QFont::Normal);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("INFO_BADGE"), Theme::AUTO);
    this->setNum(num);
}

InfoBadge::InfoBadge(float num, QWidget *parent, QString level) : QLabel(parent)
{
    this->level = InfoLevel.value(QString("INFOAMTION"));
    this->lightBackgroundColor = QColor();
    this->darkBackgroundColor = QColor();
    this->manager = nullptr;
    this->setLevel(level);

    Font().setFont(this, 11, QFont::Normal);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("INFO_BADGE"), Theme::AUTO);
    this->setNum(num);
}

void InfoBadge::setLevel(QString level)
{
    if(level == this->level){
        return;
    }

    this->level = level;
    this->setProperty("level", new QVariant(QVariant::fromValue<QString>(level))); //TODO:关注是否能设置正确的值
    this->update();
}

void InfoBadge::setProperty(const char *name, QVariant *value)
{
    QLabel::setProperty(name, *value);
    if(QString(name) != QString("level")){
        return;
    }

    QMap<QString, QString>::const_iterator it;
    for (it = InfoLevel.begin(); it != InfoLevel.end(); ++it){ //TODO:特殊关注
        if(value->value<QString>() == it.value()){
            this->level = it.value();
        }
    }
}


void InfoBadge::setCustomBackgroundColor(QVariant *light, QVariant *dark)
{
    if(light->canConvert<QColor>() && dark->canConvert<QColor>()){
        this->lightBackgroundColor = QColor(light->value<QColor>());
        this->darkBackgroundColor = QColor(dark->value<QColor>());
    }else if(light->canConvert<QString>() && dark->canConvert<QString>()){
        qDebug() << light->value<QString>();
        this->lightBackgroundColor = QColor(light->value<QString>());
        this->darkBackgroundColor = QColor(dark->value<QString>());
    }
    this->update();
}


void InfoBadge::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(this->_backgroundColor());

    float r = float(this->height()) / 2; //TODO:确定是否为0

    painter.drawRoundedRect(this->rect(), r, r);
    QLabel::paintEvent(e);
}

QColor InfoBadge::_backgroundColor()
{
    bool isDark = isDarkTheme();

    
    QColor _color;
    if(this->lightBackgroundColor.isValid()){
        _color = isDark ? this->darkBackgroundColor : this->lightBackgroundColor;
    }else if(this->level == InfoLevel.value(QString("INFOAMTION"))){
        _color = isDark ? QColor(157, 157, 157) : QColor(138, 138, 138);
    }else if(this->level == InfoLevel.value(QString("SUCCESS"))){
        _color = isDark ? QColor(108, 203, 95) : QColor(15, 123, 15);
    }else if(this->level == InfoLevel.value(QString("ATTENTION"))){
        _color = *(ThemeColor().themeColor());
    }else if(this->level == InfoLevel.value(QString("WARNING"))){
        _color = isDark ? QColor(255, 244, 206) : QColor(157, 93, 0);
    }else{
        _color = isDark ? QColor(255, 153, 164) : QColor(196, 43, 28);
    }

    return _color;
    
}


InfoBadge* InfoBadge::make(QVariant *text, QWidget *parent, QString level, QWidget *target, InfoBadgePosition position)
{
    InfoBadge *w;
    if(text->canConvert<QString>()){
        qDebug() << text->value<QString>();
        w = new InfoBadge(text->value<QString>(), parent, level);
    }else if(text->canConvert<int>()){
        w = new InfoBadge(text->value<int>(), parent, level);
    }else if(text->canConvert<float>()){
        w = new InfoBadge(text->value<float>(), parent, level);
    }

    w->adjustSize();

    if(target != nullptr){
        w->manager = InfoBadgeManager::make(position, target, w);
        w->move(w->manager->position());
    }
    
    return w;
}


InfoBadge* InfoBadge::info(QVariant *text, QWidget *parent = nullptr, QWidget *target = nullptr, InfoBadgePosition postion = InfoBadgePosition::TOP_RIGHT)
{
    qDebug() << text->typeName();
    return InfoBadge::make(text, parent, InfoLevel.value(QString("INFOAMTION")), target, postion);   
}

InfoBadge* InfoBadge::success(QVariant *text, QWidget *parent = nullptr, QWidget *target = nullptr, InfoBadgePosition postion = InfoBadgePosition::TOP_RIGHT)
{
    return InfoBadge::make(text, parent, InfoLevel.value(QString("SUCCESS")), target, postion);
}


InfoBadge* InfoBadge::attension(QVariant *text, QWidget *parent = nullptr, QWidget *target = nullptr, InfoBadgePosition postion = InfoBadgePosition::TOP_RIGHT)
{
    return InfoBadge::make(text, parent, InfoLevel.value(QString("ATTENTION")), target, postion);
}


InfoBadge* InfoBadge::warning(QVariant *text, QWidget *parent = nullptr, QWidget *target = nullptr, InfoBadgePosition postion = InfoBadgePosition::TOP_RIGHT)
{
    return InfoBadge::make(text, parent, InfoLevel.value(QString("WARNING")), target, postion);
}

InfoBadge* InfoBadge::error(QVariant *text, QWidget *parent = nullptr, QWidget *target = nullptr, InfoBadgePosition postion = InfoBadgePosition::TOP_RIGHT)
{
    return InfoBadge::make(text, parent, InfoLevel.value(QString("ERROR")), target, postion);
}

InfoBadge* InfoBadge::custom(QVariant *text, QColor light, QColor dark, QWidget *parent, QWidget *target, InfoBadgePosition postion)
{
    qDebug() << light.isValid();
    qDebug() << dark.isValid();
    InfoBadge* w = InfoBadge::make(text, parent, InfoLevel.value(QString("INFOAMTION")), target, postion);
    w->setCustomBackgroundColor(new QVariant(QVariant::fromValue<QColor>(light)), new QVariant(QVariant::fromValue<QColor>(dark)));
    return w;
}


DotInfoBadge::DotInfoBadge(QWidget *parent, QString level) : InfoBadge(parent, level)
{
    this->setFixedSize(4, 4);
}

void DotInfoBadge::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(this->_backgroundColor());
    painter.drawEllipse(this->rect());
}

DotInfoBadge* DotInfoBadge::make(QWidget *parent, QString level, QWidget *target, InfoBadgePosition position)
{
    DotInfoBadge *w = new DotInfoBadge(parent, level);

    if(target != nullptr){
        w->manager = InfoBadgeManager::make(position, target, w);
        w->move(w->manager->position());
    }

    return w;
}


DotInfoBadge* DotInfoBadge::info(QWidget *parent, QWidget *target, InfoBadgePosition position)
{
    return DotInfoBadge::make(parent, InfoLevel.value(QString("INFOAMTION")), target, position);
}

DotInfoBadge* DotInfoBadge::success(QWidget *parent, QWidget *target, InfoBadgePosition position)
{
    return DotInfoBadge::make(parent, InfoLevel.value(QString("SUCCESS")), target, position);
}


DotInfoBadge* DotInfoBadge::attension(QWidget *parent, QWidget *target, InfoBadgePosition position)
{
    return DotInfoBadge::make(parent, InfoLevel.value(QString("ATTENTION")), target, position);
}


DotInfoBadge* DotInfoBadge::warning(QWidget *parent, QWidget *target, InfoBadgePosition position)
{
    return DotInfoBadge::make(parent, InfoLevel.value(QString("WARNING")), target, position);
}


DotInfoBadge* DotInfoBadge::error(QWidget *parent, QWidget *target, InfoBadgePosition position)
{
    return DotInfoBadge::make(parent, InfoLevel.value(QString("ERROR")), target, position);
}



DotInfoBadge* DotInfoBadge::custom(QColor light, QColor dark, QWidget *parent, QWidget *target, InfoBadgePosition position)
{
    DotInfoBadge* w = DotInfoBadge::make(parent, InfoLevel.value(QString("INFOAMTION")), target, position);
    w->setCustomBackgroundColor(new QVariant(QVariant::fromValue<QColor>(light)), new QVariant(QVariant::fromValue<QColor>(dark)));
    return w;
}


IconInfoBadge::IconInfoBadge(QWidget *parent, QString level) : InfoBadge(parent, level)
{
    this->_icon = new QVariant(QVariant::fromValue<QIcon>(QIcon()));
    this->_iconSize = QSize(8, 8);
    this->setFixedSize(16, 16);
}

IconInfoBadge::IconInfoBadge(FluentIcon *icon, QWidget *parent, QString level) : InfoBadge(parent, level)
{   
    this->_icon = new QVariant(QVariant::fromValue<QIcon>(QIcon()));
    this->_iconSize = QSize(8, 8);
    this->setFixedSize(16, 16);
    this->setIcon(new QVariant(QVariant::fromValue<FluentIcon>(*icon)));
}

IconInfoBadge::IconInfoBadge(QIcon *icon, QWidget *parent, QString level) : InfoBadge(parent, level)
{
    this->_icon = new QVariant(QVariant::fromValue<QIcon>(QIcon()));
    this->_iconSize = QSize(8, 8);
    this->setFixedSize(16, 16);
    this->setIcon(new QVariant(QVariant::fromValue<QIcon>(*icon)));
}

void IconInfoBadge::setIcon(QVariant *icon)
{
    this->_icon = icon;
    this->update();
}

QIcon IconInfoBadge::icon()
{
    return MIcon().toQIcon(this->_icon);
}

QSize IconInfoBadge::iconSize()
{
    return this->_iconSize;
}

void IconInfoBadge::setIconSize(QSize size)
{
    this->_iconSize = size;
    this->update();
}

void IconInfoBadge::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(this->_backgroundColor());
    painter.drawEllipse(this->rect());

    int iw = this->iconSize().width();
    int ih = this->iconSize().height();
    int x = (this->width() - iw) / 2;
    int y = (this->height() - ih) / 2;
    QRect rect = QRect(x, y, iw, ih);

    if(this->_icon->canConvert<FluentIcon>()){
        Theme theme = !isDarkTheme() ? Theme::DARK : Theme::LIGHT;
        this->_icon->value<FluentIcon>().render(&painter, rect, theme, 0, nullptr);
    }else{
        MIcon().drawIcon(this->_icon, &painter, rect, nullptr, QIcon::State::Off);
    }
}

IconInfoBadge* IconInfoBadge::make(QVariant *icon, QWidget *parent, QString level, QWidget *target, InfoBadgePosition position)
{
    IconInfoBadge *w;
    if(icon->canConvert<FluentIcon>()){
        FluentIcon _icon = icon->value<FluentIcon>();
        w = new IconInfoBadge(&_icon, parent, level);
    }else if(icon->canConvert<QIcon>()){
        QIcon _icon = icon->value<QIcon>();
        w = new IconInfoBadge(&_icon, parent, level);
    }

    if(target != nullptr){
        w->manager = InfoBadgeManager::make(position, target, w);
        w->move(w->manager->position());
    }
    
    return w;
}

IconInfoBadge* IconInfoBadge::info(QVariant *icon, QWidget *parent, QWidget *target, InfoBadgePosition position)
{
    return IconInfoBadge::make(icon, parent, InfoLevel.value(QString("INFOAMTION")), target, position);
}

IconInfoBadge* IconInfoBadge::success(QVariant *icon, QWidget *parent, QWidget *target, InfoBadgePosition position)
{
    return IconInfoBadge::make(icon, parent, InfoLevel.value(QString("SUCCESS")), target, position);
}

IconInfoBadge* IconInfoBadge::attension(QVariant *icon, QWidget *parent, QWidget *target, InfoBadgePosition position)
{
    return IconInfoBadge::make(icon, parent, InfoLevel.value(QString("ATTENTION")), target, position);
}

IconInfoBadge* IconInfoBadge::warning(QVariant *icon, QWidget *parent, QWidget *target, InfoBadgePosition position)
{
    return IconInfoBadge::make(icon, parent, InfoLevel.value(QString("WARNING")), target, position);
}

IconInfoBadge* IconInfoBadge::error(QVariant *icon, QWidget *parent, QWidget *target, InfoBadgePosition position)
{
    return IconInfoBadge::make(icon, parent, InfoLevel.value(QString("ERROR")), target, position);
}

IconInfoBadge* IconInfoBadge::custom(QVariant *icon, QColor light, QColor dark, QWidget *parent, QWidget *target, InfoBadgePosition position)
{
    IconInfoBadge* w = IconInfoBadge::make(icon, parent, InfoLevel.value(QString("INFOAMTION")), target, position);
    w->setCustomBackgroundColor(new QVariant(QVariant::fromValue<QColor>(light)), new QVariant(QVariant::fromValue<QColor>(dark)));
    return w;
}


InfoBadgeManager::InfoBadgeManager(QWidget *target, InfoBadge *badge) : QObject()
{
    this->target = target;
    this->badge = badge;

    this->target->installEventFilter(this);
}

bool InfoBadgeManager::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this->target){
        if(event->type() == QEvent::Resize || event->type() == QEvent::Move){
            this->badge->move(this->position());
        }
    }

    return QObject::eventFilter(watched, event);
}

InfoBadgeManager *InfoBadgeManager::make(InfoBadgePosition postion, QWidget *target, InfoBadge *badge)
{   
    switch (postion)
    {
    case InfoBadgePosition::TOP_RIGHT:
        return new TopRightInfoBadgeManager(target, badge);
        break;
    case InfoBadgePosition::BOTTOM_RIGHT:
        return new BottomRightInfoBadgeManager(target, badge);
        break;
    case InfoBadgePosition::RIGHT:
        return new RightInfoBadgeManager(target, badge);
        break;
    case InfoBadgePosition::TOP_LEFT:
        return new TopLeftInfoBadgeManager(target, badge);
        break;
    case InfoBadgePosition::BOTTOM_LEFT:
        return new BottomLeftInfoBadgeManager(target, badge);
        break;
    case InfoBadgePosition::LEFT:
        return new LeftInfoBadgeManager(target, badge);
        break;
    case InfoBadgePosition::NAVIGATION_ITEM:
        return new NavigationItemInfoBadgeManager(target, badge);
        break;
    default:
        return new TopRightInfoBadgeManager(target, badge);
        break;
    }
}


QPoint InfoBadgeManager::position()
{
    return QPoint();
}


bool NavigationItemInfoBadgeManager::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this->target){
        if(event->type() == QEvent::Show){
            this->badge->show();
        }
    }

    return InfoBadgeManager::eventFilter(watched, event);
}


QPoint NavigationItemInfoBadgeManager::position() //TODO:特殊关注
{   
    QWidget *target = this->target;
    this->badge->setVisible(target->isVisible());

    auto t = qobject_cast<NavigationWidget*>(target);
    if(t->isCompacted){
        return t->geometry().topRight() - QPoint(this->badge->width() + 2, -2);
    }

    int x, y;
    auto ntw = qobject_cast<NavigationTreeWidget*>(target);
    if(ntw != nullptr){
        int dx = ntw->isLeaf() ? 10 : 35;
        x = ntw->geometry().right() - this->badge->width() - dx;
        y = ntw->y() + 18 - this->badge->height() / 2; 
    }else{
        x = target->geometry().right() - this->badge->width() - 10;
        y = target->geometry().center().y() - this->badge->height() / 2;
    }

    return QPoint(x, y);
}



QPoint TopRightInfoBadgeManager::position()
{

    QPoint pos = this->target->geometry().topRight();
    int xx = pos.x();
    int yy = pos.y();
    int x = pos.x() - this->badge->width() / 2;
    int y = pos.y() - this->badge->height() / 2;
    return QPoint(x, y);
}


QPoint RightInfoBadgeManager::position()
{
    int x = this->target->geometry().right() - this->badge->width() / 2;
    int y = this->target->geometry().center().y() - this->badge->height() / 2;
    return QPoint(x, y);
}


QPoint BottomRightInfoBadgeManager::position()
{
    QPoint pos = this->target->geometry().bottomRight();
    int x = pos.x() - this->badge->width() / 2;
    int y = pos.y() - this->badge->height() / 2;
    return QPoint(x, y);
}

QPoint TopLeftInfoBadgeManager::position()
{
    int x = this->target->x() - this->badge->width() / 2;
    int y = this->target->y() - this->badge->height() / 2;
    return QPoint(x, y);
}


QPoint LeftInfoBadgeManager::position()
{
    int x = this->target->x() - this->badge->width() / 2;
    int y = this->target->geometry().center().y() - this->badge->height() / 2;
    return QPoint(x, y);
}


QPoint BottomLeftInfoBadgeManager::position()
{
    QPoint pos = this->target->geometry().bottomLeft();
    int x = pos.x() - this->badge->width() / 2;
    int y = pos.y() - this->badge->height() / 2;
    return QPoint(x, y);
}
