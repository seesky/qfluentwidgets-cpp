#include "pivot.h"


void PivotItem::_postInit()
{
    this->isSelected = false;
    this->setProperty("isSelected", new QVariant(QVariant::fromValue<bool>(false)));
    connect(this, &PivotItem::clicked, this, [this](){
        emit(this->itemClicked(true));
    });

    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("PIVOT"), Theme::AUTO);
    Font().setFont(this, 18, QFont::Normal);
}


void PivotItem::setSelected(bool isSelected)
{
    if(this->isSelected == isSelected){
        return;
    }

    this->isSelected = isSelected;
    this->setProperty("isSelected", new QVariant(QVariant::fromValue<bool>(isSelected)));
    this->setStyle(QApplication::style());
    this->update();
}


Pivot::Pivot(QWidget *parent) : QWidget(parent)
{
    this->items = new QMap<QString, PivotItem*>();
    this->_currentRouteKey = nullptr;

    this->hBoxLayout = new QHBoxLayout(this);
    this->slideAni = FluentAnimation::create(FluentAnimationType::POINT_TO_POINT, QString("SCALE"), FluentAnimationSpeed::FAST, new QVariant(QVariant::fromValue<float>(0)), this);
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("PIVOT"), Theme::AUTO);

    this->hBoxLayout->setSpacing(0);
    this->hBoxLayout->setAlignment(Qt::AlignLeft);
    this->hBoxLayout->setContentsMargins(0, 0, 0, 0);
    this->hBoxLayout->setSizeConstraint(QHBoxLayout::SetMinimumSize);

    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}


PivotItem *Pivot::addItem(QString routeKey, QString text, std::function<void()> onClick, QVariant *icon)
{
    return this->insertItem(-1, routeKey, text, onClick, icon);
}

void Pivot::addWidget(QString routeKey, PivotItem *widget, std::function<void()> onClick)
{
    this->insertWidget(-1, routeKey, widget, onClick);
}

PivotItem *Pivot::insertItem(int index, QString routeKey, QString text, std::function<void()> onClick, QVariant *icon)
{
    if(this->items->contains(routeKey)){
        return nullptr;
    }

    PivotItem *item = new PivotItem(text, this, nullptr);
    if(icon->isValid()){
        item->setIcon(icon);
    }

    this->insertWidget(index, routeKey, item, onClick);
    return item;
}

void Pivot::insertWidget(int index, QString routeKey, PivotItem *widget, std::function<void()> onClick)
{
    if(this->items->contains(routeKey)){
        return;
    }

    widget->setProperty("routeKey", new QVariant(QVariant::fromValue<QString>(routeKey)));
    connect(widget, &PivotItem::itemClicked, this, &Pivot::_onItemClicked);
    if(onClick != nullptr){
        connect(widget, &PivotItem::itemClicked, this, [onClick](){
            onClick();
        });
    }

    (*this->items)[routeKey] = widget;
    this->hBoxLayout->insertWidget(index, widget, 1);
}


void Pivot::removeWidget(QString routeKey)
{
    if(!this->items->contains(routeKey)){
        return;
    }

    PivotItem *item = this->items->value(routeKey);
    this->items->remove(routeKey);
    this->hBoxLayout->removeWidget(item);
    qrouter->remove(routeKey);
    item->deleteLater();
}


void Pivot::clear()
{
    QMap<QString, PivotItem*>::iterator i;
    for (i = this->items->begin(); i != this->items->end(); ++i) {
        this->hBoxLayout->removeWidget(i.value());
        qrouter->remove(i.key());
        i.value()->deleteLater();
    }

    this->items->clear();
}



PivotItem *Pivot::currentItem()
{
    if(this->_currentRouteKey.isNull()){
        return nullptr;
    }

    return this->widget(this->_currentRouteKey);
}


void Pivot::setCurrentItem(QString routeKey)
{
    if(!this->items->contains(routeKey)){
        return;
    }

    this->_currentRouteKey = routeKey;
    this->slideAni->startAnimation(new QVariant(QVariant::fromValue<int>(this->widget(routeKey)->x())), nullptr);

    QMap<QString, PivotItem*>::iterator i;
    for (i = this->items->begin(); i != this->items->end(); ++i) {
        i.value()->setSelected(i.key() == routeKey);
    }
}

void Pivot::setItemFontSize(int size)
{
    QMap<QString, PivotItem*>::iterator i;
    for (i = this->items->begin(); i != this->items->end(); ++i) {
        QFont font = i.value()->font();
        font.setPixelSize(size);
        i.value()->setFont(font);
        i.value()->adjustSize();
    }
}



void Pivot::_onItemClicked()
{
    PivotItem *item = (PivotItem *)this->sender();
    this->setCurrentItem(item->property("routeKey").value<QString>());
}


PivotItem *Pivot::widget(QString routeKey)
{
    if(!this->items->contains(routeKey)){
        return nullptr;
    }

    return this->items->value(routeKey);
}


void Pivot::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    PivotItem *item =  this->currentItem();
    if(item != nullptr){
        this->slideAni->setValue(new QVariant(QVariant::fromValue<int>(item->x())));
    }
}


void Pivot::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    if(this->currentItem() == nullptr){
        return;
    }

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(*(ThemeColor().themeColor()));

    int x = this->currentItem()->width() / 2 - 8 + this->slideAni->value()->value<int>();
    painter.drawRoundedRect(x, this->height() - 3, 16, 3, 1.5, 1.5);
}