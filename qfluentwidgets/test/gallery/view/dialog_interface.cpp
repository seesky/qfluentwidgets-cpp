#include "dialog_interface.h"

DialogInterface::DialogInterface(QWidget *parent) : GalleryInterface(Translator(nullptr).dialogs, "fluentwidgets.components.dialog_box", parent)
{
    this->setObjectName("dialogInterface");

    PushButton *showDialogPushButton = new PushButton(this->tr("Show dialog"), nullptr, nullptr);
    connect(showDialogPushButton, &PushButton::clicked, this, &DialogInterface::showDialog);
    this->addExampleCard(
        this->tr("A frameless message box"),
        showDialogPushButton,
        "http://www.github.com", 0
    );

    PushButton *showMessageDialogPushButton = new PushButton(this->tr("Show dialog"), nullptr, nullptr);
    connect(showMessageDialogPushButton, &PushButton::clicked, this, &DialogInterface::showMessageDialog);
    this->addExampleCard(
        this->tr("A message box with mask"),
        showMessageDialogPushButton,
        "http://www.github.com", 0
    );


    PushButton *showCustomDialogPushButton = new PushButton(this->tr("Show dialog"), nullptr, nullptr);
    connect(showCustomDialogPushButton, &PushButton::clicked, this, &DialogInterface::showCustomDialog);
    this->addExampleCard(
        this->tr("A custom message box"),
        showCustomDialogPushButton,
        "http://www.github.com", 0
    );


    PushButton *showColorDialogPushButton = new PushButton(this->tr("Show dialog"), nullptr, nullptr);
    connect(showColorDialogPushButton, &PushButton::clicked, this, &DialogInterface::showColorDialog);
    this->addExampleCard(
        this->tr("A color dialog"),
        showColorDialogPushButton,
        "http://www.github.com", 0
    );

    this->showSimpleFlyoutPushButton = new PushButton(this->tr("Show flyout"), nullptr, nullptr);
    connect(showSimpleFlyoutPushButton, &PushButton::clicked, this, &DialogInterface::showSimpleFlyout);
    this->addExampleCard(
        this->tr("A simple flyout"),
        showSimpleFlyoutPushButton,
        "http://www.github.com", 0
    );

    this->showComplexFlyoutButton = new PushButton(this->tr("Show flyout"), nullptr, nullptr);
    connect(showComplexFlyoutButton, &PushButton::clicked, this, &DialogInterface::showComplexFlyout);
    this->addExampleCard(
        this->tr("A flyout with image and button"),
        showComplexFlyoutButton,
        "http://www.github.com", 0
    );

    this->teachingButton = new PushButton(this->tr("Show teaching tip"), nullptr, nullptr);
    connect(teachingButton, &PushButton::clicked, this, &DialogInterface::showBottomTeachingTip);
    this->addExampleCard(
        this->tr("A teaching tip"),
        teachingButton,
        "http://www.github.com", 0
    );

    this->teachingRightButton = new PushButton(this->tr("Show teaching tip"), nullptr, nullptr);
    connect(teachingRightButton, &PushButton::clicked, this, &DialogInterface::showLeftBottomTeachingTip);
    this->addExampleCard(
        this->tr("A teaching tip with image and button"),
        teachingRightButton,
        "http://www.github.com", 0
    );
}

void DialogInterface::showDialog()
{
    QString title = this->tr("This is a frameless message dialog");
    QString content = this->tr("If the content of the message box is veeeeeeeeeeeeeeeeeeeeeeeeeery long, it will automatically wrap like this.");
    Dialog *w = new Dialog(title, content, this->window());
    if(w->exec()){
        qDebug() << "Yes button is pressed";
    }else{
        qDebug() << "Cancel button is pressed";
    }
}


void DialogInterface::showMessageDialog()
{
    QString title = this->tr("This is a message dialog with mask");
    QString content = this->tr("If the content of the message box is veeeeeeeeeeeeeeeeeeeeeeeeeery long, it will automatically wrap like this.");
    MessageBoxF *w = new MessageBoxF(title, content, this->window());
    if(w->exec()){
        qDebug() << "Yes button is pressed";
    }else{
        qDebug() << "Cancel button is pressed";
    }
}


void DialogInterface::showCustomDialog()
{
    CustomMessageBox *w = new CustomMessageBox(this->window());
    if(w->exec()){
        qDebug() << w->urlLineEdit->text();
    }
}



void DialogInterface::showColorDialog()
{
    ColorDialog *w = new ColorDialog(Qt::cyan, this->tr("Choose color"), this->window(), true);
    connect(w, &ColorDialog::colorChanged, this, [](QColor c){
        qDebug() << c.name();
    });
    w->exec();
}


void DialogInterface::showSimpleFlyout()
{
    Flyout::create(
        "Lesson 3",
        this->tr("Believe in the spin, just keep believing!"),
        new QVariant(),
        new QVariant(),
        true,
        QVariant::fromValue<PushButton*>(this->showSimpleFlyoutPushButton),
        this->window(),
        FlyoutAnimationType::PULL_UP,
        true
    );
}

void DialogInterface::showComplexFlyout()
{
    FlyoutView *view = new FlyoutView(
        QString(this->tr("Julius·Zeppeli")),
        QString(this->tr("Where the tennis ball will land when it touches the net, no one can predict. \nIf that moment comes, I hope the 'goddess' exists. \nIn that case, I would accept it no matter which side the ball falls on.")),
        new QVariant(),
        new QVariant(QVariant::fromValue<QString>(QString("qfluentwidgets/images/SBR.jpg"))),
        false,
        nullptr
    );

    PushButton *button = new PushButton(QString("Action"), nullptr, nullptr);
    button->setFixedWidth(120);
    view->addWidget(button, 0, Qt::AlignRight);

    view->widgetLayout->insertSpacing(1, 5);
    view->widgetLayout->addSpacing(5);

    Flyout *w = Flyout::make(view, QVariant::fromValue<QWidget*>(this->showComplexFlyoutButton), this, FlyoutAnimationType::PULL_UP, true);
}


void DialogInterface::showBottomTeachingTip()
{
    InfoBarIcon *_icon = new InfoBarIcon();
    _icon->setIconName(QString("SUCCESS"));
    QVariant *__icon = new QVariant();
    __icon->setValue<InfoBarIcon>(*_icon);
    TeachingTip::create(
        this->teachingButton, 
        QString("Lesson 4"), 
        this->tr("With respect, let's advance towards a new stage of the spin."), 
        __icon, 
        new QVariant(), 
        true, 
        -1, 
        TeachingTipTailPosition::BOTTOM, 
        this, 
        true);
}


void DialogInterface::showLeftBottomTeachingTip()
{
    TeachingTipTailPosition position = TeachingTipTailPosition::BOTTOM_RIGHT;
    TeachingTipView *view = new TeachingTipView(
        QString("Lesson 5"), 
        this->tr("The shortest shortcut is to take a detour."), 
        new QVariant(), 
        new QVariant(QVariant::fromValue<QString>(QString("qfluentwidgets/images/Gyro.jpg"))), 
        true, 
        position, 
        nullptr);
    PushButton *button = new PushButton(QString("Action"), nullptr, nullptr);
    button->setFixedWidth(120);
    view->addWidget(button, 0, Qt::AlignRight);

    TeachingTip *w = TeachingTip::make(view, this->teachingRightButton, -1, position, this, true);

    connect(view, &TeachingTipView::closed, w, &TeachingTip::close);
}


CustomMessageBox::CustomMessageBox(QWidget *parent) : MessageBoxBase(parent)
{
    this->titleLabel = new SubtitleLabel(this->tr("Open URL"), this);
    this->urlLineEdit = new LineEdit(this);

    this->urlLineEdit->setPlaceholderText(this->tr("Enter the URL of a file, stream, or playlist"));
    this->urlLineEdit->setClearButtonEnabled(true);

    this->viewLayout->addWidget(this->titleLabel);
    this->viewLayout->addWidget(this->urlLineEdit);

    this->yesButton->setText(this->tr("Open"));
    this->cancelButton->setText(this->tr("Cancel"));

    this->widget->setMinimumWidth(360);
    this->yesButton->setDisabled(true);
    connect(this->urlLineEdit, &LineEdit::textChanged, this, &CustomMessageBox::_validateUrl);    
}

void CustomMessageBox::_validateUrl(QString text){
    this->yesButton->setEnabled(QUrl(text).isValid());
};