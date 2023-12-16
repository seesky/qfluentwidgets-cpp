#pragma once

#include <QtCore>
#include <QtGui>
#include <QtWidgets>

namespace Qfw{

class AnimationBase : public QWidget
{
    Q_OBJECT
public:
    AnimationBase();
    AnimationBase(QWidget *parent);
    ~AnimationBase();
    void _onHover(QEnterEvent *e);
    void _onLeave(QEvent *e);
    void _onPress(QMouseEvent *e);
    void _onRelease(QMouseEvent *e);
    bool eventFilter(QObject *obj, QEvent *e);
};


class TranslateYAnimation : public AnimationBase
{
    Q_OBJECT
public:
    TranslateYAnimation(QWidget *parent, int offset);
    float y();
    void y(float y);
    void _onPress(QMouseEvent *e);
    void _onRelease(QMouseEvent *e);

private:
    float _y;
    float maxOffset;
    QPropertyAnimation *ani;
signals:
    void valueChanged(float value);
};

class BackgroundColorObject;
class BackgroundAnimationWidget : public QWidget
{
    Q_OBJECT
public:
    BackgroundAnimationWidget();
    BackgroundAnimationWidget(int *args, char **kwargs);
    bool eventFilter(QObject *obj, QEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void enterEvent(QEnterEvent *e);
    void leaveEvent(QEvent *e);
    void focusInEvent(QFocusEvent *e);
    QColor *_normalBackgroundColor();
    QColor *_hoverBackgroundColor();
    QColor *_pressedBackgroundColor();
    QColor *_focusInBackgroundColor();
    QColor *_disabledBackgroundColor();
    void _updateBackgroundColor();
    QColor *getBackgroundColor();
    void setBackgroundColor(QColor *color);
    QColor *backgroundColor();

private:
    bool isHover;
    bool isPressed;
    BackgroundColorObject *bgColorObject;
    QPropertyAnimation *backgroundColorAni; //= 
};

class BackgroundColorObject : public QWidget
{
    Q_OBJECT
public:
    BackgroundColorObject();
    BackgroundColorObject(BackgroundAnimationWidget *parent);
    QColor *backgroundColor();
    void backgroundColor(QColor *color);
private:
    QColor *_backgroundColor;
};

class DropShadowAnimation : public QPropertyAnimation
{
    Q_OBJECT
public:
    DropShadowAnimation();
    DropShadowAnimation(QWidget *parent, QColor *normal, QColor *hover);
    ~DropShadowAnimation();

    void setBlurRadius(int radius);
    void setOffset(int dx, int dy);
    void setNormalColor(QColor *color);
    void setHoverColor(QColor *color);
    void setColor(QColor *color);
    QGraphicsDropShadowEffect *_createShadowEffect();
    bool eventFilter(QObject *obj, QEvent *e);
    void _onAniFinished();
private:
    QWidget *parent;
    int radius;
    int blurRadius;
    bool isHover;
    QPoint *offset;
    QColor *normalColor;
    QColor *hoverColor;
    QGraphicsDropShadowEffect *shadowEffect;
};


enum class FluentAnimationSpeed{
    FAST = 0,
    MEDIUM = 1,
    SLOW = 2
};


enum class FluentAnimationType{
    FAST_INVOKE = 0,
    STRONG_INVOKE = 1,
    FAST_DISMISS = 2,
    SOFT_DISMISS = 3,
    POINT_TO_POINT = 4,
    FADE_IN_OUT = 5
};

enum class FluentAnimationProperty{
    POSITION = 0,
    SCALE = 1,
    ANGLE = 2,
    OPACITY = 3
};

/*
class FluentAnimationProperObject : public QObject{
    Q_OBJECT
public:
    FluentAnimationProperObject();
    int getValue();
    void setValue();
    //FluentAnimationProperObject::registerManager<MyClass1>("Class1");
    //MyClass1* obj1 = reinterpret_cast<MyClass1*>(Manager::objects["Class1"]);
    template<typename T>
    void registerManager(FluentAnimationProperty propertyType);
    void* create(FluentAnimationProperty propertyType);

private:
    std::map<FluentAnimationProperty, void*> objects;
};
*/
    
}