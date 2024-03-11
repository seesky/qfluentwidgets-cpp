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
#include <QtGui/QScreen>
#include <QtGui/QClipboard>
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
#include <QtWidgets/QPlainTextEdit>

Q_DECLARE_METATYPE(QListWidgetItem *)

enum class MenuAnimationType{
    NONE = 0,
    DROP_DOWN = 1,
    PULL_UP = 2,
    FADE_IN_DROP_DOWN = 3,
    FADE_IN_PULL_UP = 4
};

Q_DECLARE_METATYPE(MenuAnimationType)

enum class MenuIndicatorType{
    CHECK = 0,
    RADIO = 1
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
    bool _isSeparator(QModelIndex index) const;
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
private:
};

class ShortcutMenuItemDelegate : public MenuItemDelegate{
    Q_OBJECT
public:
    ShortcutMenuItemDelegate(QObject *parent) : MenuItemDelegate(parent){};
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
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
    void publicSetViewportMargins(int left, int top, int right, int bottom);
    bool publicEvent(QEvent *e);
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
    QIcon *_createItemIcon(QVariant *w);
    void insertAction(QAction *before, QAction *action);
    void addActions(QList<QAction *> *actions);
    void insertActions(QAction *before, QList<QAction *> *actions);
    void removeAction(QAction *action);
    void setDefaultAction(QAction *action);
    void addMenu(RoundMenu *menu);
    void insertMenu(QAction *before, RoundMenu *menu);
    std::tuple<QListWidgetItem *, SubMenuItemWidget*> _createSubMenuItem(RoundMenu *menu);
    void addSeparator();
    void _closeParentMenu();
    void _hideMenu(bool isHideBySystem);
    void hideEvent(QHideEvent *e);
    void closeEvent(QCloseEvent *e);
    QList<QAction *> *menuActions();
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    virtual void exec(QPoint *pos, bool ani, MenuAnimationType aniType);
    void exec_(QPoint *pos, bool ani, MenuAnimationType aniType);
    void adjustPosition();
    void paintEvent(QPaintEvent *e);

    void cut(){};
    void copy(){};
    void paste(){};
    void undo(){};
    void selectAll(){};


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
    FluentIconEngine *fie;
private:

signals:
    void closedSignal();

public slots:
    void _showSubMenu(QListWidgetItem *item);
    void _onActionChanged();
    void _onItemClicked(QListWidgetItem *item);
    void _onItemEntered(QListWidgetItem *item);
    void _onShowMenuTimeOut();
};


class MenuAnimationManager : public QObject{
    Q_OBJECT
public:
    MenuAnimationManager() : QObject(){};
    MenuAnimationManager(RoundMenu *menu);
    
    virtual std::tuple<int, int> availableViewSize(QPoint *pos);
    virtual QPoint *_endPosition(QPoint *pos);
    virtual std::tuple<int, int> _menuSize();
    virtual void exec(QPoint *pos){};
    MenuAnimationManager *make(MenuAnimationType aniType, RoundMenu *menu);

    QMap<MenuAnimationType, QString> *managers;
    RoundMenu *menu;
    QPropertyAnimation *ani;
private:

public slots:
    virtual void _onValueChanged(){};
    virtual void _updateMenuViewport();
};

class DummyMenuAnimationManager : public MenuAnimationManager{
    Q_OBJECT
public:
    DummyMenuAnimationManager(RoundMenu *menu) : MenuAnimationManager(menu){};
    void exec(QPoint *pos) override;
private:
};


class DropDownMenuAnimationManager : public MenuAnimationManager{
    Q_OBJECT
public:
    DropDownMenuAnimationManager(RoundMenu *menu) : MenuAnimationManager(menu){};
    void exec(QPoint *pos)  override;
    std::tuple<int, int> availableViewSize(QPoint *pos) override;

public slots:
    void _onValueChanged() override;
};


class PullUpMenuAnimationManager : public MenuAnimationManager{
    Q_OBJECT
public:
    PullUpMenuAnimationManager(RoundMenu *menu) : MenuAnimationManager(menu){}
    void exec(QPoint *pos)  override;
    std::tuple<int, int> availableViewSize(QPoint *pos) override;
    QPoint *_endPosition(QPoint *pos) override;
public slots:
    void _onValueChanged() override;
};

class FadeInDropDownMenuAnimationManager : public MenuAnimationManager{
    Q_OBJECT
public:
    FadeInDropDownMenuAnimationManager(RoundMenu *menu);
    void exec(QPoint *pos)  override;
    std::tuple<int, int> availableViewSize(QPoint *pos) override;

    QPropertyAnimation *opacityAni;
    QParallelAnimationGroup *aniGroup;
};


class FadeInPullUpMenuAnimationManager : public MenuAnimationManager{
    Q_OBJECT
public:
    FadeInPullUpMenuAnimationManager(RoundMenu *menu);
    void exec(QPoint *pos)  override;
    std::tuple<int, int> availableViewSize(QPoint *pos) override;
    QPoint *_endPosition(QPoint *pos) override;

    QPropertyAnimation *opacityAni;
    QParallelAnimationGroup *aniGroup;
};

///////////////////////////////////////////////////////////////////////////////////////////
class MenuActionListAnimationManager : public QObject{
    Q_OBJECT
public:
    MenuActionListAnimationManager() : QObject(){};
    MenuActionListAnimationManager(MenuActionListWidget *menu);
    
    virtual std::tuple<int, int> availableViewSize(QPoint *pos);
    virtual QPoint *_endPosition(QPoint *pos);
    //std::tuple<int, int> _menuSize();
    virtual void exec(QPoint *pos){};
    MenuActionListAnimationManager *make(MenuAnimationType aniType, MenuActionListWidget *menu);

    QMap<MenuAnimationType, QString> *managers;
    MenuActionListWidget *menu;
    QPropertyAnimation *ani;
private:

public slots:
    //void _onValueChanged(){};
    //void _updateMenuViewport();
};


class DummyMenuActionListAnimationManager : public MenuActionListAnimationManager{
    Q_OBJECT
public:
    DummyMenuActionListAnimationManager(MenuActionListWidget *menu) : MenuActionListAnimationManager(menu){};
    void exec(QPoint *pos) override;
private:
};


class DropDownMenuActionListAnimationManager : public MenuActionListAnimationManager{
    Q_OBJECT
public:
    DropDownMenuActionListAnimationManager(MenuActionListWidget *menu) : MenuActionListAnimationManager(menu){};
    void exec(QPoint *pos) override;
    std::tuple<int, int> availableViewSize(QPoint *pos) override;

public slots:
    //void _onValueChanged();
};


class PullUpMenuActionListAnimationManager : public MenuActionListAnimationManager{
    Q_OBJECT
public:
    PullUpMenuActionListAnimationManager(MenuActionListWidget *menu) : MenuActionListAnimationManager(menu){}
    void exec(QPoint *pos) override;
    std::tuple<int, int> availableViewSize(QPoint *pos) override;
    QPoint *_endPosition(QPoint *pos) override;
public slots:
    //void _onValueChanged();
};

class FadeInDropDownMenuActionListAnimationManager : public MenuActionListAnimationManager{
    Q_OBJECT
public:
    FadeInDropDownMenuActionListAnimationManager(MenuActionListWidget *menu);
    void exec(QPoint *pos) override;
    std::tuple<int, int> availableViewSize(QPoint *pos) override;

    QPropertyAnimation *opacityAni;
    QParallelAnimationGroup *aniGroup;
};


class FadeInPullUpMenuActionListAnimationManager : public MenuActionListAnimationManager{
    Q_OBJECT
public:
    FadeInPullUpMenuActionListAnimationManager(MenuActionListWidget *menu);
    void exec(QPoint *pos) override;
    std::tuple<int, int> availableViewSize(QPoint *pos) override;
    QPoint *_endPosition(QPoint *pos) override;

    QPropertyAnimation *opacityAni;
    QParallelAnimationGroup *aniGroup;
};


class EditMenu : public RoundMenu{
    Q_OBJECT
public:
    EditMenu(QString title, QWidget *parent);
    void createActions();
    QString _parentText(){};
    QString _parentSelectedText(){};
    void exec(QPoint *pos, bool ani, MenuAnimationType aniType);

    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;
    QAction *cancelAct;
    QAction *selectAllAct;
    QList<QAction *> *action_list;
private:
};


class LineEditMenu : public EditMenu{
    Q_OBJECT
public:
    LineEditMenu(QLineEdit *parent);
    QString _parentText();
    QString _parentSelectedText();

    int selectionStart;
    int selectionLength;
public slots:
    void _onItemClicked(QListWidgetItem *item);
};


class TextEditMenu : public EditMenu{
    Q_OBJECT
public:
    TextEditMenu(QTextEdit *parent);
    QString _parentText();
    QString _parentSelectedText();

    int selectionStart;
    int selectionLength;
public slots:
    void _onItemClicked(QListWidgetItem *item);
};

class TextEditMenu2QPlainTextEdit : public EditMenu{
    Q_OBJECT
public:
    TextEditMenu2QPlainTextEdit(QPlainTextEdit *parent);
    QString _parentText();
    QString _parentSelectedText();

    int selectionStart;
    int selectionLength;
public slots:
    void _onItemClicked(QListWidgetItem *item);
};


class IndicatorMenuItemDelegate : public MenuItemDelegate{
    Q_OBJECT
public:
    IndicatorMenuItemDelegate(QObject *parent) : MenuItemDelegate(parent){};
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};


class CheckableMenuItemDelegate : public ShortcutMenuItemDelegate{
    Q_OBJECT
public:
    CheckableMenuItemDelegate(QObject *parent) : ShortcutMenuItemDelegate(parent){};
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void _drawIndicator(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const{};
};


class RadioIndicatorMenuItemDelegate : public CheckableMenuItemDelegate{
    Q_OBJECT
public:
    RadioIndicatorMenuItemDelegate(QObject *parent) : CheckableMenuItemDelegate(parent){};
    void _drawIndicator(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index);
};

class CheckIndicatorMenuItemDelegate : public CheckableMenuItemDelegate{
    Q_OBJECT
public:
    CheckIndicatorMenuItemDelegate(QObject *parent) : CheckableMenuItemDelegate(parent){};
    void _drawIndicator(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index);
};


QVariant *createCheckableMenuItemDelegate(MenuIndicatorType style);


class CheckableMenu : public RoundMenu{
    Q_OBJECT
public:
    CheckableMenu(QString title, QWidget *parent, MenuIndicatorType indicator);
    void _adjustItemText(QListWidgetItem *item, QAction *action);
};


class SystemTrayMenu : public RoundMenu{
    Q_OBJECT
public:
    void showEvent(QShowEvent *event);
};


class CheckableSystemTrayMenu : public CheckableMenu{
    Q_OBJECT
public:
    void showEvent(QShowEvent *event);
};