#include <QtCore/Qt>
#include <QtCore/QEvent>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include "../components/navigation/navigation_widget.h"
#include "../components/navigation/navigation_panel.h"
#include "../components/dialog_box/dialog.h"
#include "../common/config.h"
#include "../common/style_sheet.h"
#include "../common/icon.h"
#include "../../qfluentwidgets/qframelesswindow/windows/qframe_less_window.h"
#include "../../qfluentwidgets/qframelesswindow/titlebar/titlebar.h"


class Widget : public QWidget{
public:

    QLabel *label;
    QHBoxLayout *hBoxLayout;

    Widget(QString text, QWidget *parent) : QWidget(parent)
    {
        this->label = new QLabel(text, this);
        this->hBoxLayout = new QHBoxLayout(this);

        this->label->setAlignment(Qt::AlignCenter);
        this->hBoxLayout->addWidget(this->label, 1, Qt::AlignCenter);

        this->setObjectName(text.replace(" ", "-"));
    }

};


class NavigationBar2 : public QWidget{
public:

    QHBoxLayout *hBoxLayout;
    NavigationToolButton *menuButton;
    NavigationPanel *navigationPanel;
    QLabel *titleLabel;

    NavigationBar2(QWidget *parent) : QWidget(parent)
    {
        this->hBoxLayout = new QHBoxLayout(this);
        FluentIcon *menuIcon = new FluentIcon();
        menuIcon->setIconName(QString("MENU"));
        this->menuButton = new NavigationToolButton(new QVariant(QVariant::fromValue<FluentIcon>(*menuIcon)), this);
        this->navigationPanel = new NavigationPanel(parent, true);
        this->titleLabel = new QLabel(this);

        this->navigationPanel->move(0, 31);
        this->hBoxLayout->setContentsMargins(5, 5, 5, 5);
        this->hBoxLayout->addWidget(this->menuButton);
        this->hBoxLayout->addWidget(this->titleLabel);

        connect(this->menuButton, &NavigationToolButton::clicked, this, &NavigationBar2::showNavigationPanel);
        this->navigationPanel->setExpandWidth(260);
        this->navigationPanel->setMenuButtonVisible(true);
        this->navigationPanel->hide();

        this->navigationPanel->setAcrylicEnabled(false);
        this->window()->installEventFilter(this);
    }

    void setTitle(QString title)
    {
        this->titleLabel->setText(title);
        this->titleLabel->adjustSize();
    }

  
    void addItem(QString routeKey, QVariant *icon, QString text, std::function<void()> onClick, bool selectable, NavigationItemPosition position)
    {
        this->navigationPanel->addItem(routeKey, icon, text, [onClick, this, text](){
            onClick();
            this->setTitle(text);
        }, selectable, position, QString(), QString());
    }

    void addSeparator(NavigationItemPosition position = NavigationItemPosition::TOP)
    {
        this->navigationPanel->addSeparator(position);
    }


    void setCurrentItem(QString routeKey)
    {
        this->navigationPanel->setCurrentItem(routeKey);
        this->setTitle(((NavigationTreeWidget *)this->navigationPanel->widget(routeKey))->text());
    }
    
    
    bool eventFilter(QObject *watched, QEvent *event) override
    {
        if(watched == this->window()){
            if(event->type() == QEvent::Resize){
                QResizeEvent *re = dynamic_cast<QResizeEvent*>(event);
                this->navigationPanel->setFixedHeight(re->size().height() - 31);
            }
        }

        return QWidget::eventFilter(watched, event);
    }

public slots:
    void showNavigationPanel()
    {
        this->navigationPanel->show();
        this->navigationPanel->raise();
        this->navigationPanel->expand(true);
    }
};



class Window : public WindowsFramelessWindow{
public:

    QVBoxLayout *vBoxLayout;
    NavigationBar2 *navigationInterface;
    QStackedWidget *stackWidget;
    Widget *searchInterface;
    Widget *musicInterface;
    Widget *videoInterface;
    Widget *folderInterface;
    Widget *settingInterface;

    Window() : WindowsFramelessWindow(nullptr){
        this->setTitleBar(new StandardTitleBar(this));

        this->vBoxLayout = new QVBoxLayout(this);
        this->navigationInterface = new NavigationBar2(this);
        this->stackWidget = new QStackedWidget(this);

        this->searchInterface = new Widget(QString("Search Interface"), this);
        this->musicInterface = new Widget(QString("Music Interface"), this);
        this->videoInterface = new Widget(QString("Video Interface"), this);
        this->folderInterface = new Widget(QString("Folder Interface"), this);
        this->settingInterface = new Widget(QString("Setting Interface"), this);

        this->stackWidget->addWidget(this->searchInterface);
        this->stackWidget->addWidget(this->musicInterface);
        this->stackWidget->addWidget(this->videoInterface);
        this->stackWidget->addWidget(this->folderInterface);
        this->stackWidget->addWidget(this->settingInterface);

        this->initLayout();
        this->initNavigation();
        this->initWindow();
        
    }

    void initLayout()
    {
        this->vBoxLayout->setSpacing(0);
        this->vBoxLayout->setContentsMargins(0, this->titleBar->height(), 0, 0);
        this->vBoxLayout->addWidget(this->navigationInterface);
        this->vBoxLayout->addWidget(this->stackWidget);
        this->vBoxLayout->setStretchFactor(this->stackWidget, 1);
    }


    void initNavigation()
    {
        FluentIcon *searchIcon = new FluentIcon();
        searchIcon->setIconName(QString("SEARCH"));
        this->addSubInterface(this->searchInterface, new QVariant(QVariant::fromValue<FluentIcon>(*searchIcon)), QString("Search"), NavigationItemPosition::TOP);

        FluentIcon *musicIcon = new FluentIcon();
        musicIcon->setIconName(QString("MUSIC"));
        this->addSubInterface(this->musicInterface, new QVariant(QVariant::fromValue<FluentIcon>(*musicIcon)), QString("Music library"), NavigationItemPosition::TOP);

        FluentIcon *videoIcon = new FluentIcon();
        videoIcon->setIconName(QString("VIDEO"));
        this->addSubInterface(this->videoInterface, new QVariant(QVariant::fromValue<FluentIcon>(*videoIcon)), QString("Video library"), NavigationItemPosition::TOP);

        this->navigationInterface->addSeparator(NavigationItemPosition::TOP);

        FluentIcon *folderIcon = new FluentIcon();
        folderIcon->setIconName(QString("FOLDER"));
        this->addSubInterface(this->folderInterface, new QVariant(QVariant::fromValue<FluentIcon>(*folderIcon)), QString("Folder library"), NavigationItemPosition::SCROLL);

        FluentIcon *settingIcon = new FluentIcon();
        settingIcon->setIconName(QString("SETTING"));
        this->addSubInterface(this->settingInterface, new QVariant(QVariant::fromValue<FluentIcon>(*settingIcon)), QString("Settings"), NavigationItemPosition::BOTTOM);

        connect(this->stackWidget, &QStackedWidget::currentChanged, this, &Window::onCurrentInterfaceChanged);
        this->stackWidget->setCurrentIndex(1);

    }


    void addSubInterface(QWidget *w, QVariant *icon, QString text, NavigationItemPosition position = NavigationItemPosition::TOP)
    {
        this->stackWidget->addWidget(w);
        this->navigationInterface->addItem(w->objectName(), icon, text, [this, w](){
            this->switchTo(w);
        }, true, position);
    }


    void initWindow()
    {
        this->resize(500, 600);
        this->setWindowIcon(QIcon("resource/logo.png"));
        this->setWindowTitle(QString("Fluentt Widgets"));
        this->titleBar->setAttribute(Qt::WA_StyledBackground);

        QDesktopWidget *desktopWidget = QApplication::desktop();
        int w = desktopWidget->width();
        int h = desktopWidget->height();
        this->move(w / 2 - this->width() / 2, h / 2 - this->height() / 2);

        this->setQss();
    }


    void setQss()
    {
        QString color = isDarkTheme() ? QString("dark") : QString("light");
        qDebug() << color;
        QFile file(QString("resource/%1/demo.qss").arg(color));
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream stream(&file);
            QString styleSheet = stream.readAll();
            this->setStyleSheet(styleSheet);
            this->searchInterface->setStyleSheet(styleSheet);
            file.close();
        } else {
            qWarning("Cannot open file: %s", qPrintable(file.errorString()));
        }



        
    }


    void switchTo(QWidget *widget)
    {
        this->stackWidget->setCurrentWidget(widget);
    }


    void showMessageBox()
    {
        MessageBoxF *w = new MessageBoxF(QString("This is a help message"), QString("You clicked a customized navigation widget. You can add more custom widgets by calling `NavigationInterface.addWidget()` 😉"), this);
        w->exec();
    }

public slots:
    void onCurrentInterfaceChanged(int index)
    {
        QWidget *widget = this->stackWidget->widget(index);
        this->navigationInterface->setCurrentItem(widget->objectName());
    }

};



int main(int argc, char *argv[])
{
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    
    QApplication *app = new QApplication(argc, argv);
    Window *w = new Window();
    w->show();
    return app->exec();
}