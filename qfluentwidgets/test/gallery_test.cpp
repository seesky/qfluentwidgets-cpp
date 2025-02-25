#include <QtCore/Qt>
#include <QtCore/QTranslator>
#include <QtWidgets/QApplication>

#include "../common/translator.h"
#include "gallery/view/main_window.h"
#include "gallery/config/gallery_config.h"

int main(int argc, char *argv[])
{
    

    if(qconfig->get(QVariant::fromValue<OptionsConfigItem*>(galleryConfig->dpiScale)).value<QString>() == "auto"){
        QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
        QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    }else{
        QApplication::setAttribute(Qt::AA_DisableHighDpiScaling);
        qputenv("QT_SCALE_FACTOR", qconfig->get(QVariant::fromValue<OptionsConfigItem*>(galleryConfig->dpiScale)).value<QString>().toUtf8());
    }

    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    
    //qputenv("QT_PLUGIN_PATH", "");

    QApplication *app = new QApplication(argc, argv);

    // QString plugins_path = QCoreApplication::applicationDirPath()+"/plugins/";
    // qputenv("QT_QPA_PLATFORM_PLUGIN_PATH", plugins_path.toUtf8());

    //QApplication::addLibraryPath(QCoreApplication::applicationDirPath()+"/plugins/");

    // QString appDirPath = QCoreApplication::applicationDirPath();
    // QString pluginsDirPath = appDirPath + "/plugins/platforms";
    // qDebug() << pluginsDirPath;
    // app->addLibraryPath(pluginsDirPath);
    
    app->setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);


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
    settingTranslator->load(*locale, "gallery", ".", "gallery/i18n");

    app->installTranslator(fluentTranslator);
    app->installTranslator(settingTranslator);

    MainWindow *w = new MainWindow(nullptr);
    w->show();
    return app->exec();
}