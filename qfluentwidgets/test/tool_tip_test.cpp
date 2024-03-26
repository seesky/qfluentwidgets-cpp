#include <QtCore/Qt>
#include <QtCore/QSize>
#include <QtCore/QPoint>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>

#include "../components/widgets/progress_bar.h"
#include "../components/widgets/button.h"
#include "../common/icon.h"
#include "../common/style_sheet.h"
#include "../components/widgets/tool_tip.h"

class Demo : public QWidget{
public:

    QHBoxLayout *hBox;
    PushButton *button1;
    PushButton *button2;
    PushButton *button3;
    Demo(){
        this->hBox = new QHBoxLayout(this);
        this->button1 = new PushButton(QString("キラキラ"), this, nullptr);
        this->button2 = new PushButton(QString("食べた愛"), this, nullptr);
        this->button3 = new PushButton(QString("シアワセ"), this, nullptr);

        this->button1->setToolTip(QString("aiko - キラキラ ✨"));
        this->button2->setToolTip(QString("aiko - 食べた愛 🥰"));
        this->button3->setToolTip(QString("aiko - シアワセ 😊"));
        this->button1->setToolTipDuration(1000);

        this->button1->installEventFilter(new ToolTipFilter(this->button1, 0, ToolTipPosition::TOP));
        this->button2->installEventFilter(new ToolTipFilter(this->button2, 0, ToolTipPosition::BOTTOM));
        this->button3->installEventFilter(new ToolTipFilter(this->button3, 300, ToolTipPosition::RIGHT));

        this->hBox->setContentsMargins(24, 24, 24, 24);
        this->hBox->setSpacing(16);
        this->hBox->addWidget(this->button1);
        this->hBox->addWidget(this->button2);
        this->hBox->addWidget(this->button3);

        this->resize(480, 240);
    };

};




int main(int argc, char *argv[])
{
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    
    QApplication *app = new QApplication(argc, argv);
    Demo *w = new Demo();
    w->show();
    return app->exec();
}