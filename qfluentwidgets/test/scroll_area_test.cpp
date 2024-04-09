#include <QtCore/QEasingCurve>
#include <QtCore/Qt>
#include <QtGui/QPixmap>
#include <QtWidgets/QApplication>
#include "../components/widgets/label.h"
#include "../components/widgets/scroll_area.h"


class Demo : public SmoothScrollArea{
public:
    Demo(QWidget *parent) : SmoothScrollArea(parent){
        this->label = new PixmapLabel(this);
        this->label->setPixmap(new QPixmap("resource/pips_pager_resource/shoko.jpg"));

        this->setScrollAnimation(Qt::Vertical, 400, QEasingCurve::OutQuint);
        this->setScrollAnimation(Qt::Horizontal, 400, QEasingCurve::OutQuint);

        this->horizontalScrollBar()->setValue(1900);
        this->setWidget(this->label);
        this->resize(1200, 800);

        QFile file("resource/pips_pager_resource/demo.qss");
        if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream stream(&file);
            QString stylesheet = stream.readAll();
            this->setStyleSheet(stylesheet);
            file.close();
        } else {
            // 处理错误，例如，文件无法打开
        }
    }

    PixmapLabel *label;

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