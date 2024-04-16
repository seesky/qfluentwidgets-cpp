#include "sample_card.h"

SampleCard::SampleCard(QVariant *icon, QString title, QString content, QString routeKey, int index, QWidget *parent) : CardWidget(parent)
{
    this->index = index;
    this->routeKey = routeKey;

    this->iconWidget = new IconWidget(icon, this);
    this->titleLabel = new QLabel(title, this);
    this->contentLabel = new QLabel(std::get<0>(TextWrap::wrap(content, 45, false, this->font())), this);

    this->hBoxLayout = new QHBoxLayout(this);
    this->vBoxLayout = new QVBoxLayout();

    this->setFixedSize(360, 90);
    this->iconWidget->setFixedSize(48, 48);

    this->hBoxLayout->setSpacing(28);
    this->hBoxLayout->setContentsMargins(20, 0, 0, 0);
    this->vBoxLayout->setSpacing(2);
    this->vBoxLayout->setContentsMargins(0, 0, 0, 0);
    this->vBoxLayout->setAlignment(Qt::AlignVCenter);

    this->hBoxLayout->setAlignment(Qt::AlignVCenter);
    this->hBoxLayout->addWidget(this->iconWidget);
    this->hBoxLayout->addLayout(this->vBoxLayout);
    this->vBoxLayout->addStretch(1);
    this->vBoxLayout->addWidget(this->titleLabel);
    this->vBoxLayout->addWidget(this->contentLabel);
    this->vBoxLayout->addStretch(1);

    this->titleLabel->setObjectName("titleLabel");
    this->contentLabel->setObjectName("contentLabel");
}


void SampleCard::mouseReleaseEvent(QMouseEvent *e) 
{   
    CardWidget::mouseReleaseEvent(e);
    emit(signalBus->switchToSampleCard(this->routeKey, this->index));
}


SampleCardView::SampleCardView(QString title, QWidget *parent) : QWidget(parent)
{
    this->titleLabel = new QLabel(title, this);
    this->vBoxLayout = new QVBoxLayout(this);
    this->flowLayout = new FlowLayout(nullptr, false, false);

    this->vBoxLayout->setContentsMargins(36, 0, 36, 0);
    this->vBoxLayout->setSpacing(10);
    this->flowLayout->setContentsMargins(0, 0, 0, 0);
    this->flowLayout->setHorizontalSpacing(12);
    this->flowLayout->setVerticalSpacing(12);

    this->vBoxLayout->addWidget(this->titleLabel);
    this->vBoxLayout->addLayout(this->flowLayout, 1);

    this->titleLabel->setObjectName("viewTitleLabel");
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("SAMPLE_CARD"), Theme::AUTO);
}


void SampleCardView::addSampleCard(QVariant *icon, QString title, QString content, QString routeKey, int index)
{
    SampleCard *card = new SampleCard(icon, title, content, routeKey, index, this);
    this->flowLayout->addWidget(card);
}