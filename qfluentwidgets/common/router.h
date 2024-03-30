#pragma once

#include <QtCore/Qt>
#include <QtCore/QMap>
#include <QtCore/QVariant>
#include <QtCore/QObject>
#include <QtWidgets/QWidget>
#include <QtWidgets/QStackedWidget>

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
    Router(QWidget *parent);
    void setDefaultRouteKey(QStackedWidget *stacked, QString routeKey);
    void push(QStackedWidget *stacked, QString routeKey);
    void pop();
    bool remove(QString routeKey);

    QList<RouteItem*> history;
    QMap<QStackedWidget*, StackedHistory*> *stackHistories; 

signals:
    void emptyChanged(bool);
};


static Router *qrouter = new Router(nullptr);