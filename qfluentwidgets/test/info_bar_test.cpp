#include <QtCore/Qt>
#include <QtCore/QSize>
#include <QtCore/QPoint>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>

#include "../components/widgets/info_bar.h"
#include "../components/widgets/button.h"
#include "../common/icon.h"
#include "../common/style_sheet.h"

class Demo : public QWidget{
public:

    QHBoxLayout *hBoxLayout;
    PushButton *button1;
    PushButton *button2;
    PushButton *button3;
    PushButton *button4;
    PushButton *button5;
    Demo(){
        this->hBoxLayout = new QHBoxLayout(this);
        this->button1 = new PushButton(QString("Information"), this, nullptr);
        this->button2 = new PushButton(QString("Success"), this, nullptr);
        this->button3 = new PushButton(QString("Warning"), this, nullptr);
        this->button4 = new PushButton(QString("Error"), this, nullptr);
        this->button5 = new PushButton(QString("Custom"), this, nullptr);

        connect(this->button1, &PushButton::clicked, this, &Demo::createInfoInfoBar);
        connect(this->button2, &PushButton::clicked, this, &Demo::createSuccessInfoBar);
        connect(this->button3, &PushButton::clicked, this, &Demo::createWarningInfoBar);
        connect(this->button4, &PushButton::clicked, this, &Demo::createErrorInfoBar);
        connect(this->button5, &PushButton::clicked, this, &Demo::createCustomInfoBar);

        this->hBoxLayout->addWidget(this->button1);
        this->hBoxLayout->addWidget(this->button2);
        this->hBoxLayout->addWidget(this->button3);
        this->hBoxLayout->addWidget(this->button4);
        this->hBoxLayout->addWidget(this->button5);


        this->hBoxLayout->setContentsMargins(30, 0, 30, 0);


        this->resize(700, 700);
    };


public slots:
    InfoBarIcon *icon = new InfoBarIcon();
    
    void createInfoInfoBar(){
        QString content = QString("My name is kira yoshikake, 33 years old. Living in the villa area northeast of duwangting, unmarried. I work in Guiyou chain store. Every day I have to work overtime until 8 p.m. to go home. I don't smoke. The wine is only for a taste. Sleep at 11 p.m. for 8 hours a day. Before I go to bed, I must drink a cup of warm milk, then do 20 minutes of soft exercise, get on the bed, and immediately fall asleep. Never leave fatigue and stress until the next day. Doctors say I'm normal.");
        InfoBarIcon *icon = new InfoBarIcon();
        icon->setIconName(QString("INFORMATION"));

        InfoBar *w = new InfoBar(icon, QString("Title"), content, Qt::Orientation::Vertical, true, 2000, InfoBarPosition::TOP_RIGHT, this);
        w->addWidget(new PushButton(QString("Action"), nullptr, nullptr), 0);
        w->show();
    };
    void createSuccessInfoBar(){
        InfoBar::success(QString("Lesson 4"), QString("With respect, let's advance towards a new stage of the spin."),
            Qt::Horizontal, true, 2000, InfoBarPosition::TOP, this);
    };
    void createWarningInfoBar(){
        InfoBar::warning(QString("Lesson 3"), QString("Believe in the spin, just keep believing!"),
            Qt::Horizontal, false, 2000, InfoBarPosition::TOP_LEFT, this);
    };
    void createErrorInfoBar(){
        InfoBar::error(QString("Lesson 5"), QString("迂回路を行けば最短ルート。"),
            Qt::Horizontal, true, -1, InfoBarPosition::TOP_RIGHT, this);
    };
    void createCustomInfoBar(){
        
        InfoBarIcon *icon = new InfoBarIcon();
        icon->setIconName(QString("GITHUB"));
        InfoBar *w = InfoBar::_new(icon, QString("Zeppeli"), QString("人間讃歌は「勇気」の讃歌ッ！！ 人間のすばらしさは勇気のすばらしさ！！"), Qt::Orientation::Horizontal, true, 2000, InfoBarPosition::BOTTOM, this);
        //w->setCustomBackgroundColor(QVariant::fromValue<QString>("white"), QVariant::fromValue<QString>("#202020"));
        
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