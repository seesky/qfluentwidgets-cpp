#include "segmented_widget.h"

SegmentedItem::SegmentedItem() : PivotItem(){
    this->_postInit();
}

SegmentedItem::SegmentedItem(QWidget *parent) : PivotItem(parent){
    this->_postInit();
}

SegmentedItem::SegmentedItem(QString text, QWidget *parent, QVariant *icon): PivotItem(text, parent, icon){
    this->_postInit();
}

SegmentedItem::SegmentedItem(QIcon *icon, QString text, QWidget *parent): PivotItem(icon, text, parent){
    this->_postInit();
}

SegmentedItem::SegmentedItem(FluentIcon *icon, QString text, QWidget *parent): PivotItem(icon, text, parent){
    this->_postInit();
}


void SegmentedItem::_postInit()
{
    PivotItem::_postInit();
    Font().setFont(this, 14, QFont::Normal);
}





SegmentedToolItem::SegmentedToolItem(QWidget *parent) : ToolButton(parent){
    this->_postInit();
}


SegmentedToolItem::SegmentedToolItem(FluentIcon *icon, QWidget *parent) : ToolButton(icon, parent){
    this->_postInit();
}


SegmentedToolItem::SegmentedToolItem(SpinIcon *icon, QWidget *parent) : ToolButton(icon, parent){
    this->_postInit();
}


SegmentedToolItem::SegmentedToolItem(QIcon *icon, QWidget *parent) : ToolButton(icon, parent){
    this->_postInit();
}


SegmentedToolItem::SegmentedToolItem(QString icon, QWidget *parent) : ToolButton(icon, parent){
    this->_postInit();
}


void SegmentedToolItem::_postInit()
{
    this->isSelected = false;
    this->setProperty("isSelected", new QVariant(QVariant::fromValue<bool>(false)));
    connect(this, &SegmentedToolItem::clicked, this, [this](){
        emit(this->itemClicked(true));
    });

    this->setFixedSize(38, 33);
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("PIVOT"), Theme::AUTO);
}


void SegmentedToolItem::setSelected(bool isSelected)
{
    if(this->isSelected == isSelected){
        return;
    }

    this->isSelected = isSelected;
    this->setProperty("isSelected", new QVariant(QVariant::fromValue<bool>(isSelected)));
    this->setStyle(QApplication::style());
    this->update();
}


SegmentedToggleToolItem::SegmentedToggleToolItem(QWidget *parent) : TransparentToolButton(parent)
{}


SegmentedToggleToolItem::SegmentedToggleToolItem(FluentIcon *icon, QWidget *parent) : TransparentToolButton(icon, parent)
{
    this->_postInit();
}


SegmentedToggleToolItem::SegmentedToggleToolItem(SpinIcon *icon, QWidget *parent) : TransparentToolButton(icon, parent)
{
    this->_postInit();
}


SegmentedToggleToolItem::SegmentedToggleToolItem(QIcon *icon, QWidget *parent) : TransparentToolButton(icon, parent)
{
    this->_postInit();
}


SegmentedToggleToolItem::SegmentedToggleToolItem(QString icon, QWidget *parent) : TransparentToolButton(icon, parent)
{
    this->_postInit();
}

void SegmentedToggleToolItem::_postInit()
{
    TransparentToolButton::_postInit();
    this->isSelected = false;

    this->setFixedSize(50, 32);
    connect(this, &SegmentedToggleToolItem::clicked, this, [this](){
        emit(this->itemClicked(true));
    });
}


void SegmentedToggleToolItem::setSelected(bool isSelected)
{
    if(this->isSelected = isSelected){
        return;
    }

    this->isSelected = isSelected;
    this->setChecked(isSelected);
}


void SegmentedToggleToolItem::_drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state)
{
    QIcon *_icon;
    if(this->isSelected && icon->canConvert<FluentIcon>()){
        Theme theme = !isDarkTheme() ? Theme::DARK : Theme::LIGHT;
        _icon = icon->value<FluentIcon>().icon(theme, nullptr);
        MIcon().drawIcon(new QVariant(QVariant::fromValue<QIcon>(*_icon)), painter, rect, nullptr, state);
    }else{
        MIcon().drawIcon(icon, painter, rect, nullptr, state);
    }
}



SegmentedWidget::SegmentedWidget(QWidget *parent) : Pivot(parent)
{
    this->setAttribute(Qt::WA_StyledBackground);
}


SegmentedItem *SegmentedWidget::insertItem(int index, QString routeKey, QString text, std::function<void()> onClick, QVariant *icon)
{
    if(this->items->contains(routeKey)){
        return nullptr;
    }

    SegmentedItem *item = new SegmentedItem(text, this, nullptr);
    if(icon->isValid()){
        item->setIcon(icon);
    }

    this->insertWidget(index, routeKey, item, onClick);
    return item;
}


void SegmentedWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    if(this->currentItem() == nullptr){
        return;
    }

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    if(isDarkTheme()){
        painter.setPen(QColor(255, 255, 255, 14));
        painter.setBrush(QColor(255, 255, 255, 15));
    }else{
        painter.setPen(QColor(0, 0, 0, 19));
        painter.setBrush(QColor(255, 255, 255, 179));
    }

    PivotItem *item = this->currentItem();
    QRect rect = item->rect().adjusted(1, 1, -1, -1).translated(this->slideAni->value()->value<int>(), 0);
    painter.drawRoundedRect(rect, 5, 5);

    painter.setPen(Qt::PenStyle::NoPen);
    painter.setBrush(*(ThemeColor().themeColor()));

    int x = this->currentItem()->width() / 2 - 8 + this->slideAni->value()->value<int>();
    painter.drawRoundedRect(QRectF(x, this->height() - 3.5, 16, 3), 1.5, 1.5);
}



SegmentedToolWidget::SegmentedToolWidget(QWidget *parent) : SegmentedWidget(parent)
{
    SegmentedWidget::setAttribute(Qt::WA_StyledBackground, true);
}


SegmentedToolItem *SegmentedToolWidget::addItem(QString routeKey, QVariant *icon, std::function<void()> onClick)
{
    return this->insertItem(-1, routeKey, icon, onClick);
}

void SegmentedToolWidget::insertWidget(int index, QString routeKey, SegmentedToolItem *widget, std::function<void()> onClick)
{
    if(this->items->contains(routeKey)){
        return;
    }

    widget->setProperty("routeKey", new QVariant(QVariant::fromValue<QString>(routeKey)));
    connect(widget, &SegmentedToolItem::itemClicked, this, &Pivot::_onItemClicked);
    if(onClick != nullptr){
        connect(widget, &SegmentedToolItem::itemClicked, this, [onClick](){
            onClick();
        });
    }

    (*this->items)[routeKey] = widget;
    this->hBoxLayout->insertWidget(index, widget, 1);
}


SegmentedToolItem *SegmentedToolWidget::insertItem(int index, QString routeKey, QVariant *icon, std::function<void()> onClick)
{
    if(this->items->contains(routeKey)){
        return nullptr;
    }

    SegmentedToolItem *item = this->_createItem(icon);
    this->insertWidget(index, routeKey, item, onClick);
    return item;
}


SegmentedToolItem *SegmentedToolWidget::_createItem(QVariant *icon)
{
    if(icon->canConvert<FluentIcon>()){
        FluentIcon _icon =  icon->value<FluentIcon>();
        return new SegmentedToolItem(&_icon, nullptr);
    }else if(icon->canConvert<QIcon>()){
        QIcon _icon = icon->value<QIcon>();
        return new SegmentedToolItem(&_icon, nullptr);
    }
}



SegmentedToggleToolItem *SegmentedToggleToolWidget::_createItem(QVariant *icon)
{
    if(icon->canConvert<FluentIcon>()){
        FluentIcon _icon =  icon->value<FluentIcon>();
        return new SegmentedToggleToolItem(&_icon, nullptr);
    }else if(icon->canConvert<QIcon>()){
        QIcon _icon = icon->value<QIcon>();
        return new SegmentedToggleToolItem(&_icon, nullptr);
    }
}



void SegmentedToggleToolWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    if(this->currentItem() == nullptr){
        return;
    }

    QPainter painter(this);
    painter.setRenderHints(QPainter::RenderHint::Antialiasing);

    painter.setPen(Qt::PenStyle::NoPen);
    painter.setBrush(*(ThemeColor().themeColor()));

    PivotItem * item = this->currentItem();
    painter.drawRoundedRect(QRectF(this->slideAni->value()->value<int>(), 0, item->width(), item->height()), 4, 4);
}