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


class CommandBarsView1 : public QWidget{
public:

    QHBoxLayout *hBoxLayout;
    CommandBar *commandBar;
    TransparentDropDownPushButton *dropDownButton;
    CommandBarsView1() : QWidget(){
        this->hBoxLayout = new QHBoxLayout(this);
        this->commandBar = new CommandBar(this);
        //this->dropDownButton = this->createDropDownButton();

        this->hBoxLayout->addWidget(this->commandBar, 0);

        this->commandBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        
        /*
        FluentIcon *addIcon = new FluentIcon();
        addIcon->setIconName("ADD");
        this->addButton(addIcon, QString("Add"));
        this->commandBar->addSeparator();
        
        
        */
        FluentIcon *editIcon = new FluentIcon();
        editIcon->setIconName("EDIT");
        Action *editAction = new Action(editIcon, QString("Edit"), nullptr);
        connect(editAction, &Action::triggered, this, &CommandBarsView1::onEdit);
        editAction->setCheckable(true);
        this->commandBar->addAction(editAction);
        
        /*
        FluentIcon *copyIcon = new FluentIcon();
        copyIcon->setIconName("COPY");
        this->addButton(copyIcon, QString("Copy"));
        FluentIcon *shareIcon = new FluentIcon();
        shareIcon->setIconName("SHARE");
        this->addButton(shareIcon, QString("Share"));
        
        
        
        this->commandBar->addWidget(this->dropDownButton);
        
        
        
        FluentIcon *sortIcon = new FluentIcon();
        sortIcon->setIconName("SCROLL");
        Action *sortAction = new Action(sortIcon, QString("Sort"), nullptr);
        connect(sortAction, &Action::triggered, this, [this](){
            qDebug() << QString("排序");
        });
        this->commandBar->addHiddenAction(sortAction);

        
        FluentIcon *settingsIcon = new FluentIcon();
        settingsIcon->setIconName("SETTING");
        Action *settingsAction = new Action(settingsIcon, QString("Settings"), nullptr);
        settingsAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
        this->commandBar->addHiddenAction(settingsAction);
        */
        
        this->resize(240, 40);
        this->setWindowTitle(QString("Drag window"));
    }

    void addButton(FluentIcon *icon, QString text)
    {
        Action *action = new Action(icon, text, this);
        connect(action, &Action::triggered, this, [this, text](){
            qDebug() << text;
        });
        this->commandBar->addAction(action);
    }

    TransparentDropDownPushButton *createDropDownButton()
    {
        FluentIcon *menuIcon = new FluentIcon();
        menuIcon->setIconName("MENU");
        TransparentDropDownPushButton *button = new TransparentDropDownPushButton(menuIcon, QString("Menu"), this);
        button->setFixedHeight(34);
        Font().setFont(this, 12, QFont::Normal);

        RoundMenu *menu = new RoundMenu(QString(""), this);
        QList<QAction *> *actions = new QList<QAction *>();

        
        FluentIcon *copyIcon = new FluentIcon();
        copyIcon->setIconName("COPY");
        Action *copyAction = new Action(copyIcon, QString("Copy"), nullptr);
        actions->append(copyAction);

        
        
        
        FluentIcon *cutIcon = new FluentIcon();
        cutIcon->setIconName("CUT");
        Action *cutAction = new Action(cutIcon, QString("Cut"), nullptr);
        actions->append(cutAction);

        FluentIcon *pasteIcon = new FluentIcon();
        pasteIcon->setIconName("PASTE");
        Action *pasteAction = new Action(pasteIcon, QString("Paste"), nullptr);
        actions->append(pasteAction);

        
        FluentIcon *cancelIcon = new FluentIcon();
        cancelIcon->setIconName("CANCEL");
        Action *cancelAction = new Action(cancelIcon, QString("Cancel"), nullptr);
        actions->append(cancelAction);
        

        Action *allAction = new Action(QString("Select all"), nullptr);
        actions->append(allAction);

        menu->addActions(actions);

        button->setMenu(menu);
        return button;
    }

public slots:
    void onEdit(bool isChecked)
    {
        if(isChecked){
            qDebug() << QString("Enter edit mode");
        }else{
            qDebug() << QString("Exit edit mode");
        }
    }
};



int main(int argc, char *argv[])
{
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    
    QApplication *app = new QApplication(argc, argv);
    CommandBarsView1 *w = new CommandBarsView1();
    w->show();
    return app->exec();
}