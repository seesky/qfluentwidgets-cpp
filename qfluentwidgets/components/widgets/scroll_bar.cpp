#include "scroll_bar.h"


/*
void MQAbstractScrollArea::setVerticalScrollBarPolicy(Qt::ScrollBarPolicy policy)
{
    ((QAbstractScrollArea *)this->parent())->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    s->vScrollBar->setForceHidden(policy == Qt::ScrollBarAlwaysOff);
}

void MQAbstractScrollArea::setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy policy)
{
    ((QAbstractScrollArea *)this->parent())->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    s->vScrollBar->setForceHidden(policy == Qt::ScrollBarAlwaysOff);
}
*/


ArrowButton::ArrowButton(FluentIcon *icon, QWidget *parent) : QToolButton(parent)
{
    this->setFixedSize(10, 10);
    this->_icon = icon;
}

void ArrowButton::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    float s = isDown() ? 7 : 8;
    float x = (this->width() - s) / 2;
    QColor color = (new QColor("#858789"))->name();
    //QColor color = (QColor("#858789")).name();
    std::map<QString, QString> attributes = {
        {"fill", color.name()}
    };
    this->_icon->render(&painter, QRect(x, x, s, s), Theme::AUTO, 0, &attributes);

}


ScrollBarGroove::ScrollBarGroove(Qt::Orientation orient, QWidget *parent) : QWidget(parent)
{
    if(orient == Qt::Vertical)
    {
        this->setFixedWidth(12);
        FluentIcon *upButtonIcon = new FluentIcon();
        upButtonIcon->setIconName("CARE_UP_SOLID");
        this->upButton = new ArrowButton(upButtonIcon, this);
        FluentIcon *downButtonIcon = new FluentIcon();
        downButtonIcon->setIconName("CARE_DOWN_SOLID");
        this->downButton = new ArrowButton(downButtonIcon, this);
        QVBoxLayout *layout = new QVBoxLayout(this);
        setLayout(layout);
        layout->addWidget(this->upButton, 0, Qt::AlignHCenter);
        layout->addStretch(1);
        layout->addWidget(this->downButton, 0, Qt::AlignHCenter);
        layout->setContentsMargins(0, 3, 0, 3);
        //this->setLayout(layout);
    }else{
        setFixedHeight(12);
        FluentIcon *upButtonIcon = new FluentIcon();
        upButtonIcon->setIconName("CARE_LEFT_SOLID");
        this->upButton = new ArrowButton(upButtonIcon, this);
        FluentIcon *downButtonIcon = new FluentIcon();
        downButtonIcon->setIconName("CARE_RIGHT_SOLID");
        this->downButton = new ArrowButton(downButtonIcon, this);
        QHBoxLayout *layout = new QHBoxLayout(this);
        setLayout(layout);
        layout->addWidget(this->upButton, 0, Qt::AlignVCenter);
        layout->addStretch(1);
        layout->addWidget(this->downButton, 0, Qt::AlignVCenter);
        layout->setContentsMargins(3, 0, 3, 0);
    }

    this->opacityEffect = new QGraphicsOpacityEffect(this);
    this->opacityAni = new QPropertyAnimation(this->opacityEffect, QString("opacity").toUtf8(), this);
    this->setGraphicsEffect(this->opacityEffect);
    this->opacityEffect->setOpacity(0);
}


void ScrollBarGroove::fadeIn()
{
    this->opacityAni->setEndValue(1);
    this->opacityAni->setDuration(150);
    this->opacityAni->start();
}

void ScrollBarGroove::fadeOut()
{
    this->opacityAni->setEndValue(0);
    this->opacityAni->setDuration(150);
    this->opacityAni->start();
}

void ScrollBarGroove::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    if(!isDarkTheme())
    {
        painter.setBrush(QColor(252, 252, 252, 217));
    }else{
        painter.setBrush(QColor(44, 44, 44, 245));
    }

    painter.drawRoundedRect(this->rect(), 6, 6);

    painter.end();
}


ScrollBarHandle::ScrollBarHandle(Qt::Orientation orient, QWidget *parent) : QWidget(parent)
{
    this->orient = orient;
    if(orient == Qt::Vertical){
        this->setFixedWidth(3);
    }else{
        this->setFixedHeight(3);
    }
}

void ScrollBarHandle::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    float r = this->orient == Qt::Vertical ? width() / 2 : height() / 2;
    QColor c = isDarkTheme() ? QColor(255, 255, 255, 139) : QColor(0, 0, 0, 114);
    painter.setBrush(c);
    painter.drawRoundedRect(this->rect(), r, r);
    painter.end();
}

ScrollBar::ScrollBar(Qt::Orientation orient, QAbstractScrollArea *parent) : QWidget(parent)
{
    this->groove = new ScrollBarGroove(orient, this);
    this->handle = new ScrollBarHandle(orient, this);
    this->timer = new QTimer(this);

    this->_orientation = orient;
    this->_singleStep = 1;
    this->_pageStep = 50;
    this->_padding = 14;

    this->_minimum = 0;
    this->_maximum = 0;
    this->_value = 0;

    this->_isPressed = false;
    this->_isEnter = false;
    this->_isExpanded = false;
    this->_pressedPos =  QPoint();
    this->_isForceHidden = false;

    if(orient == Qt::Vertical)  //TODO:这里之前有个一个bug，当不执行setvisible方法的时候，在界面上会出现一个方框
    {
        this->partnerBar = parent->verticalScrollBar();

        parent->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        //parent->setVisible(false);
        //QAbstractScrollArea *asa = new QAbstractScrollArea(parent);
        //asa->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        //asa->setVisible(false);
    }else{
        this->partnerBar = parent->horizontalScrollBar();
        //QAbstractScrollArea *asa = new QAbstractScrollArea(parent);
        //asa->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        //asa->setVisible(false);
        parent->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        //parent->setVisible(false);
    }

    this->__initWidget(parent);
}

void ScrollBar::__initWidget(QWidget *parent)
{
    //connect(this->groove->upButton, SIGNAL(QToolButton::clicked), SLOT(this->_onPageUp()));
    connect(this->groove->upButton, &ArrowButton::clicked, this, &ScrollBar::_onPageUp);

    //connect(this->groove->downButton, SIGNAL(QToolButton::clicked), SLOT(this->_onPageDown()));

    connect(this->groove->downButton, &ArrowButton::clicked, this, &ScrollBar::_onPageDown);

    //connect(this->groove->opacityAni, SIGNAL(QPropertyAnimation::valueChanged), SLOT(this->_onOpacityAniValueChanged()));
    connect(this->groove->opacityAni, &QPropertyAnimation::valueChanged, this, &ScrollBar::_onOpacityAniValueChanged);

    //connect(this->partnerBar, SIGNAL(QScrollBar::rangeChanged), SLOT(this->setRange));
    connect(this->partnerBar, &QScrollBar::rangeChanged, this, &ScrollBar::setRange);

    //connect(this->partnerBar, SIGNAL(QScrollBar::valueChanged), SLOT(this->_onValueChanged));
    connect(this->partnerBar, &QScrollBar::valueChanged, this, &ScrollBar::_onValueChanged);
    //connect(this, SIGNAL(this->valueChanged()), SLOT(this->partnerBar->setValue())); //TODO:这个地方需要重点关注是否正确
    connect(this, &ScrollBar::valueChanged, this->partnerBar, &QScrollBar::setValue); //TODO:这个地方需要重点关注是否正确
    parent->installEventFilter(this);

    this->setRange(this->partnerBar->minimum(), this->partnerBar->maximum());
    this->setVisible(this->maximum() > 0 && !this->_isForceHidden);
    this->_adjustPos(((QWidget *)this->parent())->size());
}

void ScrollBar::_onPageUp()
{
    this->setValue(this->value() - this->pageStep());
}

void ScrollBar::_onPageDown()
{
    this->setValue(this->value() + this->pageStep());
}

void ScrollBar::_onValueChanged(int value)
{
    this->val = value;
}

int ScrollBar::value()
{
    return this->_value;
}

//TODO:@pyqtProperty(int, notify=valueChanged)
int ScrollBar::getVal()
{
    return this->_value;
}

void ScrollBar::setVal(int value)
{
    if(value == this->value())
    {
        return;
    }
    value = qMax(this->minimum(), qMin(value, this->maximum()));
    this->_value = value;
    emit(this->valueChanged(value));
    this->_adjustHandlePos();
}

int ScrollBar::minimum()
{
    return this->_minimum;
}

int ScrollBar::maximum()
{
    return this->_maximum;
}

Qt::Orientation ScrollBar::orientation()
{
    return this->_orientation;
}

int ScrollBar::pageStep()
{
    return this->_pageStep;
}

int ScrollBar::singleStep()
{
    return this->_singleStep;
}

bool ScrollBar::isSliderDown()
{
    return this->_isPressed;
}

void ScrollBar::setValue(int value)
{
    this->val = value;
}

void ScrollBar::setMinimum(int min)
{
    if(min == this->minimum())
    {
        return;
    }

    this->_minimum = min;
    emit(this->rangeChanged(std::tuple<int,int>(min, this->maximum())));
}

void ScrollBar::setMaximum(int max)
{
    if(max == this->maximum())
    {
        return;
    }
    this->_maximum = max;
    emit(this->rangeChanged(std::tuple<int,int>(this->minimum(), max)));
}

void ScrollBar::setRange(int min, int max)
{
    if(min > max || (min == this->minimum() && max == this->maximum()))
    {
        return;
    }
    this->setMinimum(min);
    this->setMaximum(max);
    this->_adjustHandleSize();
    this->_adjustHandlePos();
    this->setVisible(max > 0 && !this->_isForceHidden);
    emit(this->rangeChanged(std::tuple<int, int>(min, max)));
}

void ScrollBar::setPageStep(int step)
{
    if(step >= 1){
        this->_pageStep = step;
    }
}

void ScrollBar::setSingleStep(int step)
{
    if(step >= 1){
        this->_singleStep = step;
    }
}

void ScrollBar::setSliderDown(bool isDown)
{
    this->_isPressed = true;
    if(isDown)
    {
        emit(this->sliderPressed());
    }else{
        emit(this->sliderReleased());       
    }
}

void ScrollBar::expand()
{
    if(this->_isExpanded || !this->_isEnter)
    {
        return;
    }
    this->_isExpanded = true;
    this->groove->fadeIn();
}

void ScrollBar::collapse()
{
    if(!this->_isExpanded || this->_isEnter)
    {
        return;
    }
    this->_isExpanded = false;
    this->groove->fadeOut();
}

void ScrollBar::enterEvent(QEvent *event)
{
    this->_isEnter = true;
    this->timer->stop();
    this->timer->singleShot(200, this, &ScrollBar::expand); //TODO:重点关注
}

void ScrollBar::leaveEvent(QEvent *event)
{
    this->_isEnter = false;
    this->timer->stop();
    this->timer->singleShot(200, this, &ScrollBar::collapse); //TODO:重点关注
}


bool ScrollBar::eventFilter(QObject *watched, QEvent *event)
{
    if(watched != this->parent())
    {
        return QWidget::eventFilter(watched, event);
    }

    if(event->type() == QEvent::Resize)
    {
        this->_adjustPos(((QResizeEvent *)event)->size());
    }

    return QWidget::eventFilter(watched, event);
}

void ScrollBar::resizeEvent(QResizeEvent *event)
{
    this->groove->resize(this->size());
}

void ScrollBar::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    this->_isPressed = true;
    this->_pressedPos = (event->pos());

    //TODO:if self.childAt(e.pos()) is self.handle or not self._isSlideResion(e.pos()):
    if(this->childAt(event->pos()) == this->handle || !this->_isSlideResion(event->pos())){
        return;
    }

    int value;
    if(this->orientation() == Qt::Vertical)
    {
        
        if(event->pos().y() > this->handle->geometry().bottom())
        {
            value = event->pos().y() - this->handle->height() - this->_padding;
        }else{
            value = event->pos().y() - this->_padding;
        }
    }else{
        if(event->pos().x() > this->handle->geometry().right())
        {
            value = event->pos().x() - this->handle->width() - this->_padding;
        }else{
            value = event->pos().x() - this->_padding;
        }
    }

    this->setValue(int(value / qMax(this->_slideLength(), 1) * this->maximum()));
    emit(this->sliderPressed()); 

}

void ScrollBar::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
    this->_isPressed = false;
    emit(this->sliderReleased());
}

void ScrollBar::mouseMoveEvent(QMouseEvent *event)
{
    int dv;
    if(this->orientation() == Qt::Vertical)
    {
        dv = event->pos().y() - this->_pressedPos.y();
    }else{
        dv = event->pos().x() - this->_pressedPos.x();
    }

    dv = int(dv / qMax(this->_slideLength(), 1) * (this->maximum() - this->minimum()));
    //ScrollBar::setValue(this->value() + dv);
    this->setValue(this->value() + dv);
    emit(this->sliderMoved());
}

void ScrollBar::_adjustPos(QSize size)
{
    if(this->orientation() == Qt::Vertical)
    {
        this->resize(12, size.height() - 2);
        this->move(size.width() - 13, 1);
    }else{
        this->resize(size.width() - 2, 12);
        this->move(1, size.height() - 13);
    }
}

void ScrollBar::_adjustHandleSize()
{
    QWidget *p = (QWidget *)this->parent();
    if(this->orientation() == Qt::Vertical)
    {
        int total = this->maximum() - this->minimum() + p->height();
        int s = int(this->_grooveLength() * p->height() / qMax(total, 1));
        this->handle->setFixedHeight(qMax(30, s));
    }else{
        int total = this->maximum() - this->minimum() + p->width();
        int s = int(this->_grooveLength() * p->width() / qMax(total, 1));
        this->handle->setFixedWidth(qMax(30, s));
    }
}

void ScrollBar::_adjustHandlePos()
{
    int total = qMax(this->maximum() - this->minimum(), 1);
    int delta = int(this->value() / total * this->_slideLength());

    if(this->orientation() == Qt::Vertical)
    {
        int x = this->width() - this->handle->width() - 3;
        this->handle->move(x, this->_padding + delta);
    }else{
        int y = this->height() - this->handle->height() - 3;
        this->handle->move(this->_padding + delta, y);
    }
    
}

int ScrollBar::_grooveLength()
{
    if(this->orientation() == Qt::Vertical)
    {
        return this->height() -2 * this->_padding;
    }
    return this->width() - 2 * this->_padding;
}

int ScrollBar::_slideLength()
{
    if(this->orientation() == Qt::Vertical)
    {
        return this->_grooveLength() - this->handle->height();
    }
    return this->_grooveLength() - this->handle->width();
}

bool ScrollBar::_isSlideResion(QPoint pos)
{
    if(this->orientation() == Qt::Vertical)
    {
        if(this->_padding <= pos.y() && pos.y() <= (this->height() - this->_padding))
        {
            return true;
        }else{
            return false;
        }
    }

    if(this->_padding <= pos.x() && pos.x() <= (this->width() - this->_padding))
        {
            return true;
        }else{
            return false;
    }
}

void ScrollBar::_onOpacityAniValueChanged()
{
    qreal opacity = this->groove->opacityEffect->opacity();
    if(this->orientation() == Qt::Vertical){
        this->handle->setFixedWidth(int(3 + opacity * 3));
    }else{
        this->handle->setFixedHeight(int(3 + opacity * 3));
    }
    this->_adjustHandlePos();
}

void ScrollBar::setForceHidden(bool isHidden)
{
    this->_isForceHidden = isHidden;
    this->setVisible(this->maximum() > 0 && !isHidden);
}

void ScrollBar::wheelEvent(QWheelEvent *event)
{
    QScrollArea *p = (QScrollArea *)this->parent();
    QApplication::sendEvent(p->viewport(), event);
}

SmoothScrollBar::SmoothScrollBar(Qt::Orientation orient, QAbstractScrollArea *parent) : ScrollBar(orient, parent)
{
    this->duration = 500;
    this->ani = new QPropertyAnimation();
    this->ani->setTargetObject(this);
    this->ani->setPropertyName(QString("val").toUtf8()); //TODO:这里无法使用对象的val值
    this->ani->setEasingCurve(QEasingCurve::OutCubic);
    this->ani->setDuration(this->duration);

    this->__value = this->value();
}   

void SmoothScrollBar::setValue(int value, bool useAni)
{
    if(value == this->value())
    {
        return;
    }
    this->ani->stop();

    if(!useAni)
    {
        this->val = value;
        return;
    }

    int dv = qAbs(value - this->value());
    if(dv < 50)
    {
        this->ani->setDuration(int(this->duration * dv / 70));
    }else{
        this->ani->setDuration(this->duration);
    }

    this->ani->setStartValue(this->value());
    this->ani->setEndValue(value);
    this->ani->start();
}

void SmoothScrollBar::scrollValue(int value, bool useAni = true)
{
    this->__value += value;
    this->__value = qMax(this->minimum(), this->__value);
    this->__value = qMin(this->maximum(), this->__value);
    this->setValue(this->__value, useAni);
}

void SmoothScrollBar::scrollTo(int value, bool useAni = true)
{
    this->__value = value;
    this->__value = qMax(this->minimum(), this->__value);
    this->__value = qMin(this->maximum(), this->__value);
    this->setValue(this->__value, useAni);
}

void SmoothScrollBar::resetValue(int value)
{
    this->__value = value;
}

void SmoothScrollBar::mousePressEvent(QMouseEvent *event)
{
    this->ani->stop();
    ScrollBar::mousePressEvent(event);
    this->__value = this->value();
}

void SmoothScrollBar::mouseMoveEvent(QMouseEvent *event)
{
    this->ani->stop();
    ScrollBar::mouseMoveEvent(event);
    this->__value = this->value();
}

void SmoothScrollBar::setScrollAnimation(int duration, QEasingCurve easing = QEasingCurve::OutCubic)
{
    this->duration = duration;
    this->ani->setDuration(duration);
    this->ani->setEasingCurve(easing);
}

SmoothScrollDelegate::SmoothScrollDelegate(QAbstractScrollArea *parent, bool useAni = false) :  QObject(parent)
{
    this->useAni = useAni;
    this->vScrollBar = new SmoothScrollBar(Qt::Vertical, parent);
    this->hScrollBar = new SmoothScrollBar(Qt::Horizontal, parent);
    this->verticalSmoothScroll = new SmoothScroll(parent, Qt::Vertical);
    this->horizonSmoothScroll = new SmoothScroll(parent, Qt::Horizontal);

    QAbstractItemView *itemView = qobject_cast<QAbstractItemView *>(parent);
    if(itemView){
        itemView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        itemView->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        parent->viewport()->installEventFilter(this);
        this->vScrollBar->setForceHidden(true);
        this->hScrollBar->setForceHidden(true);
        return;
    }

    QListView *listView = qobject_cast<QListView *>(parent);
    if(listView){
        itemView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        itemView->horizontalScrollBar()->setStyleSheet("QScrollBar:horizontal{height: 0px}");
        parent->viewport()->installEventFilter(this);
        this->vScrollBar->setForceHidden(true);
        this->hScrollBar->setForceHidden(true);
        return;
    }

    //parent->viewport()->installEventFilter(this);
    //this->vScrollBar->setForceHidden(true);
    //this->hScrollBar->setForceHidden(true);
    //TODO:parent.setVerticalScrollBarPolicy = self.setVerticalScrollBarPolicy
    //TODO:parent.setHorizontalScrollBarPolicy = self.setHorizontalScrollBarPolicy
}

bool SmoothScrollDelegate::eventFilter(QObject *watched, QWheelEvent *event)
{
    if(event->type() == QEvent::Wheel)
    {
        if(event->angleDelta().y() != 0)
        {
            if(!this->useAni)
            {
                this->verticalSmoothScroll->wheelEvent(event);
            }else{
                this->vScrollBar->scrollValue(-event->angleDelta().y(), true);
            }
        }else{
            if(!this->useAni)
            {
                this->horizonSmoothScroll->wheelEvent(event);
            }else{
                this->hScrollBar->scrollValue(-event->angleDelta().x(), true);
            }
        }
        event->setAccepted(true);
        return true;
    }
    return QObject::eventFilter(watched, event);
}