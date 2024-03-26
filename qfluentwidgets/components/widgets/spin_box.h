#pragma once


#include <QtCore/Qt>
#include <QtCore/QSize>
#include <QtCore/QRectF>
#include <QtCore/QPoint>
#include <QtGui/QPainter>
#include <QtGui/QPainterPath>
#include <QtGui/QColor>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

#include "flyout.h"
#include "../../common/style_sheet.h"
#include "../../common/icon.h"
#include "../../common/font.h"
#include "button.h"
#include "line_edit.h"

class SpinButton : public QToolButton{
    Q_OBJECT
public:
    SpinButton(SpinIcon *icon, QWidget *parent);
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void paintEvent(QPaintEvent *e) override;

    bool isPressed;
    SpinIcon *_icon;

};


class CompactSpinButton : public QToolButton{
    Q_OBJECT
public:
    CompactSpinButton(QWidget *parent);
    void paintEvent(QPaintEvent *e) override;
};


class SpinFlyoutView : public FlyoutViewBase{
    Q_OBJECT
public:
    SpinFlyoutView(QWidget *parent);
    void paintEvent(QPaintEvent *e) override;

    TransparentToolButton *upButton;
    TransparentToolButton *downButton;
    QVBoxLayout *vBoxLayout;
};

class SpinBox : public QSpinBox{
    Q_OBJECT
public:
    SpinBox(QWidget *parent);
    void spinBoxBaseInit();
    void inlineSpinBoxBaseInit();
    void _drawBorderBottom();
    void paintEvent(QPaintEvent *e) override;
    void setAccelerated(bool on);

    QHBoxLayout *hBoxLayout;
    SpinButton *upButton;
    SpinButton *downButton;
public slots:
    void _showContextMenu(QPoint pos);

};




class CompactSpinBox : public QSpinBox{
    Q_OBJECT
public:
    CompactSpinBox(QWidget *parent);
    void spinBoxBaseInit();
    void compactSpinBoxBaseInit();
    void _drawBorderBottom();
    void paintEvent(QPaintEvent *e) override;
    void focusInEvent(QFocusEvent *event) override;
    void setAccelerated(bool on);

    QHBoxLayout *hBoxLayout;
    CompactSpinButton *compactSpinButton;
    SpinFlyoutView *spinFlyoutView;
    Flyout *spinFlyout;
public slots:
    void _showContextMenu(QPoint pos);
    void _showFlyout();
};


class DoubleSpinBox : public QDoubleSpinBox{
    Q_OBJECT
public:
    DoubleSpinBox(QWidget *parent);
    void spinBoxBaseInit();
    void inlineSpinBoxBaseInit();
    void _drawBorderBottom();
    void paintEvent(QPaintEvent *e) override;
    void setAccelerated(bool on);

    QHBoxLayout *hBoxLayout;
    SpinButton *upButton;
    SpinButton *downButton;
public slots:
    void _showContextMenu(QPoint pos);

};


class CompactDoubleSpinBox : public QDoubleSpinBox{
    Q_OBJECT
public:
    CompactDoubleSpinBox(QWidget *parent);
    void spinBoxBaseInit();
    void compactSpinBoxBaseInit();
    void _drawBorderBottom();
    void paintEvent(QPaintEvent *e) override;
    void focusInEvent(QFocusEvent *event) override;
    void setAccelerated(bool on);

    QHBoxLayout *hBoxLayout;
    CompactSpinButton *compactSpinButton;
    SpinFlyoutView *spinFlyoutView;
    Flyout *spinFlyout;
public slots:
    void _showContextMenu(QPoint pos);
    void _showFlyout();
};



class TimeEdit : public QTimeEdit{
    Q_OBJECT
public:
    TimeEdit(QWidget *parent);
    void spinBoxBaseInit();
    void inlineSpinBoxBaseInit();
    void _drawBorderBottom();
    void paintEvent(QPaintEvent *e) override;
    void setAccelerated(bool on);

    QHBoxLayout *hBoxLayout;
    SpinButton *upButton;
    SpinButton *downButton;
public slots:
    void _showContextMenu(QPoint pos);

};



class CompactTimeEdit : public QTimeEdit{
    Q_OBJECT
public:
    CompactTimeEdit(QWidget *parent);
    void spinBoxBaseInit();
    void compactSpinBoxBaseInit();
    void _drawBorderBottom();
    void paintEvent(QPaintEvent *e) override;
    void focusInEvent(QFocusEvent *event) override;
    void setAccelerated(bool on);

    QHBoxLayout *hBoxLayout;
    CompactSpinButton *compactSpinButton;
    SpinFlyoutView *spinFlyoutView;
    Flyout *spinFlyout;
public slots:
    void _showContextMenu(QPoint pos);
    void _showFlyout();
};



class DateTimeEdit : public QDateTimeEdit{
    Q_OBJECT
public:
    DateTimeEdit(QWidget *parent);
    void spinBoxBaseInit();
    void inlineSpinBoxBaseInit();
    void _drawBorderBottom();
    void paintEvent(QPaintEvent *e) override;
    void setAccelerated(bool on);

    QHBoxLayout *hBoxLayout;
    SpinButton *upButton;
    SpinButton *downButton;
public slots:
    void _showContextMenu(QPoint pos);

};


class CompactDateTimeEdit : public QDateTimeEdit{
    Q_OBJECT
public:
    CompactDateTimeEdit(QWidget *parent);
    void spinBoxBaseInit();
    void compactSpinBoxBaseInit();
    void _drawBorderBottom();
    void paintEvent(QPaintEvent *e) override;
    void focusInEvent(QFocusEvent *event) override;
    void setAccelerated(bool on);

    QHBoxLayout *hBoxLayout;
    CompactSpinButton *compactSpinButton;
    SpinFlyoutView *spinFlyoutView;
    Flyout *spinFlyout;
public slots:
    void _showContextMenu(QPoint pos);
    void _showFlyout();
};


class DateEdit : public QDateEdit{
    Q_OBJECT
public:
    DateEdit(QWidget *parent);
    void spinBoxBaseInit();
    void inlineSpinBoxBaseInit();
    void _drawBorderBottom();
    void paintEvent(QPaintEvent *e) override;
    void setAccelerated(bool on);

    QHBoxLayout *hBoxLayout;
    SpinButton *upButton;
    SpinButton *downButton;
public slots:
    void _showContextMenu(QPoint pos);

};



class CompactDateEdit : public QDateEdit{
    Q_OBJECT
public:
    CompactDateEdit(QWidget *parent);
    void spinBoxBaseInit();
    void compactSpinBoxBaseInit();
    void _drawBorderBottom();
    void paintEvent(QPaintEvent *e) override;
    void focusInEvent(QFocusEvent *event) override;
    void setAccelerated(bool on);

    QHBoxLayout *hBoxLayout;
    CompactSpinButton *compactSpinButton;
    SpinFlyoutView *spinFlyoutView;
    Flyout *spinFlyout;
public slots:
    void _showContextMenu(QPoint pos);
    void _showFlyout();
};