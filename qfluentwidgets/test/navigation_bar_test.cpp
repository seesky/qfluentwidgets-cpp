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
#include "../common/config.h"
#include "../common/style_sheet.h"
#include "../common/icon.h"
#include "../../qfluentwidgets/qframelesswindow/windows/qframe_less_window.h"
#include "../../qfluentwidgets/qframelesswindow/titlebar/titlebar.h"


class Widget : public QFrame{
    Q_OBJECT
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


class MStackedWidget : public QFrame{
    Q_OBJECT
public:
    MStackedWidget(QWidget *parent) : QFrame(parent){
        this->hBoxLayout = new QHBoxLayout(this);
        this->view = new PopUpAniStackedWidget(this);
        this->hBoxLayout->setContentsMargins(0, 0, 0, 0);
        this->hBoxLayout->addWidget(this->view);

        connect(this->view, &PopUpAniStackedWidget::currentChanged, this, &MStackedWidget::currentChanged);
    }


    void addWidget(QWidget *widget){
        this->view->addWidget(widget, 0, 76);
    }


    QWidget *widget(int index){
        return this->view->widget(index);
    }


    void setCurrentWidget(QWidget *widget, bool popOut = false){
        if(!popOut){
            this->view->setCurrentWidget(widget, false, true, 250, QEasingCurve::OutQuad);
        }else{
            this->view->setCurrentWidget(widget, true, false, 200, QEasingCurve::InQuad);
        }
    }


    void setCurrentIndex(int index, bool popOut){
        this->setCurrentWidget(this->view->widget(index), popOut);
    }

    QHBoxLayout *hBoxLayout;
    PopUpAniStackedWidget *view;

signals:
    void currentChanged(int);
};




class CustomTitleBar : public TitleBar{
    Q_OBJECT
public:
    QLabel *iconLabel;
    QLabel *titleLabel;
    SearchLineEdit *searchLineEdit;
    QVBoxLayout *vBoxLayout;
    QHBoxLayout *buttonLayout;
    CustomTitleBar(QWidget *parent) : TitleBar(parent){

        this->setFixedHeight(48);
        this->hBoxLayout->removeWidget(this->minBtn);
        this->hBoxLayout->removeWidget(this->maxBtn);
        this->hBoxLayout->removeWidget(this->closeBtn);

        this->iconLabel = new QLabel(this);
        this->iconLabel->setFixedSize(18, 50);
        this->hBoxLayout->insertSpacing(0, 20);
        this->hBoxLayout->insertWidget(1, this->iconLabel, 0, Qt::AlignLeft | Qt::AlignBottom);
        connect(this->window(), &QWidget::windowIconChanged, this, &CustomTitleBar::setIcon);

        this->titleLabel = new QLabel(this);
        this->hBoxLayout->insertWidget(2, this->titleLabel, 0, Qt::AlignLeft | Qt::AlignBottom);
        this->titleLabel->setObjectName(QString("titleLabel"));
        connect(this->window(), &QWidget::windowTitleChanged, this, &CustomTitleBar::setTitle);

        this->searchLineEdit = new SearchLineEdit(this);
        this->searchLineEdit->setPlaceholderText(QString("搜索应用、游戏、电影、设备等"));
        this->searchLineEdit->setFixedWidth(400);
        this->searchLineEdit->setClearButtonEnabled(true);

        this->vBoxLayout = new QVBoxLayout();
        this->buttonLayout = new QHBoxLayout();
        this->buttonLayout->setSpacing(0);
        this->buttonLayout->setContentsMargins(0, 0, 0, 0);
        this->buttonLayout->setAlignment(Qt::AlignTop);
        this->buttonLayout->addWidget(this->minBtn);
        this->buttonLayout->addWidget(this->maxBtn);
        this->buttonLayout->addWidget(this->closeBtn);
        this->vBoxLayout->addLayout(this->buttonLayout);
        this->vBoxLayout->addStretch(1);
        this->hBoxLayout->addLayout(this->vBoxLayout, 0);

    }

    void resizeEvent(QResizeEvent *event) override{
        this->searchLineEdit->move((this->width() - this->searchLineEdit->width()) / 2, 8);
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
    Q_OBJECT
public:
    QHBoxLayout *hBoxLayout;
    NavigationBar *navigationBar;
    MStackedWidget *stackWidget;


    Widget *homeInterface;
    Widget *appInterface;
    Widget *videoInterface;
    Widget *libraryInterface;

    Window() : WindowsFramelessWindow(nullptr){
        this->setTitleBar(new CustomTitleBar(this));

        this->hBoxLayout = new QHBoxLayout(this);
        this->navigationBar = new NavigationBar(this);
        this->stackWidget = new MStackedWidget(this);

        this->homeInterface = new Widget(QString("Home Interface"), this);
        this->appInterface = new Widget(QString("Application Interface"), this);
        this->videoInterface = new Widget(QString("Video Interface"), this);
        this->libraryInterface = new Widget(QString("library Interface"), this);

        this->initLayout();

        this->initNavigation();

        this->initWindow();
    }


    void initLayout(){
        this->hBoxLayout->setSpacing(0);
        this->hBoxLayout->setContentsMargins(0, 48, 0, 0);
        this->hBoxLayout->addWidget(this->navigationBar);
        this->hBoxLayout->addWidget(this->stackWidget);
        this->hBoxLayout->setStretchFactor(this->stackWidget, 1);
    }

    void initNavigation(){

        
        FluentIcon *honmeIcon = new FluentIcon();
        honmeIcon->setIconName(QString("HOME"));
        FluentIcon *honmeFillIcon = new FluentIcon();
        honmeFillIcon->setIconName(QString("HOME_FILL"));
        this->addSubInterface(this->homeInterface, new QVariant(QVariant::fromValue<FluentIcon>(*honmeIcon)), QString("主页"), NavigationItemPosition::TOP, new QVariant(QVariant::fromValue<FluentIcon>(*honmeFillIcon)));
        
        
        FluentIcon *applicatonIcon = new FluentIcon();
        applicatonIcon->setIconName(QString("APPLICATION"));
        this->addSubInterface(this->appInterface, new QVariant(QVariant::fromValue<FluentIcon>(*applicatonIcon)), QString("应用"), NavigationItemPosition::TOP, new QVariant());
        
        FluentIcon *videoIcon = new FluentIcon();
        videoIcon->setIconName(QString("VIDEO"));
        this->addSubInterface(this->videoInterface, new QVariant(QVariant::fromValue<FluentIcon>(*videoIcon)), QString("视频"), NavigationItemPosition::TOP, new QVariant());

        
        FluentIcon *bookShelfIcon = new FluentIcon();
        bookShelfIcon->setIconName(QString("BOOK_SHELF"));
        FluentIcon *libraryFillIcon = new FluentIcon();
        libraryFillIcon->setIconName(QString("HOME_FILL"));
        this->addSubInterface(this->libraryInterface, new QVariant(QVariant::fromValue<FluentIcon>(*bookShelfIcon)), QString("库"), NavigationItemPosition::BOTTOM, new QVariant(QVariant::fromValue<FluentIcon>(*libraryFillIcon)));


        
        FluentIcon *helpIcon = new FluentIcon();
        helpIcon->setIconName(QString("HELP"));
        this->navigationBar->addItem(QString("Help"), new QVariant(QVariant::fromValue<FluentIcon>(*helpIcon)), QString("帮助"), [this](){
            this->showMessageBox();
        }, false, new QVariant(), NavigationItemPosition::BOTTOM);
        
        
        connect(this->stackWidget, &MStackedWidget::currentChanged, this, &Window::onCurrentInterfaceChanged);
        this->navigationBar->setCurrentItem(this->homeInterface->objectName());

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


    void addSubInterface(QWidget *w, QVariant *icon, QString text, NavigationItemPosition position = NavigationItemPosition::TOP, QVariant *selectedIcon = nullptr)
    {
        this->stackWidget->addWidget(w);
        this->navigationBar->addItem(w->objectName(), icon, text, [this, w](){
            this->switchTo(w);
        }, true, selectedIcon ,position);
    }



    void setQss()
    {
        QString color = isDarkTheme() ? QString("dark") : QString("light");
        qDebug() << color;
        QFile file(QString("resource/%1/navigation_bar_demo.qss").arg(color));
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream stream(&file);
            QString styleSheet = stream.readAll();
            this->setStyleSheet(styleSheet);
            file.close();
        } else {
            qWarning("Cannot open file: %s", qPrintable(file.errorString()));
        }
        
    }

    void switchTo(QWidget *widget)
    {
        this->stackWidget->setCurrentWidget(widget, false);
    }


    void showMessageBox()
    {
        MessageBoxF *w = new MessageBoxF(QString("This is a help message"), QString("You clicked a customized navigation widget. You can add more custom widgets by calling `NavigationInterface.addWidget()` 😉"), this);
        w->yesButton->setText("ok");
        w->cancelButton->setText("cancel");
        w->exec();
    }



public slots:
    void onCurrentInterfaceChanged(int index)
    {
        QWidget *widget = this->stackWidget->widget(index);
        this->navigationBar->setCurrentItem(widget->objectName());
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


#include "navigation_bar_test.moc"