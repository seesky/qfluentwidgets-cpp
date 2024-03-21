#pragma once

#include <QtCore/Qt>
#include <QtCore/QUrl>
#include <QtCore/QSizeF>
#include <QtCore/QTimer>
#include <QtGui/QPainter>
#include <QtMultimediaWidgets/QGraphicsVideoItem>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QGraphicsScene>
#include "../common/style_sheet.h"
#include "../multimedia/media_play_bar.h"

/*
class GraphicsVideoItem : public QGraphicsVideoItem{
    Q_OBJECT
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};
*/


class VideoWidget : public QGraphicsView{
    Q_OBJECT
public:
    VideoWidget(QWidget *parent);
    void setVideo(QUrl url);
    void hideEvent(QHideEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    
    void play();
    void pause();
    void stop();
    void togglePlayState();
    void resizeEvent(QResizeEvent *event) override;
    QVariant *player();

    bool isHover;
    QTimer *timer;
    QVBoxLayout *vBoxLayout;
    QGraphicsVideoItem *videoItem;
    QGraphicsScene *graphicsScene;
    StandardMediaPlayBar *playBar;

public slots:
    void _onHideTimeOut();
};