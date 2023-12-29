#include <iostream>
#include <QtCore>
#include <QtWidgets>
#include "./qfluentwidgets/components/widgets/button.h"

class ButtonView : public QWidget{
public:
    ButtonView(){
        setStyleSheet("ButtonView{background: rgb(255,255,255)}");
    }
};

class PushButtonDemo : public ButtonView{
public:
    PushButton *pushButton1;
    PushButton *pushButton2;
    PrimaryPushButton *primaryButton1;
    PrimaryPushButton *primaryButton2;
    TransparentPushButton *transparentPushButton1;
    TransparentPushButton *transparentPushButton2;
    ToggleButton *ToggleButton1;
    ToggleButton *ToggleButton2;
    QGridLayout *gridLayout;
    PushButtonDemo(){
        
        //push button
        pushButton1 = new PushButton(QString("Standard push button"), nullptr, nullptr);
        FluentIcon *pushButton2Icon = new FluentIcon();
        pushButton2Icon->setIconName("FOLDER");
        pushButton2 = new PushButton(pushButton2Icon, "Standard push button with icon", this);
        //primary color push button
        primaryButton1 = new PrimaryPushButton(QString("Accent style button"), this, nullptr);
        FluentIcon *primaryButton2Icon = new FluentIcon();
        primaryButton2Icon->setIconName("UPDATE");
        primaryButton2 = new PrimaryPushButton(primaryButton2Icon, "Accent style button with icon", this);
        //transparent push button
        transparentPushButton1 = new TransparentPushButton("Transparent push button", this, nullptr);
        FluentIcon *transparentPushButton2Icon = new FluentIcon();
        transparentPushButton2Icon->setIconName("BOOK_SHELF");
        transparentPushButton2 = new TransparentPushButton(transparentPushButton2Icon, "Transparent push button", this);
        //toggle button
        ToggleButton1 = new ToggleButton("Toggle push button", this, nullptr);


        gridLayout = new QGridLayout();
        gridLayout->addWidget(pushButton1, 0, 0);
        gridLayout->addWidget(pushButton2, 0, 1);
        gridLayout->addWidget(primaryButton1, 1, 0);
        gridLayout->addWidget(primaryButton2, 1, 1);
        gridLayout->addWidget(transparentPushButton1, 2, 0);
        gridLayout->addWidget(transparentPushButton2, 2, 1);
        gridLayout->addWidget(ToggleButton1, 3, 0);
        setLayout(gridLayout);
        resize(600, 700);
    }
};

int main(int argc, char *argv[])
{
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    
    QApplication *app = new QApplication(argc, argv);
    PushButtonDemo *w = new PushButtonDemo();
    w->show();
    return app->exec();
}