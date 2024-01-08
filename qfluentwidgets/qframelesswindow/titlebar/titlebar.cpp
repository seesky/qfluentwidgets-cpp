#include "titlebar.h"

TitleBarBase::TitleBarBase(QWidget *parent) : QWidget(parent)
{
    this->minBtn = new MinimizeButton(this);
    this->closeBtn = new CloseButton(this);
    this->maxBtn = new MaximizeButton(this);

    this->_isDoubleClickEnabled = true;

    resize(200, 32);
    setFixedHeight(32);
    
    connect(this->minBtn, &QAbstractButton::clicked, window(), &QWidget::showMinimized);
    connect(this->maxBtn, &QAbstractButton::clicked, this, &TitleBarBase::__toggleMaxState);
    connect(this->closeBtn, &QAbstractButton::clicked, window(), &QWidget::close);

    //connect(this->minBtn, SIGNAL(clicked()), this->window(), SLOT(showMinimized()));
    //connect(this->maxBtn, SIGNAL(clicked()), this, SLOT(__toggleMaxState()));
    //connect(this->closeBtn, SIGNAL(clicked()), this->window(), SLOT(close()));
    //connect(this->minBtn, &MinimizeButton::clicked, this, SLOT(window()->showMinimized));
    //connect(this->maxBtn, SIGNAL(&QAbstractButton::clicked), this, SLOT(&TitleBarBase::__toggleMaxState));
    //connect(this->closeBtn, SIGNAL(&QAbstractButton::clicked), this, SLOT(window()->close));

    window()->installEventFilter(this);
}

bool TitleBarBase::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == window())
    {
        if(event->type() == QEvent::WindowStateChange)
        {
            this->maxBtn->setMaxState(window()->isMaximized());
            return false;
        }
    }
    return QWidget::eventFilter(watched, event);
}


void TitleBarBase::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button() != Qt::LeftButton || !this->_isDoubleClickEnabled)
    {
        return;
    }
    this->__toggleMaxState();
}


void TitleBarBase::mouseMoveEvent(QMouseEvent *event)
{
    QPoint p = event->pos();
    if(!this->canDrag(&p))
        return;
    
    WindowsMoveResize::startSystemMove((QWindow *)window(), event->globalPos());
}

void TitleBarBase::mousePressEvent(QMouseEvent *event)
{
    QPoint p = event->pos();
    if(!this->canDrag(&p))
        return;
    
    WindowsMoveResize::startSystemMove((QWindow *)window(), event->globalPos());
}

void TitleBarBase::__toggleMaxState()
{
    if(window()->isMaximized()){
        window()->showNormal();
    }else{
        window()->showMaximized();
    }
}

bool TitleBarBase::_isDragRegion(QPoint *pos)
{
    int width = 0;
    QList<TitleBarButton *> list = this->findChildren<TitleBarButton *>();
    for(TitleBarButton *value : list){
        if(value->isVisible()){
            width += value->width();
        }
    }
    return pos->x() > 0 && pos->x() < (this->width() - width);
}

bool TitleBarBase::_hasButtonPressed()
{
    QList<TitleBarButton *> list = this->findChildren<TitleBarButton *>();
    for(TitleBarButton *value : list){
        if(value->isPressed()){
            return false;
        }
    }
    return true;
}

bool TitleBarBase::canDrag(QPoint *pos)
{
    return this->_isDragRegion(pos) && !this->_hasButtonPressed();
}

void TitleBarBase::setDoubleClickEnabled(bool isEnabled)
{
    this->_isDoubleClickEnabled = isEnabled;
}

TitleBar::TitleBar(QWidget *parent) : TitleBarBase(parent)
{
    this->hBoxLayout = new QHBoxLayout(this);

    this->hBoxLayout->setSpacing(0);
    this->hBoxLayout->setContentsMargins(0, 0, 0, 0);
    this->hBoxLayout->setAlignment(Qt::AlignCenter | Qt::AlignLeft);
    this->hBoxLayout->addStretch(1);
    this->hBoxLayout->addWidget(this->minBtn, 0, Qt::AlignRight);
    this->hBoxLayout->addWidget(this->maxBtn, 0, Qt::AlignRight);
    this->hBoxLayout->addWidget(this->closeBtn, 0, Qt::AlignRight);
}


StandardTitleBar::StandardTitleBar(QWidget *parent) : TitleBar(parent)
{
    this->iconLabel = new QLabel(this);
    this->iconLabel->setFixedSize(20, 20);
    this->hBoxLayout->insertSpacing(0, 10);
    this->hBoxLayout->insertWidget(1, this->iconLabel, 0, Qt::AlignLeft);
    connect(window(), SIGNAL(&QWidget::windowIconChanged), this, SLOT(&StandardTitleBar::setIcon));

    this->titleLabel = new QLabel(this);
    this->hBoxLayout->insertWidget(2, this->titleLabel, 0, Qt::AlignLeft);
    this->titleLabel->setStyleSheet("QLabel{background: transparent;font: 13px 'Segoe UI';padding: 0 4px}");
    connect(window(), SIGNAL(&QWidget::windowTitleChanged), this, SLOT(&StandardTitleBar::setTitle));
}

void StandardTitleBar::setTitle(QString title)
{
    this->titleLabel->setText(title);
    this->titleLabel->adjustSize();
}

void StandardTitleBar::setIcon(QVariant *icon)
{
    if(icon->canConvert<QIcon>()){
        QIcon i = icon->value<QIcon>();
        this->iconLabel->setPixmap(QIcon(i).pixmap(20, 20));
    }else if(icon->canConvert<QPixmap>()){
        QPixmap i = icon->value<QPixmap>();
        this->iconLabel->setPixmap(QIcon(i).pixmap(20, 20));
    }else if(icon->canConvert<QString>()){
        QString i = icon->value<QString>();
        this->iconLabel->setPixmap(QIcon(i).pixmap(20, 20));
    }
    
}