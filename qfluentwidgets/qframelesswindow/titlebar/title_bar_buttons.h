#pragma once

#include <QtCore/QFile>
#include <QtCore/QPointF>
#include <QtCore/QRectF>
#include <QtCore/Qt>
#include <QtGui/QColor>
#include <QtGui/QPainter>
#include <QtGui/QPainterPath>
#include <QtGui/QPen>
#include <QtGui/QMouseEvent>
#include <QtWidgets/QAbstractButton>
#include <QtSvg/QSvgRenderer>
#include <QtXml/QDomDocument>


enum class TitleBarButtonState{
    NORMAL = 0,
    HOVER = 1,
    PRESSED = 2
};

class TitleBarButton : public QAbstractButton{
    Q_OBJECT
public:
    TitleBarButton(QWidget *parent);
    void setState(TitleBarButtonState state);
    bool isPressed();
    QColor *getNormalColor();
    QColor *getHoverColor();
    QColor *getPressedColor();
    QColor *getNormalBackgroundColor();
    QColor *getHoverBackgroundColor();
    QColor *getPressedBackgroundColor();
    void setNormalColor(QColor *color);
    void setHoverColor(QColor *color);
    void setPressedColor(QColor *color);
    void setNormalBackgroundColor(QColor *color);
    void setHoverBackgroundColor(QColor *color);
    void setPressedBackgroundColor(QColor *color);
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    std::tuple<QColor*, QColor*> _getColors();

    TitleBarButtonState _state;
    QColor *_normalColor;
    QColor *_hoverColor;
    QColor *_pressedClor;
    QColor *_normalBgColor;
    QColor *_hoverBgColor;
    QColor *_PressedBgColor; 
private:
};

class SvgTitleBarButton : public TitleBarButton{
    Q_OBJECT
public:
    SvgTitleBarButton(QString iconPath, QWidget *parent);
    void setIcon(QString iconPath);
    void paintEvent(QPaintEvent *e);

    QDomDocument *_svgDom;
private:
};

class MinimizeButton : public TitleBarButton{
    Q_OBJECT
public:
    MinimizeButton(QWidget *parent) : TitleBarButton(parent){};
    void paintEvent(QPaintEvent *e);
private:
};

class MaximizeButton : public TitleBarButton{
    Q_OBJECT
public:
    MaximizeButton(QWidget *parent);
    void setMaxState(bool isMax);
    void paintEvent(QPaintEvent *e);

    bool _isMax;
private: 
};

class CloseButton : public SvgTitleBarButton{
    Q_OBJECT
public:
    CloseButton(QWidget *parent);
private:
};