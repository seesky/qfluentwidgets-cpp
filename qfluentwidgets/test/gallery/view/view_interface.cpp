#include "view_interface.h"

ViewInterface::ViewInterface(QWidget *parent) : GalleryInterface(Translator(nullptr).view, "fluentwidgets.components.widgets", parent)
{
    this->setObjectName("viewInterface");

    this->addExampleCard(
        this->tr("A simple ListView"),
        new ListFrame(this),
        "http://www.github.com", 0
    );

    this->addExampleCard(
        this->tr("A simple TableView"),
        new TableFrame(this),
        "http://www.github.com", 0
    );

    TreeFrame *frame1 = new TreeFrame(this, false);
    this->addExampleCard(
        this->tr("A simple TreeView"),
        frame1,
        "http://www.github.com", 0
    );


    TreeFrame *frame2 = new TreeFrame(this, true);
    this->addExampleCard(
        this->tr("A TreeView with Multi-selection enabled"),
        frame2,
        "http://www.github.com", 0
    );

    HorizontalFlipView *flipView = new HorizontalFlipView(this);
    QList<QVariant *> flipImageList = QList<QVariant *>();
    flipImageList.append(new QVariant(QVariant::fromValue<QString>(QString("resource/shoko1.jpg"))));
    flipImageList.append(new QVariant(QVariant::fromValue<QString>(QString("resource/shoko2.jpg"))));
    flipImageList.append(new QVariant(QVariant::fromValue<QString>(QString("resource/shoko3.jpg"))));
    flipImageList.append(new QVariant(QVariant::fromValue<QString>(QString("resource/shoko4.jpg"))));
    flipView->addImages(flipImageList);

    this->addExampleCard(
        this->tr("Flip view"),
        flipView,
        "http://www.github.com", 0
    );
}




Frame::Frame(QWidget *parent) : QFrame(parent)
{
    this->hBoxLayout = new QHBoxLayout(this);
    this->hBoxLayout->setContentsMargins(0, 8, 0, 0);

    this->setObjectName("frame");
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("VIEW_INTERFACE"), Theme::AUTO);
}


void Frame::addWidget(QWidget *widget)
{
    this->hBoxLayout->addWidget(widget);
}


ListFrame::ListFrame(QWidget *parent) : Frame(parent)
{
    this->listWidget = new ListWidget(this);
    this->addWidget(this->listWidget);

    QStringList stands = {
        this->tr("Star Platinum"), this->tr("Hierophant Green"),
        this->tr("Made in Haven"), this->tr("King Crimson"),
        this->tr("Silver Chariot"), this->tr("Crazy diamond"),
        this->tr("Metallica"), this->tr("Another One Bites The Dust"),
        this->tr("Heaven's Door"), this->tr("Killer Queen"),
        this->tr("The Grateful Dead"), this->tr("Stone Free"),
        this->tr("The World"), this->tr("Sticky Fingers"),
        this->tr("Ozone Baby"), this->tr("Love Love Deluxe"),
        this->tr("Hermit Purple"), this->tr("Gold Experience"),
        this->tr("King Nothing"), this->tr("Paper Moon King"),
        this->tr("Scary Monster"), this->tr("Mandom"),
        this->tr("20th Century Boy"), this->tr("Tusk Act 4"),
        this->tr("Ball Breaker"), this->tr("Sex Pistols"),
        this->tr("D4C • Love Train"), this->tr("Born This Way"),
        this->tr("SOFT & WET"), this->tr("Paisley Park"),
        this->tr("Wonder of U"), this->tr("Walking Heart"),
        this->tr("Cream Starter"), this->tr("November Rain"),
        this->tr("Smooth Operators"), this->tr("The Matte Kudasai")
    };

    for(int i = 0; i < stands.size(); i++){
        this->listWidget->addItem(new QListWidgetItem(stands.at(i)));
    }

    this->setFixedSize(300, 380);
}



TreeFrame::TreeFrame(QWidget *parent, bool enableCheck = false) : Frame(parent)
{
    this->tree = new TreeWidget(this);
    this->addWidget(this->tree);

    QTreeWidgetItem *item1 = new QTreeWidgetItem({this->tr("JoJo 1 - Phantom Blood")});
    item1->addChildren({
        new QTreeWidgetItem({this->tr("Jonathan Joestar")}),
        new QTreeWidgetItem({this->tr("Dio Brando")}),
        new QTreeWidgetItem({this->tr("Will A. Zeppeli")})
    });

    this->tree->addTopLevelItem(item1);

    QTreeWidgetItem *item2 = new QTreeWidgetItem({this->tr("JoJo 3 - Stardust Crusaders")});
    QTreeWidgetItem *item21 = new QTreeWidgetItem({this->tr("Jotaro Kujo")});
    item21->addChildren({
        new QTreeWidgetItem({this->tr("空条承太郎")}),
        new QTreeWidgetItem({this->tr("空条蕉太狼")}),
        new QTreeWidgetItem({this->tr("阿强")}),
        new QTreeWidgetItem({this->tr("卖鱼强")}),
        new QTreeWidgetItem({this->tr("那个无敌的男人")}),
    });
    item2->addChild(item21);
    this->tree->addTopLevelItem(item2);
    this->tree->expandAll();
    this->tree->setHeaderHidden(true);

    this->setFixedSize(300, 380);

    if(enableCheck){
        QTreeWidgetItemIterator it(this->tree);
        while(*it){
            (*it)->setCheckState(0, Qt::Unchecked);
            ++it;
        }
    }
}


TableFrame::TableFrame(QWidget *parent) : TableWidget(parent)
{
    this->verticalHeader()->hide();
    this->setBorderRadius(8);
    this->setBorderVisible(true);

    this->setColumnCount(5);
    this->setRowCount(60);
    this->setHorizontalHeaderLabels({
        this->tr("Title"), this->tr("Artist"),
        this->tr("Album"), this->tr("Year"), this->tr("Duration")
    });

    QList<QStringList> songInfos = QList<QStringList>();
    songInfos.append(QStringList() << "かばん" << "aiko" << "かばん" << "2004" << "5:04");
    songInfos.append(QStringList() << "爱你" << "王心凌" << "爱你" << "2004" << "3:39");
    songInfos.append(QStringList() << "星のない世界" << "aiko" << "星のない世界/横顔" << "2007" << "5:30");
    songInfos.append(QStringList() << "横顔" << "aiko" << "星のない世界/横顔" << "2007" << "5:06");
    songInfos.append(QStringList() << "秘密" << "aiko" << "秘密" << "2008" << "5:25");
    songInfos.append(QStringList() << "二人" << "aiko" << "二人" << "2008" << "5:00");
    songInfos.append(QStringList() << "スパークル" << "RADWIMPS" << "君の名は" << "2016" << "8:54");
    songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
    songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
    songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
    songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
    songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
    songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
    songInfos.append(QStringList() << "かばん" << "aiko" << "かばん" << "2004" << "5:04");
    songInfos.append(QStringList() << "爱你" << "王心凌" << "爱你" << "2004" << "3:39");
    songInfos.append(QStringList() << "星のない世界" << "aiko" << "星のない世界/横顔" << "2007" << "5:30");
    songInfos.append(QStringList() << "横顔" << "aiko" << "星のない世界/横顔" << "2007" << "5:06");
    songInfos.append(QStringList() << "秘密" << "aiko" << "秘密" << "2008" << "5:25");
    songInfos.append(QStringList() << "二人" << "aiko" << "二人" << "2008" << "5:00");
    songInfos.append(QStringList() << "スパークル" << "RADWIMPS" << "君の名は" << "2016" << "8:54");
    songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
    songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
    songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
    songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
    songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
    songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
    songInfos.append(QStringList() << "かばん" << "aiko" << "かばん" << "2004" << "5:04");
    songInfos.append(QStringList() << "爱你" << "王心凌" << "爱你" << "2004" << "3:39");
    songInfos.append(QStringList() << "星のない世界" << "aiko" << "星のない世界/横顔" << "2007" << "5:30");
    songInfos.append(QStringList() << "横顔" << "aiko" << "星のない世界/横顔" << "2007" << "5:06");
    songInfos.append(QStringList() << "秘密" << "aiko" << "秘密" << "2008" << "5:25");
    songInfos.append(QStringList() << "二人" << "aiko" << "二人" << "2008" << "5:00");
    songInfos.append(QStringList() << "スパークル" << "RADWIMPS" << "君の名は" << "2016" << "8:54");
    songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
    songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
    songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
    songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
    songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
    songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
    songInfos.append(QStringList() << "かばん" << "aiko" << "かばん" << "2004" << "5:04");
    songInfos.append(QStringList() << "爱你" << "王心凌" << "爱你" << "2004" << "3:39");
    songInfos.append(QStringList() << "星のない世界" << "aiko" << "星のない世界/横顔" << "2007" << "5:30");
    songInfos.append(QStringList() << "横顔" << "aiko" << "星のない世界/横顔" << "2007" << "5:06");
    songInfos.append(QStringList() << "秘密" << "aiko" << "秘密" << "2008" << "5:25");
    songInfos.append(QStringList() << "二人" << "aiko" << "二人" << "2008" << "5:00");
    songInfos.append(QStringList() << "スパークル" << "RADWIMPS" << "君の名は" << "2016" << "8:54");
    songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
    songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
    songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
    songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
    songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
    songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
    songInfos.append(QStringList() << "かばん" << "aiko" << "かばん" << "2004" << "5:04");
    songInfos.append(QStringList() << "爱你" << "王心凌" << "爱你" << "2004" << "3:39");
    songInfos.append(QStringList() << "星のない世界" << "aiko" << "星のない世界/横顔" << "2007" << "5:30");
    songInfos.append(QStringList() << "横顔" << "aiko" << "星のない世界/横顔" << "2007" << "5:06");
    songInfos.append(QStringList() << "秘密" << "aiko" << "秘密" << "2008" << "5:25");
    songInfos.append(QStringList() << "二人" << "aiko" << "二人" << "2008" << "5:00");
    songInfos.append(QStringList() << "スパークル" << "RADWIMPS" << "君の名は" << "2016" << "8:54");
    songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
    songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
    songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
    songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
    songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
    songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
    songInfos.append(QStringList() << "かばん" << "aiko" << "かばん" << "2004" << "5:04");
    songInfos.append(QStringList() << "爱你" << "王心凌" << "爱你" << "2004" << "3:39");
    songInfos.append(QStringList() << "星のない世界" << "aiko" << "星のない世界/横顔" << "2007" << "5:30");
    songInfos.append(QStringList() << "横顔" << "aiko" << "星のない世界/横顔" << "2007" << "5:06");
    songInfos.append(QStringList() << "秘密" << "aiko" << "秘密" << "2008" << "5:25");
    songInfos.append(QStringList() << "二人" << "aiko" << "二人" << "2008" << "5:00");
    songInfos.append(QStringList() << "スパークル" << "RADWIMPS" << "君の名は" << "2016" << "8:54");
    songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "どうしたって伝えられないから" << "2016" << "3:16");
    songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
    songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
    songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
    songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");
    songInfos.append(QStringList() << "なんでもないや" << "RADWIMPS" << "君の名は" << "2016" << "3:16");

    songInfos += songInfos;

    for(int i = 0; i < songInfos.length(); i++){
        for(int n = 0; n < 5; n++){
            this->setItem(i, n, new QTableWidgetItem(songInfos.at(i).at(n)));
        }
    }

    this->setFixedSize(625, 440);
    this->resizeColumnsToContents();
}