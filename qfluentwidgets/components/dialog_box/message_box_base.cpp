#include "message_box_base.h"

MessageBoxBase::MessageBoxBase(QWidget *parent) : MaskDialogBase(parent)
{
    this->buttonGroup = new QFrame(this->widget);
    this->yesButton = new PrimaryPushButton(this->tr("OK"), this->buttonGroup, nullptr);
    this->cancelButton = new QPushButton(this->tr("Cancel"), this->buttonGroup);

    this->vBoxLayout = new QVBoxLayout(this->widget);
    this->viewLayout = new QVBoxLayout();
    this->buttonLayout = new QHBoxLayout(this->buttonGroup);

    this->__initWidget();
}

void MessageBoxBase::__initWidget()
{
    this->__setQss();
    this->__initLayout();

    this->setShadowEffect(60, std::tuple<int, int>(0, 10), QColor(0, 0, 0, 50));
    this->setMaskColor(QColor(0, 0, 0, 76));

    this->yesButton->setAttribute(Qt::WA_LayoutUsesWidgetRect);
    this->cancelButton->setAttribute(Qt::WA_LayoutUsesWidgetRect);

    this->yesButton->setFocus();
    this->buttonGroup->setFixedHeight(81);

    connect(this->yesButton, &PrimaryPushButton::clicked, this, &MessageBoxBase::__onYesButtonClicked);
    connect(this->cancelButton, &QPushButton::clicked, this, &MessageBoxBase::__onCancelButtonClicked);
}


void MessageBoxBase::__initLayout()
{
    this->_hBoxLayout->removeWidget(this->widget);
    this->_hBoxLayout->addWidget(this->widget, 1, Qt::AlignCenter);
    
    this->vBoxLayout->setSpacing(0);
    this->vBoxLayout->setContentsMargins(0, 0, 0, 0);
    this->vBoxLayout->addLayout(this->viewLayout, 1);
    this->vBoxLayout->addWidget(this->buttonGroup, 0, Qt::AlignBottom);

    this->viewLayout->setSpacing(12);
    this->viewLayout->setContentsMargins(24, 24, 24, 24);

    this->buttonLayout->setSpacing(12);
    this->buttonLayout->setContentsMargins(24, 24, 24, 24);
    this->buttonLayout->addWidget(this->yesButton, 1, Qt::AlignVCenter);
    this->buttonLayout->addWidget(this->cancelButton, 1, Qt::AlignVCenter);
}


void MessageBoxBase::__onCancelButtonClicked()
{
    this->reject();
    emit(this->rejected());
}

void MessageBoxBase::__onYesButtonClicked()
{
    this->accept();
    emit(this->accepted());
}

void MessageBoxBase::__setQss()
{
    this->buttonGroup->setObjectName(QString("buttonGroup"));
    this->cancelButton->setObjectName(QString("cancelButton"));
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("DIALOG"), Theme::AUTO);
}

void MessageBoxBase::hideYesButton()
{
    this->yesButton->hide();
    this->buttonLayout->insertStretch(0, 1);
}

void MessageBoxBase::hideCancelButton()
{
    this->cancelButton->hide();
    this->buttonLayout->insertStretch(0, 1);
}



