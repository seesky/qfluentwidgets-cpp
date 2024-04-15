#pragma once

#include <QtCore/Qt>
#include <QtCore/QMap>
#include <QtCore/QVariant>
#include <QtCore/QObject>
#include <QtCore/QDebug>
#include <QtWidgets/QWidget>
#include <QtWidgets/QStackedWidget>

#include "../window/stacked_widget.h"

class RouteItem{
public:
    RouteItem(QStackedWidget *stacked, QString routeKey);
    bool __eq__(RouteItem *other);

    QStackedWidget *stacked;
    QString routeKey;
};

class StackedHistory{
public:
    StackedHistory(QStackedWidget *stacked);
    int __len__();
    bool isEmpty();
    bool push(QString routeKey);
    void pop();
    void remove(QString routeKey);
    QString top();
    void setDefaultRouteKey(QString routeKey);
    void goToTop();

    QStackedWidget *stacked;
    QString defaultRouteKey;
    QList<QString> history;
};


class Router : public QObject{
    Q_OBJECT
public:
    static Router* getInstance();
    void setDefaultRouteKey(QStackedWidget *stacked, QString routeKey);
    void push(QStackedWidget *stacked, QString routeKey);
    void pop();
    bool remove(QString routeKey);

    
    QList<RouteItem*> history;
    QMap<QStackedWidget*, StackedHistory*> *stackHistories; 


private:
    Router(QWidget *parent);
    Router(const Router&) = delete;
    Router& operator=(const Router&) = delete;
    static Router* instance;

signals:
    void emptyChanged(bool);
};


static Router *qrouter = Router::getInstance();