#include "message_dialog.h"

MessageDialog::MessageDialog(QString title, QString content, QWidget *parent) : MaskDialogBase(parent)
{
    this->content = content;
    this->titleLabel = new QLabel(title, this->widget);
    this->contentLabel = new QLabel(content, this->widget);
    this->yesButton = new QPushButton(this->tr("OK"), this->widget);
    this->cancelButton = new QPushButton(this->tr("Cancel"), this->widget);
    this->__initWidget();
}

void MessageDialog::__initWidget()
{
    this->windowMask->resize(this->size());
    this->widget->setMaximumWidth(540);
    this->titleLabel->move(24, 24);
    this->contentLabel->move(24, 56);
    this->contentLabel->setText(std::get<0>(TextWrap::wrap(this->content, 71, true, this->font())));

    this->__setQss();
    this->__initLayout();

    connect(this->yesButton, &QPushButton::clicked, this, &MessageDialog::__onYesButtonClicked);
    connect(this->cancelButton, &QPushButton::clicked, this, &MessageDialog::__onCancelButtonClicked);
}


void MessageDialog::__initLayout()
{
    this->contentLabel->adjustSize();
    this->widget->setFixedSize(48 + this->contentLabel->width(), this->contentLabel->y() + this->contentLabel->height() + 92);
    this->yesButton->resize((this->widget->width() - 54) / 2, 32);
    this->cancelButton->resize(this->yesButton->width(), 32);
    this->yesButton->move(24, this->widget->height() - 56);
    this->cancelButton->move(this->widget->width() - 24 - this->cancelButton->width(), this->widget->height() - 56);
}

void MessageDialog::__onCancelButtonClicked()
{
    emit(this->cancelSignal());
    this->setResult(this->Rejected);
    this->close();
}

void MessageDialog::__onYesButtonClicked()
{
    this->setEnabled(false);
    emit(this->yesSignal());
    this->setResult(this->Accepted);
    this->close();
}

void MessageDialog::__setQss()
{
    this->windowMask->setObjectName("windowMask");
    this->titleLabel->setObjectName("titleLabel");
    this->contentLabel->setObjectName("contentLabel");
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("MESSAGE_DIALOG"), Theme::AUTO);
}