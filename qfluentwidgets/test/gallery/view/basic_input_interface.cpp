#include "basic_input_interface.h"

BasicInputInterface::BasicInputInterface(QWidget *parent) : GalleryInterface(Translator(nullptr).basicInput, "fluentwidgets.components.widgets", parent)
{
    this->setObjectName("basicInputInterface");

    this->addExampleCard(
        this->tr("A simple button with text content"),
        new PushButton(this->tr("Standard push button"), nullptr, nullptr),
        "http://www.github.com", 0);
    
    ToolButton *button = new ToolButton("qfluentwidgets/images/kunkun.png", nullptr);
    button->setIconSize(QSize(40, 40));
    button->resize(70, 70);
    this->addExampleCard(
        this->tr("A button with graphical content"),
        button,
        "http://www.github.com", 0);
    

    this->addExampleCard(
        this->tr("Accent style applied to push button"),
        new PrimaryPushButton(this->tr("Accent style button"), nullptr, nullptr),
        "http://github.com", 0);
    
    FluentIcon *primaryToolButtonicon = new FluentIcon();
    primaryToolButtonicon->setIconName(QString("BASKETBALL"));
    this->addExampleCard(
        this->tr("Accent style applied to tool button"),
        new PrimaryToolButton(primaryToolButtonicon, nullptr),
        "http://www.github.com", 0);
    
    FluentIcon *pillPushButtonicon = new FluentIcon();
    pillPushButtonicon->setIconName(QString("TAG"));
    this->addExampleCard(
        this->tr("Pill push button"),
        new PillPushButton(pillPushButtonicon, this->tr("Tag"), nullptr),
        "http://www.baidu.com", 0);
    
    this->addExampleCard(
        this->tr("Pill tool button"),
        new PillToolButton(primaryToolButtonicon, nullptr),
        "http://www.github.com", 0);
    
    FluentIcon *bookShelficon = new FluentIcon();
    bookShelficon->setIconName(QString("BOOK_SHELF"));
    this->addExampleCard(
        this->tr("A transparent push button"),
        new TransparentPushButton(bookShelficon, this->tr("Transparent push button"), nullptr),
        "http://www.github.com", 0
    );

    this->addExampleCard(
        this->tr("A transparent tool button"),
        new TransparentToolButton(bookShelficon, this),
        "http://www.github.com", 0
    );


    this->addExampleCard(
        this->tr("A 3-state CheckBox"),
        new CheckBox(this->tr("Two-state CheckBox"), nullptr),
        "http://www.github.com", 0
    );

    CheckBox *checkBox2State = new CheckBox(this->tr("A 2-state CheckBox"), nullptr);
    checkBox2State->setTristate(false);
    this->addExampleCard(
        this->tr("A 2-state CheckBox"),
        checkBox2State,
        "http://www.github.com", 0
    );

    ComboBox *comboBox = new ComboBox(nullptr);
    comboBox->setMinimumWidth(210);
    QList<QString> *items = new QList<QString>();
    items->append(QString("test1 🥰"));
    items->append(QString("test2 ☆"));
    items->append(QString("test3"));
    items->append(QString("test4sdfsdfsdf"));
    comboBox->addItems(*items);
    comboBox->setCurrentIndex(0);

    this->addExampleCard(
        this->tr("A ComboBox with items"),
        comboBox,
        "http://www.github.com", 0
    );


    EditableComboBox *editableComboBox = new EditableComboBox(nullptr);
    editableComboBox->addItems(*items);
    editableComboBox->setPlaceholderText(this->tr("Choose your stand"));
    editableComboBox->setMinimumWidth(210);
    this->addExampleCard(
        this->tr("An editable ComboBox"),
        editableComboBox,
        "http://www.github.com", 0
    );

    RoundMenu *menu = new RoundMenu(QString(""), this);

    FluentIcon *sendIcon = new FluentIcon();
    sendIcon->setIconName("SEND");
    Action *sendAction = new Action(sendIcon, this->tr("Send"), nullptr);
    menu->addAction(sendAction);

    FluentIcon *saveIcon = new FluentIcon();
    saveIcon->setIconName("SAVE");
    Action *saveAction = new Action(saveIcon, this->tr("Save"), nullptr);
    menu->addAction(saveAction);

    FluentIcon *mailIcon = new FluentIcon();
    mailIcon->setIconName("MAIL");
    DropDownPushButton *dropDownPushButton = new DropDownPushButton(mailIcon, this->tr("Email"), this);
    dropDownPushButton->setMenu(menu);

    this->addExampleCard(
        this->tr("A push button with drop down menu"),
        dropDownPushButton,
        "http://www.baidu.com", 0
    );


    DropDownToolButton *dropDownToolButton = new DropDownToolButton(mailIcon, this);
    dropDownToolButton->setMenu(menu);
    this->addExampleCard(
        this->tr("A tool button with drop down menu"),
        dropDownToolButton,
        "http://www.github.com", 0
    );

    PrimaryDropDownPushButton *primaryDropDownButton = new PrimaryDropDownPushButton(mailIcon,this->tr("Email"), this);
    primaryDropDownButton->setMenu(menu);
    this->addExampleCard(
        this->tr("A primary color push button with drop down menu"),
        primaryDropDownButton,
        "http://www.github.com", 0
    );

    PrimaryDropDownToolButton *primaryDropDownToolButton = new PrimaryDropDownToolButton(mailIcon, this);
    primaryDropDownToolButton->setMenu(menu);
    this->addExampleCard(
        this->tr("A primary color tool button with drop down menu"),
        primaryDropDownToolButton,
        "http://www.github.com", 0
    );

    TransparentDropDownPushButton *transparentDropDownPushButton = new TransparentDropDownPushButton(mailIcon, this->tr("Email"), this);
    transparentDropDownPushButton->setMenu(menu);
    this->addExampleCard(
        this->tr("A transparent push button with drop down menu"),
        transparentDropDownPushButton,
        "http://www.github.com", 0
    );

    FluentIcon *linkIcon = new FluentIcon();
    linkIcon->setIconName("LINK");
    QVariant url = QVariant::fromValue<QString>(QString("http://www.usable-programming.com"));
    this->addExampleCard(
        this->tr("A hyperlink button that navigates to a URI"),
        new HyperlinkButton(linkIcon, &url, "http://www.usable-programming.com", this),
        "http://www.usable-programming.com", 0
    );

    QWidget *radioWidget = new QWidget();
    QVBoxLayout *radioLayout = new QVBoxLayout(radioWidget);
    radioLayout->setContentsMargins(2, 0, 0, 0);
    radioLayout->setSpacing(15);
    RadioButton *radioButton1 = new RadioButton(this->tr("Star Platinum"), radioWidget);
    RadioButton *radioButton2 = new RadioButton(this->tr("Crazy Diamond"), radioWidget);
    RadioButton *radioButton3 = new RadioButton(this->tr("Soft and Wet"), radioWidget);
    QButtonGroup *buttonGroup = new QButtonGroup(radioWidget);
    buttonGroup->addButton(radioButton1);
    buttonGroup->addButton(radioButton2);
    buttonGroup->addButton(radioButton3);
    radioLayout->addWidget(radioButton1);
    radioLayout->addWidget(radioButton2);
    radioLayout->addWidget(radioButton3);
    radioButton1->click();
    this->addExampleCard(
        this->tr("A group of RadioButton controls in a button group"),
        radioWidget,
        "http://www.github.com", 0
    );


    Slider *slider = new Slider(Qt::Horizontal, nullptr);
    slider->setRange(0, 100);
    slider->setValue(30);
    slider->setMinimumWidth(200);
    this->addExampleCard(
        this->tr("A simple horizontal slider"),
        slider,
        "http://www.github.com", 0
    );

    SplitPushButton *splitPushButton = new SplitPushButton(primaryToolButtonicon, this->tr("Choose your stand"), this);
    splitPushButton->setFlyout(menu);
    this->addExampleCard(
        this->tr("A split push button with drop down menu"),
        splitPushButton,
        "http://www.github.com", 0
    );



    RoundMenu *ikunMenu = new RoundMenu(QString(""), this);
    ikunMenu->addAction(new Action(this->tr("Sing"), nullptr));
    ikunMenu->addAction(new Action(this->tr("Jump"), nullptr));
    ikunMenu->addAction(new Action(this->tr("Rap"), nullptr));
    ikunMenu->addAction(new Action(this->tr("Music"), nullptr));
    SplitToolButton *splitToolButton = new SplitToolButton(new QIcon("qfluentwidgets/images/kunkun.png"), this);
    //splitToolButton->setIconSize(new QSize(30, 30));
    splitToolButton->setFlyout(ikunMenu);
    this->addExampleCard(
        this->tr("A split tool button with drop down menu"),
        splitToolButton,
        "http://www.github.com", 0
    );

    PrimarySplitPushButton *primarySplitPushButton = new PrimarySplitPushButton(primaryToolButtonicon, this->tr("Choose your stand"), this);
    primarySplitPushButton->setFlyout(menu);
    this->addExampleCard(
        this->tr("A primary color split push button with drop down menu"),
        primarySplitPushButton,
        "http://www.github.com", 0
    );

    PrimarySplitToolButton *primarySplitToolButton = new PrimarySplitToolButton(primaryToolButtonicon, this);
    primarySplitToolButton->setFlyout(ikunMenu);
    this->addExampleCard(
        this->tr("A primary color split tool button with drop down menu"),
        primarySplitToolButton,
        "http://www.github.com", 0
    );


    SwitchButton *switchButton = new SwitchButton(this->tr("Off"), nullptr, IndicatorPosition::LEFT);
    this->addExampleCard(
        this->tr("A simple switch button"),
        switchButton,
        "http://www.github.com", 0
    );

    this->addExampleCard(
        this->tr("A simple toggle push button"),
        new ToggleButton(primaryToolButtonicon, this->tr("Start practicing"), this),
        "http://www.github.com", 0
    );

    this->addExampleCard(
        this->tr("A simple toggle tool button"),
        new ToggleToolButton(primaryToolButtonicon, this),
        "http://www.github.com", 0
    );

    this->addExampleCard(
        this->tr("A transparent toggle push button"),
        new TransparentTogglePushButton(primaryToolButtonicon, this->tr("Start practicing"), this),
        "http://www.github.com", 0
    );

    this->addExampleCard(
        this->tr("A transparent toggle tool button"),
        new TransparentToggleToolButton(primaryToolButtonicon, this),
        "http://www.github.com", 0
    );

}