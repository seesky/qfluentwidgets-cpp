#pragma once

#include "../../../common/style_sheet.h"
#include "../../../common/config.h"

const static QMap<QString, QString> StyleSheetMap = {
    {"LINK_CARD", "link_card"},
    {"SAMPLE_CARD", "sample_card"},
    {"HOME_INTERFACE", "home_interface"},
    {"ICON_INTERFACE", "icon_interface"},
    {"VIEW_INTERFACE", "view_interface"},
    {"SETTING_INTERFACE", "setting_interface"},
    {"GALLERY_INTERFACE", "gallery_interface"},
    {"NAVIGATION_VIEW_INTERFACE", "navigation_view_interface"},
};


class StyleSheet : public StyleSheetBase{
public:
    StyleSheet();
    QString path(QString ThemeOptionsName, QString FluentStyleSheetName, Theme theme);
};