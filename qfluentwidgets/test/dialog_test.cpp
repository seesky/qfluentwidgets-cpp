#include <QtCore/QDate>
#include <QtCore/Qt>
#include <QtCore/QTime>
#include <QtCore/QUrl>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include "../components/dialog_box/dialog.h"
#include "../components/widgets/label.h"
#include "../components/widgets/line_edit.h"
#include "../components/widgets/button.h"
#include "../common/style_sheet.h"


class WindowView : public QWidget{
public:
    WindowView(){
        setStyleSheet("ButtonView{background: rgb(255,255,255)}");
    }
};

class DialogDemo : public QWidget{
public:
    

    QVBoxLayout *vBoxLayout;
    PrimaryPushButton *btn;

    DialogDemo(){
        this->vBoxLayout = new QVBoxLayout(this);

        this->btn = new PrimaryPushButton(QString("打开 URL"), this, nullptr);
        this->resize(950,  500);
        this->vBoxLayout->addWidget(this->btn, 0, Qt::AlignHCenter);
        connect(this->btn, &PrimaryPushButton::clicked, this, &DialogDemo::showDialog);
    }

public slots:
    void showDialog(){
        QString title = QString("Are you sure you want to delete the folder?");
        QString content = QString("If you delete the 'Music' folder from the list, the folder will no longer appear in the list, but will not be deleted.");
        Dialog *w = new Dialog(title, content, this);
        if(w->exec()){
            qDebug() << "Yes button is pressed";
        }else{
            qDebug() << "Cancel button is pressed";
        }
    };
};



int main(int argc, char *argv[])
{
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    
    QApplication *app = new QApplication(argc, argv);
    DialogDemo *w = new DialogDemo();
    w->show();
    return app->exec();
}