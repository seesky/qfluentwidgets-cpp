#pragma once

#include <QtCore/Qt>
#include <QtCore/QRect>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QEasingCurve>
#include <QtCore/QRectF>
#include <QtGui/QFont>
#include <QtGui/QPainter>
#include <QtGui/QColor>
#include <QtGui/QIcon>
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>

#include "../../common/config.h"
#include "../../common/font.h"
#include "../../common/style_sheet.h"
#include "../../common/icon.h"
#include "../../common/router.h"
#include "../../components/widgets/scroll_area.h"
#include "navigation_widget.h"
#include "navigation_panel.h"

class IconSlideAnimation : public QPropertyAnimation{
    Q_OBJECT
    Q_PROPERTY(float offset READ getOffset WRITE setOffset)
public:
    IconSlideAnimation(QWidget *parent);
    float getOffset();
    void setOffset(float value);
    void slideDown();
    void slideUp();

    float _offset;
    int maxOffset;

};



class NavigationBarPushButton : public NavigationPushButton{
    Q_OBJECT
public:
    NavigationBarPushButton(QVariant *icon, QString text, bool isSelectable, QVariant *selectedIcon, QWidget *parent);
    QIcon selectedIcon();
    void setSelectedIcon(QVariant *icon);
    void setSelectedTextVisible(bool isVisible);
    void paintEvent(QPaintEvent *event) override;
    void setSelected(bool isSelected);

    IconSlideAnimation *iconAni;
    QVariant *_selectedIcon;
    bool _isSelectedTextVisible;
};



class NavigationBar : public QWidget{
    Q_OBJECT
public:
    NavigationBar(QWidget *parent);
    void __initWidget();
    void __initLayout();
    NavigationWidget *widget(QString routeKey);
    NavigationBarPushButton *addItem(QString routeKey, QVariant *icon, QString text, std::function<void()> onClick, bool selectable, QVariant *selectedIcon, NavigationItemPosition position);
    void addWidget(QString routeKey, NavigationWidget *widget, std::function<void()> onClick, NavigationItemPosition position);
    NavigationBarPushButton *insertItem(int index, QString routeKey, QVariant *icon, QString text, std::function<void()> onClick, bool selectable, QVariant *selectedIcon, NavigationItemPosition position);
    void insertWidget(int index, QString routeKey, NavigationWidget *widget, std::function<void()> onClick, NavigationItemPosition position);
    void _registerWidget(QString routeKey, NavigationWidget *widget, std::function<void()> onClick);
    void _insertWidgetToLayout(int index, NavigationWidget *widget, NavigationItemPosition position);
    void removeWidget(QString routeKey);
    void setCurrentItem(QString routeKey);
    void setFont(QFont font);
    void setSelectedTextVisible(bool isVisible);
    QList<NavigationWidget*> buttons();

    SingleDirectionScrollArea *scrollArea;
    QWidget *scrollWidget;
    QVBoxLayout *vBoxLayout;
    QVBoxLayout *topLayout;
    QVBoxLayout *bottomLayout;
    QVBoxLayout *scrollLayout;

    QMap<QString, NavigationWidget*> items;
    Router *history;

public slots:
    void _onWidgetClicked();
};