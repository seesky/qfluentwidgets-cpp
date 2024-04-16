#pragma once

#include "gallery_interface.h"
#include "../common/translator.h"
#include "../../../components/widgets/line_edit.h"
#include "../../../components/widgets/spin_box.h"

class TextInterface : public GalleryInterface{
    Q_OBJECT
public:
    TextInterface(QWidget *parent);
};
