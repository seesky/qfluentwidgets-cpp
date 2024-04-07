#include <QtCore/Qt>
#include <QtCore/QPoint>
#include <QtCore/QSize>
#include <QtCore/QUrl>
#include <QtCore/QRect>
#include <QtCore/QPropertyAnimation>
#include <QtGui/QIcon>
#include <QtGui/QFont>
#include <QtGui/QColor>
#include <QtGui/QPainter>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QGraphicsOpacityEffect>

#include "../components/widgets/card_widget.h"
#include "../components/widgets/icon_widget.h"
#include "../components/widgets/label.h"
#include "../components/widgets/button.h"
#include "../components/widgets/menu.h"
#include "../components/widgets/info_bar.h"
#include "../components/widgets/scroll_area.h"
#include "../components/widgets/separator.h"
#include "../components/widgets/arcylic_label.h"
#include "../components/widgets/flip_view.h"

#include "../components/navigation/navigation_panel.h"
#include "../components/layout/flow_layout.h"
#include "../window/fluent_window.h"

#include "../common/style_sheet.h"
#include "../common/config.h"
#include "../common/icon.h"
#include "../common/font.h"

#include "../qframelesswindow/utils/win32_utils.h"

class AppCard : public CardWidget{
public:
    AppCard(QVariant *icon, QString title, QString content, QWidget *parent) : CardWidget(parent){
        this->iconWidget = new IconWidget(icon, this);
        this->titleLabel = new BodyLabel(title, this);
        this->contentLabel = new CaptionLabel(content, this);
        this->openButton = new PushButton(QString("打开"), this, nullptr);

        FluentIcon *moreIcon = new FluentIcon();
        moreIcon->setIconName(QString("MORE"));
        this->moreButton = new TransparentToolButton(moreIcon, this);

        this->hBoxLayout = new QHBoxLayout(this);
        this->vBoxLayout = new QVBoxLayout();

        this->setFixedHeight(73);
        this->iconWidget->setFixedSize(48, 48);
        this->contentLabel->setTextColor(QColor("#606060"), QString("#d2d2d2"));
        this->openButton->setFixedWidth(120);

        this->hBoxLayout->setContentsMargins(20, 11, 11, 11);
        this->hBoxLayout->setSpacing(15);
        this->hBoxLayout->addWidget(this->iconWidget);

        this->vBoxLayout->setContentsMargins(0, 0, 0, 0);
        this->vBoxLayout->setSpacing(0);
        this->vBoxLayout->addWidget(this->titleLabel, 0, Qt::AlignVCenter);
        this->vBoxLayout->addWidget(this->contentLabel, 0, Qt::AlignVCenter);
        this->vBoxLayout->setAlignment(Qt::AlignVCenter);
        this->hBoxLayout->addLayout(this->vBoxLayout);

        this->hBoxLayout->addStretch(1);
        this->hBoxLayout->addWidget(this->openButton, 0, Qt::AlignRight);
        this->hBoxLayout->addWidget(this->moreButton, 0, Qt::AlignRight);

        this->moreButton->setFixedSize(32, 32);
        connect(this->moreButton, &TransparentToolButton::clicked, this, &AppCard::onMoreButtonClicked);
    }
    void onMoreButtonClicked(){
        RoundMenu *menu = new RoundMenu(QString(), this);
        
        FluentIcon *shareIcon = new FluentIcon();
        shareIcon->setIconName("SHARE");
        Action *shareAction = new Action(shareIcon, QString("共享"), this);
        menu->addAction(shareAction);

        FluentIcon *chatIcon = new FluentIcon();
        chatIcon->setIconName("CHAT");
        Action *chatAction = new Action(chatIcon, QString("写评论"), this);
        menu->addAction(chatAction);

        FluentIcon *pinIcon = new FluentIcon();
        pinIcon->setIconName("PIN");
        Action *pinAction = new Action(pinIcon, QString("固定到任务栏"), this);
        menu->addAction(pinAction);  

        int x = (this->moreButton->width() - menu->width()) / 2 + 10;
        QPoint pos = this->moreButton->mapToGlobal(QPoint(x, this->moreButton->height()));
        menu->exec(&pos, true, MenuAnimationType::DROP_DOWN);
    }

    IconWidget *iconWidget;
    BodyLabel *titleLabel;
    CaptionLabel *contentLabel;
    PushButton *openButton;
    TransparentToolButton *moreButton;

    QHBoxLayout *hBoxLayout;
    QVBoxLayout *vBoxLayout;
};



class EmojiCard : public ElevatedCardWidget{
public:
    EmojiCard(QString iconPath, QWidget *parent) : ElevatedCardWidget(parent){
        this->iconWidget = new ImageLabel(iconPath, this);
        QFileInfo fileInfo(iconPath);
        this->label = new CaptionLabel(fileInfo.baseName(), this);

        this->iconWidget->scaledToHeight(68);

        this->vBoxLayout = new QVBoxLayout(this);
        this->vBoxLayout->setAlignment(Qt::AlignCenter);
        this->vBoxLayout->addStretch(1);
        this->vBoxLayout->addWidget(this->iconWidget, 0, Qt::AlignCenter);
        this->vBoxLayout->addStretch(1);
        this->vBoxLayout->addWidget(this->label, 0, Qt::AlignHCenter | Qt::AlignBottom);

        this->setFixedSize(168, 176);
    }

    ImageLabel *iconWidget;
    CaptionLabel *label;
    QVBoxLayout *vBoxLayout;
};


class StatisticsWidget : public QWidget{
public:
    StatisticsWidget(QString title, QString value, QWidget *parent) : QWidget(parent){
        this->titleLabel = new CaptionLabel(title, this);
        this->valueLabel = new BodyLabel(value, this);
        this->vBoxLayout = new QVBoxLayout(this);

        this->vBoxLayout->setContentsMargins(16, 0, 16, 0);
        this->vBoxLayout->addWidget(this->valueLabel, 0, Qt::AlignTop);
        this->vBoxLayout->addWidget(this->titleLabel, 0, Qt::AlignBottom);

        Font().setFont(this->valueLabel, 18, QFont::DemiBold);
        this->titleLabel->setTextColor(QColor(96, 96, 96), QColor(206, 206, 206));
    }

    CaptionLabel *titleLabel;
    BodyLabel *valueLabel;
    QVBoxLayout *vBoxLayout;
};


class AppInfoCard : public SimpleCardWidget{
public:
    AppInfoCard(QWidget *parent) : SimpleCardWidget(parent){
        this->iconLabel = new ImageLabel(QString("qfluentwidgets/images/logo.png"), this);
        this->iconLabel->setBorderRadius(8, 8, 8, 8);
        this->iconLabel->scaledToWidth(120);

        this->nameLabel = new TitleLabel(QString("QFluentWidgets"), this);
        this->installButton = new PrimaryPushButton(QString("安装"), this, nullptr);
        this->companyLabel = new HyperlinkLabel(QUrl("https://github.com"), QString("GitHub"), this);
        this->installButton->setFixedWidth(160);

        this->scoreWidget = new StatisticsWidget(QString("平均"), QString("5.0"), this);
        this->separator = new VerticalSeparator(this);
        this->commentWidget = new StatisticsWidget(QString("评论数"), QString("3K"), this);

        this->descriptionLabel = new BodyLabel(QString("Fluent-Widgets 是一个基于 Qt 的 Fluent Design 风格组件库，包含许多美观实用的组件，支持亮暗主题无缝切换和自定义主题色，帮助开发者快速实现美观优雅的现代化界面。"), this);
        this->descriptionLabel->setWordWrap(true);

        this->tagButton = new PillPushButton(QString("组件库"), this, nullptr);
        this->tagButton->setCheckable(false);
        Font().setFont(this->tagButton, 12, QFont::Normal);
        this->tagButton->setFixedSize(80, 32);

        FluentIcon *shareIcon = new FluentIcon();
        shareIcon->setIconName("SHARE");
        this->shareButton = new TransparentToolButton(shareIcon, this);
        this->shareButton->setFixedSize(32, 32);
        this->shareButton->setIconSize(QSize(14, 14));

        this->hBoxLayout = new QHBoxLayout(this);
        this->vBoxLayout = new QVBoxLayout();
        this->topLayout = new QHBoxLayout();
        this->statisticsLayout = new QHBoxLayout();
        this->buttonLayout = new QHBoxLayout();

        this->initLayout();
    }
    void initLayout(){
        this->hBoxLayout->setSpacing(30);
        this->hBoxLayout->setContentsMargins(34, 24, 24, 24);
        this->hBoxLayout->addWidget(this->iconLabel);
        this->hBoxLayout->addLayout(this->vBoxLayout);

        this->vBoxLayout->setContentsMargins(0, 0, 0, 0);
        this->vBoxLayout->setSpacing(0);

        this->vBoxLayout->addLayout(this->topLayout);
        this->topLayout->setContentsMargins(0, 0, 0, 0);
        this->topLayout->addWidget(this->nameLabel);
        this->topLayout->addWidget(this->installButton, 0, Qt::AlignRight);

        this->vBoxLayout->addSpacing(3);
        this->vBoxLayout->addWidget(this->companyLabel);

        this->vBoxLayout->addSpacing(20);
        this->vBoxLayout->addLayout(this->statisticsLayout);
        this->statisticsLayout->setSpacing(10);
        this->statisticsLayout->addWidget(this->scoreWidget);
        this->statisticsLayout->addWidget(this->separator);
        this->statisticsLayout->addWidget(this->commentWidget);
        this->statisticsLayout->setAlignment(Qt::AlignLeft);

        this->vBoxLayout->addSpacing(20);
        this->vBoxLayout->addWidget(this->descriptionLabel);

        this->vBoxLayout->addSpacing(12);
        this->buttonLayout->setContentsMargins(0, 0, 0, 0);
        this->vBoxLayout->addLayout(this->buttonLayout);
        this->buttonLayout->addWidget(this->tagButton, 0, Qt::AlignLeft);
        this->buttonLayout->addWidget(this->shareButton, 0, Qt::AlignRight);
    }

    ImageLabel *iconLabel;
    TitleLabel *nameLabel;
    PrimaryPushButton *installButton;
    HyperlinkLabel *companyLabel;
    StatisticsWidget *scoreWidget;
    VerticalSeparator *separator;
    StatisticsWidget *commentWidget;
    BodyLabel *descriptionLabel;
    PillPushButton *tagButton;
    TransparentToolButton *shareButton;
    QHBoxLayout *hBoxLayout;
    QVBoxLayout *vBoxLayout;
    QHBoxLayout *topLayout;
    QHBoxLayout *statisticsLayout;
    QHBoxLayout *buttonLayout;
};


class GalleryCard : public HeaderCardWidget{
public:
    GalleryCard(QWidget *parent) : HeaderCardWidget(parent){

        this->setTitle(QString("屏幕截图"));

        this->flipView = new HorizontalFlipView(this);

        FluentIcon *expandButtonIcon = new FluentIcon();
        expandButtonIcon->setIconName("CHEVRON_RIGHT_MED");
        this->expandButton = new TransparentToolButton(expandButtonIcon, this);

        this->expandButton->setFixedSize(32, 32);
        this->expandButton->setIconSize(QSize(12, 12));

        QList<QVariant *> flipImageList = QList<QVariant *>();
        flipImageList.append(new QVariant(QVariant::fromValue<QString>(QString("resource/shoko1.jpg"))));
        flipImageList.append(new QVariant(QVariant::fromValue<QString>(QString("resource/shoko2.jpg"))));
        flipImageList.append(new QVariant(QVariant::fromValue<QString>(QString("resource/shoko3.jpg"))));
        flipImageList.append(new QVariant(QVariant::fromValue<QString>(QString("resource/shoko4.jpg"))));

        this->flipView->addImages(flipImageList);

        this->flipView->setBorderRadius(8);
        this->flipView->setSpacing(10);

        this->headerLayout->addWidget(this->expandButton, 0, Qt::AlignRight);
        this->viewLayout->addWidget(this->flipView);
    }

    HorizontalFlipView *flipView;
    TransparentToolButton *expandButton;
};


class DescriptionCard : public HeaderCardWidget{
public:
    DescriptionCard(QWidget *parent) : HeaderCardWidget(parent){
        this->descriptionLabel = new BodyLabel(QString("Fluent-Widgets 是一个基于 Qt 的 Fluent Design 风格组件库，包含许多美观实用的组件，支持亮暗主题无缝切换和自定义主题色，帮助开发者快速实现美观优雅的现代化界面。"), this);
        this->descriptionLabel->setWordWrap(true);
        this->viewLayout->addWidget(this->descriptionLabel);
        this->setTitle(QString("描述"));
    }

    BodyLabel *descriptionLabel;
};


class SystemRequirementCard : public HeaderCardWidget{
public:
    SystemRequirementCard(QWidget *parent) : HeaderCardWidget(parent){
        this->setTitle(QString("系统要求"));
        this->infoLabel = new BodyLabel(QString("此产品适用于你的设备。具有复选标记的项目符合开发人员的系统要求。"), this);

        InfoBarIcon *infoBarIcon = new InfoBarIcon();
        infoBarIcon->setIconName("SUCCESS");
        this->successIcon = new IconWidget(infoBarIcon, this);
        this->detailButton = new HyperlinkLabel(QString("详细信息"), this);

        this->vBoxLayout = new QVBoxLayout();
        this->hBoxLayout = new QHBoxLayout();

        this->successIcon->setFixedSize(16, 16);
        this->hBoxLayout->setSpacing(10);
        this->vBoxLayout->setSpacing(16);
        this->hBoxLayout->setContentsMargins(0, 0, 0, 0);
        this->vBoxLayout->setContentsMargins(0, 0, 0, 0);

        this->hBoxLayout->addWidget(this->successIcon);
        this->hBoxLayout->addWidget(this->infoLabel);
        this->vBoxLayout->addLayout(this->hBoxLayout);
        this->vBoxLayout->addWidget(this->detailButton);

        this->viewLayout->addLayout(this->vBoxLayout);

    }

    BodyLabel *infoLabel;
    IconWidget *successIcon;
    HyperlinkLabel *detailButton;
    QVBoxLayout *vBoxLayout;
    QHBoxLayout *hBoxLayout;
};



class LightBox : public QWidget{
public:
    LightBox(QWidget *parent) : QWidget(parent){
        if(isDarkTheme()){
            tintColor = QColor(32, 32, 32, 200);
        }else{
            tintColor = QColor(255, 255, 255, 160);
        }

        this->acrylicBrush = new AcrylicBrush(this, 30, tintColor, QColor(0, 0, 0, 0), 0.03);

        this->opacityEffect = new QGraphicsOpacityEffect(this);
        this->opacityAni = new QPropertyAnimation(this->opacityEffect, "opacity", this);
        this->opacityEffect->setOpacity(1);
        this->setGraphicsEffect(this->opacityEffect);

        this->vBoxLayout = new QVBoxLayout(this);

        FluentIcon *closeIcon = new FluentIcon();
        closeIcon->setIconName("CLOSE");
        this->closeButton = new TransparentToolButton(closeIcon, this);
        this->flipView = new HorizontalFlipView(this);
        this->nameLabel = new BodyLabel(QString("屏幕截图1"), this);
        this->pageNumButton = new PillPushButton(QString("1 / 4"), this, nullptr);

        this->pageNumButton->setCheckable(false);
        this->pageNumButton->setFixedSize(80, 32);
        Font().setFont(this->nameLabel, 16, QFont::DemiBold);

        this->closeButton->setFixedSize(32, 32);
        this->closeButton->setIconSize(QSize(14, 14));
        connect(this->closeButton, &TransparentToolButton::clicked, this, &LightBox::fadeOut);

        this->vBoxLayout->setContentsMargins(26, 28, 26, 28);
        this->vBoxLayout->addWidget(this->closeButton, 0, Qt::AlignRight | Qt::AlignTop);
        this->vBoxLayout->addWidget(this->flipView, 1);
        this->vBoxLayout->addWidget(this->nameLabel, 0, Qt::AlignHCenter);
        this->vBoxLayout->addSpacing(10);
        this->vBoxLayout->addWidget(this->pageNumButton, 0, Qt::AlignHCenter);

        QList<QVariant *> flipImageList = QList<QVariant *>();
        flipImageList.append(new QVariant(QVariant::fromValue<QString>(QString("resource/shoko1.jpg"))));
        flipImageList.append(new QVariant(QVariant::fromValue<QString>(QString("resource/shoko2.jpg"))));
        flipImageList.append(new QVariant(QVariant::fromValue<QString>(QString("resource/shoko3.jpg"))));
        flipImageList.append(new QVariant(QVariant::fromValue<QString>(QString("resource/shoko4.jpg"))));

        this->flipView->addImages(flipImageList);

        connect(this->flipView, &HorizontalFlipView::currentIndexChanged, this, &LightBox::setCurrentIndex);
    };

    void setCurrentIndex(int index){
        this->nameLabel->setText(QString("屏幕截图%1").arg(index + 1));
        this->pageNumButton->setText(QString("%1/%2").arg(index + 1).arg(this->flipView->count()));
        this->flipView->setCurrentIndex(index);
    }

    void paintEvent(QPaintEvent *event) override{
        if(this->acrylicBrush->isAvailable()){
            return this->acrylicBrush->paint();
        }

        QPainter painter(this);
        painter.setPen(Qt::NoPen);
        if(isDarkTheme()){
            painter.setBrush(QColor(32, 32, 32));
        }else{
            painter.setBrush(QColor(255, 255, 255));
        }

        painter.drawRect(this->rect());
    }

    void resizeEvent(QResizeEvent *event) override{
        int w = this->width() - 52;
        this->flipView->setItemSize(QSize(w, w * 9 / 16));
    }


    void fadeIn(){
        QRect rect = QRect(this->mapToGlobal(QPoint()), this->size());
        this->acrylicBrush->grabImage(rect);

        this->opacityAni->setStartValue(0);
        this->opacityAni->setEndValue(1);
        this->opacityAni->setDuration(150);
        this->opacityAni->start();
        this->show();
    }

    void fadeOut(){
        this->opacityAni->setStartValue(1);
        this->opacityAni->setEndValue(0);
        this->opacityAni->setDuration(150);
        connect(this->opacityAni, &QPropertyAnimation::finished, this, &LightBox::_onAniFinished);
        this->opacityAni->start();
    }

    void _onAniFinished(){
        disconnect(this->opacityAni, &QPropertyAnimation::finished, this, &LightBox::_onAniFinished);
        this->hide();
    }

    QColor tintColor;
    AcrylicBrush *acrylicBrush;
    QGraphicsOpacityEffect *opacityEffect;
    QPropertyAnimation *opacityAni;
    QVBoxLayout *vBoxLayout;
    TransparentToolButton *closeButton;
    HorizontalFlipView *flipView;
    BodyLabel *nameLabel;
    PillPushButton *pageNumButton;
};


class MicaWindow : public WindowsFramelessWindow{
public:
    MicaWindow(QWidget *parent) : WindowsFramelessWindow(parent){
        this->setTitleBar(new MSFluentTitleBar(this));
        if(isGreaterEqualWin11()){
            this->windowEffect->setMicaEffect((HWND)this->winId(), isDarkTheme(), false);
        }
    }
};



class Demo1 : public MicaWindow{
public:
    Demo1(QWidget *parent) : MicaWindow(parent){
        this->setWindowIcon(QIcon("qfluentwidgets/images/logo.png"));
        this->setWindowTitle(QString("Fluent Emoji gallery"));

        this->flowLayout = new FlowLayout(this, false, false);

        this->resize(580, 680);
        this->flowLayout->setSpacing(6);
        this->flowLayout->setContentsMargins(30, 60, 30, 30);
        this->flowLayout->setAlignment(Qt::AlignVCenter);

        QDir directory("./resource/card_widget");
        QStringList pngFiles = directory.entryList(QStringList() << "*.png", QDir::Files);


        
        foreach(QString filename, pngFiles) {
            QString filePath = directory.filePath(filename);
            //qDebug() << filePath.remove(0, 2);
            addCard(filePath.remove(0, 2)); // 假设addCard接受QString作为参数
        }
        
        
    }

    void addCard(QString iconPath){
        EmojiCard *card = new EmojiCard(iconPath, this);
        this->flowLayout->addWidget(card);
    }

    FlowLayout *flowLayout;
};


class Demo2 : public MicaWindow{
public:
    Demo2(QWidget *parent) : MicaWindow(parent){
        this->resize(600, 600);

        this->vBoxLayout = new QVBoxLayout(this);

        this->vBoxLayout->setSpacing(6);
        this->vBoxLayout->setContentsMargins(30, 60, 30, 30);
        this->vBoxLayout->setAlignment(Qt::AlignTop);

        QString suffix = QString("qfluentwidgets/images/controls%1");
        this->addCard(new QVariant(QVariant::fromValue<QString>(QString("qfluentwidgets/images/logo.png"))), QString("Fluent-Widgets"), QString("Shokokawaii Inc."));
        this->addCard(new QVariant(QVariant::fromValue<QString>(suffix.arg("/TitleBar.png"))), QString("Frameless-Window"), QString("Shokokawaii Inc."));
        this->addCard(new QVariant(QVariant::fromValue<QString>(suffix.arg("/RatingControl.png"))), QString("反馈中心"), QString("Microsoft Corporation"));
        this->addCard(new QVariant(QVariant::fromValue<QString>(suffix.arg("/Checkbox.png"))), QString("Microsoft 使用技巧"), QString("Microsoft Corporation"));
        this->addCard(new QVariant(QVariant::fromValue<QString>(suffix.arg("/Pivot.png"))), QString("MSN 天气"), QString("Microsoft Corporation"));
        this->addCard(new QVariant(QVariant::fromValue<QString>(suffix.arg("/MediaPlayerElement.png"))), QString("电影和电视"), QString("Microsoft Corporation"));
        this->addCard(new QVariant(QVariant::fromValue<QString>(suffix.arg("/PersonPicture.png"))), QString("照片"), QString("Microsoft Corporation"));
    }

    void addCard(QVariant *icon, QString title, QString content){
        AppCard *card = new AppCard(icon, title, content, this);
        this->vBoxLayout->addWidget(card, 0, Qt::AlignTop);
    }

    QVBoxLayout *vBoxLayout;

};


class AppInterface : public SingleDirectionScrollArea{
public:
    AppInterface(QWidget *parent) : SingleDirectionScrollArea(parent, Qt::Vertical){
        this->view = new QWidget(this);
        this->vBoxLayout = new QVBoxLayout(this->view);
        this->appCard = new AppInfoCard(this);
        this->galleryCard = new GalleryCard(this);
        this->descriptionCard = new DescriptionCard(this);
        this->systemCard = new SystemRequirementCard(this);

        this->lightBox = new LightBox(this);
        this->lightBox->hide();
        connect(this->galleryCard->flipView, &HorizontalFlipView::itemClicked, this, &AppInterface::showLightBox);

        this->setWidget(this->view);
        this->setWidgetResizable(true);
        this->setObjectName("appInterface");

        this->vBoxLayout->setSpacing(10);
        this->vBoxLayout->setContentsMargins(0, 0, 10, 30);
        this->vBoxLayout->addWidget(this->appCard, 0, Qt::AlignTop);
        this->vBoxLayout->addWidget(this->galleryCard, 0, Qt::AlignTop);
        this->vBoxLayout->addWidget(this->descriptionCard, 0, Qt::AlignTop);
        this->vBoxLayout->addWidget(this->systemCard, 0, Qt::AlignTop);

        this->setStyleSheet(QString("QScrollArea {border: none; background:transparent}"));
        this->view->setStyleSheet(QString("QWidget {background:transparent}"));
    }

    void showLightBox(){
        int index = this->galleryCard->flipView->currentIndex();
        this->lightBox->setCurrentIndex(index);
        this->lightBox->fadeIn();
    }

    void resizeEvent(QResizeEvent *event) override{
        SingleDirectionScrollArea::resizeEvent(event);
        this->lightBox->resize(this->size());
    }



    QWidget *view;
    QVBoxLayout *vBoxLayout;
    AppInfoCard *appCard;
    GalleryCard *galleryCard;
    DescriptionCard *descriptionCard;
    SystemRequirementCard *systemCard;
    LightBox *lightBox;
};


class Demo3 : public MSFluentWindow{
public:
    Demo3(QWidget *parent) : MSFluentWindow(parent){
        this->appInterface = new AppInterface(this);

        FluentIcon *libraryIcon = new FluentIcon();
        libraryIcon->setIconName(QString("LIBRARY"));
        FluentIcon *libraryFillIcon = new FluentIcon();
        libraryFillIcon->setIconName(QString("LIBRARY_FILL"));
        this->addSubInterface(this->appInterface, new QVariant(QVariant::fromValue<FluentIcon>(*libraryIcon)), QString("库"), new QVariant(QVariant::fromValue<FluentIcon>(*libraryFillIcon)), NavigationItemPosition::TOP, true);
        
        FluentIcon *editIcon = new FluentIcon();
        editIcon->setIconName(QString("EDIT"));
        this->navigationInterface->addItem(QString("editInterface"), new QVariant(QVariant::fromValue<FluentIcon>(*editIcon)), QString("编辑"), nullptr, false, new QVariant(), NavigationItemPosition::TOP);
        FluentIcon *settingIcon = new FluentIcon();
        settingIcon->setIconName(QString("SETTING"));
        this->navigationInterface->addItem(QString("settingInterface"), new QVariant(QVariant::fromValue<FluentIcon>(*settingIcon)), QString("设置"), nullptr, false, new QVariant(), NavigationItemPosition::BOTTOM);

        this->resize(880, 760);
        this->setWindowTitle(QString("Fluent Widgets"));
        this->setWindowIcon(QIcon("qfluentwidgets/images/logo.png"));
        this->titleBar->raise();

    }

    AppInterface *appInterface;

};



int main(int argc, char *argv[])
{
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    
    QApplication *app = new QApplication(argc, argv);
    Demo1 *w = new Demo1(nullptr);
    w->show();

    Demo2 *w2 = new Demo2(nullptr);
    w2->show();

    Demo3 *w3 = new Demo3(nullptr);
    w3->show();
    return app->exec();
}