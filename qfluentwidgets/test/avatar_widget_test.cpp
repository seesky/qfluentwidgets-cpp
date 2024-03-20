#include <iostream>
#include <QtCore>
#include <QtWidgets>
#include <QtCore/Qt>
#include "../../qfluentwidgets/components/widgets/label.h"




class AvatarWidgetView : public QWidget{
public:

    QHBoxLayout *hBoxLayout;

    AvatarWidgetView() : QWidget(){
        this->resize(400, 300);
        this->setStyleSheet(QString("Demo {background: white}"));
        
        this->hBoxLayout = new QHBoxLayout(this);

        QPixmap avatar = QPixmap("resource/shoko.png");

        int sizes[4] = {96, 48, 32, 24};
        for(int i = 0; i < 4; i++){
            AvatarWidget *w = new AvatarWidget(avatar, this);
            int s = sizes[i];
            w->setRadius(s / 2);
            this->hBoxLayout->addWidget(w);
        }
    }

};



int main(int argc, char *argv[])
{
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    
    QApplication *app = new QApplication(argc, argv);
    AvatarWidgetView *w = new AvatarWidgetView();
    w->show();
    return app->exec();
}