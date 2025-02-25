#pragma once

#include <QtCore/Qt>
#include <QtCore/QSize>
#include <QtCore/QMetaObject>
#include <QtGui/QIcon>
#include <QtGui/QPixmap>
#include <QtWidgets/QLabel>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QSizePolicy>
#include <QtWidgets/QSpacerItem>
#include <QtGui/QPixmap>


#include "../../qfluentwidgets-cpp/qfluentwidgets/qframelesswindow/windows/qframe_less_window.h"
#include "../../qfluentwidgets-cpp/qfluentwidgets/common/style_sheet.h"
#include "../../qfluentwidgets-cpp/qfluentwidgets/window/fluent_window.h"
#include "../../qfluentwidgets-cpp/qfluentwidgets/components/widgets/label.h"
#include "../../qfluentwidgets-cpp/qfluentwidgets/components/widgets/check_box.h"
#include "../../qfluentwidgets-cpp/qfluentwidgets/components/widgets/button.h"
#include "../../qfluentwidgets-cpp/qfluentwidgets/components/widgets/line_edit.h"




class LoginWindow : public AcrylicWindow{
    Q_OBJECT
public:
    LoginWindow(QWidget *parent);
    void resizeEvent(QResizeEvent *event) override;
    void setupUi();
    void retranslateUi();

    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QSizePolicy *sizePolicy;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *spacerItem;
    QLabel *label_2;
    QSizePolicy *sizePolicy2;
    QSpacerItem *spacerItem1;
    QGridLayout *gridLayout;
    LineEdit *lineEdit;
    BodyLabel *label_3;
    LineEdit *lineEdit_2;
    BodyLabel *label_4;
    BodyLabel *label_5;
    LineEdit *lineEdit_3;
    BodyLabel *label_6;
    LineEdit *lineEdit_4;
    QSpacerItem *spacerItem2;
    CheckBox *checkBox;
    QSpacerItem *spacerItem3;
    PrimaryPushButton *pushButton;
    QSpacerItem *spacerItem4;
    HyperlinkButton *pushButton_2;
    QSpacerItem *spacerItem5;


};