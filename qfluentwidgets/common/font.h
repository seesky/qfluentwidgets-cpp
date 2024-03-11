#pragma once

#include <QtGui/QFont>
#include <QtWidgets/QWidget>

class Font{
public:
    void setFont(QWidget *widget, int fontSize, QFont::Weight weight);
    QFont getFont(int fontSize, QFont::Weight weight);
};
