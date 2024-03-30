#include "navigation_panel.h"

NavigationToolTipFilter::NavigationToolTipFilter(QWidget *parent, int showDelay, ToolTipPosition position= ToolTipPosition::TOP) : ToolTipFilter(parent, showDelay, position)
{

}

bool NavigationToolTipFilter::_canShowToolTip()
{
    bool isVisible = ToolTipFilter::_canShowToolTip();
    NavigationWidget *parent = qobject_cast<NavigationWidget*>(this->parent());
    return isVisible && parent->isCompacted;
}


NavigationItem::NavigationItem(QString routeKey, QString parentRouteKey, NavigationWidget *widget)
{
    this->routeKey = routeKey;
    this->parentRouteKey = parentRouteKey;
    this->widget = widget;
}


NavigationPanel::NavigationPanel(QWidget *parent, bool isMinimalEnabled = false) : QFrame(parent)
{
    this->_parent = parent;
    this->_isMenuButtonVisible = true;
    this->_isReturnButtonVisible = false;
    this->_isCollapsible = true;
    this->_isAcrylicEnabled = false;

    this->acrylicBrush = new AcrylicBrush(this, 30, QColor(242, 242, 242, 150), QColor(255, 255, 255, 10), 0.03);

    this->scrollArea = new SingleDirectionScrollArea(this, Qt::Vertical);
    this->scrollWidget = new QWidget();

    FluentIcon *menuButtonIcon = new FluentIcon();
    menuButtonIcon->setIconName(QString("MENU"));
    this->menuButton = new NavigationToolButton(new QVariant(QVariant::fromValue<FluentIcon>(*menuButtonIcon)), this);

    FluentIcon *returnButtonIcon = new FluentIcon();
    returnButtonIcon->setIconName(QString("MENU"));
    this->returnButton = new NavigationToolButton(new QVariant(QVariant::fromValue<FluentIcon>(*returnButtonIcon)), this);

    this->vBoxLayout = new NavigationItemLayout(this);
    this->topLayout = new NavigationItemLayout(nullptr);
    this->bottomLayout = new NavigationItemLayout(nullptr);
    this->scrollLayout = new NavigationItemLayout(this->scrollWidget);

    this->items = QMap<QString, NavigationItem*>();
    this->history = qrouter;

    this->expandAni = new QPropertyAnimation(this, "geometry", this);
    this->expandWidth = 322;

    this->isMinimalEnabled = isMinimalEnabled;

    if(isMinimalEnabled){
        this->displayMode = NavigationDisplayMode::MINIMAL;
    }else{
        this->displayMode = NavigationDisplayMode::COMPACT;
    }

    this->__initWidget();
}


void NavigationPanel::__initWidget()
{
    this->resize(48, this->height());
    this->setAttribute(Qt::WA_StyledBackground);
    this->window()->installEventFilter(this);

    this->returnButton->hide();
    this->returnButton->setDisabled(true);

    this->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->scrollArea->setWidget(this->scrollWidget);
    this->scrollArea->setWidgetResizable(true);

    this->expandAni->setEasingCurve(QEasingCurve::OutQuad);
    this->expandAni->setDuration(150);

    connect(this->menuButton, &NavigationToolButton::clicked, this, &NavigationPanel::toggle);
    connect(this->expandAni, &QPropertyAnimation::finished, this, &NavigationPanel::_onExpandAniFinished);
    connect(this->history, &Router::emptyChanged, this->returnButton, &NavigationToolButton::setDisabled);
    connect(this->returnButton, &NavigationToolButton::clicked, this->history, &Router::pop);

    this->returnButton->installEventFilter(new ToolTipFilter(this->returnButton, 1000, ToolTipPosition::TOP));
    this->returnButton->setToolTip(this->tr("Back"));

    this->menuButton->installEventFilter(new ToolTipFilter(this->menuButton, 1000, ToolTipPosition::TOP));
    this->menuButton->setToolTip(this->tr("Open Navigation"));

    this->setProperty("menu", false);
    this->scrollWidget->setObjectName(QString("scrollWidget"));
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("NAVIGATION_INTERFACE"), Theme::AUTO);
    FluentStyleSheet().apply(this->scrollWidget, FluentStyleSheetMap.value("NAVIGATION_INTERFACE"), Theme::AUTO);
    this->__initLayout();
}


void NavigationPanel::__initLayout()
{
    this->vBoxLayout->setContentsMargins(0, 5, 0, 5);
    this->topLayout->setContentsMargins(4, 0, 4, 0);
    this->bottomLayout->setContentsMargins(4, 0, 4, 0);
    this->scrollLayout->setContentsMargins(4, 0, 4, 0);
    this->vBoxLayout->setSpacing(4);
    this->topLayout->setSpacing(4);
    this->bottomLayout->setSpacing(4);
    this->scrollLayout->setSpacing(4);

    this->vBoxLayout->addLayout(this->topLayout, 0);
    this->vBoxLayout->addWidget(this->scrollArea, 1, Qt::AlignTop);
    this->vBoxLayout->addLayout(this->bottomLayout, 0);

    this->vBoxLayout->setAlignment(Qt::AlignTop);
    this->topLayout->setAlignment(Qt::AlignTop);
    this->scrollLayout->setAlignment(Qt::AlignTop);
    this->bottomLayout->setAlignment(Qt::AlignBottom);

    this->topLayout->addWidget(this->returnButton, 0, Qt::AlignTop);
    this->topLayout->addWidget(this->menuButton, 0, Qt::AlignTop);
}



void NavigationPanel::_updateAcrylicColor()
{
    QColor tintColor;
    QColor luminosityColor;
    if(isDarkTheme()){
        tintColor = QColor(32, 32, 32, 200);
        luminosityColor = QColor(0, 0, 0, 0);
    }else{
        tintColor = QColor(255, 255, 255, 180);
        luminosityColor = QColor(255, 255, 255, 0);
    }

    this->acrylicBrush->tintColor = tintColor;
    this->acrylicBrush->luminosityColor = luminosityColor;
}


NavigationWidget *NavigationPanel::widget(QString routeKey)
{
    if(!this->items.contains(routeKey)){
        QString error = QString("%1 is illegal.").arg(routeKey);
        throw std::invalid_argument(error.toUtf8());
    }
    return this->items.value(routeKey)->widget;
}


NavigationTreeWidget *NavigationPanel::addItem(QString routeKey, QVariant *icon, QString text, std::function<void()> onClick, bool selectable, NavigationItemPosition position, QString tooltip, QString parentRouteKey)
{
    return this->insertItem(-1, routeKey, icon, text, onClick, selectable, position, tooltip, parentRouteKey);
}


void NavigationPanel::addWidget(QString routeKey, NavigationWidget *widget, std::function<void()> onClick, NavigationItemPosition position, QString tooltip, QString parentRouteKey)
{
    this->insertWidget(-1, routeKey, widget, onClick, position, tooltip, parentRouteKey);
}


NavigationTreeWidget *NavigationPanel::insertItem(int index, QString routeKey, QVariant *icon, QString text, std::function<void()> onClick, bool selectable, NavigationItemPosition position, QString tooltip, QString parentRouteKey)
{
    if(this->items.contains(routeKey)){
        return nullptr;
    }

    NavigationTreeWidget *w = new NavigationTreeWidget(icon, text, selectable, this);
    this->insertWidget(index, routeKey, w, onClick, position, tooltip, parentRouteKey);
    return w;
}


void NavigationPanel::insertWidget(int index, QString routeKey, NavigationWidget *widget, std::function<void()> onClick, NavigationItemPosition position, QString tooltip, QString parentRouteKey)
{
    if(this->items.contains(routeKey)){
        return;
    }

    this->_registerWidget(routeKey, parentRouteKey, widget, onClick, tooltip);
    if(!parentRouteKey.isNull()){
        ((NavigationTreeWidget*)this->widget(parentRouteKey))->insertChild(index, (NavigationTreeWidget*)widget); //TODO:特殊关注
    }else{
        this->_insertWidgetToLayout(index, widget, position);
    }
}


void NavigationPanel::addSeparator(NavigationItemPosition position)
{
    this->insertSeparator(-1, position);
}


void NavigationPanel::insertSeparator(int index, NavigationItemPosition position)
{
    NavigationSeparator *separator = new NavigationSeparator(this);
    this->_insertWidgetToLayout(index, separator, position);
}


void NavigationPanel::_registerWidget(QString routeKey, QString parentRouteKey, NavigationWidget *widget, std::function<void()> onClick, QString tooltip)
{
    connect(widget, &NavigationWidget::clicked, this, &NavigationPanel::_onWidgetClicked);

    if(onClick != nullptr){
        connect(widget, &NavigationWidget::clicked, this, [onClick](){
            onClick();
        });
    }

    widget->setProperty("routeKey", routeKey);
    widget->setProperty("parentRouteKey", parentRouteKey);
    this->items[routeKey] = new NavigationItem(routeKey, parentRouteKey, widget);

    if(this->displayMode == NavigationDisplayMode::EXPAND || this->displayMode == NavigationDisplayMode::MENU){
        widget->setCompacted(false);
    }

    if(!tooltip.isNull()){
        widget->setToolTip(tooltip);
        widget->installEventFilter(new NavigationToolTipFilter(widget, 1000, ToolTipPosition::TOP));
    }
}


void NavigationPanel::_insertWidgetToLayout(int index, NavigationWidget *widget, NavigationItemPosition position)
{
    if(position == NavigationItemPosition::TOP){
        widget->setParent(this);
        this->topLayout->insertWidget(index, widget, 0, Qt::AlignTop);
    }else if(position == NavigationItemPosition::SCROLL){
        widget->setParent(this->scrollWidget);
        this->scrollLayout->insertWidget(index, widget, 0, Qt::AlignTop);
    }else{
        widget->setParent(this);
        this->bottomLayout->insertWidget(index, widget, 0, Qt::AlignBottom);
    }

    widget->show();
}

void NavigationPanel::removeWidget(QString routeKey)
{
    if(!this->items.contains(routeKey)){
        return;
    }

    NavigationItem *item = this->items.value(routeKey);
    this->items.remove(routeKey);

    if(item->parentRouteKey != nullptr){
        ((NavigationTreeWidget*)this->widget(item->parentRouteKey))->removeChild((NavigationTreeWidget*)item->widget); //TODO:特殊关注
    }

    auto it = qobject_cast<NavigationTreeWidgetBase*>(item->widget);
    if(it != nullptr){

        QList<NavigationWidget *> list = item->widget->findChildren<NavigationWidget*>(nullptr, Qt::FindChildrenRecursively); //TODO:特殊关注
        for(int i = 0; i < list.size(); i++){
            QVariant key = list.at(i)->property("routeKey");
            if(key.isNull()){
                continue;
            }

            this->items.remove(key.value<QString>());
            list.at(i)->deleteLater();
            this->history->remove(key.value<QString>());
        }
    }
    item->widget->deleteLater();
    this->history->remove(routeKey);
    
}


void NavigationPanel::setMenuButtonVisible(bool isVisible)
{
    this->_isMenuButtonVisible = isVisible;
    this->menuButton->setVisible(isVisible);
}


void NavigationPanel::setReturnButtonVisible(bool isVisible)
{
    this->_isReturnButtonVisible = isVisible;
    this->returnButton->setVisible(isVisible);
}


void NavigationPanel::setCollapsible(bool on)
{
    this->_isCollapsible = on;
    if(!on && this->displayMode != NavigationDisplayMode::EXPAND){
        this->expand(false);
    }
}

void NavigationPanel::setExpandWidth(int width)
{
    if(width <= 42){
        return;
    }

    this->expandWidth = width;
    EXPAND_WIDTH = width - 10;
}


void NavigationPanel::setAcrylicEnabled(bool isEnabled)
{
    if(isEnabled == this->isAcrylicEnabled()){
        return;
    }

    this->_isAcrylicEnabled = isEnabled;
    this->setProperty("transparent", this->_canDrawAcrylic());
    this->setStyle(QApplication::style());
    this->update();
}

bool NavigationPanel::isAcrylicEnabled()
{
    return this->_isAcrylicEnabled;
}

void NavigationPanel::expand(bool useAni = true)
{
    this->_setWidgetCompacted(false);
    this->expandAni->setProperty("expand", true);
    this->menuButton->setToolTip(this->tr("Close Navigation"));

    int expandWidth = 1007 + this->expandWidth - 322;
    if((this->window()->width() > expandWidth && !this->isMinimalEnabled) || !this->_isCollapsible){
        this->displayMode = NavigationDisplayMode::EXPAND;
    }else{
        this->setProperty("menu", true);
        this->setStyle(QApplication::style());
        this->displayMode = NavigationDisplayMode::MENU;

        if(this->_canDrawAcrylic()){
            this->acrylicBrush->grabImage(QRect(this->mapToGlobal(QPoint()), QSize(this->expandWidth, this->height())));
        }

        if(!this->_parent->isWindow()){
            QPoint pos = ((QWidget *)this->parent())->pos();
            this->setParent(this->window());
            this->move(pos);
        }

        this->show();
    }

    if(useAni){
        emit(this->displayModeChanged(this->displayMode));
        this->expandAni->setStartValue(QVariant::fromValue<QRect>(QRect(this->pos(), QSize(48, this->height()))));
        this->expandAni->setEndValue(QVariant::fromValue<QRect>(QRect(this->pos(), QSize(this->expandWidth, this->height()))));
        this->expandAni->start();
    }else{
        this->setFixedWidth(this->expandWidth);
        this->_onExpandAniFinished();
    }
}



void NavigationPanel::collapse()
{
    if(this->expandAni->state() == QPropertyAnimation::Running){
        return;
    }

    QList<NavigationItem *> list = this->items.values();
    for(int i = 0; i < list.length(); i++){
        NavigationItem *w = list.at(i);
        auto a = qobject_cast<NavigationTreeWidget*>(w->widget);
        if(a != nullptr && a->isRoot()){
            a->setExpanded(false, true);
        } 
    }

    this->expandAni->setStartValue(QVariant::fromValue<QRect>(QRect(this->pos(), QSize(this->width(), this->height()))));
    this->expandAni->setEndValue(QVariant::fromValue<QRect>(QRect(this->pos(), QSize(48, this->height()))));
    this->expandAni->setProperty("expand", QVariant::fromValue<bool>(false));
    this->expandAni->start();

    this->menuButton->setToolTip(this->tr("Open Navigation"));
}


void NavigationPanel::toggle()
{
    if(this->displayMode == NavigationDisplayMode::COMPACT || this->displayMode == NavigationDisplayMode::MINIMAL){
        this->expand(true);
    }else{
        this->collapse();
    }
}


void NavigationPanel::setCurrentItem(QString routeKey)
{
    if(!this->items.contains(routeKey)){
        return;
    }

    QMap<QString, NavigationItem *>::iterator i;
    for (i = this->items.begin(); i != this->items.end(); ++i) {
        i.value()->widget->setSelected(i.key() == routeKey);
    }
}


void NavigationPanel::_onWidgetClicked()
{
    NavigationWidget *widget =  (NavigationWidget *)this->sender();
    if(!widget->isSelectable){
        return this->_showFlyoutNavigationMenu((NavigationTreeWidget *)widget); //TODO:特殊关注
    }

    this->setCurrentItem((((NavigationTreeWidget *)widget)->property("routeKey")).value<QString>());

    auto a = qobject_cast<NavigationTreeWidgetBase*>(widget);
    //auto b = qobject_cast<NavigationTreeWidgetBase*>(widget);
    bool isLeaf = (a == nullptr) || ((NavigationTreeWidgetBase*)widget)->isLeaf();
    if(this->displayMode == NavigationDisplayMode::MENU && isLeaf){
        this->collapse();
    }else if(this->isCollapsed()){
        this->_showFlyoutNavigationMenu((NavigationTreeWidget *)widget); //TODO:特殊关注
    }

}


void NavigationPanel::_showFlyoutNavigationMenu(NavigationTreeWidget *widget)
{
    auto a = qobject_cast<NavigationTreeWidget*>(widget);
    if(!(this->isCollapsed()  && a != nullptr)){
        return;
    }

    if(!a->isRoot() || a->isLeaf()){
        return;
    }

    QHBoxLayout *layout = new QHBoxLayout();

    if(this->_canDrawAcrylic()){
        AcrylicFlyoutViewBase *view = new AcrylicFlyoutViewBase(nullptr);
        view->setLayout(layout);
        Flyout *flyout = new AcrylicFlyout(view, this->window(), true);

        NavigationFlyoutMenu *menu = new NavigationFlyoutMenu(a, view);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->addWidget(menu);

        flyout->resize(flyout->sizeHint());
        QPoint pos = SlideRightFlyoutAnimationManager(flyout).position(a);
        flyout->exec(pos, FlyoutAnimationType::SLIDE_RIGHT);
        connect(menu, &NavigationFlyoutMenu::expanded, [this, flyout, a, menu](){
            this->_adjustFlyoutMenuSize(flyout, a, menu);
        });
    }else{
        FlyoutViewBase *view = new FlyoutViewBase(nullptr);
        view->setLayout(layout);
        Flyout *flyout = new Flyout(view, this->window(), true);

        NavigationFlyoutMenu *menu = new NavigationFlyoutMenu(a, view);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->addWidget(menu);

        flyout->resize(flyout->sizeHint());
        QPoint pos = SlideRightFlyoutAnimationManager(flyout).position(a);
        flyout->exec(pos, FlyoutAnimationType::SLIDE_RIGHT);
        connect(menu, &NavigationFlyoutMenu::expanded, [this, flyout, a, menu](){
            this->_adjustFlyoutMenuSize(flyout, a, menu);
        });
    }
}


void NavigationPanel::_adjustFlyoutMenuSize(Flyout *flyout, NavigationTreeWidget *widget, NavigationFlyoutMenu *menu)
{
    flyout->view->setFixedSize(menu->size());
    flyout->setFixedSize(flyout->layout()->sizeHint());

    FlyoutAnimationManager *manager = flyout->aniManger;
    QPoint pos = manager->position(widget);

    QRect rect = this->window()->geometry();
    int w = flyout->sizeHint().width() + 5;
    int h = flyout->sizeHint().height();
    int x = qMax(rect.left(), qMin(pos.x(), rect.right() - w));
    int y = qMax(rect.top() + 42, qMin(pos.y() - 4, rect.bottom() - h + 5));
    flyout->move(x, y);
}

bool NavigationPanel::isCollapsed()
{
    return this->displayMode == NavigationDisplayMode::COMPACT;
}

void NavigationPanel::resizeEvent(QResizeEvent *event)
{
    if(event->oldSize().height() == this->height()){
        return;
    }

    int th = this->topLayout->minimumSize().height();
    int bh = this->bottomLayout->minimumSize().height();
    int h = this->height() - th - bh - 20;
    this->scrollArea->setFixedHeight(qMax(h, 36));
}

bool NavigationPanel::eventFilter(QObject *obj, QEvent *e)
{
    if(obj != this->window() || !this->_isCollapsible){
        return QFrame::eventFilter(obj, e);
    }

    if(e->type() == QEvent::MouseButtonRelease){
        QMouseEvent *_e = (QMouseEvent *)e;
        if(!this->geometry().contains(_e->pos()) && this->displayMode == NavigationDisplayMode::MENU){
            this->collapse();
        }
    }else if(e->type() == QEvent::Resize){
        QResizeEvent *_e = (QResizeEvent*)e;
        int w = _e->size().width();
        if(w < 1008 && this->displayMode == NavigationDisplayMode::EXPAND){
            this->collapse();
        }else if(w > 1008 && this->displayMode == NavigationDisplayMode::COMPACT && !this->_isMenuButtonVisible){
            this->expand(true);
        }
    }

    return QFrame::eventFilter(obj, e);
}


void NavigationPanel::_onExpandAniFinished()
{
    if(!this->expandAni->property("expand").value<bool>()){
        if(this->isMinimalEnabled){
            this->displayMode = NavigationDisplayMode::MINIMAL;
        }else{
            this->displayMode = NavigationDisplayMode::COMPACT;
        }
        emit(this->displayModeChanged(this->displayMode));
    }

    if(this->displayMode == NavigationDisplayMode::MINIMAL){
        this->hide();
        this->setProperty("menu", false);
        this->setStyle(QApplication::style());
    }else if(this->displayMode == NavigationDisplayMode::COMPACT){
        this->setProperty("menu", false);
        this->setStyle(QApplication::style());

        QList<NavigationItem *> list = this->items.values();
        for(int i = 0; i < list.length(); i++){
            list.at(i)->widget->setCompacted(true);
        }

        if(!this->_parent->isWindow()){
            this->setParent(this->_parent);
            this->move(0, 0);
            this->show();
        }
    }
}


void NavigationPanel::_setWidgetCompacted(bool isCompacted)
{
    QList<NavigationWidget*> list = this->findChildren<NavigationWidget*>();
    for(int i = 0; i < list.length(); i++){
        list.at(i)->setCompacted(isCompacted);
    }
}


int NavigationPanel::layoutMinHeight()
{
    int th = this->topLayout->minimumSize().height();
    int bh = this->bottomLayout->minimumSize().height();
    QList<NavigationSeparator*> list = this->findChildren<NavigationSeparator*>();
    int sh = 0;
    for(int i = 0; i < list.length(); i++){
        sh += list.at(i)->height();
    }
    int spacing = this->topLayout->count() * this->topLayout->spacing();
    spacing += this->bottomLayout->count() * this->bottomLayout->spacing();
    return 36 + th + bh + sh + spacing;
}

bool NavigationPanel::_canDrawAcrylic()
{
    return this->acrylicBrush->isAvailabel() && this->isAcrylicEnabled();
}


void NavigationPanel::paintEvent(QPaintEvent *event)
{
    if(!this->_canDrawAcrylic() || this->displayMode != NavigationDisplayMode::MENU){
        return QFrame::paintEvent(event);
    }

    QPainterPath path = QPainterPath();
    path.setFillRule(Qt::WindingFill);
    path.addRoundedRect(0, 1, this->width() - 1, this->height() - 1, 7, 7);
    path.addRect(0, 1, 8, this->height() - 1);
    this->acrylicBrush->setClipPath(path);

    this->_updateAcrylicColor();
    this->acrylicBrush->paint();

    QFrame::paintEvent(event);
}



void NavigationItemLayout::setGeometry(const QRect& rect)
{
    QVBoxLayout::setGeometry(rect);
    for(int i = 0; i < this->count(); i++){
        QLayoutItem *item =  this->itemAt(i);
        auto a = qobject_cast<NavigationSeparator*>(item->widget());
        if(a != nullptr){
            QRect geo =  a->geometry();
            item->widget()->setGeometry(0, geo.y(), geo.width(), geo.height());
        }
    }
}


