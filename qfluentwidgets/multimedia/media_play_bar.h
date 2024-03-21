#pragma once

#include <QtCore/Qt>
#include <QtCore/QSize>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QPoint>
#include <QtGui/QPixmap>
#include <QtGui/QPainter>
#include <QtGui/QColor>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGraphicsOpacityEffect>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>

#include "../common/icon.h"
#include "../common/style_sheet.h"
#include "../components/widgets/button.h"
#include "../components/widgets/tool_tip.h"
#include "../components/widgets/slider.h"
#include "../components/widgets/label.h"
#include "../components/widgets/flyout.h"
#include "media_player.h"


class MediaPlayBarButton : public TransparentToolButton{
    Q_OBJECT
public:
    MediaPlayBarButton(QWidget *parent) : TransparentToolButton(parent){};
    MediaPlayBarButton(FluentIcon *icon, QWidget *parent) : TransparentToolButton(icon, parent){};
    MediaPlayBarButton(QIcon *icon, QWidget *parent) : TransparentToolButton(icon, parent){};
    MediaPlayBarButton(QString icon, QWidget *parent) : TransparentToolButton(icon, parent){};
    void _postInit() override;
};


class PlayButton : public MediaPlayBarButton{
    Q_OBJECT
public:
    PlayButton(QWidget *parent) : MediaPlayBarButton(parent){};
    PlayButton(FluentIcon *icon, QWidget *parent) : MediaPlayBarButton(icon, parent){};
    PlayButton(QIcon *icon, QWidget *parent) : MediaPlayBarButton(icon, parent){};
    PlayButton(QString icon, QWidget *parent) : MediaPlayBarButton(icon, parent){};
    void _postInit() override;
    void setPlay(bool isPlay);
};


class VolumeView : public FlyoutViewBase{
    Q_OBJECT
public:
    VolumeView(QWidget *parent);
    void setMuted(bool isMute);
    void setVolume(int volume);
    void paintEvent(QPaintEvent *event) override;

    MediaPlayBarButton *muteButton;
    Slider *volumeSlider;
    CaptionLabel *volumeLabel;
};


class VolumeButton : public MediaPlayBarButton{
    Q_OBJECT
public:
    VolumeButton(QWidget *parent) : MediaPlayBarButton(parent){
        this->_postInit();
    };
    VolumeButton(FluentIcon *icon, QWidget *parent) : MediaPlayBarButton(icon, parent){
        this->_postInit();
    };
    VolumeButton(QIcon *icon, QWidget *parent) : MediaPlayBarButton(icon, parent){
        this->_postInit();
    };
    VolumeButton(QString icon, QWidget *parent) : MediaPlayBarButton(icon, parent){
        this->_postInit();
    };
    void _postInit() override;
    void setMuted(bool isMute);
    void setVolume(int volume);


    VolumeView *volumeView;
    Flyout *volumeFlyout;
    bool isMuted;
signals:
    void volumeChanged(int);
    void mutedChanged(bool);

public slots:
    void _showVolumeFlyout();
};


class MediaPlayBarBase : public QWidget{
    Q_OBJECT
public:
    MediaPlayBarBase(QWidget *parent);
    void setMediaPlayer(QVariant *player);
    void fadeIn();
    void fadeOut();
    void play();
    void pause();
    void stop();
    void setVolume(int volume);
    void setPosition(int position);

    void togglePlayState();
    void paintEvent(QPaintEvent *event) override;

    //MediaPlayerBase *player;
    QVariant *player;
    PlayButton *playButton;
    VolumeButton *volumeButton;
    Slider *progressSlider;
    QGraphicsOpacityEffect *opacityEffect;
    QPropertyAnimation *opacityAni;

public slots:
    virtual void _onPositionChanged(int position);
    void _onMediaStatusChanged();
};



class SimpleMediaPlayBar : public MediaPlayBarBase{
    Q_OBJECT
public:
    SimpleMediaPlayBar(QWidget *parent);
    void addButton(MediaPlayBarButton *button);

    QHBoxLayout *hBoxLayout;
};


class StandardMediaPlayBar : public MediaPlayBarBase{
    Q_OBJECT
public:
    StandardMediaPlayBar(QWidget *parent);
    void __initWidgets();
    void skipBack(int ms);
    void skipForward(int ms);
    QString _formatTime(int time);

    QVBoxLayout *vBoxLayout;
    QHBoxLayout *timeLayout;
    QHBoxLayout *buttonLayout;
    QWidget *leftButtonContainer;
    QWidget *centerButtonContainer;
    QWidget *rightButtonContainer;
    QHBoxLayout *leftButtonLayout;
    QHBoxLayout *centerButtonLayout;
    QHBoxLayout *rightButtonLayout;

    MediaPlayBarButton *skipBackButton;
    MediaPlayBarButton *skipForwardButton;

    CaptionLabel *currentTimeLabel;
    CaptionLabel *remainTimeLabel;

public slots:
    void _onPositionChanged(int position) override;
};