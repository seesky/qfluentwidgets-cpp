#include "command_bar.h"

void CommandButton::_postInit()
{
    TransparentToggleToolButton::_postInit();
    this->setCheckable(false);
    this->setToolButtonStyle(Qt::ToolButtonIconOnly);
    Font().setFont(this, 12, QFont::Normal);

    this->_text = QString("");
    this->_action = nullptr;
    this->_isTight = false;
}

void CommandButton::setTight(bool isTight)
{
    this->_isTight = isTight;
    this->update();
}

bool CommandButton::isTight() const
{
    return this->_isTight;
}

QSize CommandButton::sizeHint() const
{
    if(this->isIconOnly()){
        return this->isTight() ? QSize(36, 34) : QSize(48, 34);
    }

    int tw = this->fontMetrics().width(this->text());

    Qt::ToolButtonStyle style = this->toolButtonStyle();

    if(style == Qt::ToolButtonTextBesideIcon){
        return QSize(tw + 47, 34);
    }

    if(style == Qt::ToolButtonTextOnly){
        return QSize(tw + 32, 34);
    }

    return QSize(tw + 32, 50);
}


bool CommandButton::isIconOnly() const
{
    if(this->text().isNull()){
        return true;
    }

    return this->toolButtonStyle() == Qt::ToolButtonIconOnly || this->toolButtonStyle() == Qt::ToolButtonFollowStyle;
}


void CommandButton::_drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state)
{
    //qDebug() << icon->typeName();
}

QString CommandButton::text() const
{
    return this->_text;
}

void CommandButton::setText(QString text)
{
    this->_text = text;
    this->update();
}

void CommandButton::setAction(QAction *action)
{
    this->_action = action;
    this->_onActionChanged();

    connect(this, &CommandButton::clicked, action, &QAction::trigger);
    connect(action, &QAction::toggled, this, &CommandButton::setChecked);
    connect(action, &QAction::changed, this, &CommandButton::_onActionChanged);

    this->installEventFilter(new CommandToolTipFilter(this, 700, ToolTipPosition::TOP));
}


void CommandButton::_onActionChanged()
{
    QAction *action = this->action();
    auto ac = qobject_cast<Action*>(action);

    if(ac != nullptr){
        QVariant *iconQ = new QVariant();
        QIcon *i = ac->icon();
        Icon* ii = (Icon*)(i);
        iconQ->setValue<Icon>(*ii);
        this->setIcon(iconQ);  //TODO:特殊关注
        this->setText(ac->text());
        this->setToolTip(ac->toolTip());
        this->setEnabled(ac->isEnabled());
        this->setCheckable(ac->isCheckable());
        this->setChecked(ac->isChecked());
    }else{
        QVariant *iconQ = new QVariant();
        iconQ->setValue(action->icon());
        this->setIcon(iconQ);  //TODO:特殊关注

        this->setText(action->text());
        this->setToolTip(action->toolTip());
        this->setEnabled(action->isEnabled());
        this->setCheckable(action->isCheckable());
        this->setChecked(action->isChecked());
    }
    
}



QAction *CommandButton::action()
{
    return this->_action;
}


void CommandButton::paintEvent(QPaintEvent *event)
{
    TransparentToggleToolButton::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    if(!this->isChecked()){
        painter.setPen(isDarkTheme() ? Qt::white : Qt::black);
    }else{
        painter.setPen(isDarkTheme() ? Qt::black : Qt::white);
    }

    if(!this->isEnabled()){
        painter.setOpacity(0.43);
    }else if(this->isPressed){
        painter.setOpacity(0.63);
    }

    Qt::ToolButtonStyle style =  this->toolButtonStyle();
    int iw = this->iconSize().width();
    int ih = this->iconSize().height();



    if(this->isIconOnly()){
        int y = (this->height() - ih) / 2;
        int x = (this->width() - iw) / 2;
        TransparentToggleToolButton::_drawIcon(this->_icon, &painter, QRect(x, y, iw, ih), QIcon::State::Off);
    }else if(style == Qt::ToolButtonTextOnly){
        painter.drawText(this->rect(), Qt::AlignCenter, this->text());
    }else if(style == Qt::ToolButtonTextBesideIcon){
        int he = this->height();
        int y = (this->height() - ih) / 2;
        TransparentToggleToolButton::_drawIcon(this->_icon, &painter, QRect(11, y, iw, ih), QIcon::State::Off);

        QRectF rect = QRectF(26, 0, this->width() - 26, this->height());
        painter.drawText(rect, Qt::AlignCenter, this->text());
    }else if(style == Qt::ToolButtonTextUnderIcon){
        int he = this->width();
        int x = (this->width() - iw) / 2;
        TransparentToggleToolButton::_drawIcon(this->_icon, &painter, QRect(x, 9, iw, ih), QIcon::State::Off);

        QRectF rect = QRectF(0, ih + 13, this->width(), this->height() - ih - 13);
        painter.drawText(rect, Qt::AlignHCenter | Qt::AlignTop, this->text());
    }
}


CommandToolTipFilter::CommandToolTipFilter(QWidget *parent, int showDelay, ToolTipPosition position) : ToolTipFilter(parent, showDelay, position)
{

}

bool CommandToolTipFilter::_canShowToolTip()
{
    return ToolTipFilter::_canShowToolTip()  && ((CommandButton *)this->parent())->isIconOnly(); //TODO:特殊关注
}


void MoreActionsButton::_postInit()
{
    FluentIcon *icon = new FluentIcon();
    icon->setIconName(QString("MORE"));
    QVariant *iconQVariant = new QVariant();
    iconQVariant->setValue<FluentIcon>(*icon);

    this->setIcon(iconQVariant);
}

QSize MoreActionsButton::sizeHint() const
{
    return QSize(40, 34);
}

void MoreActionsButton::clearState()
{
    this->setAttribute(Qt::WA_UnderMouse, false);
    QHoverEvent *e = new QHoverEvent(QEvent::HoverLeave, QPoint(-1, 1), QPoint());
    QApplication::sendEvent(this, e);
}


CommandSeparator::CommandSeparator(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(9, 34);
}

void CommandSeparator::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setPen(isDarkTheme() ? QColor(255, 255, 255, 21) : QColor(0, 0, 0, 15));
    painter.drawLine(5, 2, 5, this->height() - 2);
}


CommandMenu::CommandMenu(QWidget *parent) : RoundMenu(QString(""), parent)
{
    this->setItemHeight(32);
    this->view->setIconSize(QSize(16, 16));
}



CommandBar::CommandBar(QWidget *parent) : QFrame(parent)
{
    this->_widgets = QList<QWidget*>();
    this->_hiddenWidgets = QList<QWidget*>();
    this->_hiddenActions = QList<QAction*>();

    this->_menuAnimation = MenuAnimationType::DROP_DOWN;
    this->_toolButtonStyle = Qt::ToolButtonIconOnly;
    this->_iconSize = QSize(16, 16);
    this->_isButtonTight = false;
    this->_spacing = 4;

    this->moreButton = new MoreActionsButton(this);
    connect(this->moreButton, &MoreActionsButton::clicked, this, &CommandBar::_showMoreActionsMenu);
    this->moreButton->hide();

    Font().setFont(this, 12, QFont::Normal);
    this->setAttribute(Qt::WA_TranslucentBackground);
}

void CommandBar::setSpaing(int spacing)
{
    if(spacing == this->_spacing){
        return;
    }

    this->_spacing = spacing;
    this->updateGeometry();
}

int CommandBar::spacing()
{
    return this->_spacing;
}


CommandButton* CommandBar::addAction(QAction *action)
{
    if(this->actions().contains(action)){
        return nullptr;
    }

    CommandButton* button = this->_createButton(action);
    this->_insertWidgetToLayout(-1, button);
    QFrame::addAction(action);
    return button;
}

void CommandBar::addActions(QList<QAction*> actions)
{
    for(int i = 0; i < actions.length(); i++){
        this->addAction(actions.at(i));
    }
}

void CommandBar::addHiddenAction(QAction *action)
{
    if(this->actions().contains(action)){
        return;
    }

    this->_hiddenActions.append(action);
    this->updateGeometry();
    QFrame::addAction(action);
}

void CommandBar::addHiddenActions(QList<QAction*> actions)
{
    for(int i = 0; i < actions.length(); i++){
        this->addHiddenAction(actions.at(i));
    }
}

CommandButton* CommandBar::insertAction(QAction *before, QAction *action)
{
    if(!this->actions().contains(before)){
        return nullptr;
    }

    int index = this->actions().indexOf(before);
    CommandButton* button = this->_createButton(action);
    this->_insertWidgetToLayout(index, button);
    QFrame::insertAction(before, action);
    return button;
}

void CommandBar::addSeparator()
{
    this->insertSeparator(-1);
}

void CommandBar::insertSeparator(int index)
{
    this->_insertWidgetToLayout(index, new CommandSeparator(this));
}

void CommandBar::addWidget(QWidget *widget)
{
    this->_insertWidgetToLayout(-1, widget);
}

void CommandBar::removeAction(QAction *action)
{
    if(!this->actions().contains(action)){
        return;
    }

    for(int i = 0; i < this->commandButtons().length(); i++){
        if(this->commandButtons().at(i)->action() == action){
            this->_widgets.removeOne(this->commandButtons().at(i));
            this->commandButtons().at(i)->hide();
            this->commandButtons().at(i)->deleteLater();
            break;
        }
    }

    this->updateGeometry();
}



void CommandBar::removeWidget(QWidget *widget)
{
    if(!this->_widgets.contains(widget)){
        return;
    }

    this->_widgets.removeOne(widget);
    this->updateGeometry();
}


void CommandBar::removeHiddenAction(QAction *action)
{
    if(this->_hiddenActions.contains(action)){
        this->_hiddenActions.removeOne(action);
    }
}

void CommandBar::setToolButtonStyle(Qt::ToolButtonStyle style)
{
    if(this->toolButtonStyle() == style){
        return;
    }

    this->_toolButtonStyle = style;
    for(int i = 0; i < this->commandButtons().length(); i++){
        this->commandButtons().at(i)->setToolButtonStyle(style);
    }
}

Qt::ToolButtonStyle CommandBar::toolButtonStyle()
{
    return this->_toolButtonStyle;
}

void CommandBar::setButtonTight(bool isThight)
{
    if(this->isButtonTight() == isThight){
        return;
    }

    this->_isButtonTight = isThight;

    for(int i = 0; i < this->commandButtons().length(); i++){
        this->commandButtons().at(i)->setTight(isThight);
    }

    this->updateGeometry();
}


bool CommandBar::isButtonTight()
{
    return this->_isButtonTight;
}

void CommandBar::setIconSize(QSize size)
{
    if(size == this->iconSize()){
        return;
    }

    this->_iconSize = size;
    for(int i = 0; i < this->commandButtons().length(); i++){
        this->commandButtons().at(i)->setIconSize(size);
    }
}


QSize CommandBar::iconSize()
{
    return this->_iconSize;
}

void CommandBar::resizeEvent(QResizeEvent *event)
{
    this->updateGeometry();
}

CommandButton* CommandBar::_createButton(QAction *action)
{
    CommandButton *button = new CommandButton(this);
    button->setAction(action);
    button->setToolButtonStyle(this->toolButtonStyle());
    button->setTight(this->isButtonTight());
    button->setIconSize(this->iconSize());
    button->setFont(this->font());
    return button;
}


void CommandBar::_insertWidgetToLayout(int index, QWidget *widget)
{
    widget->setParent(this);
    widget->show();

    if(index < 0){
        this->_widgets.append(widget);
    }else{
        this->_widgets.insert(index, widget);
    }

    int maxHeight = 0;
    for(int i = 0; i < this->_widgets.length(); i++){
        if(this->_widgets.at(i)->height() > maxHeight){
            maxHeight = this->_widgets.at(i)->height();
        }
    }
    this->setFixedHeight(maxHeight);
    this->updateGeometry();
}


QSize CommandBar::minimumSizeHint()
{
    return this->moreButton->size();
}   

void CommandBar::updateGeometry()
{
    this->_hiddenWidgets.clear();
    this->moreButton->hide();

    QList<QWidget *> visibles = this->_visibleWidgets();
    int x = this->contentsMargins().left();
    int h = this->height();

    for(int i = 0; i < visibles.length(); i++){
        visibles.at(i)->show();
        visibles.at(i)->move(x, (h - visibles.at(i)->height()) / 2);
        x += (visibles.at(i)->width() + this->spacing());
    }

    if(!this->_hiddenActions.isEmpty() || visibles.length() < this->_widgets.length()){
        this->moreButton->show();
        this->moreButton->move(x, (h - this->moreButton->height()) / 2);
    }

    for(int i = visibles.length(); i < this->_widgets.length(); i++){
        this->_widgets.at(i)->hide();
        this->_hiddenWidgets.append(this->_widgets.at(i));
    }
}



QList<QWidget*> CommandBar::_visibleWidgets()
{
    if(this->suitableWidth() <= this->width()){
        return this->_widgets;
    }

    int w = this->moreButton->width();
    int index;
    for(int i = 0; i < this->_widgets.length(); i++){
        index = i;
        w += this->_widgets.at(i)->width();
        if(i > 0){
            w += this->spacing();
        }

        if(w > this->width()){
            break;
        }
    }

    return this->_widgets.mid(0, index);
}


int CommandBar::suitableWidth()
{
    QList<int> widths = QList<int>();
    for(int i = 0; i < this->_widgets.length(); i++){
        widths.append(this->_widgets.at(i)->width());
    }

    if(!this->_hiddenActions.isEmpty()){
        widths.append(this->moreButton->width());
    }

    return std::accumulate(widths.begin(), widths.end(), 0) + this->spacing() * qMax(widths.length() - 1, 0);
}


void CommandBar::resizeToSuitableWidth()
{
    this->setFixedWidth(this->suitableWidth());
}

void CommandBar::setFont(QFont font)
{
    QFrame::setFont(font);
    for(int i = 0; i < this->commandButtons().length(); i++){
        this->commandButtons().at(i)->setFont(font);
    }
}

QList<CommandButton*> CommandBar::commandButtons()
{
    QList<CommandButton*> commandButtonList = QList<CommandButton*>();
    for(int i = 0; i < this->_widgets.length(); i++){
        auto b = qobject_cast<CommandButton*>(this->_widgets.at(i));
        if(b != nullptr){
            commandButtonList.append(b);
        }
    }
    return commandButtonList;
}


void CommandBar::setMenuDropDown(bool down)
{
    if(down){
        this->_menuAnimation = MenuAnimationType::DROP_DOWN;
    }else{
        this->_menuAnimation = MenuAnimationType::PULL_UP;
    }
}

bool CommandBar::isMenuDropDown()
{
    return this->_menuAnimation == MenuAnimationType::DROP_DOWN;
}

void CommandBar::_showMoreActionsMenu()
{
    this->moreButton->clearState();

    QList<QAction *> actions = QList<QAction *>(this->_hiddenActions);

    for(int i = this->_hiddenWidgets.length() - 1; i >= 0; i--){
        auto b = qobject_cast<CommandButton*>(this->_hiddenWidgets.at(i));
        if(b != nullptr){
            actions.prepend(b->action());
        }
    }

    CommandMenu *menu = new CommandMenu(this);
    menu->addActions(&actions);

    int x = -menu->width() + menu->layout()->contentsMargins().right() + this->moreButton->width() + 18;
    int y;
    if(this->_menuAnimation == MenuAnimationType::DROP_DOWN){
        y = this->moreButton->height();
    }else{
        y = -5;
    }

    QPoint pos = this->moreButton->mapToGlobal(QPoint(x, y));
    menu->exec(&pos, true, this->_menuAnimation);
}



CommandViewMenu::CommandViewMenu(QWidget *parent) : CommandMenu(parent)
{
    this->view->setObjectName(QString("commandListWidget"));
}

void CommandViewMenu::setDropDown(bool down, bool _long)
{
    this->view->setProperty("dropDown", down);
    this->view->setProperty("long", _long);
    this->view->setStyle(QApplication::style());
    this->view->update();
}


CommandViewBar::CommandViewBar(QWidget *parent) : CommandBar(parent)
{
    this->setMenuDropDown(true);
}


void CommandViewBar::setMenuDropDown(bool down)
{
    if(down){
        this->_menuAnimation = MenuAnimationType::FADE_IN_DROP_DOWN;
    }else{
        this->_menuAnimation = MenuAnimationType::FADE_IN_PULL_UP;
    }
}

bool CommandViewBar::isMenuDropDown()
{
    return this->_menuAnimation == MenuAnimationType::FADE_IN_DROP_DOWN;
}

void CommandViewBar::_showMoreActionsMenu()
{
    this->moreButton->clearState();

    QList<QAction *> actions = QList<QAction *>(this->_hiddenActions);

    for(int i = this->_hiddenWidgets.length() - 1; i >= 0; i--){
        auto b = qobject_cast<CommandButton*>(this->_hiddenWidgets.at(i));
        if(b != nullptr){
            actions.prepend(b->action());
        }
    }

    CommandViewMenu *menu = new CommandViewMenu(this);
    menu->addActions(&actions);

    CommandBarView *view = (CommandBarView *)(this->parent());
    view->setMenuVisible(true);

    connect(menu, &CommandViewMenu::closedSignal, this, [this, view](){
        view->setMenuVisible(false);
    });
    menu->setDropDown(this->isMenuDropDown(), menu->view->width() > view->width()+5);

    if(menu->view->width() < view->width()){
        menu->view->setFixedWidth(view->width());
        menu->adjustSize();
    }

    int x = -menu->width() + menu->layout()->contentsMargins().right() + this->moreButton->width() + 18;
    int y;
    if(this->isMenuDropDown()){
        y = this->moreButton->height();
    }else{
        y = -13;
        menu->setShadowEffect(0, std::tuple<int,int>(0, 0), new QColor(0, 0, 0, 0));
        menu->layout()->setContentsMargins(12, 20, 12, 8);
    }

    QPoint pos = this->moreButton->mapToGlobal(QPoint(x, y));
    menu->exec(&pos, true, this->_menuAnimation);
}


CommandBarView::CommandBarView(QWidget *parent) : FlyoutViewBase(parent)
{
    this->bar = new CommandViewBar(this);
    this->hBoxLayout = new QHBoxLayout(this);

    this->hBoxLayout->setContentsMargins(6, 6, 6, 6);
    this->hBoxLayout->addWidget(this->bar);
    this->hBoxLayout->setSizeConstraint(QHBoxLayout::SetMinAndMaxSize);

    this->setButtonTight(true);
    this->setIconSize(QSize(14, 14));

    this->_isMenuVisible = false;
}

void CommandBarView::setMenuVisible(bool isVisible)
{
    this->_isMenuVisible = isVisible;
    this->update();
}

void CommandBarView::addWidget(QWidget *widget)
{
    this->bar->addWidget(widget);
}

void CommandBarView::setSpaing(int spacing)
{
    this->bar->setSpaing(spacing);
}

int CommandBarView::spacing()
{
    return this->bar->spacing();
}


CommandButton *CommandBarView::addAction(QAction *action)
{
    return this->bar->addAction(action);
}

void CommandBarView::addActions(QList<QAction*> actions)
{
    this->bar->addActions(actions);
}

void CommandBarView::addHiddenAction(QAction *action)
{
    this->bar->addHiddenAction(action);
}

void CommandBarView::addHiddenActions(QList<QAction*> actions)
{
    this->bar->addHiddenActions(actions);
}

CommandButton *CommandBarView::insertAction(QAction *before, QAction *action)
{
    return this->bar->insertAction(before, action);
}

void CommandBarView::addSeparator()
{
    this->bar->addSeparator();
}

void CommandBarView::insertSeparator(int index)
{
    this->bar->insertSeparator(index);
}

void CommandBarView::removeAction(QAction *action)
{
    this->bar->removeAction(action);
}

void CommandBarView::removeWidget(QWidget *widget)
{
    this->bar->removeWidget(widget);
}

void CommandBarView::removeHiddenAction(QAction *action)
{
    this->bar->removeAction(action);
}


void CommandBarView::setToolButtonStyle(Qt::ToolButtonStyle style)
{
    this->bar->setToolButtonStyle(style);
}

Qt::ToolButtonStyle CommandBarView::toolButtonStyle()
{
    return this->bar->toolButtonStyle();
}

void CommandBarView::setButtonTight(bool isThight)
{
    this->bar->setButtonTight(isThight);
}

bool CommandBarView::isButtonTight()
{
    this->bar->isButtonTight();
}

void CommandBarView::setIconSize(QSize size)
{
    this->bar->setIconSize(size);
}

QSize CommandBarView::iconSize()
{
    return this->bar->iconSize();
}

void CommandBarView::setFont(QFont font)
{
    this->bar->setFont(font);
}

void CommandBarView::setMenuDropDown(bool down)
{
    this->bar->setMenuDropDown(down);
}

int CommandBarView::suitableWidth()
{
    QMargins m = this->contentsMargins();
    return m.left() + m.right() + this->bar->suitableWidth();
}

void CommandBarView::resizeToSuitableWidth()
{
    this->bar->resizeToSuitableWidth();
    this->setFixedWidth(this->suitableWidth());
}

QList<QAction *> CommandBarView::actions()
{
    return this->bar->actions();
}

void CommandBarView::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    QPainterPath path = QPainterPath();
    path.setFillRule(Qt::WindingFill);
    path.addRoundedRect(QRectF(this->rect().adjusted(1, 1, -1, -1)), 8, 8);

    int y;
    if(this->_isMenuVisible){
        y = this->bar->isMenuDropDown() ? this->height() - 10 : 1;
        path.addRect(1, y, this->width() - 2, 9);
    }

    painter.setBrush(isDarkTheme() ? QColor(40, 40, 40) : QColor(248, 248, 248));
    painter.setPen(isDarkTheme() ? QColor(56, 56, 56) : QColor(233, 233, 233));
    painter.drawPath(path.simplified());
}