#pragma once

#include <QtCore/Qt>
#include <QtCore/QRectF>
#include <QtGui/QPainter>
#include <QtGui/QFont>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QSizePolicy>

#include "../../common/font.h"
#include "../../common/router.h"
#include "../../common/style_sheet.h"
#include "../../common/animation.h"
#include "../../components/widgets/button.h"
#include "navigation_panel.h"


class PivotItem : public PushButton{
    Q_OBJECT
public:
    PivotItem(){
        this->_postInit();
    };
    PivotItem(QWidget *parent) : PushButton(parent){
        this->_postInit();
    };
    PivotItem(QString text, QWidget *parent, QVariant *icon): PushButton(text, parent, icon){
        this->_postInit();
    };
    PivotItem(QIcon *icon, QString text, QWidget *parent): PushButton(icon, text, parent){
        this->_postInit();
    };
    PivotItem(FluentIcon *icon, QString text, QWidget *parent): PushButton(icon, text, parent){
        this->_postInit();
    };
    void _postInit();
    void setSelected(bool isSelected);

    bool isSelected;

signals:
    void itemClicked(bool);
};


class Pivot : public QWidget{
    Q_OBJECT
public:
    Pivot(QWidget *parent);
    PivotItem *addItem(QString routeKey, QString text, std::function<void()> onClick, QVariant *icon);
    void addWidget(QString routeKey, PivotItem *widget, std::function<void()> onClick);
    PivotItem *insertItem(int index, QString routeKey, QString text, std::function<void()> onClick, QVariant *icon);
    void insertWidget(int index, QString routeKey, PivotItem *widget, std::function<void()> onClick);
    void removeWidget(QString routeKey);
    void clear();
    PivotItem *currentItem();
    void setCurrentItem(QString routeKey);
    void setItemFontSize(int size);
    PivotItem *widget(QString routeKey);
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;


    QMap<QString, PivotItem*> *items;
    QString _currentRouteKey;
    QHBoxLayout *hBoxLayout;
    FluentAnimation *slideAni;

public slots:
    void _onItemClicked();

};