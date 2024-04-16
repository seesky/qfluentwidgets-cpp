
#include "setting_interface.h"

SettingInterface::SettingInterface(QWidget *parent) : ScrollArea(parent)
{
    this->scrollWidget = new QWidget();
    this->expandLayout = new ExpandLayout(this->scrollWidget);
    this->settingLabel = new QLabel(this->tr("Settings"), this);

    QList<QString> songQuality = {"Standard quality", "Super quality", "Lossless quality"};
    this->onlineSongQuality = new OptionsConfigItem("Online", "SongQuality", SongQuality.value("STANDARD"), songQuality, false);

    this->onlinePageSize = new RangeConfigItem("Online", "PageSize", 30, 0, 50, false);
    
    QList<QString> mvQuality = {"Full HD", "HD", "SD", "LD"};
    this->onlineMvQuality = new OptionsConfigItem("Online", "MvQuality", "DH", mvQuality, false);

    QList<QString> enableList = {"true", "false"};
    this->enableAcrylicBackground = new OptionsConfigItem("MainWindow", "EnableAcrylicBackground", "false", enableList, false);

    QList<QString> languageList = {"chinese simplified", "chinese traditional", "english", "auto"};

    this->onlineMusicGroup = new SettingCardGroup(this->tr("Online Music"), this->scrollWidget);
    FluentIcon *rangeSettingCardIcon = new FluentIcon();
    rangeSettingCardIcon->setIconName(QString("SEARCH"));
    this->onlinePageSizeCard = new RangeSettingCard(
        QVariant::fromValue<RangeConfigItem*>(this->onlinePageSize), 
        new QVariant(QVariant::fromValue<FluentIcon>(*rangeSettingCardIcon)), 
        this->tr("Number of online music displayed on each page"), 
        QString(), 
        this->onlineMusicGroup);
    
    
    FluentIcon *onlineMusicQualitySettingCardIcon = new FluentIcon();
    onlineMusicQualitySettingCardIcon->setIconName(QString("MUSIC"));
    QList<QString> onlineMusicQualityList = {"Standard quality", "Super quality", "Lossless quality"};
    this->onlineMusicQualityCard = new OptionsSettingCard(
        QVariant::fromValue<OptionsConfigItem*>(this->onlineSongQuality), 
        new QVariant(QVariant::fromValue<FluentIcon>(*onlineMusicQualitySettingCardIcon)), 
        this->tr("Online music quality"), 
        QString(), 
        onlineMusicQualityList, 
        this->onlineMusicGroup);

    FluentIcon *onlineMvQualitySettingCardIcon = new FluentIcon();
    onlineMvQualitySettingCardIcon->setIconName(QString("VIDEO"));
    QList<QString> onlineMvQualityList = {"Full HD", "HD", "SD", "LD"};
    this->onlineMvQualityCard = new OptionsSettingCard(
        QVariant::fromValue<OptionsConfigItem*>(this->onlineMvQuality), 
        new QVariant(QVariant::fromValue<FluentIcon>(*onlineMvQualitySettingCardIcon)), 
        this->tr("Online MV quality"), 
        QString(), 
        onlineMvQualityList, 
        this->onlineMusicGroup);


    this->personalGroup = new SettingCardGroup(this->tr("Personalization"), this->scrollWidget);
    FluentIcon *enableAcrylicSettingCardIcon = new FluentIcon();
    enableAcrylicSettingCardIcon->setIconName(QString("TRANSPARENT"));
    this->enableAcrylicCard = new SwitchSettingCard(
        new QVariant(QVariant::fromValue<FluentIcon>(*enableAcrylicSettingCardIcon)), 
        this->tr("Use Acrylic effect"), 
        this->tr("Acrylic effect has better visual experience, but it may cause the window to become stuck"), 
        QVariant::fromValue<OptionsConfigItem*>(this->enableAcrylicBackground), 
        this->personalGroup);

    /*
    FluentIcon *themeCardSettingCardIcon = new FluentIcon();
    themeCardSettingCardIcon->setIconName(QString("BRUSH"));
    QList<QString> hemeCardList = {"light", "dark", "auto"};
    this->themeCard = new OptionsSettingCard(
        QVariant(QVariant::fromValue<OptionsConfigItem*>(qconfig->themeMode)),
        new QVariant(QVariant::fromValue<FluentIcon>(*themeCardSettingCardIcon)),
        this->tr("Application theme"),
        this->tr("Change the appearance of your application"),
        hemeCardList,
        this->personalGroup
    );
    */

    FluentIcon *languageCardSettingCardIcon = new FluentIcon();
    languageCardSettingCardIcon->setIconName(QString("LANGUAGE"));
    this->languageCard = new ComboBoxSettingCard(
        QVariant(QVariant::fromValue<OptionsConfigItem*>(qconfig->language)),
        new QVariant(QVariant::fromValue<FluentIcon>(*languageCardSettingCardIcon)),
        this->tr("Language"),
        this->tr("Set your preferred language for UI"),
        languageList,
        this->personalGroup
    );

    this->aboutGroup = new SettingCardGroup(this->tr("About"), this->scrollWidget);
    FluentIcon *helpCardSettingCardIcon = new FluentIcon();
    helpCardSettingCardIcon->setIconName(QString("HELP"));
    this->helpCard = new HyperlinkCard("http://www.github.com", 
        this->tr("Open help page"),
        new QVariant(QVariant::fromValue<FluentIcon>(*helpCardSettingCardIcon)),
        this->tr("Help"),
        this->tr("Discover new features and learn useful tips about PyQt-Fluent-Widgets"),
        this->aboutGroup
        );

    FluentIcon *feedbackCardSettingCardIcon = new FluentIcon();
    feedbackCardSettingCardIcon->setIconName(QString("FEEDBACK"));
    this->feedbackCard = new PrimaryPushSettingCard(
        this->tr("Provide feedback"),
        new QVariant(QVariant::fromValue<FluentIcon>(*feedbackCardSettingCardIcon)),
        this->tr("Provide feedback"),
        this->tr("Help us improve PyQt-Fluent-Widgets by providing feedback"),
        this->aboutGroup
    );

    FluentIcon *aboutCardSettingCardIcon = new FluentIcon();
    aboutCardSettingCardIcon->setIconName(QString("INFO"));
    this->aboutCard = new PrimaryPushSettingCard(
        this->tr("Check update"),
        new QVariant(QVariant::fromValue<FluentIcon>(*aboutCardSettingCardIcon)),
        this->tr("About"),
        QString("© Copyright") + QString(" 2024, SeeSky."),
        this->aboutGroup
    );

    this->__initWidget();
}

void SettingInterface::__initWidget()
{
    this->resize(1000, 800);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setViewportMargins(0, 80, 0, 20);
    this->setWidget(this->scrollWidget);
    this->setWidgetResizable(true);
    this->setObjectName("settingInterface");

    this->scrollWidget->setObjectName("scrollWidget");
    this->settingLabel->setObjectName("settingLabel");
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("SETTING_INTERFACE"), Theme::AUTO);


    this->__initLayout();
    this->__connectSignalToSlot();
}

void SettingInterface::__initLayout()
{
    this->settingLabel->move(36, 30);
    this->onlineMusicGroup->addSettingCard(this->onlinePageSizeCard);
    this->onlineMusicGroup->addSettingCard(this->onlineMusicQualityCard);
    this->onlineMusicGroup->addSettingCard(this->onlineMvQualityCard);

    this->personalGroup->addSettingCard(this->enableAcrylicCard);
    //this->personalGroup->addSettingCard(this->themeCard);
    this->personalGroup->addSettingCard(this->languageCard);

    this->aboutGroup->addSettingCard(this->helpCard);
    this->aboutGroup->addSettingCard(this->feedbackCard);
    this->aboutGroup->addSettingCard(this->aboutCard);

    this->expandLayout->setSpacing(28);
    this->expandLayout->setContentsMargins(60, 10, 60, 0);
    this->expandLayout->addWidget(this->personalGroup);
    this->expandLayout->addWidget(this->onlineMusicGroup);
    this->expandLayout->addWidget(this->aboutGroup);
}

void SettingInterface::__showRestartTooltip()
{
    InfoBar::warning("", this->tr("Configuration takes effect after restart"), Qt::Horizontal, true, 1000, InfoBarPosition::TOP_RIGHT, this->window());
}

void SettingInterface::__connectSignalToSlot()
{
    connect(qconfig, &QConfig::appRestartSig, this, &SettingInterface::__showRestartTooltip);
}