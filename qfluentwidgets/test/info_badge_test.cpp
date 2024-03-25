#include <QtCore/Qt>
#include <QtCore/QSize>
#include <QtCore/QPoint>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>

#include "../components/widgets/info_badge.h"
#include "../components/widgets/button.h"
#include "../common/icon.h"


class Demo : public QWidget{
public:

    QVBoxLayout *vBoxLayout;
    QHBoxLayout *hBoxLayout1;
    QHBoxLayout *hBoxLayout2;
    QHBoxLayout *hBoxLayout3;
    ToolButton *button;
    QPushButton *button2;
    Demo(){
        this->vBoxLayout = new QVBoxLayout(this);

        this->hBoxLayout1 = new QHBoxLayout();
        this->hBoxLayout1->setSpacing(20);
        this->hBoxLayout1->setSizeConstraint(QHBoxLayout::SetMinimumSize);

        this->hBoxLayout1->addStretch();
        this->hBoxLayout1->addWidget(InfoBadge::info(new QVariant(QVariant::fromValue<int>(1)), nullptr, nullptr, InfoBadgePosition::TOP_RIGHT));
        this->hBoxLayout1->addWidget(InfoBadge::success(new QVariant(QVariant::fromValue<int>(10)), nullptr, nullptr, InfoBadgePosition::TOP_RIGHT));
        this->hBoxLayout1->addWidget(InfoBadge::attension(new QVariant(QVariant::fromValue<int>(100)), nullptr, nullptr, InfoBadgePosition::TOP_RIGHT));
        this->hBoxLayout1->addWidget(InfoBadge::warning(new QVariant(QVariant::fromValue<int>(1000)), nullptr, nullptr, InfoBadgePosition::TOP_RIGHT));
        this->hBoxLayout1->addWidget(InfoBadge::error(new QVariant(QVariant::fromValue<int>(10000)), nullptr, nullptr, InfoBadgePosition::TOP_RIGHT));
        this->hBoxLayout1->addWidget(InfoBadge::custom(new QVariant(QVariant::fromValue<QString>("1w+")), QColor("#005fb8"), QColor("#60cdff"), nullptr, nullptr, InfoBadgePosition::TOP_RIGHT));
        this->hBoxLayout1->addStretch();
        this->vBoxLayout->addLayout(this->hBoxLayout1);

        this->hBoxLayout2 = new QHBoxLayout();
        this->hBoxLayout2->setSpacing(20);
        this->hBoxLayout2->setSizeConstraint(QHBoxLayout::SetMinimumSize);

        this->hBoxLayout2->addStretch(1);
        this->hBoxLayout2->addWidget(DotInfoBadge::info(nullptr, nullptr, InfoBadgePosition::TOP_RIGHT));
        this->hBoxLayout2->addWidget(DotInfoBadge::success(nullptr, nullptr, InfoBadgePosition::TOP_RIGHT));
        this->hBoxLayout2->addWidget(DotInfoBadge::attension(nullptr, nullptr, InfoBadgePosition::TOP_RIGHT));
        this->hBoxLayout2->addWidget(DotInfoBadge::warning(nullptr, nullptr, InfoBadgePosition::TOP_RIGHT));
        this->hBoxLayout2->addWidget(DotInfoBadge::error(nullptr, nullptr, InfoBadgePosition::TOP_RIGHT));
        this->hBoxLayout2->addWidget(DotInfoBadge::custom(QColor("#005fb8"), QColor("#60cdff"), nullptr, nullptr, InfoBadgePosition::TOP_RIGHT));
        this->hBoxLayout2->addStretch(1);
        this->vBoxLayout->addLayout(this->hBoxLayout2);

        this->hBoxLayout3 = new QHBoxLayout();
        this->hBoxLayout3->setSpacing(20);
        this->hBoxLayout3->setSizeConstraint(QHBoxLayout::SetMinimumSize);

        this->hBoxLayout3->addStretch(1);

        FluentIcon *accept_medium_icon = new FluentIcon();
        accept_medium_icon->setIconName(QString("ACCEPT_MEDIUM"));
        this->hBoxLayout3->addWidget(IconInfoBadge::info(new QVariant(QVariant::fromValue<FluentIcon>(*accept_medium_icon)), nullptr, nullptr, InfoBadgePosition::TOP_RIGHT));
        this->hBoxLayout3->addWidget(IconInfoBadge::success(new QVariant(QVariant::fromValue<FluentIcon>(*accept_medium_icon)), nullptr, nullptr, InfoBadgePosition::TOP_RIGHT));
        this->hBoxLayout3->addWidget(IconInfoBadge::attension(new QVariant(QVariant::fromValue<FluentIcon>(*accept_medium_icon)), nullptr, nullptr, InfoBadgePosition::TOP_RIGHT));
        
        FluentIcon *cancel_medium_icon = new FluentIcon();
        cancel_medium_icon->setIconName(QString("CANCEL_MEDIUM"));
        this->hBoxLayout3->addWidget(IconInfoBadge::warning(new QVariant(QVariant::fromValue<FluentIcon>(*cancel_medium_icon)), nullptr, nullptr, InfoBadgePosition::TOP_RIGHT));
        this->hBoxLayout3->addWidget(IconInfoBadge::error(new QVariant(QVariant::fromValue<FluentIcon>(*cancel_medium_icon)), nullptr, nullptr, InfoBadgePosition::TOP_RIGHT));
        
        FluentIcon *ringer_icon = new FluentIcon();
        ringer_icon->setIconName(QString("RINGER"));
        IconInfoBadge *badge = IconInfoBadge::custom(new QVariant(QVariant::fromValue<FluentIcon>(*ringer_icon)), QColor("#005fb8"), QColor("#60cdff"), nullptr, nullptr, InfoBadgePosition::TOP_RIGHT);
        badge->setFixedSize(32, 32);
        badge->setIconSize(QSize(16, 16));
        this->hBoxLayout3->addWidget(badge);

        this->hBoxLayout3->addStretch(1);
        this->vBoxLayout->addLayout(this->hBoxLayout3);

        
        FluentIcon *basketball_icon = new FluentIcon();
        basketball_icon->setIconName(QString("BASKETBALL"));
        this->button = new ToolButton(basketball_icon, this);

        this->vBoxLayout->addWidget(this->button, 0, Qt::AlignHCenter);
        
        InfoBadge::success(new QVariant(QVariant::fromValue<int>(1)), this, this->button, InfoBadgePosition::TOP_RIGHT);
        

        this->resize(450, 400);
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