#include <iostream>
#include <QtCore>
#include <QtWidgets>
#include <QtCore/Qt>
#include "../common/icon.h"
#include "../common/style_sheet.h"
#include "../common/config.h"
#include "../../qfluentwidgets/components/widgets/button.h"
#include "../../qfluentwidgets/components/widgets/menu.h"
#include "../../qfluentwidgets/components/widgets/flyout.h"
#include "../../qfluentwidgets/components/widgets/label.h"
#include "../../qfluentwidgets/components/widgets/command_bar.h"
#include "../../qfluentwidgets/qframelesswindow/windows/qframe_less_window.h"
#include "../../qfluentwidgets/qframelesswindow/titlebar/titlebar.h"
#include "../../qfluentwidgets/components/dialog_box/dialog.h"


class SystemTrayIcon : public QSystemTrayIcon{
public:

   SystemTrayMenu *menu;
    SystemTrayIcon(QWidget *parent) : QSystemTrayIcon(parent){
        this->setIcon(parent->windowIcon());
        this->setToolTip(QString("硝子酱一级棒卡哇伊🥰"));

        this->menu = new SystemTrayMenu(QString(""), parent);
        QList<QAction*> *actions = new QList<QAction*>();
        actions->append(new Action(QString("🎤   唱"), this));
        actions->append(new Action(QString("🕺   跳"), this));
        actions->append(new Action(QString("🤘🏼   RAP"), this));
        actions->append(new Action(QString("🎶   Music"), this));
        Action *a = new Action(QString("🏀   篮球"), this);
        connect(a, &Action::triggered, this, &SystemTrayIcon::ikun);
        actions->append(a);
        this->menu->addActions(actions);

        this->setContextMenu(this->menu);

    }

public slots:
    void ikun()
    {
        QString content = R"(巅峰产生虚伪的拥护，黄昏见证真正的使徒 🏀

                         ⠀⠰⢷⢿⠄
                   ⠀⠀⠀⠀⠀⣼⣷⣄
                   ⠀⠀⣤⣿⣇⣿⣿⣧⣿⡄
                   ⢴⠾⠋⠀⠀⠻⣿⣷⣿⣿⡀
                   ⠀⢀⣿⣿⡿⢿⠈⣿
                   ⠀⠀⠀⢠⣿⡿⠁⠀⡊⠀⠙
                   ⠀⠀⠀⢿⣿⠀⠀⠹⣿
                   ⠀⠀⠀⠀⠹⣷⡀⠀⣿⡄
                   ⠀⠀⠀⠀⣀⣼⣿⠀⢈⣧)";
        
        MessageBoxF *w = new MessageBoxF(QString("坤家军！集合！"), content, (QWidget *)(this->parent()));
        w->yesButton->setText(QString("献出心脏"));
        w->cancelButton->setText(QString("你干嘛~"));
        w->exec();
    }
};


class Demo : public QWidget{
public:

    QLabel *label;
    SystemTrayIcon *systemTrayIcon;
    Demo(QWidget *parent) : QWidget(parent){
        this->setLayout(new QHBoxLayout());
        this->label = new QLabel(QString("Right-click system tray icon"), this);
        this->label->setAlignment(Qt::AlignCenter);
        this->layout()->addWidget(this->label);

        this->resize(500, 500);
        this->setStyleSheet(QString("Demo{background: white} QLabel{font-size: 20px}"));
        this->setWindowIcon(QIcon("qfluentwidgets/images/logo.png"));

        this->systemTrayIcon = new SystemTrayIcon(this);
        this->systemTrayIcon->show();
    }

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