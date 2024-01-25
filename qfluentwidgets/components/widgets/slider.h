#pragma once

#include <QtCore/QSize>
#include <QtCore/Qt>
#include <QtCore/QPoint>
#include <QtCore/QRectF>
#include <QtCore/QPropertyAnimation>
#include <QtGui/QColor>
#include <QtGui/QMouseEvent>
#include <QtGui/QPainter>
#include <QtGui/QPainterPath>
#include <QtWidgets/QProxyStyle>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStyleOptionSlider>
#include <QtWidgets/QWidget>
#include "../../common/style_sheet.h"



class SliderHandle : public QWidget{
    Q_OBJECT
    Q_PROPERTY(float radius READ radius WRITE setRadius)
public:
    SliderHandle(QWidget *parent);
    float radius();
    void setRadius(float r);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void _startAni(float radius);
    void paintEvent(QPaintEvent *event);

    float _radius;
    QPropertyAnimation *radiusAni;
signals:
    void pressed();
    void released();
};


class Slider : public QSlider{
    Q_OBJECT
public:
    Slider(QWidget *parent);
    Slider(Qt::Orientation orientation, QWidget *parent);
    void _postInit();
    void setOrientation(Qt::Orientation orientation);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *ev);
    int grooveLength();

    float _posToValue(QPoint *pos);
    void paintEvent(QPaintEvent *event);
    void _drawHorizonGroove(QPainter *painter);
    void _drawVerticalGroove(QPainter *painter);
    void resizeEvent(QResizeEvent *event);

    SliderHandle *handle;
    QPoint *_pressedPos;
signals:
    void clicked(int);

public slots:
    void _adjustHandlePos();
};


class ClickableSlider : public QSlider{
    Q_OBJECT
public:
    ClickableSlider(QWidget *parent) : QSlider(parent){};
    void mousePressEvent(QMouseEvent *event);
signals:
    void clicked(int);
};

class HollowHandleStyle : public QProxyStyle{
public:
    HollowHandleStyle(QMap<QString, QVariant*> *config, QStyle *style);
    QRect subControlRect(ComplexControl cc, const QStyleOptionComplex *opt, SubControl sc, const QWidget *widget) const;
    void drawComplexControl(ComplexControl cc, const QStyleOptionComplex *opt, QPainter *painter, const QWidget *widget) const;
    
    QMap<QString, QVariant*> *config;
};