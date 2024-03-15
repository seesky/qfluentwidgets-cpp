#include "dialog.h"


Dialog::Dialog(QString title, QString content, QWidget *parent) : FramelessDialog(parent)
{
    this->_setUpUi(title, content, this);

    this->windowTitleLabel = new QLabel(title, this);

    this->setResizeEnabled(false);
    this->resize(240, 192);
    this->titleBar->hide();

    this->vBoxLayout->insertWidget(0, this->windowTitleLabel, 0, Qt::AlignTop);
    this->windowTitleLabel->setObjectName(QString("windowTitleLabel"));
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("DIALOG"), Theme::AUTO);
    this->setFixedSize(this->size());
}


void Dialog::_setUpUi(QString title, QString content, QWidget *parent)
{
    this->content = content;
    this->titleLabel = new QLabel(title, parent);
    this->contentLabel = new QLabel(content, parent);

    this->buttonGroup = new QFrame(parent);
    this->yesButton = new PrimaryPushButton(this->tr("OK"), this->buttonGroup, nullptr);
    this->cancelButton = new QPushButton(this->tr("Cancel"), this->buttonGroup);

    this->vBoxLayout = new QVBoxLayout(parent);
    this->textLayout = new QVBoxLayout();
    this->buttonLayout = new QHBoxLayout(this->buttonGroup);

    this->__initWidget();
}

void Dialog::__initWidget()
{
    this->__setQss();
    this->__initLayout();

    this->yesButton->setAttribute(Qt::WA_LayoutUsesWidgetRect);
    this->cancelButton->setAttribute(Qt::WA_LayoutUsesWidgetRect);

    this->yesButton->setFocus();
    this->buttonGroup->setFixedHeight(81);

    this->_adjustText();

    connect(this->yesButton, &PrimaryPushButton::clicked, this, &Dialog::__onYesButtonClicked);
    connect(this->cancelButton, &QPushButton::clicked, this, &Dialog::__onCancelButtonClicked);
}

void Dialog::_adjustText()
{
    int w, chars;
    if(this->isWindow()){
        if(this->parent()){
            w = qMax(this->titleLabel->width(), ((QWidget *)this->parent())->width()); //TODO特殊关注
            chars = qMax(qMin(w / 9, 140), 30);
        }else{
            chars = 100;
        }
    }else{
        w = qMax(this->titleLabel->width(), this->window()->width());
        chars = qMax(qMin(w / 9, 100), 30);
    }

    this->contentLabel->setText(std::get<0>(TextWrap::wrap(this->content, chars, false, this->font())));
}


void Dialog::__initLayout()
{
    this->vBoxLayout->setSpacing(0);
    this->vBoxLayout->setContentsMargins(0, 0, 0, 0);
    this->vBoxLayout->addLayout(this->textLayout, 1);
    this->vBoxLayout->addWidget(this->buttonGroup, 0, Qt::AlignBottom);
    this->vBoxLayout->setSizeConstraint(QVBoxLayout::SetMinimumSize);

    this->textLayout->setSpacing(12);
    this->textLayout->setContentsMargins(24, 24, 24, 24);
    this->textLayout->addWidget(this->titleLabel, 0, Qt::AlignTop);
    this->textLayout->addWidget(this->contentLabel, 0, Qt::AlignTop);

    this->buttonLayout->setSpacing(12);
    this->buttonLayout->setContentsMargins(24, 24, 24, 24);
    this->buttonLayout->addWidget(this->yesButton, 1, Qt::AlignVCenter);
    this->buttonLayout->addWidget(this->cancelButton, 1, Qt::AlignVCenter);
}

void Dialog::__onCancelButtonClicked()
{
    this->reject();
    emit(this->cancelSignal());
}

void Dialog::__onYesButtonClicked()
{
    this->accept();
    emit(this->yesSignal());
}

void Dialog::__setQss()
{
    this->titleLabel->setObjectName(QString("titleLabel"));
    this->contentLabel->setObjectName(QString("contentLabel"));
    this->buttonGroup->setObjectName(QString("buttonGroup"));
    this->cancelButton->setObjectName(QString("cancelButton"));

    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("DIALOG"), Theme::AUTO);

    this->yesButton->adjustSize();
    this->cancelButton->adjustSize();
}

void Dialog::setContentCopyable(bool isCopyable)
{
    if(isCopyable){
        this->contentLabel->setTextInteractionFlags(Qt::TextInteractionFlag::TextSelectableByMouse);
    }else{
        this->contentLabel->setTextInteractionFlags(Qt::TextInteractionFlag::NoTextInteraction);
    }
}

void Dialog::setTitleBarVisible(bool isVisible)
{
    this->windowTitleLabel->setVisible(isVisible);
}


MessageBoxF::MessageBoxF(QString title, QString content, QWidget *parent) : MaskDialogBase(parent)
{
    this->_setUpUi(title, content, this->widget);

    this->setShadowEffect(60, std::tuple<int,int>(0, 10), QColor(0, 0, 0, 50));
    this->setMaskColor(QColor(0, 0, 0, 76));
    this->_hBoxLayout->removeWidget(this->widget);
    this->_hBoxLayout->addWidget(this->widget, 1, Qt::AlignCenter);

    this->buttonGroup->setMinimumWidth(280);
    this->widget->setFixedSize(
        qMax(this->contentLabel->width(), this->titleLabel->width()) + 48,
        this->contentLabel->y() + this->contentLabel->height() + 105
    );
}




void MessageBoxF::_setUpUi(QString title, QString content, QWidget *parent)
{
    this->content = content;
    this->titleLabel = new QLabel(title, parent);
    this->contentLabel = new QLabel(content, parent);

    this->buttonGroup = new QFrame(parent);
    this->yesButton = new PrimaryPushButton(this->tr("OK"), this->buttonGroup, nullptr);
    this->cancelButton = new QPushButton(this->tr("Cancel"), this->buttonGroup);

    this->vBoxLayout = new QVBoxLayout(parent);
    this->textLayout = new QVBoxLayout();
    this->buttonLayout = new QHBoxLayout(this->buttonGroup);

    this->__initWidget();
}

void MessageBoxF::__initWidget()
{
    this->__setQss();
    this->__initLayout();

    this->yesButton->setAttribute(Qt::WA_LayoutUsesWidgetRect);
    this->cancelButton->setAttribute(Qt::WA_LayoutUsesWidgetRect);

    this->yesButton->setFocus();
    this->buttonGroup->setFixedHeight(81);

    this->_adjustText();

    connect(this->yesButton, &PrimaryPushButton::clicked, this, &MessageBoxF::__onYesButtonClicked);
    connect(this->cancelButton, &QPushButton::clicked, this, &MessageBoxF::__onCancelButtonClicked);
}

void MessageBoxF::_adjustText()
{
    int w, chars;
    if(this->isWindow()){
        if(this->parent()){
            w = qMax(this->titleLabel->width(), ((QWidget *)this->parent())->width()); //TODO:特殊关注
            chars = qMax(qMin(w / 9, 140), 30);
        }else{
            chars = 100;
        }
    }else{
        w = qMax(this->titleLabel->width(), ((QWidget *)this->parent())->width()); //TODO:特殊关注
        chars = qMax(qMin(w / 9, 100), 30);
    }

    this->contentLabel->setText(std::get<0>(TextWrap::wrap(this->content, chars, false, this->font())));
}


void MessageBoxF::__initLayout()
{
    this->vBoxLayout->setSpacing(0);
    this->vBoxLayout->setContentsMargins(0, 0, 0, 0);
    this->vBoxLayout->addLayout(this->textLayout, 1);
    this->vBoxLayout->addWidget(this->buttonGroup, 0, Qt::AlignBottom);
    this->vBoxLayout->setSizeConstraint(QVBoxLayout::SetMinimumSize);

    this->textLayout->setSpacing(12);
    this->textLayout->setContentsMargins(24, 24, 24, 24);
    this->textLayout->addWidget(this->titleLabel, 0, Qt::AlignTop);
    this->textLayout->addWidget(this->contentLabel, 0, Qt::AlignTop);

    this->buttonLayout->setSpacing(12);
    this->buttonLayout->setContentsMargins(24, 24, 24, 24);
    this->buttonLayout->addWidget(this->yesButton, 1, Qt::AlignVCenter);
    this->buttonLayout->addWidget(this->cancelButton, 1, Qt::AlignVCenter);
}

void MessageBoxF::__onCancelButtonClicked()
{
    this->reject();
    emit(this->cancelSignal());
}

void MessageBoxF::__onYesButtonClicked()
{
    this->accept();
    emit(this->yesSignal());
}

void MessageBoxF::__setQss()
{
    this->titleLabel->setObjectName(QString("titleLabel"));
    this->contentLabel->setObjectName(QString("contentLabel"));
    this->buttonGroup->setObjectName(QString("buttonGroup"));
    this->cancelButton->setObjectName(QString("cancelButton"));

    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("DIALOG"), Theme::AUTO);

    this->yesButton->adjustSize();
    this->cancelButton->adjustSize();
}

void MessageBoxF::setContentCopyable(bool isCopyable)
{
    if(isCopyable){
        this->contentLabel->setTextInteractionFlags(Qt::TextInteractionFlag::TextSelectableByMouse);
    }else{
        this->contentLabel->setTextInteractionFlags(Qt::TextInteractionFlag::NoTextInteraction);
    }
}

bool MessageBoxF::eventFilter(QObject *obj, QEvent *e)
{
    if(obj == this->window()){
        if(e->type() == QEvent::Resize){
            this->_adjustText();
        }
    }
    return MaskDialogBase::eventFilter(obj, e);
}