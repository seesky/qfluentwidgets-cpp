#include "status_info_interface.h"


StatusInfoInterface::StatusInfoInterface(QWidget *parent) : GalleryInterface(Translator(nullptr).statusInfo, "fluentwidgets.components.widgets", parent)
{
    this->setObjectName("statusInfoInterface");

    this->stateTooltip = nullptr;

    PushButton *button1 = new PushButton(this->tr("Show StateToolTip"), nullptr, nullptr);
    connect(button1, &PushButton::clicked, this, &StatusInfoInterface::onStateButtonClicked);
    this->addExampleCard(
        this->tr("State tool tip"),
        button1,
        "http://www.github.com", 0
    );

    
    PushButton *button2 = new PushButton(this->tr("Button with a simple ToolTip"), nullptr, nullptr);
    button2->installEventFilter(new ToolTipFilter(button2, 500, ToolTipPosition::TOP));
    button2->setToolTip(this->tr("Simple ToolTip"));
    this->addExampleCard(
        this->tr("A button with a simple ToolTip"),
        button2,
        "http://www.github.com", 0
    );

    
    PixmapLabel *label = new PixmapLabel(nullptr);
    label->setPixmap(new QPixmap("qfluentwidgets/images/kunkun.png"));
    label->installEventFilter(new ToolTipFilter(label, 500, ToolTipPosition::TOP));
    label->setToolTip(this->tr("Label with a ToolTip"));
    label->setToolTipDuration(2000);
    label->setFixedSize(160, 160);
    this->addExampleCard(
        this->tr("A label with a ToolTip"),
        label,
        "http://www.github.com", 0
    );

    
    QWidget *w = new QWidget();
    w->setLayout(new QHBoxLayout());
    w->layout()->addWidget(InfoBadge::info(new QVariant(QVariant::fromValue<int>(1)), nullptr, nullptr, InfoBadgePosition::TOP_RIGHT));
    w->layout()->addWidget(InfoBadge::success(new QVariant(QVariant::fromValue<int>(10)), nullptr, nullptr, InfoBadgePosition::TOP_RIGHT));
    w->layout()->addWidget(InfoBadge::attension(new QVariant(QVariant::fromValue<int>(100)), nullptr, nullptr, InfoBadgePosition::TOP_RIGHT));
    w->layout()->addWidget(InfoBadge::warning(new QVariant(QVariant::fromValue<int>(1000)), nullptr, nullptr, InfoBadgePosition::TOP_RIGHT));
    w->layout()->addWidget(InfoBadge::error(new QVariant(QVariant::fromValue<int>(10000)), nullptr, nullptr, InfoBadgePosition::TOP_RIGHT));
    w->layout()->addWidget(InfoBadge::custom(new QVariant(QVariant::fromValue<QString>("1w+")), QColor("#005fb8"), QColor("#60cdff"), nullptr, nullptr, InfoBadgePosition::TOP_RIGHT));
    w->layout()->setSpacing(20);
    w->layout()->setContentsMargins(0, 10, 0, 10);
    this->addExampleCard(
        this->tr("InfoBadge in different styles"),
        w, 
        "http://www.github.com", 0
    );

    
    //short info bar
    InfoBarIcon *successInfoBaricon = new InfoBarIcon();
    successInfoBaricon->setIconName(QString("SUCCESS"));
    InfoBar *successInfoBar = new InfoBar(successInfoBaricon, this->tr("Success"), this->tr("The Anthem of man is the Anthem of courage."), Qt::Orientation::Horizontal, true, -1, InfoBarPosition::NONE, this);
    this->addExampleCard(
        this->tr("A closable InfoBar"),
        successInfoBar,
        "http://www.github.com", 0
    );

    QString content = this->tr("My name is kira yoshikake, 33 years old. Living in the villa area northeast of duwangting, unmarried. I work in Guiyou chain store. Every day I have to work overtime until 8 p.m. to go home. I don't smoke. The wine is only for a taste. Sleep at 11 p.m. for 8 hours a day. Before I go to bed, I must drink a cup of warm milk, then do 20 minutes of soft exercise, get on the bed, and immediately fall asleep. Never leave fatigue and stress until the next day. Doctors say I'm normal.");
    InfoBarIcon *warningInfoBaricon = new InfoBarIcon();
    warningInfoBaricon->setIconName(QString("WARNING"));
    InfoBar *warningInfoBar = new InfoBar(
        warningInfoBaricon, 
        this->tr("Warning"), 
        content, 
        Qt::Orientation::Vertical, 
        true, 
        -1, 
        InfoBarPosition::NONE, 
        this);
    this->addExampleCard(
        this->tr("A closable InfoBar with long message"),
        warningInfoBar,
        "http://www.github.com", 0
    );

    InfoBarIcon *githubInfoBaricon = new InfoBarIcon();
    githubInfoBaricon->setIconName(QString("SUCCESS"));
    InfoBar *githubInfoBar = new InfoBar(
        githubInfoBaricon, 
        this->tr("GitHub"), 
        this->tr("When you look long into an abyss, the abyss looks into you."), 
        Qt::Orientation::Horizontal, 
        true, 
        -1, 
        InfoBarPosition::NONE, 
        this);
    githubInfoBar->addWidget(new PushButton(this->tr("Action"), nullptr, nullptr), 0);
    githubInfoBar->setCustomBackgroundColor(QVariant::fromValue<QString>("white"), QVariant::fromValue<QString>("#2a2a2a"));
    this->addExampleCard(
        this->tr("An InfoBar with custom icon, background color and widget."),
        githubInfoBar,
        "http://www.github.com", 0
    );


    QWidget *w2 = new QWidget(this);
    QHBoxLayout *hBoxlayout = new QHBoxLayout(w2);
    PushButton *button3 = new PushButton(this->tr("Top right"), w2, nullptr); 
    PushButton *button4 = new PushButton(this->tr("Top"), w2, nullptr);
    PushButton *button5 = new PushButton(this->tr("Top left"), w2, nullptr);
    PushButton *button6 = new PushButton(this->tr("Bottom right"), w2, nullptr);
    PushButton *button7 = new PushButton(this->tr("Bottom"), w2, nullptr);
    PushButton *button8 = new PushButton(this->tr("Bottom left"), w2, nullptr);

    connect(button3, &PushButton::clicked, this, &StatusInfoInterface::createTopRightInfoBar);
    connect(button4, &PushButton::clicked, this, &StatusInfoInterface::createTopInfoBar);
    connect(button5, &PushButton::clicked, this, &StatusInfoInterface::createTopLeftInfoBar);
    connect(button6, &PushButton::clicked, this, &StatusInfoInterface::createBottomRightInfoBar);
    connect(button7, &PushButton::clicked, this, &StatusInfoInterface::createBottomInfoBar);
    connect(button8, &PushButton::clicked, this, &StatusInfoInterface::createBottomLeftInfoBar);

    hBoxlayout->addWidget(button3);
    hBoxlayout->addWidget(button4);
    hBoxlayout->addWidget(button5);
    hBoxlayout->addWidget(button6);
    hBoxlayout->addWidget(button7);
    hBoxlayout->addWidget(button8);
    hBoxlayout->setContentsMargins(0, 0, 0, 0);
    hBoxlayout->setSpacing(15);
    this->addExampleCard(
        this->tr("InfoBar with different pop-up locations"),
        w2,
        "http://www.github.com", 0
    );


    IndeterminateProgressBar *bar1 = new IndeterminateProgressBar(this, true);
    bar1->setFixedWidth(200);
    ExampleCard *bar1Card = this->addExampleCard(
        this->tr("An indeterminate progress bar"),
        bar1,
        "http://www.github.com", 0
    );
    bar1Card->topLayout->setContentsMargins(12, 24, 12, 24);


    ProgressBar *bar2 = new ProgressBar(this, true);
    bar2->setFixedWidth(200);
    this->addExampleCard(
        this->tr("An determinate progress bar"),
        new ProgressWidget(bar2, this),
        "http://www.github.com", 0
    );

    IndeterminateProgressRing *ring = new IndeterminateProgressRing(this, true);
    ring->setFixedSize(70, 70);
    this->addExampleCard(
        this->tr("An indeterminate progress ring"),
        ring,
        "http://www.github.com", 0
    );

    ProgressRing *ring2 = new ProgressRing(this, true);
    ring2->setFixedSize(80, 80);
    ring2->setTextVisible(true);
    this->addExampleCard(
        this->tr("An determinate progress ring"),
        new ProgressWidget(ring2, this),
        "http://www.github.com", 0
    );
}


void StatusInfoInterface::createTopRightInfoBar()
{
    InfoBar::info(
        this->tr("Lesson 3"),
        this->tr("Believe in the spin, just keep believing!"),
        Qt::Horizontal,
        true,
        2000,
        InfoBarPosition::TOP_RIGHT,
        this);
}

void StatusInfoInterface::createTopInfoBar()
{
    InfoBar::success(
        this->tr("Lesson 4"),
        this->tr("With respect, let's advance towards a new stage of the spin."),
        Qt::Horizontal,
        true,
        2000,
        InfoBarPosition::TOP,
        this);
}

void StatusInfoInterface::createTopLeftInfoBar()
{
    InfoBar::warning(
        this->tr("Lesson 5"),
        this->tr("The shortest shortcut is to take a detour."),
        Qt::Horizontal,
        false,
        2000,
        InfoBarPosition::TOP_LEFT,
        this);    
}

void StatusInfoInterface::createBottomRightInfoBar()
{
    InfoBar::error(
        this->tr("No Internet"),
        this->tr("An error message which won't disappear automatically."),
        Qt::Horizontal,
        true,
        -1,
        InfoBarPosition::BOTTOM_RIGHT,
        this); 
}

void StatusInfoInterface::createBottomInfoBar()
{
    InfoBar::success(
        this->tr("Lesson 1"),
        this->tr("Don't have any strange expectations of me."),
        Qt::Horizontal,
        true,
        2000,
        InfoBarPosition::BOTTOM,
        this); 
}

void StatusInfoInterface::createBottomLeftInfoBar()
{
    InfoBar::warning(
        this->tr("Lesson 2"),
        this->tr("Don't let your muscles notice."),
        Qt::Horizontal,
        true,
        1500,
        InfoBarPosition::BOTTOM_LEFT,
        this); 
}


void StatusInfoInterface::onStateButtonClicked()
{
    if(this->stateTooltip != nullptr){
        this->stateTooltip->setContent(this->tr("The model training is complete! 😆"));
        ((PushButton*)this->sender())->setText(this->tr("Show StateToolTip"));
        this->stateTooltip->setState(true);
        this->stateTooltip = nullptr;
    }else{
        this->stateTooltip = new StateToolTip(
            this->tr("Training model"),
            this->tr("Please wait patiently"), this->window());
        ((PushButton*)this->sender())->setText(this->tr("Hide StateToolTip"));
        this->stateTooltip->move(this->stateTooltip->getSuitablePos());
        this->stateTooltip->show();
    }
}   


ProgressWidget::ProgressWidget(QWidget *widget, QWidget *parent) : QWidget(parent)
{
    QHBoxLayout *hBoxLayout = new QHBoxLayout(this);
    this->spinBox = new SpinBox(this);
    connect(this->spinBox, QOverload<int>::of(&SpinBox::valueChanged), (ProgressBar*)widget, &ProgressBar::setValue);
    this->spinBox->setRange(0, 100);

    hBoxLayout->addWidget(widget);
    hBoxLayout->addSpacing(50);
    hBoxLayout->addWidget(new QLabel(this->tr("Progress")));
    hBoxLayout->addSpacing(5);
    hBoxLayout->addWidget(this->spinBox);
    hBoxLayout->setContentsMargins(0, 0, 0, 0);
    this->spinBox->setValue(0);
}