#include <QtCore/Qt>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>

#include "../components/navigation/pivot.h"
#include "../common/style_sheet.h"

class Demo : public QWidget{
public:
    Pivot *pivot;
    QStackedWidget *stackedWidget;
    QVBoxLayout *vBoxLayout;
    QLabel *songInterface;
    QLabel *albumInterface;
    QLabel *artistInterface;
    Demo(QWidget *parent) : QWidget(parent){
        this->setObjectName("Demo");
        this->setStyleSheet(QString("Demo{background: white} QLabel{ font: 20px 'Segoe UI'; background: rgb(142,142,142); border-radius: 8px;}"));
        this->resize(400, 400);
        this->pivot = new Pivot(this);
        this->stackedWidget = new QStackedWidget(this);
        this->vBoxLayout = new QVBoxLayout(this);

        this->songInterface = new QLabel(QString("Song Interface"), this);
        this->albumInterface = new QLabel(QString("Album Interface"), this);
        this->artistInterface = new QLabel(QString("Artist Interface"), this);

        this->addSubInterface(this->songInterface, QString("songInterface"), QString("Song"));
        this->addSubInterface(this->albumInterface, QString("albumInterface"), QString("Album"));
        this->addSubInterface(this->artistInterface, QString("artistInterface"), QString("Artist"));

        this->vBoxLayout->addWidget(this->pivot, 0, Qt::AlignHCenter);
        this->vBoxLayout->addWidget(this->stackedWidget);
        this->vBoxLayout->setContentsMargins(30, 0, 30, 30);

        connect(this->stackedWidget, &QStackedWidget::currentChanged, this, &Demo::onCurrentIndexChanged);
        this->stackedWidget->setCurrentWidget(this->songInterface);
        this->pivot->setCurrentItem(this->songInterface->objectName());
    }


    void addSubInterface(QLabel *widget, QString objectName, QString text)
    {
        widget->setObjectName(objectName);
        widget->setAlignment(Qt::AlignCenter);
        this->stackedWidget->addWidget(widget);
        this->pivot->addItem(objectName, text, [this, widget](){
            this->stackedWidget->setCurrentWidget(widget);
        }, new QVariant());
    }

    void onCurrentIndexChanged(int index){
        QWidget *widget = this->stackedWidget->widget(index);
        this->pivot->setCurrentItem(widget->objectName());
    }
};


int main(int argc, char *argv[])
{
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    
    QApplication *app = new QApplication(argc, argv);
    Demo *w = new Demo(nullptr);
    w->show();
    return app->exec();
}