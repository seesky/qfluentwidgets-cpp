#include <iostream>
#include <QtCore>
#include <QtWidgets>
#include <QtCore/Qt>
#include "../components/widgets/button.h"
#include "../components/widgets/teaching_tip.h"


class CustomFlyoutView : public FlyoutViewBase{
public:
    CustomFlyoutView(QWidget *parent) : FlyoutViewBase(parent){
        this->vBoxLayout = new QVBoxLayout(this);
        this->label = new BodyLabel(QString("这是一场「试炼」，我认为这就是一场为了战胜过去的「试炼」，\n只有战胜了那些幼稚的过去，人才能有所成长。"), nullptr);
        this->button = new PrimaryPushButton(QString("Action"), nullptr, nullptr);
        this->button->setFixedWidth(140);
        this->vBoxLayout->setSpacing(12);
        this->vBoxLayout->setContentsMargins(20, 16, 20, 16);
        this->vBoxLayout->addWidget(this->label);
        this->vBoxLayout->addWidget(this->button);
    };

    QVBoxLayout *vBoxLayout;
    BodyLabel *label;
    PrimaryPushButton *button;
};


class ButtonView : public QWidget{
public:
    ButtonView(){
        setStyleSheet("ButtonView{background: rgb(255,255,255)}");
    }
};



class FlyoutViewTest : public ButtonView{
public:

    
    QHBoxLayout *vBoxLayout;
    PushButton *button1;
    PushButton *button2;
    PushButton *button3;


    FlyoutViewTest(){
        this->vBoxLayout = new QHBoxLayout(this);
        this->button1 = new PushButton(QString("Top"), this, nullptr);
        this->button2 = new PushButton(QString("Bottom"), this, nullptr);
        this->button3 = new PushButton(QString("Custom"), this, nullptr);

        this->resize(750, 550);
        this->button1->setFixedWidth(150);
        this->button2->setFixedWidth(150);
        this->button3->setFixedWidth(150);
        this->vBoxLayout->addWidget(this->button1, 0, Qt::AlignBottom);
        this->vBoxLayout->addWidget(this->button2, 0, Qt::AlignBottom);
        this->vBoxLayout->addWidget(this->button3, 0, Qt::AlignBottom);
        this->vBoxLayout->setContentsMargins(30, 50, 30, 50);

        connect(this->button1, &PushButton::clicked, this, &FlyoutViewTest::showFlyout1);
        connect(this->button2, &PushButton::clicked, this, &FlyoutViewTest::showFlyout2);
        connect(this->button3, &PushButton::clicked, this, &FlyoutViewTest::showFlyout3);
       
    };


public slots:
    void showFlyout1(bool isChecked)
    {
        TeachingTipTailPosition position = TeachingTipTailPosition::BOTTOM;
        TeachingTipView *view = new TeachingTipView(QString("Lesson 5"), QString("最短的捷径就是绕远路，绕远路才是我的最短捷径。"), new QVariant(), new QVariant(QVariant::fromValue<QString>(QString("resource/Gyro.jpg"))), true, position, nullptr);
        PushButton *button = new PushButton(QString("Action"), nullptr, nullptr);
        button->setFixedWidth(120);
        view->addWidget(button, 0, Qt::AlignRight);

        TeachingTip *w = TeachingTip::make(view, this->button1, -1, position, this, true);

        connect(view, &TeachingTipView::closed, w, &TeachingTip::close);
    };

    void showFlyout2(bool isChecked)
    {
        InfoBarIcon *_icon = new InfoBarIcon();
        _icon->setIconName(QString("SUCCESS"));
        QVariant *__icon = new QVariant();
        __icon->setValue<InfoBarIcon>(*_icon);
        TeachingTip::create(this->button2, QString("Lesson 4"), QString("表达敬意吧，表达出敬意，然后迈向回旋的另一个全新阶段！"), __icon, new QVariant(), true, 2000, TeachingTipTailPosition::TOP, this, true);
    };

    void showFlyout3(bool isChecked)
    {
        PopupTeachingTip::make(new CustomFlyoutView(nullptr), this->button3,  2000, TeachingTipTailPosition::RIGHT, this, true);
    };
};



int main(int argc, char *argv[])
{
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    
    QApplication *app = new QApplication(argc, argv);
    FlyoutViewTest *w = new FlyoutViewTest();
    w->show();
    return app->exec();
}