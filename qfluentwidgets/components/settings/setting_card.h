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


class SettingCard : public QFrame{
    Q_OBJECT
public:
    SettingCard(QVariant *icon, QString title, QString content, QWidget *parent);
    void setTitle(QString title);
    void setContent(QString content);
    
    void paintEvent(QPaintEvent *event) override;

    IconWidget *iconLabel;
    QLabel *titleLabel;
    QLabel *contentLabel;
    QHBoxLayout *hBoxLayout;
    QVBoxLayout *vBoxLayout;

public slots:
    virtual void setValue(QString value);
};



class SwitchSettingCard : public SettingCard{
    Q_OBJECT
public:
    SwitchSettingCard(QVariant *icon, QString title, QString content, QVariant configItem, QWidget *parent);
    void setChecked(bool isChecked);
    bool isChecked();

    QVariant configItem;
    SwitchButton *switchButton;

signals:
    void checkedChanged(bool);

public slots:
    void __onCheckedChanged(bool isChecked);
    void setValue(bool isChecked);
};



class RangeSettingCard : public SettingCard{
    Q_OBJECT
public:
    RangeSettingCard(QVariant configItem, QVariant *icon, QString title, QString content, QWidget *parent);

    QVariant configItem;
    Slider *slider;
    QLabel *valueLabel;


signals:
    void valueChanged(int);

public slots:
    void __onValueChanged(int value);
    void setValue(int value);
};


class PushSettingCard : public SettingCard{
    Q_OBJECT
public:
    PushSettingCard(QString text, QVariant *icon, QString title, QString content, QWidget *parent);

    QPushButton *button;
signals:
    void clicked();
};


class PrimaryPushSettingCard : public PushSettingCard{
    Q_OBJECT
public:
    PrimaryPushSettingCard(QString text, QVariant *icon, QString title, QString content, QWidget *parent);
};


class HyperlinkCard : public SettingCard{
    Q_OBJECT
public:
    HyperlinkCard(QString url, QString text, QVariant *icon, QString title, QString content, QWidget *parent);
    HyperlinkButton *linkButton;
};




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


class ColorSettingCard : public SettingCard{
    Q_OBJECT
public:
    ColorSettingCard(QVariant item, QVariant *icon, QString title, QString content, QWidget *parent, bool enableAlpha);

    QVariant configItem;
    ColorPickerButton *colorPicker;

signals:
    void colorChanged(QColor);

public slots:
    void __onColorChanged(QColor color);
    void setValue(QColor color);
};


class ComboBoxSettingCard : public SettingCard{
    Q_OBJECT
public:
    ComboBoxSettingCard(QVariant configItem, QVariant *icon, QString title, QString content, QList<QString> texts, QWidget *parent);

    QVariant configItem;
    ComboBox *comboBox;
    QMap<QString, QString> optionToText;
public slots:
    void _onCurrentIndexChanged(int index);
    void setValue(QString value);
};