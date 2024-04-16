#include "icon_interface.h"

IconSearchLineEdit::IconSearchLineEdit(QWidget *parent) : SearchLineEdit(parent)
{
    this->setPlaceholderText(this->tr("Search icons"));
    this->setFixedWidth(304);
    connect(this, &IconSearchLineEdit::textChanged, this, &IconSearchLineEdit::search);
}


IconCard::IconCard(FluentIcon *icon, QWidget *parent) : QFrame(parent)
{
    this->icon = icon;
    this->isSelected = false;

    this->iconWidget = new IconWidget(*icon, this);
    this->nameLabel = new QLabel(this);
    this->vBoxLayout = new QVBoxLayout(this);

    this->setFixedSize(96, 96);
    this->vBoxLayout->setSpacing(0);
    this->vBoxLayout->setContentsMargins(8, 28, 8, 0);
    this->vBoxLayout->setAlignment(Qt::AlignTop);
    this->iconWidget->setFixedSize(28, 28);
    this->vBoxLayout->addWidget(this->iconWidget, 0, Qt::AlignHCenter);
    this->vBoxLayout->addSpacing(14);
    this->vBoxLayout->addWidget(this->nameLabel, 0, Qt::AlignHCenter);

    QString text = this->nameLabel->fontMetrics().elidedText(icon->iconName, Qt::ElideRight, 90);
    this->nameLabel->setText(text);
}


void IconCard::mouseReleaseEvent(QMouseEvent *event)
{
    if(this->isSelected){
        return;
    }

    emit(this->clicked(this->icon));
}


void IconCard::setSelected(bool isSelected, bool force)
{
    if(isSelected == this->isSelected && !force){
        return;
    }

    this->isSelected = isSelected;

    if(!isSelected){
        this->iconWidget->setIcon(new QVariant(QVariant::fromValue<FluentIcon>(*(this->icon))));
    }else{
        QIcon *icon = this->icon->icon(isDarkTheme() ? Theme::LIGHT : Theme::DARK, QColor());
        this->iconWidget->setIcon(new QVariant(QVariant::fromValue<QIcon>(*(icon))));
    }

    this->setProperty("isSelected", isSelected);
    this->setStyle(QApplication::style());
}


IconInfoPanel::IconInfoPanel(FluentIcon *icon, QWidget *parent) : QFrame(parent)
{
    this->nameLabel = new QLabel(icon->iconName, this);
    this->iconWidget = new IconWidget(*icon, this);
    this->iconNameTitleLabel = new QLabel(this->tr("Icon name"), this);
    this->iconNameLabel = new QLabel(icon->iconName, this);
    this->enumNameTitleLabel = new QLabel(this->tr("Enum member"), this);
    this->enumNameLabel = new QLabel(QString("FluentIconMap.%1").arg(icon->iconName), this);

    this->vBoxLayout = new QVBoxLayout(this);
    this->vBoxLayout->setContentsMargins(16, 20, 16, 20);
    this->vBoxLayout->setSpacing(0);
    this->vBoxLayout->setAlignment(Qt::AlignTop);

    this->vBoxLayout->addWidget(this->nameLabel);
    this->vBoxLayout->addSpacing(16);
    this->vBoxLayout->addWidget(this->iconWidget);
    this->vBoxLayout->addSpacing(45);
    this->vBoxLayout->addWidget(this->iconNameTitleLabel);
    this->vBoxLayout->addSpacing(5);
    this->vBoxLayout->addWidget(this->iconNameLabel);
    this->vBoxLayout->addSpacing(34);
    this->vBoxLayout->addWidget(this->enumNameTitleLabel);
    this->vBoxLayout->addSpacing(5);
    this->vBoxLayout->addWidget(this->enumNameLabel);

    this->iconWidget->setFixedSize(48, 48);
    this->setFixedWidth(216);

    this->nameLabel->setObjectName("nameLabel");
    this->iconNameTitleLabel->setObjectName("subTitleLabel");
    this->enumNameTitleLabel->setObjectName("subTitleLabel");
}

void IconInfoPanel::setIcon(FluentIcon *icon)
{
    this->iconWidget->setIcon(new QVariant(QVariant::fromValue<FluentIcon>(*icon)));
    this->nameLabel->setText(icon->iconName);
    this->iconNameLabel->setText(icon->iconName);
    this->enumNameLabel->setText(QString("FluentIconMap.%1").arg(icon->iconName));
}

/*
IconCardView::IconCardView(QWidget *parent) : QWidget(parent)
{

}
*/