#include "progress_ring.h"

ProgressRing::ProgressRing(QWidget *parent, bool useAni) : ProgressBar(parent, useAni)
{
    this->lightBackgroundColor = QColor(0, 0, 0, 34);
    this->darkBackgroundColor = QColor(255, 255, 255, 34);
    this->_strokeWidth = 6;

    this->setTextVisible(false);
    this->setFixedSize(100, 100);
    Font().setFont(this, 14, QFont::Normal);
}

int ProgressRing::getStrokeWidth()
{
    return this->_strokeWidth;
}

void ProgressRing::setStrokeWidth(int w)
{
    this->_strokeWidth = w;
    this->update();
}

void ProgressRing::_drawText(QPainter *painter, QString text)
{
    painter->setFont(this->font());
    painter->setPen(isDarkTheme() ? Qt::white : Qt::black);
    painter->drawText(this->rect(), Qt::AlignCenter, text);
}

void ProgressRing::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    int cw = this->_strokeWidth;
    int w = qMin(this->height(), this->width()) - cw;
    QRectF rc = QRectF(cw / 2, this->height() / 2 - w / 2, w, w);

    QColor bc = isDarkTheme() ? this->darkBackgroundColor : this->lightBackgroundColor;
    QPen pen = QPen(bc, cw, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);
    painter.drawArc(rc, 0, 360*16);

    if(this->maximum() <= this->minimum()){
        return;
    }

    pen.setColor(this->barColor());
    painter.setPen(pen);
    int degree = this->getVal() / (this->maximum() - this->minimum()) * 360;
    painter.drawArc(rc, 90*16, -degree*16);

    if(this->isTextVisible()){
        this->_drawText(&painter, this->valText());
    }
}


IndeterminateProgressRing::IndeterminateProgressRing(QWidget *parent, bool start) : QProgressBar(parent)
{
    this->lightBackgroundColor = QColor(0, 0, 0, 0);
    this->darkBackgroundColor = QColor(255, 255, 255, 0);
    this->_lightBarColor = QColor();
    this->_darkBarColor = QColor();
    this->_strokeWidth = 6;

    this->_startAngle = -180;
    this->_spanAngle = 0;

    this->startAngleAni1 = new QPropertyAnimation(this, "startAngle", this);
    this->startAngleAni2 = new QPropertyAnimation(this, "startAngle", this);
    this->spanAngleAni1 = new QPropertyAnimation(this, "spanAngle", this);
    this->spanAngleAni2 = new QPropertyAnimation(this, "spanAngle", this);

    this->startAngleAniGroup = new QSequentialAnimationGroup(this);
    this->spanAngleAniGroup = new QSequentialAnimationGroup(this);
    this->aniGroup = new QParallelAnimationGroup(this);

    this->startAngleAni1->setDuration(1000);
    this->startAngleAni1->setStartValue(0);
    this->startAngleAni1->setEndValue(450);

    this->startAngleAni2->setDuration(1000);
    this->startAngleAni2->setStartValue(450);
    this->startAngleAni2->setEndValue(1080);

    this->startAngleAniGroup->addAnimation(this->startAngleAni1);
    this->startAngleAniGroup->addAnimation(this->startAngleAni2);

    this->spanAngleAni1->setDuration(1000);
    this->spanAngleAni1->setStartValue(0);
    this->spanAngleAni1->setEndValue(180);

    this->spanAngleAni2->setDuration(1000);
    this->spanAngleAni2->setStartValue(180);
    this->spanAngleAni2->setEndValue(0);

    this->spanAngleAniGroup->addAnimation(this->spanAngleAni1);
    this->spanAngleAniGroup->addAnimation(this->spanAngleAni2);

    this->aniGroup->addAnimation(this->startAngleAniGroup);
    this->aniGroup->addAnimation(this->spanAngleAniGroup);
    this->aniGroup->setLoopCount(-1);

    this->setFixedSize(80, 80);

    if(start){
        this->start();
    }

}


int IndeterminateProgressRing::getStartAngle()
{
    return this->_startAngle;
}

void IndeterminateProgressRing::setStartAngle(int angle)
{
    this->_startAngle = angle;
    this->update();
}


int IndeterminateProgressRing::getSpanAngle()
{
    return this->_spanAngle;
}


void IndeterminateProgressRing::setSpanAngle(int angle)
{
    this->_spanAngle = angle;
    this->update();
}


int IndeterminateProgressRing::getStrokeWidth()
{
    return this->_strokeWidth;
}

void IndeterminateProgressRing::setStrokeWidth(int w)
{
    this->_strokeWidth = w;
    this->update();
}

void IndeterminateProgressRing::start()
{
    this->_startAngle = 0;
    this->_spanAngle = 0;
    this->aniGroup->start();
}

void IndeterminateProgressRing::stop()
{
    this->aniGroup->stop();
    this->setStartAngle(0);
    this->setSpanAngle(0);
}

QColor IndeterminateProgressRing::lightBarColor()
{
    return this->_lightBarColor.isValid() ? this->_lightBarColor : *(ThemeColor().themeColor());
}

QColor IndeterminateProgressRing::darkBarColor()
{
    return this->_darkBarColor.isValid() ? this->_darkBarColor : *(ThemeColor().themeColor());
}

void IndeterminateProgressRing::setCustomBarColor(QVariant *light, QVariant *dark)
{
    this->_lightBarColor = QColor(light->value<QString>());
    this->_darkBarColor = QColor(dark->value<QString>());
    this->update();
}

void IndeterminateProgressRing::setCustomBackgroundColor(QVariant *light, QVariant *dark)
{
    this->lightBackgroundColor = QColor(light->value<QString>());
    this->darkBackgroundColor = QColor(dark->value<QString>());
    this->update();
}

void IndeterminateProgressRing::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    int cw = this->_strokeWidth;
    int w = qMin(this->height(), this->width()) - cw;
    QRectF rc = QRectF(cw / 2, this->height() / 2 - w / 2, w, w);

    QColor bc = isDarkTheme() ? this->darkBackgroundColor : this->lightBackgroundColor;
    QPen pen = QPen(bc, cw, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);
    painter.drawArc(rc, 0, 360*16);

    pen.setColor(isDarkTheme() ? this->darkBarColor() : this->lightBarColor());
    painter.setPen(pen);

    int startAngle = -this->getStartAngle() + 180;
    painter.drawArc(rc, (startAngle % 360) * 16, -this->getSpanAngle() * 16);
}



