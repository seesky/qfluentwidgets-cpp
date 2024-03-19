#include <iostream>
#include <QtCore>
#include <QtWidgets>
#include <QtCore/Qt>
#include "../../qfluentwidgets/components/layout/flow_layout.h"



class FlowLayoutView : public QWidget{
public:
   
    
    FlowLayout *layout;
    FlowLayoutView(){
        layout = new FlowLayout(this, true, false);
        
        layout->setAnimation(250, QEasingCurve::OutQuad);
        layout->setContentsMargins(30, 30, 30, 30);
        layout->setVerticalSpacing(20);
        layout->setHorizontalSpacing(10);

        layout->addWidget(new QPushButton(QString("aiko")));
        layout->addWidget(new QPushButton(QString("刘静爱")));
        layout->addWidget(new QPushButton(QString("柳井爱子")));
        layout->addWidget(new QPushButton(QString("aiko 赛高")));
        layout->addWidget(new QPushButton(QString("aiko 太爱啦😘")));

        this->resize(250, 300);
        this->setStyleSheet(QString("Demo{background: white} QPushButton{padding: 5px 10px; font:15px 'Microsoft YaHei'}"));  //TODO:特殊关注
    }


public slots:

};



int main(int argc, char *argv[])
{
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    
    QApplication *app = new QApplication(argc, argv);
    FlowLayoutView *w = new FlowLayoutView();
    w->show();
    return app->exec();
}