#pragma once

#include <QtCore/QAbstractAnimation>
#include <QtCore/QEasingCurve>
#include <QtCore/QPoint>
#include <QtCore/QPropertyAnimation>
#include <QtWidgets/QGraphicsOpacityEffect>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

class OpacityAniStackedWidget : public QStackedWidget{
    Q_OBJECT
public:
    OpacityAniStackedWidget(QWidget *parent);
    void addWidget(QWidget *w);
    void setCurrentIndex(int index);
    void setCurrentWidget(QWidget *w);

    int __nextIndex;
    QList<QGraphicsOpacityEffect *> __effects;
    QList<QPropertyAnimation *> __anis;
    QGraphicsOpacityEffect *effect;
    QPropertyAnimation *ani;
public slots:
    void __onAniFinished();
};


class PopUpAniInfo{
public:
    PopUpAniInfo(QWidget *widget, int deltaX, int deltaY, QPropertyAnimation *ani);

    QWidget *widget;
    int deltaX;
    int deltaY;
    QPropertyAnimation *ani;
};


class PopUpAniStackedWidget : public QStackedWidget{
    Q_OBJECT
public:
    PopUpAniStackedWidget(QWidget *parent);
    void addWidget(QWidget *widget, int deltaX, int deltaY);
    void setCurrentIndex(int index, bool needPopOut, bool showNextWidgetDirectly, int duration, QEasingCurve easingCurve);
    void setCurrentWidget(QWidget *widget, bool needPopOut, bool showNextWidgetDirectly, int duration, QEasingCurve easingCurve);

    QList<PopUpAniInfo*> aniInfos;
    int _nextIndex;
    QPropertyAnimation *_ani;


signals:
    void aniFinished();
    void aniStart();

public slots:
    void __setAnimation(QPropertyAnimation *ani, QPoint startValue, QPoint endValue, int duration, QEasingCurve easingCurve);
    void __onAniFinished();
};