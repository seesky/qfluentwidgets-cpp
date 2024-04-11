#include "setting_card_group.h"

SettingCardGroup::SettingCardGroup(QString title, QWidget *parent) : QWidget(parent)
{
    this->titleLabel = new QLabel(title, this);
    this->vBoxLayout = new QVBoxLayout(this);
    this->cardLayout = new ExpandLayout(nullptr);

    this->vBoxLayout->setContentsMargins(0, 0, 0, 0);
    this->vBoxLayout->setAlignment(Qt::AlignTop);
    this->vBoxLayout->setSpacing(0);
    this->cardLayout->setContentsMargins(0, 0, 0, 0);
    this->cardLayout->setSpacing(2);

    this->vBoxLayout->addWidget(this->titleLabel);
    this->vBoxLayout->addSpacing(12);
    this->vBoxLayout->addLayout(this->cardLayout, 1);

    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("SETTING_CARD_GROUP"), Theme::AUTO);
    Font().setFont(this->titleLabel, 20, QFont::Normal);
    this->titleLabel->adjustSize();
}

void SettingCardGroup::addSettingCard(QWidget *card)
{
    card->setParent(this);
    this->cardLayout->addWidget(card);
    this->adjustSize();
}

void SettingCardGroup::addSettingCards(QList<QWidget*> cards)
{
    for(int i = 0; i < cards.length(); i++){
        this->addSettingCard(cards.at(i));
    }
}

void SettingCardGroup::adjustSize()
{
    int h = this->cardLayout->heightForWidth(this->width()) + 46;
    return this->resize(this->width(), h);
}