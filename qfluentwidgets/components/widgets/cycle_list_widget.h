#pragma once

#include <QtCore/Qt>
#include <QtCore/QSize>
#include <QtCore/QEvent>
#include <QtCore/QRectF>
#include <QtGui/QPainter>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QListWidgetItem>
#include <QtWidgets/QToolButton>
#include "scroll_bar.h"
#include "../../common/icon.h"
#include "../../common/config.h"

class ScrollButtonC : public QToolButton{
    Q_OBJECT
public:
    ScrollButtonC(FluentIcon *icon, QWidget *parent);
    bool eventFilter(QObject *watched, QEvent *event) override;
    void paintEvent(QPaintEvent *e) override;

    FluentIcon *_icon;
    bool isPressed;
};

class CycleListWidget : public QListWidget{
    Q_OBJECT
public:
    CycleListWidget(QList<QVariant> *items, QSize *itemSize, Qt::Alignment align, QWidget *parent);
    void setItems(QList<QVariant> *items);
    void _createItems(QList<QVariant> *items);
    void _addColumnItems(QList<QVariant> *items, bool disabled);
    void _onItemClicked(QListWidgetItem *item);
    void setSelectedItem(QString text);
    void scrollToItem(QListWidgetItem *item, ScrollHint hint);
    void wheelEvent(QWheelEvent *e) override;
    void scrollDown();
    void scrollUp();
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;
    QListWidgetItem *currentItem();
    int currentIndex();
    void setCurrentIndex(int index);

    QSize *itemSize;
    Qt::Alignment align;
    ScrollButtonC *upButton;
    ScrollButtonC *downButton;
    int scrollDuration;
    QList<QVariant> *originItems;
    SmoothScrollBar *vScrollBar;
    int visibleNumber;
    bool isCycle;
    int _currentIndex;
signals:
    void currentItemChanged(QListWidgetItem *item);
};