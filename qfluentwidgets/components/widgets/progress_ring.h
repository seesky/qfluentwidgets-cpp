#pragma once

#include <QtCore/Qt>
#include <QtCore/QRectF>
#include <QtCore/QEasingCurve>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QParallelAnimationGroup>
#include <QtCore/QSequentialAnimationGroup>
#include <QtGui/QColor>
#include <QtGui/QPen>
#include <QtGui/QPainter>
#include <QtGui/QFont>
#include <QtWidgets/QProgressBar>

#include "progress_bar.h"
#include "../../common/font.h"
#include "../../common/style_sheet.h"


class ProgressRing : public ProgressBar{
    Q_OBJECT
    Q_PROPERTY(int strokeWidth READ getStrokeWidth WRITE setStrokeWidth)
public:
    ProgressRing(QWidget *parent, bool useAni);
    int getStrokeWidth();
    void setStrokeWidth(int w);
    void _drawText(QPainter *painter, QString text);
    void paintEvent(QPaintEvent *e) override;

    int _strokeWidth;
};


class IndeterminateProgressRing : public QProgressBar{
    Q_OBJECT
    Q_PROPERTY(int strokeWidth READ getStrokeWidth WRITE setStrokeWidth)
    Q_PROPERTY(int startAngle READ getStartAngle WRITE setStartAngle)
    Q_PROPERTY(int spanAngle READ getSpanAngle WRITE setSpanAngle)
public:
    IndeterminateProgressRing(QWidget *parent, bool start);
    int getStartAngle();
    void setStartAngle(int angle);
    int getSpanAngle();
    void setSpanAngle(int angle);
    int getStrokeWidth();
    void setStrokeWidth(int w);
    void start();
    void stop();
    QColor lightBarColor();
    QColor darkBarColor();
    void setCustomBarColor(QVariant *light, QVariant *dark);
    void setCustomBackgroundColor(QVariant *light, QVariant *dark);
    void paintEvent(QPaintEvent *e) override;

    QColor lightBackgroundColor;
    QColor darkBackgroundColor;
    QColor _lightBarColor;
    QColor _darkBarColor;
    int _strokeWidth;

    int _startAngle;
    int _spanAngle;

    QPropertyAnimation *startAngleAni1;
    QPropertyAnimation *startAngleAni2;
    QPropertyAnimation *spanAngleAni1;
    QPropertyAnimation *spanAngleAni2;

    QSequentialAnimationGroup *startAngleAniGroup;
    QSequentialAnimationGroup *spanAngleAniGroup;
    QParallelAnimationGroup *aniGroup;
};