#include <QtCore/Qt>
#include <QtCore/QSize>
#include <QtCore/QPoint>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>

#include "../components/widgets/progress_ring.h"
#include "../components/widgets/spin_box.h"
#include "../components/widgets/button.h"
#include "../common/icon.h"
#include "../common/style_sheet.h"

class Demo : public QWidget{
public:

    QVBoxLayout *vBoxLayout;
    QHBoxLayout *hBoxLayout;
    IndeterminateProgressRing *spinner;
    ProgressRing *progressRing;
    SpinBox *spinBox;
    ToggleToolButton *button;
    Demo(){
        this->vBoxLayout = new QVBoxLayout(this);
        this->hBoxLayout = new QHBoxLayout();

        FluentIcon *icon = new FluentIcon();
        icon->setIconName(QString("PAUSE_BOLD"));
        this->button = new ToggleToolButton(icon, this);
        this->spinner = new IndeterminateProgressRing(this, true);
        this->progressRing = new ProgressRing(this, true);
        this->spinBox = new SpinBox(this);

        this->progressRing->setVal(50);
        this->progressRing->setTextVisible(true);
        this->progressRing->setFixedSize(80, 80);

        this->spinBox->setRange(0, 180);
        this->spinBox->setValue(50);
        connect(this->spinBox, static_cast<void(SpinBox::*)(int)>(&SpinBox::valueChanged), this->progressRing, &ProgressRing::setValue); //TODO:关注信号是否正确

        this->hBoxLayout->addWidget(this->progressRing, 0, Qt::AlignHCenter);
        this->hBoxLayout->addWidget(this->spinBox, 0, Qt::AlignHCenter);

        this->vBoxLayout->setContentsMargins(30, 30, 30, 30);
        this->vBoxLayout->addLayout(this->hBoxLayout);
        this->vBoxLayout->addWidget(this->spinner, 0, Qt::AlignHCenter);
        this->vBoxLayout->addWidget(this->button, 0, Qt::AlignHCenter);

        connect(this->button, &ToggleToolButton::clicked, this, &Demo::onButtonClicked);


        this->resize(400, 400);
    };

public slots:
    void onButtonClicked(){
        if(!this->progressRing->isPaused()){
            this->progressRing->pause();
            FluentIcon *icon = new FluentIcon();
            icon->setIconName(QString("PLAY_SOLID"));
            this->button->setIcon(new QVariant(QVariant::fromValue<FluentIcon>(*icon)));
        }else{
            this->progressRing->resume();
            FluentIcon *icon = new FluentIcon();
            icon->setIconName(QString("PAUSE_BOLD"));
            this->button->setIcon(new QVariant(QVariant::fromValue<FluentIcon>(*icon)));
        }
    
        
    };
};




int main(int argc, char *argv[])
{
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    
    QApplication *app = new QApplication(argc, argv);
    Demo *w = new Demo();
    w->show();
    return app->exec();
}