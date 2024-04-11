#include "setting_card.h"


SettingCard::SettingCard(QVariant *icon, QString title, QString content, QWidget *parent) : QFrame(parent)
{
    this->iconLabel = new IconWidget(icon, this);
    this->titleLabel = new QLabel(title, this);
    this->contentLabel = new QLabel(content.isEmpty() ? QString("") : content, this);
    this->hBoxLayout = new QHBoxLayout(this);
    this->vBoxLayout = new QVBoxLayout();

    if(content.isEmpty()){
        this->contentLabel->hide();
    }

    this->setFixedHeight(!content.isEmpty() ? 70 : 50);
    this->iconLabel->setFixedSize(16, 16);

    this->hBoxLayout->setSpacing(0);
    this->hBoxLayout->setContentsMargins(16, 0, 0, 0);
    this->hBoxLayout->setAlignment(Qt::AlignVCenter);
    this->vBoxLayout->setSpacing(0);
    this->vBoxLayout->setContentsMargins(0, 0, 0, 0);
    this->vBoxLayout->setAlignment(Qt::AlignVCenter);

    this->hBoxLayout->addWidget(this->iconLabel, 0, Qt::AlignLeft);
    this->hBoxLayout->addSpacing(16);

    this->hBoxLayout->addLayout(this->vBoxLayout);
    this->vBoxLayout->addWidget(this->titleLabel, 0, Qt::AlignLeft);
    this->vBoxLayout->addWidget(this->contentLabel, 0, Qt::AlignLeft);

    this->hBoxLayout->addSpacing(16);
    this->hBoxLayout->addStretch(1);

    this->contentLabel->setObjectName(QString("contentLabel"));
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("SETTING_CARD"), Theme::AUTO);
}


void SettingCard::setTitle(QString title)
{
    this->titleLabel->setText(title);
}

void SettingCard::setContent(QString content)
{
    this->contentLabel->setText(content);
    this->contentLabel->setVisible(!content.isEmpty());
}

void SettingCard::setValue(QString value)
{

}

void SettingCard::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    if(isDarkTheme()){
        painter.setBrush(QColor(255, 255, 255, 13));
        painter.setPen(QColor(0, 0, 0, 50));
    }else{
        painter.setBrush(QColor(255, 255, 255, 170));
        painter.setPen(QColor(0, 0, 0, 19));
    }

    painter.drawRoundedRect(this->rect().adjusted(1, 1, -1, -1), 6, 6);
}

SwitchSettingCard::SwitchSettingCard(QVariant *icon, QString title, QString content, QVariant configItem, QWidget *parent) : SettingCard(icon, title, content, parent)
{
    this->configItem = configItem;
    this->switchButton = new SwitchButton(this->tr("Off"), this, IndicatorPosition::RIGHT);

    if(configItem.isValid()){

        QString ic = qconfig->get(configItem).value<QString>();

        if(ic == "false"){
            this->setValue(false);
        }else if(ic == "true"){
            this->setValue(true);
        }

        
        //connect(configItem.value<OptionsConfigItem*>(), &OptionsConfigItem::valueChanged, this, &SwitchSettingCard::setValue);  
        connect(configItem.value<OptionsConfigItem*>(), &OptionsConfigItem::valueChanged, this, [this](QString value){
            if(value == QString("false")){
                this->setChecked(false);
            }else{
                this->setChecked(true);
            }
        });  
    }

    this->hBoxLayout->addWidget(this->switchButton, 0, Qt::AlignRight);
    this->hBoxLayout->addSpacing(16);

    connect(this->switchButton, &SwitchButton::checkedChanged, this, &SwitchSettingCard::__onCheckedChanged);
}



void SwitchSettingCard::__onCheckedChanged(bool isChecked)
{
    this->setValue(isChecked);
    emit(this->checkedChanged(isChecked));
}


void SwitchSettingCard::setValue(bool isChecked)
{
    if(this->configItem.isValid()){
        if(isChecked){
            qconfig->set(this->configItem, "true", true, false);
        }else{
            qconfig->set(this->configItem, "false", true, false);
        }
    }

    this->switchButton->setChecked(isChecked);
    this->switchButton->setText(isChecked ? this->tr("On") : this->tr("Off"));
}

void SwitchSettingCard::setChecked(bool isChecked)
{
    this->setValue(isChecked);
}


bool SwitchSettingCard::isChecked()
{
    return this->switchButton->isChecked();
}



RangeSettingCard::RangeSettingCard(QVariant configItem, QVariant *icon, QString title, QString content, QWidget *parent) : SettingCard(icon, title, content, parent)
{
    this->configItem = configItem;
    this->slider = new Slider(Qt::Horizontal, this);
    this->valueLabel = new QLabel(this);
    this->slider->setMinimumWidth(268);

    this->slider->setSingleStep(1);
    this->slider->setRange(configItem.value<RangeConfigItem*>()->min_value, configItem.value<RangeConfigItem*>()->max_value);
    this->slider->setValue(configItem.value<RangeConfigItem*>()->getValue());
    this->valueLabel->setNum(configItem.value<RangeConfigItem*>()->getValue());

    this->hBoxLayout->addStretch(1);
    this->hBoxLayout->addWidget(this->valueLabel, 0, Qt::AlignRight);
    this->hBoxLayout->addSpacing(6);
    this->hBoxLayout->addWidget(this->slider, 0, Qt::AlignRight);
    this->hBoxLayout->addSpacing(16);

    this->setValue(qconfig->get(this->configItem).value<QString>().toInt());

    this->valueLabel->setObjectName(QString("valueLabel"));
    connect(configItem.value<RangeConfigItem*>(), &RangeConfigItem::valueChanged, this, &RangeSettingCard::setValue);
    connect(this->slider, &Slider::valueChanged, this, &RangeSettingCard::__onValueChanged);
}


void RangeSettingCard::__onValueChanged(int value)
{
    this->setValue(value);
    emit(this->valueChanged(value));
}

void RangeSettingCard::setValue(int value)
{
    qconfig->set(this->configItem, QVariant::fromValue<int>(value), true, false);
    this->valueLabel->setNum(value);
    this->valueLabel->adjustSize();
    this->slider->setValue(value);
}



PushSettingCard::PushSettingCard(QString text, QVariant *icon, QString title, QString content, QWidget *parent) : SettingCard(icon, title, content, parent)
{
    this->button = new QPushButton(text, this);
    this->hBoxLayout->addWidget(this->button, 0, Qt::AlignRight);
    this->hBoxLayout->addSpacing(16);
    connect(this->button, &QPushButton::clicked, this, &PushSettingCard::clicked);
}



PrimaryPushSettingCard::PrimaryPushSettingCard(QString text, QVariant *icon, QString title, QString content, QWidget *parent) : PushSettingCard(text, icon, title, content, parent)
{
    this->button->setObjectName(QString("primaryButton"));
}


HyperlinkCard::HyperlinkCard(QString url, QString text, QVariant *icon, QString title, QString content, QWidget *parent) : SettingCard(icon, title, content, parent)
{
    QVariant _url = QVariant::fromValue<QString>(url);
    this->linkButton = new HyperlinkButton(&_url, text, this, nullptr);
    this->hBoxLayout->addWidget(this->linkButton, 0, Qt::AlignRight);
    this->hBoxLayout->addSpacing(16);
}




ColorPickerButton::ColorPickerButton(QColor color, QString title, QWidget *parent, bool enableAlpha) : QToolButton(parent)
{
    this->title = title;
    this->enableAlpha = enableAlpha;
    this->setFixedSize(96, 32);
    this->setAttribute(Qt::WA_TranslucentBackground);

    this->setColor(color);
    this->setCursor(Qt::PointingHandCursor);
    connect(this, &ColorPickerButton::clicked, this, &ColorPickerButton::__showColorDialog);
}

void ColorPickerButton::__showColorDialog()
{
    ColorDialog *w = new ColorDialog(this->color, this->tr("Choose ") + this->title, this->window(), this->enableAlpha);
    connect(w, &ColorDialog::colorChanged, this, &ColorPickerButton::__onColorChanged);
    w->exec();
}

void ColorPickerButton::setColor(QColor color)
{
    this->color = QColor(color);
    this->update();
}

void ColorPickerButton::__onColorChanged(QColor color)
{
    this->setColor(color);
    emit(this->colorChanged(color));
}

void ColorPickerButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    QColor pc = isDarkTheme() ? QColor(255, 255, 255, 10) : QColor(234, 234, 234);
    painter.setPen(pc);

    QColor _color = QColor(this->color);
    if(!this->enableAlpha){
        _color.setAlpha(255);
    }

    painter.setBrush(_color);
    painter.drawRoundedRect(this->rect().adjusted(1, 1, -1, -1), 5, 5);
    painter.end();
}


ColorSettingCard::ColorSettingCard(QVariant configItem, QVariant *icon, QString title, QString content, QWidget *parent, bool enableAlpha) : SettingCard(icon, title, content, parent)
{
    this->configItem = configItem;
    this->colorPicker = new ColorPickerButton(qconfig->get(configItem).value<QColor>(), title, this, enableAlpha);
    this->hBoxLayout->addWidget(this->colorPicker, 0, Qt::AlignRight);
    this->hBoxLayout->addSpacing(16);
    connect(this->colorPicker, &ColorPickerButton::colorChanged, this, &ColorSettingCard::__onColorChanged);
    connect(configItem.value<ColorConfigItem*>(), &ColorConfigItem::valueChanged, this, &ColorSettingCard::setValue);
}


void ColorSettingCard::__onColorChanged(QColor color)
{
    qconfig->set(this->configItem, QVariant::fromValue<QColor>(color), true, false);
    emit(this->colorChanged(color));
}

void ColorSettingCard::setValue(QColor color)
{
    this->colorPicker->setColor(color);
    qconfig->set(this->configItem, QVariant::fromValue<QColor>(color), true, false);
}


ComboBoxSettingCard::ComboBoxSettingCard(QVariant configItem, QVariant *icon, QString title, QString content, QList<QString> texts, QWidget *parent) : SettingCard(icon, title, content, parent)
{
    this->configItem = configItem;
    this->comboBox = new ComboBox(this);
    this->hBoxLayout->addWidget(this->comboBox, 0, Qt::AlignRight);
    this->hBoxLayout->addSpacing(16);

    this->optionToText = QMap<QString, QString>();
    for(int i = 0; i < texts.length(); i++){
        this->optionToText.insert(configItem.value<OptionsConfigItem*>()->options().at(i), texts.at(i));
        this->comboBox->addItem(texts.at(i), nullptr, new QVariant(QVariant::fromValue<QString>(configItem.value<OptionsConfigItem*>()->options().at(i))));
    }

    this->comboBox->setCurrentText(this->optionToText.value(qconfig->get(configItem).value<QString>()));
    connect(this->comboBox, &ComboBox::currentIndexChanged, this, &ComboBoxSettingCard::_onCurrentIndexChanged);
    connect(configItem.value<OptionsConfigItem*>(), &OptionsConfigItem::valueChanged, this, &ComboBoxSettingCard::setValue);
}


void ComboBoxSettingCard::_onCurrentIndexChanged(int index)
{
    qconfig->set(this->configItem, QVariant::fromValue<QString>(this->comboBox->itemData(index)->value<QString>()), true, false);
}

void ComboBoxSettingCard::setValue(QString value)
{
    if(!this->optionToText.contains(value)){
        return;
    }

    this->comboBox->setCurrentText(this->optionToText.value(value));
    qconfig->set(this->configItem, QVariant::fromValue<QString>(value), true, false);
}