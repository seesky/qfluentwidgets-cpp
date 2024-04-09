#include "pips_pager.h"


PipPagerScrollButton::PipPagerScrollButton(QWidget *parent) : ToolButton(parent)
{
    this->_postInit();
}

PipPagerScrollButton::PipPagerScrollButton(FluentIcon *icon, QWidget *parent) : ToolButton(icon, parent)
{
    this->_postInit();
}

PipPagerScrollButton::PipPagerScrollButton(SpinIcon *icon, QWidget *parent) : ToolButton(icon, parent)
{
    this->_postInit();
}

PipPagerScrollButton::PipPagerScrollButton(QIcon *icon, QWidget *parent) : ToolButton(icon, parent)
{
    this->_postInit();
}

PipPagerScrollButton::PipPagerScrollButton(QString icon, QWidget *parent) : ToolButton(icon, parent)
{
    this->_postInit();    
}

void PipPagerScrollButton::_postInit()
{
    this->setFixedSize(12, 12);
}

void PipPagerScrollButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    QColor color;
    if(isDarkTheme()){
        color = QColor(255, 255, 255);
        painter.setOpacity(this->isHover || this->isPressed ? 0.773 : 0.541);
    }else{
        color = QColor(0, 0, 0);
        painter.setOpacity(this->isHover || this->isPressed ? 0.616 : 0.45);
    }

    QRect rect;
    if(this->isPressed){
        rect = QRect(3, 3, 6, 6);
    }else{
        rect = QRect(2, 2, 8, 8);
    }

    std::map<QString, QString> attributes;
    attributes[QString("fill")] = color.name();
    MIcon().drawIcon(this->_icon, &painter, rect, &attributes, QIcon::State::Off);
}


PipsDelegate::PipsDelegate(QWidget *parent) : QStyledItemDelegate(parent)
{
    this->hoveredRow = -1;
    this->pressedRow = -1;
}

void PipsDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();
    painter->setRenderHints(QPainter::Antialiasing);
    painter->setPen(Qt::NoPen);

    bool isHover = index.row() == this->hoveredRow;
    bool isPressed = index.row() == this->pressedRow;

    QColor color;
    if(isDarkTheme()){
        if(isHover || isPressed){
            color = QColor(255, 255, 255, 197);
        }else{
            color = QColor(255, 255, 255, 138);
        }
    }else{
        if(isHover || isPressed){
            color = QColor(0, 0, 0, 157);
        }else{
            color = QColor(0, 0, 0, 114);
        }
    }

    painter->setBrush(color);

    int r;
    if(option.state & QStyle::State_Selected || (isHover && !isPressed)){
        r = 3;
    }else{
        r = 2;
    }

    int x = option.rect.x() + 6 - r;
    int y = option.rect.y() + 6 - r;
    painter->drawEllipse(QRectF(x, y, 2 * r, 2 * r));

    painter->restore();
}


void PipsDelegate::setPressedRow(int row)
{
    this->pressedRow = row;
    ((PipsPager *)this->parent())->viewport()->update(); //TODO:需要确认类型
}

void PipsDelegate::setHoveredRow(int row)
{
    this->hoveredRow = row;
    ((PipsPager *)this->parent())->viewport()->update(); //TODO:需要确认类型
}


PipsPager::PipsPager(QWidget *parent) : QListWidget(parent)
{
    this->orientation = Qt::Horizontal;
    this->_postInit();
}

PipsPager::PipsPager(Qt::Orientation orientation, QWidget *parent) : QListWidget(parent)
{
    this->orientation = orientation;
    this->_postInit();
}

void PipsPager::_postInit()
{
    this->_visibleNumber = 5;
    this->isHover = false;

    this->delegate = new PipsDelegate(this);
    this->scrollBar = new SmoothScrollBar(this->orientation, this);

    this->scrollBar->setScrollAnimation(500, QEasingCurve::OutCubic);
    this->scrollBar->setForceHidden(true);

    this->setMouseTracking(true);
    this->setUniformItemSizes(true);
    this->setGridSize(QSize(12, 12));
    this->setItemDelegate(this->delegate);
    this->setMovement(QListWidget::Static);
    this->setVerticalScrollMode(this->ScrollPerPixel);
    this->setHorizontalScrollMode(this->ScrollPerPixel);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("PIPS_PAGER"), Theme::AUTO);

    if(this->isHorizontal()){
        this->setFlow(QListWidget::LeftToRight);
        this->setViewportMargins(15, 0, 15, 0);

        FluentIcon *preButtonIcon = new FluentIcon();
        preButtonIcon->setIconName("CARE_LEFT_SOLID");
        this->preButton = new PipPagerScrollButton(preButtonIcon, this);
        FluentIcon *nextButtonIcon = new FluentIcon();
        nextButtonIcon->setIconName("CARE_RIGHT_SOLID");
        this->nextButton = new PipPagerScrollButton(nextButtonIcon, this);
        this->setFixedHeight(12);

        this->preButton->installEventFilter(new ToolTipFilter(this->preButton, 1000, ToolTipPosition::LEFT));
        this->nextButton->installEventFilter(new ToolTipFilter(this->nextButton, 1000, ToolTipPosition::RIGHT));


    }else{
        this->setViewportMargins(0, 15, 0, 15);
        FluentIcon *preButtonIcon = new FluentIcon();
        preButtonIcon->setIconName("CARE_UP_SOLID");
        this->preButton = new PipPagerScrollButton(preButtonIcon, this);
        FluentIcon *nextButtonIcon = new FluentIcon();
        nextButtonIcon->setIconName("CARE_DOWN_SOLID");
        this->nextButton = new PipPagerScrollButton(nextButtonIcon, this);
        this->setFixedWidth(12);

        this->preButton->installEventFilter(new ToolTipFilter(this->preButton, 1000, ToolTipPosition::TOP));
        this->nextButton->installEventFilter(new ToolTipFilter(this->nextButton, 1000, ToolTipPosition::BOTTOM));
    }

    this->setPreviousButtonDisplayMode(PipsScrollButtonDisplayMode::NEVER);
    this->setNextButtonDisplayMode(PipsScrollButtonDisplayMode::NEVER);
    this->preButton->setToolTip(this->tr("Previous Page"));
    this->nextButton->setToolTip(this->tr("Next Page"));

    connect(this->preButton, &PipPagerScrollButton::clicked, this, &PipsPager::scrollPrevious);
    connect(this->nextButton, &PipPagerScrollButton::clicked, this, &PipsPager::scrollNext);
    connect(this, &PipsPager::itemPressed, this, &PipsPager::_setPressedItem);
    connect(this, &PipsPager::itemEntered, this, &PipsPager::_setHoveredItem);
}


void PipsPager::_setPressedItem(QListWidgetItem *item)
{
    this->delegate->setPressedRow(this->row(item));
    this->setCurrentIndex(this->row(item));
}


void PipsPager::_setHoveredItem(QListWidgetItem *item)
{
    this->delegate->setHoveredRow(this->row(item));
}


void PipsPager::setPageNumber(int n)
{
    this->clear();
    
    QStringList list = QStringList();
    for(int i = 0; i < n; i++){
        list.append(QString("15555"));
    }

    this->addItems(list);

    for(int i = 0; i < n; i++){
        QListWidgetItem *item = this->item(i);
        item->setData(Qt::UserRole, QVariant::fromValue<int>(i + 1));
        item->setSizeHint(this->gridSize());
    }

    this->setCurrentIndex(0);
    this->adjustSize();
}

int PipsPager::getPageNumber()
{
    return this->count();
}

int PipsPager::getVisibleNumber()
{
    return this->_visibleNumber;
}

void PipsPager::setVisibleNumber(int n)
{
    this->_visibleNumber = n;
    this->adjustSize();
}

void PipsPager::scrollNext()
{
    this->setCurrentIndex(this->currentIndex() + 1);
}

void PipsPager::scrollPrevious()
{
    this->setCurrentIndex(this->currentIndex() - 1);
}


void PipsPager::scrollToItem(QListWidgetItem *item, QListWidget::ScrollHint hint = QListWidget::PositionAtCenter)
{
    int index = this->row(item);
    QSize size = item->sizeHint();
    int s = this->isHorizontal() ? size.width() : size.height();
    this->scrollBar->scrollTo(s * (index - this->getVisibleNumber() / 2), true);

    this->clearSelection();
    item->setSelected(false);

    emit(this->currentIndexChanged(index));
} 


void PipsPager::adjustSize()
{
    QMargins m = this->viewportMargins();
    if(this->isHorizontal()){
        int w = this->getVisibleNumber() * this->gridSize().width() + m.left() + m.right();
        this->setFixedWidth(w);
    }else{
        int h = this->getVisibleNumber() * this->gridSize().height() + m.top() + m.bottom();
        this->setFixedHeight(h);
    }
}


bool PipsPager::isHorizontal()
{
    return this->orientation == Qt::Horizontal;
}


void PipsPager::setCurrentIndex(int index)
{
    if( !(0 <= index && index < this->count())){
        return;
    }

    QListWidgetItem *item = this->item(index);
    this->scrollToItem(item, QListWidget::PositionAtCenter);
    QListWidget::setCurrentItem(item);

    this->_updateScrollButtonVisibility();
}


bool PipsPager::isPreviousButtonVisible()
{
    if(this->currentIndex() <= 0 || this->previousButtonDisplayMode == PipsScrollButtonDisplayMode::NEVER){
        return false;
    }

    if(this->previousButtonDisplayMode == PipsScrollButtonDisplayMode::ON_HOVER){
        return this->isHover;
    }

    return true;
}

bool PipsPager::isNextButtonVisible()
{
    if(this->currentIndex() >= this->count() - 1 || this->nextButtonDisplayMode == PipsScrollButtonDisplayMode::NEVER){
        return false;
    }

    if(this->nextButtonDisplayMode == PipsScrollButtonDisplayMode::ON_HOVER){
        return this->isHover;
    }

    return true;
}

int PipsPager::currentIndex()
{
    return QListWidget::currentIndex().row();
}

void PipsPager::setPreviousButtonDisplayMode(PipsScrollButtonDisplayMode mode)
{
    this->previousButtonDisplayMode = mode;
    this->preButton->setVisible(this->isPreviousButtonVisible());
}

void PipsPager::setNextButtonDisplayMode(PipsScrollButtonDisplayMode mode)
{
    this->nextButtonDisplayMode = mode;
    this->nextButton->setVisible(this->isNextButtonVisible());
}

void PipsPager::mouseReleaseEvent(QMouseEvent *e)
{
    QListWidget::mouseReleaseEvent(e);
    this->delegate->setPressedRow(-1);
}

void PipsPager::enterEvent(QEvent *event)
{
    QListWidget::enterEvent(event);
    this->isHover = true;
    this->_updateScrollButtonVisibility();
}

void PipsPager::leaveEvent(QEvent *event)
{
    QListWidget::leaveEvent(event);
    this->isHover = false;
    this->delegate->setHoveredRow(-1);
    this->_updateScrollButtonVisibility();
}


void PipsPager::_updateScrollButtonVisibility()
{
    this->preButton->setVisible(this->isPreviousButtonVisible());
    this->nextButton->setVisible(this->isNextButtonVisible());
}


void PipsPager::wheelEvent(QWheelEvent *e)
{

}

void PipsPager::resizeEvent(QResizeEvent *event) 
{
    int w = this->width();
    int h = this->height();
    int bw = this->preButton->width();
    int bh = this->preButton->height();

    if(this->isHorizontal()){
        this->preButton->move(0, h / 2 - bh / 2);
        this->nextButton->move(w - bw, h / 2 - bh / 2);
    }else{
        this->preButton->move(w / 2 - bw / 2, 0);
        this->nextButton->move(w / 2 - bw / 2, h - bh);
    }
}


HorizontalPipsPager::HorizontalPipsPager(QWidget *parent) : PipsPager(Qt::Horizontal, parent)
{

}


VerticalPipsPager::VerticalPipsPager(QWidget *parent) : PipsPager(Qt::Vertical, parent)
{

}