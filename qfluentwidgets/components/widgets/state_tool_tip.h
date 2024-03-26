#pragma once

#include <QtCore/QPropertyAnimation>
#include <QtCore/Qt>
#include <QtCore/QTimer>
#include <QtCore/QPoint>
#include <QtCore/QRectF>
#include <QtGui/QPainter>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QGraphicsOpacityEffect>

#include "../../common/style_sheet.h"
#include "../../common/config.h"
#include "../../common/icon.h"

class StateCloseButton : public QToolButton{
    Q_OBJECT
public:
    StateCloseButton(QWidget *parent);
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    bool isPressed;
    bool isEnter;
};


class StateToolTip : public QWidget{
    Q_OBJECT
public:
    StateToolTip(QString title, QString content, QWidget *parent);
    void __initWidget();
    void __initLayout();
    void __setQss();
    void setTitle(QString title);
    void setContent(QString content);
    void setState(bool isDone);
    QPoint getSuitablePos();
    void paintEvent(QPaintEvent *event) override;

    QString title;
    QString content;
    QLabel *titleLabel;
    QLabel *contentLabel;
    QTimer *rotateTimer;
    QGraphicsOpacityEffect *opacityEffect;
    QPropertyAnimation *animation;
    StateCloseButton *closeButton;
    bool isDone;
    int rotateAngle;
    int deltaAngle;

signals:
    void closedSignal();

public slots:
    void __onCloseButtonClicked();
    void __fadeOut();
    void __rotateTimerFlowSlot();

};