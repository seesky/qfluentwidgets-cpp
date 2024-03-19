#include "flow_layout.h"

FlowLayout::FlowLayout(QWidget *parent, bool needAni = false, bool isTight = false) : QLayout(parent)
{
    this->_items = QList<QLayoutItem*>();
    this->_anis = QList<QPropertyAnimation*>();
    this->_aniGroup = new QParallelAnimationGroup(this);
    this->_verticalSpacing = 10;
    this->_horizontalSpacing = 10;
    this->duration = 300;
    this->ease = QEasingCurve::Linear;
    this->needAni = needAni;
    this->isTight = isTight;
}


void FlowLayout::addItem(QLayoutItem *item)
{
    this->_items.append(item);
}

void FlowLayout::addWidget(QWidget *w)
{
    QLayout::addWidget(w);
    if(!this->needAni){
        return;
    }

    QPropertyAnimation *ani = new QPropertyAnimation(w, "geometry", nullptr);
    ani->setEndValue(QRect(QPoint(0, 0), w->size()));
    ani->setDuration(this->duration);
    ani->setEasingCurve(this->ease);
    w->setProperty("flowAni", QVariant::fromValue<QPropertyAnimation*>(ani));
    this->_anis.append(ani);
    this->_aniGroup->addAnimation(ani);
}


void FlowLayout::setAnimation(int duration, QEasingCurve ease)
{
    if(!this->needAni){
        return;
    }

    this->duration = duration;
    this->ease = ease;

    for(int i = 0; i < this->_anis.length(); i++){
        this->_anis.at(i)->setDuration(duration);
        this->_anis.at(i)->setEasingCurve(ease);
    }
}

int FlowLayout::count() const
{
    return this->_items.length();
}


QLayoutItem *FlowLayout::itemAt(int index) const
{
    if(0 <= index && index < this->_items.length()){
        return this->_items.at(index);
    }

    return nullptr;
}

QLayoutItem *FlowLayout::takeAt(int index)
{
    if(0 <= index && index < this->_items.length()){
        QWidgetItem *item = (QWidgetItem *)(this->_items.at(index)); //TODO:特殊关注
        QPropertyAnimation* ani = item->widget()->property("flowAni").value<QPropertyAnimation*>();
        if(ani != nullptr){
            this->_anis.removeOne(ani);
            this->_aniGroup->removeAnimation(ani);
            ani->deleteLater();
        }

        QLayoutItem *r = this->_items.at(index); //TODO:特殊关注
        this->_items.removeAt(index);
        return r;
    }
    return nullptr;
}



QLayoutItem * FlowLayout::removeWidget(QWidget *widget)
{
    for(int i = 0; i < this->_items.length(); i++){
        if(this->_items.at(i)->widget() == widget){
            return this->takeAt(i);
        }
    }
}

void FlowLayout::removeAllWidgets()
{
    while(!this->_items.isEmpty()){
        this->takeAt(0);
    }
}

void FlowLayout::takeAllWidgets()
{
    while(!this->_items.isEmpty()){
        QLayoutItem *w = this->takeAt(0);
        if(w != nullptr){
            w->widget()->deleteLater(); //特殊关注
        }
    }
}

Qt::Orientation FlowLayout::expandingDirections()
{
    return Qt::Orientation::Horizontal; //特殊关注
}



bool FlowLayout::hasHeightForWidth()
{
    return true;
}


int FlowLayout::heightForWidth(int width)
{
    return this->_doLayout(QRect(0, 0, width, 0), false);
}

void FlowLayout::setGeometry(const QRect& rect)
{
    QLayout::setGeometry(rect);
    this->_doLayout(rect, true);
}

QSize FlowLayout::sizeHint() const
{
    return this->minimumSize();
}

QSize FlowLayout::minimumSize() const
{
    QSize size = QSize();

    for(int i = 0; i < this->_items.length(); i++){
        size = size.expandedTo(this->_items.at(i)->minimumSize());
    }

    QMargins m = this->contentsMargins();
    size += QSize(m.left()+m.right(), m.top()+m.bottom());
    return size;
}

void FlowLayout::setVerticalSpacing(int spacing)
{
    this->_verticalSpacing = spacing;
}

int FlowLayout::verticalSpacing()
{
    return this->_verticalSpacing;
}

void FlowLayout::setHorizontalSpacing(int spacing)
{
    this->_horizontalSpacing = spacing;
}

int FlowLayout::horizontalSpacing()
{
    return this->_horizontalSpacing;
}

int FlowLayout::_doLayout(QRect rect, bool move)
{
    bool aniRestart = false;
    QMargins margin = this->contentsMargins();

    int x = rect.x() + margin.left();
    int y = rect.y() + margin.top();
    int rowHeight = 0;
    int spaceX = this->horizontalSpacing();
    int spaceY = this->verticalSpacing();


    for(int i = 0; i < this->_items.length(); i++){
        if(this->_items.at(i)->widget() != nullptr && !this->_items.at(i)->widget()->isVisible() && this->isTight){
            continue;
        }

        int netxtX = x + this->_items.at(i)->sizeHint().width() + spaceX;

        if(netxtX - spaceX > rect.right() && rowHeight > 0){
            x = rect.x() + margin.left();
            y = y + rowHeight + spaceY;
            netxtX = x + this->_items.at(i)->sizeHint().width() + spaceX;
            rowHeight = 0;
        }

        if(move){
            QRect target = QRect(QPoint(x, y), this->_items.at(i)->sizeHint());
            if(!this->needAni){
                this->_items.at(i)->setGeometry(target);
            }else if(target != this->_anis.at(i)->endValue()){
                this->_anis.at(i)->stop();
                this->_anis.at(i)->setEndValue(target);
                aniRestart = true;
            }
        }

        x = netxtX;
        rowHeight = qMax(rowHeight, this->_items.at(i)->sizeHint().height());
    }

    if(this->needAni && aniRestart){
        this->_aniGroup->stop();
        this->_aniGroup->start();
    }

    return y + rowHeight + margin.bottom() - rect.y();
}


