#include "menu_interface.h"

MenuInterface::MenuInterface(QWidget *parent) : GalleryInterface(Translator(nullptr).menus, "fluentwidgets.components.widgets", parent)
{
    this->setObjectName("menuInterface");

    
    this->button1 = new PushButton(this->tr("Show menu"), nullptr, nullptr);
    connect(this->button1, &PushButton::clicked, this, [this](){
        this->createMenu(this->button1->mapToGlobal(QPoint(this->button1->width() + 5, -100)));
    });

    this->addExampleCard(
        this->tr("Rounded corners menu"),
        this->button1,
        "http://www.github.com", 0
    );

    this->button3 = new PushButton(this->tr("Show menu"), nullptr, nullptr);
    connect(this->button3, &PushButton::clicked, this, [this](){
        this->createCustomWidgetMenu(this->button3->mapToGlobal(QPoint(this->button3->width() + 5, -100)));
    });

    this->addExampleCard(
        this->tr("Rounded corners menu with custom widget"),
        this->button3,
        "http://www.github.com", 0
    );

    

    this->button2 = new PushButton(this->tr("Show menu"), nullptr, nullptr);
    connect(this->button2, &PushButton::clicked, this, [this](){
        this->createCheckableMenu(this->button2->mapToGlobal(QPoint(this->button2->width() + 5, -100)));
    });

    
    this->addExampleCard(
        this->tr("Checkable menu"),
        this->button2,
        "http://www.github.com", 0
    );

    

    this->addExampleCard(
        this->tr("Command bar"),
        this->createCommandBar(),
        "http://www.github.com", 1
    );

    QWidget *widget = new QWidget(this);
    widget->setLayout(new QVBoxLayout());
    widget->layout()->setContentsMargins(0, 0, 0, 0);
    widget->layout()->setSpacing(10);

    QLabel *label = new QLabel(this->tr("Click the image to open a command bar flyout 👇️🥵"));
    this->imageLabel = new ImageLabel("qfluentwidgets/images/chidanta5.jpg", nullptr);
    this->imageLabel->scaledToWidth(350);
    this->imageLabel->setBorderRadius(8, 8, 8, 8);
    connect(this->imageLabel, &ImageLabel::clicked, this, &MenuInterface::createCommandBarFlyout);

    widget->layout()->addWidget(label);
    widget->layout()->addWidget(this->imageLabel);

    this->addExampleCard(
        this->tr("Command bar flyout"),
        widget,
        "http://www.github.com", 1
    );
    
}


void MenuInterface::createMenu(QPoint pos)
{
    RoundMenu *menu = new RoundMenu("", this);

    FluentIcon *copyIcon = new FluentIcon();
    copyIcon->setIconName(QString("COPY"));
    FluentIcon *cutIcon = new FluentIcon();
    cutIcon->setIconName(QString("CUT"));
    FluentIcon *addIcon = new FluentIcon();
    addIcon->setIconName(QString("ADD"));
    FluentIcon *videoIcon = new FluentIcon();
    videoIcon->setIconName(QString("VIDEO"));
    FluentIcon *musicIcon = new FluentIcon();
    musicIcon->setIconName(QString("MUSIC"));
    FluentIcon *pasteIcon = new FluentIcon();
    pasteIcon->setIconName(QString("PASTE"));
    FluentIcon *cancelIcon = new FluentIcon();
    cancelIcon->setIconName(QString("CANCEL"));
    FluentIcon *settingIcon = new FluentIcon();
    settingIcon->setIconName(QString("SETTING"));
    FluentIcon *helpIcon = new FluentIcon();
    helpIcon->setIconName(QString("HELP"));
    FluentIcon *feedbackIcon = new FluentIcon();
    feedbackIcon->setIconName(QString("FEEDBACK"));


    menu->addAction(new Action(copyIcon, this->tr("Copy"), nullptr));
    menu->addAction(new Action(cutIcon, this->tr("Cut"), nullptr));

    RoundMenu *subemnu = new RoundMenu(this->tr("Add to"), this);
    subemnu->setIcon(new QVariant(QVariant::fromValue<FluentIcon>(*addIcon)));
    subemnu->addAction(new Action(videoIcon, this->tr("Video"), nullptr));
    subemnu->addAction(new Action(musicIcon, this->tr("Music"), nullptr));
    menu->addMenu(subemnu);

    menu->addAction(new Action(pasteIcon, this->tr("Paste"), nullptr));
    menu->addAction(new Action(cancelIcon, this->tr("Undo"), nullptr));

    menu->addSeparator();
    menu->addAction(new Action(this->tr("Select all"), nullptr));

    menu->insertAction(
        menu->actions().at(menu->actions().size() - 1), new Action(settingIcon, this->tr("Settings"), nullptr)
    );
    menu->insertAction(
        menu->actions().at(menu->actions().size() - 1), new Action(helpIcon, this->tr("Help"), nullptr)
    );
    menu->insertAction(
        menu->actions().at(menu->actions().size() - 1), new Action(feedbackIcon, this->tr("Feedback"), nullptr)
    );

    menu->exec(&pos, true, MenuAnimationType::DROP_DOWN);
}


void MenuInterface::createCustomWidgetMenu(QPoint pos)
{
    RoundMenu *menu = new RoundMenu("", this);
    
    ProfileCard *card = new ProfileCard("qfluentwidgets/images/shoko.png", this->tr("Shoko"), "baxuelong@163.com", menu);
    menu->addWidget(card, false, nullptr);

    menu->addSeparator();
    
    FluentIcon *peopleIcon = new FluentIcon();
    peopleIcon->setIconName(QString("PEOPLE"));
    FluentIcon *shoppintIcon = new FluentIcon();
    shoppintIcon->setIconName(QString("SHOPPING_CART"));
    FluentIcon *codeIcon = new FluentIcon();
    codeIcon->setIconName(QString("CODE"));
    FluentIcon *settingIcon = new FluentIcon();
    settingIcon->setIconName(QString("SETTING"));

    

    menu->addAction(new Action(peopleIcon, this->tr("Manage account profile"), nullptr));
    menu->addAction(new Action(shoppintIcon, this->tr("Payment method"), nullptr));
    menu->addAction(new Action(codeIcon, this->tr("Redemption code and gift card"), nullptr));

    menu->addSeparator();
    menu->addAction(new Action(settingIcon, this->tr("Settings"), nullptr));
    menu->exec(&pos, true, MenuAnimationType::DROP_DOWN);
}


CheckableMenu *MenuInterface::createCheckableMenu(QPoint pos)
{
    CheckableMenu *menu = new CheckableMenu("", this, MenuIndicatorType::CHECK);


    FluentIcon *calendarIcon = new FluentIcon();
    calendarIcon->setIconName(QString("CALENDAR"));
    FluentIcon *cameraIcon = new FluentIcon();
    cameraIcon->setIconName(QString("CAMERA"));
    FluentIcon *editIcon = new FluentIcon();
    editIcon->setIconName(QString("EDIT"));
    FluentIcon *fontIcon = new FluentIcon();
    fontIcon->setIconName(QString("FONT"));
    FluentIcon *upIcon = new FluentIcon();
    upIcon->setIconName(QString("UP"));
    FluentIcon *downIcon = new FluentIcon();
    downIcon->setIconName(QString("DOWN"));


    Action *createTimeAction;
    Action *shootTimeAction;
    Action *modifiedTimeAction;
    Action *nameAction;
    QActionGroup *actionGroup1;

    createTimeAction = new Action(calendarIcon, this->tr("Create Date"), nullptr);
    createTimeAction->setCheckable(true);
    shootTimeAction = new Action(cameraIcon, this->tr("Shooting Date"), nullptr);
    shootTimeAction->setCheckable(true);
    modifiedTimeAction = new Action(editIcon, this->tr("Modified time"), nullptr);
    modifiedTimeAction->setCheckable(true);
    nameAction = new Action(fontIcon, this->tr("Name"), nullptr);
    nameAction->setCheckable(true);
    actionGroup1 = new QActionGroup(this);
    actionGroup1->addAction(createTimeAction);
    actionGroup1->addAction(shootTimeAction);
    actionGroup1->addAction(modifiedTimeAction);
    actionGroup1->addAction(nameAction);

    shootTimeAction->setChecked(true);
    

    menu->addAction(createTimeAction);
    menu->addAction(shootTimeAction);
    menu->addAction(modifiedTimeAction);
    menu->addAction(nameAction);

    menu->addSeparator();


    Action *ascendAction;
    Action *descendAction;
    QActionGroup *actionGroup2;

    ascendAction = new Action(upIcon, this->tr("Ascending"), nullptr);
    ascendAction->setCheckable(true);
    descendAction = new Action(downIcon, this->tr("Descending"), nullptr);
    descendAction->setCheckable(true);
    actionGroup2 = new QActionGroup(this);
    actionGroup2->addAction(ascendAction);
    actionGroup2->addAction(descendAction);

    ascendAction->setChecked(true);

    menu->addAction(ascendAction);
    menu->addAction(descendAction);

    if(!pos.isNull()){
        menu->exec(&pos, true, MenuAnimationType::DROP_DOWN);
    }

    return menu;
}


CommandBar *MenuInterface::createCommandBar()
{
    CommandBar *bar = new CommandBar(this);
    bar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    FluentIcon *addIcon = new FluentIcon();
    addIcon->setIconName(QString("ADD"));
    FluentIcon *editIcon = new FluentIcon();
    editIcon->setIconName(QString("EDIT"));
    FluentIcon *rotateIcon = new FluentIcon();
    rotateIcon->setIconName(QString("ROTATE"));
    FluentIcon *zoomInIcon = new FluentIcon();
    zoomInIcon->setIconName(QString("ZOOM_IN"));
    FluentIcon *zoomOutIcon = new FluentIcon();
    zoomOutIcon->setIconName(QString("ZOOM_OUT"));
    FluentIcon *infoIcon = new FluentIcon();
    infoIcon->setIconName(QString("INFO"));
    FluentIcon *deleteIcon = new FluentIcon();
    deleteIcon->setIconName(QString("DELETE"));
    FluentIcon *shareIcon = new FluentIcon();
    shareIcon->setIconName(QString("SHARE"));
    FluentIcon *scrollIcon = new FluentIcon();
    scrollIcon->setIconName(QString("SCROLL"));
    FluentIcon *settingIcon = new FluentIcon();
    settingIcon->setIconName(QString("SETTING"));

    bar->addAction(new Action(addIcon, this->tr("Add"), nullptr));
    bar->addAction(new Action(rotateIcon, this->tr("Rotate"), nullptr));
    bar->addAction(new Action(zoomInIcon, this->tr("Zoom in"), nullptr));
    bar->addAction(new Action(zoomOutIcon, this->tr("Zoom out"), nullptr));

    bar->addSeparator();
    Action *editAciton = new Action(editIcon, this->tr("Edit"), nullptr);
    editAciton->setCheckable(true);
    bar->addAction(editAciton);
    bar->addAction(new Action(infoIcon, this->tr("Info"), nullptr));
    bar->addAction(new Action(deleteIcon, this->tr("Delete"), nullptr));
    bar->addAction(new Action(shareIcon, this->tr("Share"), nullptr));

    TransparentDropDownPushButton *button = new TransparentDropDownPushButton(scrollIcon, this->tr("Sort"), this);
    button->setMenu(this->createCheckableMenu(QPoint()));
    button->setFixedHeight(34);
    Font().setFont(button, 12, QFont::Normal);
    bar->addWidget(button);

    Action *settingAction = new Action(settingIcon, this->tr("Settings"), nullptr);
    settingAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_I));
    bar->addHiddenAction(settingAction);
    return bar;
}


void MenuInterface::createCommandBarFlyout()
{
    CommandBarView *view = new CommandBarView(this);

    FluentIcon *shareIcon = new FluentIcon();
    shareIcon->setIconName(QString("SHARE"));
    FluentIcon *deleteIcon = new FluentIcon();
    deleteIcon->setIconName(QString("DELETE"));
    FluentIcon *settingIcon = new FluentIcon();
    settingIcon->setIconName(QString("SETTING"));
    FluentIcon *saveIcon = new FluentIcon();
    saveIcon->setIconName(QString("SAVE"));
    FluentIcon *heartIcon = new FluentIcon();
    heartIcon->setIconName(QString("HEART"));
    FluentIcon *printIcon = new FluentIcon();
    printIcon->setIconName(QString("PRINT"));

    view->addAction(new Action(shareIcon, this->tr("Share"), nullptr));
    Action *saveAction = new Action(saveIcon, this->tr("Save"), nullptr);
    connect(saveAction, &Action::triggered, this, &MenuInterface::saveImage);
    view->addAction(saveAction);

    view->addAction(new Action(heartIcon, this->tr("Add to favorate"), nullptr));
    view->addAction(new Action(deleteIcon, this->tr("Delete"), nullptr));
    Action *printAction = new Action(printIcon, this->tr("Print"), nullptr);
    printAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_P));
    view->addHiddenAction(printAction);
    Action *settingAction = new Action(settingIcon, this->tr("Settings"), nullptr);
    settingAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    view->addHiddenAction(settingAction);

    view->resizeToSuitableWidth();

    int x = this->imageLabel->width();
    QPoint pos = this->imageLabel->mapToGlobal(QPoint(x, 0));
    Flyout::make(view, QVariant::fromValue<QPoint>(pos), this, FlyoutAnimationType::FADE_IN, true);

}


void MenuInterface::saveImage()
{
    QString path = QFileDialog::getSaveFileName(
        this,
        this->tr("Save image"),
        QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),
        "PNG (*.png)"
    );

    this->imageLabel->image.save(path);
}


ProfileCard::ProfileCard(QString avatarPath, QString name, QString email, QWidget *parent) : QWidget(parent)
{
    this->avatar = new AvatarWidget(avatarPath, this);
    this->nameLabel = new BodyLabel(name, this);
    this->emailLabel = new CaptionLabel(email, this);
    QVariant url = QVariant::fromValue<QString>(QString("http://www.usable-programming.com"));
    this->logoutButton = new HyperlinkButton(&url, QString("注销"), this, nullptr);

    QColor color = isDarkTheme() ? QColor(206, 206, 206) : QColor(96, 96, 96);
    this->emailLabel->setStyleSheet(QString("QLabel{color: '%1").arg(color.name()));
    Font().setFont(this->logoutButton, 13, QFont::Normal);

    this->setFixedSize(307, 82);
    this->avatar->setRadius(24);
    this->avatar->move(2, 6);
    this->nameLabel->move(64, 13);
    this->emailLabel->move(64, 32);
    this->logoutButton->move(52, 48);
}