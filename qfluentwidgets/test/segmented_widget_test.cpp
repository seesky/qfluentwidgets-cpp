#include <QtCore/Qt>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QHBoxLayout>

#include "../components/navigation/segmented_widget.h"
#include "../common/style_sheet.h"
#include "../common/icon.h"
#include "../components/navigation/navigation_widget.h"

class Demo : public QWidget{
public:
    SegmentedWidget *pivot;
    QStackedWidget *stackedWidget;
    QVBoxLayout *vBoxLayout;
    QLabel *songInterface;
    QLabel *albumInterface;
    QLabel *artistInterface;

    Demo() : QWidget(){
        this->setObjectName(QString("Demo"));
        this->setStyleSheet(QString("Demo{background: white}QLabel{font: 20px 'Segoe UI';background: rgb(210,210,210);border-radius: 8px;}"));
        this->resize(400, 400);

        this->pivot = new SegmentedWidget(this);
        this->stackedWidget = new QStackedWidget(this);

        this->vBoxLayout = new QVBoxLayout(this);

        this->songInterface = new QLabel(QString("Song Interface"), this);
        this->albumInterface = new QLabel(QString("Album Interface"), this);
        this->artistInterface = new QLabel(QString("Artist Interface"), this);

        FluentIcon *musicIcon = new FluentIcon();
        musicIcon->setIconName(QString("MUSIC"));
        this->addSubInterface(this->songInterface, QString("songInterface"), QString("Song"));

        FluentIcon *albumIcon = new FluentIcon();
        albumIcon->setIconName(QString("ALBUM"));
        this->addSubInterface(this->albumInterface, QString("albumInterface"), QString("Album"));

        FluentIcon *artisIcon = new FluentIcon();
        artisIcon->setIconName(QString("PEOPLE"));
        this->addSubInterface(this->artistInterface, QString("artistInterface"), QString("Artist"));

        this->vBoxLayout->addWidget(this->pivot);
        this->vBoxLayout->addWidget(this->stackedWidget);
        this->vBoxLayout->setContentsMargins(30, 30, 30, 30);

        connect(this->stackedWidget, &QStackedWidget::currentChanged, this, &Demo::onCurrentInterfaceChanged);
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


public slots:
    void onCurrentInterfaceChanged(int index)
    {
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
    Demo *w = new Demo();
    w->show();
    return app->exec();
}