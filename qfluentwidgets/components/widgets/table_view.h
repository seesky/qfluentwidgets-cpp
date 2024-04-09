#pragma once

#include <QtCore/Qt>
#include <QtCore/QMargins>
#include <QtCore/QModelIndex>
#include <QtCore/QItemSelectionModel>
#include <QtGui/QPainter>
#include <QtGui/QColor>
#include <QtGui/QKeyEvent>
#include <QtGui/QPalette>
#include <QtGui/QBrush>
#include <QtWidgets/QStyledItemDelegate>
#include <QtWidgets/QApplication>
#include <QtWidgets/QStyleOptionViewItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>
#include <QtWidgets/QTableWidgetItem>
#include <QtWidgets/QHeaderView>

#include "../../common/font.h"
#include "../../common/style_sheet.h"
#include "line_edit.h"
#include "scroll_bar.h"

class TableItemDelegate : public QStyledItemDelegate{
    Q_OBJECT
public:
    TableItemDelegate(QTableView *parent);
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


class TableWidget : public QTableWidget{
    Q_OBJECT
    Q_PROPERTY(bool selectRightClickedRow READ isSelectRightClickedRow WRITE setSelectRightClickedRow)
public:
    TableWidget(QWidget *parent);
    void showEvent(QShowEvent *event);
    void setBorderVisible(bool isVisible);
    void setBorderRadius(int radius);
    void _setHoverRow(int row);
    void _setPressedRow(int row);
    void _setSelectedRows(QList<QModelIndex> indexes);
    void leaveEvent(QEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void keyPressEvent(QKeyEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *event);
    void setItemDelegate(TableItemDelegate *delegate);
    void selectAll();
    void clearSelection();
    void setCurrentIndex(QModelIndex *index);
    void updateSelectedRows();

    void setCurrentCell(int row, int column, QItemSelectionModel::SelectionFlag command);
    void setCurrentCell(int row, int column, QItemSelectionModel::SelectionFlags command);
    void setCurrentItem(QTableWidgetItem *item, QItemSelectionModel::SelectionFlag command);
    void setCurrentItem(QTableWidgetItem *item, QItemSelectionModel::SelectionFlags command);
    bool isSelectRightClickedRow();
    void setSelectRightClickedRow(bool isSelect);

    TableItemDelegate *delegate;
    SmoothScrollDelegate *scrollDelagate;
    bool _isSelectRightClickedRow;

public slots:
    void selectRow(int row);
};


class TableView : public QTableView{
    Q_OBJECT
    Q_PROPERTY(bool selectRightClickedRow READ isSelectRightClickedRow WRITE setSelectRightClickedRow)
public:
    TableView(QWidget *parent);
    void showEvent(QShowEvent *event);
    void setBorderVisible(bool isVisible);
    void setBorderRadius(int radius);
    void _setHoverRow(int row);
    void _setPressedRow(int row);
    void _setSelectedRows(QList<QModelIndex> indexes);
    void leaveEvent(QEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void keyPressEvent(QKeyEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *event);
    void setItemDelegate(TableItemDelegate *delegate);
    void selectAll();
    void clearSelection();
    void setCurrentIndex(QModelIndex *index);
    void updateSelectedRows();

    bool isSelectRightClickedRow();
    void setSelectRightClickedRow(bool isSelect);

    TableItemDelegate *delegate;
    SmoothScrollDelegate *scrollDelagate;
    bool _isSelectRightClickedRow;

public slots:
    void selectRow(int row);
};