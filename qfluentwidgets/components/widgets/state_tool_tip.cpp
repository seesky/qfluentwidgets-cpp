#include "state_tool_tip.h"

StateCloseButton::StateCloseButton(QWidget *parent) : QToolButton(parent)
{
    this->setFixedSize(12, 12);
    this->isPressed = false;
    this->isEnter = false;
}

void StateCloseButton::enterEvent(QEvent *event)
{
    this->isEnter = true;
    this->update();
}

void StateCloseButton::leaveEvent(QEvent *event)
{
    this->isEnter = false;
    this->isPressed = false;
    this->update();
}

void StateCloseButton::mousePressEvent(QMouseEvent *event)
{
    this->isPressed = true;
    this->update();
    QToolButton::mousePressEvent(event);
}

void StateCloseButton::mouseReleaseEvent(QMouseEvent *event)
{
    this->isPressed = false;
    this->update();
    QToolButton::mouseReleaseEvent(event);
}

void StateCloseButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    if(this->isPressed){
        painter.setOpacity(0.6);
    }else if(this->isEnter){
        painter.setOpacity(0.8);
    }

    Theme theme = !isDarkTheme() ? Theme::DARK : Theme::LIGHT;
    FluentIcon *icon = new FluentIcon();
    icon->setIconName(QString("CLOSE"));
    icon->render(&painter, this->rect(), Theme::AUTO, 0, nullptr);
}


StateToolTip::StateToolTip(QString title, QString content, QWidget *parent) : QWidget(parent)
{
    this->title = title;
    this->content = content;

    this->titleLabel = new QLabel(this->title, this);
    this->contentLabel = new QLabel(this->content, this);
    this->rotateTimer = new QTimer(this);

    this->opacityEffect = new QGraphicsOpacityEffect(this);
    this->animation = new QPropertyAnimation(this->opacityEffect, "opacity");
    this->closeButton = new StateCloseButton(this);

    this->isDone = false;
    this->rotateAngle = 0;
    this->deltaAngle = 20;

    this->__initWidget();
}


void StateToolTip::__initWidget()
{
    this->setAttribute(Qt::WA_StyledBackground);
    this->setGraphicsEffect(this->opacityEffect);
    this->opacityEffect->setOpacity(1);
    this->rotateTimer->setInterval(50);
    this->contentLabel->setMinimumWidth(200);

    connect(this->closeButton, &StateCloseButton::clicked, this, &StateToolTip::__onCloseButtonClicked);
    connect(this->rotateTimer, &QTimer::timeout, this, &StateToolTip::__rotateTimerFlowSlot);

    this->__setQss();
    this->__initLayout();

    this->rotateTimer->start();
}

void StateToolTip::__initLayout()
{
    this->setFixedSize(qMax(this->titleLabel->width(), this->contentLabel->width()) + 56, 51);
    this->titleLabel->move(32, 9);
    this->contentLabel->move(12, 27);
    this->closeButton->move(this->width() - 24, 19);
}

void StateToolTip::__setQss()
{
    this->titleLabel->setObjectName(QString("titleLabel"));
    this->contentLabel->setObjectName(QString("contentLabel"));

    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("STATE_TOOL_TIP"), Theme::AUTO);
    
    this->titleLabel->adjustSize();
    this->contentLabel->adjustSize();
}


void StateToolTip::setTitle(QString title)
{
    this->title = title;
    this->titleLabel->setText(title);
    this->titleLabel->adjustSize();
}

void StateToolTip::setContent(QString content)
{
    this->content = content;
    this->contentLabel->setText(content);

    this->contentLabel->adjustSize();
}


void StateToolTip::setState(bool isDone)
{
    this->isDone = isDone;
    this->update();
    if(isDone){
        QTimer::singleShot(1000, this, &StateToolTip::__fadeOut);
    }
}

void StateToolTip::__onCloseButtonClicked()
{
    emit(this->closedSignal());
    this->hide();
}

void StateToolTip::__fadeOut()
{
    this->rotateTimer->stop();
    this->animation->setDuration(200);
    this->animation->setStartValue(1);
    this->animation->setEndValue(0);
    connect(this->animation, &QPropertyAnimation::finished, this, &StateToolTip::deleteLater);
    this->animation->start();
}

void StateToolTip::__rotateTimerFlowSlot()
{
    this->rotateAngle = (this->rotateAngle + this->deltaAngle) % 360;
    this->update();
}

QPoint StateToolTip::getSuitablePos()
{
    for(int i = 0; i < 10; i++){
        int dy = i * (this->height() + 16);
        QPoint pos = QPoint(((QWidget*)this->parent())->width() - this->width() - 24, 50 + dy);
        QWidget *widget = ((QWidget*)this->parent())->childAt(pos + QPoint(2, 2));
        auto _widget = qobject_cast<StateToolTip*>(widget);

        if(_widget != nullptr){
            pos += QPoint(0, this->height() + 16);
        }else{
            break;
        }

        return pos;
    }
}


void StateToolTip::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    Theme theme = !isDarkTheme() ? Theme::DARK : Theme::LIGHT;

    if(!this->isDone){
        painter.translate(19, 18);
        painter.rotate(this->rotateAngle);
        FluentIcon *icon = new FluentIcon();
        icon->setIconName(QString("SYNC"));
        icon->render(&painter, QRect(-8, -8, 16, 16), theme, 0, nullptr);
    }else{
        FluentIcon *icon = new FluentIcon();
        icon->setIconName(QString("COMPLETED"));
        icon->render(&painter, QRect(11, 10, 16, 16), theme, 0, nullptr);
    }
}