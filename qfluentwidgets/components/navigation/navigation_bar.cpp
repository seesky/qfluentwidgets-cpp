#include "navigation_bar.h"

IconSlideAnimation::IconSlideAnimation(QWidget *parent) : QPropertyAnimation(parent)
{
    this->_offset = 0;
    this->maxOffset = 6;
    this->setTargetObject(this);
    this->setPropertyName("offset");
}


float IconSlideAnimation::getOffset()
{
    return this->_offset;
}


void IconSlideAnimation::setOffset(float value)
{
    this->_offset = value;
    ((QWidget*)this->parent())->update();
}


void IconSlideAnimation::slideDown()
{
    this->setEndValue(this->maxOffset);
    this->setDuration(100);
    this->start();
}


void IconSlideAnimation::slideUp()
{
    this->setEndValue(0);
    this->setDuration(100);
    this->start();
}


NavigationBarPushButton::NavigationBarPushButton(QVariant *icon, QString text, bool isSelectable, QVariant *selectedIcon, QWidget *parent) : NavigationPushButton(icon, text, isSelectable, parent)
{
    this->iconAni = new IconSlideAnimation(this);
    this->_selectedIcon = selectedIcon;
    this->_isSelectedTextVisible = true;

    this->setFixedSize(64, 58);
    Font().setFont(this, 11, QFont::Normal);
}


QIcon NavigationBarPushButton::selectedIcon()
{
    if(this->_selectedIcon){
        return MIcon().toQIcon(this->_selectedIcon);
    }

    return QIcon();
}


void NavigationBarPushButton::setSelectedIcon(QVariant *icon)
{
    this->_selectedIcon = icon;
    this->update();
}


void NavigationBarPushButton::setSelectedTextVisible(bool isVisible)
{
    this->_isSelectedTextVisible = isVisible;
    this->update();
}   

void NavigationBarPushButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
    painter.setPen(Qt::NoPen);

    if(this->isSelected){
        painter.setBrush(isDarkTheme() ? QColor(255, 255, 255, 42) : Qt::white);
        painter.drawRoundedRect(this->rect(), 5, 5);

        painter.setBrush(*(ThemeColor().themeColor()));

        if(!this->isPressed){
            painter.drawRoundedRect(0, 16, 4, 24, 2, 2);
        }else{
            painter.drawRoundedRect(0, 19, 4, 18, 2, 2);
        }

    }else if(this->isPressed || this->isEnter){
        int c = isDarkTheme() ? 255 : 0;
        int alpha = this->isEnter ? 9 : 6;
        painter.setBrush(QColor(c, c, c, alpha));
        painter.drawRoundedRect(this->rect(), 5, 5);
    }

    if((this->isPressed || !this->isEnter) && !this->isSelected){
        painter.setOpacity(0.6);
    }

    if(!this->isEnabled()){
        painter.setOpacity(0.4);
    }


    QRect rect;
    if(this->_isSelectedTextVisible){
        rect = QRect(22, 13, 20, 20);
    }else{
        rect = QRect(22, 13 + this->iconAni->getOffset(), 20, 20);
    }

    QVariant *selectedIcon;
    if(this->_selectedIcon->isValid()){
        selectedIcon = this->_selectedIcon;
    }else if(this->_icon->isValid()){
        selectedIcon = this->_icon;
    }

    if(selectedIcon->canConvert<FluentIcon>() && this->isSelected){
        std::map<QString, QString> attributes;
        attributes[QString("fill")] = ThemeColor().themeColor()->name();
        selectedIcon->value<FluentIcon>().render(&painter, rect, Theme::AUTO, 0, &attributes);
    }else if(this->isSelected){
        MIcon().drawIcon(selectedIcon, &painter, rect, nullptr, QIcon::State::Off);
    }else{
        MIcon().drawIcon(this->_icon, &painter, rect, nullptr, QIcon::State::Off);
    }

    if(this->isSelected){
        painter.setPen(*(ThemeColor().themeColor()));
    }else{
        painter.setPen(isDarkTheme() ? Qt::white : Qt::black);
    }

    painter.setFont(this->font());

    rect = QRect(0, 32, this->width(), 26);
    painter.drawText(rect, Qt::AlignCenter, this->text());
}


void NavigationBarPushButton::setSelected(bool isSelected)
{
    if(isSelected == this->isSelected){
        return;
    }

    this->isSelected = isSelected;

    if(isSelected){
        this->iconAni->slideDown();
    }else{
        this->iconAni->slideUp();
    }
}


NavigationBar::NavigationBar(QWidget *parent) : QWidget(parent)
{
    this->scrollArea = new SingleDirectionScrollArea(this, Qt::Vertical);
    this->scrollWidget = new QWidget();

    this->vBoxLayout = new QVBoxLayout(this);
    this->topLayout = new QVBoxLayout();
    this->bottomLayout = new QVBoxLayout();
    this->scrollLayout = new QVBoxLayout(this->scrollWidget);

    this->items = QMap<QString, NavigationWidget*>();
    this->history = qrouter;

    this->__initWidget();
}


void NavigationBar::__initWidget()
{
    this->resize(48, this->height());
    this->setAttribute(Qt::WA_StyledBackground);
    this->window()->installEventFilter(this);

    this->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->scrollArea->setWidget(this->scrollWidget);
    this->scrollArea->setWidgetResizable(true);

    this->scrollWidget->setObjectName(QString("scrollWidget"));
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("NAVIGATION_INTERFACE"), Theme::AUTO);
    FluentStyleSheet().apply(this->scrollWidget, FluentStyleSheetMap.value("NAVIGATION_INTERFACE"), Theme::AUTO);
    this->__initLayout();
}

void NavigationBar::__initLayout()
{
    this->vBoxLayout->setContentsMargins(0, 5, 0, 5);
    this->topLayout->setContentsMargins(4, 0, 4, 0);
    this->bottomLayout->setContentsMargins(4, 0, 4, 0);
    this->scrollLayout->setContentsMargins(4, 0, 4, 0);
    this->vBoxLayout->setSpacing(4);
    this->topLayout->setSpacing(4);
    this->bottomLayout->setSpacing(4);
    this->scrollLayout->setSpacing(4);

    this->vBoxLayout->addLayout(this->topLayout, 0);
    this->vBoxLayout->addWidget(this->scrollArea);
    this->vBoxLayout->addLayout(this->bottomLayout, 0);

    this->vBoxLayout->setAlignment(Qt::AlignTop);
    this->topLayout->setAlignment(Qt::AlignTop);
    this->scrollLayout->setAlignment(Qt::AlignTop);
    this->bottomLayout->setAlignment(Qt::AlignBottom);
}


NavigationWidget *NavigationBar::widget(QString routeKey)
{
    if(!this->items.contains(routeKey)){
        //throw std::invalid_argument(QString("%1 is illegal.").arg(routeKey));
        return nullptr;
    }

    return this->items[routeKey];
}


NavigationBarPushButton *NavigationBar::addItem(QString routeKey, QVariant *icon, QString text, std::function<void()> onClick, bool selectable, QVariant *selectedIcon, NavigationItemPosition position)
{
    return this->insertItem(-1, routeKey, icon, text, onClick, selectable, selectedIcon, position);
}


void NavigationBar::addWidget(QString routeKey, NavigationWidget *widget, std::function<void()> onClick, NavigationItemPosition position)
{
    this->insertWidget(-1, routeKey, widget, onClick, position);
}

NavigationBarPushButton *NavigationBar::insertItem(int index, QString routeKey, QVariant *icon, QString text, std::function<void()> onClick, bool selectable, QVariant *selectedIcon, NavigationItemPosition position)
{
    if(this->items.contains(routeKey)){
        return nullptr;
    }

    NavigationBarPushButton *w = new NavigationBarPushButton(icon, text, selectable, selectedIcon, this);
    this->insertWidget(index, routeKey, w, onClick, position);
    return w;
}


void NavigationBar::insertWidget(int index, QString routeKey, NavigationWidget *widget, std::function<void()> onClick, NavigationItemPosition position)
{
    if(this->items.contains(routeKey)){
        return;
    }

    this->_registerWidget(routeKey, widget, onClick);
    this->_insertWidgetToLayout(index, widget, position);
}


void NavigationBar::_registerWidget(QString routeKey, NavigationWidget *widget, std::function<void()> onClick)
{
    connect(widget, &NavigationWidget::clicked, this, &NavigationBar::_onWidgetClicked);

    if(onClick != nullptr){
        connect(widget, &NavigationWidget::clicked, this, [onClick](){
            onClick();
        });
    }

    widget->setProperty("routeKey", routeKey);
    this->items[routeKey] = widget;
}


void NavigationBar::_insertWidgetToLayout(int index, NavigationWidget *widget, NavigationItemPosition position)
{
    if(position == NavigationItemPosition::TOP){
        widget->setParent(this);
        this->topLayout->insertWidget(index, widget, 0, Qt::AlignTop | Qt::AlignHCenter);
    }else if(position == NavigationItemPosition::SCROLL){
        widget->setParent(this->scrollWidget);
        this->scrollLayout->insertWidget(index, widget, 0, Qt::AlignTop | Qt::AlignHCenter);
    }else{
        widget->setParent(this);
        this->bottomLayout->insertWidget(index, widget, 0, Qt::AlignBottom | Qt::AlignHCenter);
    }

    widget->show();
}


void NavigationBar::removeWidget(QString routeKey)
{
    if(!this->items.contains(routeKey)){
        return;
    }

    NavigationWidget *widget = this->items.end().value();
    this->items.remove(this->items.end().key());
    widget->deleteLater();
    this->history->remove(routeKey);
}

void NavigationBar::setCurrentItem(QString routeKey)
{
    if(!this->items.contains(routeKey)){
        return;
    }

    QMap<QString, NavigationWidget*>::const_iterator it;
    for (it = this->items.begin(); it != this->items.end(); ++it){
        it.value()->setSelected(it.key() == routeKey);
    }
}


void NavigationBar::setFont(QFont font)
{
    QWidget::setFont(font);

    for(int i = 0; i < this->buttons().length(); i++){
        this->buttons().at(i)->setFont(font);
    }
}


void NavigationBar::setSelectedTextVisible(bool isVisible)
{
    for(int i = 0; i < this->buttons().length(); i++){
        ((NavigationBarPushButton*)this->buttons().at(i))->setSelectedTextVisible(isVisible);
    }
}


QList<NavigationWidget*> NavigationBar::buttons()
{
    QList<NavigationWidget*> list = QList<NavigationWidget*>();
    QMap<QString, NavigationWidget*>::const_iterator it;
    for (it = this->items.begin(); it != this->items.end(); ++it){
        auto a = qobject_cast<NavigationPushButton*>(it.value());
        if(a != nullptr){
            list.append(a);
        }
    }
    return list;
}

void NavigationBar::_onWidgetClicked()
{
    NavigationWidget *widget = (NavigationWidget *)this->sender();
    if(widget->isSelectable){
        this->setCurrentItem(widget->property("routeKey").value<QString>());
    }
}