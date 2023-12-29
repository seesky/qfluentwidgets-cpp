#pragma once

#include <QtWidgets>

class Font{
public:
    void setFont(QWidget *widget, int fontSize, QFont::Weight weight);
    QFont getFont(int fontSize, QFont::Weight weight);
};
