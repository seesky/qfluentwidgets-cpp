#pragma once

#include <QtCore/QEasingCurve>
#include <QtCore/QVariant>
#include <QtCore/Qt>
#include <QtGui/QWheelEvent>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>
#include "../../common/smooth_scroll.h"
#include "scroll_bar.h"

class ScrollArea : public QScrollArea{
    Q_OBJECT
public:
    ScrollArea(QWidget *parent);
    SmoothScrollDelegate *scrollDelagate;
};

class SingleDirectionScrollArea : public QScrollArea{
    Q_OBJECT
public:
    SingleDirectionScrollArea(QWidget *parent, Qt::Orientation orient);
    void setVerticalScrollBarPolicy(Qt::ScrollBarPolicy policy);
    void setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy policy);
    void setSmoothMode(SmoothMode mode);
    void keyPressEvent(QKeyEvent *e) override;
    void wheelEvent(QWheelEvent *e) override;
    void publicSetViewportMargins(int left, int top, int right, int bottom);

    Qt::Orientation orient;
    SmoothScroll *smoothScroll;
    SmoothScrollBar *vScrollBar;
    SmoothScrollBar *hScrollBar;
};

class SmoothScrollArea : public QScrollArea{
    Q_OBJECT
public:
    SmoothScrollArea(QWidget *parent);
    void setScrollAnimation(Qt::Orientation orient, int duration, QEasingCurve easing);

    SmoothScrollDelegate *delegate;
};