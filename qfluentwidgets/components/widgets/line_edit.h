#pragma once

#include <QtCore/QSize>
#include <QtCore/Qt>
#include <QtCore/QRectF>
#include <QtCore/QPoint>
#include <QtCore/QTimer>
#include <QEvent>
#include <QAbstractItemModel>
#include <QtGui/QPainter>
#include <QtGui/QPainterPath>
#include <QtGui/QIcon>
#include <QtGui/QCursor>
#include <QCompleter>
#include "../../common/style_sheet.h"
#include "../../common/icon.h"
#include "../../common/font.h"
#include "menu.h"
#include "scroll_bar.h"


class CompleterMenu;
class LineEditButton : public QToolButton{
    Q_OBJECT
public:
    LineEditButton(QVariant *icon, QWidget *parent);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);

    QVariant *_icon;
    bool isPressed;
    CompleterMenu *_completerMenu;
};


class LineEdit : public QLineEdit{
    Q_OBJECT
public:
    LineEdit(QWidget *parent);
    void setClearButtonEnabled(bool enable);
    bool isClearButtonEnabled();
    virtual void setCompleter(QCompleter *completer);
    QCompleter *completer();
    void focusOutEvent(QFocusEvent *e);
    void focusInEvent(QFocusEvent *e);
    void setCompleterMenu(CompleterMenu *menu);
    void _showCompleterMenu();
    void contextMenuEvent(QContextMenuEvent *e) override;
    void paintEvent(QPaintEvent *e);

    bool _isClearButtonEnabled;
    CompleterMenu *_completerMenu;
    QCompleter *_completer;
    QHBoxLayout *hBoxLayout;
    LineEditButton *clearButton;
public slots:
    void __onTextChanged(QString text);
    void __onTextEdited(QString text);
};


class CompleterMenu : public RoundMenu{
    Q_OBJECT
public:
    CompleterMenu(LineEdit *lineEdit);
    bool setCompletion(QAbstractItemModel *model);
    void setItems(QStringList *items);
    void _onItemClicked(QListWidgetItem *item);
    bool eventFilter(QObject *watched, QEvent *event);
    void __onItemSelected(QString text);
    bool popup();

    QStringList *items;
    LineEdit *lineEdit;
signals:
    void activated(const QString &text);
};

class SearchLineEdit : public LineEdit{
    Q_OBJECT
public:
    SearchLineEdit(QWidget *parent);
    void search();
    void setClearButtonEnabled(bool enable);

    LineEditButton *searchButton;
signals:
    void searchSignal(QString);
    void clearSignal();
};


class EditLayer : public QWidget{
    Q_OBJECT
public:
    EditLayer(QWidget *parent);
    bool eventFilter(QObject *watched, QEvent *event);
    void paintEvent(QPaintEvent *event);

};

class TextEdit : public QTextEdit{
    Q_OBJECT
public:
    TextEdit(QWidget *parent);
    void contextMenuEvent(QContextMenuEvent *e);
    SmoothScrollDelegate *scrollDelegate;
    EditLayer *layer;
};


class PlainTextEdit : public QPlainTextEdit{
    Q_OBJECT
public:
    PlainTextEdit(QWidget *parent);
    void contextMenuEvent(QContextMenuEvent *e);
    SmoothScrollDelegate *scrollDelegate;
    EditLayer *layer;
};


class PasswordLineEdit : public LineEdit{
    Q_OBJECT
public:
    PasswordLineEdit(QWidget *parent);
    void setPasswordVisible(bool isVisible);
    bool isPasswordVisible();
    void setClearButtonEnabled(bool enable);
    void setViewPasswordButtonVisible(bool isVisible);
    bool eventFilter(QObject *watched, QEvent *event);

    LineEditButton *viewButton;
};