#pragma once

#include <QtCore/Qt>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

class VBoxLayout : public QVBoxLayout{
    Q_OBJECT
public:
    VBoxLayout(QWidget *parent);
    void addWidgets(QList<QWidget*> widgets, int stretch, Qt::Alignment alignment);
    void addWidget(QWidget *widget, int stretch, Qt::Alignment alignment);
    void removeWidget(QWidget *widget);
    void deleteWidget(QWidget *widget);
    void removeAllWidget();

    QList<QWidget*> widgets;
};