#include "slider.h"

SliderHandle::SliderHandle(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(22, 22);
    this->_radius = 5;
    this->radiusAni = new QPropertyAnimation(this, QString("radius").toUtf8(), this);
    this->radiusAni->setDuration(100);
}

float SliderHandle::radius()
{
    return this->_radius;
}

void SliderHandle::setRadius(float r)
{
    this->_radius = r;
    this->update();
}

void SliderHandle::enterEvent(QEvent *event)
{
    this->_startAni(6.5);
}

void SliderHandle::leaveEvent(QEvent *event)
{
    this->_startAni(5);
}

void SliderHandle::mousePressEvent(QMouseEvent *event)
{
    this->_startAni(4);
    emit this->pressed();
}

void SliderHandle::_startAni(float radius)
{
    this->radiusAni->stop();
    this->radiusAni->setStartValue(this->radius());
    this->radiusAni->setEndValue(radius);
    this->radiusAni->start();
}

void SliderHandle::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::RenderHint::Antialiasing);
    painter.setPen(Qt::PenStyle::NoPen);

    bool isDark = isDarkTheme();
    painter.setPen(QColor(0, 0, 0, isDark ? 90 : 25));
    painter.setBrush(isDark ? QColor(69, 69, 69) : Qt::GlobalColor::white);
    painter.drawEllipse(this->rect().adjusted(1, 1, -1, -1));

    painter.setBrush(*(ThemeColor().themeColor()));
    painter.drawEllipse(QPoint(11, 11), this->radius(), this->radius());
    painter.end();
}


Slider::Slider(QWidget *parent = nullptr) : QSlider(parent)
{
    this->_postInit();
}

Slider::Slider(Qt::Orientation orientation, QWidget *parent = nullptr) : QSlider(orientation, parent)
{
    this->_postInit();
}

void Slider::_postInit()
{
    this->handle = new SliderHandle(this);
    this->_pressedPos = new QPoint();
    this->setOrientation(this->orientation());

    connect(this->handle, &SliderHandle::pressed, this, &QSlider::sliderPressed);
    connect(this->handle, &SliderHandle::released, this, &QSlider::sliderReleased);
    connect(this, &QSlider::valueChanged, this, &Slider::_adjustHandlePos);
}


void Slider::setOrientation(Qt::Orientation orientation)
{
    QSlider::setOrientation(orientation);
    if(orientation == Qt::Orientation::Horizontal){
        this->setMinimumHeight(22);
    }else{
        this->setMinimumWidth(22);
    }
}

void Slider::mousePressEvent(QMouseEvent *event)
{
    this->_pressedPos = new QPoint(event->pos());
    this->setValue(this->_posToValue(new QPoint(event->pos())));
    int v = this->value();
    emit this->clicked(this->value());
}

void Slider::mouseMoveEvent(QMouseEvent *ev)
{
    this->setValue(this->_posToValue(new QPoint(ev->pos())));
    this->_pressedPos = new QPoint(ev->pos());
    emit this->sliderMoved((this->value()));
}

int Slider::grooveLength()
{
    int l = this->orientation() == Qt::Orientation::Horizontal ? this->width() : this->height();
    return l - this->handle->width();
}

void Slider::_adjustHandlePos()
{
    float total = qMax(this->maximum() - this->minimum(), 1);
    float delta = int((this->value() - this->minimum()) / total * this->grooveLength());

    if(this->orientation() == Qt::Orientation::Vertical){
        this->handle->move(0, delta);
    }else{
        this->handle->move(delta, 0);
    }
}

float Slider::_posToValue(QPoint *pos)
{
    float pd = this->handle->width() / 2;
    float gs = qMax(this->grooveLength(), 1);
    float v = this->orientation() == Qt::Orientation::Horizontal ? pos->x() : pos->y();

    int maximum = this->maximum();
    int minimum =  this->minimum();

    int returnValue = int((v - pd) / gs * (this->maximum() - this->minimum()) + this->minimum());
    return returnValue;
}


void Slider::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::RenderHint::Antialiasing);
    painter.setPen(Qt::PenStyle::NoPen);
    painter.setBrush(isDarkTheme() ? QColor(255, 255, 255, 115) : QColor(0, 0, 0, 100));

    if(this->orientation() == Qt::Orientation::Horizontal){
        this->_drawHorizonGroove(&painter);
    }else{
        this->_drawVerticalGroove(&painter);
    }
}

//绘制水平槽
void Slider::_drawHorizonGroove(QPainter *painter)
{
    float w = this->width();
    float r = this->handle->width() / 2;

    painter->drawRoundedRect(QRectF(r, r - 2, w - r * 2, 4), 2, 2);

    if(this->maximum() - this->minimum() == 0){
        return;
    }

    painter->setBrush(*(ThemeColor().themeColor()));

    int selfValue = this->value();
    int selfMinimum = this->minimum();
    int selfMaximum = this->maximum();

    float aw = (float(this->value()) - float(this->minimum())) / (float(this->maximum()) - float(this->minimum())) * (w - r * 2);
    //qDebug() << aw;
    painter->drawRoundedRect(QRectF(r, r - 2, aw, 4), 2, 2);
}


void Slider::_drawVerticalGroove(QPainter *painter)
{
    float h = this->height();
    float r = this->handle->width() / 2;

    painter->drawRoundedRect(QRectF(r - 2, r, 4, h - 2 * r), 2, 2);

    if(this->maximum() - this->minimum() == 0){
        return;
    }

    painter->setBrush(*(ThemeColor().themeColor()));
    float ah = (float(this->value()) - float(this->minimum())) / (float(this->maximum()) - float(this->minimum())) * (h - r * 2);
    painter->drawRoundedRect(QRectF(r - 2, r, 4, ah), 2, 2);
}

void Slider::resizeEvent(QResizeEvent *event)
{
    this->_adjustHandlePos();
}

void ClickableSlider::mousePressEvent(QMouseEvent *event)
{
    QSlider::mousePressEvent(event);

    int value;
    if(this->orientation() == Qt::Horizontal){
        value = int(event->pos().x() / this->width() * this->maximum());
    }else{
        value = int((this->height() - event->pos().y()) / this->height() * this->maximum());
    }

    this->setValue(value);
    emit this->clicked(this->value());
}


HollowHandleStyle::HollowHandleStyle(QMap<QString, QVariant*> *config, QStyle *style = nullptr) : QProxyStyle(style)
{
    QMap<QString, QVariant*> *_config;
    this->config = new QMap<QString, QVariant*>();
    this->config->insert(QString("groove.height"), new QVariant(QVariant::fromValue<int>(3)));
    this->config->insert(QString("sub-page.color"), new QVariant(QVariant::fromValue<QColor>(QColor(255, 255, 255))));
    this->config->insert(QString("add-page.color"), new QVariant(QVariant::fromValue<QColor>(QColor(255, 255, 255, 64))));
    this->config->insert(QString("handle.color"), new QVariant(QVariant::fromValue<QColor>(QColor(255, 255, 255))));
    this->config->insert(QString("handle.ring-width"), new QVariant(QVariant::fromValue<int>(4)));
    this->config->insert(QString("handle.hollow-radius"), new QVariant(QVariant::fromValue<int>(6)));
    this->config->insert(QString("handle.margin"), new QVariant(QVariant::fromValue<int>(4)));

    _config = !config->isEmpty() ? config : new QMap<QString, QVariant*>();
    this->config->unite(*_config);

    float w = this->config->value(QString("handle.margin"))->value<int>() + 
        this->config->value(QString("handle.ring-width"))->value<int>() + 
        this->config->value(QString("handle.hollow-radius"))->value<int>();
    
    this->config->insert(QString("handle.size"), new QVariant(QVariant::fromValue<QSize>(QSize(2*w, 2*w))));
}

QRect HollowHandleStyle::subControlRect(ComplexControl cc, const QStyleOptionComplex *opt, SubControl sc, const QWidget *widget) const
{
    const QStyleOptionSlider * _opt = qstyleoption_cast<const QStyleOptionSlider *>(opt);

    if(_opt != nullptr){
        if(cc != this->CC_Slider ||  _opt->orientation != Qt::Horizontal || sc == this->SC_SliderTickmarks){
            return QProxyStyle::subControlRect(cc, opt, sc, widget);
        }

        QRect rect = opt->rect;

        if(sc == this->SC_SliderGroove){
            int h = this->config->value(QString("groove.height"))->value<int>();
            QRectF grooveRect = QRectF(0, (rect.height() - h) / 2, rect.width(), h);
            return grooveRect.toRect();
        }else if(sc == this->SC_SliderHandle){
            QSize size = this->config->value(QString("handle.size"))->value<QSize>();
            int x = this->sliderPositionFromValue(_opt->minimum, _opt->maximum, _opt->sliderPosition, rect.width());

            x *= (rect.width() - size.width()) / rect.width();
            QRectF sliderRect = QRectF(x, 0, size.width(), size.height());
            return sliderRect.toRect();
        }
    }else{
        return QProxyStyle::subControlRect(cc, opt, sc, widget);
    }
}


void HollowHandleStyle::drawComplexControl(ComplexControl cc, const QStyleOptionComplex *opt, QPainter *painter, const QWidget *widget = nullptr) const
{

    const QStyleOptionSlider * _opt = qstyleoption_cast<const QStyleOptionSlider *>(opt);

    if(_opt != nullptr){
        if(cc != this->CC_Slider || ((QStyleOptionSlider *)opt)->orientation != Qt::Horizontal){
            return QProxyStyle::drawComplexControl(cc, opt, painter, widget);
        }

        QRect grooveRect = this->subControlRect(cc, opt, this->SC_SliderGroove, widget);
        QRect handleRect = this->subControlRect(cc, opt, this->SC_SliderHandle, widget);
        painter->setRenderHints(QPainter::Antialiasing);
        painter->setPen(Qt::NoPen);

        painter->save();
        painter->translate(grooveRect.topLeft());

        int w = handleRect.x() - grooveRect.x();
        int h = this->config->value(QString("groove.height"))->value<int>();
        painter->setBrush(this->config->value(QString("sub-page.color"))->value<QColor>());
        painter->drawRect(0, 0, w, h);

        int x = w + this->config->value(QString("handle.size"))->value<QSize>().width();
        painter->setBrush(this->config->value(QString("add-page.color"))->value<QColor>());
        painter->drawRect(x, 0, grooveRect.width() - w, h);
        painter->restore();

        int ringWidth = this->config->value(QString("handle.ring-width"))->value<int>();
        int hollowRadius = this->config->value(QString("handle.hollow-radius"))->value<int>();
        int radius = ringWidth + hollowRadius;

        QPainterPath *path = new QPainterPath();
        path->moveTo(0, 0);
        QPoint center = handleRect.center() - QPoint(1, 1);
        path->addEllipse(center, radius, radius);
        path->addEllipse(center, hollowRadius, hollowRadius);

        QColor handleColor = this->config->value(QString("handle.color"))->value<QColor>();
        handleColor.setAlpha(opt->activeSubControls != this->SC_SliderHandle ? 255 : 153);
        painter->setBrush(handleColor);
        painter->drawPath(*path);

        if(((QSlider *)widget)->isSliderDown()){
            handleColor.setAlpha(255);
            painter->setBrush(handleColor);
            painter->drawEllipse(handleRect);
        }

        painter->end();
    }else{
        return QProxyStyle::drawComplexControl(cc, opt, painter, widget);
    }
}
