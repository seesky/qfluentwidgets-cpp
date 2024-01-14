/*
 * @Description: 
 * @Version: 1.0
 * @Autor: Xuelong Ba
 * @Date: 2024-01-13 08:31:04
 * @LastEditors: Xuelong Ba
 * @LastEditTime: 2024-01-14 23:23:08
 */
#pragma once

#include "../../common/icon.h"
#include "../../common/style_sheet.h"
#include "../../common/font.h"
#include "scroll_bar.h"
#include "../../common/config.h"
#include "../../qframelesswindow/windows/window_effect.h"
#include <QtCore/QEasingCurve>
#include <QtCore/QEvent>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QObject>
#include <QtCore/QModelIndex>
#include <QtCore/Qt>
#include <QtCore/QSize>
#include <QtCore/QRectF>
#include <QtCore/QPoint>
#include <QtCore/QTimer>
#include <QtCore/QParallelAnimationGroup>
#include <QtGui/QIcon>
#include <QtGui/QColor>
#include <QtGui/QPainter>
#include <QtGui/QPen>
#include <QtGui/QPixmap>
#include <QtGui/QRegion>
#include <QtGui/QCursor>
#include <QtGui/QTextCursor>
#include <QtGui/QHoverEvent>
#include <QtGui/QFontMetrics>
#include <QtGui/QKeySequence>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMenu>
#include <QtWidgets/QProxyStyle>
#include <QtWidgets/QStyle>
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidgetItem>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QStyledItemDelegate>
#include <QtWidgets/QStyleOptionViewItem>

enum class MenuAnimationType{
    NONE = 0,
    DROP_DOWN = 1,
    PULL_UP = 2,
    FADE_IN_DROP_DOWN = 3,
    FADE_IN_PULL_UP = 4
};


/*
    QApplication a(argc, argv);
    MyClass myClassObject; //contains a function called MemberFunc
    //create a slotforwarder object so 
    SlotForwarder *memberFuncSlot = new SlotForwarder (std::tr1::bind(&MyClass::MemberFunc, &myClassObject));
    QObject::connect(ui.button,SIGNAL(clicked()),memberFuncSlot,SLOT(forward());
*/
class SlotForwarder : public QObject
{
    Q_OBJECT
public:
    typedef void (*Function)();
    SlotForwarder(Function function, QObject* parent = 0) 
        : QObject(parent)
        , m_fptr(function)
    {}
public slots:
    void forward()
    {
        m_fptr();
    }
private:
    Function m_fptr;
};


class CustomMenuStyle : public QProxyStyle{
    Q_OBJECT
public:
    CustomMenuStyle(int iconSize);
    int pixelMetric(PixelMetric metric, QStyleOption *option, QWidget *widget); 

    int iconSize;
private:
};

class DWMMenu : public QMenu{
    Q_OBJECT
public:
    DWMMenu(QString title, QWidget *parent);
    bool event(QEvent *e);

    WindowsWindowEffect *windowEffect;
private:
};


class SubMenuItemWidget : public QWidget{
    Q_OBJECT
public:
    SubMenuItemWidget(QMenu *menu, QListWidgetItem *item, QWidget *parent);
    void enterEvent(QEvent *event);
    void paintEvent(QPaintEvent *event);

    QMenu *menu;
    QListWidgetItem *item;
private:
signals:
    void showMenuSig(QListWidgetItem *);
};


class MenuItemDelegate : public QStyledItemDelegate{
    Q_OBJECT
public:
    MenuItemDelegate(QObject *parent) : QStyledItemDelegate(parent){};
    bool _isSeparator(QModelIndex index);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index);
private:
};

class ShortcutMenuItemDelegate : public MenuItemDelegate{
    Q_OBJECT
public:
    ShortcutMenuItemDelegate(QObject *parent) : MenuItemDelegate(parent){};
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index);
private:
};


class MenuActionListWidget : public QListWidget{
    Q_OBJECT
public:
    MenuActionListWidget(QWidget *parent);
    void insertItem(int row, QListWidgetItem *item);
    void addItem(QListWidgetItem *item);
    QListWidgetItem *takeItem(int row);
    void adjustSize(QPoint *pos, MenuAnimationType aniType);
    void setItemHeight(int height);
    void setMaxVisibleItems(int num);
    int maxVisibleItems();
    int heightForAnimation(QPoint *pos, MenuAnimationType aniType);
    int itemsHeight();

    int _itemHeight;
    int _maxVisibleItems;
    SmoothScrollDelegate *scrollDelegate;
private:
};


class MenuAnimationManager;
class RoundMenu : public QMenu{
    Q_OBJECT
public:
    RoundMenu(QString title, QWidget *parent);
    void __initWidgets();
    void setMaxVisibleItems(int num);
    void setItemHeight(int height);
    void setShadowEffect(int blurRadius, std::tuple<int, int> offset, QColor *color);
    void _setParentMenu(RoundMenu *parent, QListWidgetItem *item);
    void adjustSize();
    QVariant *icon();
    QString title();
    void clear();
    void setIcon(QVariant *icon);
    void addAction(QAction *action);
    void addWidget(QWidget *widget, bool selectable, SlotForwarder *onClick);
    QListWidgetItem *_createActionItem(QAction *action, QAction *before);
    bool _hasItemIcon();
    int _adjustItemText(QListWidgetItem *item, QAction *action);
    int _longestShortcutWidth();
    QIcon *_createItemIcon(QAction *w);
    void insertAction(QAction *before, QAction *action);
    void addActions(QList<QAction *> *action);
    void insertActions(QAction *before, QList<QAction *> *actions);
    void removeAction(QAction *action);
    void setDefaultAction(QAction *action);
    void addMenu(RoundMenu *menu);
    void insertMenu(QAction *before, RoundMenu *menu);
    std::tuple<QListWidgetItem *, SubMenuItemWidget*> _createSubMenuItem(RoundMenu *menu);
    void _showSubMenu(QListWidgetItem *item);
    void _onShowMenuTimeOut();
    void addSeparator();
    void _onItemClicked(QListWidgetItem *item);
    void _closeParentMenu();
    void _onItemEntered(QListWidgetItem *item);
    void _hideMenu(bool isHideBySystem);
    void hideEvent(QHideEvent *e);
    void closeEvent(QCloseEvent *e);
    QAction *menuActions();
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void _onActionChanged();
    void exec_(QPoint *pos, bool ani, MenuAnimationType aniType);
    void adjustPosition();
    void paintEvent(QPaintEvent *e);

    QString _title;
    QVariant *_icon;
    QList<QAction *> *_actions;
    QList<RoundMenu *> *_subMenus;
    bool isSubMenu;
    RoundMenu *parentMenu;
    QListWidgetItem *menuItem;
    QListWidgetItem *lastHoverItem;
    QListWidgetItem *lastHoverSubMenuItem;
    bool isHideBySystem;
    int itemHeight;
    QHBoxLayout *hBoxLayout;
    MenuActionListWidget *view;
    MenuAnimationManager *aniManager;
    QTimer *timer;
    QGraphicsDropShadowEffect *shadowEffect;
private:

signals:
    void closedSignal();
};


class MenuAnimationManager : public QObject{
    Q_OBJECT
public:

private:
};