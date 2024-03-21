#include "video_widget.h"

/*
void GraphicsVideoItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setCompositionMode(QPainter::CompositionMode_Difference);
}
*/

VideoWidget::VideoWidget(QWidget *parent) : QGraphicsView(parent)
{
    this->isHover = false;
    this->timer = new QTimer(this);

    this->vBoxLayout = new QVBoxLayout(this);
    this->videoItem = new QGraphicsVideoItem();
    this->graphicsScene = new QGraphicsScene(this);
    this->playBar = new StandardMediaPlayBar(this);

    this->setMouseTracking(true);
    this->setScene(this->graphicsScene);
    this->graphicsScene->addItem(this->videoItem);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    this->player()->value<MediaPlayer*>()->setVideoOutput(this->videoItem); //TODO:特殊关注
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("MEDIA_PLAYER"), Theme::AUTO);

    connect(this->timer, &QTimer::timeout, this, &VideoWidget::_onHideTimeOut);
}


void VideoWidget::setVideo(QUrl url)
{
    this->player()->value<MediaPlayer*>()->setSource(url);
    this->fitInView(this->videoItem, Qt::KeepAspectRatio);
}


void VideoWidget::hideEvent(QHideEvent *event)
{
    this->pause();
    event->accept();
}


void VideoWidget::wheelEvent(QWheelEvent *event)
{
    return;
}

void VideoWidget::enterEvent(QEvent *event)
{
    this->isHover = true;
    this->playBar->fadeIn();
}

void VideoWidget::leaveEvent(QEvent *event)
{
    this->isHover = false;
    this->timer->start(3000);
}



void VideoWidget::_onHideTimeOut()
{
    if(!this->isHover){
        this->playBar->fadeOut();
    }
}


void VideoWidget::play()
{
    this->playBar->play();
}

void VideoWidget::pause()
{
    this->playBar->pause();
}


void VideoWidget::stop()
{
    this->playBar->pause();
}


void VideoWidget::togglePlayState()
{
    if(this->player()->value<MediaPlayer*>()->isPlaying()){
        this->pause();
    }else{
        this->play();
    }
}

void VideoWidget::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    this->videoItem->setSize(QSizeF(this->size()));
    this->fitInView(this->videoItem, Qt::KeepAspectRatio);
    this->playBar->move(11, this->height() - this->playBar->height() - 11);
    this->playBar->setFixedSize(this->width() - 22, this->playBar->height());
}

QVariant *VideoWidget::player()
{
    return this->playBar->player;
}