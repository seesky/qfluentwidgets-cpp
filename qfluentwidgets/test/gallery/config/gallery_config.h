#pragma once

#include "../../../common/config.h"
#include "../../../common/style_sheet.h"


class GalleryConfig{
public:
    static GalleryConfig* getInstance();
    OptionsConfigItem *micaEnabled;
    OptionsConfigItem *dpiScale;
    OptionsConfigItem *languate;
    OptionsConfigItem *checkUpdateAtStartUp;
    RangeConfigItem *blurRadius;
private:
    GalleryConfig();
    GalleryConfig(const GalleryConfig&) = delete;
    GalleryConfig& operator=(const GalleryConfig&) = delete;
    static GalleryConfig* instance;
};

static GalleryConfig *galleryConfig = GalleryConfig::getInstance();