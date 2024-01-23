#pragma once

#include <QtCore/Qt>
#include <QtCore/QRectF>
#include <QtCore/QPoint>
#include <QtCore/QObject>
#include <QtCore/QEvent>
#include <QtGui/QPainter>
#include <QtGui/QCursor>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QApplication>

#include "menu.h"
#include "line_edit.h"
#include "../../common/animation.h"
#include "../../common/icon.h"
#include "../../common/font.h"
#include "../../common/style_sheet.h"

class ComboItem{
public:
    ComboItem(QString text, QVariant *icon, QVariant *userData);
    QIcon getIcon();
    void setIcon();

    QString text;
    QVariant *userData;
    QVariant *_icon;
};

class ComboBoxMenu;
class ComboBox : public QPushButton{
    Q_OBJECT
public:
    ComboBox(QWidget *parent);
    bool eventFilter(QObject *watched, QEvent *event);
    void addItem(QString text, QVariant *icon, QVariant *userData);
    void addItems(QList<QString> texts);
    void removeItem(int index);
    int currentIndex();
    void setCurrentIndex(int index);
    void setText(QString text);
    QString currentText();
    QVariant *currentData();
    void setCurrentText(QString text);
    void setItemText(int index, QString text);
    QVariant *itemData(int index);
    QString itemText(int index);
    QVariant *itemIcon(int index);
    void setItemData(int index, QVariant *value);
    void setItemIcon(int index, QVariant *icon);
    int findData(QVariant *data);
    int findText(QString text);
    void clear();
    int count();
    void insertItem(int index, QString text, QVariant *icon, QVariant *userData);
    void insertItems(int index, QList<QString> texts);
    void setMaxVisibleItems(int num);
    int maxVisibleItems();
    void _closeComboMenu();
    ComboBoxMenu *_createComboMenu();
    void _showComboMenu();
    void _toggleComboMenu();
    void setPlaceholderText(QString text);
    void _updateTextState(bool isPlaceholder);
    void mouseReleaseEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);

    bool isHover;
    bool isPressed;
    QList<ComboItem *> *items;
    int _currentIndex;
    int _maxVisibleItems;
    ComboBoxMenu *dropMenu;
    QString _placeholderText;
    TranslateYAnimation *arrowAni;
signals:
    void currentIndexChanged(int);
    void currentTextChanged(QString);

public slots:
    void _onItemClicked(int index);
    void _onDropMenuClosed();
};


class EditableComboBox : public LineEdit{
    Q_OBJECT
public:
    EditableComboBox(QWidget *parent);
    bool eventFilter(QObject *watched, QEvent *event);
    void addItem(QString text, QVariant *icon, QVariant *userData);
    void addItems(QList<QString> texts);
    void removeItem(int index);
    int currentIndex();
    void setCurrentIndex(int index);
    void setText(QString text);
    QString currentText();
    QVariant *currentData();
    void setCurrentText(QString text);
    void setItemText(int index, QString text);
    QVariant *itemData(int index);
    QString itemText(int index);
    QVariant *itemIcon(int index);
    void setItemData(int index, QVariant *value);
    void setItemIcon(int index, QVariant *icon);
    int findData(QVariant *data);
    int findText(QString text);
    void clear();
    int count();
    void insertItem(int index, QString text, QVariant *icon, QVariant *userData);
    void insertItems(int index, QList<QString> texts);
    void setMaxVisibleItems(int num);
    int maxVisibleItems();
    void _closeComboMenu();
    ComboBoxMenu *_createComboMenu();
    void _showComboMenu();
    void _toggleComboMenu();
    void setCompleterMenu(CompleterMenu *menu);
    void setPlaceholderText(QString text);
    void _onTextEdited(QString text);

    bool isHover;
    bool isPressed;
    QList<ComboItem *> *items;
    int _currentIndex;
    int _maxVisibleItems;
    ComboBoxMenu *dropMenu;
    QString _placeholderText;
    LineEditButton *dropButton;
signals:
    void currentIndexChanged(int);
    void currentTextChanged(QString);

public slots:
    void _onItemClicked(int index);
    void _onDropMenuClosed();
    void _onReturnPressed();
    void _onClearButtonClicked();
    void __onActivated(QString text);
};


class ComboBoxMenu : public RoundMenu{
    Q_OBJECT
public:
    ComboBoxMenu(QWidget *parent);
    void exec(QPoint *pos, bool ani, MenuAnimationType aniType);
};