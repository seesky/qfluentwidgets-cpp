#pragma once

#include <QtCore/Qt>
#include <QtCore/QSize>
#include <QtWidgets/QWidget>
#include <QtWIdgets/QVBoxLayout>
#include <QtWIdgets/QButtonGroup>

#include "../../../components/widgets/button.h"
#include "../../../components/widgets/check_box.h"
#include "../../../components/widgets/combo_box.h"
#include "../../../components/widgets/slider.h"
#include "../../../components/widgets/switch_button.h"
#include "gallery_interface.h"
#include "../common/translator.h"

class BasicInputInterface : public GalleryInterface{
    Q_OBJECT
public:
    BasicInputInterface(QWidget *parent);
};