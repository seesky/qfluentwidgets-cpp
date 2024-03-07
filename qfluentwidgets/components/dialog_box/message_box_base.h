#pragma once

#include <QtCore/Qt>
#include <QtGui/QColor>
#include <QtWidgets/QFrame>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QPushButton>

#include "../../common/style_sheet.h"
#include "../widgets/button.h"
#include "mask_dialog_base.h"

class MessageBoxBase : public MaskDialogBase{
    Q_OBJECT
public:
    MessageBoxBase(QWidget *parent);
    void __initWidget();
    void __initLayout();
    void __setQss();
    void hideYesButton();
    void hideCancelButton();

    QFrame *buttonGroup;
    PrimaryPushButton *yesButton;
    QPushButton *cancelButton;
    QVBoxLayout *vBoxLayout;
    QVBoxLayout *viewLayout;
    QHBoxLayout *buttonLayout;

signals:
    void accepted();
    void rejected();

public slots:
    void __onCancelButtonClicked();
    void __onYesButtonClicked();
};


