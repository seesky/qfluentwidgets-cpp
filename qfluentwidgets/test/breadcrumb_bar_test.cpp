#include <iostream>
#include <QtCore>
#include <QtWidgets>
#include <QtCore/Qt>
#include <QtCore/QUuid>
#include "../common/icon.h"
#include "../common/style_sheet.h"
#include "../common/config.h"
#include "../../qfluentwidgets/components/widgets/button.h"
#include "../../qfluentwidgets/components/widgets/menu.h"
#include "../../qfluentwidgets/components/widgets/flyout.h"
#include "../../qfluentwidgets/components/widgets/label.h"
#include "../../qfluentwidgets/components/widgets/command_bar.h"
#include "../../qfluentwidgets/components/widgets/line_edit.h"
#include "../../qfluentwidgets/qframelesswindow/windows/qframe_less_window.h"
#include "../../qfluentwidgets/qframelesswindow/titlebar/titlebar.h"
#include "../../qfluentwidgets/components/dialog_box/dialog.h"
#include "../../qfluentwidgets/components/navigation/breadcrumb.h"

class Demo : public QWidget{
public:

    BreadcrumbBar *breadcrumbBar;
    QStackedWidget *stackedWidget;
    LineEdit *lineEdit;
    PrimaryToolButton *addButton;
    QVBoxLayout *vBoxLayout;
    QHBoxLayout *lineEditLayout;

    Demo(QWidget *parent) : QWidget(parent){
        this->breadcrumbBar = new BreadcrumbBar(this);
        this->stackedWidget = new QStackedWidget(this);
        this->lineEdit = new LineEdit(this);

        FluentIcon *sendIcon = new FluentIcon();
        sendIcon->setIconName(QString("SEND"));
        this->addButton = new PrimaryToolButton(sendIcon, this);

        this->vBoxLayout = new QVBoxLayout(this);
        this->lineEditLayout = new QHBoxLayout();

        connect(this->addButton, &PrimaryToolButton::clicked, this, [this](){
            this->addInterface(this->lineEdit->text());
        });

        connect(this->lineEdit, &LineEdit::returnPressed, this, [this](){
            this->addInterface(this->lineEdit->text());
        });
        this->lineEdit->setPlaceholderText(QString("Enter the name of interface"));

        Font().setFont(this->breadcrumbBar, 26, QFont::Normal);
        this->breadcrumbBar->setSpacing(26);
        connect(this->breadcrumbBar, &BreadcrumbBar::currentItemChanged, this, &Demo::switchInterface);

        this->addInterface(QString("Home"));
        this->addInterface(QString("Documents"));

        this->vBoxLayout->setContentsMargins(20, 20, 20, 20);
        this->vBoxLayout->addWidget(this->breadcrumbBar);
        this->vBoxLayout->addWidget(this->stackedWidget);
        this->vBoxLayout->addLayout(this->lineEditLayout);

        this->lineEditLayout->addWidget(this->lineEdit, 1);
        this->lineEditLayout->addWidget(this->addButton);

        this->resize(500, 500);

    }

    void addInterface(QString text){
        if(text.isEmpty()){
            return;
        }

        SubtitleLabel *w = new SubtitleLabel(text, nullptr);
        w->setObjectName(QUuid::createUuid().toString());
        w->setAlignment(Qt::AlignCenter);

        this->lineEdit->clear();
        this->stackedWidget->addWidget(w);
        this->stackedWidget->setCurrentWidget(w);

        this->breadcrumbBar->addItem(w->objectName(), text);

    }

public slots:
    void switchInterface(QString objectName)
    {
        this->stackedWidget->setCurrentWidget(this->findChild<SubtitleLabel*>(objectName));
    }
};


int main(int argc, char *argv[])
{
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    
    QApplication *app = new QApplication(argc, argv);
    Demo *w = new Demo(nullptr);
    w->show();
    return app->exec();
}