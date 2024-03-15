#include <QtCore/Qt>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include "../components/dialog_box/message_dialog.h"
#include "../components/widgets/button.h"
#include "../components/dialog_box/dialog.h"


class WindowView : public QWidget{
public:
    WindowView(){
        setStyleSheet("ButtonView{background: rgb(255,255,255)}");
    }
};

class MessageDialogDemo : public QWidget{
public:
    

    QVBoxLayout *vBoxLayout;
    PrimaryPushButton *btn;

    MessageDialogDemo(){
        this->vBoxLayout = new QVBoxLayout(this);

        this->btn = new PrimaryPushButton(QString("Click Me"), this, nullptr);
        this->resize(1000,  500);
        this->btn->move(455, 25);
        connect(this->btn, &PrimaryPushButton::clicked, this, &MessageDialogDemo::showDialog);
    }

public slots:
    void showDialog(){
       QString title = QString("Are you sure you want to delete the folder?");
       QString content = QString("If you delete the \"Music\" folder from the list, the folder will no longer appear in the list, but will not be deleted.");
       MessageBoxF *w = new MessageBoxF(title, content, this);
       if(w->exec()){
            qDebug() << QString("Yes button is pressed");
       }else{
            qDebug() << QString("Cancel button is pressed");
       }
    };
};



int main(int argc, char *argv[])
{
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    
    QApplication *app = new QApplication(argc, argv);
    MessageDialogDemo *w = new MessageDialogDemo();
    w->show();
    return app->exec();
}