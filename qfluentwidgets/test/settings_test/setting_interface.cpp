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


    
    this->__initWidget();
    
}

void SettingInterface::__initWidget()
{
    this->resize(1000, 800);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setViewportMargins(0, 120, 0, 20);
    this->setWidget(this->scrollWidget);
    this->setWidgetResizable(true);

    this->__setQss();

    this->__initLayout();
}

void SettingInterface::__initLayout()
{
    this->settingLabel->move(60, 63);

    this->onlineMusicGroup->addSettingCard(this->onlinePageSizeCard);
    this->onlineMusicGroup->addSettingCard(this->onlineMusicQualityCard);
    this->onlineMusicGroup->addSettingCard(this->onlineMvQualityCard);

    this->personalGroup->addSettingCard(this->enableAcrylicCard);
    this->personalGroup->addSettingCard(this->themeCard);

    this->expandLayout->setSpacing(28);
    this->expandLayout->setContentsMargins(60, 10, 60, 0);
    this->expandLayout->addWidget(this->personalGroup);
    this->expandLayout->addWidget(this->onlineMusicGroup);
}


void SettingInterface::__setQss()
{
    this->scrollWidget->setObjectName("scrollWidget");
    this->settingLabel->setObjectName("settingLabel");

    QString color = isDarkTheme() ? QString("dark") : QString("light");

    QFile file(QString("resource/setting_resource/qss/%1/demo.qss").arg(color));
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        QString styleSheet = stream.readAll();
        this->setStyleSheet(styleSheet);
        file.close();
    } else {
        qWarning("Cannot open file: %s", qPrintable(file.errorString()));
    }
}