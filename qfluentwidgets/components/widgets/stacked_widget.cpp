#include "stacked_widget.h"

OpacityAniStackedWidget::OpacityAniStackedWidget(QWidget *parent) : QStackedWidget(parent)
{
    this->__nextIndex = 0;
    this->__effects = QList<QGraphicsOpacityEffect *>();
    this->__anis = QList<QPropertyAnimation *>();
}


void OpacityAniStackedWidget::addWidget(QWidget *w)
{
    QStackedWidget::addWidget(w);

    this->effect = new QGraphicsOpacityEffect(this);
    effect->setOpacity(1);
    this->ani = new QPropertyAnimation(effect, "opacity", this);
    this->ani->setDuration(220);
    connect(this->ani, &QPropertyAnimation::finished, this, &OpacityAniStackedWidget::__onAniFinished);
    this->__anis.append(ani);
    this->__effects.append(effect);
    w->setGraphicsEffect(effect);
}



void OpacityAniStackedWidget::setCurrentIndex(int index)
{
    int index_ = this->currentIndex();
    if(index == index_){
        return;
    }

    if(index > index_){
        QPropertyAnimation *ani = this->__anis.at(index);
        ani->setStartValue(0);
        ani->setEndValue(1);
        QStackedWidget::setCurrentIndex(index);
    }else{
        QPropertyAnimation *ani = this->__anis.at(index_);
        ani->setStartValue(1);
        ani->setEndValue(0);
    }

    this->widget(index_)->show();
    this->__nextIndex = index;
    ani->start();
}


void OpacityAniStackedWidget::setCurrentWidget(QWidget *w)
{   
    this->setCurrentIndex(this->indexOf(w));
}

void OpacityAniStackedWidget::__onAniFinished()
{
    QStackedWidget::setCurrentIndex(this->__nextIndex);
}


PopUpAniInfo::PopUpAniInfo(QWidget *widget, int deltaX, int deltaY, QPropertyAnimation *ani)
{
    this->widget = widget;
    this->deltaX = deltaX;
    this->deltaY = deltaY;
    this->ani = ani;
}



PopUpAniStackedWidget::PopUpAniStackedWidget(QWidget *parent) : QStackedWidget(parent)
{
    this->aniInfos = QList<PopUpAniInfo*>();
    //this->_nextIndex = nullptr;
    this->_ani = nullptr;
}


void PopUpAniStackedWidget::addWidget(QWidget *widget, int deltaX = 0, int deltaY = 76)
{
    QStackedWidget::addWidget(widget);

    this->aniInfos.append(new PopUpAniInfo(widget, deltaX, deltaY, new QPropertyAnimation(widget, "pos")));
}


void PopUpAniStackedWidget::setCurrentIndex(int index, bool needPopOut = false, bool showNextWidgetDirectly = true, int duration = 250, QEasingCurve easingCurve = QEasingCurve::OutQuad)
{
    if(index < 0 || index >= this->count()){
        throw std::invalid_argument(QString("The index %1 is illegal.").arg(index).toUtf8());
    }

    if(index == this->currentIndex()){
        return;
    }

    if(this->_ani != nullptr && this->_ani->state() == QAbstractAnimation::Running){
        this->_ani->stop();
        this->__onAniFinished();
    }

    this->_nextIndex = index;

    PopUpAniInfo *nextAniInfo = this->aniInfos.at(index);
    PopUpAniInfo *currentAniInfo = this->aniInfos.at(this->currentIndex());

    QWidget *currentWidget = this->currentWidget();
    QWidget *nextWidget = nextAniInfo->widget;
    QPropertyAnimation *ani = needPopOut ? currentAniInfo->ani : nextAniInfo->ani;
    this->_ani = ani;

    if(needPopOut){
        int _deltaX = currentAniInfo->deltaX;
        int _deltaY = currentAniInfo->deltaY;

        QPoint pos = currentWidget->pos() + QPoint(_deltaX, _deltaY);
        this->__setAnimation(ani, currentWidget->pos(), pos, duration, easingCurve);
        nextWidget->setVisible(showNextWidgetDirectly);
    }else{
        int _deltaX = nextAniInfo->deltaX;
        int _deltaY = nextAniInfo->deltaY;
        QPoint pos = nextWidget->pos() + QPoint(_deltaX, _deltaY);
        this->__setAnimation(ani, pos, QPoint(nextWidget->x(), 0), duration, easingCurve);
        QStackedWidget::setCurrentIndex(index);
    }

    connect(ani, &QPropertyAnimation::finished, this, &PopUpAniStackedWidget::__onAniFinished);
    ani->start();
    emit(this->aniStart());
}



void PopUpAniStackedWidget::setCurrentWidget(QWidget *widget, bool needPopOut = false, bool showNextWidgetDirectly = false, int duration = 250, QEasingCurve easingCurve = QEasingCurve::OutQuad)
{
    this->setCurrentIndex(this->indexOf(widget), needPopOut, showNextWidgetDirectly, duration, easingCurve);
}


void PopUpAniStackedWidget::__setAnimation(QPropertyAnimation *ani, QPoint startValue, QPoint endValue, int duration, QEasingCurve easingCurve)
{
    ani->setEasingCurve(easingCurve);
    ani->setStartValue(startValue);
    ani->setEndValue(endValue);
    ani->setDuration(duration);
}


void PopUpAniStackedWidget::__onAniFinished()
{
    this->_ani->disconnect();
    QStackedWidget::setCurrentIndex(this->_nextIndex);
    emit(this->aniFinished());
}