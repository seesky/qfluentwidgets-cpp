#pragma once

#include <QtWidgets/QWidget>

#include "gallery_interface.h"
#include "../common/translator.h"
#include "../../../components/layout/flow_layout.h"
#include "../../../components/widgets/button.h"

class LayoutInterface : public GalleryInterface{
    Q_OBJECT
public:
    LayoutInterface(QWidget *parent);
    QWidget *createWidget(bool animation);
};
