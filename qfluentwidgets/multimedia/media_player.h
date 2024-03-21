#pragma once

#include <QtCore/Qt>
#include <QtCore/QObject>
#include <QtCore/QUrl>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaContent>
#include <QtWidgets/QWidget>

class MediaPlayerBase : public QObject{
    Q_OBJECT
public:
    MediaPlayerBase(QWidget *parent) : QObject(parent){};
    virtual bool isPlaying(){};
    virtual QMediaPlayer::MediaStatus mediaStatus(){};
    virtual QMediaPlayer::State playbackState(){};
    virtual int duration(){};
    virtual QPoint position(){};
    virtual int volume(){};
    virtual QUrl source(){};
    virtual void pause(){};
    virtual void play(){};
    virtual void stop(){};
    virtual float playbackRate(){};
    virtual void setPosition(int position){};
    virtual void setSource(QUrl media){};
    virtual void setPlaybackRate(float rate){};
    virtual void setVolume(int volume){};
    virtual void setMuted(bool isMuted){};
    virtual QObject *videoOutput(){};
    virtual void setVideoOutput(QObject *output){};

signals:
    void mediaStatusChanged(QMediaPlayer::MediaStatus);
    void palybackRateChanged(float);
    void positionChanged(int);
    void durationChanged(int);
    void sourceChanged(QUrl);
    void volumeChanged(int);
    void mutedChanged(bool);
};



class MediaPlayer : public QMediaPlayer{
    Q_OBJECT
public:
    MediaPlayer(QWidget *parent);
    bool isPlaying();
    QUrl source();
    void setSource(QUrl media);
signals:
    void sourceChanged(QUrl);
};