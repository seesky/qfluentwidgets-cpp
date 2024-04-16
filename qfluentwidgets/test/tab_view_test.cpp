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
#include <QtWidgets/QFrame>
#include "../components/navigation/navigation_widget.h"
#include "../components/navigation/navigation_panel.h"
#include "../components/navigation/navigation_bar.h"
#include "../components/navigation/navigation_interface.h"
#include "../components/dialog_box/dialog.h"
#include "../components/widgets/line_edit.h"
#include "../components/widgets/stacked_widget.h"
#include "../components/widgets/tab_view.h"
#include "../common/config.h"
#include "../common/style_sheet.h"
#include "../common/icon.h"
#include "../../qfluentwidgets/qframelesswindow/windows/qframe_less_window.h"
#include "../../qfluentwidgets/qframelesswindow/titlebar/titlebar.h"
#include "../window/fluent_window.h"


class Widget : public QFrame{
    Q_OBJECT
public:
    SubtitleLabel *label;
    QHBoxLayout *hBoxLayout;

    Widget(QString text, QWidget *parent){
        this->setObjectName(text.replace(" ", "-"));
        this->label = new SubtitleLabel(text, this);
        this->label->setAlignment(Qt::AlignCenter);
        this->hBoxLayout = new QHBoxLayout(this);
        this->hBoxLayout->addWidget(this->label, 1, Qt::AlignCenter);
        this->hBoxLayout->setContentsMargins(0, 32, 0, 0);
    }
};


class TabInterface : public QFrame{
    Q_OBJECT
public:
    IconWidget *iconWidget;
    SubtitleLabel *label;
    QVBoxLayout *vBoxLayout;
    TabInterface(QString text, QVariant *icon, QString objectName, QWidget *parent){
        this->iconWidget = new IconWidget(icon, this);
        this->label = new SubtitleLabel(text, this);
        this->iconWidget->setFixedSize(120, 120);

        this->vBoxLayout = new QVBoxLayout(this);
        this->vBoxLayout->setAlignment(Qt::AlignCenter);
        this->vBoxLayout->setSpacing(30);
        this->vBoxLayout->addWidget(this->iconWidget, 0, Qt::AlignCenter);
        this->vBoxLayout->addWidget(this->label, 0, Qt::AlignCenter);
        Font().setFont(this->label, 24, QFont::Normal);

        this->setObjectName(objectName);
    }

};


class CustomTitleBar : public MSFluentTitleBar{
    Q_OBJECT
public:
    QLabel *iconLabel;
    QLabel *titleLabel;
    SearchLineEdit *searchLineEdit;
    QVBoxLayout *vBoxLayout;
    QHBoxLayout *buttonLayout;


    QHBoxLayout *toolButtonLayout;
    TransparentToolButton *searchButton;
    TransparentToolButton *forwardButton;
    TransparentToolButton *backButton;
    TabBar *tabBar;
    TransparentDropDownToolButton *avatar;
    CustomTitleBar(QWidget *parent) : MSFluentTitleBar(parent){

        this->toolButtonLayout = new QHBoxLayout();
        QColor color = isDarkTheme() ? QColor(206, 206, 206) : QColor(96, 96, 96);

        
        FluentIcon *searchIcon = new FluentIcon();
        searchIcon->setIconName(QString("SEARCH_MIRROR"));
        QIcon *_searchIcon = searchIcon->icon(Theme::AUTO, color);
        this->searchButton = new TransparentToolButton(_searchIcon, this);

        FluentIcon *forwardIcon = new FluentIcon();
        forwardIcon->setIconName(QString("RIGHT_ARROW"));
        QIcon *_forwardIcon = forwardIcon->icon(Theme::AUTO, color);
        this->forwardButton = new TransparentToolButton(_forwardIcon, this);

        FluentIcon *backIcon = new FluentIcon();
        backIcon->setIconName(QString("LEFT_ARROW"));   
        QIcon *_backIcon = backIcon->icon(Theme::AUTO, color);
        this->backButton = new TransparentToolButton(_backIcon, this);
        
        this->forwardButton->setDisabled(true);
        this->toolButtonLayout->setContentsMargins(20, 0, 20, 0);
        this->toolButtonLayout->setSpacing(15);
        this->toolButtonLayout->addWidget(this->searchButton);
        this->toolButtonLayout->addWidget(this->backButton);
        this->toolButtonLayout->addWidget(this->forwardButton);
        this->hBoxLayout->insertLayout(4, this->toolButtonLayout);
        
        
        this->tabBar = new TabBar(this);

        this->tabBar->setMovable(true);
        this->tabBar->setTabMaximumWidth(220);
        this->tabBar->setTabShadowEnabled(false);
        this->tabBar->setTabSelectedBackgroundColor(QColor(255, 255, 255, 125), QColor(255, 255, 255, 50));
        
        connect(this->tabBar, &TabBar::tabCloseRequested, this, [this](int a){
            this->tabBar->removeTab(a);
        });

        connect(this->tabBar, &TabBar::currentChanged, this, [this](int i){
            this->tabBar->tabText(i);
        });

        this->hBoxLayout->insertWidget(5, this->tabBar, 1);
        this->hBoxLayout->setStretch(6, 0);
        
        this->avatar = new TransparentDropDownToolButton(QString("qfluentwidgets/iamges/shoko.png"), this);
        this->avatar->setIconSize(QSize(26, 26));
        this->avatar->setFixedHeight(30);
        this->hBoxLayout->insertWidget(7, this->avatar, 0, Qt::AlignRight);
        this->hBoxLayout->insertSpacing(8, 20);
        
    }

    bool canDrag(QPoint *pos) override{
        if(!TitleBar::canDrag(pos)){
            return false;
        }

        pos->setX(pos->x() - this->tabBar->x());
        return !this->tabBar->tabRegion().contains(*pos);
    }

};




class Window : public MSFluentWindow{
    Q_OBJECT
public:
    QHBoxLayout *hBoxLayout;
    NavigationBar *navigationBar;


    QStackedWidget *homeInterface;
    Widget *appInterface;
    Widget *videoInterface;
    Widget *libraryInterface;
    TabBar *tabBar;

    Window(QWidget *parent) : MSFluentWindow(parent){
        
        
        this->setTitleBar(new CustomTitleBar(this));
        
        this->tabBar = ((CustomTitleBar *)(this->titleBar))->tabBar;

        //this->hBoxLayout = new QHBoxLayout(this);
        //this->navigationBar = new NavigationBar(this);
        //this->stackWidget = new MStackedWidget(this);

        this->homeInterface = new QStackedWidget(this);
        this->homeInterface->setObjectName(QString("homeInterface"));
        this->appInterface = new Widget(QString("Application Interface"), this);
        this->videoInterface = new Widget(QString("Video Interface"), this);
        this->libraryInterface = new Widget(QString("library Interface"), this);

        //this->initLayout();

        this->initNavigation();

        this->initWindow();
        
    }

    /*
    void initLayout(){
        this->hBoxLayout->setSpacing(0);
        this->hBoxLayout->setContentsMargins(0, 48, 0, 0);
        this->hBoxLayout->addWidget(this->navigationBar);
        this->hBoxLayout->addWidget(this->stackWidget);
        this->hBoxLayout->setStretchFactor(this->stackWidget, 1);
    }
    */

    void initNavigation(){

        
        FluentIcon *honmeIcon = new FluentIcon();
        honmeIcon->setIconName(QString("HOME"));
        FluentIcon *honmeFillIcon = new FluentIcon();
        honmeFillIcon->setIconName(QString("HOME_FILL"));
        this->addSubInterface(this->homeInterface, new QVariant(QVariant::fromValue<FluentIcon>(*honmeIcon)), QString("主页"), new QVariant(QVariant::fromValue<FluentIcon>(*honmeFillIcon)), NavigationItemPosition::TOP, false);
        
        
        FluentIcon *applicatonIcon = new FluentIcon();
        applicatonIcon->setIconName(QString("APPLICATION"));
        this->addSubInterface(this->appInterface, new QVariant(QVariant::fromValue<FluentIcon>(*applicatonIcon)), QString("应用"),  new QVariant(), NavigationItemPosition::TOP, false);
        
        FluentIcon *videoIcon = new FluentIcon();
        videoIcon->setIconName(QString("VIDEO"));
        this->addSubInterface(this->videoInterface, new QVariant(QVariant::fromValue<FluentIcon>(*videoIcon)), QString("视频"),  new QVariant(), NavigationItemPosition::TOP, false);

        
        FluentIcon *bookShelfIcon = new FluentIcon();
        bookShelfIcon->setIconName(QString("BOOK_SHELF"));
        FluentIcon *libraryFillIcon = new FluentIcon();
        libraryFillIcon->setIconName(QString("HOME_FILL"));
        this->addSubInterface(this->libraryInterface, new QVariant(QVariant::fromValue<FluentIcon>(*bookShelfIcon)), QString("库"), new QVariant(QVariant::fromValue<FluentIcon>(*libraryFillIcon)), NavigationItemPosition::BOTTOM, false);

        
        
        FluentIcon *helpIcon = new FluentIcon();
        helpIcon->setIconName(QString("HELP"));
        this->navigationInterface->addItem(QString("Help"), new QVariant(QVariant::fromValue<FluentIcon>(*helpIcon)), QString("帮助"), [this](){
            this->showMessageBox();
        }, false, new QVariant(), NavigationItemPosition::BOTTOM);
        
        
        this->navigationInterface->setCurrentItem(this->homeInterface->objectName());


        this->addTab(QString("Heart"), QString("As long as you love me"), new QVariant(QVariant::fromValue<QString>("qfluentwidgets/images/Heart.png")));
        connect(this->tabBar, &TabBar::currentChanged, this, &Window::onTabChanged);
        connect(this->tabBar, &TabBar::tabAddRequested, this, &Window::onTabAddRequested);        

        

    }

    void initWindow(){
        this->resize(1100, 750);
        this->setWindowIcon(QIcon("qfluentwidgets/images/logo.png"));
        this->setWindowTitle(QString("Qt Widgets"));
        this->titleBar->setAttribute(Qt::WA_StyledBackground);

        QRect desktop = QApplication::desktop()->availableGeometry();
        int w = desktop.width();
        int h = desktop.height();
        this->move(w / 2 - this->width() / 2, h / 2 - this->height() / 2);

    }



    void showMessageBox()
    {
        MessageBoxF *w = new MessageBoxF(QString("This is a help message"), QString("You clicked a customized navigation widget. You can add more custom widgets by calling `NavigationInterface.addWidget()` 😉"), this);
        w->yesButton->setText("ok");
        w->cancelButton->setText("cancel");
        w->exec();
    }

    void addTab(QString routeKey, QString text, QVariant *icon)
    {
        this->tabBar->addTab(routeKey, text, icon, nullptr);
        this->homeInterface->addWidget(new TabInterface(text, icon, routeKey, this));
    }



public slots:

    void onTabChanged(int index){
        QString objectName = this->tabBar->currentTab()->routeKey();
        this->homeInterface->setCurrentWidget(this->findChild<TabInterface*>(objectName));
        this->stackedWidget->setCurrentWidget(this->homeInterface, false);
    }

    void onTabAddRequested()
    {
        QString text = QString("硝子酱一级棒卡哇伊×%1").arg(this->tabBar->count());
        this->addTab(text, text, new QVariant(QVariant::fromValue<QString>(QString("qfluentwidgets/images/Smiling_with_heart.png"))));
    }

};



int main(int argc, char *argv[])
{
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    
    QApplication *app = new QApplication(argc, argv);
    Window *w = new Window(nullptr);
    w->show();
    return app->exec();
}


#include "tab_view_test.moc"