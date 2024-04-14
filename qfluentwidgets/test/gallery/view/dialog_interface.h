#pragma once

#include "gallery_interface.h"
#include "../common/translator.h"
#include "../../../components/dialog_box/dialog.h"
#include "../../../components/dialog_box/message_box_base.h"
#include "../../../components/widgets/line_edit.h"
#include "../../../components/dialog_box/color_dialog.h"
#include "../../../components/widgets/flyout.h"
#include "../../../components/widgets/teaching_tip.h"


class DialogInterface : public GalleryInterface{
    Q_OBJECT
public:
    DialogInterface(QWidget *parent);
    PushButton *showSimpleFlyoutPushButton;
    PushButton *showComplexFlyoutButton;
    PushButton *teachingButton;
    PushButton *teachingRightButton;
public slots:
    void showDialog();
    void showMessageDialog();
    void showCustomDialog();
    void showColorDialog();
    void showSimpleFlyout();
    void showComplexFlyout();
    void showBottomTeachingTip();
    void showLeftBottomTeachingTip();
};


class CustomMessageBox : public MessageBoxBase{
    Q_OBJECT
public:
    CustomMessageBox(QWidget *parent);
    void _validateUrl(QString text);

    SubtitleLabel *titleLabel;
    LineEdit *urlLineEdit;
};