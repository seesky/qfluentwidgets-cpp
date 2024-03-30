#include <iostream>
#include <QtWidgets>
#include <QtCore/Qt>
#include "../../qfluentwidgets/components/material/acrylic_flyout.h"


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
        this->button1 = new PushButton(QString("Click Me"), this, nullptr);
        this->button2 = new PushButton(QString("Click Me"), this, nullptr);
        this->button3 = new PushButton(QString("Click Me"), this, nullptr);

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
        
        InfoBarIcon *_icon = new InfoBarIcon();
        _icon->setIconName(QString("SUCCESS"));
        QVariant *__icon = new QVariant();
        __icon->setValue<InfoBarIcon>(*_icon);


        AcrylicFlyout::create(
            QString("Lesson 4"),
            QString("表达敬意吧，表达出敬意，然后迈向回旋的另一个全新阶段！"),
            __icon,
            new QVariant(),
            true,
            QVariant::fromValue<QWidget*>(this->button1),
            this,
            FlyoutAnimationType::PULL_UP,
            true
        );

        
    };

    void showFlyout2(bool isChecked)
    {
        AcrylicFlyoutView *view = new AcrylicFlyoutView(
            QString("杰洛·齐贝林"),
            QString("触网而起的网球会落到哪一侧，谁也无法知晓。\n如果那种时刻到来，我希望「女神」是存在的。\n这样的话，不管网球落到哪一边，我都会坦然接受的吧。"),
            new QVariant(),
            new QVariant(QVariant::fromValue<QString>(QString("resource/SBR.jpg"))),
            true,
            nullptr
        );

        PushButton *button = new PushButton(QString("Action"), nullptr, nullptr);
        button->setFixedWidth(120);
        view->addWidget(button, 0, Qt::AlignRight);

        view->widgetLayout->insertSpacing(1, 5);
        view->widgetLayout->addSpacing(5);

        AcrylicFlyout *w = AcrylicFlyout::make(view, QVariant::fromValue<QWidget*>(this->button2), this, FlyoutAnimationType::PULL_UP, true);
        connect(view, &FlyoutView::closed, w, &AcrylicFlyout::close);
    };

    void showFlyout3(bool isChecked)
    {
        AcrylicFlyout::make(new CustomFlyoutView(nullptr), QVariant::fromValue<QWidget*>(this->button3), this, FlyoutAnimationType::DROP_DOWN, true);
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