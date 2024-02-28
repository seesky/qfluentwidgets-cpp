#include <QtCore/QDate>
#include <QtCore/Qt>
#include <QtCore/QTime>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include "../components/date_time/time_picker.h"
#include "../components/date_time/picker_base.h"
#include "../components/date_time/date_picker.h"

class SecondsFormatter : public PickerColumnFormatter{
public:
    QString encode(QVariant value) override{
        if(value.canConvert<QString>()){ //TODO:是否能处理所有的数据类型？
            return value.value<QString>() + "秒"; 
        }else if(value.canConvert<int>()){
            return QString::number(value.value<int>());
        }
    };
    QVariant decode(QString value) override{
        return QVariant::fromValue<int>(value.left(value.length() - 1).toInt());
    };
};

class WindowView : public QWidget{
public:
    WindowView(){
        setStyleSheet("ButtonView{background: rgb(255,255,255)}");
    }
};

class TimePickerDemo : public QWidget{
public:
    

    QVBoxLayout *vBoxLayout;
    
    PickerBase *pickerBase;
    DatePicker *datePicker1;
    ZhDatePicker *datePicker2;
    AMTimePicker *timePicker1;
    TimePicker *timePicker2;
    TimePicker *timePicker3;


    TimePickerDemo(){
        this->setStyleSheet(QString("Demo{background: white}"));
        this->vBoxLayout = new QVBoxLayout(this);

        this->datePicker1 = new DatePicker(this, DatePicker::MM_DD_YYYY, true);
        this->datePicker2 = new ZhDatePicker(this);
        this->timePicker1 = new AMTimePicker(this, false);
        this->timePicker2 = new TimePicker(this, false);
        this->timePicker3 = new TimePicker(this, true);

        this->timePicker3->setColumnFormatter(this->timePicker3, 2, new SecondsFormatter());

        this->resize(500, 500);
        this->vBoxLayout->addWidget(this->datePicker1, 0, Qt::AlignHCenter);
        this->vBoxLayout->addWidget(this->datePicker2, 0, Qt::AlignHCenter);
        this->vBoxLayout->addWidget(this->timePicker1, 0, Qt::AlignHCenter);
        this->vBoxLayout->addWidget(this->timePicker2, 0, Qt::AlignHCenter);
        this->vBoxLayout->addWidget(this->timePicker3, 0, Qt::AlignHCenter);
    }

};



int main(int argc, char *argv[])
{
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    
    QApplication *app = new QApplication(argc, argv);
    TimePickerDemo *w = new TimePickerDemo();
    w->show();
    return app->exec();
}