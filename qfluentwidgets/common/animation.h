#pragma once

#include <QtCore>
#include <QtGui>
#include <QtWidgets>


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

protected:
   
private:

private slots:

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
public:
    BackgroundColorObject();
    BackgroundColorObject(BackgroundAnimationWidget *parent);
    QColor *backgroundColor();
    void backgroundColor(QColor *color);
private:
    QColor *_backgroundColor;
};