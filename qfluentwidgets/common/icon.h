#pragma once
#include <string>
#include <QtCore/QRect>
#include <QtGui/QIcon>
#include <QtGui/QIconEngine>
#include <QtGui/QPainter>
#include <QtSvg/QSvgRenderer>
#include <QVariant>
#include <QtWidgets/QAction>
#include <QMetaType>
#include "config.h"

//namespace Qfw{

const static std::map<QString, QString> FluentIconMap = {
        {"UP", "One"},
        {"UP", "Up"},
        {"ADD", "Add"},
        {"BUS", "Bus"},
        {"CAR", "Car"},
        {"CUT", "Cut"},
        {"IOT", "IOT"},
        {"PIN", "Pin"},
        {"TAG", "Tag"},
        {"VPN", "VPN"},
        {"CAFE", "Cafe"},
        {"CHAT", "Chat"},
        {"COPY", "Copy"},
        {"CODE", "Code"},
        {"DOWN", "Down"},
        {"EDIT", "Edit"},
        {"FLAG", "Flag"},
        {"FONT", "Font"},
        {"GAME", "Game"},
        {"HELP", "Help"},
        {"HIDE", "Hide"},
        {"HOME", "Home"},
        {"INFO", "Info"},
        {"LEAF", "Leaf"},
        {"LINK", "Link"},
        {"MAIL", "Mail"},
        {"MENU", "Menu"},
        {"MUTE", "Mute"},
        {"MORE", "More"},
        {"MOVE", "Move"},
        {"PLAY", "Play"},
        {"SAVE", "Save"},
        {"SEND", "Send"},
        {"SYNC", "Sync"},
        {"UNIT", "Unit"},
        {"VIEW", "View"},
        {"WIFI", "Wifi"},
        {"ZOOM", "Zoom"},
        {"ALBUM", "Album"},
        {"BRUSH", "Brush"},
        {"BROOM", "Broom"},
        {"CLOSE", "Close"},
        {"CLOUD", "Cloud"},
        {"EMBED", "Embed"},
        {"GLOBE", "Globe"},
        {"HEART", "Heart"},
        {"LABEL", "Label"},
        {"MEDIA", "Media"},
        {"MOVIE", "Movie"},
        {"MUSIC", "Music"},
        {"ROBOT", "Robot"},
        {"PAUSE", "Pause"},
        {"PASTE", "Paste"},
        {"PHOTO", "Photo"},
        {"PHONE", "Phone"},
        {"PRINT", "Print"},
        {"SHARE", "Share"},
        {"TILES", "Tiles"},
        {"UNPIN", "Unpin"},
        {"VIDEO", "Video"},
        {"TRAIN", "Train"},
        {"ADD_TO ","AddTo"},
        {"ACCEPT", "Accept"},
        {"CAMERA", "Camera"},
        {"CANCEL", "Cancel"},
        {"DELETE", "Delete"},
        {"FOLDER", "Folder"},
        {"FILTER", "Filter"},
        {"MARKET", "Market"},
        {"SCROLL", "Scroll"},
        {"LAYOUT", "Layout"},
        {"GITHUB", "GitHub"},
        {"UPDATE", "Update"},
        {"REMOVE", "Remove"},
        {"RETURN", "Return"},
        {"PEOPLE", "People"},
        {"QRCODE", "QRCode"},
        {"RINGER", "Ringer"},
        {"ROTATE", "Rotate"},
        {"SEARCH", "Search"},
        {"VOLUME", "Volume"},
        {"FRIGID ", "Frigid"},
        {"SAVE_AS", "SaveAs"},
        {"ZOOM_IN", "ZoomIn"},
        {"CONNECT ","Connect"},
        {"HISTORY", "History"},
        {"SETTING", "Setting"},
        {"PALETTE", "Palette"},
        {"MESSAGE", "Message"},
        {"FIT_PAGE", "FitPage"},
        {"ZOOM_OUT", "ZoomOut"},
        {"AIRPLANE", "Airplane"},
        {"ASTERISK", "Asterisk"},
        {"CALORIES", "Calories"},
        {"CALENDAR", "Calendar"},
        {"FEEDBACK", "Feedback"},
        {"LIBRARY", "BookShelf"},
        {"MINIMIZE", "Minimize"},
        {"CHECKBOX", "CheckBox"},
        {"DOCUMENT", "Document"},
        {"LANGUAGE", "Language"},
        {"DOWNLOAD", "Download"},
        {"QUESTION", "Question"},
        {"SPEAKERS", "Speakers"},
        {"DATE_TIME", "DateTime"},
        {"FONT_SIZE", "FontSize"},
        {"HOME_FILL", "HomeFill"},
        {"PAGE_LEFT", "PageLeft"},
        {"SAVE_COPY", "SaveCopy"},
        {"SEND_FILL", "SendFill"},
        {"SKIP_BACK", "SkipBack"},
        {"SPEED_OFF", "SpeedOff"},
        {"ALIGNMENT", "Alignment"},
        {"BLUETOOTH", "Bluetooth"},
        {"COMPLETED", "Completed"},
        {"CONSTRACT", "Constract"},
        {"HEADPHONE", "Headphone"},
        {"MEGAPHONE", "Megaphone"},
        {"PROJECTOR", "Projector"},
        {"EDUCATION", "Education"},
        {"LEFT_ARROW", "LeftArrow"},
        {"ERASE_TOOL", "EraseTool"},
        {"PAGE_RIGHT", "PageRight"},
        {"PLAY_SOLID", "PlaySolid"},
        {"BOOK_SHELF", "BookShelf"},
        {"HIGHTLIGHT", "Highlight"},
        {"FOLDER_ADD", "FolderAdd"},
        {"PAUSE_BOLD", "PauseBold"},
        {"PENCIL_INK", "PencilInk"},
        {"PIE_SINGLE", "PieSingle"},
        {"QUICK_NOTE", "QuickNote"},
        {"SPEED_HIGH", "SpeedHigh"},
        {"STOP_WATCH", "StopWatch"},
        {"ZIP_FOLDER", "ZipFolder"},
        {"BASKETBALL", "Basketball"},
        {"BRIGHTNESS", "Brightness"},
        {"DICTIONARY", "Dictionary"},
        {"MICROPHONE", "Microphone"},
        {"ARROW_DOWN", "ChevronDown"},
        {"FULL_SCREEN", "FullScreen"},
        {"MIX_VOLUMES", "MixVolumes"},
        {"REMOVE_FROM", "RemoveFrom"},
        {"RIGHT_ARROW", "RightArrow"},
        {"QUIET_HOURS ","QuietHours"},
        {"FINGERPRINT", "Fingerprint"},
        {"APPLICATION", "Application"},
        {"CERTIFICATE", "Certificate"},
        {"TRANSPARENT", "Transparent"},
        {"IMAGE_EXPORT", "ImageExport"},
        {"SPEED_MEDIUM", "SpeedMedium"},
        {"LIBRARY_FILL", "LibraryFill"},
        {"MUSIC_FOLDER", "MusicFolder"},
        {"POWER_BUTTON", "PowerButton"},
        {"SKIP_FORWARD", "SkipForward"},
        {"CARE_UP_SOLID", "CareUpSolid"},
        {"ACCEPT_MEDIUM", "AcceptMedium"},
        {"CANCEL_MEDIUM", "CancelMedium"},
        {"CHEVRON_RIGHT", "ChevronRight"},
        {"CLIPPING_TOOL", "ClippingTool"},
        {"SEARCH_MIRROR", "SearchMirror"},
        {"SHOPPING_CART", "ShoppingCart"},
        {"FONT_INCREASE", "FontIncrease"},
        {"BACK_TO_WINDOW", "BackToWindow"},
        {"COMMAND_PROMPT", "CommandPrompt"},
        {"CLOUD_DOWNLOAD", "CloudDownload"},
        {"DICTIONARY_ADD", "DictionaryAdd"},
        {"CARE_DOWN_SOLID", "CareDownSolid"},
        {"CARE_LEFT_SOLID", "CareLeftSolid"},
        {"CLEAR_SELECTION", "ClearSelection"},
        {"DEVELOPER_TOOLS", "DeveloperTools"},
        {"BACKGROUND_FILL", "BackgroundColor"},
        {"CARE_RIGHT_SOLID", "CareRightSolid"},
        {"CHEVRON_DOWN_MED", "ChevronDownMed"},
        {"CHEVRON_RIGHT_MED", "ChevronRightMed"},
        {"EMOJI_TAB_SYMBOLS", "EmojiTabSymbols"},
        {"EXPRESSIVE_INPUT_ENTRY", "ExpressiveInputEntry"}
};

class SvgIconEngine : public QIconEngine{
public:
    SvgIconEngine(QString svg);
    void paint(QPainter *painter, const QRect &rect, QIcon::Mode mode, QIcon::State state) override;
    QIconEngine *clone() const override;
    QPixmap pixmap(const QSize &size, QIcon::Mode mode, QIcon::State state);
private:
    QString svg;
};


class FluentIconBase{
public:
    QIcon *_icon;
    QString path(Theme theme);
    QIcon *icon(Theme theme, QColor color);
    QIcon *qicon(bool reverse);
    QString iconName;
    void setIconName(QString iconName);
    virtual void render(QPainter *painter, QRect rect, Theme theme, int indexes, std::map<QString, QString> *attributes);
private:
    FluentIconBase *t = this;
};

Q_DECLARE_METATYPE(FluentIconBase)
Q_DECLARE_METATYPE(FluentIconBase *)

class FluentIcon : public FluentIconBase{
public:
    QIcon *icon(Theme theme, QColor color);
    QString path(Theme theme);
    void render(QPainter *painter, QRect rect, Theme theme, int indexes, std::map<QString, QString> *attributes) override;
private:
    //std::map<QString, QString> FluentIconMap = FluentIconMap;
};

Q_DECLARE_METATYPE(FluentIcon)

class Icon : public QIcon{
public:
    Icon();
    Icon(FluentIcon *fluentIcon);
    FluentIcon *fluentIcon;
private:

};

Q_DECLARE_METATYPE(Icon)

class FluentIconEngine : public QIconEngine{
public:

    FluentIconEngine(QVariant *icon, bool reverse);
    void paint(QPainter *painter, const QRect &rect, QIcon::Mode mode, QIcon::State state) override;
    FluentIconEngine *clone() const override;
private:
    QVariant *icon; //QICon | Icon | FluentIconBase
    QIcon *icon_QIcon;
    bool isThemeReversed;
};

class MIcon{
public:
    QIcon toQIcon(QVariant *icon);
    void drawIcon(QVariant *icon, QPainter *painter, QRect rect, std::map<QString, QString> *attributes, QIcon::State state);
};

class Action : public QAction{
    Q_OBJECT
public:
    Action(QObject *parent);
    Action(QString text, QObject *parent);
    Action(QIcon icon, QString text, QObject *parent);
    Action(FluentIcon *icon, QString text, QObject *parent);
    QIcon *icon();
    void setIcon(QVariant *icon);

    FluentIcon *fluentIcon;
private:
};