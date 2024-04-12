#pragma once

#include <QtCore/QTranslator>
#include <QtCore/QLocale>
#include <QtCore/QDebug>

class FluentTranslator : public QTranslator{
    Q_OBJECT
public:
    FluentTranslator(QLocale *locale, QObject *parent);
    void load(QLocale *locale);
};