#include "translator.h"

Translator::Translator(QObject *parent)
{
    this->text = this->tr("Text");
    this->view = this->tr("View");
    this->menus = this->tr("Menus & toolbars");
    this->icons = this->tr("Icons");
    this->layout = this->tr("Layout");
    this->dialogs = this->tr("Dialogs & flyouts");
    this->scroll = this->tr("Scrolling");
    this->material = this->tr("Material");
    this->dateTime = this->tr("Date & time");
    this->navigation = this->tr("Navigation");
    this->basicInput = this->tr("Basic input");
    this->statusInfo = this->tr("Status & info");
}


