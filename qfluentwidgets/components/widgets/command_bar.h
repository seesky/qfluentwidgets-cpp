#pragma once

#include <QtCore/Qt>
#include <QtCore/QSize>
#include <QtCore/QRectF>
#include <QtCore/QRect>
#include <QtCore/QPoint>
#include <QtCore/QEvent>
#include <QtGui/QPixmap>
#include <QtGui/QPainter>
#include <QtGui/QColor>
#include <QtGui/QFont>
#include <QtGui/QHoverEvent>
#include <QtGui/QPainterPath>
#include <QtWidgets/QAction>
#include <QtWidgets/QLayoutItem>
#include <QtWidgets/QWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QApplication>

#include "../../common/font.h"
#include "../../common/icon.h"
#include "../../common/style_sheet.h"
#include "menu.h"
#include "button.h"
#include "tool_tip.h"
#include "flyout.h"

class CommandToolTipFilter;
class CommandButton : public TransparentToggleToolButton{
    Q_OBJECT
public:
    CommandButton(QWidget *parent) : TransparentToggleToolButton(parent){};
    CommandButton(FluentIcon *icon, QWidget *parent) : TransparentToggleToolButton(icon, parent){
        this->_postInit();
    };
    CommandButton(QIcon *icon, QWidget *parent) : TransparentToggleToolButton(icon, parent){
        this->_postInit();
    };
    CommandButton(QString icon, QWidget *parent) : TransparentToggleToolButton(icon, parent){
        this->_postInit();
    };
    void _postInit() override;
    void setTight(bool isTight);
    bool isTight() const;
    QSize sizeHint() const override;
    bool isIconOnly() const;
    void _drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state) override;
    QString text() const;
    void setText(QString text);
    void setAction(QAction *action);
    QAction *action();
    void paintEvent(QPaintEvent *event) override;

    QString _text;
    QAction *_action;
    bool _isTight;

public slots:
    void _onActionChanged();

};


class CommandToolTipFilter : public ToolTipFilter{
    Q_OBJECT
public:
    CommandToolTipFilter(QWidget *parent, int showDelay, ToolTipPosition position);
    bool _canShowToolTip() override;
};


class MoreActionsButton : public CommandButton{
    Q_OBJECT
public:
    MoreActionsButton(QWidget *parent) : CommandButton(parent){
        this->_postInit();
    };
    MoreActionsButton(FluentIcon *icon, QWidget *parent) : CommandButton(icon, parent){
        this->_postInit();
    };
    MoreActionsButton(QIcon *icon, QWidget *parent) : CommandButton(icon, parent){
        this->_postInit();
    };
    MoreActionsButton(QString icon, QWidget *parent) : CommandButton(icon, parent){
        this->_postInit();
    };

    void _postInit();
    QSize sizeHint() const override;
    void clearState();
};


class CommandSeparator : public QWidget{
    Q_OBJECT
public:
    CommandSeparator(QWidget *parent);
    void paintEvent(QPaintEvent *e) override;
};


class CommandMenu : public RoundMenu{
    Q_OBJECT
public:
    CommandMenu(QWidget *parent);

};

class CommandBar : public QFrame{
    Q_OBJECT
public:
    CommandBar(QWidget *parent);
    void setSpaing(int spacing);
    int spacing();
    CommandButton* addAction(QAction *action);
    void addActions(QList<QAction*> actions);
    void addHiddenAction(QAction *action);
    void addHiddenActions(QList<QAction*> actions);
    CommandButton* insertAction(QAction *before, QAction *action);
    void addSeparator();
    void insertSeparator(int index);
    void addWidget(QWidget *widget);
    void removeAction(QAction *action);
    void removeWidget(QWidget *widget);
    void removeHiddenAction(QAction *action);
    void setToolButtonStyle(Qt::ToolButtonStyle style);
    Qt::ToolButtonStyle toolButtonStyle();
    void setButtonTight(bool isThight);
    bool isButtonTight();
    void setIconSize(QSize size);
    QSize iconSize();
    void resizeEvent(QResizeEvent *event) override;
    CommandButton* _createButton(QAction *action);
    void _insertWidgetToLayout(int index, QWidget *widget);
    QSize minimumSizeHint();
    void updateGeometry();
    QList<QWidget*> _visibleWidgets();
    int suitableWidth();
    void resizeToSuitableWidth();
    void setFont(QFont font);
    QList<CommandButton*> commandButtons();
    virtual void setMenuDropDown(bool down);
    virtual bool isMenuDropDown();
    

    QList<QWidget*> _widgets;
    QList<QWidget*> _hiddenWidgets;
    QList<QAction*> _hiddenActions;

    MenuAnimationType _menuAnimation;
    Qt::ToolButtonStyle _toolButtonStyle;
    QSize _iconSize;
    bool _isButtonTight;
    int _spacing;
    MoreActionsButton *moreButton;

public slots:
    virtual void _showMoreActionsMenu();
};


class CommandViewMenu : public CommandMenu{
    Q_OBJECT
public:
    CommandViewMenu(QWidget *parent);
    void setDropDown(bool down, bool _long);
};

class CommandBarView;
class CommandViewBar : public CommandBar{
    Q_OBJECT
public:
    CommandViewBar(QWidget *parent);
    void setMenuDropDown(bool down) override;
    bool isMenuDropDown() override;


public slots:
    void _showMoreActionsMenu() override;
};


class CommandBarView : public FlyoutViewBase{
    Q_OBJECT
public:
    CommandBarView(QWidget *parent);
    void setMenuVisible(bool isVisible);
    void addWidget(QWidget *widget);
    void setSpaing(int spacing);
    int spacing();
    CommandButton *addAction(QAction *action);
    void addActions(QList<QAction*> actions);
    void addHiddenAction(QAction *action);
    void addHiddenActions(QList<QAction*> actions);
    CommandButton *insertAction(QAction *before, QAction *action);
    void addSeparator();
    void insertSeparator(int index);
    void removeAction(QAction *action);
    void removeWidget(QWidget *widget);
    void removeHiddenAction(QAction *action);
    void setToolButtonStyle(Qt::ToolButtonStyle style);
    Qt::ToolButtonStyle toolButtonStyle();
    void setButtonTight(bool isThight);
    bool isButtonTight();
    void setIconSize(QSize size);
    QSize iconSize();
    void setFont(QFont font);
    virtual void setMenuDropDown(bool down);
    int suitableWidth();
    void resizeToSuitableWidth();
    QList<QAction *> actions();
    void paintEvent(QPaintEvent *e) override;

    CommandViewBar *bar;
    QHBoxLayout *hBoxLayout;
    bool _isMenuVisible;
};