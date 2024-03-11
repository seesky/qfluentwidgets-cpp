#pragma once

#include <QtCore/Qt>
#include <QtCore/QEvent>
#include <QtCore/QSize>
#include <QtCore/QRectF>
#include <QtCore/QObject>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QEasingCurve>
#include <QtCore/QTimer>
#include <QtCore/QParallelAnimationGroup>
#include <QtCore/QPoint>
#include <QtGui/QPainter>
#include <QtGui/QIcon>
#include <QtGui/QColor>
#include <QtWidgets/QWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QGraphicsOpacityEffect>

#include "../../common/auto_wrap.h"
#include "../../common/style_sheet.h"
#include "../../common/icon.h"
#include "button.h"

Q_DECLARE_METATYPE(QPropertyAnimation*)







enum class InfoBarPosition{
    TOP = 0,
    BOTTOM = 1,
    TOP_LEFT = 2,
    TOP_RIGHT = 3,
    BOTTOM_LEFT = 4,
    BOTTOM_RIGHT = 5,
    NONE = 6
};

class InfoIconWidget : public QWidget{
    Q_OBJECT
public:
    InfoIconWidget(InfoBarIcon *icon, QWidget *parent);
    void paintEvent(QPaintEvent *event) override;
    InfoBarIcon *icon;
};


class InfoBar : public QFrame{
    Q_OBJECT
public:
    InfoBar(InfoBarIcon *icon, QString title, QString content, Qt::Orientation orient, bool isClosable, int duration, InfoBarPosition position, QWidget *parent);
    void __initWidget();
    void __initLayout();
    void __setQss();
    void __fadeOut();
    void _adjustText();
    void addWidget(QWidget *widget, int stretch);
    void setCustomBackgroundColor(QVariant light, QVariant dark);
    bool eventFilter(QObject *obj, QEvent *e) override;
    void closeEvent(QCloseEvent *event) override;
    void showEvent(QShowEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    static InfoBar* _new(InfoBarIcon *, QString title, QString content, Qt::Orientation orient, bool isCloseable, int duration, InfoBarPosition position, QWidget *parent);
    static InfoBar* success(QString title, QString content, Qt::Orientation orient, bool isClosable, int duration, InfoBarPosition position, QWidget *parent);
    static InfoBar* info(QString title, QString content, Qt::Orientation orient, bool isClosable, int duration, InfoBarPosition position, QWidget *parent);
    static InfoBar* warning(QString title, QString content, Qt::Orientation orient, bool isClosable, int duration, InfoBarPosition position, QWidget *parent);
    static InfoBar* error(QString title, QString content, Qt::Orientation orient, bool isClosable, int duration, InfoBarPosition position, QWidget *parent);
    
    QString title;
    QString content;
    Qt::Orientation orient;
    InfoBarIcon *icon;
    int duration;
    bool isClosable;
    InfoBarPosition position;
    QLabel *titleLabel;
    QLabel *contentLabel;
    TransparentToolButton *closeButton;
    InfoIconWidget *iconWidget;

    QHBoxLayout *hBoxLayout;
    QBoxLayout *textLayout;
    QBoxLayout *widgetLayout;

    QGraphicsOpacityEffect *opacityEffect;
    QPropertyAnimation *opacityAni;

    QColor lightBackgroundColor;
    QColor darkBackgroundColor;
signals:
    void closedSignal();
};


class InfoBarManager : public QObject{
    Q_OBJECT
public:
    InfoBarManager();
    void add(InfoBar *infoBar);
    void remove(InfoBar *infoBar);
    QPropertyAnimation *_createSlideAni(InfoBar *infoBar);
    void _updateDropAni(QObject *parent);
    virtual QPoint _pos(InfoBar *infoBar, QSize parentSize);
    virtual QPoint _slideStartPos(InfoBar *infoBar);
    bool eventFilter(QObject *obj, QEvent *e) override;
    static InfoBarManager *make(InfoBarPosition position);

    int spacing;
    int margin;
    QMap<QObject*, QList<InfoBar*>*> infoBars;
    QMap<QObject*, QParallelAnimationGroup*> aniGroups;
    QList<QPropertyAnimation*> slideAnis;
    QList<QPropertyAnimation*> dropAnis;
    bool __initialized;
private:
};


class TopInfoBarManager : public InfoBarManager{
    Q_OBJECT
public:
    TopInfoBarManager();
    QPoint _pos(InfoBar *infoBar, QSize parentSize) override;
    QPoint _slideStartPos(InfoBar *infoBar) override;
};



class TopRightInfoBarManager : public InfoBarManager{
    Q_OBJECT
public:
    TopRightInfoBarManager();
    QPoint _pos(InfoBar *infoBar, QSize parentSize) override;
    QPoint _slideStartPos(InfoBar *infoBar) override;
};


class BottomRightInfoBarManager : public InfoBarManager{
    Q_OBJECT
public:
    BottomRightInfoBarManager();
    QPoint _pos(InfoBar *infoBar, QSize parentSize) override;
    QPoint _slideStartPos(InfoBar *infoBar) override;
};


class TopLeftInfoBarManager : public InfoBarManager{
    Q_OBJECT
public:
    TopLeftInfoBarManager();
    QPoint _pos(InfoBar *infoBar, QSize parentSize) override;
    QPoint _slideStartPos(InfoBar *infoBar) override;
};


class BottomLeftInfoBarManager : public InfoBarManager{
    Q_OBJECT
public:
    BottomLeftInfoBarManager();
    QPoint _pos(InfoBar *infoBar, QSize parentSize) override;
    QPoint _slideStartPos(InfoBar *infoBar) override;
};


class BottomInfoBarManager : public InfoBarManager{
    Q_OBJECT
public:
    BottomInfoBarManager();
    QPoint _pos(InfoBar *infoBar, QSize parentSize) override;
    QPoint _slideStartPos(InfoBar *infoBar) override;
};