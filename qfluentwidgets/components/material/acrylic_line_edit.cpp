#include "acrylic_line_edit.h"

AcrylicLineEdit::AcrylicLineEdit(QWidget *parent) : LineEdit(parent)
{

}

void AcrylicLineEdit::setCompleter(QCompleter *completer)
{
    LineEdit::setCompleter(completer);
    this->setCompleterMenu(new AcrylicCompleterMenu(this));
}

void AcrylicLineEdit::contextMenuEvent(QContextMenuEvent *e)
{
    AcrylicLineEditMenu *menu = new AcrylicLineEditMenu(this);
    QPoint *p = new QPoint(e->globalPos()); 
    menu->exec(p, true, MenuAnimationType::DROP_DOWN);
    delete menu; //TODO:特殊关注
}

AcrylicSearchLineEdit::AcrylicSearchLineEdit(QWidget *parent) : SearchLineEdit(parent)
{

}

void AcrylicSearchLineEdit::setCompleter(QCompleter *completer)
{
    SearchLineEdit::setCompleter(completer);
    this->setCompleterMenu(new AcrylicCompleterMenu(this));
}

void AcrylicSearchLineEdit::contextMenuEvent(QContextMenuEvent *e)
{
    AcrylicLineEditMenu *menu = new AcrylicLineEditMenu(this);
    QPoint *p = new QPoint(e->globalPos()); 
    menu->exec(p, true, MenuAnimationType::DROP_DOWN);
    delete menu; //TODO:特殊关注
}