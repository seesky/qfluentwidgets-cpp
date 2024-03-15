#include <QtCore/Qt>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include "../components/dialog_box/folder_list_dialog.h"
#include "../components/widgets/button.h"


class WindowView : public QWidget{
public:
    WindowView(){
        setStyleSheet("ButtonView{background: rgb(255,255,255)}");
    }
};

class FolderListDialogDemo : public QWidget{
public:
    

    QVBoxLayout *vBoxLayout;
    PrimaryPushButton *btn;

    FolderListDialogDemo(){
        this->vBoxLayout = new QVBoxLayout(this);

        this->btn = new PrimaryPushButton(QString("Click Me"), this, nullptr);
        this->resize(950,  500);
        this->vBoxLayout->addWidget(this->btn, 0, Qt::AlignHCenter);
        connect(this->btn, &PrimaryPushButton::clicked, this, &FolderListDialogDemo::showDialog);
    }

public slots:
    void showDialog(){
        QStringList folder_paths = QStringList();
        folder_paths.append(QString("D:/KuGou"));
        folder_paths.append(QString("C:/Users/shoko/Documents/Music"));
        
        QString title = QString("Build your collection from your local music files");
        QString content = QString("Right now, we're watching these folders:");
        FolderListDialog *w = new FolderListDialog(folder_paths, title, content, this);
        connect(w, &FolderListDialog::folderChanged, this, [](const QStringList& x){
            for(int i = 0; i < x.length(); i++){
                qDebug() << x.at(i);
            }
        });
        w->exec();
    };
};



int main(int argc, char *argv[])
{
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    
    QApplication *app = new QApplication(argc, argv);
    FolderListDialogDemo *w = new FolderListDialogDemo();
    w->show();
    return app->exec();
}