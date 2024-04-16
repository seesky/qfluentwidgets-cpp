#include "link_card.h"

LinkCard::LinkCard(QVariant *icon, QString title, QString content, QString url, QWidget *parent) : QFrame(parent)
{
    this->url = QUrl(url);
    this->setFixedSize(198, 220);
    this->iconWidget = new IconWidget(icon, this);
    this->titleLabel = new QLabel(title, this);
    this->contentLabel = new QLabel(std::get<0>(TextWrap::wrap(content, 28, false, this->font())), this);
    FluentIcon *iconLine = new FluentIcon();
    iconLine->setIconName(QString("LINK"));
    this->urlWidget = new IconWidget(*iconLine, this);

    this->__initWidget();
}


void LinkCard::__initWidget()
{
    this->setCursor(Qt::PointingHandCursor);

    this->iconWidget->setFixedSize(54, 54);
    this->urlWidget->setFixedSize(16, 16);

    this->vBoxLayout = new QVBoxLayout(this);
    this->vBoxLayout->setSpacing(0);
    this->vBoxLayout->setContentsMargins(24, 24, 0, 13);
    this->vBoxLayout->addWidget(this->iconWidget);
    this->vBoxLayout->addSpacing(16);
    this->vBoxLayout->addWidget(this->titleLabel);
    this->vBoxLayout->addSpacing(8);
    this->vBoxLayout->addWidget(this->contentLabel);
    this->vBoxLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    this->urlWidget->move(170, 192);

    this->titleLabel->setObjectName("titleLabel");
    this->contentLabel->setObjectName("contentLabel");
}

void LinkCard::mouseReleaseEvent(QMouseEvent *event)
{
    QFrame::mouseReleaseEvent(event);
    QDesktopServices::openUrl(this->url);
}


LinkCardView::LinkCardView(QWidget *parent) : SingleDirectionScrollArea(parent, Qt::Vertical)
{
    this->view = new QWidget(this);
    this->hBoxLayout = new QHBoxLayout(this->view);

    this->hBoxLayout->setContentsMargins(36, 0, 0, 0);
    this->hBoxLayout->setSpacing(12);
    this->hBoxLayout->setAlignment(Qt::AlignLeft);

    this->setWidget(this->view);
    this->setWidgetResizable(true);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->view->setObjectName("view");
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("LINK_CARD"), Theme::AUTO);
}


void LinkCardView::addCard(QVariant *icon, QString title, QString content, QString url)
{
    LinkCard *card = new LinkCard(icon, title, content, url, this->view);
    this->hBoxLayout->addWidget(card, 0, Qt::AlignLeft);
}