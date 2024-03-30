#pragma once

#include <QtCore/Qt>
#include <QtCore/QQueue>
#include <QtCore/QRect>
#include <QtCore/QRectF>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QMargins>
#include <QtCore/QEasingCurve>
#include <QtCore/QPoint>
#include <QtCore/QEvent>
#include <QtCore/QSize>
#include <QtGui/QColor>
#include <QtGui/QPainter>
#include <QtGui/QPen>
#include <QtGui/QIcon>
#include <QtGui/QCursor>
#include <QtGui/QFont>
#include <QtGui/QBrush>
#include <QtGui/QPixmap>
#include <QtGui/QImage>
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>

#include "../../common/config.h"
#include "../../common/style_sheet.h"
#include "../../common/icon.h"
#include "../../common/font.h"
#include "../../components/widgets/scroll_area.h"
#include "../../components/widgets/info_badge.h"
#include "../../components/widgets/flyout.h"

static int EXPAND_WIDTH = 312;

class NavigationWidget : public QWidget{
    Q_OBJECT
public:
    NavigationWidget(bool isSelectable, QWidget *parent);
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void click();
    virtual void setCompacted(bool isCompacted);



    bool isCompacted;
    bool isSelected;
    bool isPressed;
    bool isEnter;
    bool isSelectable;
    QWidget *treeParent;
    int nodeDepth;

signals:
    void clicked(bool);
    void selectedChanged(bool);

public slots:
    virtual void setSelected(bool isSelected);

};



class NavigationPushButton : public NavigationWidget{
    Q_OBJECT
public:
    NavigationPushButton(QVariant *icon, QString text, bool isSelectable, QWidget *parent);
    QString text();
    virtual void setText(QString text);
    QIcon icon();
    void setIcon(QVariant *icon);
    virtual QMargins _margins();
    virtual bool _canDrawIndicator();
    void paintEvent(QPaintEvent *event) override;

    QVariant *_icon;
    QString _text;
};


class NavigationToolButton : public NavigationPushButton{
    Q_OBJECT
public:
    NavigationToolButton(QVariant *icon, QWidget *parent);
    //void setText(QString text) override;
    void setCompacted(bool isCompacted);
};


class NavigationSeparator : public NavigationWidget{
    Q_OBJECT
public:
    NavigationSeparator(QWidget *parent);
    void setCompacted(bool isCompacted);
    void paintEvent(QPaintEvent *event) override;
};

class NavigationTreeWidget;
class NavigationTreeItem : public NavigationPushButton{
    Q_OBJECT
    Q_PROPERTY(float arrowAngle READ getArrowAngle WRITE setArrowAngle)
public:
    NavigationTreeItem(QVariant *icon, QString text, bool isSelectable, QWidget *parent);
    void setExpanded(bool isExpanded);
    void mouseReleaseEvent(QMouseEvent *event) override;
    bool _canDrawIndicator() override;
    QMargins _margins() override;
    void paintEvent(QPaintEvent *event) override;
    float getArrowAngle();
    void setArrowAngle(float angle);

    float _arrowAngle;
    QPropertyAnimation *rotateAni;
signals:
    void itemClicked(bool, bool);
};


class NavigationTreeWidgetBase : public NavigationWidget{
    Q_OBJECT
public:
    NavigationTreeWidgetBase(bool isSelectable, QWidget *parent): NavigationWidget(isSelectable, parent){};
    void addChild(NavigationWidget *child){};
    void insertChild(int index, NavigationWidget *child){};
    void removeChild(NavigationWidget *child){};
    bool isRoot(){
        return true;
    };
    virtual bool isLeaf(){
        return true;
    };
    virtual void setExpanded(bool isExpanded){};
    QList<NavigationWidget*> childItems(){

    };
};


class NavigationTreeWidget : public NavigationTreeWidgetBase{
    Q_OBJECT
public:
    NavigationTreeWidget(QVariant *icon, QString text, bool isSelectable, QWidget *parent);
    void __initWidget();
    void addChild(NavigationTreeWidgetBase *child);
    QString text();
    QIcon icon();
    void setText(QString text);
    void setIcon(QVariant *icon);
    void setFont(QFont font);
    NavigationTreeWidget *clone();
    int suitableWidth();
    void insertChild(int index, NavigationWidget *child);
    void removeChild(NavigationWidget *child);
    QList<NavigationTreeWidget*> childItems();
    void setExpanded(bool isExpanded, bool ani);
    bool isRoot();
    bool isLeaf();
    void mouseReleaseEvent(QMouseEvent *event);
    void setCompacted(bool isCompacted);

    QList<NavigationTreeWidget*> treeChildren;
    bool isExpanded;
    QVariant *_icon;
    NavigationTreeItem *itemWidget;
    QVBoxLayout *vBoxLayout;
    QPropertyAnimation *expandAni;

signals:
    void expanded();

public slots:
    void _onClicked(bool triggerByUser, bool clickArrow);
    void setSelected(bool isSelected) override;
};



class NavigationAvatarWidget : public NavigationWidget{
    Q_OBJECT
public:
    NavigationAvatarWidget(QString name, QVariant *avatar, QWidget *parent);
    void setName(QString name);
    void setAvatar(QVariant *avatar);
    void paintEvent(QPaintEvent *event) override;

    QString name;
    QImage avatar;
};



class NavigationFlyoutMenu : public ScrollArea{
    Q_OBJECT
public:
    NavigationFlyoutMenu(NavigationTreeWidget *tree, QWidget *parent);
    void _initNode(NavigationFlyoutMenu *root);

    int _suitableWidth();
    QList<NavigationTreeWidget *> *visibleTreeNodes();

    QWidget *view;
    NavigationTreeWidget *treeWidget;
    QList<NavigationTreeWidget*> treeChildren;
    QVBoxLayout *vBoxLayout;

signals:
    void expanded();

public slots:
    void _adjustViewSize(bool _emit);
};