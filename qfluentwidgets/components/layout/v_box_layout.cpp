#include "v_box_layout.h"

VBoxLayout::VBoxLayout(QWidget *parent) : QVBoxLayout(parent)
{
    this->widgets = QList<QWidget*>();
}

void VBoxLayout::addWidgets(QList<QWidget*> widgets, int stretch = 0, Qt::Alignment alignment = Qt::AlignTop)
{
    for(int i = 0; i < widgets.length(); i++){
        this->addWidget(widgets.at(i), stretch, alignment);
    }
}

void VBoxLayout::addWidget(QWidget *widget, int stretch = 0, Qt::Alignment alignment = Qt::AlignTop)
{
    QVBoxLayout::addWidget(widget, stretch, alignment);
    this->widgets.append(widget);
    widget->show();
}

void VBoxLayout::removeWidget(QWidget *widget)
{
    QVBoxLayout::removeWidget(widget);
    this->widgets.removeOne(widget);
}

void VBoxLayout::deleteWidget(QWidget *widget)
{
    this->removeWidget(widget);
    widget->hide();
    widget->deleteLater();
}

void VBoxLayout::removeAllWidget()
{
    for(int i = 0; i < this->widgets.length(); i++){
        QVBoxLayout::removeWidget(this->widgets.at(i));
    }

    this->widgets.clear();
}