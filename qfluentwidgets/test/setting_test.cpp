#include <QtCore/Qt>
#include <QtCore/QLocale>
#include <QtCore/QTranslator>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QDesktopWidget>

#include "../../qfluentwidgets/qframelesswindow/windows/qframe_less_window.h"
#include "../../qfluentwidgets/common/config.h"
#include "../../qfluentwidgets/common/translator.h"
#include "settings_test/setting_interface.h"
#include "settings_test/setting_config.h"


class Window : public WindowsFramelessWindow{
public:
    Window(QWidget *parent) : WindowsFramelessWindow(parent){
        this->setTitleBar(new StandardTitleBar(this));
        this->hBoxLayout = new QHBoxLayout(this);
        this->settingInterface = new SettingInterface(this);
        this->hBoxLayout->setContentsMargins(0, 0, 0, 0);
        this->hBoxLayout->addWidget(this->settingInterface);

        this->setWindowIcon(QIcon("resource/logo.png"));
        this->setWindowTitle("Fluent Widgets");
        this->resize(1080, 784);

        QRect desktop = QApplication::desktop()->availableGeometry();
        int w = desktop.width();
        int h = desktop.height();
        this->move(w / 2 - this->width() / 2, h / 2 - this->height() / 2);

        this->titleBar->raise();

        this->setQss();


    }
    void setQss(){
        QString color = isDarkTheme() ? QString("dark") : QString("light");

        QFile file(QString("resource/setting_resource/qss/%1/setting_interface.qss").arg(color));
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream stream(&file);
            QString styleSheet = stream.readAll();
            this->setStyleSheet(styleSheet);
            file.close();
        } else {
            qWarning("Cannot open file: %s", qPrintable(file.errorString()));
        }
    }

    QHBoxLayout *hBoxLayout;
    SettingInterface *settingInterface;
};



int main(int argc, char *argv[])
{
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    
    QApplication *app = new QApplication(argc, argv);

    QString languageString = qconfig->get(QVariant::fromValue<OptionsConfigItem *>(qconfig->language)).value<QString>();
    QLocale *locale;
    if(languageString == "chinese simplified"){
        locale = new QLocale(QLocale::Chinese, QLocale::China);
    }else if(languageString == "chinese traditional"){
        locale = new QLocale(QLocale::Chinese, QLocale::HongKong);
    }else if(languageString == "english"){
        locale = new QLocale(QLocale::English);
    }else{
        locale = new QLocale();
    }
    
    FluentTranslator *fluentTranslator = new FluentTranslator(locale, nullptr);
    QTranslator *settingTranslator = new QTranslator();
    settingTranslator->load(*locale, "settings", ".", "resource/i18n");

    app->installTranslator(fluentTranslator);
    app->installTranslator(settingTranslator);

   
    Window *w = new Window(nullptr);
    w->show();
    return app->exec();
}