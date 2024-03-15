#pragma once

#include <QtCore/Qt>
#include <QtCore/QObject>
#include <QtCore/QEvent>
#include <QtGui/QColor>
#include <QtWidgets/QLabel>
#include <QtWidgets/QFrame>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include "../../qframelesswindow/windows/qframe_less_window.h"

#include "../../common/style_sheet.h"
#include "../widgets/button.h"
#include "mask_dialog_base.h"
#include "../../common/auto_wrap.h"

class Dialog : public FramelessDialog{
    Q_OBJECT
public:
    Dialog(QString title, QString content, QWidget *parent);
    void _setUpUi(QString title, QString content, QWidget *parent);
    void __initWidget();
    void _adjustText();
    void __initLayout();
    void __setQss();
    void setContentCopyable(bool isCopyable);
    void setTitleBarVisible(bool isVisible);

    QString content;
    QLabel *titleLabel;
    QLabel *contentLabel;
    QLabel *windowTitleLabel;
    QFrame *buttonGroup;
    PrimaryPushButton *yesButton;
    QPushButton *cancelButton;
    QVBoxLayout *vBoxLayout;
    QVBoxLayout *textLayout;
    QHBoxLayout *buttonLayout;
signals:
    void yesSignal();
    void cancelSignal();

public slots:
    void __onCancelButtonClicked();
    void __onYesButtonClicked();
};



class MessageBoxF : public MaskDialogBase{
    Q_OBJECT
public:
    MessageBoxF(QString title, QString content, QWidget *parent);
    void _setUpUi(QString title, QString content, QWidget *parent);
    void __initWidget();
    void _adjustText();
    void __initLayout();
    void __setQss();
    void setContentCopyable(bool isCopyable);
    bool eventFilter(QObject *obj, QEvent *e) override;

    QString content;
    QLabel *titleLabel;
    QLabel *contentLabel;
    QLabel *windowTitleLabel;
    QFrame *buttonGroup;
    PrimaryPushButton *yesButton;
    QPushButton *cancelButton;
    QVBoxLayout *vBoxLayout;
    QVBoxLayout *textLayout;
    QHBoxLayout *buttonLayout;
signals:
    void yesSignal();
    void cancelSignal();

public slots:
    void __onCancelButtonClicked();
    void __onYesButtonClicked();
};