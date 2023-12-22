#pragma once

#include "config.h"
#include <map>
#include <QtCore>
#include <QtCore/QRect>
#include <QtGui/QIcon>
#include <QtGui/QIconEngine>
#include <QtGui/QPainter>
#include <QtSvg/QSvgRenderer>
#include <QVariant>
#include <QMetaType>
#include <QList>

const static QMap<QString, QString> CustomStyleSheetMap = {
    {"DARK_QSS_KEY", "darkCustomQss"},
    {"LIGHT_QSS_KEY", "lightCustomQss"}
};

const static QMap<QString, QString> ThemeColorMap = {
    {"PRIMARY" , "ThemeColorPrimary"},
    {"DARK_1" , "ThemeColorDark1"},
    {"DARK_2" , "ThemeColorDark2"},
    {"DARK_3" , "ThemeColorDark3"},
    {"LIGHT_1" , "ThemeColorLight1"},
    {"LIGHT_2" , "ThemeColorLight2"},
    {"LIGHT_3" , "ThemeColorLight3"}
};

const static std::map<QString, QString> FluentStyleSheetMap = {
    {"MENU" , "menu"},
    {"LABEL" , "label"},
    {"PIVOT" , "pivot"},
    {"BUTTON" , "button"},
    {"DIALOG" , "dialog"},
    {"SLIDER" , "slider"},
    {"INFO_BAR" , "info_bar"},
    {"SPIN_BOX" , "spin_box"},
    {"TAB_VIEW" , "tab_view"},
    {"TOOL_TIP" , "tool_tip"},
    {"CHECK_BOX" , "check_box"},
    {"COMBO_BOX" , "combo_box"},
    {"FLIP_VIEW" , "flip_view"},
    {"LINE_EDIT" , "line_edit"},
    {"LIST_VIEW" , "list_view"},
    {"TREE_VIEW" , "tree_view"},
    {"INFO_BADGE" , "info_badge"},
    {"PIPS_PAGER" , "pips_pager"},
    {"TABLE_VIEW" , "table_view"},
    {"CARD_WIDGET" , "card_widget"},
    {"TIME_PICKER" , "time_picker"},
    {"COLOR_DIALOG" , "color_dialog"},
    {"MEDIA_PLAYER" , "media_player"},
    {"SETTING_CARD" , "setting_card"},
    {"TEACHING_TIP" , "teaching_tip"},
    {"FLUENT_WINDOW" , "fluent_window"},
    {"SWITCH_BUTTON" , "switch_button"},
    {"MESSAGE_DIALOG" , "message_dialog"},
    {"STATE_TOOL_TIP" , "state_tool_tip"},
    {"CALENDAR_PICKER" , "calendar_picker"},
    {"FOLDER_LIST_DIALOG" , "folder_list_dialog"},
    {"SETTING_CARD_GROUP" , "setting_card_group"},
    {"EXPAND_SETTING_CARD" , "expand_setting_card"},
    {"NAVIGATION_INTERFACE" , "navigation_interface"}
};
class StyleSheetBase;
class StyleSheetManager : public QObject{
    Q_OBJECT
public:
    StyleSheetManager();
    void register_(QVariant source, QWidget *widget, bool reset);
    void deregister(QWidget *widget);
    QMutableMapIterator<QWidget*, StyleSheetBase*> items();
    StyleSheetBase *source(QWidget *widget);
private:
    QMap<QWidget*, StyleSheetBase*> *widgets;
};

class QssTemplate{
public:
    QssTemplate(QString qss);
    QString safe_substitute(QMap<QString, QString> mapping);
private:
    QString delimiter = "--";
    QString value;
};

class StyleSheetBase{
public:
    StyleSheetBase();
    QString path(Theme theme);
    QString content(Theme theme);
    void apply(QWidget *widget, Theme theme);
    bool operator==(const StyleSheetBase& other) const {
        return *this == other;
    }
private:
    StyleSheetBase *self;   
};

Q_DECLARE_METATYPE(StyleSheetBase)

class FluentStyleSheet : public StyleSheetBase{
public:
    QString path(QString ThemeOptionsName, QString FluentStyleSheetName, Theme theme);
};

class StyleSheetFile : public StyleSheetBase{
public:
    StyleSheetFile();
    StyleSheetFile(QString path);
    QString path(Theme theme);
private:
    QString filePath;
};

Q_DECLARE_METATYPE(StyleSheetFile)

class CustomStyleSheetWatcher : public QObject{
    Q_OBJECT
public:
    bool eventFilter(QWidget *obj, QEvent *event);
private:
};


class StyleSheetCompose : public StyleSheetBase{
public:
    StyleSheetCompose();
    StyleSheetCompose(QList<StyleSheetBase> *sources);
    QString content(Theme theme);
    void add(StyleSheetBase *source);
    void remove(StyleSheetBase *source);
private:
    QList<StyleSheetBase> *sources;
};

Q_DECLARE_METATYPE(StyleSheetCompose)


class CustomStyleSheet : public StyleSheetBase{
public:
    CustomStyleSheet(){};
    CustomStyleSheet(QWidget *widget);
    QString path(Theme theme);
    CustomStyleSheet *setCustomStyleSheet(QString lightQss, QString darkQss);
    CustomStyleSheet *setLightStyleSheet(QString qss);
    CustomStyleSheet *setDarkStyleSheet(QString qss);
    QString lightStyleSheet();
    QString darkStyleSheet();
    QString content(Theme theme);
    bool operator==(const CustomStyleSheet& other) const {
        return this->widget == other.widget;
    }
private:
    QWidget *widget;
};

Q_DECLARE_METATYPE(CustomStyleSheet)
