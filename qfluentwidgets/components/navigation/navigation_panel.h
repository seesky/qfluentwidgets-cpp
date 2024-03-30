#pragma once

#include <QtCore/Qt>
#include <QtCore/QVariant>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QRect>
#include <QtCore/QSize>
#include <QtCore/QEvent>
#include <QtCore/QEasingCurve>
#include <QtCore/QPoint>
#include <QtGui/QResizeEvent>
#include <QtGui/QIcon>
#include <QtGui/QColor>
#include <QtGui/QPainterPath>
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>

#include <functional>

#include "navigation_widget.h"
#include "../../components/widgets/arcylic_label.h"
#include "../../components/widgets/scroll_area.h"
#include "../../components/widgets/tool_tip.h"
#include "../../components/widgets/flyout.h"
#include "../../components/material/acrylic_flyout.h"
#include "../../common/router.h"
#include "../../common/style_sheet.h"
#include "../../common/icon.h"


enum class NavigationDisplayMode{
    MINIMAL = 0,
    COMPACT = 1,
    EXPAND = 2,
    MENU = 3
};

enum class NavigationItemPosition{
    TOP = 0,
    SCROLL = 1,
    BOTTOM = 2
};


class NavigationToolTipFilter : public ToolTipFilter{
    Q_OBJECT
public:
    NavigationToolTipFilter(QWidget *parent, int showDelay, ToolTipPosition position);
    bool _canShowToolTip() override;
};

/*
class RouteKeyError : public QException{
    Q_OBJECT
public:
};
*/

class NavigationItem{
public:
    NavigationItem(QString routeKey, QString parentRouteKey, NavigationWidget *widget);

    QString routeKey;
    QString parentRouteKey;
    NavigationWidget *widget;
};

class NavigationItemLayout;
class NavigationPanel : public QFrame{
    Q_OBJECT
public:
    NavigationPanel(QWidget *parent, bool isMinimalEnabled);
    void __initWidget();
    void __initLayout();
    void _updateAcrylicColor();
    NavigationWidget *widget(QString routeKey);
    NavigationTreeWidget *addItem(QString routeKey, QVariant *icon, QString text, std::function<void()> onClick, bool selectable, NavigationItemPosition position, QString tooltip, QString parentRouteKey);
    void addWidget(QString routeKey, NavigationWidget *widget, std::function<void()> onClick, NavigationItemPosition position, QString tooltip, QString parentRouteKey);
    NavigationTreeWidget *insertItem(int index, QString routeKey, QVariant *icon, QString text, std::function<void()> onClick, bool selectable, NavigationItemPosition position, QString tooltip, QString parentRouteKey);
    void insertWidget(int index, QString routeKey, NavigationWidget *widget, std::function<void()> onClick, NavigationItemPosition position, QString tooltip, QString parentRouteKey);
    void addSeparator(NavigationItemPosition position);
    void insertSeparator(int index, NavigationItemPosition position);
    void _registerWidget(QString routeKey, QString parentRouteKey, NavigationWidget *widget, std::function<void()>onClick, QString tooltip);
    void _insertWidgetToLayout(int index, NavigationWidget *widget, NavigationItemPosition position);
    void removeWidget(QString routeKey);
    void setMenuButtonVisible(bool isVisible);
    void setReturnButtonVisible(bool isVisible);
    void setCollapsible(bool on);
    void setExpandWidth(int width);
    void setAcrylicEnabled(bool isEnabled);
    bool isAcrylicEnabled();
    void expand(bool useAni);
    void collapse();

    void setCurrentItem(QString routeKey);
    void _showFlyoutNavigationMenu(NavigationTreeWidget *widget);
    void _adjustFlyoutMenuSize(Flyout *flyout, NavigationTreeWidget *widget, NavigationFlyoutMenu *menu);
    bool isCollapsed();
    void resizeEvent(QResizeEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *e) override;
    void _setWidgetCompacted(bool isCompacted);
    int layoutMinHeight();
    bool _canDrawAcrylic();
    void paintEvent(QPaintEvent *event) override;

    QWidget *_parent;
    bool _isMenuButtonVisible;
    bool _isReturnButtonVisible;
    bool _isCollapsible;
    bool _isAcrylicEnabled;
    
    AcrylicBrush * acrylicBrush;
    SingleDirectionScrollArea *scrollArea;
    QWidget *scrollWidget;
    NavigationToolButton *menuButton;
    NavigationToolButton *returnButton;

    NavigationItemLayout *vBoxLayout;
    NavigationItemLayout *topLayout;
    NavigationItemLayout *bottomLayout;
    NavigationItemLayout *scrollLayout;

    QMap<QString, NavigationItem*> items;
    Router *history;

    QPropertyAnimation *expandAni;
    int expandWidth;

    bool isMinimalEnabled;
    NavigationDisplayMode displayMode;

signals:
    void displayModeChanged(NavigationDisplayMode);

public slots:
    void _onWidgetClicked();
    void _onExpandAniFinished();
    void toggle();
};



class NavigationItemLayout : public QVBoxLayout{
    Q_OBJECT
public:
    NavigationItemLayout(QWidget *parent) : QVBoxLayout(parent){};
    void setGeometry(const QRect& rect) override;
};