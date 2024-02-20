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
                this->setBackgroundColor(this->_normalBackgroundColor());
            }else{
                this->setBackgroundColor(this->_disabledBackgroundColor());
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
    return this->bgColorObject->backgroundColor();
}

void  BackgroundAnimationWidget::setBackgroundColor(QColor *color)
{
    this->bgColorObject->backgroundColor(color);
}


QColor *BackgroundAnimationWidget::backgroundColor()
{
    return this->getBackgroundColor();
}

BackgroundColorObject::BackgroundColorObject(BackgroundAnimationWidget *parent)
{
    this->_backgroundColor = parent->_normalBackgroundColor();
}




QColor *BackgroundColorObject::backgroundColor()
{
    return this->_backgroundColor;
}

void BackgroundColorObject::backgroundColor(QColor *color)
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


/*
template<typename T>
void FluentAnimationProperObject::registerManager(FluentAnimationProperty propertyType)
{
    if (objects.find(propertyType) == objects.end()) {
        //objects[propertyType] = propertyType;
    }
}

void* FluentAnimationProperObject::create(FluentAnimationProperty propertyType)
{
    if(objects.find(propertyType) == objects.end()){
        throw std::runtime_error("PropertyType has not been registered");
    }
    return this->objects.at(propertyType);
}

*/


//}