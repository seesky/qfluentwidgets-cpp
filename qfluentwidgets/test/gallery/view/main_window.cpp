#include "main_window.h"

MainWindow::MainWindow(QWidget *parent) : FluentWindow(parent)
{
    this->initWindow();

    //create sub interface
    this->basicInputInterface = new BasicInputInterface(this);
    this->dateTimeInterface = new DateTimeInterface(this);
    this->dialogInterface = new DialogInterface(this);
    this->layoutInterface = new LayoutInterface(this);
    this->materialInterface = new MaterialInterface(this);
    this->menuInterface = new MenuInterface(this);

    this->navigationInterface->setAcrylicEnabled(true);

    this->connectSignalToSlot();

    this->initNavigation();
    this->splashScreen->finish();
}


void MainWindow::connectSignalToSlot()
{
    connect(signalBus, &SignalBus::micaEnableChanged, this, &MainWindow::setMicaEffectEnabled);
    connect(signalBus, &SignalBus::switchToSampleCard, this, &MainWindow::switchToSample);
    connect(signalBus, &SignalBus::supportSignal, this, &MainWindow::onSupport);
}


void MainWindow::initNavigation()
{
    Translator *t = new Translator(nullptr);
    
    
    //add sub interface
    NavigationItemPosition pos = NavigationItemPosition::SCROLL;
    
    FluentIcon *basicInputInterfaceIcon = new FluentIcon();
    basicInputInterfaceIcon->setIconName(QString("CHECKBOX"));
    this->addSubInterface(
        this->basicInputInterface,
        new QVariant(QVariant::fromValue<FluentIcon>(*basicInputInterfaceIcon)),
        t->basicInput,
        pos, nullptr, false);
    
    FluentIcon *dateTimeInterfaceIcon = new FluentIcon();
    dateTimeInterfaceIcon->setIconName(QString("DATE_TIME"));
    this->addSubInterface(
        this->dateTimeInterface,
        new QVariant(QVariant::fromValue<FluentIcon>(*dateTimeInterfaceIcon)),
        t->dateTime,
        pos, nullptr, false);
    
    FluentIcon *dialogInterfaceIcon = new FluentIcon();
    dialogInterfaceIcon->setIconName(QString("MESSAGE"));
    this->addSubInterface(
        this->dialogInterface,
        new QVariant(QVariant::fromValue<FluentIcon>(*dialogInterfaceIcon)),
        t->dialogs,
        pos, nullptr, false);
    
    FluentIcon *layoutInterfaceIcon = new FluentIcon();
    layoutInterfaceIcon->setIconName(QString("LAYOUT"));
    this->addSubInterface(
        this->layoutInterface,
        new QVariant(QVariant::fromValue<FluentIcon>(*layoutInterfaceIcon)),
        t->layout,
        pos, nullptr, false);
    

    FluentIcon *materialInterfaceIcon = new FluentIcon();
    materialInterfaceIcon->setIconName(QString("PALETTE"));
    this->addSubInterface(
        this->materialInterface,
        new QVariant(QVariant::fromValue<FluentIcon>(*materialInterfaceIcon)),
        t->menus,
        pos, nullptr, false);

    
    FluentIcon *menuInterfaceIcon = new FluentIcon();
    menuInterfaceIcon->setIconName(QString("MENU"));
    this->addSubInterface(
        this->menuInterface,
        new QVariant(QVariant::fromValue<FluentIcon>(*menuInterfaceIcon)),
        t->material,
        pos, nullptr, false);

}




void MainWindow::initWindow()
{
    this->resize(960, 780);
    this->setMinimumWidth(760);
    this->setWindowIcon(QIcon("resource/gallery_resource/images/logo.png"));
    this->setWindowTitle("Fluent Widgets");

    if(qconfig->get(QVariant::fromValue<OptionsConfigItem*>(galleryConfig->micaEnabled)).value<QString>() == "true"){
        this->setMicaEffectEnabled(true);
    }else{
        this->setMicaEffectEnabled(false);
    }

    this->splashScreen = new SplashScreen(new QVariant(QVariant::fromValue<QIcon>(this->windowIcon())), this, true);
    this->splashScreen->setIconSize(QSize(106, 106));
    this->splashScreen->raise();

    QRect desktop = QApplication::desktop()->availableGeometry();
    int w = desktop.width();
    int h = desktop.height();
    this->move(w / 2 - this->width() / 2, h / 2 - this->height() / 2);
    this->show();
    QApplication::processEvents();
}


void MainWindow::onSupport()
{
    MessageBoxF *w = new MessageBoxF("支持项目", "感谢支持本项目，感谢开源。", this);
    w->yesButton->setText("确认");
    w->cancelButton->setText("退出");
    if(w->exec()){
        QDesktopServices::openUrl(QUrl("http://www.github.com"));
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    FluentWindow::resizeEvent(event);
    this->splashScreen->resize(this->size());
}

void MainWindow::switchToSample(QString routeKey, int index)
{
    QList<GalleryInterface *> interfaces = this->findChildren<GalleryInterface*>();
    for(int i = 0; i < interfaces.length(); i++){
        GalleryInterface* w = interfaces.at(i);
        if(w->objectName() == routeKey){
            this->stackedWidget->setCurrentWidget(w, false);
            w->scrollToCard(index);
        }
    }
}