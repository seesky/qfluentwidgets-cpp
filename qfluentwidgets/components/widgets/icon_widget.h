#pragma once

#include <QtGui/QIcon>
#include <QtGui/QPainter>
#include <QtWidgets/QWidget>

#include "../../common/icon.h"

class IconWidget : public QWidget{
    Q_OBJECT
public:
    IconWidget(QWidget *parent);
    IconWidget(QVariant *icon, QWidget *parent);
    IconWidget(FluentIcon icon, QWidget *parent);
    IconWidget(InfoBarIcon *icon, QWidget *parent);
    IconWidget(QIcon icon, QWidget *parent);
    IconWidget(QString icon, QWidget *parent);
    QIcon getIcon();
    void setIcon(QVariant *icon);
    void paintEvent(QPaintEvent *event) override;

    QVariant *_icon;
};