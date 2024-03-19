#include "teaching_tip.h"


TeachTipBubble::TeachTipBubble(FlyoutViewBase *view, TeachingTipTailPosition tailPosition, QWidget *parent) : QWidget(parent)
{
    this->manager = TeachingTipManager::make(tailPosition);
    this->hBoxLayout = new QHBoxLayout(this);
    this->view = view;

    this->manager->doLayout(this);
    this->hBoxLayout->addWidget(this->view);
}

void TeachTipBubble::setView(FlyoutViewBase *view)
{
    this->hBoxLayout->removeWidget(this->view);
    this->view->deleteLater();
    this->view = view;
    this->hBoxLayout->addWidget(view);
}

void TeachTipBubble::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    painter.setBrush(isDarkTheme() ? QColor(40, 40, 40) : QColor(248, 248, 248));
    painter.setPen(isDarkTheme() ? QColor(23, 23, 23) : QColor(0, 0, 0, 17));

    this->manager->draw(this, &painter);
}


TeachingTip::TeachingTip(FlyoutViewBase *view, QWidget *target, int duration, TeachingTipTailPosition tailPosition, QWidget *parent, bool isDeleteOnClose) : QWidget(parent)
{
    this->target = target;
    this->duration = duration;
    this->isDeleteOnClose = isDeleteOnClose;
    this->manager = TeachingTipManager::make(tailPosition);

    this->hBoxLayout = new QHBoxLayout(this);
    this->opacityAni = new QPropertyAnimation(this, "windowOpacity", this);

    this->bubble = new TeachTipBubble(view, tailPosition, this);

    this->hBoxLayout->setContentsMargins(15, 8, 15, 20);
    this->hBoxLayout->addWidget(this->bubble);
    this->setShadowEffect(35, std::tuple<int,int>(0, 8));

    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);

    if(parent != nullptr && parent->window() != nullptr){
        parent->window()->installEventFilter(this);
    }
}


void TeachingTip::setShadowEffect(int blurRadius, std::tuple<int, int> offset)
{
    QColor color = QColor(0, 0, 0, isDarkTheme() ? 80 : 30);
    this->shadowEffect = new QGraphicsDropShadowEffect(this->bubble);
    this->shadowEffect->setBlurRadius(blurRadius);
    this->shadowEffect->setOffset(std::get<0>(offset), std::get<1>(offset));
    this->shadowEffect->setColor(color);
    this->bubble->setGraphicsEffect(nullptr);
    this->bubble->setGraphicsEffect(this->shadowEffect);
}

void TeachingTip::_fadeOut()
{
    this->opacityAni->setDuration(167);
    this->opacityAni->setStartValue(1);
    this->opacityAni->setEndValue(0);
    connect(this->opacityAni, &QPropertyAnimation::finished, this, &TeachingTip::close);
    this->opacityAni->start();
}


void TeachingTip::showEvent(QShowEvent *event)
{
    if(this->duration >= 0){
        QTimer::singleShot(this->duration, this, &TeachingTip::_fadeOut);
    }

    this->move(this->manager->position(this));
    this->opacityAni->setDuration(167);
    this->opacityAni->setStartValue(0);
    this->opacityAni->setEndValue(1);
    this->opacityAni->start();
    QWidget::showEvent(event);
}

void TeachingTip::closeEvent(QCloseEvent *event)
{
    if(this->isDeleteOnClose){
        this->deleteLater();
    }

    QWidget::closeEvent(event);
}

bool TeachingTip::eventFilter(QObject *watched, QEvent *event)
{
    if(this->parent() != nullptr && watched == ((QWidget*)this->parent())->window()){
        if(event->type() == QEvent::Resize || event->type() == QEvent::WindowStateChange || event->type() == QEvent::Move){
            this->move(this->manager->position(this));
        }
    }

    return QWidget::eventFilter(watched, event);
}

void TeachingTip::addWidget(QWidget *widget, int stretch, Qt::AlignmentFlag align)
{
    //this->getView()->addSpacing(8); //TODO:找不到addSpacing方法
    this->getView()->addWidget(widget, stretch, align);
}


FlyoutViewBase *TeachingTip::getView()
{
    return this->bubble->view;
}


void TeachingTip::setView(FlyoutViewBase *view)
{
    this->bubble->setView(view);
}


TeachingTip *TeachingTip::make(FlyoutViewBase *view, QWidget *target, int duration, TeachingTipTailPosition tailPosition, QWidget *parent, bool isDeleteOnClose)
{
    TeachingTip *w = new TeachingTip(view, target, duration, tailPosition, parent, isDeleteOnClose);
    w->show();
    return w;
}


TeachingTip *TeachingTip::create(QWidget *target, QString title, QString content, QVariant *icon, QVariant *image, bool isClosable, int duration, TeachingTipTailPosition tailPostion, QWidget *parent, bool isDeleteOnClose)
{
    TeachingTipView *view = new TeachingTipView(title, content, icon, image, isClosable, tailPostion, nullptr);
    TeachingTip *w = TeachingTip::make(view, target, duration, tailPostion, parent, isDeleteOnClose);
    connect(view, &TeachingTipView::closed, w, &TeachingTip::close);
    return w;
}


PopupTeachingTip::PopupTeachingTip(FlyoutViewBase *view, QWidget *target, int duration, TeachingTipTailPosition tailPosition, QWidget *parent, bool isDeleteOnClose) : TeachingTip(view, target, duration, tailPosition, parent, isDeleteOnClose)
{
    this->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
}


TeachingTipManager::TeachingTipManager() : QObject()
{

}

void TeachingTipManager::doLayout(TeachTipBubble *tip)
{
    tip->hBoxLayout->setContentsMargins(0, 0, 0, 0);
}

ImagePosition TeachingTipManager::imagePosition()
{
    return ImagePosition::TOP;
}

QPoint TeachingTipManager::position(TeachingTip *tip)
{
    QPoint pos = this->_pos(tip);
    int x = pos.x();
    int y = pos.y();

    QRect rect = QApplication::screenAt(QCursor::pos())->availableGeometry();
    x = qMax(rect.left(), qMin(pos.x(), rect.right() - tip->width() - 4));
    y = qMax(rect.top(), qMin(pos.y(), rect.bottom() - tip->height() - 4));
    return QPoint(x, y);
}

void TeachingTipManager::draw(TeachTipBubble *tip, QPainter *painter)
{
    QRect rect = tip->rect().adjusted(1, 1, -1, -1);
    painter->drawRoundedRect(rect, 8, 8);
}

QPoint TeachingTipManager::_pos(TeachingTip *tip)
{
    return tip->pos();
}

TeachingTipManager *TeachingTipManager::make(TeachingTipTailPosition position)
{
    switch (position)
    {
    case TeachingTipTailPosition::TOP:
        return new TopTailTeachingTipManager();
        break;
    case TeachingTipTailPosition::BOTTOM:
        return new BottomTailTeachingTipManager();
        break;
    case TeachingTipTailPosition::LEFT:
        return new LeftTailTeachingTipManager();
        break;
    case TeachingTipTailPosition::RIGHT:
        return new RightTailTeachingTipManager();
        break;
    case TeachingTipTailPosition::TOP_RIGHT:
        return new TopRightTailTeachingTipManager();
        break;
    case TeachingTipTailPosition::BOTTOM_RIGHT:
        return new BottomRightTailTeachingTipManager();
        break;
    case TeachingTipTailPosition::TOP_LEFT:
        return new TopLeftTailTeachingTipManager();
        break;
    case TeachingTipTailPosition::BOTTOM_LEFT:
        return new BottomLeftTailTeachingTipManager();
        break;
    case TeachingTipTailPosition::LEFT_TOP:
        return new LeftTopTailTeachingTipManager();
        break;
    case TeachingTipTailPosition::LEFT_BOTTOM:
        return new LeftBottomTailTeachingTipManager();
        break;
    case TeachingTipTailPosition::RIGHT_TOP:
        return new RightTopTailTeachingTipManager();
        break;
    case TeachingTipTailPosition::RIGHT_BOTTOM:
        return new RightBottomTailTeachingTipManager();
        break;
    case TeachingTipTailPosition::NONE:
        return new TeachingTipManager();
        break;
    default:
        return nullptr;
        break;
    }
}


TopTailTeachingTipManager::TopTailTeachingTipManager() : TeachingTipManager()
{

}

void TopTailTeachingTipManager::doLayout(TeachTipBubble *tip)
{
    tip->hBoxLayout->setContentsMargins(0, 8, 0, 0);
}

ImagePosition TopTailTeachingTipManager::imagePosition()
{
    return ImagePosition::BOTTOM;
}

void TopTailTeachingTipManager::draw(TeachTipBubble *tip, QPainter *painter)
{
    int w = tip->width();
    int h = tip->height();
    int pt = tip->hBoxLayout->contentsMargins().top();

    QPainterPath path = QPainterPath();
    path.addRoundedRect(1, pt, w - 2, h - pt - 1, 8, 8);
    QVector<QPointF> v = QVector<QPointF>();
    v.append(QPointF(w / 2 - 7, pt));
    v.append(QPointF(w / 2, 1));
    v.append(QPointF(w / 2 + 7, pt));
    path.addPolygon(QPolygonF(v));
    
    painter->drawPath(path.simplified());
}


QPoint TopTailTeachingTipManager::_pos(TeachingTip *tip)
{
    QWidget *target = tip->target;
    QPoint pos = target->mapToGlobal(QPoint(0, target->height()));
    int x = pos.x() + target->width() / 2 - tip->sizeHint().width() / 2;
    int y = pos.y() - tip->layout()->contentsMargins().top();
    return QPoint(x, y);
}


BottomTailTeachingTipManager::BottomTailTeachingTipManager() : TeachingTipManager()
{

}

void BottomTailTeachingTipManager::doLayout(TeachTipBubble *tip)
{
    tip->hBoxLayout->setContentsMargins(0, 0, 0, 8);
}

void BottomTailTeachingTipManager::draw(TeachTipBubble *tip, QPainter *painter)
{
    int w = tip->width();
    int h = tip->height();
    int pb = tip->hBoxLayout->contentsMargins().bottom();

    QPainterPath path = QPainterPath();
    path.addRoundedRect(1, 1, w - 2, h - pb - 1, 8, 8);
    QVector<QPointF> v = QVector<QPointF>();
    v.append(QPointF(w / 2 - 7, h = pb));
    v.append(QPointF(w / 2, h - 1));
    v.append(QPointF(w / 2 + 7, h - pb));
    path.addPolygon(QPolygonF(v));
    
    painter->drawPath(path.simplified());
}


QPoint BottomTailTeachingTipManager::_pos(TeachingTip *tip)
{
    QWidget *target = tip->target;
    QPoint pos = target->mapToGlobal(QPoint());
    int x = pos.x() + target->width() / 2 - tip->sizeHint().width() / 2;
    int y = pos.y() - tip->sizeHint().height() + tip->layout()->contentsMargins().bottom();
    return QPoint(x, y);
}


LeftTailTeachingTipManager::LeftTailTeachingTipManager() : TeachingTipManager()
{

}

void LeftTailTeachingTipManager::doLayout(TeachTipBubble *tip)
{
    tip->hBoxLayout->setContentsMargins(8, 0, 0, 0);
}

ImagePosition LeftTailTeachingTipManager::imagePosition()
{
    return ImagePosition::RIGHT;
}

void LeftTailTeachingTipManager::draw(TeachTipBubble *tip, QPainter *painter)
{
    int w = tip->width();
    int h = tip->height();
    int pl = 8;

    QPainterPath path = QPainterPath();
    path.addRoundedRect(pl, 1, w - pl - 2, h - 2, 8, 8);
    QVector<QPointF> v = QVector<QPointF>();
    v.append(QPointF(pl, h / 2 - 7));
    v.append(QPointF(1, h / 2));
    v.append(QPointF(pl, h / 2 + 7));
    path.addPolygon(QPolygonF(v));
    
    painter->drawPath(path.simplified());
}


QPoint LeftTailTeachingTipManager::_pos(TeachingTip *tip)
{
    QWidget *target = tip->target;
    QMargins m =  tip->layout()->contentsMargins();
    QPoint pos = target->mapToGlobal(QPoint(target->width(), 0));
    int x = pos.x() - m.left();
    int y = pos.y() - tip->getView()->sizeHint().height() / 2 + target->height() / 2 - m.top();
    return QPoint(x, y);
}



RightTailTeachingTipManager::RightTailTeachingTipManager() : TeachingTipManager()
{

}


void RightTailTeachingTipManager::doLayout(TeachTipBubble *tip)
{
    tip->hBoxLayout->setContentsMargins(0, 0, 8, 0);
}


ImagePosition RightTailTeachingTipManager::imagePosition()
{
    return ImagePosition::LEFT;
}


void RightTailTeachingTipManager::draw(TeachTipBubble *tip, QPainter *painter)
{
    int w = tip->width();
    int h = tip->height();
    int pr = 8;

    QPainterPath path = QPainterPath();
    path.addRoundedRect(1, 1, w - pr - 1, h - 2, 8, 8);
    QVector<QPointF> v = QVector<QPointF>();
    v.append(QPointF(w - pr, h / 2 - 7));
    v.append(QPointF(w - 1, h / 2));
    v.append(QPointF(w - pr, h / 2 + 7));
    path.addPolygon(QPolygonF(v));
    
    painter->drawPath(path.simplified());
}


QPoint RightTailTeachingTipManager::_pos(TeachingTip *tip)
{
    QWidget *target = tip->target;
    QMargins m =  tip->layout()->contentsMargins();
    QPoint pos = target->mapToGlobal(QPoint(0, 0));
    int x = pos.x() - tip->sizeHint().width() + m.right();
    int y = pos.y() - tip->getView()->sizeHint().height() / 2 + target->height() / 2 - m.top();
    return QPoint(x, y);
}


TopLeftTailTeachingTipManager::TopLeftTailTeachingTipManager() : TopTailTeachingTipManager()
{

}

void TopLeftTailTeachingTipManager::draw(TeachTipBubble *tip, QPainter *painter)
{
    int w = tip->width();
    int h = tip->height();
    int pt = tip->hBoxLayout->contentsMargins().top();

    QPainterPath path = QPainterPath();
    path.addRoundedRect(1, pt, w - 2, h - pt - 1, 8, 8);
    QVector<QPointF> v = QVector<QPointF>();
    v.append(QPointF(20, pt));
    v.append(QPointF(27, 1));
    v.append(QPointF(34, pt));
    path.addPolygon(QPolygonF(v));
    
    painter->drawPath(path.simplified());
}

QPoint TopLeftTailTeachingTipManager::_pos(TeachingTip *tip)
{
    QWidget *target = tip->target;
    QPoint pos = target->mapToGlobal(QPoint(0, target->height()));
    int x = pos.x() - tip->layout()->contentsMargins().left();
    int y = pos.y() - tip->layout()->contentsMargins().top();
    return QPoint(x, y);
}


TopRightTailTeachingTipManager::TopRightTailTeachingTipManager() : TopTailTeachingTipManager()
{

}


void TopRightTailTeachingTipManager::draw(TeachTipBubble *tip, QPainter *painter)
{
    int w = tip->width();
    int h = tip->height();
    int pt = tip->hBoxLayout->contentsMargins().top();

    QPainterPath path = QPainterPath();
    path.addRoundedRect(1, pt, w - 2, h - pt - 1, 8, 8);
    QVector<QPointF> v = QVector<QPointF>();
    v.append(QPointF(w - 20, pt));
    v.append(QPointF(w - 27, 1));
    v.append(QPointF(w - 34, pt));
    path.addPolygon(QPolygonF(v));
    
    painter->drawPath(path.simplified());
}


QPoint TopRightTailTeachingTipManager::_pos(TeachingTip *tip)
{
    QWidget *target = tip->target;
    QPoint pos = target->mapToGlobal(QPoint(target->width(), target->height()));
    int x = pos.x() - tip->sizeHint().width() + tip->layout()->contentsMargins().left();
    int y = pos.y() - tip->layout()->contentsMargins().top();
    return QPoint(x, y);
}


BottomLeftTailTeachingTipManager::BottomLeftTailTeachingTipManager() : BottomTailTeachingTipManager()
{

}

void BottomLeftTailTeachingTipManager::draw(TeachTipBubble *tip, QPainter *painter)
{
    int w = tip->width();
    int h = tip->height();
    int pb = tip->hBoxLayout->contentsMargins().bottom();

    QPainterPath path = QPainterPath();
    path.addRoundedRect(1, 1, w - 2, h - pb - 1, 8, 8);
    QVector<QPointF> v = QVector<QPointF>();
    v.append(QPointF(20, h - pb));
    v.append(QPointF(27, h - 1));
    v.append(QPointF(34, h - pb));
    path.addPolygon(QPolygonF(v));
    
    painter->drawPath(path.simplified());
}


QPoint BottomLeftTailTeachingTipManager::_pos(TeachingTip *tip)
{
    QWidget *target = tip->target;
    QPoint pos = target->mapToGlobal(QPoint());
    int x = pos.x() - tip->layout()->contentsMargins().left();
    int y = pos.y() - tip->sizeHint().height() + tip->layout()->contentsMargins().bottom();
    return QPoint(x, y);
}




BottomRightTailTeachingTipManager::BottomRightTailTeachingTipManager() : BottomTailTeachingTipManager()
{

}


void BottomRightTailTeachingTipManager::draw(TeachTipBubble *tip, QPainter *painter)
{
    int w = tip->width();
    int h = tip->height();
    int pb = tip->hBoxLayout->contentsMargins().bottom();

    QPainterPath path = QPainterPath();
    path.addRoundedRect(1, 1, w - 2, h - pb - 1, 8, 8);
    QVector<QPointF> v = QVector<QPointF>();
    v.append(QPointF(w - 20, h - pb));
    v.append(QPointF(w - 27, h - 1));
    v.append(QPointF(w - 34, h - pb));
    path.addPolygon(QPolygonF(v));
    
    painter->drawPath(path.simplified());
}


QPoint BottomRightTailTeachingTipManager::_pos(TeachingTip *tip)
{
    QWidget *target = tip->target;
    QPoint pos = target->mapToGlobal(QPoint(target->width(), 0));
    int x = pos.x() - tip->sizeHint().width() + tip->layout()->contentsMargins().left();
    int y = pos.y() - tip->sizeHint().height() + tip->layout()->contentsMargins().bottom();
    return QPoint(x, y);
}


LeftTopTailTeachingTipManager::LeftTopTailTeachingTipManager() : LeftTailTeachingTipManager()
{

}

ImagePosition LeftTopTailTeachingTipManager::imagePosition()
{
    return ImagePosition::BOTTOM;
}


void LeftTopTailTeachingTipManager::draw(TeachTipBubble *tip, QPainter *painter)
{
    int w = tip->width();
    int h = tip->height();
    int pl = 8;

    QPainterPath path = QPainterPath();
    path.addRoundedRect(pl, 1, w - pl - 2, h - 2, 8, 8);
    QVector<QPointF> v = QVector<QPointF>();
    v.append(QPointF(pl, 10));
    v.append(QPointF(1, 17));
    v.append(QPointF(pl, 24));
    path.addPolygon(QPolygonF(v));
    
    painter->drawPath(path.simplified());
}


QPoint LeftTopTailTeachingTipManager::_pos(TeachingTip *tip)
{
    QWidget *target = tip->target;
    QMargins m = tip->layout()->contentsMargins();
    QPoint pos = target->mapToGlobal(QPoint(target->width(), 0));
    int x = pos.x() - m.left();
    int y = pos.y() - m.top();
    return QPoint(x, y);
}


LeftBottomTailTeachingTipManager::LeftBottomTailTeachingTipManager() : LeftTailTeachingTipManager()
{

}


ImagePosition LeftBottomTailTeachingTipManager::imagePosition()
{
    return ImagePosition::TOP;
}

void LeftBottomTailTeachingTipManager::draw(TeachTipBubble *tip, QPainter *painter)
{
    int w = tip->width();
    int h = tip->height();
    int pl = 9;

    QPainterPath path = QPainterPath();
    path.addRoundedRect(pl, 1, w - pl - 1, h - 2, 8, 8);
    QVector<QPointF> v = QVector<QPointF>();
    v.append(QPointF(pl, h - 10));
    v.append(QPointF(1, h - 17));
    v.append(QPointF(pl, h - 24));
    path.addPolygon(QPolygonF(v));
    
    painter->drawPath(path.simplified());
}


QPoint LeftBottomTailTeachingTipManager::_pos(TeachingTip *tip)
{
    QWidget *target = tip->target;
    QMargins m = tip->layout()->contentsMargins();
    QPoint pos = target->mapToGlobal(QPoint(target->width(), target->height()));
    int x = pos.x() - m.left();
    int y = pos.y() - tip->sizeHint().height() + m.bottom();
    return QPoint(x, y);
}


RightTopTailTeachingTipManager::RightTopTailTeachingTipManager() : RightTailTeachingTipManager()
{

}


ImagePosition RightTopTailTeachingTipManager::imagePosition()
{
    return ImagePosition::BOTTOM;
}


void RightTopTailTeachingTipManager::draw(TeachTipBubble *tip, QPainter *painter)
{
    int w = tip->width();
    int h = tip->height();
    int pr = 8;

    QPainterPath path = QPainterPath();
    path.addRoundedRect(1, 1, w - pr - 1, h - 2, 8, 8);
    QVector<QPointF> v = QVector<QPointF>();
    v.append(QPointF(w - pr, 10));
    v.append(QPointF(w - 1, 17));
    v.append(QPointF(w - pr, 24));
    path.addPolygon(QPolygonF(v));
    
    painter->drawPath(path.simplified());
}


QPoint RightTopTailTeachingTipManager::_pos(TeachingTip *tip)
{
    QWidget *target = tip->target;
    QMargins m = tip->layout()->contentsMargins();
    QPoint pos = target->mapToGlobal(QPoint(0, 0));
    int x = pos.x() - tip->sizeHint().width() + m.right();
    int y = pos.y() - m.top();
    return QPoint(x, y);
}


RightBottomTailTeachingTipManager::RightBottomTailTeachingTipManager() : RightTailTeachingTipManager()
{

}

ImagePosition RightBottomTailTeachingTipManager::imagePosition()
{
    return ImagePosition::TOP;
}

void RightBottomTailTeachingTipManager::draw(TeachTipBubble *tip, QPainter *painter)
{
    int w = tip->width();
    int h = tip->height();
    int pr = 8;

    QPainterPath path = QPainterPath();
    path.addRoundedRect(1, 1, w - pr - 1, h - 2, 8, 8);
    QVector<QPointF> v = QVector<QPointF>();
    v.append(QPointF(w - pr, h - 10));
    v.append(QPointF(w - 1, h - 17));
    v.append(QPointF(w - pr, h - 24));
    path.addPolygon(QPolygonF(v));
    
    painter->drawPath(path.simplified());
}


QPoint RightBottomTailTeachingTipManager::_pos(TeachingTip *tip)
{
    QWidget *target = tip->target;
    QMargins m = tip->layout()->contentsMargins();
    QPoint pos = target->mapToGlobal(QPoint(0, target->height()));
    int x = pos.x() - tip->sizeHint().width() + m.right();
    int y = pos.y() - tip->sizeHint().height() + m.bottom();
    return QPoint(x, y);
}


TeachingTipView::TeachingTipView(QString title, QString content, QVariant *icon, QVariant *image, bool isClosable, TeachingTipTailPosition tailPosition, QWidget *parent) : FlyoutView(title, content, icon, image, isClosable, parent)
{
    this->manager = TeachingTipManager::make(tailPosition);
    this->hBoxLayout = new QHBoxLayout();
    this->hBoxLayout->setContentsMargins(0, 0, 0, 0);
}


void TeachingTipView::_adjustImage()
{
    if(this->manager->imagePosition() == ImagePosition::TOP || this->manager->imagePosition() == ImagePosition::BOTTOM){
        return FlyoutView::_adjustImage();
    }

    int h = this->vBoxLayout->sizeHint().height() - 2;
    this->imageLabel->scaledToHeight(h);
}

void TeachingTipView::_addImageToLayout()
{
    this->imageLabel->setHidden(this->imageLabel->isNull());
    ImagePosition pos = this->manager->imagePosition();

    if(pos == ImagePosition::TOP){
        this->imageLabel->setBorderRadius(8, 8, 0, 0);
        this->vBoxLayout->insertWidget(0, this->imageLabel);
    }else if(pos == ImagePosition::BOTTOM){
        this->imageLabel->setBorderRadius(0, 0, 8, 8);
        this->vBoxLayout->addWidget(this->imageLabel);
    }else if(pos == ImagePosition::LEFT){
        this->vBoxLayout->removeItem(this->vBoxLayout->itemAt(0));
        this->hBoxLayout->addLayout(this->viewLayout);
        this->vBoxLayout->addLayout(this->hBoxLayout);

        this->imageLabel->setBorderRadius(8, 0, 8, 0);
        this->hBoxLayout->insertWidget(0, this->imageLabel);
    }else if(pos == ImagePosition::RIGHT){
        this->vBoxLayout->removeItem(this->vBoxLayout->itemAt(0));
        this->hBoxLayout->addLayout(this->viewLayout);
        this->vBoxLayout->addLayout(this->hBoxLayout);

        this->imageLabel->setBorderRadius(0, 8, 0, 8);
        this->hBoxLayout->addWidget(this->imageLabel);
    }
}


void TeachingTipView::paintEvent(QPaintEvent *event)
{
    
}