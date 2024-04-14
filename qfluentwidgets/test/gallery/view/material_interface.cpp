#include "material_interface.h"


MaterialInterface::MaterialInterface(QWidget *parent) : GalleryInterface(Translator(nullptr).material, "fluentwidgets.components.widgets", parent)
{
    this->setObjectName("materialInterface");

    this->label = new AcrylicLabel(
        qconfig->get(QVariant::fromValue<RangeConfigItem*>(galleryConfig->blurRadius)).value<QString>().toUInt(),
        QColor(105, 114, 168, 102),
        QColor(255, 255, 255, 0),
        std::tuple<int,int>(),
        nullptr
    );

    this->label->setImage("qfluentwidgets/images/chidanta.jpg");
    this->label->setMaximumSize(787, 579);
    this->label->setMinimumSize(197, 145);
    connect(galleryConfig->blurRadius, &RangeConfigItem::valueChanged, this, &MaterialInterface::onBlurRadiusChanged);

    this->addExampleCard(
        this->tr("Acrylic label"),
        this->label,
        "http://www.github.com", 1
    );
}


void MaterialInterface::onBlurRadiusChanged(int radius)
{
    this->label->blurRadius = radius;
    this->label->setImage("qfluentwidgets/images/chidanta.jpg");
}