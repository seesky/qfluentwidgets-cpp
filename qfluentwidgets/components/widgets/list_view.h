#pragma once

#include <QtCore/Qt>
#include <QtCore/QModelIndex>
#include <QtCore/QItemSelectionModel>
#include <QtGui/QPainter>
#include <QtWidgets/QStyleOptionViewItem>
#include <QtWidgets/QListView>
#include <QtWidgets/QListWidgetItem>
#include <QtWidgets/QListView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QWidget>

#include "scroll_bar.h"
#include "table_view.h"
#include "../../common/style_sheet.h"

class ListItemDelegate : public QStyledItemDelegate{
    Q_OBJECT
public:
    ListItemDelegate(QListView *parent);
    void setHoverRow(int row);
    void setPressedRow(int row);
    void setSelectedRows(QList<QModelIndex> indexes);
    QSize sizeHint(QStyleOptionViewItem *option, QModelIndex *index);
    QWidget *createEditor(QWidget *parent, QStyleOptionViewItem *option, QModelIndex *index);
    void updateEditorGeometry(QWidget *editor, QStyleOptionViewItem *option, QModelIndex *index);
    virtual void _drawbackground(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual void _drawIndicator(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const override;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    int margin;
    int hoverRow;
    int pressedRow;
    QList<int> selectedRows;
};


class ListWidget : public QListWidget{
    Q_OBJECT
    Q_PROPERTY(bool selectRightClickedRow READ isSelectRightClickedRow WRITE setSelectRightClickedRow)
public:
    ListWidget(QWidget *parent);
    void _setHoverRow(int row);
    void _setPressedRow(int row);
    void _setSelectedRows(QList<QModelIndex> indexes);
    void leaveEvent(QEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void keyPressEvent(QKeyEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void setItemDelegate(ListItemDelegate *delegate);
    void clearSelection();
    void setCurrentIndex(QModelIndex index);
    void updateSelectedRows();
    void setCurrentItem(QListWidgetItem *item, QItemSelectionModel::SelectionFlag command);
    void setCurrentItem(QListWidgetItem *item, QItemSelectionModel::SelectionFlags command);
    void setCurrentRow(int row, QItemSelectionModel::SelectionFlag command);
    void setCurrentRow(int row, QItemSelectionModel::SelectionFlags command);
    bool isSelectRightClickedRow();
    void setSelectRightClickedRow(bool isSelect);

    ListItemDelegate *delegate;
    SmoothScrollDelegate *scrollDelegate;
    bool _isSelectRightClickedRow;
};


class ListView : public QListView{
    Q_OBJECT
    Q_PROPERTY(bool selectRightClickedRow READ isSelectRightClickedRow WRITE setSelectRightClickedRow)
public:
    ListView(QWidget *parent);
    void _setHoverRow(int row);
    void _setPressedRow(int row);
    void _setSelectedRows(QList<QModelIndex> indexes);
    void leaveEvent(QEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void keyPressEvent(QKeyEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void setItemDelegate(ListItemDelegate *delegate);
    void clearSelection();
    void setCurrentIndex(QModelIndex index);
    void updateSelectedRows();
    bool isSelectRightClickedRow();
    void setSelectRightClickedRow(bool isSelect);

    ListItemDelegate *delegate;
    SmoothScrollDelegate *scrollDelegate;
    bool _isSelectRightClickedRow;
};