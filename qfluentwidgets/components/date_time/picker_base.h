#pragma once

#include <QtCore/Qt>
#include <QtCore/QSize>
#include <QtCore/QRectF>
#include <QtCore/QPoint>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QEasingCurve>
#include <QtCore/QObject>
#include <QtGui/QColor>
#include <QtGui/QPainter>
#include <QtGui/QCursor>
#include <QtGui/QRegion>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QtWidgets/QSizePolicy>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QListWidgetItem>

#include "../widgets/cycle_list_widget.h"
#include "../widgets/button.h"
#include "../../common/icon.h"
#include "../../common/style_sheet.h"

class SeparatorWidget : public QWidget{
    Q_OBJECT
public:
    SeparatorWidget(Qt::Orientation orient, QWidget *parent);
};


class ItemMaskWidget : public QWidget{
    Q_OBJECT
public:
    ItemMaskWidget(QList<CycleListWidget *> *listWidgets, QWidget *parent);
    void paintEvent(QPaintEvent *event) override;
    void _drawText(QListWidgetItem *item, QPainter *painter, int y);

    QList<CycleListWidget *> *listWidgets;
};


class PickerColumnFormatter : public QObject{
    Q_OBJECT
public:
    PickerColumnFormatter() : QObject(){};
    virtual QString encode(QVariant value);
    virtual QVariant decode(QString value);
};


class DigitFormatter : public PickerColumnFormatter{
    Q_OBJECT
public:
    QVariant decode(QString value) override;
};


class PickerColumnButton : public QPushButton{
    Q_OBJECT
    //Q_PROPERTY(bool hasBorder READ getHasBorder WRITE setHasBorder)
    //Q_PROPERTY(QString __align READ getAlign WRITE setAlign)
public:
    PickerColumnButton(QString name, QList<QString> *items, int width, Qt::AlignmentFlag align, PickerColumnFormatter *formatter, QWidget *parent);
    Qt::AlignmentFlag align();
    void setAlignment(Qt::AlignmentFlag align);
    QString value();
    void setValue(QString v);
    QList<QVariant> *items();
    void setItems(QList<QString> *items);
    PickerColumnFormatter* formatter();
    void setFormatter(PickerColumnFormatter *formatter);
    QString name();
    void setName(QString name);
    //bool getHasBorder();
    //void setHasBorder();
    //QString getAlign();
    //void setAlign(QString align);

    QString _name;
    QString _value;
    Qt::AlignmentFlag _align;
    bool hasBorder;
    QList<QString> *_items;
    PickerColumnFormatter *_formatter;
};


class PickerPanel;
class PickerBase : public QPushButton{
    Q_OBJECT
public:
    PickerBase(QWidget *parent);
    void addColumn(QString name, QList<QString> *items, int width, Qt::AlignmentFlag align, PickerColumnFormatter *formatter);
    void setColumnAlignment(PickerBase *picker, int index, Qt::AlignmentFlag align);
    void setColumnWidth(PickerBase *picker, int index, int width);
    void setColumnTight(PickerBase *picker, int index);
    void setColumnVisible(PickerBase *picker, int index, bool isVisible);
    QList<QString> *value();
    QList<QString> *initialValue();
    void setColumnValue(PickerBase *picker, int index, QString value);
    void setColumnInitialValue(PickerBase *picker, int index, QString value);
    void setColumnFormatter(PickerBase *picker, int index, PickerColumnFormatter *formatter);
    void setColumnItems(PickerBase *picker, int index, QList<QString> *items);
    QString encodeValue(PickerBase *picker, int index, QString value);
    QVariant decodeValue(PickerBase *picker, int index, QString value);
    void setColumn(PickerBase *picker, int index, QString name, QList<QString> items, int width, Qt::AlignmentFlag align);
    void clearColumns();
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void _setButtonProperty(const char *name, bool value);
    virtual QList<QString> * panelInitialValue();

    virtual void _onConfirmed(QList<QString> *value);
    

    QList<PickerColumnButton *> *columns;
    QHBoxLayout *hBoxLayout;

public slots:
    void _showPanel();
    void _onColumnValueChanged(PickerPanel *panel, int index, QString value);
    //void _onColumnValueChanged(int index, const QString &value);
};


class PickerToolButton : public TransparentToolButton{
    Q_OBJECT
public:
    PickerToolButton(FluentIcon *icon, QWidget *parent) : TransparentToolButton(icon, parent){};
    PickerToolButton(QIcon *icon, QWidget *parent) : TransparentToolButton(icon, parent){};
    PickerToolButton(QString icon, QWidget *parent) : TransparentToolButton(icon, parent){};
    void _drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state) override;
};

class PickerPanel : public QWidget{
    Q_OBJECT
public:
    PickerPanel(QWidget *parent);
    void __initWidget();
    void setShadowEffect(int blurRadius, std::tuple<int,int> offset, QColor color);
    void addColumn(QList<QVariant> *items, int width, Qt::AlignmentFlag align);
    void resizeEvent(QResizeEvent *event);
    QList<QString> *value();
    void setValue(QList<QString> *list);
    QString columnValue(int index);
    void setColumnValue(int index, QString value);
    CycleListWidget *column(int index);
    void exec(QPoint pos, bool ani);


    int itemHeight;
    QList<CycleListWidget *> *listWidgets;
    QFrame *view;
    ItemMaskWidget *itemMaskWidget;
    SeparatorWidget *hSeparatorWidget;
    PickerToolButton *yesButton;
    PickerToolButton *cancelButton;
    QHBoxLayout *hBoxLayout;
    QHBoxLayout *listLayout;
    QHBoxLayout *buttonLayout;
    QVBoxLayout *vBoxLayout;
    QGraphicsDropShadowEffect *shadowEffect;
    bool isExpanded;
    QPropertyAnimation *ani;
signals:
    void confirmed(QList<QString> *);
    void columnValueChanged(int, QString);

public slots:
    void _onAniValueChanged(QVariant opacity);
    void _fadeOut();
};