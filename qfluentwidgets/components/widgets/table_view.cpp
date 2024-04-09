#include "table_view.h"


TableItemDelegate::TableItemDelegate(QTableView *parent) : QStyledItemDelegate(parent)
{
    this->margin = 2;
    this->hoverRow = -1;
    this->pressedRow = -1;
    this->selectedRows = QList<int>();
}

void TableItemDelegate::setHoverRow(int row)
{
    this->hoverRow = row;
}

void TableItemDelegate::setPressedRow(int row)
{
    this->pressedRow = row;
}

void TableItemDelegate::setSelectedRows(QList<QModelIndex> indexes)
{
    this->selectedRows.clear();
    for(int i = 0; i < indexes.length(); i++){
        this->selectedRows.append(indexes.at(i).row());
        if(indexes.at(i).row() == this->pressedRow){
            this->pressedRow = -1;
        }
    }
}

QSize TableItemDelegate::sizeHint(QStyleOptionViewItem *option, QModelIndex *index)
{
    QSize size = QStyledItemDelegate::sizeHint(*option, *index);
    size = size.grownBy(QMargins(0, this->margin, 0, this->margin));
    return size;
}

QWidget *TableItemDelegate::createEditor(QWidget *parent, QStyleOptionViewItem *option, QModelIndex *index)
{
    LineEdit *lineEdit = new LineEdit(parent);
    lineEdit->setProperty("transparent", false);
    lineEdit->setStyle(QApplication::style());
    lineEdit->setText(option->text);
    lineEdit->setClearButtonEnabled(true);
    return lineEdit;
}

void TableItemDelegate::updateEditorGeometry(QWidget *editor, QStyleOptionViewItem *option, QModelIndex *index)
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



void TableItemDelegate::_drawbackground(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int r = 5;
    QRect rect;
    if(index.column() == 0){
        rect = option.rect.adjusted(4, 0, r + 1, 0);
        painter->drawRoundedRect(rect, r, r);
    }else if(index.column() == index.model()->columnCount(index.parent()) - 1){
        rect = option.rect.adjusted(-r - 1, 0, -4, 0);
        painter->drawRoundedRect(rect, r, r);
    }else{
        rect = option.rect.adjusted(-1, 0, 1, 0);
        painter->drawRect(rect);
    }
}


void TableItemDelegate::_drawIndicator(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int y = option.rect.y();
    int h = option.rect.height();
    int ph = qRound(this->pressedRow == index.row() ? 0.35 * h : 0.257 * h);
    painter->setBrush(*(ThemeColor().themeColor()));
    painter->drawRoundedRect(4, ph + y, 3, h - 2 * ph, 1.5, 1.5);
}


void TableItemDelegate::initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const
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


void TableItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
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
    this->_drawbackground(painter, mutableRect, index);

    painter->restore();
    QStyledItemDelegate::paint(painter, mutableRect, index);
}


TableWidget::TableWidget(QWidget *parent) : QTableWidget(parent)
{
    this->delegate = new TableItemDelegate(this);
    this->scrollDelagate = new SmoothScrollDelegate(this, true);
    this->_isSelectRightClickedRow = false;

    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("TABLE_VIEW"), Theme::AUTO);

    this->setShowGrid(false);
    this->setMouseTracking(true);
    this->setAlternatingRowColors(true);
    this->setItemDelegate(this->delegate);
    this->setSelectionBehavior(TableWidget::SelectRows);
    this->horizontalHeader()->setHighlightSections(false);

    connect(this, &QTableWidget::entered, this, [this](QModelIndex i){
        this->_setHoverRow(i.row());
    });

    connect(this, &QTableWidget::pressed, this, [this](QModelIndex i){
        this->_setPressedRow(i.row());
    });

    connect(this->verticalHeader(), &QHeaderView::sectionClicked, this, &TableWidget::selectRow);
}


void TableWidget::showEvent(QShowEvent *event)
{
    QTableWidget::showEvent(event);
    this->resizeRowsToContents();
}


void TableWidget::setBorderVisible(bool isVisible)
{
    this->setProperty("isBorderVisible", isVisible);
    this->setStyle(QApplication::style());
}


void TableWidget::setBorderRadius(int radius)
{
    QString qss = QString("QTableView{border-radius: %1px}").arg(radius);
    setCustomStyleSheet(this, qss, qss);
}


void TableWidget::_setHoverRow(int row)
{
    this->delegate->setHoverRow(row);
    this->viewport()->update();
}   

void TableWidget::_setPressedRow(int row)
{
    this->delegate->setPressedRow(row);
    this->viewport()->update();
}


void TableWidget::_setSelectedRows(QList<QModelIndex> indexes)
{
    this->delegate->setSelectedRows(indexes);
    this->viewport()->update();
}

void TableWidget::leaveEvent(QEvent *event)
{
    QTableWidget::leaveEvent(event);
    this->_setHoverRow(-1);
}


void TableWidget::resizeEvent(QResizeEvent *event)
{
    QTableWidget::resizeEvent(event);
    this->viewport()->update();
}

void TableWidget::keyPressEvent(QKeyEvent *e)
{
    QTableWidget::keyPressEvent(e);
    this->updateSelectedRows();
}

void TableWidget::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton || this->_isSelectRightClickedRow){
        return QTableView::mousePressEvent(e);
    }

    QModelIndex index = this->indexAt(e->pos());
    if(index.isValid()){
        this->_setPressedRow(index.row());
    }

    QWidget::mousePressEvent(e);
}


void TableWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QTableWidget::mouseReleaseEvent(event);
    this->updateSelectedRows();

    if(this->indexAt(event->pos()).row() < 0 || event->button() == Qt::RightButton){
        this->_setPressedRow(-1);
    }
}


void TableWidget::setItemDelegate(TableItemDelegate *delegate)
{
    this->delegate = delegate;
    QTableWidget::setItemDelegate(delegate);
}

void TableWidget::selectAll()
{
    QTableWidget::selectAll();
    this->updateSelectedRows();
}

void TableWidget::selectRow(int row)
{
    QTableWidget::selectRow(row);
    this->updateSelectedRows();
}


void TableWidget::clearSelection()
{
    QTableWidget::clearSelection();
    this->updateSelectedRows();
}

void TableWidget::setCurrentIndex(QModelIndex *index)
{
    QTableWidget::setCurrentIndex(*index);
    this->updateSelectedRows();
}


void TableWidget::updateSelectedRows()
{
    this->_setSelectedRows(this->selectedIndexes());
}


void TableWidget::setCurrentCell(int row, int column, QItemSelectionModel::SelectionFlag command)
{
    this->setCurrentItem(this->item(row, column), command);
}

void TableWidget::setCurrentCell(int row, int column, QItemSelectionModel::SelectionFlags command)
{
    this->setCurrentItem(this->item(row, column), command);
}


void TableWidget::setCurrentItem(QTableWidgetItem *item, QItemSelectionModel::SelectionFlag command)
{

    if(command == QItemSelectionModel::SelectionFlag::NoUpdate){
        QTableWidget::setCurrentItem(item, command);
    }else{
         QTableWidget::setCurrentItem(item, command);
    }
    this->updateSelectedRows();

    this->updateSelectedRows();
}


void TableWidget::setCurrentItem(QTableWidgetItem *item, QItemSelectionModel::SelectionFlags command)
{

    if(command == QItemSelectionModel::SelectionFlag::NoUpdate){
        QTableWidget::setCurrentItem(item, command);
    }else{
         QTableWidget::setCurrentItem(item, command);
    }
    this->updateSelectedRows();

    this->updateSelectedRows();
}


bool TableWidget::isSelectRightClickedRow()
{
    return this->_isSelectRightClickedRow;
}   

void TableWidget::setSelectRightClickedRow(bool isSelect)
{
    this->_isSelectRightClickedRow = isSelect;
}



TableView::TableView(QWidget *parent) : QTableView(parent)
{
    this->delegate = new TableItemDelegate(this);
    this->scrollDelagate = new SmoothScrollDelegate(this, true);
    this->_isSelectRightClickedRow = false;

    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("TABLE_VIEW"), Theme::AUTO);

    this->setShowGrid(false);
    this->setMouseTracking(true);
    this->setAlternatingRowColors(true);
    this->setItemDelegate(this->delegate);
    this->setSelectionBehavior(TableWidget::SelectRows);
    this->horizontalHeader()->setHighlightSections(false);

    connect(this, &QTableWidget::entered, this, [this](QModelIndex i){
        this->_setHoverRow(i.row());
    });

    connect(this, &QTableWidget::pressed, this, [this](QModelIndex i){
        this->_setPressedRow(i.row());
    });

    connect(this->verticalHeader(), &QHeaderView::sectionClicked, this, &TableView::selectRow);
}


void TableView::showEvent(QShowEvent *event)
{
    QTableView::showEvent(event);
    this->resizeRowsToContents();
}


void TableView::setBorderVisible(bool isVisible)
{
    this->setProperty("isBorderVisible", isVisible);
    this->setStyle(QApplication::style());
}


void TableView::setBorderRadius(int radius)
{
    QString qss = QString("QTableView{{border-radius: {%1}px}}").arg(radius);
    setCustomStyleSheet(this, qss, qss);
}


void TableView::_setHoverRow(int row)
{
    this->delegate->setHoverRow(row);
    this->viewport()->update();
}   

void TableView::_setPressedRow(int row)
{
    this->delegate->setPressedRow(row);
    this->viewport()->update();
}


void TableView::_setSelectedRows(QList<QModelIndex> indexes)
{
    this->delegate->setSelectedRows(indexes);
    this->viewport()->update();
}

void TableView::leaveEvent(QEvent *event)
{
    QTableView::leaveEvent(event);
    this->_setHoverRow(-1);
}


void TableView::resizeEvent(QResizeEvent *event)
{
    QTableView::resizeEvent(event);
    this->viewport()->update();
}

void TableView::keyPressEvent(QKeyEvent *e)
{
    QTableView::keyPressEvent(e);
    this->updateSelectedRows();
}

void TableView::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton || this->_isSelectRightClickedRow){
        return QTableView::mousePressEvent(e);
    }

    QModelIndex index = this->indexAt(e->pos());
    if(index.isValid()){
        this->_setPressedRow(index.row());
    }

    QWidget::mousePressEvent(e);
}


void TableView::mouseReleaseEvent(QMouseEvent *event)
{
    QTableView::mouseReleaseEvent(event);
    this->updateSelectedRows();

    if(this->indexAt(event->pos()).row() < 0 || event->button() == Qt::RightButton){
        this->_setPressedRow(-1);
    }
}


void TableView::setItemDelegate(TableItemDelegate *delegate)
{
    this->delegate = delegate;
    QTableView::setItemDelegate(delegate);
}

void TableView::selectAll()
{
    QTableView::selectAll();
    this->updateSelectedRows();
}

void TableView::selectRow(int row)
{
    QTableView::selectRow(row);
    this->updateSelectedRows();
}


void TableView::clearSelection()
{
    QTableView::clearSelection();
    this->updateSelectedRows();
}

void TableView::setCurrentIndex(QModelIndex *index)
{
    QTableView::setCurrentIndex(*index);
    this->updateSelectedRows();
}


void TableView::updateSelectedRows()
{
    this->_setSelectedRows(this->selectedIndexes());
}


bool TableView::isSelectRightClickedRow()
{
    return this->_isSelectRightClickedRow;
}   

void TableView::setSelectRightClickedRow(bool isSelect)
{
    this->_isSelectRightClickedRow = isSelect;
}