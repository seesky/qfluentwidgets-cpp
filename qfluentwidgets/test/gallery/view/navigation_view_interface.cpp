#include "navigation_view_interface.h"


NavigationViewInterface::NavigationViewInterface(QWidget *parent) : GalleryInterface(Translator(nullptr).navigation, "fluentwidgets.components.navigation", parent)
{
    this->setObjectName("navigationViewInterface");

    BreadcrumbBar *breadcrumb = new BreadcrumbBar(this);
    QStringList items = {
        this->tr("Home"), this->tr("Documents"), this->tr("Study"),
        this->tr("Janpanese Sensei"), this->tr("Action Film"), this->tr("G Cup"),
        this->tr("Mikami Yua"), this->tr("Folder1"), this->tr("Folder2"),
    };
    for(int i = 0; i < items.length(); i++){
        breadcrumb->addItem(items.at(i), items.at(i));
    }

    this->addExampleCard(
        this->tr("Breadcrumb bar"),
        breadcrumb,
        "http://www.github.com", 1
    );

    this->addExampleCard(
        this->tr("A basic pivot"),
        new PivotInterface(this),
        "http://www.github.com", 0
    );

    this->addExampleCard(
        this->tr("A segmented control"),
        new SegmentedInterface(this),
        "http://www.github.com", 0
    );

    this->addExampleCard(
        this->tr("Another segmented control"),
        this->createToggleToolWidget(),
        "http://www.github.com", 0
    );

    ExampleCard *card = this->addExampleCard(
        this->tr("A tab bar"),
        new TabInterface(this),
        "http://www.github.com", 1
    );
    card->topLayout->setContentsMargins(12, 0, 0, 0);
}


QWidget* NavigationViewInterface::createToggleToolWidget()
{
    SegmentedToggleToolWidget *w = new SegmentedToggleToolWidget(this);

    FluentIcon *transparentIcon = new FluentIcon();
    transparentIcon->setIconName(QString("TRANSPARENT"));
    w->addItem("k1", new QVariant(QVariant::fromValue<FluentIcon>(*transparentIcon)), nullptr);

    FluentIcon *checkboxIcon = new FluentIcon();
    checkboxIcon->setIconName(QString("CHECKBOX"));
    w->addItem("k2", new QVariant(QVariant::fromValue<FluentIcon>(*checkboxIcon)), nullptr);

    FluentIcon *constractIcon = new FluentIcon();
    constractIcon->setIconName(QString("CONSTRACT"));
    w->addItem("k3", new QVariant(QVariant::fromValue<FluentIcon>(*constractIcon)), nullptr);

    w->setCurrentItem("k1");

    return w;
}


PivotInterface::PivotInterface(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(300, 140);

    this->pivot = new Pivot(this);
    this->stackedWidget = new QStackedWidget(this);
    this->vBoxLayout = new QVBoxLayout(this);

    this->songInterface = new QLabel("Song Interface", this);
    this->albumInterface = new QLabel("Album Interface", this);
    this->artistInterface = new QLabel("Artist Interface", this);

    this->addSubInterface(this->songInterface, "songInterface", this->tr("Song"));
    this->addSubInterface(this->albumInterface, "albumInterface", this->tr("Album"));
    this->addSubInterface(this->artistInterface, "artistInterface", this->tr("Artist"));

    this->vBoxLayout->addWidget(this->pivot, 0, Qt::AlignLeft);
    this->vBoxLayout->addWidget(this->stackedWidget);
    this->vBoxLayout->setContentsMargins(0, 0, 0, 0);
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("NAVIGATION_VIEW_INTERFACE"), Theme::AUTO);

    connect(this->stackedWidget, &QStackedWidget::currentChanged, this, &PivotInterface::onCurrentIndexChanged);
    this->stackedWidget->setCurrentWidget(this->songInterface);
    this->pivot->setCurrentItem(this->songInterface->objectName());

    //qrouter->setDefaultRouteKey(this->stackedWidget, this->songInterface->objectName());
}


void PivotInterface::addSubInterface(QLabel *widget, QString objectName, QString text)
{
    widget->setObjectName(objectName);
    widget->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    this->stackedWidget->addWidget(widget);
    this->pivot->addItem(
        objectName,
        text,
        [this, widget](){
            this->stackedWidget->setCurrentWidget(widget);
        },
        new QVariant()
    );
}


void PivotInterface::onCurrentIndexChanged(int index)
{
    QWidget *widget = this->stackedWidget->widget(index);
    this->pivot->setCurrentItem(widget->objectName());
    //qrouter->push(this->stackedWidget, widget->objectName());
}



// SegmentedInterface::SegmentedInterface(QWidget *parent) : QWidget(parent)
// {
//     this->pivot = new SegmentedWidget(this);
//     this->vBoxLayout->removeWidget(this->pivot);
//     this->vBoxLayout->insertWidget(0, this->pivot);
// }


SegmentedInterface::SegmentedInterface(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(300, 140);

    this->pivot = new SegmentedWidget(this);
    this->stackedWidget = new QStackedWidget(this);
    this->vBoxLayout = new QVBoxLayout(this);

    this->songInterface = new QLabel("Song Interface", this);
    this->albumInterface = new QLabel("Album Interface", this);
    this->artistInterface = new QLabel("Artist Interface", this);

    this->addSubInterface(this->songInterface, "songInterface", this->tr("Song"));
    this->addSubInterface(this->albumInterface, "albumInterface", this->tr("Album"));
    this->addSubInterface(this->artistInterface, "artistInterface", this->tr("Artist"));

    this->vBoxLayout->addWidget(this->pivot, 0, Qt::AlignLeft);
    this->vBoxLayout->addWidget(this->stackedWidget);
    this->vBoxLayout->setContentsMargins(0, 0, 0, 0);
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("NAVIGATION_VIEW_INTERFACE"), Theme::AUTO);

    connect(this->stackedWidget, &QStackedWidget::currentChanged, this, &SegmentedInterface::onCurrentIndexChanged);
    this->stackedWidget->setCurrentWidget(this->songInterface);
    this->pivot->setCurrentItem(this->songInterface->objectName());

    //qrouter->setDefaultRouteKey(this->stackedWidget, this->songInterface->objectName());
}


void SegmentedInterface::addSubInterface(QLabel *widget, QString objectName, QString text)
{
    widget->setObjectName(objectName);
    widget->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    this->stackedWidget->addWidget(widget);
    this->pivot->addItem(
        objectName,
        text,
        [this, widget](){
            this->stackedWidget->setCurrentWidget(widget);
        },
        new QVariant()
    );
}


void SegmentedInterface::onCurrentIndexChanged(int index)
{
    QWidget *widget = this->stackedWidget->widget(index);
    this->pivot->setCurrentItem(widget->objectName());
    //qrouter->push(this->stackedWidget, widget->objectName());
}




TabInterface::TabInterface(QWidget *parent) : QWidget(parent)
{
    this->tabCount = 1;

    this->tabBar = new TabBar(this);
    this->stackedWidget = new QStackedWidget(this);
    this->tabView = new QWidget(this);
    this->controlPanel = new QFrame(this);

    this->movableCheckBox = new CheckBox(this->tr("IsTabMovable"), this);
    this->movableCheckBox->setTristate(false);
    
    this->scrollableCheckBox = new CheckBox(this->tr("IsTabScrollable"), this);
    this->scrollableCheckBox->setTristate(false);
    this->shadowEnabledCheckBox = new CheckBox(this->tr("IsTabShadowEnabled"), this);
    this->shadowEnabledCheckBox->setTristate(false);
    this->tabMaxWidthLabel = new BodyLabel(this->tr("TabMaximumWidth"), this);
    this->tabMaxWidthSpinBox = new SpinBox(this);
    this->closeDisplayModeLabel = new BodyLabel(this->tr("TabCloseButtonDisplayMode"), this);
    this->closeDisplayModeComboBox = new ComboBox(this);

    this->hBoxLayout = new QHBoxLayout(this);
    this->vBoxLayout = new QVBoxLayout(this->tabView);
    this->panelLayout = new QVBoxLayout(this->controlPanel);

    this->songInterface = new QLabel("Song Interface", this);
    this->albumInterface = new QLabel("Album Interface", this);
    this->artistInterface = new QLabel("Artist Interface", this);

    this->__initWidget();
}

void TabInterface::__initWidget()
{
    this->initLayout();

    this->shadowEnabledCheckBox->setChecked(true);
    this->tabMaxWidthSpinBox->setValue(this->tabBar->tabMaximumWidth());

    this->closeDisplayModeComboBox->addItem(this->tr("Always"), nullptr, new QVariant(QVariant::fromValue<TabCloseButtonDisplayMode>(TabCloseButtonDisplayMode::ALWAYS)));
    this->closeDisplayModeComboBox->addItem(this->tr("OnHover"), nullptr, new QVariant(QVariant::fromValue<TabCloseButtonDisplayMode>(TabCloseButtonDisplayMode::ON_HOVER)));
    this->closeDisplayModeComboBox->addItem(this->tr("Never"), nullptr, new QVariant(QVariant::fromValue<TabCloseButtonDisplayMode>(TabCloseButtonDisplayMode::NEVER)));
    connect(this->closeDisplayModeComboBox, &ComboBox::currentIndexChanged, this, &TabInterface::onDisplayModeChanged);

    this->addSubInterface(this->songInterface, "tabSongInterface", this->tr("Song"), new QVariant("qfluentwidgets/images/MusicNote.png"));
    this->addSubInterface(this->albumInterface, "tabAlbumInterface", this->tr("Album"), new QVariant("qfluentwidgets/images/Dvd.png"));
    this->addSubInterface(this->artistInterface, "tabArtistInterface", this->tr("Artist"), new QVariant("qfluentwidgets/images/Singer.png"));

    this->controlPanel->setObjectName("controlPanel");
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("NAVIGATION_VIEW_INTERFACE"), Theme::AUTO);

    this->connectSignalToSlot();

    //qrouter->setDefaultRouteKey(this->stackedWidget, this->songInterface->objectName());
}


void TabInterface::connectSignalToSlot()
{
    connect(this->movableCheckBox, &CheckBox::stateChanged, this, [this](){
        this->tabBar->setMovable(this->movableCheckBox->isChecked());
    });

    connect(this->scrollableCheckBox, &CheckBox::stateChanged, this, [this](){
        this->tabBar->setScrollable(this->scrollableCheckBox->isChecked());
    });

    connect(this->shadowEnabledCheckBox, &CheckBox::stateChanged, this, [this](){
        this->tabBar->setTabShadowEnabled(this->shadowEnabledCheckBox->isChecked());
    });

    connect(this->tabMaxWidthSpinBox, QOverload<int>::of(&SpinBox::valueChanged), this->tabBar, &TabBar::setTabMaximumWidth);

    connect(this->tabBar, &TabBar::tabAddRequested, this, &TabInterface::addTab);
    connect(this->tabBar, &TabBar::tabCloseRequested, this, &TabInterface::removeTab);

    connect(this->stackedWidget, &QStackedWidget::currentChanged, this, &TabInterface::onCurrentIndexChanged);
}


void TabInterface::initLayout()
{
    this->tabBar->setTabMaximumWidth(200);

    this->setFixedHeight(280);
    this->controlPanel->setFixedWidth(220);
    this->hBoxLayout->addWidget(this->tabView, 1);
    this->hBoxLayout->addWidget(this->controlPanel, 0, Qt::AlignRight);
    this->hBoxLayout->setContentsMargins(0, 0, 0, 0);

    this->vBoxLayout->addWidget(this->tabBar);
    this->vBoxLayout->addWidget(this->stackedWidget);
    this->vBoxLayout->setContentsMargins(0, 0, 0, 0);

    this->panelLayout->setSpacing(8);
    this->panelLayout->setContentsMargins(14, 16, 14, 14);
    this->panelLayout->setAlignment(Qt::AlignTop);

    this->panelLayout->addWidget(this->movableCheckBox);
    this->panelLayout->addWidget(this->scrollableCheckBox);
    this->panelLayout->addWidget(this->shadowEnabledCheckBox);

    this->panelLayout->addSpacing(4);
    this->panelLayout->addWidget(this->tabMaxWidthLabel);
    this->panelLayout->addWidget(this->tabMaxWidthSpinBox);

    this->panelLayout->addSpacing(4);
    this->panelLayout->addWidget(this->closeDisplayModeLabel);
    this->panelLayout->addWidget(this->closeDisplayModeComboBox);
}


void TabInterface::addSubInterface(QLabel *widget, QString objectName, QString text, QVariant *icon)
{
    widget->setObjectName(objectName);
    widget->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    this->stackedWidget->addWidget(widget);
    this->tabBar->addTab(
        objectName,
        text,
        icon,
        [this, widget](){
            this->stackedWidget->setCurrentWidget(widget);
        }
    );
}   


void TabInterface::onDisplayModeChanged(int index)
{
    TabCloseButtonDisplayMode mode = this->closeDisplayModeComboBox->itemData(index)->value<TabCloseButtonDisplayMode>();
    this->tabBar->setCloseButtonDisplayMode(mode);
}

void TabInterface::onCurrentIndexChanged(int index)
{
    QWidget *widget = this->stackedWidget->widget(index);
    if(widget == nullptr){
        return;
    }

    this->tabBar->setCurrentTab(widget->objectName());
    //qrouter->push(this->stackedWidget, widget->objectName());
}

void TabInterface::addTab()
{
    QString text = QString("硝子酱一级棒卡哇伊×%1").arg(QString::number(this->tabCount));
    this->addSubInterface(new QLabel(QString("🥰 ").arg(text)), text, text, new QVariant("qfluentwidgets/images/Smiling_with_heart.png"));
    this->tabCount += 1;
}

void TabInterface::removeTab(int index)
{
    TabItem *item = this->tabBar->tabItem(index);
    QWidget *widget = this->findChild<QLabel*>(item->routeKey());

    this->stackedWidget->removeWidget(widget);
    this->tabBar->removeTab(index);
    widget->deleteLater();
}