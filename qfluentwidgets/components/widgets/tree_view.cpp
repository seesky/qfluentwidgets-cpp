#include "tree_view.h"

TreeItemDelegate::TreeItemDelegate(QTreeView *parent) : QStyledItemDelegate(parent)
{

}

void TreeItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    QStyledItemDelegate::paint(painter, option, index);

    if(!(option.state & (QStyle::State_Selected | QStyle::State_MouseOver))){
        return;
    }

    painter->save();
    painter->setPen(Qt::NoPen);

    int h = option.rect.height() - 4;
    int c = isDarkTheme() ? 255 : 0;
    painter->setBrush(QColor(c, c, c, 9));
    painter->drawRoundedRect(4, option.rect.y() + 2, ((QWidget*)this->parent())->width() - 8, h, 4, 4);

    if(option.state & QStyle::State_Selected && ((QTreeView*)this->parent())->horizontalScrollBar()->value() == 0){
        painter->setBrush(*(ThemeColor().themeColor()));
        painter->drawRoundedRect(4, 9 + option.rect.y(), 3, h - 13, 1.5, 1.5);
    }

    painter->restore();
}


void TreeItemDelegate::initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const
{
    QStyledItemDelegate::initStyleOption(option, index);

    option->font = index.data(Qt::FontRole).isValid() ? index.data(Qt::FontRole).value<QFont>() : Font().getFont(13, QFont::Normal);

    QColor textColor = isDarkTheme() ? Qt::white : Qt::black;


    if(index.data(Qt::TextColorRole).isValid()){
        QBrush textBrush = index.data(Qt::TextColorRole).value<QBrush>();
        textColor = textBrush.color();
    }
    
    option->palette.setColor(QPalette::Text, textColor);
    option->palette.setColor(QPalette::HighlightedText, textColor);
}


TreeWidget::TreeWidget(QWidget *parent) : QTreeWidget(parent)
{
    this->scrollDelagate = new SmoothScrollDelegate(this, true);

    this->header()->setHighlightSections(false);
    this->header()->setDefaultAlignment(Qt::AlignCenter);

    this->setItemDelegate(new TreeItemDelegate(this));
    this->setIconSize(QSize(16, 16));

    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("TREE_VIEW"), Theme::AUTO);
}

void TreeWidget::drawBranches(QPainter *painter, const QRect &rect, const QModelIndex &index) const
{
    QRect r = QRect(rect);
    r.moveLeft(15);
    return QTreeView::drawBranches(painter, r, index);
}


void TreeWidget::setBorderVisible(bool isVisible)
{
    this->setProperty("isBorderVisible", isVisible);
    this->setStyle(QApplication::style());
}

void TreeWidget::setBorderRadius(int radius)
{
    QString qss = QString("QTreeView{border-radius: %1px}").arg(radius);
    setCustomStyleSheet(this, qss, qss);
}



TreeView::TreeView(QWidget *parent) : QTreeView(parent)
{
    this->scrollDelagate = new SmoothScrollDelegate(this, true);

    this->header()->setHighlightSections(false);
    this->header()->setDefaultAlignment(Qt::AlignCenter);

    this->setItemDelegate(new TreeItemDelegate(this));
    this->setIconSize(QSize(16, 16));

    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("TREE_VIEW"), Theme::AUTO);
}

void TreeView::drawBranches(QPainter *painter, const QRect &rect, const QModelIndex &index) const
{
    QRect r = QRect(rect);
    r.moveLeft(15);
    return QTreeView::drawBranches(painter, r, index);
}


void TreeView::setBorderVisible(bool isVisible)
{
    this->setProperty("isBorderVisible", isVisible);
    this->setStyle(QApplication::style());
}




void TreeView::setBorderRadius(int radius)
{
    QString qss = QString("QTreeView{border-radius: %1px}").arg(radius);
    setCustomStyleSheet(this, qss, qss);
}
