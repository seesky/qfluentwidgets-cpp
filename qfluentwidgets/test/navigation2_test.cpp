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
#include "../components/navigation/navigation_interface.h"
#include "../components/dialog_box/dialog.h"
#include "../common/config.h"
#include "../common/style_sheet.h"
#include "../common/icon.h"
#include "../../qfluentwidgets/qframelesswindow/windows/qframe_less_window.h"
#include "../../qfluentwidgets/qframelesswindow/titlebar/titlebar.h"


class Widget : public QFrame{
public:
    QLabel *label;
    QHBoxLayout *hBoxLayout;

    Widget(QString text, QWidget *parent){
        this->setObjectName(text.replace(" ", "-"));
        this->label = new QLabel(text, this);
        this->label->setAlignment(Qt::AlignCenter);
        this->hBoxLayout = new QHBoxLayout(this);
        this->hBoxLayout->addWidget(this->label, 1, Qt::AlignCenter);
        

        this->hBoxLayout->setContentsMargins(0, 32, 0, 0);
    }
};

//自定义NavigationWidget
class MAvatarWidget : public NavigationWidget{
public:
    QImage avatar;
    MAvatarWidget(bool isSelectable = false, QWidget *parent = nullptr) : NavigationWidget(isSelectable, parent){
        this->avatar = QImage("resource/shoko.png").scaled(24, 24, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }

    void paintEvent(QPaintEvent *event) override{
        QPainter painter(this);
        painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing);
        painter.setPen(Qt::NoPen);

        if(this->isPressed){
            painter.setOpacity(0.7);
        }

        if(this->isEnter){
            int c = isDarkTheme() ? 255 : 0;
            painter.setBrush(QColor(c, c, c, 10));
            painter.drawRoundedRect(this->rect(), 5, 5);
        }

        painter.setBrush(QBrush(this->avatar));
        painter.translate(8, 6);
        painter.drawEllipse(0, 0, 24, 24);
        painter.translate(-8, -6);

        if(!this->isCompacted){
            painter.setPen(isDarkTheme() ? Qt::white : Qt::black);
            QFont font = QFont(QString("Segoe UI"));
            font.setPixelSize(14);
            painter.setFont(font);
            painter.drawText(QRect(44, 0, 255, 36), Qt::AlignVCenter, QString("zhiyiYo"));
        }
    }
};


class CustomTitleBar : public TitleBar{
public:
    QLabel *iconLabel;
    QLabel *titleLabel;
    CustomTitleBar(QWidget *parent) : TitleBar(parent){
        this->iconLabel = new QLabel(this);
        this->iconLabel->setFixedSize(18, 18);
        this->hBoxLayout->insertSpacing(0, 10);
        this->hBoxLayout->insertWidget(1, this->iconLabel, 0, Qt::AlignLeft | Qt::AlignBottom);
        connect(this->window(), &QWidget::windowIconChanged, this, &CustomTitleBar::setIcon);

        this->titleLabel = new QLabel(this);
        this->hBoxLayout->insertWidget(2, this->titleLabel, 0, Qt::AlignLeft | Qt::AlignBottom);
        this->titleLabel->setObjectName(QString("titleLabel"));
        connect(this->window(), &QWidget::windowTitleChanged, this, &CustomTitleBar::setTitle);
    }


public slots:
    void setTitle(QString title){
        this->titleLabel->setText(title);
        this->titleLabel->adjustSize();
    }


    void setIcon(QIcon icon){
        this->iconLabel->setPixmap(QIcon(icon).pixmap(18, 18));
    }
};


class Window : public WindowsFramelessWindow{
public:
    QHBoxLayout *hBoxLayout;
    NavigationInterface *navigationInterface;
    QStackedWidget *stackWidget;

    Widget *searchInterface;
    Widget *musicInterface;
    Widget *videoInterface;
    Widget *folderInterface;
    Widget *settingInterface;

    Window() : WindowsFramelessWindow(nullptr){
        this->setTitleBar(new CustomTitleBar(this));

        this->hBoxLayout = new QHBoxLayout(this);
        this->navigationInterface = new NavigationInterface(this, true, true, true);
        this->stackWidget = new QStackedWidget(this);

        this->searchInterface = new Widget(QString("Search Interface"), this);
        this->musicInterface = new Widget(QString("Music Interface"), this);
        this->videoInterface = new Widget(QString("Video Interface"), this);
        this->folderInterface = new Widget(QString("Folder Interface"), this);
        this->settingInterface = new Widget(QString("Setting Interface"), this);

        this->initLayout();

        this->initNavigation();

        this->initWindow();
    }


    void initLayout(){
        this->hBoxLayout->setSpacing(0);
        this->hBoxLayout->setContentsMargins(0, 0, 0, 0);
        this->hBoxLayout->addWidget(this->navigationInterface);
        this->hBoxLayout->addWidget(this->stackWidget);
        this->hBoxLayout->setStretchFactor(this->stackWidget, 1);

        this->titleBar->raise();
        connect(this->navigationInterface, &NavigationInterface::displayModeChanged, this->titleBar, &TitleBar::raise);
    }

    void initNavigation(){

        
        FluentIcon *searchIcon = new FluentIcon();
        searchIcon->setIconName(QString("SEARCH"));
        this->addSubInterface(this->searchInterface, new QVariant(QVariant::fromValue<FluentIcon>(*searchIcon)), QString("Search"), NavigationItemPosition::TOP, nullptr);

        FluentIcon *musicIcon = new FluentIcon();
        musicIcon->setIconName(QString("MUSIC"));
        this->addSubInterface(this->musicInterface, new QVariant(QVariant::fromValue<FluentIcon>(*musicIcon)), QString("Music library"), NavigationItemPosition::TOP, nullptr);

        FluentIcon *videoIcon = new FluentIcon();
        videoIcon->setIconName(QString("VIDEO"));
        this->addSubInterface(this->videoInterface, new QVariant(QVariant::fromValue<FluentIcon>(*videoIcon)), QString("Video library"), NavigationItemPosition::TOP, nullptr);


        this->navigationInterface->addSeparator(NavigationItemPosition::TOP);

        
        FluentIcon *folderIcon = new FluentIcon();
        folderIcon->setIconName(QString("FOLDER"));
        this->addSubInterface(this->folderInterface, new QVariant(QVariant::fromValue<FluentIcon>(*folderIcon)), QString("Folder library"), NavigationItemPosition::SCROLL);

        /*
        this->navigationInterface->addWidget(QString("avatar"), new NavigationAvatarWidget(QString("zhiyiYo"), new QVariant(QVariant::fromValue<QString>(QString("resource/shoko.png"))), nullptr), [this](){
            this->showMessageBox();
        }, NavigationItemPosition::BOTTOM, QString(), QString());
        */

        this->navigationInterface->addWidget(QString("avatar"), new MAvatarWidget(false, nullptr), [this](){this->showMessageBox();}, NavigationItemPosition::BOTTOM, QString(), QString());


        FluentIcon *settingIcon = new FluentIcon();
        settingIcon->setIconName(QString("SETTING"));
        this->addSubInterface(this->settingInterface, new QVariant(QVariant::fromValue<FluentIcon>(*settingIcon)), QString("Settings"), NavigationItemPosition::BOTTOM);

        qrouter->setDefaultRouteKey(this->stackWidget, this->musicInterface->objectName());
        
        
        connect(this->stackWidget, &QStackedWidget::currentChanged, this, &Window::onCurrentInterfaceChanged);
        this->stackWidget->setCurrentIndex(1);

    }

    void initWindow(){
        this->resize(900, 700);
        this->setWindowIcon(QIcon("resource/logo.png"));
        this->setWindowTitle(QString("Qt Widgets"));
        this->titleBar->setAttribute(Qt::WA_StyledBackground);

        QRect desktop = QApplication::desktop()->availableGeometry();
        int w = desktop.width();
        int h = desktop.height();
        this->move(w / 2 - this->width() / 2, h / 2 - this->height() / 2);

        this->setQss();
    }


    void addSubInterface(QWidget *w, QVariant *icon, QString text, NavigationItemPosition position = NavigationItemPosition::TOP, QWidget *parent = nullptr)
    {
        this->stackWidget->addWidget(w);
        this->navigationInterface->addItem(w->objectName(), icon, text, [this, w](){
            this->switchTo(w);
        }, true, position, text, QString());
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
        w->yesButton->setText("ok");
        w->cancelButton->setText("cancel");
        w->exec();
    }


    void resizeEvent(QResizeEvent *event) override{
        this->titleBar->move(46, 0);
        this->titleBar->resize(this->width() - 46, this->titleBar->height());
    }


public slots:
    void onCurrentInterfaceChanged(int index)
    {
        QWidget *widget = this->stackWidget->widget(index);
        this->navigationInterface->setCurrentItem(widget->objectName());
        qrouter->push(this->stackWidget, widget->objectName());
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