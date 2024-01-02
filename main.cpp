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
    TransparentTogglePushButton *transparentTogglePushButton1;
    TransparentTogglePushButton *transparentTogglePushButton2;
    HyperlinkButton *hyperlinkButton1;
    HyperlinkButton *hyperlinkButton2;
    QGridLayout *gridLayout;
    PushButtonDemo(){

        gridLayout = new QGridLayout();

        ///*
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
        FluentIcon *ToggleButton2Icon = new FluentIcon();
        ToggleButton2Icon->setIconName("SEND");
        ToggleButton2 = new ToggleButton(ToggleButton2Icon, "Toggle push button", this);
        //transparent toggle push button
        transparentTogglePushButton1 = new TransparentTogglePushButton("Transparent toggle button", this, nullptr);
        FluentIcon *transparentTogglePushButton2Icon = new FluentIcon();
        transparentTogglePushButton2Icon->setIconName("BOOK_SHELF");
        transparentTogglePushButton2 = new TransparentTogglePushButton(transparentTogglePushButton2Icon, "Transparent toggle button", this);

        //hyperlink button
        QVariant url = QVariant::fromValue<QString>(QString("http://www.usable-programming.com"));
        hyperlinkButton1 = new HyperlinkButton(&url, "Hyper link button", this, nullptr);
        FluentIcon *hyperlinkButton2Icon = new FluentIcon();
        hyperlinkButton2Icon->setIconName("LINK");
        hyperlinkButton2 = new HyperlinkButton(hyperlinkButton2Icon, &url, "Hyper link button", this);


        gridLayout->addWidget(pushButton1, 0, 0);
        gridLayout->addWidget(pushButton2, 0, 1);
        gridLayout->addWidget(primaryButton1, 1, 0);
        gridLayout->addWidget(primaryButton2, 1, 1);
        gridLayout->addWidget(transparentPushButton1, 2, 0);
        gridLayout->addWidget(transparentPushButton2, 2, 1);
        //*/
        gridLayout->addWidget(ToggleButton1, 3, 0);
        gridLayout->addWidget(ToggleButton2, 3, 1);
        gridLayout->addWidget(transparentTogglePushButton1, 4, 0);
        gridLayout->addWidget(transparentTogglePushButton2, 4, 1);
        gridLayout->addWidget(hyperlinkButton1, 5, 0);
        gridLayout->addWidget(hyperlinkButton2, 5, 1);
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