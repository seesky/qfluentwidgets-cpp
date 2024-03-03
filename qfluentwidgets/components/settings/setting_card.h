#pragma once

#include <QtCore/Qt>
#include <QtGui/QColor>
#include <QtGui/QIcon>
#include <QtGui/QIcon>
#include <QtGui/QPainter>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>

#include "../dialog_box/color_dialog.h"
#include "../widgets/combo_box.h"
#include "../widgets/switch_button.h"
#include "../widgets/slider.h"
#include "../widgets/icon_widget.h"
#include "../widgets/button.h"
#include "../../common/style_sheet.h"
#include "../../common/config.h"
#include "../../common/icon.h"

/*
class SettingCard : public QFrame{
    Q_OBJECT
public:
    SettingCard(QVariant icon, QString title, QString content, QWidget *parent);
    void setTitle(QString title);
    void setContent(QString content);
    virtual void setValue(QString value);
    void paintEvent(QPaintEvent *event) override;

    IconWidget *iconLabel;
    QLabel *titleLabel;
    QLabel *contentLabel;
    QHBoxLayout *hBoxLayout;
    QVBoxLayout *vBoxLayout;
};



class SwitchSettingCard : public SettingCard{
    Q_OBJECT
public:
    SwitchSettingCard(QVariant icon, QString title, QString content, ConfigItem *configItem, QWidget *parent);
    void setValue(bool isChecked);
    void setChecked(bool isChecked);
    bool isChecked();

    ConfigItem *configItem;
    SwitchButton *switchButton;

signals:
    void checkedChanged(bool);

public slots:
    void __onCheckedChanged(bool isChecked);
};

*/


class ColorPickerButton : public QToolButton{
    Q_OBJECT
public:
    ColorPickerButton(QColor color, QString title, QWidget *parent, bool enableAlpha);
    void setColor(QColor color);
    void paintEvent(QPaintEvent *event) override;

    QString title;
    bool enableAlpha;
    QColor color;
signals:
    void colorChanged(QColor);

public slots:
    void __showColorDialog();
    void __onColorChanged(QColor color);
};