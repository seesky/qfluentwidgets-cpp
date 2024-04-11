#include "expand_layout.h"

ExpandLayout::ExpandLayout(QWidget *parent) : QLayout(parent)
{
    this->__items = QList<QLayoutItem*>();
    this->__widgets = QList<QWidget*>();
}

void ExpandLayout::addWidget(QWidget *widget)
{
    if(this->__widgets.contains(widget)){
        return;
    }

    this->__widgets.append(widget);
    widget->installEventFilter(this);
}

void ExpandLayout::addItem(QLayoutItem *item)
{
    this->__items.append(item);
}

int ExpandLayout::count() const
{
    return this->__items.length();
}

QLayoutItem *ExpandLayout::itemAt(int index) const
{
    if(0 <= index && index < this->__items.length()){
        return this->__items.at(index);
    }
    return nullptr;
}

QLayoutItem *ExpandLayout::takeAt(int index)
{
    if(0 <= index && index < this->__items.length()){
        this->__widgets.takeAt(index);
        return this->__items.takeAt(index);
    }
    return nullptr;
}

Qt::Orientations ExpandLayout::expandingDirections() const
{
    return Qt::Vertical;
}

bool ExpandLayout::hasHeightForWidth() const
{
    return true;
}

int ExpandLayout::heightForWidth(int width) const
{
    return this->__doLayout(QRect(0, 0, width, 0), false);
}

void ExpandLayout::setGeometry(const QRect& rect)
{
    QLayout::setGeometry(rect);
    this->__doLayout(rect, true);
}

QSize ExpandLayout::sizeHint() const
{
    return this->minimumSize();
}

QSize ExpandLayout::minimumSize() const
{
    QSize size = QSize();

    for(int i = 0; i < this->__widgets.length(); i++){
        size = size.expandedTo(this->__widgets.at(i)->minimumSize());
    }

    QMargins m = this->contentsMargins();
    size += QSize(m.left() + m.right(), m.top() + m.bottom());

    return size;
}


int ExpandLayout::__doLayout(QRect rect, bool move) const
{
    QMargins margin = this->contentsMargins();
    int x = rect.x() + margin.left();
    int y = rect.y() + margin.top() + margin.bottom();
    int width = rect.width() - margin.left() - margin.right();

    for(int i = 0; i < this->__widgets.length(); i++){
        QWidget *w = this->__widgets.at(i);
        if(w->isHidden()){
            continue;
        }

        y += (i > 0) * this->spacing();
        if(move){
            w->setGeometry(QRect(QPoint(x, y), QSize(width, w->height())));
        }

        y += w->height();
    }

    return y - rect.y();
}


bool ExpandLayout::eventFilter(QObject *watched, QEvent *event)
{
    if(this->__widgets.contains((QWidget*)watched)){
        if(event->type() == QEvent::Resize){
            QResizeEvent *re = dynamic_cast<QResizeEvent*>(event);
            QSize ds = re->size() - re->oldSize();
            if(ds.height() != 0 && ds.width() == 0){
                QWidget *w = this->parentWidget();
                w->resize(w->width(), w->height() + ds.height());
            }
        }
    }
    return QLayout::eventFilter(watched, event);
}