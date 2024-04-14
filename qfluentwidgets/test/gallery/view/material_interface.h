#pragma once

#include "gallery_interface.h"
#include "../common/translator.h"
#include "../../../components/widgets/arcylic_label.h"

class MaterialInterface : public GalleryInterface{
    Q_OBJECT
public:
    MaterialInterface(QWidget *parent);
    int radius;
    AcrylicLabel *label;
public slots:
    void onBlurRadiusChanged(int radius);
};
