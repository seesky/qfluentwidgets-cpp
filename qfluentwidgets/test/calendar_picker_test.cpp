#include <iostream>
#include <QtCore>
#include <QtWidgets>
#include <QtCore/Qt>
#include "../components/date_time/calendar_picker.h"



class WindowView : public QWidget{
public:
    WindowView(){
        setStyleSheet("ButtonView{background: rgb(255,255,255)}");
    }
};

class CalendarPickerDemo : public QWidget{
public:
    
    CalendarPicker *picker;
    QHBoxLayout *hBoxLayout;

    CalendarPickerDemo(){
        this->setStyleSheet(QString("Demo{background: white}"));

        this->picker = new CalendarPicker(this);
        
        this->hBoxLayout = new QHBoxLayout(this);
        this->hBoxLayout->addWidget(this->picker, 0, Qt::AlignCenter);
        this->resize(500, 500);
    }

};



int main(int argc, char *argv[])
{
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    
    QApplication *app = new QApplication(argc, argv);
    CalendarPickerDemo *w = new CalendarPickerDemo();
    w->show();
    return app->exec();
}