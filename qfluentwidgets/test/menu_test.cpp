#include <QtCore/Qt>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QAction>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>

#include "../components/widgets/menu.h"
#include "../common/style_sheet.h"
#include "../common/config.h"
#include "../common/icon.h"



class Demo : public QWidget{
public:

    QLabel *label;

    Demo() : QWidget(){
        this->setLayout(new QHBoxLayout());
        this->label = new QLabel("Right-click your mouse", this);
        this->label->setAlignment(Qt::AlignCenter);
        this->layout()->addWidget(this->label);
        this->resize(400, 400);

        this->setStyleSheet(QString("Demo{background: white} QLabel{font-size: 20px}"));
    }

    void contextMenuEvent(QContextMenuEvent *event)
    {
        RoundMenu *menu = new RoundMenu(QString(""), this);

        
        FluentIcon *copyIcon = new FluentIcon();
        copyIcon->setIconName("COPY");
        Action *copyAction = new Action(copyIcon, QString("Copy"), nullptr);
        menu->addAction(copyAction);

        FluentIcon *cutIcon = new FluentIcon();
        cutIcon->setIconName("CUT");
        Action *cutAction = new Action(cutIcon, QString("Cut"), nullptr);
        menu->addAction(cutAction);

        menu->actions().at(0)->setCheckable(true);
        menu->actions().at(0)->setChecked(true);

        

        RoundMenu *submenu = new RoundMenu(QString("Add to"), this);
        FluentIcon *addIcon = new FluentIcon();
        addIcon->setIconName("ADD");
        submenu->setIcon(new QVariant(QVariant::fromValue<FluentIcon>(*addIcon)));

        
        ///////////////////////////////////

        
        QList<QAction *> *actions = new QList<QAction *>();

        FluentIcon *videoIcon = new FluentIcon();
        videoIcon->setIconName("VIDEO");
        Action *videoAction = new Action(videoIcon, QString("Video"), nullptr);
        actions->append(videoAction);

        
        FluentIcon *musicIcon = new FluentIcon();
        musicIcon->setIconName("MUSIC");
        Action *musicAction = new Action(musicIcon, QString("MUSIC"), nullptr);
        actions->append(musicAction);
        
        submenu->addActions(actions);
        
        
        menu->addMenu(submenu);
        


        
        QList<QAction *> *actions2 = new QList<QAction *>();

        
        FluentIcon *pasteIcon = new FluentIcon();
        pasteIcon->setIconName("PASTE");
        Action *pasteAction = new Action(pasteIcon, QString("Paste"), nullptr);
        actions2->append(pasteAction);

        
        FluentIcon *undoIcon = new FluentIcon();
        undoIcon->setIconName("CANCEL");
        Action *undoAction = new Action(undoIcon, QString("Undo"), nullptr);
        actions2->append(undoAction);

        menu->addActions(actions2);

        menu->addSeparator();
        
        
        Action *selectAllAction = new Action(QString("Select All"), this);
        selectAllAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_A));
        menu->addAction(selectAllAction);

        FluentIcon *settingsIcon = new FluentIcon();
        settingsIcon->setIconName("SETTING");
        Action *settingsAction = new Action(settingsIcon, QString("Settings"), nullptr);
        menu->insertAction(menu->actions().takeLast(), settingsAction);


        
        QList<QAction *> *actions3 = new QList<QAction *>();

        
        FluentIcon *helpIcon = new FluentIcon();
        helpIcon->setIconName("HELP");
        Action *helpAction = new Action(helpIcon, QString("Help"), nullptr);
        helpAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_H));
        actions3->append(helpAction);

        
        FluentIcon *feedbackIcon = new FluentIcon();
        feedbackIcon->setIconName("FEEDBACK");
        Action *feedbackAction = new Action(feedbackIcon, QString("Feedback"), nullptr);
        feedbackAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F));
        actions3->append(feedbackAction);

        menu->insertActions(menu->actions().takeLast(), actions3);

        
        menu->actions().at(menu->actions().size() - 2)->setCheckable(true);
        menu->actions().at(menu->actions().size() - 2)->setChecked(true);

        
        QPoint p = event->globalPos();
        menu->exec(&p, true, MenuAnimationType::DROP_DOWN);
    }
};


class Demo1 : public QWidget{
public:

    QLabel *label;

    Demo1() : QWidget(){
        this->setLayout(new QHBoxLayout());
        this->label = new QLabel("Right-click your mouse", this);
        this->label->setAlignment(Qt::AlignCenter);
        this->layout()->addWidget(this->label);
        this->resize(400, 400);

        this->setStyleSheet(QString("Demo{background: white} QLabel{font-size: 20px}"));
    }

    void contextMenuEvent(QContextMenuEvent *event)
    {
        CheckableMenu *menu = new CheckableMenu("", this, MenuIndicatorType::RADIO);


        FluentIcon *calendarIcon = new FluentIcon();
        calendarIcon->setIconName(QString("CALENDAR"));
        FluentIcon *cameraIcon = new FluentIcon();
        cameraIcon->setIconName(QString("CAMERA"));
        FluentIcon *editIcon = new FluentIcon();
        editIcon->setIconName(QString("EDIT"));
        FluentIcon *fontIcon = new FluentIcon();
        fontIcon->setIconName(QString("FONT"));
        FluentIcon *upIcon = new FluentIcon();
        upIcon->setIconName(QString("UP"));
        FluentIcon *downIcon = new FluentIcon();
        downIcon->setIconName(QString("DOWN"));


        Action *createTimeAction;
        Action *shootTimeAction;
        Action *modifiedTimeAction;
        Action *nameAction;
        QActionGroup *actionGroup1;

        createTimeAction = new Action(calendarIcon, this->tr("Create Date"), nullptr);
        createTimeAction->setCheckable(true);
        createTimeAction->setChecked(true);
        shootTimeAction = new Action(cameraIcon, this->tr("Shooting Date"), nullptr);
        shootTimeAction->setCheckable(true);
        modifiedTimeAction = new Action(editIcon, this->tr("Modified time"), nullptr);
        modifiedTimeAction->setCheckable(true);
        nameAction = new Action(fontIcon, this->tr("Name"), nullptr);
        nameAction->setCheckable(true);
        actionGroup1 = new QActionGroup(this);
        actionGroup1->addAction(createTimeAction);
        actionGroup1->addAction(shootTimeAction);
        actionGroup1->addAction(modifiedTimeAction);
        actionGroup1->addAction(nameAction);

        shootTimeAction->setChecked(true);
        

        menu->addAction(createTimeAction);
        menu->addAction(shootTimeAction);
        menu->addAction(modifiedTimeAction);
        menu->addAction(nameAction);

        menu->addSeparator();


        Action *ascendAction;
        Action *descendAction;
        QActionGroup *actionGroup2;

        ascendAction = new Action(upIcon, this->tr("Ascending"), nullptr);
        ascendAction->setCheckable(true);
        descendAction = new Action(downIcon, this->tr("Descending"), nullptr);
        descendAction->setCheckable(true);
        actionGroup2 = new QActionGroup(this);
        actionGroup2->addAction(ascendAction);
        actionGroup2->addAction(descendAction);

        ascendAction->setChecked(true);

         menu->addAction(ascendAction);
        menu->addAction(descendAction);

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
    Demo *w = new Demo();
    w->show(); 
    Demo1 *w1 = new Demo1();
    w1->show();
    return app->exec();
}