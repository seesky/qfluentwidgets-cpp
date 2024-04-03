#include "animation.h"

//namespace Qfw{

AnimationBase::AnimationBase(){}

AnimationBase::AnimationBase(QWidget *parent)
{   
    parent->installEventFilter(this);
}

AnimationBase::~AnimationBase(){}


void AnimationBase::_onLeave(QEvent *e){}

void AnimationBase::_onHover(QEnterEvent *e){}

void AnimationBase::_onPress(QMouseEvent *e){};

void AnimationBase::_onRelease(QMouseEvent *e){};

bool AnimationBase::eventFilter(QObject *obj, QEvent *e)
{
    if(obj == parent())
    {
        if(e->type() == QEvent::MouseButtonPress){
            _onPress(dynamic_cast<QMouseEvent*>(e));
        }else if(e->type() == QEvent::MouseButtonRelease){
            _onRelease(dynamic_cast<QMouseEvent*>(e));
        }else if(e->type() == QEvent::Enter){
            _onHover(dynamic_cast<QEnterEvent*>(e));
        }else if(e->type() == QEvent::Leave){
            _onLeave(e);
        }
    }

    return eventFilter(obj, e);
}


TranslateYAnimation::TranslateYAnimation(QWidget *parent, int offset = 2)
{
    this->_y = 0;
    this->maxOffset = offset;
    this->ani = new QPropertyAnimation(this, "y", this);
}

float TranslateYAnimation::getY()
{
    return this->_y;
}

void TranslateYAnimation::setY(float y)
{
    this->_y = y;
    parentWidget()->update();
    emit(this->valueChanged(y));
}


void TranslateYAnimation::_onPress(QMouseEvent *e)
{
    ani->setEndValue(this->maxOffset);
    ani->setEasingCurve(QEasingCurve::OutQuad);
    ani->setDuration(150);
    ani->start();
}

void TranslateYAnimation::_onRelease(QMouseEvent *e)
{
    ani->setEndValue(0);
    ani->setDuration(500);
    ani->setEasingCurve(QEasingCurve::OutElastic);
    ani->start();
}

BackgroundAnimationWidget::BackgroundAnimationWidget()
{
    this->isHover = false;
    this->isPressed = false;
    this->bgColorObject = new BackgroundColorObject(this);
    this->backgroundColorAni = new QPropertyAnimation(this->bgColorObject, "backgroundColor", this);
    this->backgroundColorAni->setDuration(120);
    this->installEventFilter(this);
    //TOOD: qconfig.themeChanged.connect(self._updateBackgroundColor)
}

BackgroundAnimationWidget::BackgroundAnimationWidget(int *args, char **kwargs)
{
    this->isHover = false;
    this->isPressed = false;
    this->bgColorObject = new BackgroundColorObject(this);
    this->backgroundColorAni = new QPropertyAnimation(this->bgColorObject, "backgroundColor", this);
    this->backgroundColorAni->setDuration(120);
    this->installEventFilter(this);
    //TOOD: qconfig.themeChanged.connect(self._updateBackgroundColor)
}

bool BackgroundAnimationWidget::eventFilter(QObject *obj, QEvent *e)
{
    if(obj == this)
    {
        if(e->type() == QEvent::Type::EnabledChange)
        {
            if(this->isEnabled())
            {
                this->setBackgroundColor(QColor(*(this->_normalBackgroundColor())));
            }else{
                this->setBackgroundColor(QColor(*(this->_disabledBackgroundColor())));
            }
        }
    }
    return QWidget::eventFilter(obj, e);
}

void BackgroundAnimationWidget::mousePressEvent(QMouseEvent *e)
{
    this->isPressed = true;
    this->_updateBackgroundColor();
    QWidget::mousePressEvent(e);
}

void BackgroundAnimationWidget::mouseReleaseEvent(QMouseEvent *e)
{
    this->isPressed = false;
    this->_updateBackgroundColor();
    QWidget::mouseReleaseEvent(e);
}

void BackgroundAnimationWidget::enterEvent(QEnterEvent *e)
{
    this->isHover = true;
    this->_updateBackgroundColor();
}

void BackgroundAnimationWidget::leaveEvent(QEvent *e)
{
    this->isHover = false;
    this->_updateBackgroundColor();
}

void BackgroundAnimationWidget::focusInEvent(QFocusEvent *e)
{
    QWidget::focusInEvent(e);
    this->_updateBackgroundColor();
}

QColor *BackgroundAnimationWidget::_normalBackgroundColor()
{
    QColor *color = new QColor(0, 0, 0, 0);
    return color;
}

QColor *BackgroundAnimationWidget::_hoverBackgroundColor()
{
    return this->_normalBackgroundColor();
}

QColor *BackgroundAnimationWidget::_pressedBackgroundColor()
{
    return this->_normalBackgroundColor();
}

QColor *BackgroundAnimationWidget::_focusInBackgroundColor()
{
    return this->_normalBackgroundColor();
}


QColor *BackgroundAnimationWidget::_disabledBackgroundColor()
{
    return this->_normalBackgroundColor();
}


void BackgroundAnimationWidget::_updateBackgroundColor()
{
    QColor *color;
    if(!this->isEnabled())
    {
        color = this->_disabledBackgroundColor();
    }else if(dynamic_cast<QLineEdit*>(this) != nullptr && this->hasFocus()){
        color = this->_focusInBackgroundColor();
    }else if(this->isPressed){
        color = this->_pressedBackgroundColor();
    }else if(this->isHover){
        color = this->_normalBackgroundColor();
    }

    this->backgroundColorAni->stop();
    this->backgroundColorAni->setEndValue(*color);
    this->backgroundColorAni->start();

}

QColor *BackgroundAnimationWidget::getBackgroundColor()
{
    return new QColor(this->bgColorObject->getBackgroundColor());
}

void  BackgroundAnimationWidget::setBackgroundColor(QColor color)
{
    this->bgColorObject->setBackgroundColor(color);
}


QColor *BackgroundAnimationWidget::backgroundColor()
{
    return this->getBackgroundColor();
}

BackgroundColorObject::BackgroundColorObject(BackgroundAnimationWidget *parent) : QWidget(parent)
{
    this->_backgroundColor = QColor(*(parent->_normalBackgroundColor()));
}




QColor BackgroundColorObject::getBackgroundColor()
{
    return this->_backgroundColor;
}

void BackgroundColorObject::setBackgroundColor(QColor color)
{
    this->_backgroundColor = color;
    QWidget::update();
}



DropShadowAnimation::DropShadowAnimation(QWidget *parent, QColor *normalColor, QColor *hoverColor)
{
    this->parent = parent;
    this->normalColor = normalColor;
    this->hoverColor = hoverColor;
    this->offset = new QPoint(0, 0);
    this->blurRadius = 38;
    this->isHover = false;
    this->shadowEffect = new QGraphicsDropShadowEffect(this);
    this->shadowEffect->setColor(*this->normalColor);
    parent->installEventFilter(this);
    
}

DropShadowAnimation::~DropShadowAnimation(){}

void DropShadowAnimation::setBlurRadius(int radius)
{
    this->blurRadius = radius;
}

void DropShadowAnimation::setOffset(int dx, int dy)
{
    this->offset = new QPoint(dx, dy);
}

void DropShadowAnimation::setNormalColor(QColor *color)
{
    this->normalColor = color;
}

void DropShadowAnimation::setHoverColor(QColor *color)
{
    this->hoverColor = color;
}

void DropShadowAnimation::setColor(QColor *color){}

QGraphicsDropShadowEffect * DropShadowAnimation::_createShadowEffect()
{
    this->shadowEffect = new QGraphicsDropShadowEffect(this);
    this->shadowEffect->setOffset(*this->offset);
    this->shadowEffect->setBlurRadius(this->blurRadius);
    this->shadowEffect->setColor(*this->normalColor);
    setTargetObject(this->shadowEffect);
    setStartValue(this->shadowEffect->color());
    setPropertyName("color");
    setDuration(150);
    return this->shadowEffect;
}


bool DropShadowAnimation::eventFilter(QObject *obj, QEvent *e)
{
    if(obj == this->parent && this->parent->isEnabled())
    {
        if(e->type() == QEvent::Enter)
        {
            this->isHover = true;

            if(this->state() != QPropertyAnimation::State::Running)
            {
                this->parent->setGraphicsEffect(this->_createShadowEffect());
            }

            this->setEndValue(*this->hoverColor);
            this->start();
        }else if(e->type() == QEvent::Type::Leave || e->type() == QEvent::Type::MouseButtonPress){
            this->isHover = false;
            if(this->parent->graphicsEffect())
            {
                //TODO:self.finished.connect(self._onAniFinished)
                connect(this, &QPropertyAnimation::finished, this, &DropShadowAnimation::_onAniFinished);
                this->setEndValue(*this->normalColor);
                this->start();
            }
        }
    }
}


void DropShadowAnimation::_onAniFinished()
{
    this->finished();
    this->shadowEffect = nullptr;
    this->parent->setGraphicsEffect(nullptr);
}



FluentAnimationProperObject::FluentAnimationProperObject(QWidget *parent) : QObject(parent)
{

}


int FluentAnimationProperObject::getValue()
{
    return 0;
}


void FluentAnimationProperObject::setValue()
{

}


class AngleObject;
class OpacityObject;
class PositionObject;
class ScaleObject;
FluentAnimationProperObject* FluentAnimationProperObject::create(QString propertyType, QWidget *parent)
{

    if(propertyType == QString("POSITION")){
        return new PositionObject(parent);
    }else if(propertyType == QString("SCALE")){
        return new ScaleObject(parent);
    }else if(propertyType == QString("ANGLE")){
        return new AngleObject(parent);
    }else if(propertyType == QString("OPACITY")){
        return new OpacityObject(parent);
    }else{
        return nullptr;
    }
}



PositionObject::PositionObject(QWidget *parent) : FluentAnimationProperObject(parent)
{
    this->_position = QPoint();
}

QPoint PositionObject::getValue()
{
    return this->_position;
}

void PositionObject::setValue(QPoint pos)
{
    this->_position = pos;
    ((QWidget*)this->parent())->update();
}


ScaleObject::ScaleObject(QWidget *parent) : FluentAnimationProperObject(parent)
{
    this->_scale = 1;
}

float ScaleObject::getValue()
{
    return this->_scale;
}


void ScaleObject::setValue(float scale)
{
    this->_scale = scale;
    ((QWidget *)this->parent())->update();
}


AngleObject::AngleObject(QWidget *parent) : FluentAnimationProperObject(parent)
{
    this->_angle = 0;
}

float AngleObject::getValue()
{
    return this->_angle;
}

void AngleObject::setValue(float angle)
{
    this->_angle = angle;
    ((QWidget *)this->parent())->update();
}


OpacityObject::OpacityObject(QWidget *parent) : FluentAnimationProperObject(parent)
{
    this->_opacity = 0;
}


float OpacityObject::getValue()
{
    return this->_opacity;
}

void OpacityObject::setValue(float opacity)
{
    this->_opacity = opacity;
    ((QWidget *)this->parent())->update();
}




FluentAnimation::FluentAnimation(QWidget *parent) : QPropertyAnimation(parent)
{
    this->setSpeed(FluentAnimationSpeed::FAST);
    this->setEasingCurve(*(this->curve()));
}

QEasingCurve *FluentAnimation::createBezierCurve(int x1, int y1, int x2, int y2)
{
    QEasingCurve *curve = new QEasingCurve(QEasingCurve::BezierSpline);
    curve->addCubicBezierSegment(QPointF(x1, y1), QPointF(x2, y2), QPointF(1, 1));
    return curve;
}


QEasingCurve *FluentAnimation::curve()
{
    return FluentAnimation::createBezierCurve(0, 0, 1, 1);
}

void FluentAnimation::setSpeed(FluentAnimationSpeed speed)
{
    this->setDuration(this->speedToDuration(speed));
}


int FluentAnimation::speedToDuration(FluentAnimationSpeed speed)
{
    return 100;
}


void FluentAnimation::startAnimation(QVariant *endValue, QVariant *startValue = nullptr)
{
    this->stop();

    if(!startValue->isValid()){
        this->setStartValue(*(this->value()));
    }else{
        this->setStartValue(*startValue);
    }

    this->setEndValue(*endValue);
    this->start();
}


QVariant *FluentAnimation::value()
{
    auto positionObject = qobject_cast<PositionObject*>(this->targetObject());
    auto scaleObject = qobject_cast<ScaleObject*>(this->targetObject());
    auto angleObject = qobject_cast<AngleObject*>(this->targetObject());
    auto opacityObject = qobject_cast<OpacityObject*>(this->targetObject());


    if(positionObject != nullptr){
        return new QVariant(QVariant::fromValue<QPoint>(positionObject->getValue()));
    }
    
    if(scaleObject != nullptr){
        return new QVariant(QVariant::fromValue<float>(scaleObject->getValue()));
    }

    if(angleObject != nullptr){
        return new QVariant(QVariant::fromValue<float>(angleObject->getValue()));
    }

    if(opacityObject != nullptr){
        return new QVariant(QVariant::fromValue<float>(opacityObject->getValue()));
    }
}


void FluentAnimation::setValue(QVariant *value)
{
    auto positionObject = qobject_cast<PositionObject*>(this->targetObject());
    auto scaleObject = qobject_cast<ScaleObject*>(this->targetObject());
    auto angleObject = qobject_cast<AngleObject*>(this->targetObject());
    auto opacityObject = qobject_cast<OpacityObject*>(this->targetObject());


    if(positionObject != nullptr){
        positionObject->setValue(value->value<QPoint>());
    }
    
    if(scaleObject != nullptr){
        scaleObject->setValue(value->value<float>());
    }

    if(angleObject != nullptr){
        angleObject->setValue(value->value<float>());
    }

    if(opacityObject != nullptr){
        opacityObject->setValue(value->value<float>());
    }
}



FluentAnimation *FluentAnimation::create(FluentAnimationType aniType, QString propertyType, FluentAnimationSpeed speed = FluentAnimationSpeed::FAST, QVariant *value= nullptr, QWidget *parent = nullptr)
{
    FluentAnimationProperObject *obj = FluentAnimationProperObject::create(propertyType, parent);
    FluentAnimation *ani;

    switch (aniType)
    {
        case FluentAnimationType::FADE_IN_OUT:
            ani = new FadeInOutAnimation(parent);
            break;
        case FluentAnimationType::FAST_DISMISS:
            ani = new FastDismissAnimation(parent);
            break;
        case FluentAnimationType::FAST_INVOKE:
            ani = new FastInvokeAnimation(parent);
            break;
        case FluentAnimationType::POINT_TO_POINT:
            ani = new PointToPointAnimation(parent);
            break;
        case FluentAnimationType::SOFT_DISMISS:
            ani = new SoftDismissAnimation(parent);
            break;
        case FluentAnimationType::STRONG_INVOKE:
            ani = new StrongInvokeAnimation(parent);
            break;
        default:
            ani = nullptr;
            break;
    }

    if(ani != nullptr){
        ani->setSpeed(speed);
        ani->setTargetObject(obj);
        ani->setPropertyName(FluentAnimationPropertyMap.value(propertyType).toUtf8());

        if(value != nullptr){
            ani->setValue(value);
        }

        return ani;
    }

}


QEasingCurve *FastInvokeAnimation::curve()
{
    return FastInvokeAnimation::createBezierCurve(0, 0, 0, 1);
}

int FastInvokeAnimation::speedToDuration(FluentAnimationSpeed speed)
{
    if(speed == FluentAnimationSpeed::FAST){
        return 187;
    }

    if(speed == FluentAnimationSpeed::MEDIUM){
        return 333;
    }

    return 500;
}



QEasingCurve *StrongInvokeAnimation::curve()
{
    return StrongInvokeAnimation::createBezierCurve(0.13, 1.62, 0, 0.92);
}

int StrongInvokeAnimation::speedToDuration(FluentAnimationSpeed speed)
{
    return 667;
}


QEasingCurve *SoftDismissAnimation::curve()
{
    return StrongInvokeAnimation::createBezierCurve(1, 0, 1, 1);
}

int SoftDismissAnimation::speedToDuration(FluentAnimationSpeed speed)
{
    return 167;
}


QEasingCurve *PointToPointAnimation::curve()
{
    return StrongInvokeAnimation::createBezierCurve(0.55, 0.55, 0, 1);
}


int FadeInOutAnimation::speedToDuration(FluentAnimationSpeed speed)
{
    return 83;
}