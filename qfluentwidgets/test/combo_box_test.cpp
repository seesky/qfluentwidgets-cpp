#include <iostream>
#include <QtCore>
#include <QtWidgets>
#include <QtCore/Qt>
#include "../components/widgets/combo_box.h"


class WindowView : public QWidget{
public:
    WindowView(){
        setStyleSheet("ButtonView{background: rgb(255,255,255)}");
    }
};

class ComBoxDemo : public WindowView{
public:
    

    ComboBox *comboBox;

    QHBoxLayout *hBoxLayout;
    ComBoxDemo(){

        hBoxLayout = new QHBoxLayout();

        comboBox = new ComboBox(this);

        comboBox->setPlaceholderText("选择一个");

        QList<QString> *items = new QList<QString>();
        items->append(QString("test1 🥰"));
        items->append(QString("test2 ☆"));
        items->append(QString("test3"));
        items->append(QString("test4"));

        comboBox->addItems(*items);
        comboBox->setCurrentIndex(-1);

        connect(comboBox, &ComboBox::currentTextChanged, this, &ComBoxDemo::toggleToolButtonPrint);

        hBoxLayout->addWidget(comboBox, 1, Qt::AlignCenter);
        

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
    ComBoxDemo *w = new ComBoxDemo();
    w->show();
    return app->exec();
}