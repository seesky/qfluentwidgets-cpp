#include "media_player.h"

MediaPlayer::MediaPlayer(QWidget *parent) : QMediaPlayer(parent)
{
    connect(this, &MediaPlayer::mediaChanged, this, [](QMediaContent i){
        i.canonicalUrl();
    });
    this->setNotifyInterval(1000);
}


bool MediaPlayer::isPlaying()
{   
    return this->state() == QMediaPlayer::PlayingState;
}

QUrl MediaPlayer::source()
{
    return this->currentMedia().canonicalUrl();
}


void MediaPlayer::setSource(QUrl media)
{
    this->setMedia(QMediaContent(media));
}