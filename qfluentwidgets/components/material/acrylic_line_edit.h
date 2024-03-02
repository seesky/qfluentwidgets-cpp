#pragma once

#include "acrylic_menu.h"
#include "../widgets/line_edit.h"

class AcrylicLineEdit : public LineEdit{
    Q_OBJECT
public:
    AcrylicLineEdit(QWidget *parent);
    void setCompleter(QCompleter *completer) override;
    void contextMenuEvent(QContextMenuEvent *e) override;
};

class AcrylicSearchLineEdit : public SearchLineEdit{
    Q_OBJECT
public:
    AcrylicSearchLineEdit(QWidget *parent);
    void setCompleter(QCompleter *completer) override;
    void contextMenuEvent(QContextMenuEvent *e) override;
};