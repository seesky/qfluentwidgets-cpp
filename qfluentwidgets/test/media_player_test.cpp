#include <iostream>
#include <QtCore/QUrl>
#include <QtCore/Qt>
#include <QtCore/QFileInfo>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include "../common/style_sheet.h"
#include "../multimedia/video_widget.h"
#include "../multimedia/media_play_bar.h"




class MediaPlayerView1 : public QWidget{
public:
    QVBoxLayout *vBoxLayout;
    SimpleMediaPlayBar *simplePlayBar;
    StandardMediaPlayBar *standardPlayBar;
    QUrl url1, url2;


    MediaPlayerView1(){
        this->vBoxLayout = new QVBoxLayout(this);
        this->resize(500, 300);

        this->simplePlayBar = new SimpleMediaPlayBar(this);
        this->standardPlayBar = new StandardMediaPlayBar(this);

        this->vBoxLayout->addWidget(this->simplePlayBar);
        this->vBoxLayout->addWidget(this->standardPlayBar);

        url1 = QUrl(QString("https://files.cnblogs.com/files/blogs/677826/beat.zip?t=1693900324"));
        this->simplePlayBar->player->value<MediaPlayer*>()->setSource(url1);

        //url2 = QUrl::fromLocalFile(QFileInfo("resource/aiko - シアワセ.mp3").absoluteFilePath());
        url2 = QUrl(QString("https://files.cnblogs.com/files/blogs/677826/beat.zip?t=1693900324"));
        this->standardPlayBar->player->value<MediaPlayer*>()->setSource(url2);
       
    }

};


class MediaPlayerView2 : public QWidget{
public:

    QVBoxLayout *vBoxLayout;
    VideoWidget *videoWidget;
    MediaPlayerView2(){
        this->vBoxLayout = new QVBoxLayout(this);
        this->videoWidget = new VideoWidget(this);

        this->videoWidget->setVideo(QUrl(QString("https://files.cnblogs.com/files/blogs/677826/beat.zip?t=1693900324")));
        this->videoWidget->play();

        this->vBoxLayout->setContentsMargins(0, 0, 0, 0);
        this->vBoxLayout->addWidget(this->videoWidget);
        this->resize(800, 450);
       
    }

};




int main(int argc, char *argv[])
{
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    
    QApplication *app = new QApplication(argc, argv);
    MediaPlayerView1 *w = new MediaPlayerView1();
    w->show();

    MediaPlayerView2 *w2 = new MediaPlayerView2();
    w2->show();
    return app->exec();
}