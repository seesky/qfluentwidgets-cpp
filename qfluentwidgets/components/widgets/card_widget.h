#pragma once

#include <QtCore/Qt>
#include <QtCore/QRectF>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QPoint>
#include <QtGui/QPixmap>
#include <QtGui/QPainter>
#include <QtGui/QColor>
#include <QtGui/QPainterPath>
#include <QtGui/QFont>
#include <QtWidgets/QWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>

#include "../../common/style_sheet.h"
#include "../../common/animation.h"
#include "../../common/font.h"

class CardWidget;
class CardBackgroundColorObject : public BackgroundColorObject{
    Q_OBJECT
public:
    CardBackgroundColorObject(CardWidget *parent);
    QColor getBackgroundColor() override;
    void setBackgroundColor(QColor color) override;
};


class CardWidget : public QFrame{
    Q_OBJECT
    Q_PROPERTY(int borderRadius READ getBorderRadius WRITE setBorderRadius)
public:
    CardWidget(QWidget *parent);
    bool eventFilter(QObject *obj, QEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void enterEvent(QEvent *e) override;
    void leaveEvent(QEvent *e) override;
    void focusInEvent(QFocusEvent *e) override;
    virtual QColor _normalBackgroundColor();
    virtual QColor _hoverBackgroundColor();
    virtual QColor _pressedBackgroundColor();
    QColor _focusInBackgroundColor();
    QColor _disabledBackgroundColor();
    void _updateBackgroundColor();
    QColor getBackgroundColor();
    void setBackgroundColor(QColor color);
    QColor backgroundColor();

    void setClickEnabled(bool isEnabled);
    bool isClickEnabled();
    void setBorderRadius(int radius);
    int getBorderRadius();
    void paintEvent(QPaintEvent *event) override;

    bool isHover;
    bool isPressed;
    CardBackgroundColorObject *bgColorObject;
    QPropertyAnimation *backgroundColorAni;
    bool _isClickEnabled;
    int _borderRadius;

signals:
    void clicked();
};


class SimpleCardWidget : public CardWidget{
    Q_OBJECT
public:
    SimpleCardWidget(QWidget *parent);
    QColor _normalBackgroundColor() override;
    QColor _hoverBackgroundColor() override;
    QColor _pressedBackgroundColor() override;
    void paintEvent(QPaintEvent *event) override;
};


class ElevatedCardWidget : public SimpleCardWidget{
    Q_OBJECT
public:
    ElevatedCardWidget(QWidget *parent);
    void enterEvent(QEvent *e) override;
    void leaveEvent(QEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void _startElevateAni(QPoint start, QPoint end);
    QColor _hoverBackgroundColor() override;
    QColor _pressedBackgroundColor() override;

    DropShadowAnimation *shadowAni;
    QPropertyAnimation *elevatedAni;
    QPoint _originalPos;
};


class CardSeparator : public QWidget{
    Q_OBJECT
public:
    CardSeparator(QWidget *parent);
    void paintEvent(QPaintEvent *event) override;
};



class HeaderCardWidget : public SimpleCardWidget{
    Q_OBJECT
    Q_PROPERTY(QString title READ getTitle WRITE setTitle)
public:
    HeaderCardWidget(QWidget *parent);
    HeaderCardWidget(QString title, QWidget *parent);
    QString getTitle();
    void setTitle(QString title);

    QWidget *headerView;
    QLabel *headerLabel;
    CardSeparator *separator;
    QWidget *view;

    QVBoxLayout *vBoxLayout;
    QHBoxLayout *headerLayout;
    QHBoxLayout *viewLayout;
    
};