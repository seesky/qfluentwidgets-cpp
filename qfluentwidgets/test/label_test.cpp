#include <QtCore/Qt>
#include <QtCore/QSize>
#include <QtCore/QPoint>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>

#include "../components/widgets/state_tool_tip.h"
#include "../components/widgets/button.h"
#include "../common/icon.h"
#include "../common/style_sheet.h"
#include "../components/widgets/label.h"

class Demo : public QWidget{
public:

    QVBoxLayout *vBoxLayout;
    HyperlinkLabel *hyperlinkLabel;

    Demo(){
        this->vBoxLayout = new QVBoxLayout(this);
        this->vBoxLayout->setContentsMargins(30, 30, 30, 30);
        this->vBoxLayout->setSpacing(20);

        this->hyperlinkLabel = new HyperlinkLabel(QUrl("https://github.com"), QString("GitHub"), nullptr);

        this->vBoxLayout->addWidget(this->hyperlinkLabel);
        this->vBoxLayout->addWidget(new CaptionLabel(QString("Caption"), nullptr));
        this->vBoxLayout->addWidget(new BodyLabel(QString("Body"), nullptr));
        this->vBoxLayout->addWidget(new StrongBodyLabel(QString("Body Strong"), nullptr));
        this->vBoxLayout->addWidget(new SubtitleLabel(QString("Subtitle"), nullptr));
        this->vBoxLayout->addWidget(new TitleLabel(QString("Title"), nullptr));
        this->vBoxLayout->addWidget(new LargeTitleLabel(QString("Title Large"), nullptr));
        this->vBoxLayout->addWidget(new DisplayLabel(QString("Display"), nullptr));

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