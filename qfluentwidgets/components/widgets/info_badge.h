#pragma once

#include <QtCore/Qt>
#include <QtCore/QSize>
#include <QtCore/QRectF>
#include <QtCore/QObject>
#include <QtCore/QEvent>
#include <QtCore/QPoint>
#include <QtGui/QPixmap>
#include <QtGui/QPainter>
#include <QtGui/QColor>
#include <QtGui/QIcon>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include <QtWidgets/QSizePolicy>
#include <QDebug>

#include "../../common/font.h"
#include "../../common/icon.h"
#include "../../common/style_sheet.h"

const static QMap<QString, QString> InfoLevel = {
    {"INFOAMTION", "Info"},
    {"SUCCESS", "Success"},
    {"ATTENTION", "Attension"},
    {"WARNING", "Warning"},
    {"ERROR", "Error"}
};


enum class InfoBadgePosition{
    TOP_RIGHT = 0,
    BOTTOM_RIGHT = 1,
    RIGHT = 2,
    TOP_LEFT = 3,
    BOTTOM_LEFT = 4,
    LEFT = 5,
    NAVIGATION_ITEM = 6
};

class InfoBadgeManager;
class InfoBadge : public QLabel{
    Q_OBJECT
public:
    InfoBadge(QWidget *parent, QString level);
    InfoBadge(QString text, QWidget *parent, QString level);
    InfoBadge(int num, QWidget *parent, QString level);
    InfoBadge(float num, QWidget *parent, QString level);
    void setLevel(QString level);
    void setProperty(const char *name, QVariant *value);
    void setCustomBackgroundColor(QVariant *light, QVariant *dark);
    void paintEvent(QPaintEvent *e) override;
    QColor _backgroundColor();
    static InfoBadge* make(QVariant *text, QWidget *parent, QString level, QWidget *target, InfoBadgePosition position);
    static InfoBadge* info(QVariant *text, QWidget *parent, QWidget *target, InfoBadgePosition postion);
    static InfoBadge* success(QVariant *text, QWidget *parent, QWidget *target, InfoBadgePosition postion);
    static InfoBadge* attension(QVariant *text, QWidget *parent, QWidget *target, InfoBadgePosition postion);
    static InfoBadge* warning(QVariant *text, QWidget *parent, QWidget *target, InfoBadgePosition postion);
    static InfoBadge* error(QVariant *text, QWidget *parent, QWidget *target, InfoBadgePosition postion);
    static InfoBadge* custom(QVariant *text, QColor light, QColor dark, QWidget *parent, QWidget *target, InfoBadgePosition postion); 

    QString level;
    QColor lightBackgroundColor;
    QColor darkBackgroundColor;
    InfoBadgeManager *manager;
};


class DotInfoBadge : public InfoBadge{
    Q_OBJECT
public:
    DotInfoBadge(QWidget *parent, QString level);
    void paintEvent(QPaintEvent *e) override;
    static DotInfoBadge* make(QWidget *parent, QString level, QWidget *target, InfoBadgePosition position);
    static DotInfoBadge* info(QWidget *parent, QWidget *target, InfoBadgePosition position);
    static DotInfoBadge* success(QWidget *parent, QWidget *target, InfoBadgePosition position);
    static DotInfoBadge* attension(QWidget *parent, QWidget *target, InfoBadgePosition position);
    static DotInfoBadge* warning(QWidget *parent, QWidget *target, InfoBadgePosition position);
    static DotInfoBadge* error(QWidget *parent, QWidget *target, InfoBadgePosition position);
    static DotInfoBadge* custom(QColor light, QColor dark, QWidget *parent, QWidget *target, InfoBadgePosition position);
};



class IconInfoBadge : public InfoBadge{
    Q_OBJECT
public:
    IconInfoBadge(QWidget *parent, QString level);
    IconInfoBadge(FluentIcon *icon, QWidget *parent, QString level);
    IconInfoBadge(QIcon *icon, QWidget *parent, QString level);
    void setIcon(QVariant *icon);
    QIcon icon();
    QSize iconSize();
    void setIconSize(QSize size);
    void paintEvent(QPaintEvent *e) override;
    static IconInfoBadge* make(QVariant *icon, QWidget *parent, QString level, QWidget *target, InfoBadgePosition position);
    static IconInfoBadge* info(QVariant *icon, QWidget *parent, QWidget *target, InfoBadgePosition position);
    static IconInfoBadge* success(QVariant *icon, QWidget *parent, QWidget *target, InfoBadgePosition position);
    static IconInfoBadge* attension(QVariant *icon, QWidget *parent, QWidget *target, InfoBadgePosition position);
    static IconInfoBadge* warning(QVariant *icon, QWidget *parent, QWidget *target, InfoBadgePosition position);
    static IconInfoBadge* error(QVariant *icon, QWidget *parent, QWidget *target, InfoBadgePosition position);
    static IconInfoBadge* custom(QVariant *icon, QColor light, QColor dark, QWidget *parent, QWidget *target, InfoBadgePosition position);

    QVariant *_icon;
    QSize _iconSize;
};


class InfoBadgeManager : public QObject{
    Q_OBJECT
public:
    InfoBadgeManager(QWidget *target, InfoBadge *badge);
    bool eventFilter(QObject *watched, QEvent *event) override;
    static InfoBadgeManager *make(InfoBadgePosition postion, QWidget *target, InfoBadge *badge);
    virtual QPoint position();

    QWidget *target;
    InfoBadge *badge;
};


class TopRightInfoBadgeManager : public InfoBadgeManager{
    Q_OBJECT
public:
    TopRightInfoBadgeManager(QWidget *target, InfoBadge *badge) : InfoBadgeManager(target, badge){};
    QPoint position() override;
};


class RightInfoBadgeManager : public InfoBadgeManager{
    Q_OBJECT
public:
    RightInfoBadgeManager(QWidget *target, InfoBadge *badge) : InfoBadgeManager(target, badge){};
    QPoint position() override;
};


class BottomRightInfoBadgeManager : public InfoBadgeManager{
    Q_OBJECT
public:
    BottomRightInfoBadgeManager(QWidget *target, InfoBadge *badge) : InfoBadgeManager(target, badge){};
    QPoint position() override;
};

class TopLeftInfoBadgeManager : public InfoBadgeManager{
    Q_OBJECT
public:
    TopLeftInfoBadgeManager(QWidget *target, InfoBadge *badge) : InfoBadgeManager(target, badge){};
    QPoint position() override;
};


class LeftInfoBadgeManager : public InfoBadgeManager{
    Q_OBJECT
public:
    LeftInfoBadgeManager(QWidget *target, InfoBadge *badge) : InfoBadgeManager(target, badge){};
    QPoint position() override;
};


class BottomLeftInfoBadgeManager : public InfoBadgeManager{
    Q_OBJECT
public:
    BottomLeftInfoBadgeManager(QWidget *target, InfoBadge *badge) : InfoBadgeManager(target, badge){};
    QPoint position() override;
};

