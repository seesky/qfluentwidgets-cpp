#pragma once

#include <QtCore/QEasingCurve>
#include <QtCore/QPropertyAnimation>
#include <QtCore/Qt>
#include <QtCore/QDebug>
#include <QtCore/QEvent>
#include <QtGui/QColor>
#include <QtGui/QResizeEvent>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QtWidgets/QGraphicsOpacityEffect>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QWidget>
#include <QtWidgets/QFrame>
#include "../../common/config.h"

class MaskDialogBase : public QDialog{
    Q_OBJECT
public:
    MaskDialogBase(QWidget *parent);
    void setShadowEffect(int blurRadius, std::tuple<int,int> offset, QColor color);
    void setMaskColor(QColor color);
    void showEvent(QShowEvent *e) override;
    void done(int code) override;
    void resizeEvent(QResizeEvent *e) override;
    bool eventFilter(QObject *obj, QEvent *e) override;

    QHBoxLayout *_hBoxLayout;
    QWidget *windowMask;
    QFrame *widget;
};
