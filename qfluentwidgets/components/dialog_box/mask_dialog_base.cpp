#include "mask_dialog_base.h"

MaskDialogBase::MaskDialogBase(QWidget *parent) : QDialog(parent)
{
    this->_hBoxLayout = new QHBoxLayout(this);
    this->windowMask = new QWidget(this);

    this->widget = new QFrame(this);
    this->widget->setObjectName(QString("centerWidget"));
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setGeometry(0, 0, parent->width(), parent->height());

    int c = isDarkTheme() ? 0 : 255;
    this->windowMask->resize(this->size());
    this->windowMask->setStyleSheet(QString("background:rgba(%1, %2, %3, 0.6)").arg(c).arg(c).arg(c));
    this->_hBoxLayout->addWidget(this->widget);
    this->setShadowEffect(60, std::tuple<int, int>(0, 10), QColor(0, 0, 0, 100));

    this->window()->installEventFilter(this);
}


void MaskDialogBase::setShadowEffect(int blurRadius, std::tuple<int,int> offset, QColor color)
{
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this->widget);
    shadowEffect->setBlurRadius(blurRadius);
    shadowEffect->setOffset(std::get<0>(offset), std::get<1>(offset));
    shadowEffect->setColor(color);
    this->widget->setGraphicsEffect(nullptr);
    this->widget->setGraphicsEffect(shadowEffect);
}


void MaskDialogBase::setMaskColor(QColor color)
{
    this->windowMask->setStyleSheet(QString("background:rgba(%1, %2, %3, 0.6)").arg(color.red()).arg(color.green()).arg(color.alpha()));
}

void MaskDialogBase::showEvent(QShowEvent *e)
{
    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(this);
    this->setGraphicsEffect(opacityEffect);
    QPropertyAnimation *opacityAni = new QPropertyAnimation(opacityEffect, "opacity", this);
    opacityAni->setStartValue(0);
    opacityAni->setEndValue(1);
    opacityAni->setDuration(200);
    opacityAni->setEasingCurve(QEasingCurve::InSine);
    connect(opacityAni, &QPropertyAnimation::finished, opacityEffect, &QGraphicsOpacityEffect::deleteLater);
    opacityAni->start();
    QDialog::showEvent(e);
}

void MaskDialogBase::done(int code)
{
    this->widget->setGraphicsEffect(nullptr);
    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(this);
    this->setGraphicsEffect(opacityEffect);
    QPropertyAnimation *opacityAni = new QPropertyAnimation(opacityEffect, "opacity", this);
    opacityAni->setStartValue(1);
    opacityAni->setEndValue(0);
    opacityAni->setDuration(100);
    connect(opacityAni, &QPropertyAnimation::finished, this, [this, code](){ //TODO:特殊关注
        QDialog::done(code);
    });
    opacityAni->start();
}

void MaskDialogBase::resizeEvent(QResizeEvent *e)
{
    this->windowMask->resize(this->size());
}

bool MaskDialogBase::eventFilter(QObject *obj, QEvent *e)
{
    if(obj == this->window()){
        if(e->type() == QEvent::Resize){
            QResizeEvent *re = dynamic_cast<QResizeEvent*>(e);
            this->resize(re->size());
        }
    }

    return QDialog::eventFilter(obj, e);
}