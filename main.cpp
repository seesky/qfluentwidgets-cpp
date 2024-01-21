#include <iostream>
#include <QtCore>
#include <QtWidgets>
#include <QtCore/Qt>
#include "./qfluentwidgets/components/widgets/menu.h"
#include "./qfluentwidgets/components/widgets/button.h"
#include "./qfluentwidgets/qframelesswindow/windows/qframe_less_window.h"


class ButtonView : public QWidget{
public:
    ButtonView(){
        setStyleSheet("ButtonView{background: rgb(255,255,255)}");
    }
};

class CustomTitleBar : public StandardTitleBar{
public:
    CustomTitleBar(QWidget *parent) : StandardTitleBar(parent){
        this->minBtn->setHoverColor(new QColor(Qt::white));
        this->minBtn->setHoverBackgroundColor(new QColor(0, 100, 182));
        this->minBtn->setPressedColor(new QColor(Qt::white));
        this->minBtn->setPressedBackgroundColor(new QColor(54, 57, 65));

        this->maxBtn->setStyleSheet(QString("TitleBarButton {qproperty-hoverColor: white;qproperty-hoverBackgroundColor: rgb(0, 100, 182);qproperty-pressedColor: white;qproperty-pressedBackgroundColor: rgb(54, 57, 65);}"));
    };
private:
};

class Window : public WindowsFramelessWindow{
public:
    Window(QWidget *parent) : WindowsFramelessWindow(parent){
        WId win = this->winId();
        this->setTitleBar(new CustomTitleBar(this));
        this->label = new QLabel(this);
        this->label->setScaledContents(true);
        this->label->setPixmap(QPixmap("/qfluentwidgets/images/screenshot/shoko.png"));
        this->setWindowIcon(QIcon("/qfluentwidgets/images/screenshot/logo.png"));
        this->setWindowTitle(QString("Frameless Window"));
        this->setStyleSheet(QString("background:white"));
        this->titleBar->raise();
    }
    

    void resizeEvent(QResizeEvent *event){
        WindowsFramelessWindow::resizeEvent(event);
        int length = qMin(this->width(), this->height());
        this->label->resize(length, length);
        this->label->move(this->width() / 2 - length / 2, this->height() / 2 - length / 2);
    };
    

    QLabel *label;
private:
};

class Window2 : public AcrylicWindow{
public:
    Window2(QWidget *parent) : AcrylicWindow(parent){
        this->setWindowTitle(QString("Acrylic Window"));
        this->titleBar->raise();
    }
private:
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
    RadioButton *radioButton1;
    RadioButton *radioButton2;
    ToolButton *toolButton;
    TransparentToolButton *tranparentToolButton;
    PrimaryToolButton *primaryToolButton;
    ToggleToolButton *toggleToolButton;
    TransparentToggleToolButton *transparentToggleToolButton;


    RoundMenu *menu;
    DropDownPushButton *dropDownPushButton1;
    DropDownPushButton *dropDownPushButton2;
    TransparentDropDownPushButton *transparentDropDownPushButton1;
    TransparentDropDownPushButton *transparentDropDownPushButton2;

    DropDownToolButton *dropDownToolButton;
    TransparentDropDownToolButton *transparentDropDownToolButton;

    PrimaryDropDownPushButton *primaryDropDownPushButton1;
    PrimaryDropDownPushButton *primaryDropDownPushButton2;

    PrimaryDropDownToolButton *primaryDropDownToolButton;

    SplitPushButton *splitPushButton1;
    SplitPushButton *splitPushButton2;

    PrimarySplitPushButton *primarySplitPushButton1;
    PrimarySplitPushButton *primarySplitPushButton2;

    SplitToolButton *splitToolButton;

    QGridLayout *gridLayout;
    PushButtonDemo(){

        //WId win = this->winId();
        gridLayout = new QGridLayout();

        
        FluentIcon *menuActionIcon1 = new FluentIcon();
        menuActionIcon1->setIconName("BASKETBALL");
        FluentIcon *menuActionIcon2 = new FluentIcon();
        menuActionIcon2->setIconName("ALBUM");
        FluentIcon *menuActionIcon3 = new FluentIcon();
        menuActionIcon3->setIconName("MUSIC");
        this->menu = new RoundMenu(QString(""), nullptr);
        Action *a = new Action(menuActionIcon1, QString("Basketball"), nullptr);
        Action *b = new Action(menuActionIcon2, QString("Album"), nullptr);
        menu->addAction(a);
        menu->addAction(b);

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

        //radio button
        radioButton1 = new RadioButton("Option 1", this);
        radioButton2 = new RadioButton("Option 2", this);

        //tool button
        FluentIcon *toolbuttonIcon = new FluentIcon();
        toolbuttonIcon->setIconName("SETTING");
        toolButton = new ToolButton(toolbuttonIcon, this);

        FluentIcon *tranparentToolButtonIcon = new FluentIcon();
        tranparentToolButtonIcon->setIconName("SETTING");
        tranparentToolButton = new TransparentToolButton(tranparentToolButtonIcon, this);

        primaryToolButton = new PrimaryToolButton(toolbuttonIcon, this);

        FluentIcon *toggleToolButtonIcon = new FluentIcon();
        toggleToolButtonIcon->setIconName("SETTING");
        toggleToolButton = new ToggleToolButton(toggleToolButtonIcon, this);
        connect(toggleToolButton, &ToggleToolButton::toggled, this, &PushButtonDemo::toggleToolButtonPrint);

        FluentIcon *transparentToggleToolButtonIcon = new FluentIcon();
        transparentToggleToolButtonIcon->setIconName("SETTING");
        transparentToggleToolButton = new TransparentToggleToolButton(transparentToggleToolButtonIcon, this);

        FluentIcon *dropDownPushButton2ButtonIcon = new FluentIcon();
        dropDownPushButton2ButtonIcon->setIconName("MAIL");
        dropDownPushButton1 = new DropDownPushButton(QString("Email"), this, nullptr);
        dropDownPushButton1->setMenu(this->menu);
        dropDownPushButton2 = new DropDownPushButton(dropDownPushButton2ButtonIcon, QString("Email"), this);
        dropDownPushButton2->setMenu(this->menu);

        transparentDropDownPushButton1 = new TransparentDropDownPushButton(QString("Email"), this, nullptr);
        transparentDropDownPushButton2 = new TransparentDropDownPushButton(dropDownPushButton2ButtonIcon, QString("Email"), this);
        transparentDropDownPushButton1->setMenu(this->menu);
        transparentDropDownPushButton2->setMenu(this->menu);

        dropDownToolButton = new DropDownToolButton(dropDownPushButton2ButtonIcon, this);
        dropDownToolButton->setMenu(this->menu);

        transparentDropDownToolButton = new TransparentDropDownToolButton(dropDownPushButton2ButtonIcon, this);
        transparentDropDownToolButton->setMenu(this->menu);

        primaryDropDownPushButton1 = new PrimaryDropDownPushButton(dropDownPushButton2ButtonIcon, QString("Email"), this);
        primaryDropDownPushButton1->setMenu(this->menu);

        primaryDropDownToolButton = new PrimaryDropDownToolButton(dropDownPushButton2ButtonIcon, this);
        primaryDropDownToolButton->setMenu(this->menu);

        splitPushButton1 = new SplitPushButton(QString("Split push button"), this, nullptr);
        splitPushButton1->setFlyout(this->menu); 
        FluentIcon *splitPushButton1ButtonIcon = new FluentIcon();
        splitPushButton1ButtonIcon->setIconName("SEND_FILL");
        QVariant qvSplitPushButton1ButtonIcon = QVariant::fromValue<FluentIcon>(*splitPushButton1ButtonIcon);
        splitPushButton1->setDropIcon(&qvSplitPushButton1ButtonIcon);
        //splitPushButton1->setDropIconSize(new QSize(14,14));

        FluentIcon *splitPushButton2ButtonIcon = new FluentIcon();
        splitPushButton2ButtonIcon->setIconName("GITHUB");
        splitPushButton2 = new SplitPushButton(splitPushButton2ButtonIcon, QString("Split push button"), this);
        splitPushButton2->setFlyout(this->menu);

        primarySplitPushButton1 = new PrimarySplitPushButton(QString("Split push button"), this, nullptr);
        primarySplitPushButton1->setFlyout(this->menu);
        primarySplitPushButton1->setDropIcon(&qvSplitPushButton1ButtonIcon);
        //primarySplitPushButton1->setDropIconSize();
        primarySplitPushButton2 = new PrimarySplitPushButton(splitPushButton2ButtonIcon, QString("Split push button"), this);
        primarySplitPushButton2->setFlyout(this->menu);

        splitToolButton = new SplitToolButton(splitPushButton2ButtonIcon, this);
        splitToolButton->setFlyout(this->menu);


        gridLayout->addWidget(pushButton1, 0, 0);
        gridLayout->addWidget(pushButton2, 0, 1);
        gridLayout->addWidget(primaryButton1, 1, 0);
        gridLayout->addWidget(primaryButton2, 1, 1);
        gridLayout->addWidget(transparentPushButton1, 2, 0);
        gridLayout->addWidget(transparentPushButton2, 2, 1);
        
        gridLayout->addWidget(ToggleButton1, 3, 0);
        gridLayout->addWidget(ToggleButton2, 3, 1);
        gridLayout->addWidget(transparentTogglePushButton1, 4, 0);
        gridLayout->addWidget(transparentTogglePushButton2, 4, 1);
        gridLayout->addWidget(hyperlinkButton1, 5, 0);
        gridLayout->addWidget(hyperlinkButton2, 5, 1);
        gridLayout->addWidget(radioButton1, 6, 0);
        gridLayout->addWidget(radioButton2, 6, 1);
        gridLayout->addWidget(toolButton, 7, 0);
        gridLayout->addWidget(tranparentToolButton, 7, 1);
        gridLayout->addWidget(primaryToolButton, 7, 2);
        gridLayout->addWidget(toggleToolButton, 8, 0);
        gridLayout->addWidget(transparentToggleToolButton, 8, 1);

        
        gridLayout->addWidget(dropDownPushButton1, 9, 0);
        gridLayout->addWidget(dropDownPushButton2, 9, 1);

        gridLayout->addWidget(transparentDropDownPushButton1, 10, 0);
        gridLayout->addWidget(transparentDropDownPushButton2, 10, 1);

        gridLayout->addWidget(dropDownToolButton, 11, 0);
        gridLayout->addWidget(transparentDropDownToolButton, 11, 1);
        gridLayout->addWidget(primaryDropDownPushButton1, 11, 2);
        gridLayout->addWidget(primaryDropDownToolButton, 11, 3);


        gridLayout->addWidget(splitPushButton1, 12, 0);
        gridLayout->addWidget(splitPushButton2, 12, 1);

        gridLayout->addWidget(primarySplitPushButton1, 13, 0);
        gridLayout->addWidget(primarySplitPushButton2, 13, 1);

        gridLayout->addWidget(splitToolButton, 14, 0);
        //*/
        
        // primarySplitPushButton1 = new PrimarySplitPushButton(QString("Split push button"), this, nullptr);
        // primarySplitPushButton1->setFlyout(this->menu);
        // gridLayout->addWidget(primarySplitPushButton1, 0, 0);

        

        //gridLayout->addWidget(dropDownToolButton, 0, 1);


        setLayout(gridLayout);
        resize(600, 1000);
    }

public slots:
    void toggleToolButtonPrint()
    {
        qDebug() << "toogle tool button print...";
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
    //Window *demo = new Window(nullptr);
    //demo->show();
    //Window2 *demo2 = new Window2(nullptr);
    //demo2->show();
    return app->exec();
}