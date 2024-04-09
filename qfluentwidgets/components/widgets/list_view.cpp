#include "list_view.h"

ListItemDelegate::ListItemDelegate(QListView *parent) : QStyledItemDelegate(parent)
{
    this->margin = 2;
    this->hoverRow = -1;
    this->pressedRow = -1;
    this->selectedRows = QList<int>();
}

void ListItemDelegate::setHoverRow(int row)
{
    this->hoverRow = row;
}

void ListItemDelegate::setPressedRow(int row)
{
    this->pressedRow = row;
}

void ListItemDelegate::setSelectedRows(QList<QModelIndex> indexes)
{
    this->selectedRows.clear();
    for(int i = 0; i < indexes.length(); i++){
        this->selectedRows.append(indexes.at(i).row());
        if(indexes.at(i).row() == this->pressedRow){
            this->pressedRow = -1;
        }
    }
}

QSize ListItemDelegate::sizeHint(QStyleOptionViewItem *option, QModelIndex *index)
{
    QSize size = QStyledItemDelegate::sizeHint(*option, *index);
    size = size.grownBy(QMargins(0, this->margin, 0, this->margin));
    return size;
}

QWidget *ListItemDelegate::createEditor(QWidget *parent, QStyleOptionViewItem *option, QModelIndex *index)
{
    LineEdit *lineEdit = new LineEdit(parent);
    lineEdit->setProperty("transparent", false);
    lineEdit->setStyle(QApplication::style());
    lineEdit->setText(option->text);
    lineEdit->setClearButtonEnabled(true);
    return lineEdit;
}

void ListItemDelegate::updateEditorGeometry(QWidget *editor, QStyleOptionViewItem *option, QModelIndex *index)
{
    QRect rect = option->rect;
    int y = rect.y() + (rect.height() - editor->height() / 2);
    int x = qMax(8, rect.x());
    int w = rect.width();
    if(index->column() == 0){
        w -= 8;
    }
    editor->setGeometry(x, y, w, rect.height());
}



void ListItemDelegate::_drawbackground(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->drawRoundedRect(option.rect, 5, 5);
}


void ListItemDelegate::_drawIndicator(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int y = option.rect.y();
    int h = option.rect.height();
    int ph = qRound(this->pressedRow == index.row() ? 0.35 * h : 0.257 * h);
    painter->setBrush(*(ThemeColor().themeColor()));
    painter->drawRoundedRect(0, ph + y, 3, h - 2 * ph, 1.5, 1.5);
}


void ListItemDelegate::initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const
{
    QStyledItemDelegate::initStyleOption(option, index);
    
    if(index.data(Qt::FontRole).isValid()){
        option->font = index.data(Qt::FontRole).value<QFont>();
    }else{
        option->font = Font().getFont(13, QFont::Normal);
    }

    QColor textColor = isDarkTheme() ? Qt::white : Qt::black;
    QBrush textBrush = index.data(Qt::TextColorRole).value<QBrush>();
    if(textBrush.color().isValid()){
        textColor = textBrush.color();
    }

    option->palette.setColor(QPalette::Text, textColor);
    option->palette.setColor(QPalette::HighlightedText, textColor);
}


void ListItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setRenderHint(QPainter::Antialiasing);

    painter->setClipping(true);
    painter->setClipRect(option.rect);

    QStyleOptionViewItem mutableRect = option;
    mutableRect.rect.adjust(0, this->margin, 0, -this->margin);

    bool isHover = this->hoverRow == index.row();
    bool isPressed = this->pressedRow == index.row();
    bool isAlternate = index.row() % 2 == 0 && ((QTableView *)this->parent())->alternatingRowColors();
    bool isDark = isDarkTheme();

    int c = isDark ? 255 : 0;
    int alpha = 0;

    if(!this->selectedRows.contains(index.row())){
        if(isPressed){
            alpha = isDark ? 9 : 6;
        }else if(isHover){
            alpha = 12;
        }else if(isAlternate){
            alpha = 5;
        }
    }else{
        if(isPressed){
            alpha = isDark ? 15 : 9;
        }else if(isHover){
            alpha = 25;
        }else{
            alpha = 17;
        }

        if(index.column() == 0 && ((QTableView *)this->parent())->horizontalScrollBar()->value() == 0){
            this->_drawIndicator(painter, mutableRect, index);
        }
    }

    painter->setBrush(QColor(c, c, c, alpha));
    this->_drawbackground(painter, option, index);

    painter->restore();
    QStyledItemDelegate::paint(painter, option, index);
}


ListWidget::ListWidget(QWidget *parent) : QListWidget(parent)
{
    this->delegate = new ListItemDelegate(this);
    this->scrollDelegate = new SmoothScrollDelegate(this, true);
    this->_isSelectRightClickedRow = false;

    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("LIST_VIEW"), Theme::AUTO);
    this->setItemDelegate(this->delegate);
    this->setMouseTracking(true);

    connect(this, &ListWidget::entered, this, [this](QModelIndex i){
        this->_setHoverRow(i.row());
    });

    connect(this, &ListWidget::pressed, this, [this](QModelIndex i){
        this->_setPressedRow(i.row());
    });

}


void ListWidget::_setHoverRow(int row)
{
    this->delegate->setHoverRow(row);
    this->viewport()->update();
}

void ListWidget::_setPressedRow(int row)
{
    this->delegate->setPressedRow(row);
    this->viewport()->update();
}


void ListWidget::_setSelectedRows(QList<QModelIndex> indexes)
{
    this->delegate->setSelectedRows(indexes);
    this->viewport()->update();
}

void ListWidget::leaveEvent(QEvent *event)
{
    QListView::leaveEvent(event);
    this->_setHoverRow(-1);
}

void ListWidget::resizeEvent(QResizeEvent *event)
{
    QListView::resizeEvent(event);
    this->viewport()->update();
}

void ListWidget::keyPressEvent(QKeyEvent *e)
{
    QListView::keyPressEvent(e);
    this->updateSelectedRows();
}

void ListWidget::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton || this->_isSelectRightClickedRow){
        return QListView::mousePressEvent(e);
    }

    QModelIndex index = this->indexAt(e->pos());
    if(index.isValid()){
        this->_setPressedRow(index.row());
    }

    QWidget::mousePressEvent(e);
}

void ListWidget::mouseReleaseEvent(QMouseEvent *e)
{
    QListView::mouseReleaseEvent(e);
    this->updateSelectedRows();
    if(this->indexAt(e->pos()).row() < 0 || e->button() == Qt::RightButton){
        this->_setPressedRow(-1);
    }
}

void ListWidget::setItemDelegate(ListItemDelegate *delegate)
{
    this->delegate = delegate;
    QListWidget::setItemDelegate(delegate);
}

void ListWidget::clearSelection()
{
    QListView::clearSelection();
    this->updateSelectedRows();
}

void ListWidget::setCurrentIndex(QModelIndex index)
{
    QListView::setCurrentIndex(index);
    this->updateSelectedRows();
}


void ListWidget::updateSelectedRows()
{
    this->_setSelectedRows(this->selectedIndexes());
}


void ListWidget::setCurrentItem(QListWidgetItem *item, QItemSelectionModel::SelectionFlag command)
{
    this->setCurrentRow(this->row(item), command);
}


void ListWidget::setCurrentItem(QListWidgetItem *item, QItemSelectionModel::SelectionFlags command)
{
    this->setCurrentRow(this->row(item), command);
}



void ListWidget::setCurrentRow(int row, QItemSelectionModel::SelectionFlag command = QItemSelectionModel::SelectionFlag::NoUpdate)
{
    if(command == QItemSelectionModel::SelectionFlag::NoUpdate){
        QListWidget::setCurrentRow(row);
    }else{
        QListWidget::setCurrentRow(row, command);
    }
    this->updateSelectedRows();
}


void ListWidget::setCurrentRow(int row, QItemSelectionModel::SelectionFlags command)
{
    if(command == QItemSelectionModel::SelectionFlag::NoUpdate){
        QListWidget::setCurrentRow(row);
    }else{
        QListWidget::setCurrentRow(row, command);
    }
    this->updateSelectedRows();
}


bool ListWidget::isSelectRightClickedRow()
{
    return this->_isSelectRightClickedRow;
}

void ListWidget::setSelectRightClickedRow(bool isSelect)
{
    this->_isSelectRightClickedRow = isSelect;
}


///////////
ListView::ListView(QWidget *parent) : QListView(parent)
{
    this->delegate = new ListItemDelegate(this);
    this->scrollDelegate = new SmoothScrollDelegate(this, true);
    this->_isSelectRightClickedRow = false;

    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("LIST_VIEW"), Theme::AUTO);
    this->setItemDelegate(this->delegate);
    this->setMouseTracking(true);

    connect(this, &ListView::entered, this, [this](QModelIndex i){
        this->_setHoverRow(i.row());
    });

    connect(this, &ListView::pressed, this, [this](QModelIndex i){
        this->_setPressedRow(i.row());
    });

}


void ListView::_setHoverRow(int row)
{
    this->delegate->setHoverRow(row);
    this->viewport()->update();
}

void ListView::_setPressedRow(int row)
{
    this->delegate->setPressedRow(row);
    this->viewport()->update();
}


void ListView::_setSelectedRows(QList<QModelIndex> indexes)
{
    this->delegate->setSelectedRows(indexes);
    this->viewport()->update();
}

void ListView::leaveEvent(QEvent *event)
{
    QListView::leaveEvent(event);
    this->_setHoverRow(-1);
}

void ListView::resizeEvent(QResizeEvent *event)
{
    QListView::resizeEvent(event);
    this->viewport()->update();
}

void ListView::keyPressEvent(QKeyEvent *e)
{
    QListView::keyPressEvent(e);
    this->updateSelectedRows();
}

void ListView::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton || this->_isSelectRightClickedRow){
        return QListView::mousePressEvent(e);
    }

    QModelIndex index = this->indexAt(e->pos());
    if(index.isValid()){
        this->_setPressedRow(index.row());
    }

    QWidget::mousePressEvent(e);
}

void ListView::mouseReleaseEvent(QMouseEvent *e)
{
    QListView::mouseReleaseEvent(e);
    this->updateSelectedRows();
    if(this->indexAt(e->pos()).row() < 0 || e->button() == Qt::RightButton){
        this->_setPressedRow(-1);
    }
}

void ListView::setItemDelegate(ListItemDelegate *delegate)
{
    this->delegate = delegate;
    QListView::setItemDelegate(delegate);
}

void ListView::clearSelection()
{
    QListView::clearSelection();
    this->updateSelectedRows();
}

void ListView::setCurrentIndex(QModelIndex index)
{
    QListView::setCurrentIndex(index);
    this->updateSelectedRows();
}


void ListView::updateSelectedRows()
{
    this->_setSelectedRows(this->selectedIndexes());
}


bool ListView::isSelectRightClickedRow()
{
    return this->_isSelectRightClickedRow;
}

void ListView::setSelectRightClickedRow(bool isSelect)
{
    this->_isSelectRightClickedRow = isSelect;
}