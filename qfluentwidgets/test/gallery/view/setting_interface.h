#pragma once


#include <QtWidgets/QLabel>

#include "../../../components/widgets/scroll_area.h"
#include "../../../components/widgets/info_bar.h"
#include "../../../components/layout/expand_layout.h"
#include "../../../components/settings/setting_card_group.h"
#include "../../../components/settings/setting_card.h"
#include "../../../components/settings/options_setting_card.h"

const static QMap<QString, QString> SongQuality = {
    {"STANDARD", "Standard quality"},
    {"SUPER", "Super quality"},
    {"LOSSLESS", "Lossless quality"}
};

const static QMap<QString, QString> MvQuality = {
    {"FULL_HD", "HD"},
    {"SD", "SD"},
    {"LD", "LD"}
};


const static QMap<QString, QLocale> Language = {
    {"CHINESE_SIMPLIFIED", QLocale(QLocale::Chinese, QLocale::China)},
    {"CHINESE_TRADITIONAL", QLocale(QLocale::Chinese, QLocale::HongKong)},
    {"ENGLISH", QLocale(QLocale::English)},
    {"AUTO", QLocale()}
};

class SettingInterface : public ScrollArea{
    Q_OBJECT
public:
    SettingInterface(QWidget *parent);
    void __initWidget();
    void __initLayout();
    void __connectSignalToSlot();

    QWidget *scrollWidget;
    ExpandLayout *expandLayout;
    QLabel *settingLabel;
    SettingCardGroup *onlineMusicGroup;
    RangeSettingCard *onlinePageSizeCard;
    OptionsSettingCard *onlineMusicQualityCard;
    OptionsSettingCard *onlineMvQualityCard;

    SettingCardGroup *personalGroup;
    SwitchSettingCard *enableAcrylicCard;
    OptionsSettingCard *themeCard;
    ComboBoxSettingCard *languageCard;


    SettingCardGroup *aboutGroup;
    HyperlinkCard *helpCard;
    PrimaryPushSettingCard *feedbackCard;
    PrimaryPushSettingCard *aboutCard;

    OptionsConfigItem *onlineSongQuality;
    RangeConfigItem *onlinePageSize;
    OptionsConfigItem *onlineMvQuality;
    OptionsConfigItem *enableAcrylicBackground;
    OptionsConfigItem *language;

public slots:
    void __showRestartTooltip();
};