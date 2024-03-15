#pragma once

#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include "../../common/auto_wrap.h"
#include "../../common/style_sheet.h"
#include "mask_dialog_base.h"

class MessageDialog : public MaskDialogBase{
    Q_OBJECT
public:
    MessageDialog(QString title, QString content, QWidget *parent);
    void __initWidget();
    void __initLayout();
    void __setQss();
    QString content;
    QLabel *titleLabel;
    QLabel *contentLabel;
    QPushButton *yesButton;
    QPushButton *cancelButton;

signals:
    void yesSignal();
    void cancelSignal();

public slots:
    void __onCancelButtonClicked();
    void __onYesButtonClicked();
};

