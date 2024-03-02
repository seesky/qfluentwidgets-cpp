#pragma once

#include <QtCore/Qt>
#include <QtCore/QRect>
#include <QtCore/QRectF>
#include <QtCore/QSize>
#include <QtGui/QPainter>
#include <QtGui/QColor>
#include <QtGui/QPainterPath>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidgetItem>
#include <QtWidgets/QListWidget>

#include "../widgets/menu.h"
#include "../widgets/line_edit.h"
#include "../widgets/arcylic_label.h"
#include "../../common/style_sheet.h"

class AcrylicMenuActionListWidget : public MenuActionListWidget{
    Q_OBJECT
public:
    AcrylicMenuActionListWidget(QWidget *parent);
    void _updateAcrylicColor();
    int _topMargin();
    int _bottomMargin();
    void setItemHeight(int height);
    void addItem(QListWidgetItem *item);
    QListWidgetItem *createPlaceholderItem(int height);
    virtual QPainterPath clipPath();
    void paintEvent(QPaintEvent *event) override;

    AcrylicBrush *acrylicBrush;
};


class AcrylicMenu : public RoundMenu{
    Q_OBJECT
public:
    AcrylicMenu(QString title, QWidget *parent);
    void setUpMenu(AcrylicMenuActionListWidget *view);
    void exec(QPoint *pos, bool ani, MenuAnimationType aniType) override;
};


class AcrylicCompleterMenuActionListWidget : public AcrylicMenuActionListWidget{
    Q_OBJECT
public:
    AcrylicCompleterMenuActionListWidget(QWidget *parent) : AcrylicMenuActionListWidget(parent){};
    QPainterPath clipPath() override;
};


class AcrylicCompleterMenu : public CompleterMenu{
    Q_OBJECT
public:
    AcrylicCompleterMenu(LineEdit *lineEdit);
    void setItems(QStringList *items);
    void setUpMenu(AcrylicCompleterMenuActionListWidget *view);
    void exec(QPoint *pos, bool ani, MenuAnimationType aniType) override;
};


class AcrylicLineEditMenu : public LineEditMenu{
    Q_OBJECT
public:
    AcrylicLineEditMenu(QLineEdit *parent);
    void setUpMenu(AcrylicMenuActionListWidget *view);
    void exec(QPoint *pos, bool ani, MenuAnimationType aniType) override;
};


class AcrylicCheckableMenu : public CheckableMenu{
    Q_OBJECT
public:
    AcrylicCheckableMenu(QString title, QWidget *parent, MenuIndicatorType indicatorType);
    void setUpMenu(AcrylicMenuActionListWidget *view);
    void exec(QPoint *pos, bool ani, MenuAnimationType aniType) override;
};


class AcrylicSystemTrayMenu : public AcrylicMenu{
    Q_OBJECT
public:
    void showEvent(QShowEvent *event);
};

class AcrylicCheckableSystemTrayMenu : public AcrylicCheckableMenu{
    Q_OBJECT
public:
    void showEvent(QShowEvent *event);
};