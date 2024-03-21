#include "tool_tip.h"

ToolTip::ToolTip(QString text, QWidget *parent) : QFrame(parent)
{
    this->__text = text;
    this->__duration = 1000;

    this->container = this->_createContainer();
    this->timer = new QTimer();

    this->setLayout(new QHBoxLayout());
    this->containerLayout = new QHBoxLayout(this->container);
    this->label = new QLabel(text, this);

    this->layout()->setContentsMargins(12, 8, 12, 12);
    this->layout()->addWidget(this->container);
    this->containerLayout->addWidget(this->label);
    this->containerLayout->setContentsMargins(8, 6, 8, 6);

    this->opacityAni = new QPropertyAnimation(this, "windowOpacity", this);
    this->opacityAni->setDuration(150);

    this->shadowEffect = new QGraphicsDropShadowEffect(this);
    this->shadowEffect->setBlurRadius(25);
    this->shadowEffect->setColor(QColor(0, 0, 0, 60));
    this->shadowEffect->setOffset(0, 5);
    this->container->setGraphicsEffect(this->shadowEffect);

    this->timer->setSingleShot(true);
    connect(this->timer, &QTimer::timeout, this, &ToolTip::hide);

    this->setAttribute(Qt::WA_TransparentForMouseEvents);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);
    this->__setQss();

}

QString ToolTip::text()
{
    return this->__text;
}


void ToolTip::setText(QString text)
{
    this->__text = text;
    this->label->setText(text);
    this->container->adjustSize();
    this->adjustSize();
}


int ToolTip::duration()
{
    return this->__duration;
}


void ToolTip::setDuration(int duration)
{
    this->__duration = duration;
}


void ToolTip::__setQss()
{
    this->container->setObjectName(QString("container"));
    this->label->setObjectName(QString("contentLabel"));
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("TOOL_TIP"), Theme::AUTO);
    this->label->adjustSize();
    this->adjustSize();
}


QFrame *ToolTip::_createContainer()
{
    return new QFrame(this);
}


void ToolTip::showEvent(QShowEvent *event)
{
    this->opacityAni->setStartValue(0);
    this->opacityAni->setEndValue(1);
    this->opacityAni->start();

    this->timer->stop();
    if(this->duration() > 0){
        this->timer->start(this->__duration + this->opacityAni->duration());
    }

    QFrame::showEvent(event);
}


void ToolTip::hideEvent(QHideEvent *event)
{
    this->timer->stop();
    QFrame::hideEvent(event);
}

void ToolTip::adjustPos(QWidget *widget, ToolTipPosition position)
{
    ToolTipPositionManager *manager = ToolTipPositionManager::make(position);
    this->move(manager->position(this, widget));
}


QPoint ToolTipPositionManager::position(ToolTip *tooltip, QWidget *parent)
{
    QPoint pos = this->_pos(tooltip, parent);
    //int x = pos.x();
    //int y = pos.y();

    QRect rect = QApplication::screenAt(QCursor::pos())->availableGeometry();
    int x = qMax(rect.left(), qMin(pos.x(), rect.right() - tooltip->width() - 4));
    int y = qMax(rect.top(), qMax(pos.y(), rect.bottom() - tooltip->height() - 4));
    return QPoint(x, y);
}


QPoint ToolTipPositionManager::_pos(ToolTip *tooltip, QWidget *parent)
{
    
}


ToolTipPositionManager* ToolTipPositionManager::make(ToolTipPosition position)
{
    switch (position)
    {
    case ToolTipPosition::TOP:
        return new TopToolTipManager();
        break;
    case ToolTipPosition::BOTTOM:
        return new BottomToolTipManager();
        break;
    case ToolTipPosition::LEFT:
        return new LeftToolTipManager();
        break;
    case ToolTipPosition::RIGHT:
        return new RightToolTipManager();
        break;
    case ToolTipPosition::TOP_RIGHT:
        return new TopRightToolTipManager();
        break;
    case ToolTipPosition::BOTTOM_RIGHT:
        return new BottomRightToolTipManager();
        break;
    case ToolTipPosition::TOP_LEFT:
        return new TopLeftToolTipManager();
        break;
    case ToolTipPosition::BOTTOM_LEFT:
        return new BottomLeftToolTipManager();
        break;
    default:
        return nullptr;
        break;
    }
}


QPoint TopToolTipManager::_pos(ToolTip *tooltip, QWidget *parent)
{
    QPoint pos = parent->mapToGlobal(QPoint());
    int x = pos.x() + parent->width() / 2 - tooltip->width() / 2;
    int y = pos.y() - tooltip->height();
    return QPoint(x, y);
}


QPoint BottomToolTipManager::_pos(ToolTip *tooltip, QWidget *parent)
{
    QPoint pos = parent->mapToGlobal(QPoint());
    int x = pos.x() + parent->width() / 2 - tooltip->width() / 2;
    int y = pos.y() + tooltip->height();
    return QPoint(x, y);
}


QPoint LeftToolTipManager::_pos(ToolTip *tooltip, QWidget *parent)
{
    QPoint pos = parent->mapToGlobal(QPoint());
    int x = pos.x() - tooltip->width();
    int y = pos.y() + (parent->height() - tooltip->height()) / 2;
    return QPoint(x, y);
}


QPoint RightToolTipManager::_pos(ToolTip *tooltip, QWidget *parent)
{
    QPoint pos = parent->mapToGlobal(QPoint());
    int x = pos.x() + tooltip->width();
    int y = pos.y() + (parent->height() - tooltip->height()) / 2;
    return QPoint(x, y);
}


QPoint TopRightToolTipManager::_pos(ToolTip *tooltip, QWidget *parent)
{
    QPoint pos = parent->mapToGlobal(QPoint());
    int x = pos.x() + parent->width() - tooltip->width() + tooltip->layout()->contentsMargins().right();
    int y = pos.y() - tooltip->height();
    return QPoint(x, y);
}


QPoint TopLeftToolTipManager::_pos(ToolTip *tooltip, QWidget *parent)
{
    QPoint pos = parent->mapToGlobal(QPoint());
    int x = pos.x() - tooltip->layout()->contentsMargins().left();
    int y = pos.y() - tooltip->height();
    return QPoint(x, y);
}


QPoint BottomRightToolTipManager::_pos(ToolTip *tooltip, QWidget *parent)
{
    QPoint pos = parent->mapToGlobal(QPoint());
    int x = pos.x() + parent->width() - tooltip->width() + tooltip->layout()->contentsMargins().right();
    int y = pos.y() + tooltip->height();
    return QPoint(x, y);
}


QPoint BottomLeftToolTipManager::_pos(ToolTip *tooltip, QWidget *parent)
{
    QPoint pos = parent->mapToGlobal(QPoint());
    int x = pos.x() - tooltip->layout()->contentsMargins().left();
    int y = pos.y() + tooltip->height();
    return QPoint(x, y);
}


ToolTipFilter::ToolTipFilter(QWidget *parent, int showDelay = 300, ToolTipPosition position = ToolTipPosition::TOP) : QObject(parent)
{
    this->isEnter = false;
    this->_tooltip = nullptr;
    this->_tooltipDelay = showDelay;
    this->position = position;
    this->timer = new QTimer(this);
    this->timer->setSingleShot(true);
    connect(this->timer, &QTimer::timeout, this, &ToolTipFilter::showToolTip);
}


bool ToolTipFilter::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::ToolTip){
        return true;
    }else if(event->type() == QEvent::Hide || event->type() == QEvent::Leave){
        this->hideToolTip();
    }else if(event->type() == QEvent::Enter){
        this->isEnter = true;
        QWidget *parent = (QWidget *)(this->parent());
        if(this->_canShowToolTip()){
            if(this->_tooltip == nullptr){
                this->_tooltip = this->_createToolTip();
            }

            int t = parent->toolTipDuration() > 0 ? parent->toolTipDuration() : -1;
            this->_tooltip->setDuration(t);

            this->timer->start(this->_tooltipDelay);
        }
    }else if(event->type() == QEvent::MouseButtonPress){
        this->hideToolTip();
    }

    return QObject::eventFilter(watched, event);
}

ToolTip *ToolTipFilter::_createToolTip()
{
    return new ToolTip(((QWidget *)this->parent())->toolTip(), ((QWidget *)this->parent())->window());
}


void ToolTipFilter::hideToolTip()
{
    this->isEnter = false;
    this->timer->stop();
    if(this->_tooltip != nullptr){
        this->_tooltip->hide();
    }
}


void ToolTipFilter::showToolTip()
{
    if(!this->isEnter){
        return;
    }

    QWidget *parent = (QWidget *)(this->parent());
    this->_tooltip->setText(parent->toolTip());
    this->_tooltip->adjustPos(parent, this->position);
    this->_tooltip->show();
}


void ToolTipFilter::setToolTipDelay(int delay)
{
    this->_tooltipDelay = delay;
}

bool ToolTipFilter::_canShowToolTip()
{
    QWidget *parent = (QWidget *)(this->parent());
    return parent->isWidgetType() && !parent->toolTip().isEmpty() && parent->isEnabled();
}