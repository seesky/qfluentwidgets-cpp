#include "font.h"

void Font::setFont(QWidget *widget, int fontSize = 14, QFont::Weight weight = QFont::Normal)
{
    widget->setFont(getFont(fontSize, weight));
}

QFont Font::getFont(int fontSize, QFont::Weight weight)
{
    QFont font = QFont();
    QStringList list = QStringList() << "Segoe UI" << "Microsoft YaHei" << "PingFang SC";
    font.setFamilies(list);
    font.setPixelSize(fontSize);
    font.setWeight(weight);
    return font;
}