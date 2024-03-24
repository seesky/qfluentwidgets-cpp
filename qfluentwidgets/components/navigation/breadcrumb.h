#pragma once

#include <QtCore/Qt>
#include <QtCore/QRectF>
#include <QtCore/QPoint>
#include <QtCore/QEvent>
#include <QtGui/QPainter>
#include <QtGui/QFont>
#include <QtGui/QHoverEvent>
#include <QtWidgets/QWidget>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>

#include "../../common/font.h"
#include "../../common/icon.h"
#include "../../common/style_sheet.h"
#include "../widgets/menu.h"

class BreadcrumbWidget : public QWidget{
    Q_OBJECT
public:
    BreadcrumbWidget(QWidget *parent);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

    bool isHover;
    bool isPressed;

signals:
    void clicked();
};


class ElideButton : public BreadcrumbWidget{
    Q_OBJECT
public:
    ElideButton(QWidget *parent);
    void paintEvent(QPaintEvent *event) override;
    void clearState();
};


class BreadcrumbItem : public BreadcrumbWidget{
    Q_OBJECT
public:
    BreadcrumbItem(QString routeKey, QString text, int index, QWidget *parent);
    void setText(QString text);
    bool isRoot();
    void setSelected(bool isSelected);
    void setFont(QFont font);
    void setSpacing(int spacing);
    void paintEvent(QPaintEvent *event) override;

    QString text;
    QString routeKey;
    bool isSelected;
    int index;
    int spacing;
};


class BreadcrumbBar : public QWidget{
    Q_OBJECT
    Q_PROPERTY(int spacing READ getSpacing WRITE setSpacing)
public:
    BreadcrumbBar(QWidget *parent);
    void addItem(QString routeKey, QString text);
    void setCurrentIndex(int index);
    void setCurrentItem(QString routeKey);
    BreadcrumbItem *item(QString routeKey);
    int currentIndex();
    BreadcrumbItem *currentItem();
    void resizeEvent(QResizeEvent *event) override;
    void clear();
    void popItem();
    void updateGeometry();
    bool isElideVisible();
    void setFont(QFont font);
    int getSpacing();
    void setSpacing(int spacing);

    QMap<QString, BreadcrumbItem*> itemMap;
    QList<BreadcrumbItem*> items;
    QList<BreadcrumbItem*> hiddenItems;
    int _spacing;
    int _currentIndex;
    ElideButton *elideButton;
signals:
    void currentItemChanged(QString);
    void currentIndexChanged(int);


public slots:
    void _showHiddenItemsMenu();
};