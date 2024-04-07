#include "flip_view.h"

FlipScrollButton::FlipScrollButton(QWidget *parent) : ToolButton(parent)
{
    this->_postInit();
}

FlipScrollButton::FlipScrollButton(FluentIcon *icon, QWidget *parent) : ToolButton(icon, parent)
{
    this->_postInit();
}

FlipScrollButton::FlipScrollButton(SpinIcon *icon, QWidget *parent) : ToolButton(icon, parent)
{
    this->_postInit();
}

FlipScrollButton::FlipScrollButton(QIcon *icon, QWidget *parent) : ToolButton(icon, parent)
{
    this->_postInit();
}


FlipScrollButton::FlipScrollButton(QString icon, QWidget *parent) : ToolButton(icon, parent)
{
    this->_postInit();
}


void FlipScrollButton::_postInit()
{
    this->_opacity = 0;
    this->opacityAni = new QPropertyAnimation(this, "opacity", this);
    this->opacityAni->setDuration(150);
}


float FlipScrollButton::getOpacity()
{
    return this->_opacity;
}

void FlipScrollButton::setOpacity(float o)
{
    this->_opacity = o;
    this->update();
}

bool FlipScrollButton::isTransparent()
{
    return this->getOpacity() == 0;
}


void FlipScrollButton::fadeIn()
{
    this->opacityAni->setStartValue(this->getOpacity());
    this->opacityAni->setEndValue(1);
    this->opacityAni->start();
}

void FlipScrollButton::fadeOut()
{
    this->opacityAni->setStartValue(this->getOpacity());
    this->opacityAni->setEndValue(0);
    this->opacityAni->start();
}

void FlipScrollButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setOpacity(this->getOpacity());

    if(!isDarkTheme()){
        painter.setBrush(QColor(252, 252, 252, 217));
    }else{
        painter.setBrush(QColor(44, 44, 44, 245));
    }

    painter.drawRoundedRect(this->rect(), 4, 4);

    QColor color;
    float opacity;
    if(isDarkTheme()){
        color = QColor(255, 255, 255);
        opacity = this->isHover || this->isPressed ? 0.773 : 0.541;
    }else{
        color = QColor(0, 0, 0);
        opacity = this->isHover || this->isPressed ? 0.616 : 0.45;
    }

    painter.setOpacity(this->getOpacity() * opacity);

    int s = this->isPressed ? 6 : 8;
    int w = this->width();
    int h = this->height();
    float x = (w - s) / 2;
    float y = (h - s) / 2;
    std::map<QString, QString> attributes;
    attributes[QString("fill")] = color.name();
    MIcon().drawIcon(this->_icon, &painter, QRect(x, y, s, s), &attributes, QIcon::State::Off);
}


FlipImageDelegate::FlipImageDelegate(QWidget *parent) : QStyledItemDelegate(parent)
{
    this->borderRadius = 0;
}

QSize FlipImageDelegate::itemSize(int index) const
{
    FlipView *p = (FlipView *)this->parent();
    return p->item(index)->sizeHint();
}


void FlipImageDelegate::setBorderRadius(int radius)
{
    this->borderRadius = radius;
    ((FlipView *)this->parent())->viewport()->update(); //TODO:需要确认下类型
}


void FlipImageDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();
    painter->setRenderHints(QPainter::Antialiasing);
    painter->setPen(Qt::NoPen);

    QSize size = this->itemSize(index.row());
    FlipView *p = (FlipView *)this->parent();

    float r = p->devicePixelRatioF();
    QImage image = index.data(Qt::UserRole).value<QImage>();
    if(image.isNull()){
        return painter->restore();
    }

    int x = option.rect.x() + (option.rect.width() - size.width()) / 2;
    int y = option.rect.y() + (option.rect.height() - size.height()) / 2;
    QRectF rect = QRectF(x, y, size.width(), size.height());

    QPainterPath path = QPainterPath();
    path.addRoundedRect(rect, this->borderRadius, this->borderRadius);

    image = image.scaled(size *r, p->getAspectRatioMode(), Qt::SmoothTransformation);
    painter->setClipPath(path);

    if(p->getAspectRatioMode() == Qt::AspectRatioMode::KeepAspectRatioByExpanding){
        int iw = image.width();
        int ih = image.height();
        x = (iw - size.width()) / 2;
        y = (ih - size.height()) / 2;
        image = image.copy(x, y, size.width(), size.height());
    }

    painter->drawImage(rect, image);
    painter->restore();
}


FlipView::FlipView(QWidget *parent) : QListWidget(parent)
{
    this->orientation = Qt::Horizontal;
    this->_postInit();
}

FlipView::FlipView(Qt::Orientation orientation, QWidget *parent) : QListWidget(parent)
{
    this->orientation = orientation;
    this->_postInit();
}


void FlipView::_postInit()
{
    this->isHover = false;
    this->_currentIndex = -1;
    this->_aspectRatioMode = Qt::AspectRatioMode::IgnoreAspectRatio;
    this->_itemSize = QSize(480, 270);

    this->delegate = new FlipImageDelegate(this);
    this->scrollBar = new SmoothScrollBar(this->orientation, this);

    this->scrollBar->setScrollAnimation(500, QEasingCurve::OutCubic);
    this->scrollBar->setForceHidden(true);

    this->setMinimumSize(this->getItemSize());
    this->setItemDelegate(this->delegate);
    this->setMovement(QListWidget::Static);
    this->setVerticalScrollMode(this->ScrollPerPixel);
    this->setHorizontalScrollMode(this->ScrollPerPixel);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("FLIP_VIEW"), Theme::AUTO);

    if(this->isHorizontal()){
        this->setFlow(QListWidget::LeftToRight);

        FluentIcon *preIcon = new FluentIcon();
        preIcon->setIconName(QString("CARE_LEFT_SOLID"));
        this->preButton = new FlipScrollButton(preIcon, this);

        FluentIcon *nextIcon = new FluentIcon();
        nextIcon->setIconName(QString("CARE_RIGHT_SOLID"));
        this->nextButton = new FlipScrollButton(nextIcon, this);
        this->preButton->setFixedSize(16, 38);
        this->nextButton->setFixedSize(16, 38);
    }else{
        FluentIcon *preIcon = new FluentIcon();
        preIcon->setIconName(QString("CARE_UP_SOLID"));
        this->preButton = new FlipScrollButton(preIcon, this);

        FluentIcon *nextIcon = new FluentIcon();
        nextIcon->setIconName(QString("CARE_DOWN_SOLID"));
        this->nextButton = new FlipScrollButton(nextIcon, this);

        this->preButton->setFixedSize(38, 16);
        this->nextButton->setFixedSize(38, 16);
    }

    connect(this->preButton, &FlipScrollButton::clicked, this, &FlipView::scrollPrevious);
    connect(this->nextButton, &FlipScrollButton::clicked, this, &FlipView::scrollNext);
}


bool FlipView::isHorizontal()
{
    return this->orientation == Qt::Horizontal;
}


void FlipView::setItemSize(QSize size)
{
    if(size == this->getItemSize()){
        return;
    }

    this->_itemSize = size;

    for(int i = 0; i < this->count(); i++){
        this->_adjustItemSize(this->item(i));
    }

    this->viewport()->update();
}


QSize FlipView::getItemSize()
{
    return this->_itemSize;
}

void FlipView::setBorderRadius(int radius)
{
    this->delegate->setBorderRadius(radius);
}


int FlipView::getBorderRadius()
{
    return this->delegate->borderRadius;
}


void FlipView::scrollPrevious()
{
    this->setCurrentIndex(this->currentIndex() - 1);
}

void FlipView::scrollNext()
{
    this->setCurrentIndex(this->currentIndex() + 1);
}


void FlipView::setCurrentIndex(int index)
{
    if(!(index >= 0 && index < this->count()) || index == this->currentIndex()){
        return;
    }

    this->scrollToIndex(index);

    if(index == 0){
        this->preButton->fadeOut();
    }else if(this->preButton->isTransparent() && this->isHover){
        this->preButton->fadeIn();
    }

    if(index == this->count() - 1){
        this->nextButton->fadeOut();
    }else if(this->nextButton->isTransparent() && this->isHover){
        this->nextButton->fadeIn();
    }

    emit(this->currentIndexChanged(index));
}



void FlipView::scrollToIndex(int index)
{
    if(!(index >=0 && index < this->count())){
        return;
    }

    this->_currentIndex = index;

    int value = 0;
    if(this->isHorizontal()){
        for(int i = 0; i < index; i++){
            value += this->item(i)->sizeHint().width();
        }
    }else{
        for(int i = 0; i < index; i++){
            value += this->item(i)->sizeHint().height();
        }
    }

    value += (2 * index + 1) * this->spacing();
    this->scrollBar->scrollTo(value, true);
}


int FlipView::currentIndex()
{
    return this->_currentIndex;
}

QImage FlipView::image(int index)
{
    if(!(index >= 0 && index < this->count())){
        return QImage();
    }

    return this->item(index)->data(Qt::UserRole).value<QImage>();
}


void FlipView::addImage(QVariant *image)
{
    QList<QVariant*> list = QList<QVariant*>();
    list.append(image);
    this->addImages(list);
}

void FlipView::addImages(QList<QVariant*> images)
{
    if(images.isEmpty()){
        return;
    }

    int N = this->count();
    QStringList list = QStringList();
    for(int i = 0; i < images.length(); i++){
        list.append(QString(""));
    }
    this->addItems(list);

    for(int i = N; i < this->count(); i++){
        this->setItemImage(i, images.at(i - N));
    }

    if(this->currentIndex() < 0){
        this->_currentIndex = 0;
    }
}


void FlipView::setItemImage(int index, QVariant *image)
{
    if(!(index >= 0 && index < this->count())){
        return;
    }

    QListWidgetItem *item = this->item(index);

    QImage _image;
    if(image->canConvert<QString>()){
        _image = QImage(image->value<QString>());
    }else if(image->canConvert<QPixmap>()){
        _image = image->value<QPixmap>().toImage();
    }else{
        _image = image->value<QImage>();
    }

    item->setData(Qt::UserRole, QVariant::fromValue<QImage>(_image));
    this->_adjustItemSize(item);
}


void FlipView::_adjustItemSize(QListWidgetItem *item)
{
    QImage image = this->itemImage(this->row(item));

    int h, w;
    if(this->_aspectRatioMode == Qt::AspectRatioMode::KeepAspectRatio){
        if(this->isHorizontal()){
            h = this->getItemSize().height();
            w = image.width() * h / image.height();
        }else{
            w = this->getItemSize().width();
            h = image.height() * w / image.width();
        }
    }else{
        w = this->getItemSize().width();
        h = this->getItemSize().height();
    }

    item->setSizeHint(QSize(w, h));
}


QImage FlipView::itemImage(int index)
{
    if(!(index >= 0 && index < this->count())){
        return QImage();
    }

    QListWidgetItem *item = this->item(index);
    return item->data(Qt::UserRole).isValid() ? item->data(Qt::UserRole).value<QImage>() : QImage();
}


void FlipView::resizeEvent(QResizeEvent *event)
{
    int w = this->width();
    int h = this->height();
    int bw = this->preButton->width();
    int bh = this->preButton->height();

    if(this->isHorizontal()){
        this->preButton->move(2, h / 2 - bh / 2);
        this->nextButton->move(w - bw - 2, h / 2 - bh / 2);
    }else{
        this->preButton->move(w / 2 - bw / 2, 2);
        this->nextButton->move(w / 2 - bw / 2, h - bh - 2);
    }
}



void FlipView::enterEvent(QEvent *event)
{
    QListWidget::enterEvent(event);
    this->isHover = true;

    if(this->currentIndex() > 0){
        this->preButton->fadeIn();
    }

    
    if(this->currentIndex() < this->count() - 1){
        this->nextButton->fadeIn();
    }
    
}


void FlipView::leaveEvent(QEvent *event)
{
    QListWidget::leaveEvent(event);
    this->isHover = false;
    this->preButton->fadeOut();
    this->nextButton->fadeOut();
}


void FlipView::showEvent(QShowEvent *event)
{
    this->scrollBar->duration = 0;
    this->scrollToIndex(this->currentIndex());
    this->scrollBar->duration = 500;
}


void FlipView::wheelEvent(QWheelEvent *e)
{
    e->setAccepted(true);
    if(this->scrollBar->ani->state() == QPropertyAnimation::Running){
        return;
    }

    if(e->angleDelta().y() < 0){
        this->scrollNext();
    }else{
        this->scrollPrevious();
    }
}


Qt::AspectRatioMode FlipView::getAspectRatioMode()
{
    return this->_aspectRatioMode;
}


void FlipView::setAspectRatioMode(Qt::AspectRatioMode mode)
{
    if(mode == this->_aspectRatioMode){
        return;
    }

    this->_aspectRatioMode = mode;

    for(int i = 0; i < this->count(); i++){
        this->_adjustItemSize(this->item(i));
    }

    this->viewport()->update();
}


HorizontalFlipView::HorizontalFlipView(QWidget *parent) : FlipView(Qt::Horizontal, parent)
{

}


VerticalFlipView::VerticalFlipView(QWidget *parent) : FlipView(Qt::Vertical, parent)
{

}