#include <QtCore/Qt>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidgetItem>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>

#include "../components/widgets/list_view.h"
#include "../components/widgets/table_view.h"
#include "../common/style_sheet.h"
#include "../common/config.h"



class Demo : public QWidget{
public:
    Demo(QWidget *parent) : QWidget(parent){
        this->hBoxLayout = new QHBoxLayout(this);
        this->tableView = new TableWidget(this);

        this->tableView->setBorderVisible(true);
        //this->tableView->setBorderRadius(8); //TODO:这个地方由于style_sheet的bug造成无法正确的设置，需要对style_sheet进行重写

        this->tableView->setWordWrap(false);
        this->tableView->setRowCount(60);
        this->tableView->setColumnCount(5);

        QList<QStringList> songInfos = QList<QStringList>();
        songInfos.append(QStringList() << "かばん" << "aiko" << "かばん" << "2004" << "5:04");
        songInfos.append(QStringList() << "爱你" << "王心凌" << "爱你" << "2004" << "3:39");
        songInfos.append(QStringList() << "星のない世界" << "aiko" << "星のない世界/横顔" << "2007" << "5:30");
        songInfos.append(QStringList() << "横顔" << "aiko" << "星のない世界/横顔" << "2007" << "5:06");
        songInfos.append(QStringList() << "秘密" << "aiko" << "秘密" << "2008" << "5:25");
        songInfos.append(QStringList() << "二人" << "aiko" << "二人" << "2008" << "5:00");
        songInfos.append(QStringList() << "スパークル" << "RADWIMPS" << "君の名は" << "2016" << "8:54");
        songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
        songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
        songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
        songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
        songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
        songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
        songInfos.append(QStringList() << "かばん" << "aiko" << "かばん" << "2004" << "5:04");
        songInfos.append(QStringList() << "爱你" << "王心凌" << "爱你" << "2004" << "3:39");
        songInfos.append(QStringList() << "星のない世界" << "aiko" << "星のない世界/横顔" << "2007" << "5:30");
        songInfos.append(QStringList() << "横顔" << "aiko" << "星のない世界/横顔" << "2007" << "5:06");
        songInfos.append(QStringList() << "秘密" << "aiko" << "秘密" << "2008" << "5:25");
        songInfos.append(QStringList() << "二人" << "aiko" << "二人" << "2008" << "5:00");
        songInfos.append(QStringList() << "スパークル" << "RADWIMPS" << "君の名は" << "2016" << "8:54");
        songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
        songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
        songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
        songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
        songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
        songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
        songInfos.append(QStringList() << "かばん" << "aiko" << "かばん" << "2004" << "5:04");
        songInfos.append(QStringList() << "爱你" << "王心凌" << "爱你" << "2004" << "3:39");
        songInfos.append(QStringList() << "星のない世界" << "aiko" << "星のない世界/横顔" << "2007" << "5:30");
        songInfos.append(QStringList() << "横顔" << "aiko" << "星のない世界/横顔" << "2007" << "5:06");
        songInfos.append(QStringList() << "秘密" << "aiko" << "秘密" << "2008" << "5:25");
        songInfos.append(QStringList() << "二人" << "aiko" << "二人" << "2008" << "5:00");
        songInfos.append(QStringList() << "スパークル" << "RADWIMPS" << "君の名は" << "2016" << "8:54");
        songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
        songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
        songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
        songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
        songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
        songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
        songInfos.append(QStringList() << "かばん" << "aiko" << "かばん" << "2004" << "5:04");
        songInfos.append(QStringList() << "爱你" << "王心凌" << "爱你" << "2004" << "3:39");
        songInfos.append(QStringList() << "星のない世界" << "aiko" << "星のない世界/横顔" << "2007" << "5:30");
        songInfos.append(QStringList() << "横顔" << "aiko" << "星のない世界/横顔" << "2007" << "5:06");
        songInfos.append(QStringList() << "秘密" << "aiko" << "秘密" << "2008" << "5:25");
        songInfos.append(QStringList() << "二人" << "aiko" << "二人" << "2008" << "5:00");
        songInfos.append(QStringList() << "スパークル" << "RADWIMPS" << "君の名は" << "2016" << "8:54");
        songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
        songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
        songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
        songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
        songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
        songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
        songInfos.append(QStringList() << "かばん" << "aiko" << "かばん" << "2004" << "5:04");
        songInfos.append(QStringList() << "爱你" << "王心凌" << "爱你" << "2004" << "3:39");
        songInfos.append(QStringList() << "星のない世界" << "aiko" << "星のない世界/横顔" << "2007" << "5:30");
        songInfos.append(QStringList() << "横顔" << "aiko" << "星のない世界/横顔" << "2007" << "5:06");
        songInfos.append(QStringList() << "秘密" << "aiko" << "秘密" << "2008" << "5:25");
        songInfos.append(QStringList() << "二人" << "aiko" << "二人" << "2008" << "5:00");
        songInfos.append(QStringList() << "スパークル" << "RADWIMPS" << "君の名は" << "2016" << "8:54");
        songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
        songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
        songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
        songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
        songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
        songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
        songInfos.append(QStringList() << "かばん" << "aiko" << "かばん" << "2004" << "5:04");
        songInfos.append(QStringList() << "爱你" << "王心凌" << "爱你" << "2004" << "3:39");
        songInfos.append(QStringList() << "星のない世界" << "aiko" << "星のない世界/横顔" << "2007" << "5:30");
        songInfos.append(QStringList() << "横顔" << "aiko" << "星のない世界/横顔" << "2007" << "5:06");
        songInfos.append(QStringList() << "秘密" << "aiko" << "秘密" << "2008" << "5:25");
        songInfos.append(QStringList() << "二人" << "aiko" << "二人" << "2008" << "5:00");
        songInfos.append(QStringList() << "スパークル" << "RADWIMPS" << "君の名は" << "2016" << "8:54");
        songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "どうしたって伝えられないから" << "2016" << "3:16");
        songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
        songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
        songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
        songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
        songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");

        songInfos += songInfos;

        for(int i = 0; i < songInfos.length(); i++){
            for(int n = 0; n < 5; n++){
                this->tableView->setItem(i, n, new QTableWidgetItem(songInfos.at(i).at(n)));
            }
        }

        this->tableView->verticalHeader()->hide();
        this->tableView->setHorizontalHeaderLabels(QStringList() << "Title" << "Artist" << "Album" << "Year" << "Duration");
        this->tableView->resizeRowsToContents();

        this->setStyleSheet(QString("Demo{background: rgb(255, 255, 255)} "));
        this->hBoxLayout->setContentsMargins(50, 30, 50, 30);
        this->hBoxLayout->addWidget(this->tableView);
        this->resize(735, 760);
    }

    QHBoxLayout *hBoxLayout;
    TableWidget *tableView;
    QStringList stands;

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