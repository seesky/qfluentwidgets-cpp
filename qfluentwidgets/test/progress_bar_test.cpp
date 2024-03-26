#include <QtCore/Qt>
#include <QtCore/QSize>
#include <QtCore/QPoint>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>

#include "../components/widgets/progress_bar.h"
#include "../components/widgets/button.h"
#include "../common/icon.h"
#include "../common/style_sheet.h"

class Demo : public QWidget{
public:

    QVBoxLayout *vBoxLayout;
    ProgressBar *progressBar;
    IndeterminateProgressBar *inProgressBar;
    ToggleToolButton *button;
    Demo(){
        this->vBoxLayout = new QVBoxLayout(this);
        this->progressBar = new ProgressBar(this, true);
        this->inProgressBar = new IndeterminateProgressBar(this, true);

        FluentIcon *icon = new FluentIcon();
        icon->setIconName(QString("PAUSE_BOLD"));
        this->button = new ToggleToolButton(icon, this);
        
        this->progressBar->setValue(50);
        this->vBoxLayout->addWidget(this->progressBar);
        this->vBoxLayout->addWidget(this->inProgressBar);
        this->vBoxLayout->addWidget(this->button, 0, Qt::AlignHCenter);
        this->vBoxLayout->setContentsMargins(30, 30, 30, 30);
        this->resize(400, 400);

        connect(this->button, &ToggleToolButton::clicked, this, &Demo::onButtonClicked);


        this->resize(400, 400);
    };

public slots:
    void onButtonClicked(){
        
        if(this->inProgressBar->isStarted()){
            this->inProgressBar->pause();
            this->progressBar->pause();
            FluentIcon *icon = new FluentIcon();
            icon->setIconName(QString("PLAY_SOLID"));
            this->button->setIcon(new QVariant(QVariant::fromValue<FluentIcon>(*icon)));
        }else{
            this->inProgressBar->resume();
            this->progressBar->resume();
            FluentIcon *icon = new FluentIcon();
            icon->setIconName(QString("PAUSE_BOLD"));
            this->button->setIcon(new QVariant(QVariant::fromValue<FluentIcon>(*icon)));
        }
        
    };
};




int main(int argc, char *argv[])
{
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    
    QApplication *app = new QApplication(argc, argv);
    Demo *w = new Demo();
    w->show();
    return app->exec();
}