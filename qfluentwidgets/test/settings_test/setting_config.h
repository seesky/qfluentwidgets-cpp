#pragma once

#include <QtCore/Qt>
#include <QtCore/QLocale>
#include <QtGui/QGuiApplication>
#include <QtGui/QFont>
#include "../../common/config.h"

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

/*
class Config{
public:
    Config();
    OptionsConfigItem *downloadFolder;
    OptionsConfigItem *onlineSongQuality;
    RangeConfigItem *onlinePageSize;
    OptionsConfigItem *onlineMvQuality;
    OptionsConfigItem *enableAcrylicBackground;
    OptionsConfigItem *minimizeToTray;
    ColorConfigItem *palyBarColor;
    OptionsConfigItem *dpiScale;
    OptionsConfigItem *language;
    ColorConfigItem *desLyricHighlightColor;
    RangeConfigItem *deskLyricFontSize;
    RangeConfigItem *deskLyricStrokeSize;
    ColorConfigItem *deskLyricStrokeColor;
    OptionsConfigItem *deskLyricFontFamily;
    OptionsConfigItem *deskLyricAlignment;
    OptionsConfigItem *checkUpdateAtStartUp;

    //QFont getDeskTopLyricFont();
    //void setDesktopLyricFont(QFont font);
};


static Config *cfg = new Config();
*/