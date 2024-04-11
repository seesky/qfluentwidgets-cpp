#pragma once

#include <QtCore/Qt>
#include <QtCore/QObject>
#include <QtGui/QIcon>
#include <QtGui/QColor>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>

#include "../../components/dialog_box/color_dialog.h"
#include "expand_setting_card.h"
#include "../../components/widgets/button.h"
#include "../../common/config.h"
#include "../../common/icon.h"

class CustomColorSettingCard : public ExpandGroupSettingCard{
    Q_OBJECT
public:
    CustomColorSettingCard(QVariant configItem, QVariant *icon, QString title, QString content, QWidget *parent, bool enableAlpha);
    void __initWidget();
    void __initLayout();

    bool enableAlpha;
    QVariant configItem;
    QColor defaultColor;
    QColor customColor;
    QLabel *choiceLabel;
    QWidget *radioWidget;
    QVBoxLayout *radioLayout;
    RadioButton *defaultRadioButton;
    RadioButton *customRadioButton;
    QButtonGroup *buttonGroup;
    QWidget *customColorWidget;
    QHBoxLayout *customColorLayout;
    QLabel *customLabel;
    QPushButton *chooseColorButton;

signals:
    void colorChanged(QColor color);

public slots:
    void __onRadioButtonClicked(RadioButton *button);
    void __showColorDialog();
    void __onCustomColorChanged(QColor color);
};