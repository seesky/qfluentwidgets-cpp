#include <QtCore/QDate>
#include <QtCore/Qt>
#include <QtCore/QTime>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include "../components/widgets/arcylic_label.h"


class AcrylicBrushDemo : public QWidget{
public:
    

    AcrylicBrush *acrylicBrush;

    AcrylicBrushDemo() : QWidget(){
        this->resize(400, 400);
        this->acrylicBrush = new AcrylicBrush(this, 15, QColor(242, 242, 242, 150), QColor(255, 255, 255, 10), 0.03);
       
        QPainterPath path = QPainterPath();
        path.addEllipse(0, 0, 400, 400);
        this->acrylicBrush->setClipPath(path);

        this->acrylicBrush->setImage(QVariant::fromValue<QPixmap>(QPixmap("resource/shoko.png").scaled(400, 400, Qt::KeepAspectRatio, Qt::SmoothTransformation)));

        
    }

    void paintEvent(QPaintEvent *event) override{
        this->acrylicBrush->paint();
        QWidget::paintEvent(event);
    }

};



int main(int argc, char *argv[])
{
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    
    QApplication *app = new QApplication(argc, argv);
    AcrylicBrushDemo *w = new AcrylicBrushDemo();
    w->show();
    return app->exec();
}