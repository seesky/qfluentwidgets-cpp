#include "scroll_area.h"

ScrollArea::ScrollArea(QWidget *parent) : QScrollArea(parent)
{
    scrollDelagate = new SmoothScrollDelegate(this, false);
}

SingleDirectionScrollArea::SingleDirectionScrollArea(QWidget *parent, Qt::Orientation orient = Qt::Vertical) : QScrollArea(parent)
{
    this->orient = orient;
    this->smoothScroll = new SmoothScroll(this, orient);
    this->vScrollBar = new SmoothScrollBar(Qt::Vertical, this);
    this->hScrollBar = new SmoothScrollBar(Qt::Horizontal, this);
}

void SingleDirectionScrollArea::setVerticalScrollBarPolicy(Qt::ScrollBarPolicy policy)
{
    QScrollArea::setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->vScrollBar->setForceHidden(policy == Qt::ScrollBarAlwaysOff);
}

void SingleDirectionScrollArea::setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy policy)
{
    QScrollArea::setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->hScrollBar->setForceHidden(policy == Qt::ScrollBarAlwaysOff);
}

void SingleDirectionScrollArea::setSmoothMode(SmoothMode mode)
{
    this->smoothScroll->setSmoothMode(mode);
}

void SingleDirectionScrollArea::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Left || e->key() == Qt::Key_Right){
        return;
    }

    return QScrollArea::keyPressEvent(e);
}

void SingleDirectionScrollArea::wheelEvent(QWheelEvent *e)
{
    if(e->angleDelta().x() != 0){
        return;
    }

    this->smoothScroll->wheelEvent(e);
    e->setAccepted(true);
}


void SingleDirectionScrollArea::publicSetViewportMargins(int left, int top, int right, int bottom)
{
    this->setViewportMargins(left, top, right, bottom);
}

SmoothScrollArea::SmoothScrollArea(QWidget *parent) : QScrollArea(parent)
{
    this->delegate = new SmoothScrollDelegate(this, true);
}

void SmoothScrollArea::setScrollAnimation(Qt::Orientation orient, int duration, QEasingCurve easing)
{
    SmoothScrollBar *bar = orient == Qt::Horizontal ? this->delegate->hScrollBar : this->delegate->vScrollBar;
    bar->setScrollAnimation(duration, easing);
}