#pragma once

#include "gallery_interface.h"
#include "../common/translator.h"

#include "../../../components/widgets/scroll_area.h"
#include "../../../components/widgets/pips_pager.h"

class ScrollInterface : public GalleryInterface{
    Q_OBJECT
public:
    ScrollInterface(QWidget *parent);
};