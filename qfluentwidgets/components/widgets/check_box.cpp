#include "check_box.h"

QString CheckBoxIcon::path(Theme theme = Theme::AUTO)
{
    QString c = getIconColor(Theme::AUTO, true);
    QString path = QString("qfluentwidgets/images/check_box/" + CheckBoxIconMap.at(this->iconName) + "_" + c + ".svg");
    return path;
}


CheckBox::CheckBox(QWidget *parent) : QCheckBox(parent)
{
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("CHECK_BOX"), Theme::AUTO);
    this->setTristate();
}

CheckBox::CheckBox(QString text, QWidget *parent) : QCheckBox(parent)
{
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("CHECK_BOX"), Theme::AUTO);
    this->setText(text);
    this->setTristate();
}

void CheckBox::paintEvent(QPaintEvent *e)
{
    QCheckBox::paintEvent(e);
    QPainter *painter = new QPainter(this);

    if(!this->isEnabled()){
        painter->setOpacity(0.8);
    }

    QStyleOptionButton *opt = new QStyleOptionButton();
    opt->initFrom(this);
    QRect rect = this->style()->subElementRect(QStyle::SE_CheckBoxIndicator, opt, this);

    if(this->checkState() == Qt::Checked){
        CheckBoxIcon *icon = new CheckBoxIcon();
        icon->setIconName(QString("ACCEPT"));
        icon->render(painter, rect, Theme::AUTO, 0, nullptr);
    }else if(this->checkState() == Qt::PartiallyChecked){
        CheckBoxIcon *icon = new CheckBoxIcon();
        icon->setIconName(QString("PARTIAL_ACCEPT"));
        icon->render(painter, rect, Theme::AUTO, 0, nullptr);
    }

    painter->end();
}