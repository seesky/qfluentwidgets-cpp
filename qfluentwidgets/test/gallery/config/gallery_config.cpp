#include "gallery_config.h"

GalleryConfig* GalleryConfig::instance = nullptr;

GalleryConfig::GalleryConfig()
{
    this->micaEnabled = new OptionsConfigItem("MainWindow", "MicaEnabled", true ? "true" : "false", QList<QString>(), false);
    QList<QString> dpiList = {"1", "1.25", "1.5", "1.75", "2", "auto"};
    this->dpiScale = new OptionsConfigItem("MainWindow", "DpiScale", "auto", dpiList, true);
    QList<QString> languageList = {"chinese simplified", "chinese traditional", "english", "auto"};
    this->languate = new OptionsConfigItem("MainWindow", "Language", "auto", languageList, true);
    this->checkUpdateAtStartUp = new OptionsConfigItem("Update", "CheckUpdateAtStartUp", "false", QList<QString>(), false);

    this->blurRadius = new RangeConfigItem("Material", "AcrylicBlurRadius", 15, 0, 40, false);
}



GalleryConfig* GalleryConfig::getInstance()
{
    if(instance == nullptr){
        instance = new GalleryConfig();
    }
    return instance;
}