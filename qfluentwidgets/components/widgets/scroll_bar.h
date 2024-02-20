#pragma once


#include <QtCore/QEvent>
#include <QtCore/QEasingCurve>
#include <QtCore/Qt>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QRectF>
#include <QtCore/QTimer>
#include <QtCore/QPoint>
#include <QtCore/QObject>
#include <QtGui/QPainter>
#include <QtGui/QColor>
#include <QtGui/QMouseEvent>
#include <QtWidgets/QWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QAbstractScrollArea>
#include <QtWidgets/QGraphicsOpacityEffect>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QApplication>
#include <QtWidgets/QAbstractItemView>
#include <QtWidgets/QListView>
#include "../../common/icon.h"
#include "../../common/style_sheet.h"
#include "../../common/smooth_scroll.h"

/*
class SmoothScrollDelegat;

class MQAbstractScrollArea : public QAbstractScrollArea{
    Q_OBJECT
public:
    MQAbstractScrollArea(QWidget *parent) : QAbstractScrollArea(parent){};
    void setVerticalScrollBarPolicy(Qt::ScrollBarPolicy policy);
    void setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy policy);
};
*/


class ArrowButton : public QToolButton{
    Q_OBJECT
public:
    ArrowButton(FluentIcon *icon, QWidget *parent);
    void paintEvent(QPaintEvent *e);
    FluentIcon *_icon;
private:
};

class ScrollBarGroove : public QWidget{
    Q_OBJECT
public:
    ScrollBarGroove(Qt::Orientation orient, QWidget *parent);
    void fadeIn();
    void fadeOut();
    void paintEvent(QPaintEvent *e);
    ArrowButton *upButton;
    ArrowButton *downButton;
    QGraphicsOpacityEffect *opacityEffect;
    QPropertyAnimation *opacityAni;
private:
};

class ScrollBarHandle : public QWidget{
    Q_OBJECT
public:
    ScrollBarHandle(Qt::Orientation orient, QWidget *parent);
    void paintEvent(QPaintEvent *e);
    Qt::Orientation orient;
private:
};

class ScrollBar : public QWidget{
    Q_OBJECT
    Q_PROPERTY(int val READ getVal WRITE setVal)
public:
    ScrollBar(){};
    ScrollBar(Qt::Orientation orient, QAbstractScrollArea *parent);
    void __initWidget(QWidget *parent);
    int value();
    int getVal();
    void setVal(int value);
    int minimum();
    int maximum();
    Qt::Orientation orientation();
    int pageStep();
    int singleStep();
    bool isSliderDown();
    void setValue(int value);
    void setMinimum(int min);
    void setMaximum(int max);
    void setPageStep(int step);
    void setSingleStep(int step);
    void setSliderDown(bool isDown);
    void expand();
    void collapse();
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void _adjustPos(QSize size);
    void _adjustHandleSize();
    void _adjustHandlePos();
    int _grooveLength();
    int _slideLength();
    bool _isSlideResion(QPoint pos);
    void setForceHidden(bool isHidden);
    void wheelEvent(QWheelEvent *event);

    ScrollBarGroove *groove;
    ScrollBarHandle *handle;
    QTimer *timer;
    Qt::Orientation _orientation;
    int _singleStep;
    int _pageStep;
    int _padding;
    int _minimum;
    int _maximum;
    int _value;
    bool _isPressed;
    bool _isEnter;
    bool _isExpanded;
    QPoint _pressedPos;
    bool _isForceHidden;
    int val;
    QScrollBar *partnerBar;
private:

signals:
    void rangeChanged(std::tuple<int, int> value);
    void valueChanged(int value);
    void sliderPressed();
    void sliderReleased();
    void sliderMoved();

public slots:
    void _onPageUp();
    void _onPageDown();
    void _onOpacityAniValueChanged();
    void setRange(int min, int max);
    void _onValueChanged(int value);
};


class SmoothScrollBar : public ScrollBar{
    Q_OBJECT
public:
    SmoothScrollBar(Qt::Orientation orient, QAbstractScrollArea *parent);
    void setValue(int value, bool useAni);
    void scrollValue(int value, bool useAni);
    void scrollTo(int value, bool useAni);
    void resetValue(int value);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void setScrollAnimation(int duration, QEasingCurve easing);

    int duration;
    QPropertyAnimation *ani;
    int __value;
private:
};


class MQAbstractItemView : public QAbstractItemView{
    Q_OBJECT
public:

};

class SmoothScrollDelegate : public QObject{
    Q_OBJECT
public:
    SmoothScrollDelegate(QAbstractScrollArea *parent, bool useAni);
    bool eventFilter(QObject *watched, QWheelEvent *event);
    void setVerticalScrollBarPolicy(Qt::ScrollBarPolicy policy);
    void setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy policy);

    bool useAni;
    SmoothScrollBar *vScrollBar;
    SmoothScrollBar *hScrollBar;
    SmoothScroll *verticalSmoothScroll;
    SmoothScroll *horizonSmoothScroll;
private:
};