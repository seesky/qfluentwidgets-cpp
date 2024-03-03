#include <QtCore/QDate>
#include <QtCore/Qt>
#include <QtCore/QTime>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include "../components/settings/setting_card.h"



class WindowView : public QWidget{
public:
    WindowView(){
        setStyleSheet("ButtonView{background: rgb(255,255,255)}");
    }
};

class ColorDialogDemo : public QWidget{
public:
    

    QVBoxLayout *vBoxLayout;
    ColorPickerButton *button;

    ColorDialogDemo(){
        this->vBoxLayout = new QVBoxLayout(this);

        this->button = new ColorPickerButton(QColor("#5012aaa2"), QString("Background Color"), this, true);
        this->resize(800, 720);
        this->vBoxLayout->addWidget(this->button, 0, Qt::AlignHCenter);
    }
};



int main(int argc, char *argv[])
{
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    
    QApplication *app = new QApplication(argc, argv);
    ColorDialogDemo *w = new ColorDialogDemo();
    w->show();
    return app->exec();
}