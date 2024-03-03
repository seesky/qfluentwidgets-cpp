#include <iostream>
#include <QtCore>
#include <QtWidgets>
#include <QtCore/Qt>
#include "../../qfluentwidgets/components/widgets/switch_button.h"


class ButtonView : public QWidget{
public:
    ButtonView(){
        setStyleSheet("ButtonView{background: rgb(255,255,255)}");
    }
};



class SwitchButtonView : public ButtonView{
public:
    SwitchButton *switchButton;
    
    QGridLayout *gridLayout;
    SwitchButtonView(){
        resize(160, 80);
        this->switchButton = new SwitchButton(this, IndicatorPosition::LEFT);
        this->switchButton->move(48, 24);
        connect(this->switchButton, &SwitchButton::checkedChanged, this, &SwitchButtonView::onCheckedChanged);

        /*
        connect(this->switchButton, &SwitchButton::checkedChanged, this, [this](){
            emit(this->onCheckedChanged())
        });
        */
       
    }


public slots:
    void onCheckedChanged(bool isChecked)
    {
        QString text = isChecked ? QString("On") : QString("Off");
        this->switchButton->setText(text);
    }
};



int main(int argc, char *argv[])
{
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    
    QApplication *app = new QApplication(argc, argv);
    SwitchButtonView *w = new SwitchButtonView();
    w->show();
    return app->exec();
}