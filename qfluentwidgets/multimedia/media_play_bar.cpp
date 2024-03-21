#include "media_play_bar.h"

void MediaPlayBarButton::_postInit()
{
    TransparentToolButton::_postInit();
    this->installEventFilter(new ToolTipFilter(this, 1000, ToolTipPosition::TOP));
    this->setFixedSize(30, 30);
    this->setIconSize(QSize(16, 16));
}



void PlayButton::_postInit()
{
    MediaPlayBarButton::_postInit();
    this->setIconSize(QSize(14, 14));
    this->setPlay(false);
}

void PlayButton::setPlay(bool isPlay)
{
    if(isPlay){
        FluentIcon *icon = new FluentIcon();
        icon->setIconName(QString("PAUSE_BOLD"));
        QVariant *iconQVariant = new QVariant();
        iconQVariant->setValue<FluentIcon>(*icon);
        this->setIcon(iconQVariant);

        this->setToolTip(this->tr("Pause"));
    }else{
        FluentIcon *icon = new FluentIcon();
        icon->setIconName(QString("PLAY_SOLID"));
        QVariant *iconQVariant = new QVariant();
        iconQVariant->setValue<FluentIcon>(*icon);
        this->setIcon(iconQVariant);

        this->setToolTip(this->tr("Play"));
    }
}


VolumeView::VolumeView(QWidget *parent) : FlyoutViewBase(parent)
{
    FluentIcon *icon = new FluentIcon();
    icon->setIconName(QString("VOLUME"));
    this->muteButton = new MediaPlayBarButton(icon, this);
    this->volumeSlider = new Slider(Qt::Horizontal, this);
    this->volumeLabel = new CaptionLabel(QString("30"), this);

    this->volumeSlider->setRange(0, 100);
    this->volumeSlider->setFixedWidth(208);
    this->setFixedSize(295, 64);

    int h = this->height();
    this->muteButton->move(10, h / 2 - this->muteButton->height() / 2);
    this->volumeSlider->move(45, 21);
}

void VolumeView::setMuted(bool isMute)
{
    if(isMute){
        FluentIcon *icon = new FluentIcon();
        icon->setIconName(QString("MUTE"));
        QVariant *iconQVariant = new QVariant();
        iconQVariant->setValue<FluentIcon>(*icon);
        this->muteButton->setIcon(iconQVariant);

        this->muteButton->setToolTip(this->tr("Unmute"));
    }else{
        FluentIcon *icon = new FluentIcon();
        icon->setIconName(QString("VOLUME"));
        QVariant *iconQVariant = new QVariant();
        iconQVariant->setValue<FluentIcon>(*icon);
        this->muteButton->setIcon(iconQVariant);

        this->muteButton->setToolTip(this->tr("Mute"));
    }
}


void VolumeView::setVolume(int volume)
{
    this->volumeSlider->setValue(volume);

    this->volumeLabel->setNum(volume);
    this->volumeLabel->adjustSize();

    QRect tr = this->volumeLabel->fontMetrics().boundingRect(QString::number(volume));
    this->volumeLabel->move(this->width() - 20 - tr.width(), this->height() / 2 - tr.height() / 2);
}


void VolumeView::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    if(isDarkTheme()){
        painter.setBrush(QColor(46, 46, 46));
        painter.setPen(QColor(0, 0, 0, 20));
    }else{
        painter.setBrush(QColor(248, 248, 248));
        painter.setPen(QColor(0, 0, 0, 10));
    }

    painter.drawRoundedRect(this->rect().adjusted(1, 1, -1, -1), 8, 8);
}

void VolumeButton::_postInit()
{   
    MediaPlayBarButton::_postInit();
    this->volumeView = new VolumeView(this);
    this->volumeFlyout = new Flyout(this->volumeView, this->window(), false);
    this->setMuted(false);

    this->volumeFlyout->hide();
    connect(this->volumeView->muteButton, &MediaPlayBarButton::clicked, this, [this](){
        emit(this->mutedChanged(!this->isMuted));
    });

    connect(this->volumeView->volumeSlider, &Slider::valueChanged, this, &VolumeButton::volumeChanged);
    connect(this, &VolumeButton::clicked, this, &VolumeButton::_showVolumeFlyout);
}

void VolumeButton::setMuted(bool isMute)
{
    this->isMuted = isMute;
    this->volumeView->setMuted(isMute);

    if(isMute){
        FluentIcon *icon = new FluentIcon();
        icon->setIconName(QString("MUTE"));
        QVariant *iconQVariant = new QVariant();
        iconQVariant->setValue<FluentIcon>(*icon);
        this->setIcon(iconQVariant);
    }else{
        FluentIcon *icon = new FluentIcon();
        icon->setIconName(QString("VOLUME"));
        QVariant *iconQVariant = new QVariant();
        iconQVariant->setValue<FluentIcon>(*icon);
        this->setIcon(iconQVariant);
    }
}


void VolumeButton::setVolume(int volume)
{
    this->volumeView->setVolume(volume);
}

void VolumeButton::_showVolumeFlyout()
{
    if(this->volumeFlyout->isVisible()){
        return;
    }

    QPoint pos = PullUpFlyoutAnimationManager(this->volumeFlyout).position(this);
    this->volumeFlyout->exec(pos, FlyoutAnimationType::PULL_UP);
}



MediaPlayBarBase::MediaPlayBarBase(QWidget *parent) : QWidget(parent)
{
    this->player = nullptr;

    this->playButton = new PlayButton(this);
    this->volumeButton = new VolumeButton(this);
    this->progressSlider = new Slider(Qt::Horizontal, this);

    this->opacityEffect = new QGraphicsOpacityEffect(this);
    this->opacityAni = new QPropertyAnimation(this->opacityEffect, "opacity");
    this->opacityEffect->setOpacity(1);
    this->opacityAni->setDuration(250);

    this->setGraphicsEffect(this->opacityEffect);
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("MEDIA_PLAYER"), Theme::AUTO);
    
}


void MediaPlayBarBase::setMediaPlayer(QVariant *player)
{
    this->player = player;
    if(this->player->canConvert<MediaPlayer*>()){
        connect(this->player->value<MediaPlayer*>(), &MediaPlayer::durationChanged, this->progressSlider, &Slider::setMaximum);
        connect(this->player->value<MediaPlayer*>(), &MediaPlayer::positionChanged, this, &MediaPlayBarBase::_onPositionChanged);
        connect(this->player->value<MediaPlayer*>(), &MediaPlayer::mediaStatusChanged, this, &MediaPlayBarBase::_onMediaStatusChanged);
        connect(this->player->value<MediaPlayer*>(), &MediaPlayer::volumeChanged, this->volumeButton, &VolumeButton::setVolume);
        connect(this->player->value<MediaPlayer*>(), &MediaPlayer::mutedChanged, this->volumeButton,  &VolumeButton::setMuted);

        connect(this->progressSlider, &Slider::sliderMoved, this->player->value<MediaPlayer*>(), &MediaPlayer::setPosition);
        connect(this->progressSlider, &Slider::clicked, this->player->value<MediaPlayer*>(), &MediaPlayer::setPosition);
        connect(this->playButton, &PlayButton::clicked, this, &MediaPlayBarBase::togglePlayState);
        connect(this->volumeButton, &VolumeButton::volumeChanged, this->player->value<MediaPlayer*>(), &MediaPlayer::setVolume);
        connect(this->volumeButton, &VolumeButton::mutedChanged, this->player->value<MediaPlayer*>(), &MediaPlayer::setMuted);

        this->player->value<MediaPlayer*>()->setVolume(30);
    }

}


void MediaPlayBarBase::fadeIn()
{
    this->opacityAni->setStartValue(this->opacityEffect->opacity());
    this->opacityAni->setEndValue(1);
    this->opacityAni->start();
}


void MediaPlayBarBase::fadeOut()
{
    this->opacityAni->setStartValue(this->opacityEffect->opacity());
    this->opacityAni->setEndValue(0);
    this->opacityAni->start();
}


void MediaPlayBarBase::play()
{
    if(this->player->canConvert<MediaPlayer*>()){
        this->player->value<MediaPlayer*>()->play();
    }
}

void MediaPlayBarBase::pause()
{   
    if(this->player->canConvert<MediaPlayer*>()){
        this->player->value<MediaPlayer*>()->pause();
    }
}

void MediaPlayBarBase::stop()
{
    if(this->player->canConvert<MediaPlayer*>()){
        this->player->value<MediaPlayer*>()->stop();
    }
}


void MediaPlayBarBase::setVolume(int volume)
{
    if(this->player->canConvert<MediaPlayer*>()){
        this->player->value<MediaPlayer*>()->setVolume(volume);
    }
}

void MediaPlayBarBase::setPosition(int position)
{
    if(this->player->canConvert<MediaPlayer*>()){
        this->player->value<MediaPlayer*>()->setPosition(position);
    }
}

void MediaPlayBarBase::_onPositionChanged(int position)
{
    if(this->player->canConvert<MediaPlayer*>()){
        this->progressSlider->setValue(position);
    }
}

void MediaPlayBarBase::_onMediaStatusChanged()
{
    if(this->player->canConvert<MediaPlayer*>()){
        this->playButton->setPlay(this->player->value<MediaPlayer*>()->isPlaying());
    }
}

void MediaPlayBarBase::togglePlayState()
{
    if(this->player->canConvert<MediaPlayer*>()){
        if(this->player->value<MediaPlayer*>()->isPlaying()){
            this->player->value<MediaPlayer*>()->pause();
        }else{
            this->player->value<MediaPlayer*>()->play();
        }

        this->playButton->setPlay(this->player->value<MediaPlayer*>()->isPlaying());
    }
    
}

void MediaPlayBarBase::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    if(isDarkTheme()){
        painter.setBrush(QColor(46, 46, 46));
        painter.setPen(QColor(0, 0, 0, 20));
    }else{
        painter.setBrush(QColor(248, 248, 248));
        painter.setPen(QColor(0, 0, 0, 10));
    }

    painter.drawRoundedRect(this->rect().adjusted(1, 1, -1, -1), 8, 8);
}



SimpleMediaPlayBar::SimpleMediaPlayBar(QWidget *parent) : MediaPlayBarBase(parent)
{
    this->hBoxLayout = new QHBoxLayout(this);

    this->hBoxLayout->setContentsMargins(10, 4, 10, 4);
    this->hBoxLayout->setSpacing(6);
    this->hBoxLayout->addWidget(this->playButton, 0, Qt::AlignLeft);
    this->hBoxLayout->addWidget(this->progressSlider, 1);
    this->hBoxLayout->addWidget(this->volumeButton, 0);

    this->setFixedHeight(48);
    QVariant *mediaPlayer = new QVariant();
    mediaPlayer->setValue<MediaPlayer*>(new MediaPlayer(this));
    this->setMediaPlayer(mediaPlayer);
}


void SimpleMediaPlayBar::addButton(MediaPlayBarButton *button)
{
    this->hBoxLayout->addWidget(button, 0);
}


StandardMediaPlayBar::StandardMediaPlayBar(QWidget *parent) : MediaPlayBarBase(parent)
{
    this->vBoxLayout = new QVBoxLayout(this);
    this->timeLayout = new QHBoxLayout();
    this->buttonLayout = new QHBoxLayout();
    this->leftButtonContainer = new QWidget();
    this->centerButtonContainer = new QWidget();
    this->rightButtonContainer = new QWidget();

    this->leftButtonLayout = new QHBoxLayout(this->leftButtonContainer);
    this->centerButtonLayout = new QHBoxLayout(this->centerButtonContainer);
    this->rightButtonLayout = new QHBoxLayout(this->rightButtonContainer);

    FluentIcon *icon_skip_back = new FluentIcon();
    icon_skip_back->setIconName("SKIP_BACK");
    this->skipBackButton = new MediaPlayBarButton(icon_skip_back, this);

    FluentIcon *icon_skip_forward = new FluentIcon();
    icon_skip_forward->setIconName("SKIP_FORWARD");
    this->skipForwardButton = new MediaPlayBarButton(icon_skip_forward, this);

    this->currentTimeLabel = new CaptionLabel(QString("0:00:00"), this);
    this->remainTimeLabel = new CaptionLabel(QString("0:00:00"), this);

    this->__initWidgets();
}




void StandardMediaPlayBar::__initWidgets()
{
    this->setFixedHeight(102);
    this->vBoxLayout->setSpacing(6);
    this->vBoxLayout->setContentsMargins(5, 9, 5, 9);
    this->vBoxLayout->addWidget(this->progressSlider, 1, Qt::AlignTop);

    this->vBoxLayout->addLayout(this->timeLayout);
    this->timeLayout->setContentsMargins(10, 0, 10, 0);
    this->timeLayout->addWidget(this->currentTimeLabel, 0, Qt::AlignLeft);
    this->timeLayout->addWidget(this->remainTimeLabel, 0, Qt::AlignRight);

    this->vBoxLayout->addStretch(1);
    this->vBoxLayout->addLayout(this->buttonLayout, 1);
    this->buttonLayout->setContentsMargins(0, 0, 0, 0);
    this->leftButtonLayout->setContentsMargins(4, 0, 0, 0);
    this->centerButtonLayout->setContentsMargins(0, 0, 0, 0);
    this->rightButtonLayout->setContentsMargins(0, 0, 4, 0);

    this->leftButtonLayout->addWidget(this->volumeButton, 0, Qt::AlignLeft);
    this->centerButtonLayout->addWidget(this->skipBackButton);
    this->centerButtonLayout->addWidget(this->playButton);
    this->centerButtonLayout->addWidget(this->skipForwardButton);

    this->buttonLayout->addWidget(this->leftButtonContainer, 0, Qt::AlignLeft);
    this->buttonLayout->addWidget(this->centerButtonContainer, 0, Qt::AlignHCenter);
    this->buttonLayout->addWidget(this->rightButtonContainer, 0, Qt::AlignRight);

    QVariant *mediaPlayer = new QVariant();
    mediaPlayer->setValue<MediaPlayer*>(new MediaPlayer(this));
    this->setMediaPlayer(mediaPlayer);

    connect(this->skipBackButton, &MediaPlayBarButton::clicked, this, [this](){
        this->skipBack(10000);
    });

    connect(this->skipForwardButton, &MediaPlayBarButton::clicked, this, [this](){
        this->skipForward(30000);
    });
}


void StandardMediaPlayBar::skipBack(int ms)
{
    if(this->player->canConvert<MediaPlayer*>()){
        this->player->value<MediaPlayer*>()->setPosition(this->player->value<MediaPlayer*>()->position()-ms);
    }
}


void StandardMediaPlayBar::skipForward(int ms)
{
    if(this->player->canConvert<MediaPlayer*>()){
        this->player->value<MediaPlayer*>()->setPosition(this->player->value<MediaPlayer*>()->position()+ms);
    }
}


void StandardMediaPlayBar::_onPositionChanged(int position)
{
    if(this->player->canConvert<MediaPlayer*>()){
        MediaPlayBarBase::_onPositionChanged(position);
        this->currentTimeLabel->setText(this->_formatTime(position));
        this->remainTimeLabel->setText(this->_formatTime(this->player->value<MediaPlayer*>()->duration() - position));
    }
}


QString StandardMediaPlayBar::_formatTime(int time)
{
    int _time = time / 1000;
    int s = _time % 60;
    int m = _time / 60;
    int h = _time / 3600;
    return QString("%1:%2:%3").arg(h, 2, 10, QChar('0')).arg(m, 2, 10, QChar('0')).arg(s, 2, 10, QChar('0'));
}