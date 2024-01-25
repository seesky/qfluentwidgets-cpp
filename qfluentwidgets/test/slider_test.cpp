#include <iostream>
#include <QtCore>
#include <QtWidgets>
#include <QtCore/Qt>
#include "../components/widgets/slider.h"


class WindowView : public QWidget{
public:
    WindowView(){
        setStyleSheet("ButtonView{background: rgb(255,255,255)}");
    }
};

class SliderDemo1 : public QWidget{
public:
    
    QSlider *slider;


    QHBoxLayout *hBoxLayout;
    SliderDemo1(){
        this->resize(300, 150);
        this->setStyleSheet("SliderDemo1{background: rgb(184, 106, 106)}");

        QMap<QString, QVariant*> *style = new QMap<QString, QVariant*>();
        style->insert(QString("sub-page.color"), new QVariant(QVariant::fromValue<QColor>(QColor(70, 23, 180))));

        slider = new QSlider(Qt::Horizontal, this);
        this->slider->setStyle(new HollowHandleStyle(style, nullptr));

        this->slider->resize(200, 28);
        this->slider->move(50, 61);

    }

};


class SliderDemo2 : public WindowView{
public:
    

    Slider *slider1;
    Slider *slider2;
    

    QHBoxLayout *hBoxLayout;
    SliderDemo2(){

        hBoxLayout = new QHBoxLayout();

        slider1 = new Slider(Qt::Horizontal, this);
        slider1->setFixedWidth(200);
        slider1->move(50, 30);

        slider2 = new Slider(Qt::Vertical, this);
        slider2->setFixedHeight(150);
        slider2->move(140, 80);

        //setLayout(hBoxLayout);
        resize(300, 300);
    }

public slots:
    void toggleToolButtonPrint(QString text)
    {
        qDebug() << text;
    }
};


int main(int argc, char *argv[])
{
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    
    QApplication *app = new QApplication(argc, argv);
    SliderDemo2 *w = new SliderDemo2();
    w->show();
    return app->exec();
}