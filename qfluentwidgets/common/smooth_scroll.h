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
#include "math.h"

enum class SmoothMode {
    NO_SMOOTH,
    CONSTANT,
    LINEAR,
    QUADRATI,
    COSINE
};

class SmoothScroll{
public:
    SmoothScroll(QScrollArea *widget, Qt::Orientation orient);
    void setSmoothMode(SmoothMode smoothMode);
    void wheelEvent(QWheelEvent *e);
    void __smoothMove();
    float __subDelta(float delta, float stepsLeft);

    QScrollArea *widget;
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
};
