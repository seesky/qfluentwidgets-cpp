#include "icon_widget.h"

IconWidget::IconWidget(QWidget *parent) : QWidget(parent)
{
    QVariant icon = QVariant::fromValue<QIcon>(QIcon());
    this->setIcon(&icon);
}

IconWidget::IconWidget(QVariant icon, QWidget *parent)
{
    if(icon.canConvert<FluentIcon>()){
        IconWidget(icon.value<FluentIcon>(), parent);
    }else if(icon.canConvert<QIcon>()){
        IconWidget(icon.value<QIcon>(), parent);
    }else if(icon.canConvert<QString>()){
        IconWidget(icon.value<QString>(), parent);
    }
}

IconWidget::IconWidget(FluentIcon icon, QWidget *parent) : QWidget(parent)
{
    QVariant *__icon = new QVariant();
    __icon->setValue<FluentIcon>(icon);
    this->setIcon(__icon);
}

IconWidget::IconWidget(QIcon icon, QWidget *parent) : QWidget(parent)
{
    QVariant *__icon = new QVariant();
    __icon->setValue<QIcon>(icon);
    this->setIcon(__icon);
}

IconWidget::IconWidget(QString icon, QWidget *parent)
{
    QVariant *__icon = new QVariant();
    __icon->setValue<QString>(icon);
    this->setIcon(__icon);
}

QIcon IconWidget::getIcon()
{
    return MIcon().toQIcon(this->_icon);
}

void IconWidget::setIcon(QVariant *icon)
{
    this->_icon = icon;
    this->update();
}

void IconWidget::paintEvent(QPaintEvent *event)
{
    QPainter *painter = new QPainter(this);
    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    MIcon().drawIcon(this->_icon, painter, this->rect(), nullptr, QIcon::State::Off);
}






