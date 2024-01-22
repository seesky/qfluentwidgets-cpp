#pragma once
#include "../../common/icon.h"
#include "../../common/animation.h"
#include "menu.h"
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QRadioButton>
#include <QVariant>

class PushButton : public QPushButton{
    Q_OBJECT
public:
    PushButton(){};
    PushButton(QWidget *parent);
    void initialize(QWidget *parent);
    PushButton(QString text, QWidget *parent, QVariant *icon);
    PushButton(QIcon *icon, QString text, QWidget *parent);
    PushButton(FluentIcon *icon, QString text, QWidget *parent);
    void setIcon(QVariant *icon);
    bool setProperty(QString name, QVariant *value);
    virtual void _postInit(){};
    QIcon icon();

    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    virtual void _drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state);

    bool isPressed;
    bool isHover;
    QVariant *_icon;
};

Q_DECLARE_METATYPE(QIcon *)

class PrimaryPushButton : public PushButton{
    Q_OBJECT
public:
    //PrimaryPushButton(){};
    PrimaryPushButton(QWidget *parent) : PushButton(parent){};
    PrimaryPushButton(QString text, QWidget *parent, QVariant *icon);
    PrimaryPushButton(FluentIcon *icon, QString text, QWidget *parent);
    void _postInit() override {};
    void _drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state) override;
};

class TransparentPushButton : public PushButton{
    Q_OBJECT
public:
    TransparentPushButton(){};
    TransparentPushButton(QString text, QWidget *parent, QVariant *icon) : PushButton(text, parent, icon) {};
    TransparentPushButton(FluentIcon *icon, QString text, QWidget *parent) : PushButton(icon, text, parent){};
    void _postInit() override {};
};

class ToggleButton : public PushButton{
    Q_OBJECT
public:
    ToggleButton(){};
    ToggleButton(QString text, QWidget *parent, QVariant *icon) : PushButton(text, parent, icon){
        this->_postInit();
    };
    ToggleButton(FluentIcon *icon, QString text, QWidget *parent) : PushButton(icon, text, parent){
        this->_postInit();
    };
    void _postInit() override;
    void _drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state) override;
};

class TransparentTogglePushButton : public ToggleButton{
    Q_OBJECT
public:
    TransparentTogglePushButton(){};
    TransparentTogglePushButton(QString text, QWidget *parent, QVariant *icon) : ToggleButton(text, parent, icon){};
    TransparentTogglePushButton(FluentIcon *icon, QString text, QWidget *parent) : ToggleButton(icon, text, parent){};
};

class HyperlinkButton : public PushButton{
    Q_OBJECT
public:
    void initialize(QWidget *parent);
    HyperlinkButton(QVariant *url, QString text, QWidget *parent, QVariant *icon);
    HyperlinkButton(QIcon *icon, QVariant *url, QString text, QWidget *parent);
    HyperlinkButton(FluentIcon *icon, QVariant *url, QString text, QWidget *parent);
    QUrl *getUrl();
    void setUrl(QVariant *url);
    void _onClicked();
    void _drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state) override;
    QUrl *_url;
private:
};


class RadioButton : public QRadioButton{
    Q_OBJECT
public:
    void initialize(QWidget *parent);
    RadioButton(QString text, QWidget *parent);
private:
};


class ToolButton : public QToolButton{
    Q_OBJECT
public:
    void initialize(QWidget *parent);
    ToolButton(QWidget *parent);
    ToolButton(FluentIcon *icon, QWidget *parent);
    ToolButton(QIcon *icon, QWidget *parent);
    ToolButton(QString icon, QWidget *parent);
    virtual void _postInit();
    void setIcon(QVariant *icon);
    QIcon icon();
    bool setProperty(QString name, QVariant *value);
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    virtual void _drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state);

    bool isPressed;
    bool isHover;
    QVariant *_icon;
private:
};


class TransparentToolButton : public ToolButton{
    Q_OBJECT
public:
    TransparentToolButton(FluentIcon *icon, QWidget *parent);
    TransparentToolButton(QIcon *icon, QWidget *parent);
    TransparentToolButton(QString icon, QWidget *parent);
private:
};


class PrimaryToolButton : public ToolButton{
    Q_OBJECT
public:
    PrimaryToolButton(QWidget *parent) : ToolButton(parent){};
    PrimaryToolButton(FluentIcon *icon, QWidget *parent);
    PrimaryToolButton(QIcon *icon, QWidget *parent);
    PrimaryToolButton(QString icon, QWidget *parent);
    void _postInit() override {};
    void _drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state) override;
};

class ToggleToolButton : public ToolButton{
    Q_OBJECT
public:
    ToggleToolButton(FluentIcon *icon, QWidget *parent);
    ToggleToolButton(QIcon *icon, QWidget *parent);
    ToggleToolButton(QString icon, QWidget *parent);
    void _postInit() override;
    void _drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state) override;
private:
};

class TransparentToggleToolButton : public ToggleToolButton{
    Q_OBJECT
public:
    TransparentToggleToolButton(FluentIcon *icon, QWidget *parent) : ToggleToolButton(icon, parent){};
    TransparentToggleToolButton(QIcon *icon, QWidget *parent) : ToggleToolButton(icon, parent){};
    TransparentToggleToolButton(QString icon, QWidget *parent) : ToggleToolButton(icon, parent){};
};


class DropDownButtonBase{
public:
    DropDownButtonBase();
    void setMenu(RoundMenu *menu);
    RoundMenu *menu();
    void _showMenu();
    void _hideMenu();
    void _drawDropDownIcon(QPainter *painter, QRect rect);
    void paintEvent(QPaintEvent *event);

    RoundMenu *_menu;
    TranslateYAnimation *arrowAni;
    bool isHover;
    bool isPressed;
private:
};


class DropDownPushButton : public PushButton{
    Q_OBJECT
public:
    DropDownPushButton(QString text, QWidget *parent, QVariant *icon) : PushButton(text, parent, icon){
        this->_menu = nullptr;
        this->arrowAni = new TranslateYAnimation(this, 2);
    };
    DropDownPushButton(FluentIcon *icon, QString text, QWidget *parent) : PushButton(icon, text, parent){
        this->_menu = nullptr;
        this->arrowAni = new TranslateYAnimation(this, 2);
    };
    void mouseReleaseEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *event);

    void setMenu(RoundMenu *menu);
    RoundMenu *menu();
    void _showMenu();
    void _hideMenu();
    void _drawDropDownIcon(QPainter *painter, QRect rect);

    RoundMenu *_menu;
    TranslateYAnimation *arrowAni;
    bool isHover;
    bool isPressed;
private:
};


class TransparentDropDownPushButton : public DropDownPushButton{
    Q_OBJECT
public:
    TransparentDropDownPushButton(QString text, QWidget *parent, QVariant *icon) : DropDownPushButton(text, parent, icon){};
    TransparentDropDownPushButton(FluentIcon *icon, QString text, QWidget *parent) : DropDownPushButton(icon, text, parent){};
private:
};


class DropDownToolButton : public ToolButton{
    Q_OBJECT
public:
    DropDownToolButton(FluentIcon *icon, QWidget *parent): ToolButton(icon, parent){
        this->_menu = nullptr;
        this->arrowAni = new TranslateYAnimation(this, 2);
    };
    void mouseReleaseEvent(QMouseEvent *e) override;
    void _drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state) override;
    void paintEvent(QPaintEvent *event) override;

    void setMenu(RoundMenu *menu);
    RoundMenu *menu();
    void _showMenu();
    void _hideMenu();
    void _drawDropDownIcon(QPainter *painter, QRect rect);

    RoundMenu *_menu;
    TranslateYAnimation *arrowAni;
    bool isHover;
    bool isPressed;
private:
};


class TransparentDropDownToolButton : public DropDownToolButton{
    Q_OBJECT
public:
    TransparentDropDownToolButton(FluentIcon *icon, QWidget *parent): DropDownToolButton(icon, parent){};
};


class PrimaryDropDownPushButton : public PrimaryPushButton{
    Q_OBJECT
public:
    PrimaryDropDownPushButton(QString text, QWidget *parent, QVariant *icon) : PrimaryPushButton(text, parent, icon){
        this->_menu = nullptr;
        this->arrowAni = new TranslateYAnimation(this, 2);
    };
    PrimaryDropDownPushButton(FluentIcon *icon, QString text, QWidget *parent) : PrimaryPushButton(icon, text, parent){
        this->_menu = nullptr;
        this->arrowAni = new TranslateYAnimation(this, 2);
    };
    void mouseReleaseEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *event);

    void setMenu(RoundMenu *menu);
    RoundMenu *menu();
    void _showMenu();
    void _hideMenu();
    void _drawDropDownIcon(QPainter *painter, QRect rect);

    RoundMenu *_menu;
    TranslateYAnimation *arrowAni;
    bool isHover;
    bool isPressed;
};


class PrimaryDropDownToolButton : public PrimaryToolButton{
    Q_OBJECT
public:
    PrimaryDropDownToolButton(QWidget *parent) : PrimaryToolButton(parent){};
    PrimaryDropDownToolButton(FluentIcon *icon, QWidget *parent): PrimaryToolButton(icon, parent){
        this->_menu = nullptr;
        this->arrowAni = new TranslateYAnimation(this, 2);
    };
    void mouseReleaseEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *event);

    void setMenu(RoundMenu *menu);
    RoundMenu *menu();
    void _showMenu();
    void _hideMenu();
    void _drawDropDownIcon(QPainter *painter, QRect rect);
    void _drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state) override;

    RoundMenu *_menu;
    TranslateYAnimation *arrowAni;
    bool isHover;
    bool isPressed;
};

class SplitDropButton : public ToolButton{
    Q_OBJECT
public:
    SplitDropButton(QWidget *parent) : ToolButton(parent){
        this->_postInit();
    };
    SplitDropButton(FluentIcon *icon, QWidget *parent) : ToolButton(icon, parent){
        this->_postInit();
    };
    SplitDropButton(QIcon *icon, QWidget *parent) : ToolButton(icon, parent){
        this->_postInit();
    };
    SplitDropButton(QString icon, QWidget *parent) : ToolButton(icon, parent){
        this->_postInit();
    };
    void _drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state) override;
    void _postInit() override;

    TranslateYAnimation *arrowAni;
};


class PrimarySplitDropButton : public PrimaryToolButton{
    Q_OBJECT
public:
    PrimarySplitDropButton(QWidget *parent) : PrimaryToolButton(parent){
        //this->_postInit();
        this->_menu = nullptr;
        this->arrowAni = new TranslateYAnimation(this, 2);
    };
    PrimarySplitDropButton(FluentIcon *icon, QWidget *parent): PrimaryToolButton(icon, parent){
        this->_menu = nullptr;
        this->arrowAni = new TranslateYAnimation(this, 2);
    };
    void mouseReleaseEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *event);

    void setMenu(RoundMenu *menu);
    RoundMenu *menu();
    void _showMenu();
    void _hideMenu();
    void _drawDropDownIcon(QPainter *painter, QRect rect);
    void _drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state) override;
    void _postInit() override;

    RoundMenu *_menu;
    TranslateYAnimation *arrowAni;
};


class SplitWidgetBase : public QWidget{
    Q_OBJECT
public:
    SplitWidgetBase(){};
    SplitWidgetBase(QWidget *parent);
    void setWidget(QWidget *widget);
    void setDropButton(SplitDropButton *button);
    void setDropIcon(QVariant *icon);
    void setDropIconSize(QSize *size);
    void setFlyout(QWidget *flyout);
    

    SplitDropButton *dropButton;
    QHBoxLayout *hBoxLayout;
    QWidget *flyout;

signals:
    void dropDownClicked();

public slots:
    void showFlyout();
};


class SplitPushButton : public SplitWidgetBase{
    Q_OBJECT
public:
    SplitPushButton(){};
    SplitPushButton(QWidget *parent);
    SplitPushButton(QString text, QWidget *parent, QVariant *icon);
    SplitPushButton(QIcon *icon, QString text, QWidget *parent);
    SplitPushButton(FluentIcon *icon, QString text, QWidget *parent);

    void _postInit(){};
    QString text();
    void setText(QString text);
    QIcon *icon();
    void setIcon(QVariant *icon);
    void setIconSize(QSize *size);

    PushButton *button;
signals:
    void clicked();
};




class SplitWidgetBase2PrimaryButton : public QWidget{
    Q_OBJECT
public:
    SplitWidgetBase2PrimaryButton(){};
    SplitWidgetBase2PrimaryButton(QWidget *parent);
    void setWidget(QWidget *widget);
    void setDropButton(PrimarySplitDropButton *button);
    void setDropIcon(QVariant *icon);
    void setDropIconSize(QSize *size);
    void setFlyout(QWidget *flyout);
    
    PrimarySplitDropButton *dropButton;
    QHBoxLayout *hBoxLayout;
    QWidget *flyout;

signals:
    void dropDownClicked();

public slots:
    void showFlyout();
};



class PrimarySplitPushButton : public SplitWidgetBase2PrimaryButton{
    Q_OBJECT
public:
    //PrimarySplitPushButton(){};
    PrimarySplitPushButton(QWidget *parent);
    PrimarySplitPushButton(QString text, QWidget *parent, QVariant *icon);
    PrimarySplitPushButton(QIcon *icon, QString text, QWidget *parent);
    PrimarySplitPushButton(FluentIcon *icon, QString text, QWidget *parent);

    void _postInit(){};
    QString text();
    void setText(QString text);
    QIcon *icon();
    void setIcon(QVariant *icon);
    void setIconSize(QSize *size);

    PrimaryPushButton *button;
signals:
    void clicked();
};


class SplitToolButton : public SplitWidgetBase{
    Q_OBJECT
public:
    SplitToolButton(){};
    SplitToolButton(QWidget *parent);
    SplitToolButton(QWidget *parent, QVariant *icon);
    SplitToolButton(QIcon *icon, QWidget *parent);
    SplitToolButton(FluentIcon *icon, QWidget *parent);

    void _postInit(){};
    QString text();
    void setText(QString text);
    QIcon *icon();
    void setIcon(QVariant *icon);
    void setIconSize(QSize *size);

    ToolButton *button;
signals:
    void clicked();
};


class PrimarySplitToolButton : public SplitWidgetBase2PrimaryButton{
    Q_OBJECT
public:
    PrimarySplitToolButton(){};
    PrimarySplitToolButton(QWidget *parent);
    PrimarySplitToolButton(QWidget *parent, QVariant *icon);
    PrimarySplitToolButton(QIcon *icon, QWidget *parent);
    PrimarySplitToolButton(FluentIcon *icon, QWidget *parent);

    void _postInit(){};
    QString text();
    void setText(QString text);
    QIcon *icon();
    void setIcon(QVariant *icon);
    void setIconSize(QSize *size);

    PrimaryToolButton *button;
signals:
    void clicked();
};


class PillPushButton : public ToggleButton{
    Q_OBJECT
public:
    PillPushButton(){};
    PillPushButton(QString text, QWidget *parent, QVariant *icon) : ToggleButton(text, parent, icon){};
    PillPushButton(FluentIcon *icon, QString text, QWidget *parent) : ToggleButton(icon, text, parent){};

    void paintEvent(QPaintEvent *event) override;
};



class PillToolButton : public ToggleToolButton{
    Q_OBJECT
public:
    PillToolButton(FluentIcon *icon, QWidget *parent) : ToggleToolButton(icon, parent){};
    PillToolButton(QIcon *icon, QWidget *parent) : ToggleToolButton(icon, parent){};
    PillToolButton(QString icon, QWidget *parent) : ToggleToolButton(icon, parent){};

    void paintEvent(QPaintEvent *event) override;
};


