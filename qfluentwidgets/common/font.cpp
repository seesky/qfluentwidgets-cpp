#include "font.h"

void setFont(QWidget widget, int fontSize, QFont::Weight weight)
{
    widget.setFont(getFont(fontSize, weight));
}

QFont getFont(int fontSize, QFont::Weight weight)
{
    QFont font = QFont();
    QStringList list = QStringList() << "Segoe UI" << "Microsoft YaHei" << "PingFang SC";
    font.setFamilies(list);
    font.setPixelSize(fontSize);
    font.setWeight(weight);
    return font;
}