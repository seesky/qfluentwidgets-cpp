#include <QtCore/Qt>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidgetItem>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>

#include "../components/widgets/list_view.h"
#include "../common/style_sheet.h"
#include "../common/config.h"


class Demo : public QWidget{
public:
    Demo(QWidget *parent) : QWidget(parent){
        this->hBoxLayout = new QHBoxLayout(this);
        this->listWidget = new ListWidget(this);

        stands = QStringList(); 
        stands << "白金之星" << "绿色法皇" << "天堂制造" << "绯红之王" << "银色战车" << "疯狂钻石" << "壮烈成仁" << "败者食尘" 
            << "黑蚊子多" << "杀手皇后" << "金属制品" << "石之自由" << "砸瓦鲁多" << "钢链手指" << "臭氧宝宝" << "华丽挚爱" << "隐者之紫" 
            << "黄金体验" << "虚无之王" << "虚无之王" << "纸月之王" << "骇人恶兽" << "男子领域" << "20世纪男孩" << "牙 Act 4" 
            << "铁球破坏者" << "D4C • 爱之列车" << "天生完美" << "佩斯利公园" << "软又湿" << "奇迹于你" << "行走的心" << "护霜旅行者"
             << "十一月雨" << "调情圣手" << "片刻静候";

        for(int i = 0; i < stands.length(); i++){
            QListWidgetItem *item = new QListWidgetItem(stands.at(i));
            this->listWidget->addItem(item);
        }

        this->setStyleSheet(QString("Demo{background: rgb(249, 249, 249)}"));
        this->hBoxLayout->setContentsMargins(0, 0, 0, 0);
        this->hBoxLayout->addWidget(this->listWidget);
        this->resize(300, 400);
    }

    QHBoxLayout *hBoxLayout;
    ListWidget *listWidget;
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