#pragma once

#include <QtCore/QPoint>
#include <QtCore/QVariant>
#include <QtCore/Qt>
#include <QtCore/QRect>
#include <QtCore/QRectF>
#include <QtGui/QPixmap>
#include <QtGui/QPainter>
#include <QtGui/QColor>
#include <QtGui/QPainterPath>
#include <QtGui/QIcon>
#include <QtGui/QImage>
#include <QtWidgets/QWidget>

#include "../../common/icon.h"
#include "../../common/style_sheet.h"
#include "../../components/widgets/flyout.h"
#include "../../components/widgets/arcylic_label.h"


class AcrylicFlyoutViewBase : public FlyoutViewBase{
    Q_OBJECT
public:
    AcrylicFlyoutViewBase(QWidget* parent);
    QPainterPath acrylicClipPath();
    void paintEvent(QPaintEvent *event) override;
    void _drawAcrylic(QPainter *painter);
    void _updateAcrylicColor();

    AcrylicBrush *acrylicBrush;
};


class AcrylicFlyoutView : public FlyoutView{
    Q_OBJECT
public:
    AcrylicFlyoutView(QString title, QString content, QVariant *icon, QVariant *image, bool isClosable, QWidget *parent);
    QPainterPath acrylicClipPath();
    void paintEvent(QPaintEvent *event) override;
    void _drawAcrylic(QPainter *painter);
    void _updateAcrylicColor();

    AcrylicBrush *acrylicBrush;
};

class AcrylicFlyout : public Flyout{
    Q_OBJECT
public:
    AcrylicFlyout(FlyoutViewBase *view, QWidget *parent, bool isDeleteOnClose);
    static AcrylicFlyout* create(QString title, QString content, QVariant *icon, QVariant *image, bool isClosable, QVariant target, QWidget *parent, FlyoutAnimationType aniType, bool isDeleteOnClose);
    static AcrylicFlyout* make(FlyoutViewBase *view, QVariant target, QWidget *parent, FlyoutAnimationType aniType, bool isDeleteOnClose);
    void exec(QPoint pos, FlyoutAnimationType aniType) override;

};