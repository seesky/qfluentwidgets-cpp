#pragma once

#include <QtGui/QIcon>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QLabel>

#include "../../common/config.h"
#include "../../common/icon.h"
#include "../widgets/button.h"
#include "expand_setting_card.h"

class OptionsSettingCard : public ExpandSettingCard{
    Q_OBJECT
public:
    OptionsSettingCard(QVariant configItem, QVariant *icon, QString title, QString content, QList<QString> texts, QWidget *parent);
    void setValue(QString value);

    QList<QString> texts;
    QVariant configItem;
    QString configName;
    QLabel *choiceLabel;
    QButtonGroup *buttonGroup;

signals:
    void optionChanged(OptionsConfigItem*);

public slots:
    void __onButtonClicked(RadioButton *button);
};