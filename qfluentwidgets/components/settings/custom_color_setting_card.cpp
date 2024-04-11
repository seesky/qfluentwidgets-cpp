#include "custom_color_setting_card.h"


CustomColorSettingCard::CustomColorSettingCard(QVariant configItem, QVariant *icon, QString title, QString content, QWidget *parent, bool enableAlpha) : ExpandGroupSettingCard(icon, title, content, parent)
{
    this->enableAlpha = enableAlpha;
    this->configItem = configItem;
    this->defaultColor = QColor(configItem.value<ColorConfigItem*>()->defaultValue);
    this->customColor = QColor(qconfig->get(configItem).value<QColor>());

    this->choiceLabel = new QLabel(this);

    this->radioWidget = new QWidget(this->view);
    this->radioLayout = new QVBoxLayout(this->radioWidget);
    this->defaultRadioButton = new RadioButton(this->tr("Default color"), this->radioWidget);
    this->customRadioButton = new RadioButton(this->tr("Custom color"), this->radioWidget);
    this->buttonGroup = new QButtonGroup(this);

    this->customColorWidget = new QWidget(this->view);
    this->customColorLayout = new QHBoxLayout(this->customColorWidget);
    this->customLabel = new QLabel(this->tr("Custom color"), this->customColorWidget);
    this->chooseColorButton = new QPushButton(this->tr("Choose color"), this->customColorWidget);

    this->__initLayout();
}


void CustomColorSettingCard::__initWidget()
{
    this->__initLayout();

    if(this->defaultColor != this->customColor){
        this->customRadioButton->setChecked(true);
        this->chooseColorButton->setEnabled(true);
    }else{
        this->defaultRadioButton->setChecked(true);
        this->chooseColorButton->setEnabled(false);
    }

    this->choiceLabel->setText(this->buttonGroup->checkedButton()->text());
    this->choiceLabel->adjustSize();

    this->chooseColorButton->setObjectName("chooseColorButton");

    //connect(this->buttonGroup, QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked), this, &CustomColorSettingCard::__onRadioButtonClicked);
    connect(this->buttonGroup, QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked), this, [this](QAbstractButton *b){
        RadioButton *radioButton = qobject_cast<RadioButton *>(b);
        this->__onRadioButtonClicked(radioButton);
    });
    //connect(this->buttonGroup, static_cast<void (QButtonGroup::*)(QAbstractButton *)>(&QButtonGroup::buttonClicked), this, &CustomColorSettingCard::__onRadioButtonClicked);
    connect(this->chooseColorButton, &QPushButton::clicked, this, &CustomColorSettingCard::__showColorDialog);
}


void CustomColorSettingCard::__initLayout()
{
    this->addWidget(this->choiceLabel);

    this->radioLayout->setSpacing(19);
    this->radioLayout->setAlignment(Qt::AlignTop);
    this->radioLayout->setContentsMargins(48, 18, 0, 18);
    this->buttonGroup->addButton(this->customRadioButton);
    this->buttonGroup->addButton(this->defaultRadioButton);
    this->radioLayout->addWidget(this->customRadioButton);
    this->radioLayout->addWidget(this->defaultRadioButton);
    this->radioLayout->setSizeConstraint(QVBoxLayout::SetMinimumSize);

    this->customColorLayout->setContentsMargins(48, 18, 44, 18);
    this->customColorLayout->addWidget(this->customLabel, 0, Qt::AlignLeft);
    this->customColorLayout->addWidget(this->chooseColorButton, 0, Qt::AlignRight);
    this->customColorLayout->setSizeConstraint(QHBoxLayout::SetMinimumSize);

    this->viewLayout->setSpacing(0);
    this->viewLayout->setContentsMargins(0, 0, 0, 0);
    this->addGroupWidget(this->radioWidget);
    this->addGroupWidget(this->customColorWidget);
}


void CustomColorSettingCard::__onRadioButtonClicked(RadioButton *button)
{
    if(button->text() == this->choiceLabel->text()){
        return;
    }

    this->choiceLabel->setText(button->text());
    this->choiceLabel->adjustSize();

    if(button == this->defaultRadioButton){
        this->chooseColorButton->setDisabled(true);
        qconfig->set(this->configItem, QVariant::fromValue<QColor>(this->defaultColor), true, false);
        if(this->defaultColor != this->customColor){
            emit(this->colorChanged(this->defaultColor));
        }
    }else{
        this->chooseColorButton->setDisabled(false);
        qconfig->set(this->configItem, QVariant::fromValue<QColor>(this->customColor), true, false);
        if(this->defaultColor != this->customColor){
            emit(this->colorChanged(this->customColor));
        }
    }
}


void CustomColorSettingCard::__showColorDialog()
{
    ColorDialog *w = new ColorDialog(qconfig->get(this->configItem).value<QColor>(), this->tr("Choose color"), this->window(), this->enableAlpha);
    connect(w, &ColorDialog::colorChanged, this, &CustomColorSettingCard::__onCustomColorChanged);
    w->exec();
}


void CustomColorSettingCard::__onCustomColorChanged(QColor color)
{
    qconfig->set(this->configItem, QVariant::fromValue<QColor>(color), true, false);
    this->customColor = QColor(color);
    emit(this->colorChanged(color));
}