#pragma once

#include "gallery_interface.h"
#include "../common/translator.h"
#include "../../../components/widgets/state_tool_tip.h"
#include "../../../components/widgets/info_badge.h"
#include "../../../components/widgets/button.h"
#include "../../../components/widgets/info_bar.h"
#include "../../../components/widgets/progress_bar.h"
#include "../../../components/widgets/spin_box.h"
#include "../../../components/widgets/progress_ring.h"


class StatusInfoInterface : public GalleryInterface{
    Q_OBJECT
public:
    StatusInfoInterface(QWidget *parent);
    StateToolTip *stateTooltip;

public slots:
    void onStateButtonClicked();
    void createTopRightInfoBar();
    void createTopInfoBar();
    void createTopLeftInfoBar();
    void createBottomRightInfoBar();
    void createBottomInfoBar();
    void createBottomLeftInfoBar();
};


class ProgressWidget : public QWidget{
    Q_OBJECT
public:
    ProgressWidget(QWidget *widget, QWidget *parent);

    SpinBox *spinBox;
};
