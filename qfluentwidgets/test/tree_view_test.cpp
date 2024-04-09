#include <QtCore/Qt>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QFileSystemModel>
#include <QtWidgets/QHBoxLayout>

#include "../components/widgets/tree_view.h"
#include "../common/style_sheet.h"
#include "../common/config.h"

class Demo : public QWidget{
public:
    Demo(QWidget *parent) : QWidget(parent){
        this->hBoxLayout = new QHBoxLayout(this);
        this->setObjectName(QString("Demo"));
        this->setStyleSheet(QString("Demo{background:rgb(255,255,255)}"));

        this->view = new TreeView(this);
        this->model = new QFileSystemModel();
        this->model->setRootPath(QString("."));
        this->view->setModel(this->model);

        this->view->setBorderVisible(true);
        this->view->setBorderRadius(8);

        this->hBoxLayout->addWidget(this->view);
        this->hBoxLayout->setContentsMargins(50, 30, 50, 30);
        this->resize(800, 660);
        

    }

    QHBoxLayout *hBoxLayout;
    TreeView *view;
    QFileSystemModel *model;
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