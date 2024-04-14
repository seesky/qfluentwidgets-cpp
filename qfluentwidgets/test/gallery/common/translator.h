#pragma once

#include <QtCore/QObject>

class Translator : public QObject{
    Q_OBJECT
public:
    Translator(QObject *parent);
    QString text;
    QString view;
    QString menus;
    QString icons;
    QString layout;
    QString dialogs;
    QString scroll;
    QString material;
    QString dateTime;
    QString navigation;
    QString basicInput;
    QString statusInfo;
};