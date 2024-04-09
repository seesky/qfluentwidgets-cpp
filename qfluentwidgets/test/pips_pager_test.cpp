#include <QtCore/Qt>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>

#include "../components/widgets/pips_pager.h"
#include "../common/style_sheet.h"
#include "../common/config.h"

class Demo : public QWidget{
public:
    Demo(QWidget *parent) : QWidget(parent){
        this->vPager = new VerticalPipsPager(this);
        this->hPager = new HorizontalPipsPager(this);

        this->hPager->setPageNumber(15);
        this->vPager->setPageNumber(15);

        this->hPager->setVisibleNumber(8);
        this->hPager->setNextButtonDisplayMode(PipsScrollButtonDisplayMode::ALWAYS);
        this->hPager->setPreviousButtonDisplayMode(PipsScrollButtonDisplayMode::ALWAYS);

        this->vPager->setNextButtonDisplayMode(PipsScrollButtonDisplayMode::ALWAYS);
        this->vPager->setPreviousButtonDisplayMode(PipsScrollButtonDisplayMode::ON_HOVER);

        this->setLayout(new QHBoxLayout());
        this->layout()->addWidget(this->hPager);
        this->layout()->addWidget(this->vPager);

        this->resize(500, 500);
    }

    VerticalPipsPager *vPager;
    HorizontalPipsPager *hPager;
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