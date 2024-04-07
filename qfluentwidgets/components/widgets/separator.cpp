#include "separator.h"

HorizontalSeparator::HorizontalSeparator(QWidget *parent) : QWidget(parent)
{
    this->setFixedHeight(3);
}

void HorizontalSeparator::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    if(isDarkTheme()){
        painter.setPen(QColor(255, 255, 255, 51));
    }else{
        painter.setPen(QColor(0, 0, 0, 22));
    }

    painter.drawLine(0, 1, this->width(), 1);
}


VerticalSeparator::VerticalSeparator(QWidget *parent) : QWidget(parent)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    if(isDarkTheme()){
        painter.setPen(QColor(255, 255, 255, 51));
    }else{
        painter.setPen(QColor(0, 0, 0, 22));
    }

    painter.drawLine(1, 0, 1, this->height());
}


void VerticalSeparator::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    if(isDarkTheme()){
        painter.setPen(QColor(255, 255, 255, 51));
    }else{
        painter.setPen(QColor(0, 0, 0, 22));
    }

    painter.drawLine(1, 0, 1, this->height());
}