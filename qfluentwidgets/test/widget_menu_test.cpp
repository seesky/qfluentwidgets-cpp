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


class ProfileCard : public QWidget{
public:
    AvatarWidget *avatar;
    BodyLabel *nameLabel;
    CaptionLabel *emailLabel;
    HyperlinkButton *logoutButton;

    ProfileCard(QString avatarPath, QString name, QString email, QWidget *parent) : QWidget(parent){
        this->avatar = new AvatarWidget(avatarPath, this);
        this->nameLabel = new BodyLabel(name, this);
        this->emailLabel = new CaptionLabel(email, this);
        QVariant url = QVariant::fromValue<QString>(QString("http://www.usable-programming.com"));
        this->logoutButton = new HyperlinkButton(&url, QString("注销"), this, nullptr);

        QColor color = isDarkTheme() ? QColor(206, 206, 206) : QColor(96, 96, 96);
        this->emailLabel->setStyleSheet(QString("QLabel{color: '%1").arg(color.name()));
        Font().setFont(this->logoutButton, 13, QFont::Normal);

        this->setFixedSize(307, 82);
        this->avatar->setRadius(24);
        this->avatar->move(2, 6);
        this->nameLabel->move(64, 13);
        this->emailLabel->move(64, 32);
        this->logoutButton->move(52, 48);
    }
};


class Demo : public QWidget{
public:

    BodyLabel *label;

    Demo(QWidget *parent) : QWidget(parent){
       this->setStyleSheet(QString("Demo{background: white}"));
       this->setLayout(new QHBoxLayout());

        this->label = new BodyLabel(QString("Right-click your mouse"), this);
        this->label->setAlignment(Qt::AlignCenter);
        Font().setFont(this->label, 18, QFont::Normal);

        this->layout()->addWidget(this->label);
        this->resize(400, 400);
    }

    void contextMenuEvent(QContextMenuEvent *event) override{

        RoundMenu *menu = new RoundMenu(QString(""), this);

        ProfileCard *card = new ProfileCard(QString("resource/shoko.png"), QString("硝子酱"), QString("baxuelong@163.com"), menu);
        menu->addWidget(card, false, nullptr);

        menu->addSeparator();
        QList<QAction*> *actions = new QList<QAction*>();

        FluentIcon *peopleIcon = new FluentIcon();
        peopleIcon->setIconName("PEOPLE");
        Action *peopleAction = new Action(peopleIcon, QString("管理账户和设置"), nullptr);
        actions->append(peopleAction);

        FluentIcon *shoppingCardIcon = new FluentIcon();
        shoppingCardIcon->setIconName("SHOPPING_CART");
        Action *shoppingCardAction = new Action(shoppingCardIcon, QString("支付方式"), nullptr);
        actions->append(shoppingCardAction);

        FluentIcon *codeIcon = new FluentIcon();
        codeIcon->setIconName("CODE");
        Action *codeAction = new Action(codeIcon, QString("兑换代码和礼品卡"), nullptr);
        actions->append(codeAction);

        menu->addActions(actions);

        menu->addSeparator();

        FluentIcon *settingIcon = new FluentIcon();
        settingIcon->setIconName("SETTING");
        Action *settingAction = new Action(settingIcon, QString("设置"), nullptr);
        actions->append(settingAction);

        menu->addAction(settingAction);
        QPoint p = event->globalPos();
        menu->exec(&p, true, MenuAnimationType::DROP_DOWN);

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