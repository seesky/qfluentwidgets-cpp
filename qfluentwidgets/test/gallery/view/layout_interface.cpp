#include "layout_interface.h"


LayoutInterface::LayoutInterface(QWidget *parent) : GalleryInterface(Translator(nullptr).layout, "fluentwidgets.components.layout", parent)
{
    this->setObjectName("layoutInterface");

    this->addExampleCard(
        this->tr("Flow layout without animation"),
        this->createWidget(false),
        "http://www.github.com", 1
    );

    this->addExampleCard(
        this->tr("Flow layout with animation"),
        this->createWidget(true),
        "http://www.github.com", 1
    );
}



QWidget *LayoutInterface::createWidget(bool animation = false)
{
    QStringList texts = {
        this->tr("Star Platinum"), this->tr("Hierophant Green"),
        this->tr("Silver Chariot"), this->tr("Crazy diamond"),
        this->tr("Heaven's Door"), this->tr("Killer Queen"),
        this->tr("Gold Experience"), this->tr("Sticky Fingers"),
        this->tr("Sex Pistols"), this->tr("Dirty Deeds Done Dirt Cheap")
    };

    QWidget *widget = new QWidget();
    FlowLayout *layout = new FlowLayout(widget, animation, false);

    layout->setContentsMargins(0, 0, 0, 0);
    layout->setVerticalSpacing(20);
    layout->setHorizontalSpacing(10);

    for(int i = 0; i < texts.length(); i++){
        layout->addWidget(new PushButton(texts.at(i), nullptr, nullptr));
    }
    return widget;
}