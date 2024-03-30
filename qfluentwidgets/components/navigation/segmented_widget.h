#pragma once

#include <QtCore/Qt>
#include <QtCore/QRectF>
#include <QtGui/QPainter>
#include <QtGui/QIcon>
#include <QtGui/QColor>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

#include "../../common/font.h"
#include "../../common/icon.h"
#include "../../components/widgets/button.h"
#include "pivot.h"


class SegmentedItem : public PivotItem{
    Q_OBJECT
public:
    SegmentedItem();
    SegmentedItem(QWidget *parent);
    SegmentedItem(QString text, QWidget *parent, QVariant *icon);
    SegmentedItem(QIcon *icon, QString text, QWidget *parent);
    SegmentedItem(FluentIcon *icon, QString text, QWidget *parent);
    void _postInit() override;
};


class SegmentedToolItem : public ToolButton{
    Q_OBJECT
public:
    SegmentedToolItem(QWidget *parent);
    SegmentedToolItem(FluentIcon *icon, QWidget *parent);
    SegmentedToolItem(SpinIcon *icon, QWidget *parent);
    SegmentedToolItem(QIcon *icon, QWidget *parent);
    SegmentedToolItem(QString icon, QWidget *parent);
    void _postInit() override;
    void setSelected(bool isSelected);

    bool isSelected;

signals:
    void itemClicked(bool);
};


class SegmentedToggleToolItem : public TransparentToolButton{
    Q_OBJECT
public:
    SegmentedToggleToolItem(QWidget *parent);
    SegmentedToggleToolItem(FluentIcon *icon, QWidget *parent);
    SegmentedToggleToolItem(SpinIcon *icon, QWidget *parent);
    SegmentedToggleToolItem(QIcon *icon, QWidget *parent);
    SegmentedToggleToolItem(QString icon, QWidget *parent);
    void _postInit() override;
    void setSelected(bool isSelected);
    void _drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state) override;

    bool isSelected;
signals:
    void itemClicked(bool);
};


class SegmentedWidget : public Pivot{
    Q_OBJECT
public:
    SegmentedWidget(QWidget *parent);
    SegmentedItem *insertItem(int index, QString routeKey, QString text, std::function<void()> onClick, QVariant *icon);
    void paintEvent(QPaintEvent *event) override;
};


class SegmentedToolWidget : public SegmentedWidget{
    Q_OBJECT
public:
    SegmentedToolWidget(QWidget *parent);
    SegmentedToolItem *addItem(QString routeKey, QVariant *icon, std::function<void()> onClick);
    SegmentedToolItem *insertItem(int index, QString routeKey, QVariant *icon, std::function<void()> onClick);
    SegmentedToolItem *_createItem(QVariant *icon);
    void insertWidget(int index, QString routeKey, SegmentedToolItem *widget, std::function<void()> onClick);

    QMap<QString, SegmentedToolItem*> *items;
};


class SegmentedToggleToolWidget : public SegmentedToolWidget{
    Q_OBJECT
public:
    SegmentedToggleToolItem *_createItem(QVariant *icon);
    void paintEvent(QPaintEvent *event) override;
};