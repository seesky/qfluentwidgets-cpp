#pragma once
#include "../../common/icon.h"
#include <QtWidgets/QPushButton>
#include <QVariant>

class PushButton : public QPushButton{
    Q_OBJECT
public:
    PushButton(){};
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
    PrimaryPushButton(){};
    PrimaryPushButton(QString text, QWidget *parent, QVariant *icon);
    PrimaryPushButton(FluentIcon *icon, QString text, QWidget *parent);
    void _drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state) override;
};

class TransparentPushButton : public PushButton{
    Q_OBJECT
public:
    TransparentPushButton(){};
    TransparentPushButton(QString text, QWidget *parent, QVariant *icon) : PushButton(text, parent, icon) {};
    TransparentPushButton(FluentIcon *icon, QString text, QWidget *parent) : PushButton(icon, text, parent){};
};

class ToggleButton : public PushButton{
    Q_OBJECT
public:
    ToggleButton(){};
    ToggleButton(QString text, QWidget *parent, QVariant *icon) : PushButton(text, parent, icon){};
    ToggleButton(FluentIcon *icon, QString text, QWidget *parent) : PushButton(icon, text, parent){};
    void _postInit() override;
    void _drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state) override;
};