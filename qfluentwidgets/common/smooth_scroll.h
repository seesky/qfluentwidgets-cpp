#pragma once

#include <QtCore/QDateTime>
#include <QtCore/Qt>
#include <QtCore/QTimer>
#include <QtCore/QPoint>
#include <QtGui/QWheelEvent>
#include <QtWidgets/QApplication>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QAbstractScrollArea>
#include <QtCore/QList>
#include <QtCore/Qdebug>
#include "math.h"

enum class SmoothMode {
    NO_SMOOTH,
    CONSTANT,
    LINEAR,
    QUADRATI,
    COSINE
};

class SmoothScroll : public QObject{
    Q_OBJECT
public:
    SmoothScroll(QAbstractScrollArea *widget, Qt::Orientation orient);
    void setSmoothMode(SmoothMode smoothMode);
    void wheelEvent(QWheelEvent *e);
    
    float __subDelta(float delta, float stepsLeft);

    QAbstractScrollArea *widget;
    Qt::Orientation orient;
    int fps;
    int duration;
    int stepsTotal;
    float stepRatio;
    int acceleration;
    QWheelEvent *lastWheelEvent;
    QList<int> *scrollStamps;
    QList<float *> *stepsLeftQueue;
    QTimer *smoothMoveTimer;
    SmoothMode smoothMode;
private:
public slots:
    void __smoothMove();
};
