#pragma once

#include <QtCore/Qt>
#include <QtCore/QEvent>
#include <QtGui/QResizeEvent>
#include <QtGui/QIcon>
#include <QtWidgets/QWidget>

#include "navigation_panel.h"
#include "navigation_widget.h"
#include "../../common/style_sheet.h"
#include "../../common/icon.h"

class NavigationInterface : public QWidget{
    Q_OBJECT
public:
    NavigationInterface(QWidget *parent, bool showMenuButton, bool showReturnButton, bool collapsible);
    NavigationTreeWidget *addItem(QString routeKey, QVariant *icon, QString text, std::function<void()> onClick, bool selectable, NavigationItemPosition position, QString tooltip, QString parentRouteKey);
    void addWidget(QString routeKey, NavigationWidget *widget, std::function<void()> onClick, NavigationItemPosition position, QString tooltip, QString parentRouteKey);
    NavigationTreeWidget *insertItem(int index, QString routeKey, QVariant *icon, QString text, std::function<void()> onClick, bool selectable, NavigationItemPosition position, QString tooltip, QString parentRouteKey);
    void insertWidget(int index, QString routeKey, NavigationWidget *widget, std::function<void()> onClick, NavigationItemPosition position, QString tooltip, QString parentRouteKey);
    void addSeparator(NavigationItemPosition position);
    void insertSeparator(int index, NavigationItemPosition position);
    void removeWidget(QString routeKey);
    void setCurrentItem(QString name);
    void setExpandWidth(int width);
    void setMenuButtonVisible(bool isVisible);
    void setReturnButtonVisible(bool isVisible);
    void setCollapsible(bool collapsible);
    bool isAcrylicEnabled();
    void setAcrylicEnabled(bool isEnabled);
    NavigationWidget *widget(QString routeKey);
    bool eventFilter(QObject *obj, QEvent *e) override;
    void resizeEvent(QResizeEvent *event) override;

    NavigationPanel *panel;

signals:
    void displayModeChanged(NavigationDisplayMode);
};