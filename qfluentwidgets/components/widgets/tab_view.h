#pragma once

#include <QtCore/Qt>
#include <QtCore/QRectF>
#include <QtCore/QSize>
#include <QtCore/QPoint>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QEasingCurve>
#include <QtCore/QRect>
#include <QtGui/QPainter>
#include <QtGui/QColor>
#include <QtGui/QIcon>
#include <QtGui/QPainterPath>
#include <QtGui/QLinearGradient>
#include <QtGui/QPen>
#include <QtGui/QBrush>
#include <QtGui/QMouseEvent>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QSizePolicy>
#include <QtWidgets/QApplication>

#include "../../common/icon.h"
#include "../../common/style_sheet.h"
#include "../../common/font.h"
#include "../../common/router.h"
#include "button.h"
#include "scroll_area.h"
#include "tool_tip.h"


enum class TabCloseButtonDisplayMode{
    ALWAYS = 0,
    ON_HOVER = 1,
    NEVER = 2
};

/*
class TabBar;
// 定义一个检查索引有效性的函数模板
template<typename Func, typename... Defaults>
std::function<typename std::result_of<Func(TabBar*, int)>::type(TabBar*, int)>
checkIndex(Func func, Defaults... defaults) {
    // 返回一个 lambda 表达式，捕获 func 和 defaults...
    return [func, defaults...](TabBar* tabBar, int index) {
        // 检查索引是否有效
        if (0 <= index && index < tabBar->items->size()) {
            // 如果有效，调用原函数
            return func(tabBar, index);
        } else {
            // 如果索引无效，返回默认值
            return (... , defaults); // 折叠表达式，返回最后一个默认值
        }
    };
}
*/


class TabToolButton : public TransparentToolButton{
    Q_OBJECT
public:
    TabToolButton(QWidget *parent);
    TabToolButton(FluentIcon *icon, QWidget *parent);
    TabToolButton(SpinIcon *icon, QWidget *parent);
    TabToolButton(QIcon *icon, QWidget *parent);
    TabToolButton(QString icon, QWidget *parent);
    
    void _postInit() override;
    void _drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state)  override;

};


class TabItem : public PushButton{
    Q_OBJECT
public:
    TabItem(){};
    TabItem(QWidget *parent);
    TabItem(QString text, QWidget *parent, QVariant *icon);
    TabItem(QIcon *icon, QString text, QWidget *parent);
    TabItem(FluentIcon *icon, QString text, QWidget *parent);

    void _postInit() override;
    void __initWidget();
    void slideTo(int x, int duration);
    void setShadowEnabled(bool isEnabled);
    bool _canShowShadow();
    void setRouteKey(QString key);
    QString routeKey();
    void setBorderRadius(int radius);
    void setSelected(bool isSelected);
    void setCloseButtonDisplayMode(TabCloseButtonDisplayMode mode);
    void setTextColor(QColor color);
    void setSelectedBackgroundColor(QColor light, QColor dark);
    void resizeEvent(QResizeEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *e) override;
    void _forwardMouseEvent(QMouseEvent *e);
    QSize sizeHint();
    void paintEvent(QPaintEvent *event) override;
    void _drawSelectedBackground(QPainter *painter);
    void _drawNotSelectedBackground(QPainter *painter);
    void _drawText(QPainter *painter);


    int borderRadius;
    bool isSelected;
    bool isShadowEnabled;
    TabCloseButtonDisplayMode closeButtonDisplayMode;
    QString _routeKey;
    QColor textColor;
    QColor lightSelectedBackgroundColor;
    QColor darkSelectedBackgroundColor;
    TabToolButton *closeButton;
    QGraphicsDropShadowEffect *shadowEffect;
    QPropertyAnimation *slideAni;
signals:
    void closed();
};


class TabBar : public SingleDirectionScrollArea{
    Q_OBJECT
    Q_PROPERTY(bool movable READ isMovable WRITE setMovable)
    Q_PROPERTY(bool scrollable READ isScrollable WRITE setScrollable)
    Q_PROPERTY(int tabMaxWidth READ tabMaximumWidth WRITE setTabMaximumWidth)
    Q_PROPERTY(int tabMinWidth READ tabMinimumWidth WRITE setTabMinimumWidth)
    Q_PROPERTY(bool tabShadowEnabled READ isTabShadowEnabled WRITE setTabShadowEnabled)
public:
    TabBar(QWidget *parent);
    void __initWidget();
    void __initLayout();
    void setAddButtonVisible(bool isVisible);
    TabItem *addTab(QString routeKey, QString text, QVariant *icon, std::function<void()> onClick);
    TabItem *insertTab(int index, QString routeKey, QString text, QVariant *icon, std::function<void()> onClick);
    void removeTab(int index);
    void removeTabByKey(QString routeKey);
    void setCurrentIndex(int index);
    void setCurrentTab(QString routeKey);
    int currentIndex();
    TabItem *currentTab();
    void setCloseButtonDisplayMode(TabCloseButtonDisplayMode mode);
    TabItem *tabItem(int index);
    TabItem *tab(QString routeKey);
    QRect tabRegion();
    QRect tabRect(int index);
    QString tabText(int index);
    QIcon tabIcon(int index);
    QString tabToolTip(int index);
    void setTabsClosable(bool isClosable);
    bool tabsClosable();
    void setTabIcon(int index, QVariant *icon);
    void setTabText(int index, QString text);
    void setTabVisible(int index, bool isVisible);
    void setTabTextColor(int index, QColor color);
    void setTabToolTip(int index, QString toolTip);
    void setTabSelectedBackgroundColor(QColor light, QColor dark);
    void setTabShadowEnabled(bool isEnabled);
    bool isTabShadowEnabled();
    void paintEvent(QPaintEvent *event) override;
    void setMovable(bool movable);
    bool isMovable();
    void setScrollable(bool scrollable);
    void setTabMaximumWidth(int width);
    void setTabMinimumWidth(int width);
    int tabMaximumWidth();
    int tabMinimumWidth();
    bool isScrollable();
    int count();
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *e) override;

    void _swapItem(int index);


    QList<TabItem*> items;
    QMap<QString, TabItem*> itemMap;
    int _currentIndex;
    bool _isMovable;
    bool _isScrollable;
    bool _isTabShadowEnabled;
    int _tabMaxWidth;
    int _tabMinWidth;
    QPoint dragPos;
    bool isDraging;
    QColor lightSelectedBackgroundColor;
    QColor darkSelectedBackgroundColor;
    TabCloseButtonDisplayMode closeButtonDisplayMode;
    QWidget *view;
    QHBoxLayout *hBoxLayout;
    QHBoxLayout *itemLayout;
    QHBoxLayout *widgetLayout;

    TabToolButton *addButton;

signals:
    void currentChanged(int);
    void tabBarClicked(int);
    void tabCloseRequested(int);
    void tabAddRequested();


public slots:
    void _onItemPressed();
    void _adjustLayout();
};