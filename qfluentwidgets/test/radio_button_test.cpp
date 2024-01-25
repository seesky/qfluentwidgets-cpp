#include <iostream>
#include <QtCore>
#include <QtWidgets>
#include <QtCore/Qt>
#include "../components/widgets/button.h"


class WindowView : public QWidget{
public:
    WindowView(){
        setStyleSheet("ButtonView{background: rgb(255,255,255)}");
    }
};

class RadioButtonDemo : public WindowView{
public:
    



    QHBoxLayout *hBoxLayout;
    RadioButtonDemo(){

        hBoxLayout = new QHBoxLayout();

        RadioButton *button1 = new RadioButton("Option 1", this);
        RadioButton *button2 = new RadioButton("Option 1", this);        
        RadioButton *button3 = new RadioButton("Option 1", this);

        hBoxLayout->addWidget(button1, 0, Qt::AlignCenter);
        hBoxLayout->addWidget(button2, 0, Qt::AlignCenter);
        hBoxLayout->addWidget(button3, 0, Qt::AlignCenter);
        

        setLayout(hBoxLayout);
        resize(400, 400);
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
    RadioButtonDemo *w = new RadioButtonDemo();
    w->show();
    return app->exec();
}