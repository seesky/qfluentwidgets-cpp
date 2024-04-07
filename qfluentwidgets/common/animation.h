#pragma once

#include <QtCore/QEasingCurve>
#include <QtCore/QEvent>
#include <QtCore/QDebug>
#include <QtCore/QObject>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QPoint>
#include <QtCore/QPointF>
#include <QtGui/QMouseEvent>
#include <QtGui/QEnterEvent>
#include <QtGui/QColor>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QGraphicsDropShadowEffect>

//namespace Qfw{

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
    Q_PROPERTY(float y READ getY WRITE setY)
public:
    TranslateYAnimation(QWidget *parent, int offset);
    float getY();
    void setY(float y);
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
    void setBackgroundColor(QColor color);
    QColor *backgroundColor();

    bool isHover;
    bool isPressed;
    BackgroundColorObject *bgColorObject;
    QPropertyAnimation *backgroundColorAni; //= 
};

class BackgroundColorObject : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor backgroundColor READ getBackgroundColor WRITE setBackgroundColor)
public:
    BackgroundColorObject(BackgroundAnimationWidget *parent);
    virtual QColor getBackgroundColor();
    virtual void setBackgroundColor(QColor color);
    QColor _backgroundColor;
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


const static QMap<QString, QString> FluentAnimationPropertyMap = {
    {"POSITION", "position"},
    {"SCALE", "scale"},
    {"ANGLE", "angle"},
    {"OPACITY", "opacity"}
};


class FluentAnimationProperObject : public QObject{
    Q_OBJECT
public:
    FluentAnimationProperObject(QWidget *parent);
    int getValue();
    void setValue();
    static FluentAnimationProperObject* create(QString propertyType, QWidget *parent);
};

    
class PositionObject : public FluentAnimationProperObject{
    Q_OBJECT
    Q_PROPERTY(QPoint position READ getValue WRITE setValue)
public:
    PositionObject(QWidget *parent);
    QPoint getValue();
    void setValue(QPoint pos);

    QPoint _position;
};


class ScaleObject : public FluentAnimationProperObject{
    Q_OBJECT
    Q_PROPERTY(float scale READ getValue WRITE setValue)
public:
    ScaleObject(QWidget *parent);
    float getValue();
    void setValue(float scale);

    float _scale;
};



class AngleObject : public FluentAnimationProperObject{
    Q_OBJECT
    Q_PROPERTY(float angle READ getValue WRITE setValue)
public:
    AngleObject(QWidget *parent);
    float getValue();
    void setValue(float angle);

    float _angle;
};


class OpacityObject : public FluentAnimationProperObject{
    Q_OBJECT
    Q_PROPERTY(float opacity READ getValue WRITE setValue)
public:
    OpacityObject(QWidget *parent);
    float getValue();
    void setValue(float opacity);

    float _opacity;
};


class FluentAnimation : public QPropertyAnimation{
    Q_OBJECT
public:
    FluentAnimation(QWidget *parent);
    static QEasingCurve *createBezierCurve(int x1, int y1, int x2, int y2);
    static QEasingCurve *curve();
    void setSpeed(FluentAnimationSpeed speed);
    int speedToDuration(FluentAnimationSpeed speed);
    void startAnimation(QVariant *endValue, QVariant *startValue);
    QVariant *value();
    void setValue(QVariant *value);
    static FluentAnimation *create(FluentAnimationType aniType, QString propertyType, FluentAnimationSpeed speed, QVariant *value, QWidget *parent);

};


class FastInvokeAnimation : public FluentAnimation{
    Q_OBJECT
public:
    FastInvokeAnimation(QWidget *parent) : FluentAnimation(parent){};
    static QEasingCurve *curve();
    int speedToDuration(FluentAnimationSpeed speed);
};


class StrongInvokeAnimation : public FluentAnimation{
    Q_OBJECT
public:
    StrongInvokeAnimation(QWidget *parent) : FluentAnimation(parent){};
    static QEasingCurve *curve();
    int speedToDuration(FluentAnimationSpeed speed);
};



class FastDismissAnimation : public FluentAnimation{
    Q_OBJECT
public:
    FastDismissAnimation(QWidget *parent) : FluentAnimation(parent){};
};


class SoftDismissAnimation : public FluentAnimation{
    Q_OBJECT
public:
    SoftDismissAnimation(QWidget *parent) : FluentAnimation(parent){};
    static QEasingCurve *curve();
    int speedToDuration(FluentAnimationSpeed speed);
};


class PointToPointAnimation : public FluentAnimation{
    Q_OBJECT
public:
    PointToPointAnimation(QWidget *parent) : FluentAnimation(parent){};
    static QEasingCurve *curve();
};


class FadeInOutAnimation : public FluentAnimation{
    Q_OBJECT
public:
    FadeInOutAnimation(QWidget *parent) : FluentAnimation(parent){};
    int speedToDuration(FluentAnimationSpeed speed);
};