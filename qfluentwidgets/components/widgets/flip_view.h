#pragma once

#include <QtCore/Qt>
#include <QtCore/QModelIndex>
#include <QtCore/QSize>
#include <QtCore/QRectF>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QSizeF>
#include <QtGui/QPixmap>
#include <QtGui/QPainter>
#include <QtGui/QColor>
#include <QtGui/QImage>
#include <QtGui/QWheelEvent>
#include <QtGui/QPainterPath>
#include <QtWidgets/QStyleOptionViewItem>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QStyledItemDelegate>
#include <QtWidgets/QListWidgetItem>

#include "../../common/style_sheet.h"
#include "../../common/icon.h"
#include "../../components/widgets/scroll_bar.h"
#include "../../components/widgets/button.h"


class FlipScrollButton : public ToolButton{
    Q_OBJECT
public:
    Q_PROPERTY(float opacity READ getOpacity WRITE setOpacity)
    FlipScrollButton(QWidget *parent);
    FlipScrollButton(FluentIcon *icon, QWidget *parent);
    FlipScrollButton(SpinIcon *icon, QWidget *parent);
    FlipScrollButton(QIcon *icon, QWidget *parent);
    FlipScrollButton(QString icon, QWidget *parent);
    void _postInit() override;
    float getOpacity();
    void setOpacity(float o);
    bool isTransparent();
    void fadeIn();
    void fadeOut();
    void paintEvent(QPaintEvent *event) override;

    float _opacity;
    QPropertyAnimation *opacityAni;
};


class FlipView;
class HorizontalFlipView;
class FlipImageDelegate : public QStyledItemDelegate{
    Q_OBJECT
public:
    FlipImageDelegate(QWidget *parent);
    QSize itemSize(int index) const;
    void setBorderRadius(int radius);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    int borderRadius;
};


class FlipView : public QListWidget{
    Q_OBJECT
    Q_PROPERTY(QSize itemSize READ getItemSize WRITE setItemSize)
    Q_PROPERTY(int borderRadius READ getBorderRadius WRITE setBorderRadius)
    Q_PROPERTY(Qt::AspectRatioMode aspectRatioMode READ getAspectRatioMode WRITE setAspectRatioMode)
public:
    FlipView(QWidget *parent);
    FlipView(Qt::Orientation orientation, QWidget *parent);
    void _postInit();
    bool isHorizontal();
    void setItemSize(QSize size);
    QSize getItemSize();
    void setBorderRadius(int radius);
    int getBorderRadius();

    void setCurrentIndex(int index);
    void scrollToIndex(int index);
    int currentIndex();
    QImage image(int index);
    void addImage(QVariant *image);
    void addImages(QList<QVariant*> images);
    void setItemImage(int index, QVariant *image);
    void _adjustItemSize(QListWidgetItem *item);
    QImage itemImage(int index);
    void resizeEvent(QResizeEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void showEvent(QShowEvent *event) override;
    void wheelEvent(QWheelEvent *e) override;
    Qt::AspectRatioMode getAspectRatioMode();
    void setAspectRatioMode(Qt::AspectRatioMode mode);

    Qt::Orientation orientation;
    bool isHover;
    int _currentIndex;
    Qt::AspectRatioMode _aspectRatioMode;
    QSize _itemSize;
    FlipImageDelegate *delegate;
    SmoothScrollBar *scrollBar;
    FlipScrollButton *preButton;
    FlipScrollButton *nextButton;

signals:
    void currentIndexChanged(int);

public slots:
    void scrollPrevious();
    void scrollNext();
};


class HorizontalFlipView : public FlipView{
    Q_OBJECT
public:
    HorizontalFlipView(QWidget *parent);
};

class VerticalFlipView : public FlipView{
    Q_OBJECT
public:
    VerticalFlipView(QWidget *parent);
};