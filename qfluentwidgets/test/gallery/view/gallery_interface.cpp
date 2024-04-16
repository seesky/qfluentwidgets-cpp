#include "gallery_interface.h"

GallerySeparatorWidget::GallerySeparatorWidget(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(6, 16);
}

void GallerySeparatorWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen = QPen(1);
    pen.setCosmetic(true);
    QColor c = isDarkTheme() ? QColor(255, 255, 255, 21) : QColor(0, 0, 0, 15);
    pen.setColor(c);
    painter.setPen(pen);

    int x = this->width() / 2;
    painter.drawLine(x, 0, x, this->height());
}


ToolBar::ToolBar(QString title, QString subtitle, QWidget *parent) : QWidget(parent)
{
    this->titleLabel = new TitleLabel(title, this);
    this->subtitleLabel = new CaptionLabel(subtitle, this);

    FluentIcon *documentButtonIcon = new FluentIcon();
    documentButtonIcon->setIconName(QString("DOCUMENT"));
    this->documentButton = new PushButton(this->tr("Documenttation"), this, new QVariant(QVariant::fromValue<FluentIcon>(*documentButtonIcon)));

    FluentIcon *sourceButtonIcon = new FluentIcon();
    sourceButtonIcon->setIconName(QString("DOCUMENT"));
    this->sourceButton = new PushButton(this->tr("Source"), this, new QVariant(QVariant::fromValue<FluentIcon>(*sourceButtonIcon)));

    // FluentIcon *themeButtonIcon = new FluentIcon();
    // themeButtonIcon->setIconName(QString("CONSTRACT"));
    // this->themeButton = new ToolButton(themeButtonIcon, this);

    this->separator = new GallerySeparatorWidget(this);

    FluentIcon *supportButtonIcon = new FluentIcon();
    supportButtonIcon->setIconName(QString("HEART"));
    this->supportButton = new ToolButton(supportButtonIcon, this);

    FluentIcon *feedbackButtonIcon = new FluentIcon();
    feedbackButtonIcon->setIconName(QString("FEEDBACK"));
    this->feedbackButton = new ToolButton(feedbackButtonIcon, this);

    this->vBoxLayout = new QVBoxLayout(this);
    this->buttonLayout = new QHBoxLayout();

    this->__initWidget();
}


void ToolBar::__initWidget()
{
    this->setFixedHeight(138);
    this->vBoxLayout->setSpacing(0);
    this->vBoxLayout->setContentsMargins(36, 22, 36, 12);
    this->vBoxLayout->addWidget(this->titleLabel);
    this->vBoxLayout->addSpacing(4);
    this->vBoxLayout->addWidget(this->subtitleLabel);
    this->vBoxLayout->addSpacing(4);
    this->vBoxLayout->addLayout(this->buttonLayout, 1);
    this->vBoxLayout->setAlignment(Qt::AlignTop);

    this->buttonLayout->setSpacing(4);
    this->buttonLayout->setContentsMargins(0, 0, 0, 0);
    this->buttonLayout->addWidget(this->documentButton, 0, Qt::AlignLeft);
    this->buttonLayout->addWidget(this->sourceButton, 0, Qt::AlignLeft);
    this->buttonLayout->addStretch(1);
    //this->buttonLayout->addWidget(this->themeButton, 0, Qt::AlignRight);
    
    this->buttonLayout->addWidget(this->supportButton, 0, Qt::AlignRight);
    this->buttonLayout->addWidget(this->separator, 0, Qt::AlignRight);
    this->buttonLayout->addWidget(this->feedbackButton, 0, Qt::AlignRight);
    this->buttonLayout->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);

    //this->themeButton->installEventFilter(new ToolTipFilter(this->themeButton, 300, ToolTipPosition::TOP));
    this->supportButton->installEventFilter(new ToolTipFilter(this->supportButton, 300, ToolTipPosition::TOP));
    this->feedbackButton->installEventFilter(new ToolTipFilter(this->feedbackButton, 300, ToolTipPosition::TOP));
    //this->themeButton->setToolTip(this->tr("Toggle theme"));
    this->supportButton->setToolTip(this->tr("Support me"));
    this->feedbackButton->setToolTip(this->tr("Send feedback"));

    // connect(this->themeButton, &ToolButton::clicked, this, [](){
    //     toggleTheme(true);
    // });
    connect(this->supportButton, &ToolButton::clicked, signalBus, &SignalBus::supportSignal);
    connect(this->documentButton, &PushButton::clicked, this, [](){
        QDesktopServices::openUrl(QUrl("http://www.github.com"));
    });
    connect(this->sourceButton, &PushButton::clicked, this, [](){
        QDesktopServices::openUrl(QUrl("http://www.github.com"));
    });
    connect(this->feedbackButton, &ToolButton::clicked, this, [](){
        QDesktopServices::openUrl(QUrl("http://www.github.com"));
    });

    this->subtitleLabel->setTextColor(QColor(96, 96, 96), QColor(216, 216, 216));
}


ExampleCard::ExampleCard(QString title, QWidget *widget, QString sourcePath, int stretch, QWidget *parent) : QWidget(parent)
{
    this->widget = widget;
    this->stretch = stretch;

    this->titleLabel = new StrongBodyLabel(title, this);
    this->card = new QFrame(this);

    this->sourceWidget = new QFrame(this->card);
    this->sourcePath = sourcePath;
    this->sourcePathLabel = new BodyLabel(this->tr("Source code"), this->sourceWidget);

    FluentIcon *linkIconIcon = new FluentIcon();
    linkIconIcon->setIconName(QString("LINK"));
    this->linkIcon = new IconWidget(*linkIconIcon, this->sourceWidget);

    this->vBoxLayout = new QVBoxLayout(this);
    this->cardLayout = new QVBoxLayout(this->card);
    this->topLayout = new QHBoxLayout();
    this->bottomLayout = new QHBoxLayout(this->sourceWidget);

    this->__initWidget();
}


void ExampleCard::__initWidget()
{
    this->linkIcon->setFixedSize(16, 16);
    this->__initLayout();

    this->sourceWidget->setCursor(Qt::PointingHandCursor);
    this->sourceWidget->installEventFilter(this);

    this->card->setObjectName("card");
    this->sourceWidget->setObjectName("sourceWidget");
}


void ExampleCard::__initLayout()
{
    this->vBoxLayout->setSizeConstraint(QVBoxLayout::SetMinimumSize);
    this->cardLayout->setSizeConstraint(QVBoxLayout::SetMinimumSize);
    this->topLayout->setSizeConstraint(QHBoxLayout::SetMinimumSize);

    this->vBoxLayout->setSpacing(12);
    this->vBoxLayout->setContentsMargins(0, 0, 0, 0);
    this->topLayout->setContentsMargins(12, 12, 12, 12);
    this->bottomLayout->setContentsMargins(18, 18, 18, 18);
    this->cardLayout->setContentsMargins(0, 0, 0, 0);

    this->vBoxLayout->addWidget(this->titleLabel, 0, Qt::AlignTop);
    this->vBoxLayout->addWidget(this->card, 0, Qt::AlignTop);
    this->vBoxLayout->setAlignment(Qt::AlignTop);

    this->cardLayout->setSpacing(0);
    this->cardLayout->setAlignment(Qt::AlignTop);
    this->cardLayout->addLayout(this->topLayout, 0);
    this->cardLayout->addWidget(this->sourceWidget, 0, Qt::AlignBottom);

    this->widget->setParent(this->card);
    this->topLayout->addWidget(this->widget);
    if(this->stretch == 0){
        this->topLayout->addStretch(1);
    }

    this->widget->show();

    this->bottomLayout->addWidget(this->sourcePathLabel, 0, Qt::AlignLeft);
    this->bottomLayout->addStretch(1);
    this->bottomLayout->addWidget(this->linkIcon, 0, Qt::AlignRight);
    this->bottomLayout->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
}


bool ExampleCard::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this->sourceWidget){
        if(event->type() == QEvent::MouseButtonRelease){
            QDesktopServices::openUrl(QUrl(this->sourcePath));
        }
    }

    return QWidget::eventFilter(watched, event);
}


GalleryInterface::GalleryInterface(QString title, QString subtitle, QWidget *parent) : ScrollArea(parent)
{
    this->view = new QWidget(this);
    this->toolBar = new ToolBar(title, subtitle, this);
    this->vBoxLayout = new QVBoxLayout(this->view);

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setViewportMargins(0, this->toolBar->height(), 0, 0);
    this->setWidget(this->view);
    this->setWidgetResizable(true);

    this->vBoxLayout->setSpacing(30);
    this->vBoxLayout->setAlignment(Qt::AlignTop);
    this->vBoxLayout->setContentsMargins(36, 20, 36, 36);

    this->view->setObjectName("view");
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("GALLERY_INTERFACE"), Theme::AUTO);
}


ExampleCard *GalleryInterface::addExampleCard(QString title, QWidget *widget, QString sourcePath, int stretch = 0)
{
    ExampleCard *card = new ExampleCard(title, widget, sourcePath, stretch, this->view);
    this->vBoxLayout->addWidget(card, 0, Qt::AlignTop);
    return card;
}


void GalleryInterface::scrollToCard(int index)
{
    QWidget *w = this->vBoxLayout->itemAt(index)->widget();
    this->verticalScrollBar()->setValue(w->y());
}

void GalleryInterface::resizeEvent(QResizeEvent *e)
{
    ScrollArea::resizeEvent(e);
    this->toolBar->resize(this->width(), this->toolBar->height());
}