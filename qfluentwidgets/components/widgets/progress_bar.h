#pragma once

#include <QtCore/QEasingCurve>
#include <QtCore/QDebug>
#include <QtCore/Qt>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QParallelAnimationGroup>
#include <QtCore/QSequentialAnimationGroup>
#include <QtCore/QLocale>
#include <QtGui/QPainter>
#include <QtGui/QColor>
#include <QtWidgets/QProgressBar>
#include "../../common/style_sheet.h"
#include "math.h"


class ProgressBar : public QProgressBar{
    Q_OBJECT
    Q_PROPERTY(bool useAni READ isUseAni WRITE setUseAni)
    Q_PROPERTY(float val READ getVal WRITE setVal)
public:
    ProgressBar(QWidget *parent, bool useAni);
    float getVal();
    void setVal(float v);
    bool isUseAni();
    void setUseAni(bool isUse);
    QColor lightBarColor();
    QColor darkBarColor();
    void setCustomBarColor(QVariant *light, QVariant *dark);
    void setCustomBackgroundColor(QVariant *light, QVariant *dark);
    void resume();
    void pause();
    void setPaused(bool isPaused);
    bool isPaused();
    void error();
    void setError(bool isError);
    bool isError();
    QColor barColor();
    QString valText();
    void paintEvent(QPaintEvent *e) override;

    float _val;
    bool _useAni;
    QColor lightBackgroundColor;
    QColor darkBackgroundColor;
    QColor _lightBarColor;
    QColor _darkBarColor;
    QPropertyAnimation *ani;
    bool _isPaused;
    bool _isError;
public slots:
    void _onValueChanged(float value);
};


class IndeterminateProgressBar : public QProgressBar{
    Q_OBJECT
    Q_PROPERTY(float shortPos READ getShortPos WRITE setShortPos)
    Q_PROPERTY(float longPos READ getLongPos WRITE setLongPos)
public:
    IndeterminateProgressBar(QWidget *parent, bool start);
    QColor lightBarColor();
    QColor darkBarColor();
    void setCustomBarColor(QVariant *light, QVariant *dark);
    float getShortPos();
    void setShortPos(float p);
    float getLongPos();
    void setLongPos(float p);
    void start();
    void stop();
    bool isStarted();
    void pause();
    void resume();
    void setPaused(bool isPaused);
    bool isPaused();
    void error();
    void setError(bool isError);
    bool isError();
    QColor barColor();
    void paintEvent(QPaintEvent *e) override;

    float _shortPos;
    float _longPos;
    QPropertyAnimation *shortBarAni;
    QPropertyAnimation *longBarAni;
    QColor _lightBarColor;
    QColor _darkBarColor;
    bool _isError;
    QParallelAnimationGroup *aniGroup;
    QSequentialAnimationGroup *longBarAniGroup;

};