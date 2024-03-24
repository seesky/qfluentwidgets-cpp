#include "breadcrumb.h"

BreadcrumbWidget::BreadcrumbWidget(QWidget *parent) : QWidget(parent)
{
    this->isHover = false;
    this->isPressed = false;
}

void BreadcrumbWidget::mousePressEvent(QMouseEvent *event)
{
    this->isPressed = true;
    this->update();
}


void BreadcrumbWidget::mouseReleaseEvent(QMouseEvent *event)
{
    this->isPressed = false;
    this->update();
    emit(this->clicked());
}

void BreadcrumbWidget::enterEvent(QEvent *event)
{
    this->isHover = true;
    this->update();
}

void BreadcrumbWidget::leaveEvent(QEvent *event)
{
    this->isHover = false;
    this->update();
}



ElideButton::ElideButton(QWidget *parent) : BreadcrumbWidget(parent)
{
    this->setFixedSize(16, 16);
}

void ElideButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    if(this->isPressed){
        painter.setOpacity(0.5);
    }else if(!this->isHover){
        painter.setOpacity(0.61);
    }

    FluentIcon *icon = new FluentIcon();
    icon->setIconName(QString("MORE"));
    icon->render(&painter, this->rect(), Theme::AUTO, 0, nullptr);
}


void ElideButton::clearState()
{
    this->setAttribute(Qt::WA_UnderMouse, false);
    this->isHover = false;
    QHoverEvent *e = new QHoverEvent(QEvent::HoverLeave, QPoint(-1, -1), QPoint());
    QApplication::sendEvent(this, e);
}



BreadcrumbItem::BreadcrumbItem(QString routeKey, QString text, int index, QWidget *parent) : BreadcrumbWidget(parent)
{
    this->text = text;
    this->routeKey = routeKey;
    this->isHover = false;
    this->isPressed = false;
    this->isSelected = false;
    this->index = index;
    this->spacing = 5;
}

void BreadcrumbItem::setText(QString text)
{
    this->text = text;

    QRect rect = this->fontMetrics().boundingRect(text);
    int w = rect.width() + 1;
    if(!this->isRoot()){
        w += this->spacing * 2;
    }

    this->setFixedWidth(w);
    this->setFixedHeight(rect.height());
    this->update();
}

bool BreadcrumbItem::isRoot()
{
    return this->index == 0;
}

void BreadcrumbItem::setSelected(bool isSelected)
{
    this->isSelected = isSelected;
    this->update();
}

void BreadcrumbItem::setFont(QFont font)
{
    BreadcrumbWidget::setFont(font);
    this->setText(this->text);
}

void BreadcrumbItem::setSpacing(int spacing)
{
    this->spacing = spacing;
    this->setText(this->text);
}

void BreadcrumbItem::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::TextAntialiasing | QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    int sw = this->spacing * 2;
    if(!this->isRoot()){
        int iw = this->font().pixelSize() / 14 * 8;
        QRect rect = QRect((sw - iw) / 2, (this->height() - iw) / 2 + 1, iw, iw);

        painter.setOpacity(0.61);
        FluentIcon *icon = new FluentIcon();
        icon->setIconName(QString("CHEVRON_RIGHT_MED"));
        icon->render(&painter, rect, Theme::AUTO, 0, nullptr);
    }

    if(this->isPressed){
        float alpha = isDarkTheme() ? 0.54 : 0.45;
        painter.setOpacity(this->isSelected ? 1 : alpha);
    }else if(this->isSelected || this->isHover){
        painter.setOpacity(1);
    }else{
        painter.setOpacity(isDarkTheme() ? 0.79 : 0.61);
    }

    painter.setFont(this->font());
    painter.setPen(isDarkTheme() ? Qt::white : Qt::black);

    QRect _rect;
    if(this->isRoot()){
        _rect = this->rect();
    }else{
        _rect = QRect(sw, 0, this->width() - sw, this->height());
    }

    painter.drawText(_rect, Qt::AlignVCenter | Qt::AlignLeft, this->text);
}



BreadcrumbBar::BreadcrumbBar(QWidget *parent) : QWidget(parent)
{
    this->itemMap = QMap<QString, BreadcrumbItem*>();
    this->items = QList<BreadcrumbItem*>();
    this->hiddenItems = QList<BreadcrumbItem*>();

    this->_spacing = 10;
    this->_currentIndex = -1;

    this->elideButton = new ElideButton(this);

    Font().setFont(this, 14, QFont::Normal);
    this->setAttribute(Qt::WA_TranslucentBackground);

    this->elideButton->hide();
    connect(this->elideButton, &ElideButton::clicked, this, &BreadcrumbBar::_showHiddenItemsMenu);
}



void BreadcrumbBar::addItem(QString routeKey, QString text)
{
    if(this->itemMap.contains(routeKey)){
        return;
    }

    BreadcrumbItem *item = new BreadcrumbItem(routeKey, text, this->items.length(), this);
    item->setFont(this->font());
    item->setSpacing(this->getSpacing());
    connect(item, &BreadcrumbItem::clicked, this, [this, routeKey](){
        this->setCurrentItem(routeKey);
    });

    this->itemMap.insert(routeKey, item);
    this->items.append(item);
    int maxHeight = 0;
    for(int i = 0; i < this->items.length(); i++){
        if(this->items.at(i)->height() > maxHeight){
            maxHeight = this->items.at(i)->height();
        }
    }
    this->setFixedHeight(maxHeight);
    this->setCurrentItem(routeKey);

    this->updateGeometry();
}


void BreadcrumbBar::setCurrentIndex(int index)
{
    if(!(0 <= index && index < this->items.length()) || index == this->currentIndex()){
        return;
    }

    if(this->currentIndex() >= 0){
        this->currentItem()->setSelected(false);
    }

    this->_currentIndex = index;
    this->currentItem()->setSelected(true);

    for (int i = this->items.size() - 1; i > index; i--)
    {
        BreadcrumbItem *item = this->items.takeLast();
        this->items.removeOne(item);

        this->itemMap.remove(item->routeKey);

        item->deleteLater();
    }

    this->updateGeometry();
    emit(this->currentIndexChanged(index));
    emit(this->currentItemChanged(this->currentItem()->routeKey));

}


void BreadcrumbBar::setCurrentItem(QString routeKey)
{
    if(!this->itemMap.contains(routeKey)){
        return;
    }

    this->setCurrentIndex(this->items.indexOf(this->itemMap.value(routeKey)));
}


BreadcrumbItem *BreadcrumbBar::item(QString routeKey)
{
    BreadcrumbItem *item;
    for(int i = 0; i < this->items.length(); i++){  //TOOD：特殊关注
        item = this->items.at(i);
        if(item->routeKey == routeKey){
            return item;
        }
    }
    return nullptr;
}


int BreadcrumbBar::currentIndex()
{
    return this->_currentIndex;
}

BreadcrumbItem *BreadcrumbBar::currentItem()
{
    if(this->currentIndex() >= 0){
        return this->items.at(this->currentIndex());
    }
    return nullptr;
}

void BreadcrumbBar::resizeEvent(QResizeEvent *event)
{
    this->updateGeometry();
}

void BreadcrumbBar::clear()
{
    BreadcrumbItem *item;
    for(int i = 0; i < this->items.length(); i++){  
        item = this->items.at(i);
        this->items.removeOne(item);

        this->itemMap.remove(item->routeKey);
        item->deleteLater();
    }

    this->elideButton->hide();
    this->_currentIndex = -1;
}

void BreadcrumbBar::popItem()
{
    BreadcrumbItem *item = this->items.takeLast();
    this->items.pop_back();

    this->itemMap.remove(item->routeKey);
    item->deleteLater();

    if(this->currentIndex() >= item->index){
        this->setCurrentIndex(this->currentIndex() - 1);
    }

    this->updateGeometry();
}

void BreadcrumbBar::updateGeometry()
{
    
    if(this->items.length() == 0){
        return;
    }

    
    int x = 0;
    this->elideButton->hide();
    
    this->hiddenItems.clear();
    for(int i = 0; i < this->items.length() - 1; i++){
        this->hiddenItems.append(this->items.value(i));
    }

    
    QList<QVariant> visibleItems = QList<QVariant>(); //TODO:特殊关注是否成功保存数据

    if(true){
        for(int i = 0; i < this->items.length(); i++){
            visibleItems.append(QVariant::fromValue<BreadcrumbItem*>(this->items.at(i)));
        }
        this->hiddenItems.clear();
    }else{
        visibleItems.append(QVariant::fromValue<ElideButton*>(this->elideButton));
        visibleItems.append(QVariant::fromValue<BreadcrumbItem*>(this->items.takeLast()));

        int w = this->elideButton->width() + this->items.takeLast()->width();

        for(int i = this->items.length() - 2; i >= 0; i--){
            w += this->items.at(i)->width();
            if(w > this->width()){
                break;
            }

            visibleItems.insert(1, QVariant::fromValue<BreadcrumbItem*>(this->items.at(i)));
            this->hiddenItems.removeOne(this->items.at(i));
        }
    }

    for(int i = 0; i < this->hiddenItems.length(); i++){
        this->hiddenItems.at(i)->hide();
    }

    for(int i = 0; i < visibleItems.length(); i++){
        if(visibleItems.at(i).canConvert<ElideButton*>()){
            visibleItems.at(i).value<ElideButton*>()->move(x, (this->height() - visibleItems.at(i).value<ElideButton*>()->height()) / 2);
            visibleItems.at(i).value<ElideButton*>()->show();
            x += visibleItems.at(i).value<ElideButton*>()->width();
        }else if(visibleItems.at(i).canConvert<BreadcrumbItem*>()){
            visibleItems.at(i).value<BreadcrumbItem*>()->move(x, (this->height() - visibleItems.at(i).value<BreadcrumbItem*>()->height()) / 2);
            visibleItems.at(i).value<BreadcrumbItem*>()->show();
            x += visibleItems.at(i).value<BreadcrumbItem*>()->width();
        }
    }
    
}



bool BreadcrumbBar::isElideVisible()
{
    int w = 0;
    for(int i = 0; i < this->items.length(); i++){
        w += this->items.at(i)->width();
    }
    return w > this->width();
}




void BreadcrumbBar::setFont(QFont font)
{
    QWidget::setFont(font);

    int s = font.pixelSize() / 14 * 16; //TODO:关注是否为0
    this->elideButton->setFixedSize(s, s);

    for(int i = 0; i < this->items.length(); i++){
        this->items.at(i)->setFont(font);
    }
}


void BreadcrumbBar::_showHiddenItemsMenu()
{
    this->elideButton->clearState();

    RoundMenu *menu = new RoundMenu(QString(""), this);
    menu->setItemHeight(32);

    for(int i = 0; i < this->hiddenItems.length(); i++){
        BreadcrumbItem *item = this->hiddenItems.at(i);
        Action *action = new Action(item->text, menu);
        connect(action, &Action::triggered, this, [this, item](){
            this->setCurrentItem(item->routeKey);
        });
    }

    int x = -menu->layout()->contentsMargins().left();
    QPoint pd = this->mapToGlobal(QPoint(x, this->height()));
    int hd = menu->view->heightForAnimation(&pd, MenuAnimationType::DROP_DOWN);

    QPoint pu = this->mapToGlobal(QPoint(x, 0));
    int hu = menu->view->heightForAnimation(&pd, MenuAnimationType::PULL_UP);

    if(hd >= hu){
        menu->view->adjustSize(&pd, MenuAnimationType::DROP_DOWN);
        menu->exec(&pd, true, MenuAnimationType::DROP_DOWN);
    }else{
        menu->view->adjustSize(&pu, MenuAnimationType::PULL_UP);
        menu->exec(&pu, true, MenuAnimationType::PULL_UP);
    }
}


int BreadcrumbBar::getSpacing()
{
    return this->_spacing;
}

void BreadcrumbBar::setSpacing(int spacing)
{
    if(spacing == this->_spacing){
        return;
    }

    this->_spacing = spacing;
    for(int i = 0; i < this->items.length(); i++){
        this->items.at(i)->setSpacing(spacing);
    }
}