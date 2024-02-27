#include "cycle_list_widget.h"

ScrollButtonC::ScrollButtonC(FluentIcon *icon, QWidget *parent) : QToolButton(parent)
{
    this->_icon = icon;
    this->isPressed = false;
    this->installEventFilter(this);
}

bool ScrollButtonC::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this){
        if(event->type() == QEvent::MouseButtonPress){
            this->isPressed = true;
            this->update();
        }else if(event->type() == QEvent::MouseButtonRelease){
            this->isPressed = false;
            this->update();
        }
    }
    return QToolButton::eventFilter(watched, event);
}

void ScrollButtonC::paintEvent(QPaintEvent *e)
{
    QToolButton::paintEvent(e);
    QPainter *painter = new QPainter(this);
    painter->setRenderHints(QPainter::Antialiasing);

    int w, h;

    if(!this->isPressed){
        w = 10;
        h = 10;
    }else{
        w = 8;
        h = 8;
    }
    
    int x = (this->width() - w) / 2;
    int y = (this->height() - h) / 2;

    if(!isDarkTheme()){
        QColor color = (new QColor("#5e5e5e"))->name();
        std::map<QString, QString> attributes = {
            {"fill", color.name()}
        };
        this->_icon->render(painter, QRect(x, y, w, h), Theme::AUTO, 0, &attributes);
    }else{
        this->_icon->render(painter, QRect(x, y, w, h), Theme::AUTO, 0, nullptr);
    }
    painter->end();
}

CycleListWidget::CycleListWidget(QList<QVariant> *items, QSize *itemSize, Qt::Alignment align, QWidget *parent) : QListWidget(parent)
{
    this->itemSize = itemSize;
    this->align = align;

    FluentIcon *upButtonIcon = new FluentIcon();
    upButtonIcon->setIconName("CARE_UP_SOLID");
    this->upButton = new ScrollButtonC(upButtonIcon, this);

    FluentIcon *downButtonIcon = new FluentIcon();
    downButtonIcon->setIconName("CARE_DOWN_SOLID");
    this->downButton = new ScrollButtonC(downButtonIcon, this);

    this->scrollDuration = 250;
    this->originItems = items; //TODO：需要注意数据是否丢失

    this->vScrollBar = new SmoothScrollBar(Qt::Vertical, this);
    this->visibleNumber = 9;

    this->setItems(items);

    this->setVerticalScrollMode(this->ScrollPerPixel);
    this->vScrollBar->setScrollAnimation(this->scrollDuration, QEasingCurve::OutCubic);
    this->vScrollBar->setForceHidden(true);

    this->setViewportMargins(0, 0, 0, 0);
    this->setFixedSize(itemSize->width() + 8, itemSize->height() * this->visibleNumber);

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->upButton->hide();
    this->downButton->hide();

    connect(this->upButton, &ScrollButtonC::clicked, this, &CycleListWidget::scrollUp);
    connect(this->downButton, &ScrollButtonC::clicked, this, &CycleListWidget::scrollDown);

    connect(this, &CycleListWidget::itemClicked, this, &CycleListWidget::_onItemClicked);

    this->installEventFilter(this);
}

void CycleListWidget::setItems(QList<QVariant> *items)
{
    this->clear();
    this->_createItems(items);
}

void CycleListWidget::_createItems(QList<QVariant> *items)
{
    int N = items->length();
    this->isCycle = N > this->visibleNumber;

    if(this->isCycle){
        for(int i = 0; i < 2; i++){
            this->_addColumnItems(items, false);

            this->_currentIndex = items->length();

            QListWidget::scrollToItem(this->item(this->currentIndex() - this->visibleNumber / 2), QListWidget::PositionAtTop);
        }
    }else{
        int n = this->visibleNumber / 2;

        QList<QVariant> *tmpList = new QList<QVariant>();
        for (int i = 0; i < n; ++i) {
            tmpList->append(QVariant::fromValue<QString>(""));
        }

        this->_addColumnItems(tmpList, true);
        this->_addColumnItems(items, false);
        this->_addColumnItems(tmpList, true);

        this->_currentIndex = n;
    }
}


void CycleListWidget::_addColumnItems(QList<QVariant> *items, bool disabled)
{
    for(int i = 0; i < items->length(); i++){
        QListWidgetItem *item = new QListWidgetItem(items->at(i).value<QString>(), this);
        item->setSizeHint(*(this->itemSize));
        item->setTextAlignment(this->align | Qt::AlignVCenter);
        if(disabled){
            item->setFlags(Qt::NoItemFlags);
        }

        this->addItem(item);
    }
}

void CycleListWidget::_onItemClicked(QListWidgetItem *item)
{
    this->setCurrentIndex(this->row(item));
    this->scrollToItem(this->currentItem(), QListWidget::PositionAtCenter);
}

void CycleListWidget::setSelectedItem(QString text)
{
    if(text.isEmpty()){
        return;
    }

    QList<QListWidgetItem *> items = this->findItems(text, Qt::MatchExactly);

    if(items.isEmpty()){
        return;
    }

    if(items.length() >= 2){
        this->setCurrentIndex(this->row(items[1]));
    }else{
        this->setCurrentIndex(this->row(items[0]));
    }

    QListWidget::scrollToItem(this->currentItem(), QListWidget::PositionAtCenter);
}



void CycleListWidget::scrollToItem(QListWidgetItem *item, ScrollHint hint)
{
    int index = this->row(item);
    int y = item->sizeHint().height() * (index - this->visibleNumber / 2);
    this->vScrollBar->scrollTo(y, true);

    this->clearSelection();
    item->setSelected(false);

    emit(this->currentItemChanged(item));
}

void CycleListWidget::wheelEvent(QWheelEvent *e)
{
    if(e->angleDelta().y() < 0){
        this->scrollDown();
    }else{
        this->scrollUp();
    }
}

void CycleListWidget::scrollDown()
{
    this->setCurrentIndex(this->currentIndex() + 1);
    this->scrollToItem(this->currentItem(), QListWidget::PositionAtCenter);
}

void CycleListWidget::scrollUp()
{
    this->setCurrentIndex(this->currentIndex() - 1);
    this->scrollToItem(this->currentItem(), QListWidget::PositionAtCenter);
}


void CycleListWidget::enterEvent(QEvent *event)
{
    this->upButton->show();
    this->downButton->show();
}

void CycleListWidget::leaveEvent(QEvent *event)
{
    this->upButton->hide();
    this->downButton->hide();
}


void CycleListWidget::resizeEvent(QResizeEvent *event)
{
    this->upButton->resize(this->width(), 34);
    this->downButton->resize(this->width(), 34);
    this->downButton->move(0, this->height() - 34);
}

bool CycleListWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched != this || event->type() != QEvent::KeyPress){
        return QListWidget::eventFilter(watched, event);
    }

    QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);

    if(keyEvent != nullptr){
        if(keyEvent->key() == Qt::Key_Down){
            this->scrollDown();
            return true;
        }else if(keyEvent->key() == Qt::Key_Up){
            this->scrollUp();
            return true;
        }
    }

    return QListWidget::eventFilter(watched, event); 
    
}

QListWidgetItem* CycleListWidget::currentItem()
{
    return this->item(this->currentIndex());
}

int CycleListWidget::currentIndex()
{
    return this->_currentIndex;
}

void CycleListWidget::setCurrentIndex(int index)
{
    if(!this->isCycle){
        int n = this->visibleNumber / 2;
        this->_currentIndex = qMax(n, qMin(n + this->originItems->length() - 1, index));
    }else{
        int N = this->count() / 2;
        int m = (this->visibleNumber + 1) / 2;
        this->_currentIndex = index;

        if(index >= this->count() - m){
            this->_currentIndex = N + index - this->count();
            QListWidget::scrollToItem(this->item(this->currentIndex() - 1), this->PositionAtCenter);
        }else if(index <= m - 1){
            this->_currentIndex = N + index;
            QListWidget::scrollToItem(this->item(N + index + 1), this->PositionAtCenter);
        }

    }
}