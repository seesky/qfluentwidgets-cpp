#include "translator.h"

FluentTranslator::FluentTranslator(QLocale *locale, QObject *parent) : QTranslator(parent)
{
    this->load(locale == nullptr ? new QLocale() : locale);
}

void FluentTranslator::load(QLocale *locale)
{
    qDebug() << QString("resource/setting_resource/i18n/settings.%1.qm").arg(locale->name());
    QTranslator::load(QString("resource/setting_resource/i18n/settings.%1.qm").arg(locale->name()));
}