#include "home_interface.h"


BannerWidget::BannerWidget(QWidget *parent) : QWidget(parent)
{
    this->setFixedHeight(336);

    this->vBoxLayout = new QVBoxLayout(this);
    this->galleryLabel = new QLabel("Fluent Gallery", this);
    this->banner = QPixmap("qfluentwidgets/images/header1.png");
    this->linkCardView = new LinkCardView(this);

    this->galleryLabel->setObjectName("galleryLabel");

    this->vBoxLayout->setSpacing(0);
    this->vBoxLayout->setContentsMargins(0, 20, 0, 0);
    this->vBoxLayout->addWidget(this->galleryLabel);
    this->vBoxLayout->addWidget(this->linkCardView, 1, Qt::AlignBottom);
    this->vBoxLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    this->linkCardView->addCard(
        new QVariant(QVariant::fromValue<QString>("qfluentwidgets/images/logo.png")),
        this->tr("Getting started"),
        this->tr("An overview of app development options and samples."),
        "http:://www.github.com"
    );

    FluentIcon *gitIcon = new FluentIcon();
    gitIcon->setIconName(QString("GITHUB"));
    this->linkCardView->addCard(
        new QVariant(QVariant::fromValue<FluentIcon>(*gitIcon)),
        this->tr("GitHub repo"),
        this->tr("The latest fluent design controls and styles for your applications."),
        "http:://www.github.com"
    );


    FluentIcon *codeIcon = new FluentIcon();
    codeIcon->setIconName(QString("CODE"));
    this->linkCardView->addCard(
        new QVariant(QVariant::fromValue<FluentIcon>(*codeIcon)),
        this->tr("Code samples"),
        this->tr("Find samples that demonstrate specific tasks, features and APIs."),
        "http:://www.github.com"
    );


    FluentIcon *feedbackIcon = new FluentIcon();
    feedbackIcon->setIconName(QString("FEEDBACK"));
    this->linkCardView->addCard(
        new QVariant(QVariant::fromValue<FluentIcon>(*feedbackIcon)),
        this->tr("Send feedback"),
        this->tr("Help us improve PyQt-Fluent-Widgets by providing feedback."),
        "http:://www.github.com"
    );

}


void BannerWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    QPainterPath *path = new QPainterPath();
    path->setFillRule(Qt::WindingFill);
    int w = this->width();
    int h = this->height();
    path->addRoundedRect(QRectF(0, 0, w, h), 10, 10);
    path->addRect(QRectF(0, h - 50, 50, 50));
    path->addRect(QRectF(w - 50, 0, 50, 50));
    path->addRect(QRectF(w - 50, h - 50, 50, 50));
    QPainterPath path_ = path->simplified();

    QLinearGradient gradient(0, 0, 0, h);
    if(!isDarkTheme()){
        gradient.setColorAt(0, QColor(207, 216, 228, 255));
        gradient.setColorAt(1, QColor(207, 216, 228, 0));
    }else{
        gradient.setColorAt(0, QColor(0, 0, 0, 255));
        gradient.setColorAt(1, QColor(0, 0, 0, 0));
    }

    painter.fillPath(path_, QBrush(gradient));

    QPixmap pixmap = this->banner.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    painter.fillPath(path_, QBrush(pixmap));
}



HomeInterface::HomeInterface(QWidget *parent) : ScrollArea(parent)
{
    this->banner = new BannerWidget(this);
    this->view = new QWidget(this);
    this->vBoxLayout = new QVBoxLayout(this->view);

    this->__initWidget();
    this->loadSamples();
}


void HomeInterface::__initWidget()
{
    this->view->setObjectName("view");
    this->setObjectName("homeInterface");
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("HOME_INTERFACE"), Theme::AUTO);

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setWidget(this->view);
    this->setWidgetResizable(true);

    this->vBoxLayout->setContentsMargins(0, 0, 0, 36);
    this->vBoxLayout->setSpacing(40);
    this->vBoxLayout->addWidget(this->banner);
    this->vBoxLayout->setAlignment(Qt::AlignTop);
}

void HomeInterface::loadSamples()
{
    SampleCardView *basicInputView = new SampleCardView(
        this->tr("Basic input samples"), this->view
    );
    basicInputView->addSampleCard(
        new QVariant(QVariant::fromValue<QString>("qfluentwidgets/images/controls/Button.png")),
        "Button",
        this->tr("A control that responds to user input and emit clicked signal."),
        "basicInputInterface", 0
    );
    basicInputView->addSampleCard(
        new QVariant(QVariant::fromValue<QString>("qfluentwidgets/images/controls/Checkbox.png")),
        "CheckBox",
        this->tr("A control that a user can select or clear."),
        "basicInputInterface", 8
    );
    basicInputView->addSampleCard(
        new QVariant(QVariant::fromValue<QString>("qfluentwidgets/images/controls/ComboBox.png")),
        "ComboBox",
        this->tr("A drop-down list of items a user can select from."),
        "basicInputInterface", 10
    );
    basicInputView->addSampleCard(
        new QVariant(QVariant::fromValue<QString>("qfluentwidgets/images/controls/DropDownButton.png")),
        "DropDownButton",
        this->tr("A button that displays a flyout of choices when clicked."),
        "basicInputInterface", 12
    );
    basicInputView->addSampleCard(
        new QVariant(QVariant::fromValue<QString>("qfluentwidgets/images/controls/HyperlinkButton.png")),
        "HyperlinkButton",
        this->tr("A button that appears as hyperlink text, and can navigate to a URI or handle a Click event."),
        "basicInputInterface", 18
    );
    basicInputView->addSampleCard(
        new QVariant(QVariant::fromValue<QString>("qfluentwidgets/images/controls/RadioButton.png")),
        "RadioButton",
        this->tr("A control that allows a user to select a single option from a group of options."),
        "basicInputInterface", 19
    );
    basicInputView->addSampleCard(
        new QVariant(QVariant::fromValue<QString>("qfluentwidgets/images/controls/Slider.png")),
        "Slider",
        this->tr("A control that lets the user select from a range of values by moving a Thumb control along a track."),
        "basicInputInterface", 20
    );
    basicInputView->addSampleCard(
        new QVariant(QVariant::fromValue<QString>("qfluentwidgets/images/controls/SplitButton.png")),
        "SplitButton",
        this->tr("A two-part button that displays a flyout when its secondary part is clicked."),
        "basicInputInterface", 21
    );
    basicInputView->addSampleCard(
        new QVariant(QVariant::fromValue<QString>("qfluentwidgets/images/controls/ToggleSwitch.png")),
        "SwitchButton",
        this->tr("A switch that can be toggled between 2 states."),
        "basicInputInterface", 25
    );
    basicInputView->addSampleCard(
        new QVariant(QVariant::fromValue<QString>("qfluentwidgets/images/controls/ToggleButton.png")),
        "ToggleButton",
        this->tr("A switch that can be toggled between 2 states."),
        "basicInputInterface", 26
    ); 
    this->vBoxLayout->addWidget(basicInputView);


    SampleCardView *dateTimeView = new SampleCardView(
        this->tr("Date & time samples"), this->view
    );
    dateTimeView->addSampleCard(
        new QVariant(QVariant::fromValue<QString>("qfluentwidgets/images/controls/CalendarDatePicker.png")),
        "CalendarPicker",
        this->tr("A control that lets a user pick a date value using a calendar."),
        "dateTimeInterface", 0
    );
    dateTimeView->addSampleCard(
        new QVariant(QVariant::fromValue<QString>("qfluentwidgets/images/controls/DatePicker.png")),
        "DatePicker",
        this->tr("A control that lets a user pick a date value."),
        "dateTimeInterface", 2
    );
    dateTimeView->addSampleCard(
        new QVariant(QVariant::fromValue<QString>("qfluentwidgets/images/controls/TimePicker.png")),
        "TimePicker",
        this->tr("A configurable control that lets a user pick a time value."),
        "dateTimeInterface", 4
    );

    this->vBoxLayout->addWidget(dateTimeView);

    SampleCardView *dialogView = new SampleCardView(
        this->tr("Dialog samples"), this->view
    );
    dialogView->addSampleCard(
        new QVariant(QVariant::fromValue<QString>("qfluentwidgets/images/controls/Flyout.png")),
        "Dialog",
        this->tr("A frameless message dialog."),
        "dialogInterface", 0
    );
    dialogView->addSampleCard(
        new QVariant(QVariant::fromValue<QString>("qfluentwidgets/images/controls/ContentDialog.png")),
        "MessageBox",
        this->tr("A message dialog with mask."),
        "dialogInterface", 1
    );
    dialogView->addSampleCard(
        new QVariant(QVariant::fromValue<QString>("qfluentwidgets/images/controls/ColorPicker.png")),
        "ColorDialog",
        this->tr("A dialog that allows user to select color."),
        "dialogInterface", 2
    );
    dialogView->addSampleCard(
        new QVariant(QVariant::fromValue<QString>("qfluentwidgets/images/controls/Flyout.png")),
        "Flyout",
        this->tr("Shows contextual information and enables user interaction."),
        "dialogInterface", 3
    );
    dialogView->addSampleCard(
        new QVariant(QVariant::fromValue<QString>("qfluentwidgets/images/controls/TeachingTip.png")),
        "TeachingTip",
        this->tr("A content-rich flyout for guiding users and enabling teaching moments."),
        "dialogInterface", 5
    );
    this->vBoxLayout->addWidget(dialogView);

    SampleCardView *layoutView = new SampleCardView(
        this->tr("Layout samples"), this->view
    );
    layoutView->addSampleCard(
        new QVariant(QVariant::fromValue<QString>("qfluentwidgets/images/controls/Grid.png")),
        "FlowLayout",
        this->tr("A layout arranges components in a left-to-right flow, wrapping to the next row when the current row is full."),
        "materialInterface", 0
    );
    this->vBoxLayout->addWidget(layoutView);

    SampleCardView *materialView = new SampleCardView(
        this->tr("Material samples"), this->view
    );
    materialView->addSampleCard(
        new QVariant(QVariant::fromValue<QString>("qfluentwidgets/images/controls/Acrylic.png")),
        "AcrylicLabel",
        this->tr("A translucent material recommended for panel background."),
        "materialInterface", 0
    );
    this->vBoxLayout->addWidget(materialView);

    SampleCardView *menuView = new SampleCardView(
        this->tr("Menu & toolbars samples"), this->view
    );
    menuView->addSampleCard(
        new QVariant(QVariant::fromValue<QString>("qfluentwidgets/images/controls/MenuFlyout.png")),
        "RoundMenu",
        this->tr("Shows a contextual list of simple commands or options."),
        "menuInterface", 0
    );
    menuView->addSampleCard(
        new QVariant(QVariant::fromValue<QString>("qfluentwidgets/images/controls/CommandBar.png")),
        "CommandBar",
        this->tr("Shows a contextual list of simple commands or options."),
        "menuInterface", 2
    );
    menuView->addSampleCard(
        new QVariant(QVariant::fromValue<QString>("qfluentwidgets/images/controls/CommandBarFlyout.png")),
        "CommandBarFlyout",
        this->tr("A mini-toolbar displaying proactive commands, and an optional menu of commands."),
        "menuInterface", 3
    );
    this->vBoxLayout->addWidget(menuView);

    SampleCardView *navigationView = new SampleCardView(
        this->tr("Navigation"), this->view
    );
    navigationView->addSampleCard(
        new QVariant(QVariant::fromValue<QString>("qfluentwidgets/images/controls/BreadcrumbBar.png")),
        "BreadcrumbBar",
        this->tr("Shows the trail of navigation taken to the current location."),
        "navigationViewInterface", 0
    );
    navigationView->addSampleCard(
        new QVariant(QVariant::fromValue<QString>("qfluentwidgets/images/controls/Pivot.png")),
        "Pivot",
        this->tr("Presents information from different sources in a tabbed view."),
        "navigationViewInterface", 1
    );
    navigationView->addSampleCard(
        new QVariant(QVariant::fromValue<QString>("qfluentwidgets/images/controls/TabView.png")),
        "TabView",
        this->tr("Presents information from different sources in a tabbed view."),
        "navigationViewInterface", 3
    );
    this->vBoxLayout->addWidget(navigationView);

    SampleCardView *scrollView = new SampleCardView(
        this->tr("Scrolling samples"), this->view
    );
    scrollView->addSampleCard(
        new QVariant(QVariant::fromValue<QString>("qfluentwidgets/images/controls/ScrollViewer.png")),
        "ScrollArea",
        this->tr("A container control that lets the user pan and zoom its content smoothly."),
        "scrollInterface", 0
    );
    scrollView->addSampleCard(
        new QVariant(QVariant::fromValue<QString>("qfluentwidgets/images/controls/PipsPager.png")),
        "PipsPager",
        this->tr("A control to let the user navigate through a paginated collection when the page numbers do not need to be visually known."),
        "scrollInterface", 3
    );
    this->vBoxLayout->addWidget(scrollView);

    SampleCardView *stateInfoView = new SampleCardView(
        this->tr("Status & info samples"), this->view
    );
    stateInfoView->addSampleCard(
        new QVariant(QVariant::fromValue<QString>("qfluentwidgets/images/controls/ProgressRing.png")),
        "StateToolTip",
        this->tr("Shows the apps progress on a task, or that the app is performing ongoing work that does block user interaction."),
        "statusInfoInterface", 0
    );
    stateInfoView->addSampleCard(
        new QVariant(QVariant::fromValue<QString>("qfluentwidgets/images/controls/InfoBadge.png")),
        "InfoBadge",
        this->tr("An non-intrusive Ul to display notifications or bring focus to an area."),
        "statusInfoInterface", 3
    );
    stateInfoView->addSampleCard(
        new QVariant(QVariant::fromValue<QString>("qfluentwidgets/images/controls/InfoBar.png")),
        "InfoBar",
        this->tr("An inline message to display app-wide status change information."),
        "statusInfoInterface", 4
    );
    stateInfoView->addSampleCard(
        new QVariant(QVariant::fromValue<QString>("qfluentwidgets/images/controls/ProgressBar.png")),
        "ProgressBar",
        this->tr("Shows the apps progress on a task, or that the app is performing ongoing work that doesn't block user interaction."),
        "statusInfoInterface", 8
    );
    stateInfoView->addSampleCard(
        new QVariant(QVariant::fromValue<QString>("qfluentwidgets/images/controls/ProgressRing.png")),
        "ProgressRing",
        this->tr("Shows the apps progress on a task, or that the app is performing ongoing work that doesn't block user interaction."),
        "statusInfoInterface", 10
    );
    stateInfoView->addSampleCard(
        new QVariant(QVariant::fromValue<QString>("qfluentwidgets/images/controls/ToolTip.png")),
        "ToolTip",
        this->tr("Displays information for an element in a pop-up window."),
        "statusInfoInterface", 1
    );
    this->vBoxLayout->addWidget(stateInfoView);

    SampleCardView *textView = new SampleCardView(
        this->tr("Text samples"), this->view
    );
    textView->addSampleCard(
        new QVariant(QVariant::fromValue<QString>("qfluentwidgets/images/controls/TextBox.png")),
        "LineEdit",
        this->tr("A single-line plain text field."),
        "textInterface", 0
    );
    textView->addSampleCard(
        new QVariant(QVariant::fromValue<QString>("qfluentwidgets/images/controls/PasswordBox.png")),
        "PasswordLineEdit",
        this->tr("A control for entering passwords."),
        "textInterface", 2
    );
    textView->addSampleCard(
        new QVariant(QVariant::fromValue<QString>("qfluentwidgets/images/controls/NumberBox.png")),
        "SpinBox",
        this->tr("A text control used for numeric input and evaluation of algebraic equations."),
        "textInterface", 3
    );
    textView->addSampleCard(
        new QVariant(QVariant::fromValue<QString>("qfluentwidgets/images/controls/RichEditBox.png")),
        "TextEdit",
        this->tr("A rich text editing control that supports formatted text, hyperlinks, and other rich content."),
        "textInterface", 8
    );
    this->vBoxLayout->addWidget(textView);

    SampleCardView *collectionView = new SampleCardView(
        this->tr("View samples"), this->view
    );
    collectionView->addSampleCard(
        new QVariant(QVariant::fromValue<QString>("qfluentwidgets/images/controls/ListView.png")),
        "ListView",
        this->tr("A control that presents a collection of items in a vertical list."),
        "viewInterface", 0
    );
    collectionView->addSampleCard(
        new QVariant(QVariant::fromValue<QString>("qfluentwidgets/images/controls/DataGrid.png")),
        "TableView",
        this->tr("The DataGrid control provides a flexible way to display a collection of data in rows and columns."),
        "viewInterface", 1
    );
    collectionView->addSampleCard(
        new QVariant(QVariant::fromValue<QString>("qfluentwidgets/images/controls/TreeView.png")),
        "TreeView",
        this->tr("The TreeView control is a hierarchical list pattern with expanding and collapsing nodes that contain nested items."),
        "viewInterface", 2
    );
    collectionView->addSampleCard(
        new QVariant(QVariant::fromValue<QString>("qfluentwidgets/images/controls/FlipView.png")),
        "FlipView",
        this->tr("Presents a collection of items that the user can flip through,one item at a time."),
        "viewInterface", 4
    );

    this->vBoxLayout->addWidget(collectionView);
}