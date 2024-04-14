#include "translator.h"

FluentTranslator::FluentTranslator(QLocale *locale, QObject *parent) : QTranslator(parent)
{
    this->load(locale == nullptr ? new QLocale() : locale);
}

void FluentTranslator::load(QLocale *locale)
{
    //qDebug() << QString("qfluentwidgets/i18n/gallery.%1.qm").arg(locale->name());
    QTranslator::load(QString("qfluentwidgets/i18n/gallery.%1.qm").arg(locale->name()));
}