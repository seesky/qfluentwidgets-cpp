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