#pragma once

#include <QtCore/Qt>
#include <QtGui/QIcon>
#include <QtGui/QPainter>
#include <QtGui/QColor>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QApplication>

#include "../common/config.h"
#include "../common/icon.h"
#include "../common/router.h"
#include "../common/style_sheet.h"
#include "../common/animation.h"
#include "../../qfluentwidgets/qframelesswindow/windows/qframe_less_window.h"
#include "../components/navigation/navigation_interface.h"
#include "../components/navigation/navigation_bar.h"
#include "../components/navigation/navigation_panel.h"
#include "../components/navigation/navigation_widget.h"
#include "../../qfluentwidgets/qframelesswindow/titlebar/titlebar.h"
#include "stacked_widget.h"


class FluentWindowBase : public WindowsFramelessWindow{
    Q_OBJECT
    Q_PROPERTY(QColor backgroundColor READ getBackgroundColor WRITE setBackgroundColor)
public:
    FluentWindowBase(QWidget *parent);
    virtual void addSubInterface(QWidget *_interface, QVariant *icon, QString text, NavigationItemPosition position);
    void switchTo(QWidget *_interface);
    void _updateStackedBackground();
    QColor _normalBackgroundColor();
    void paintEvent(QPaintEvent *event) override;
    bool isMicaEffctEnabled();

    QHBoxLayout *hBoxLayout;
    StackedWidget *stackedWidget;
    NavigationInterface *navigationInterface;
    bool _isMicaEnabled;


    bool eventFilter(QObject *obj, QEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void enterEvent(QEnterEvent *e);
    void leaveEvent(QEvent *e);
    void focusInEvent(QFocusEvent *e);
    QColor _hoverBackgroundColor();
    QColor _pressedBackgroundColor();
    QColor _focusInBackgroundColor();
    QColor _disabledBackgroundColor();
    
    QColor getBackgroundColor();
    void setBackgroundColor(QColor color);
    QColor backgroundColor();

    bool isHover;
    bool isPressed;
    //BackgroundColorObject *bgColorObject;
    FluentWindowBase *bgColorObject;
    QPropertyAnimation *backgroundColorAni;
    QColor _backgroundColor;

public slots:
    void _onCurrentInterfaceChanged(int index);
    void _onThemeChangedFinished();
    void setMicaEffectEnabled(bool isEnabled);
    void _updateBackgroundColor();
};


class FluentTitleBar : public TitleBar{
    Q_OBJECT
public:
    FluentTitleBar(QWidget *parent);
    void setTitle(QString title);
    void setIcon(QIcon icon);

    QLabel *iconLabel;
    QLabel *titleLabel;
    QVBoxLayout *vBoxLayout;
    QHBoxLayout *buttonLayout;
};


class FluentWindow : public FluentWindowBase{
    Q_OBJECT
public:
    FluentWindow(QWidget *parent);
    NavigationTreeWidget *addSubInterface(QWidget *_interface, QVariant *icon, QString text, NavigationItemPosition position, QWidget *parent, bool isTransparent);
    void resizeEvent(QResizeEvent *event);

    //NavigationInterface *navigationInterface;
    QHBoxLayout *widgetLayout;
};

class MSFluentTitleBar : public FluentTitleBar{
    Q_OBJECT
public:
    MSFluentTitleBar(QWidget *parent);
};



class MSBackgroundColorObject;
class MSFluentWindow : public WindowsFramelessWindow{
    Q_OBJECT
public:
    MSFluentWindow(QWidget *parent);
    NavigationBarPushButton *addSubInterface(QWidget *_interface, QVariant *icon, QString text, QVariant *selectedIcon, NavigationItemPosition position, bool isTransparent);
    void switchTo(QWidget *_interface);
    void _updateStackedBackground();
    QColor _normalBackgroundColor();
    void paintEvent(QPaintEvent *event) override;
    void setMicaEffectEnabled(bool isEnabled);
    bool isMicaEffctEnabled();

    QHBoxLayout *hBoxLayout;
    StackedWidget *stackedWidget;
    NavigationBar *navigationInterface;
    bool _isMicaEnabled;


    bool eventFilter(QObject *obj, QEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void enterEvent(QEnterEvent *e);
    void leaveEvent(QEvent *e);
    void focusInEvent(QFocusEvent *e);
    QColor _hoverBackgroundColor();
    QColor _pressedBackgroundColor();
    QColor _focusInBackgroundColor();
    QColor _disabledBackgroundColor();
    void _updateBackgroundColor();
    QColor *getBackgroundColor();
    void setBackgroundColor(QColor color);
    QColor *backgroundColor();

    bool isHover;
    bool isPressed;
    MSBackgroundColorObject *bgColorObject;
    QPropertyAnimation *backgroundColorAni;

public slots:
    void _onCurrentInterfaceChanged(int index);
    void _onThemeChangedFinished();

};

class MSBackgroundColorObject : public BackgroundColorObject{
    Q_OBJECT
public:
    MSBackgroundColorObject(MSFluentWindow *parent);
    QColor getBackgroundColor() override;
    void setBackgroundColor(QColor color);
};


class SplitTitleBar : public TitleBar{
    Q_OBJECT
public:
    SplitTitleBar(QWidget *parent);
    void setTitle(QString title);
    void setIcon(QIcon icon);

    QLabel *iconLabel;
    QLabel *titleLabel;
};


class SplitFluentWindow : public FluentWindow{
    Q_OBJECT
public:
    SplitFluentWindow(QWidget *parent);
};