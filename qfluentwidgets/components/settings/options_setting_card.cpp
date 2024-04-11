#include "options_setting_card.h"

OptionsSettingCard::OptionsSettingCard(QVariant configItem, QVariant *icon, QString title, QString content, QList<QString> texts, QWidget *parent) : ExpandSettingCard(icon, title, content, parent)
{
    this->texts =  texts.isEmpty() ? QList<QString>() : texts;
    this->configItem = configItem;
    this->configName = configItem.value<OptionsConfigItem*>()->name;
    this->choiceLabel = new QLabel(this);
    this->buttonGroup = new QButtonGroup(this);

    this->addWidget(this->choiceLabel);

    this->viewLayout->setSpacing(19);
    this->viewLayout->setContentsMargins(48, 18, 0, 18);
    for(int i = 0; i < texts.length(); i++){
        RadioButton *button = new RadioButton(texts.at(i), this->view);
        this->buttonGroup->addButton(button);
        this->viewLayout->addWidget(button);
        button->setProperty(this->configName.toUtf8(), configItem.value<OptionsConfigItem*>()->options().at(i));
    }

    this->_adjustViewSize();
    this->setValue(qconfig->get(this->configItem).value<QString>());
    connect(configItem.value<OptionsConfigItem*>(), &OptionsConfigItem::valueChanged, this, &OptionsSettingCard::setValue);
    connect(this->buttonGroup, QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked), this, [this](QAbstractButton *b){
        RadioButton *radioButton = qobject_cast<RadioButton *>(b);
        this->__onButtonClicked(radioButton);
    });
}
    

void OptionsSettingCard::__onButtonClicked(RadioButton *button)
{
    if(button->text() == this->choiceLabel->text()){
        return;
    }

    QString value = button->property(this->configName.toUtf8()).value<QString>();
    qconfig->set(this->configItem, QVariant::fromValue<QString>(value), true, false);

    this->choiceLabel->setText(button->text());
    this->choiceLabel->adjustSize();
    emit(this->optionChanged(this->configItem.value<OptionsConfigItem*>()));
}

void OptionsSettingCard::setValue(QString value)
{
    qconfig->set(this->configItem, QVariant::fromValue<QString>(value), true, false);

    for(int i = 0; i < this->buttonGroup->buttons().length(); i++){
        QAbstractButton *button = this->buttonGroup->buttons().at(i);
        bool isChecked = button->property(this->configName.toUtf8()).value<QString>() == value;
        button->setChecked(isChecked);

        if(isChecked){
            this->choiceLabel->setText(button->text());
            this->choiceLabel->adjustSize();
        }
    }
}