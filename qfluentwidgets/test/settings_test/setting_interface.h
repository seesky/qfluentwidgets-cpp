#pragma once

#include <QtWidgets/QLabel>

#include "../../components/widgets/scroll_area.h"
#include "../../components/layout/expand_layout.h"
#include "../../components/settings/setting_card_group.h"
#include "../../components/settings/setting_card.h"
#include "../../components/settings/options_setting_card.h"
#include "setting_config.h"


class SettingInterface : public ScrollArea{
    Q_OBJECT
public:
    SettingInterface(QWidget *parent);
    void __initWidget();
    void __initLayout();
    void __setQss();

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

    OptionsConfigItem *onlineSongQuality;
    RangeConfigItem *onlinePageSize;
    OptionsConfigItem *onlineMvQuality;
    OptionsConfigItem *enableAcrylicBackground;
};