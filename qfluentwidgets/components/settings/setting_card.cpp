#include "setting_card.h"

/*
SettingCard::SettingCard(QVariant icon, QString title, QString content, QWidget *parent) : QFrame(parent)
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
    this->hBoxLayout->setSpacing(0);
    this->hBoxLayout->setContentsMargins(0, 0, 0, 0);
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
    QPainter *painter = new QPainter(this);
    painter->setRenderHints(QPainter::Antialiasing);

    if(isDarkTheme()){
        painter->setBrush(QColor(255, 255, 255, 13));
        painter->setPen(QColor(0, 0, 0, 50));
    }else{
        painter->setBrush(QColor(255, 255, 255, 170));
        painter->setPen(QColor(0, 0, 0, 19));
    }

    painter->drawRoundedRect(this->rect().adjusted(1, 1, -1, -1), 6, 6);
}

SwitchSettingCard::SwitchSettingCard(QVariant icon, QString title, QString content, ConfigItem *configItem, QWidget *parent) : SettingCard(icon, title, content, parent)
{
    this->configItem = configItem;
    this->switchButton = new SwitchButton(this->tr("Off"), this, IndicatorPosition::RIGHT);

    if(configItem != nullptr){
        
    }
}
*/










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
    //QPainter *painter = new QPainter(this);
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