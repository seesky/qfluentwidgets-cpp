#include <iostream>
#include <QtCore>
#include <QtWidgets>
#include <QtCore/Qt>
#include "../components/widgets/check_box.h"


class WindowView : public QWidget{
public:
    WindowView(){
        setStyleSheet("ButtonView{background: rgb(255,255,255)}");
    }
};

class CheckBoxDemo : public WindowView{
public:
    

    CheckBox *checkBox;

    QHBoxLayout *hBoxLayout;
    CheckBoxDemo(){

        hBoxLayout = new QHBoxLayout();

        checkBox = new CheckBox("This is a check box", this);

        hBoxLayout->addWidget(checkBox, 1, Qt::AlignCenter);
        

        setLayout(hBoxLayout);
        resize(400, 400);
    }

public slots:
    void toggleToolButtonPrint()
    {
        qDebug() << "toggleToolButtonPrint...";
    }
};


int main(int argc, char *argv[])
{
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    
    QApplication *app = new QApplication(argc, argv);
    CheckBoxDemo *w = new CheckBoxDemo();
    w->show();
    return app->exec();
}