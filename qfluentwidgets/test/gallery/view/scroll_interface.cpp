#include "scroll_interface.h"


ScrollInterface::ScrollInterface(QWidget *parent) : GalleryInterface(Translator(nullptr).scroll, "fluentwidgets.components.widgets", parent)
{
    this->setObjectName("scrollInterface");

    ScrollArea *w = new ScrollArea(nullptr);
    ImageLabel *label = new ImageLabel("qfluentwidgets/images/chidanta2.jpg", this);
    label->scaledToWidth(775);
    label->setBorderRadius(8, 8, 8, 8);

    w->horizontalScrollBar()->setValue(0);
    w->setWidget(label);
    w->setFixedSize(775, 430);

    ExampleCard *card = this->addExampleCard(
        this->tr("Smooth scroll area"),
        w,
        "http://www.github.com", 0
    );
    card->card->installEventFilter(new ToolTipFilter(card->card, 500, ToolTipPosition::TOP));
    card->card->setToolTip(this->tr("Chitanda Eru is too hot 🥵"));
    card->card->setToolTipDuration(2000);

    SmoothScrollArea *w2 = new SmoothScrollArea(nullptr);
    ImageLabel *label2 = new ImageLabel("qfluentwidgets/images/chidanta3.jpg", this);
    label->setBorderRadius(8, 8, 8, 8);

    w2->setWidget(label2);
    w2->setFixedSize(660, 540);

    ExampleCard *card2 = this->addExampleCard(
        this->tr("Smooth scroll area implemented by animation"),
        w2,
        "http://www.github.com/", 0
    );
    card2->card->installEventFilter(new ToolTipFilter(card2->card, 500, ToolTipPosition::TOP));
    card2->card->setToolTip(this->tr("Chitanda Eru is so hot 🥵🥵"));
    card2->card->setToolTipDuration(2000);


    SingleDirectionScrollArea *w3 = new SingleDirectionScrollArea(nullptr, Qt::Horizontal);
    ImageLabel *label3 = new ImageLabel("qfluentwidgets/images/chidanta4.jpg", this);
    label3->setBorderRadius(8, 8, 8, 8);

    w3->setWidget(label3);
    w3->setFixedSize(660, 498);

    ExampleCard *card3 = this->addExampleCard(
        this->tr("Single direction scroll scroll area"),
        w3,
        "http://www.github.com", 0
    );

    card3->card->installEventFilter(new ToolTipFilter(card3->card, 500, ToolTipPosition::TOP));
    card3->card->setToolTip(this->tr("Chitanda Eru is so hot 🥵🥵🥵"));
    card3->card->setToolTipDuration(2000);

    HorizontalPipsPager *pager = new HorizontalPipsPager(this);
    pager->setPageNumber(15);
    pager->setPreviousButtonDisplayMode(PipsScrollButtonDisplayMode::ALWAYS);
    pager->setNextButtonDisplayMode(PipsScrollButtonDisplayMode::ALWAYS);
    
    ExampleCard *card4 = this->addExampleCard(
        this->tr("Pips pager"),
        pager,
        "http://www.github.com", 0
    );
    card4->topLayout->setContentsMargins(12, 20, 12, 20);
    
}