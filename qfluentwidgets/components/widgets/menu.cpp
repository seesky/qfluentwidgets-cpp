#include "menu.h"

CustomMenuStyle::CustomMenuStyle(int iconSize = 14) : QProxyStyle(){
    this->iconSize = iconSize;
}

int CustomMenuStyle::pixelMetric(PixelMetric metric, QStyleOption *option, QWidget *widget)
{
    if(metric == QStyle::PM_SmallIconSize)
        return iconSize;
    
    return QProxyStyle::pixelMetric(metric, option, widget);
}


DWMMenu::DWMMenu(QString title, QWidget *parent) : QMenu(title, parent)
{
    this->windowEffect = new WindowsWindowEffect(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup | Qt::NoDropShadowWindowHint);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setStyle(new CustomMenuStyle());
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("MENU"), Theme::AUTO);
}


bool DWMMenu::event(QEvent *e)
{
    if(e->type() == QEvent::WinIdChange)
        this->windowEffect->addMenuShadowEffect((HWND)(this->winId()));
    return QMenu::event(e);
}

SubMenuItemWidget::SubMenuItemWidget(QMenu *menu, QListWidgetItem *item, QWidget *parent) : QWidget(parent)
{
    this->menu = menu;
    this->item = item;
}

void SubMenuItemWidget::enterEvent(QEvent *event)
{
    QWidget::enterEvent(event);
    emit(this->showMenuSig(this->item));
}

void SubMenuItemWidget::paintEvent(QPaintEvent *event)
{
    QPainter *painter = new QPainter(this);
    painter->setRenderHints(QPainter::Antialiasing);

    FluentIcon *icon = new FluentIcon();
    icon->setIconName("CHEVRON_RIGHT");
    icon->render(painter, QRect(this->width()-10, this->height()/2-9/2, 9, 9), Theme::AUTO, 0, nullptr); //TODO:特殊关注
}

bool MenuItemDelegate::_isSeparator(QModelIndex index)
{
    return index.model()->data(index, Qt::DecorationRole) == "seperator";
}

void MenuItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if(!this->_isSeparator(index))
        return QStyledItemDelegate::paint(painter, option, index);
    
    painter->save();

    int c = isDarkTheme() ? 0 : 255;
    QPen *pen = new QPen(QColor(c, c, c, 25), 1);
    pen->setCosmetic(true);
    painter->setPen(*pen);
    QRect rect = option.rect;
    painter->drawLine(0, rect.y() + 4, rect.width() + 12, rect.y() + 4);
    painter->restore();
}


void ShortcutMenuItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    MenuItemDelegate::paint(painter, option, index);
    if(this->_isSeparator(index))
        return;
    
    
    QAction *action = qvariant_cast<QAction*>(index.data(Qt::UserRole)); //TODO:特殊关注

    if (!action || action->shortcut().isEmpty())
        return;

    painter->save();

    if(!(option.state & QStyle::State_Enabled))
        painter->setOpacity(isDarkTheme() ? 0.5 : 0.6);
    
    QFont font = Font().getFont(12, QFont::Normal);
    painter->setFont(font);
    painter->setPen(isDarkTheme() ? QColor(255, 255, 255, 200) : QColor(0, 0, 0, 153));

    QFontMetrics *fm = new QFontMetrics(font);
    QString shortcut = action->shortcut().toString(QKeySequence::NativeText);

    int sw = fm->width(shortcut);
    painter->translate(option.rect.width() - sw - 20, 0);

    QRectF *rect = new QRectF(0, option.rect.y(), sw, option.rect.height());
    painter->drawText(*rect, Qt::AlignLeft | Qt::AlignVCenter, shortcut);

    painter->restore();
}


RoundMenu::RoundMenu(QString title, QWidget *parent) : QMenu(parent)
{
    this->_title = title;
    QVariant __icon = QVariant::fromValue<QIcon>(QIcon());
    this->_icon = &__icon;
    this->_actions = new QList<QAction *>();
    this->_subMenus = new QList<RoundMenu *>();

    this->isSubMenu = false;
    this->parentMenu = nullptr;
    this->menuItem = nullptr;
    this->lastHoverItem = nullptr;
    this->lastHoverSubMenuItem = nullptr;
    this->isHideBySystem = true;
    this->itemHeight = 28;

    this->hBoxLayout = new QHBoxLayout(this);
    this->view = new MenuActionListWidget(this);

    this->aniManager = nullptr;
    this->timer = new QTimer(this);

    this->__initWidgets();
}

void RoundMenu::__initWidgets()
{
    this->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setMouseTracking(true);

    this->timer->setSingleShot(true);
    this->timer->setInterval(400);
    connect(this->timer, &QTimer::timeout, this, &RoundMenu::_onShowMenuTimeOut);

    this->setShadowEffect(30, std::tuple<int, int>(0, 8), new QColor(0, 0, 0, 30));
    this->hBoxLayout->addWidget(this->view, 1, Qt::AlignCenter);

    this->hBoxLayout->setContentsMargins(12, 8, 12, 20);
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("MENU"), Theme::AUTO);

    connect(this->view, &MenuActionListWidget::itemClicked, this, &RoundMenu::_onItemClicked);
    connect(this->view, &MenuActionListWidget::itemEntered, this, &RoundMenu::_onItemEntered);
}


void RoundMenu::setMaxVisibleItems(int num)
{
    this->view->setMaxVisibleItems(num);
    this->adjustSize();
}

void RoundMenu::setItemHeight(int height)
{
    if(height == this->itemHeight)
        return;
    
    this->itemHeight = height;
    this->view->setItemHeight(height);
}

void RoundMenu::setShadowEffect(int blurRadius = 30, std::tuple<int, int> offset = std::tuple<int, int>(0, 8), QColor *color = new QColor(0, 0, 0, 30))
{
    this->shadowEffect = new QGraphicsDropShadowEffect(this->view);
    this->shadowEffect->setBlurRadius(blurRadius);
    this->shadowEffect->setOffset(std::get<0>(offset), std::get<1>(offset));
    this->shadowEffect->setColor(*color);
    this->view->setGraphicsEffect(nullptr);
    this->view->setGraphicsEffect(this->shadowEffect);
}


void RoundMenu::_setParentMenu(RoundMenu *parent, QListWidgetItem *item)
{
    this->parentMenu = parent;
    this->menuItem = item;
    this->isSubMenu = (parent == nullptr) ? false : true;
}


void RoundMenu::adjustSize()
{
    QMargins m = this->layout()->contentsMargins();
    int w = this->view->width() + m.left() + m.right();
    int h = this->view->height() + m.top() + m.bottom();
    this->setFixedSize(w, h);
}

QVariant *RoundMenu::icon()
{
    return this->_icon;
}

QString RoundMenu::title()
{
    return this->_title;
}

void RoundMenu::clear()
{
    for (int i = _actions->size() - 1; i >= 0; --i) {
        this->removeAction((*_actions)[i]);
    }
}

void RoundMenu::setIcon(QVariant *icon)
{
    this->_icon = icon;
}

void RoundMenu::addAction(QAction *action)
{
    QListWidgetItem *item = this->_createActionItem(action, nullptr);
    this->view->addItem(item);
    this->adjustSize();
}

void RoundMenu::addWidget(QWidget *widget, bool selectable = true, SlotForwarder *onClick = nullptr)
{
    QAction *action = new QAction();
    action->setProperty("selectable", selectable);

    QListWidgetItem *item = this->_createActionItem(action, nullptr);
    item->setSizeHint(widget->size());

    this->view->addItem(item);
    this->view->setItemWidget(item, widget);

    if(!selectable)
        item->setFlags(Qt::NoItemFlags);
    
    if(onClick != nullptr)
        connect(action, SIGNAL(QMenu::triggered()), onClick, SLOT(SlotForwarder::forward()));  //TODO:特殊关注
    
    this->adjustSize();
}


QListWidgetItem *RoundMenu::_createActionItem(QAction *action, QAction *before)
{
    if(before == nullptr){
        this->_actions->append(action);
        QMenu::addAction(action);
    }else if(this->_actions->contains(before)){
        int index = this->_actions->indexOf(before);
        this->_actions->insert(index, action);
        QMenu::insertAction(before, action);
    }else{
        throw std::invalid_argument("`before` is not in the action list");
    }

    QVariant iconQVariant = QVariant::fromValue<QAction *>(action);
    QListWidgetItem *item = new QListWidgetItem(*(this->_createItemIcon(&iconQVariant)), action->text());
    this->_adjustItemText(item, action);

    if(!action->isEnabled())
        item->setFlags(Qt::NoItemFlags);
    
    item->setData(Qt::UserRole, QVariant::fromValue<QAction *>(action));
    action->setProperty("item", QVariant::fromValue<QListWidgetItem *>(item));
    connect(action, &QAction::changed, this, &RoundMenu::_onActionChanged);
    return item;
}

bool RoundMenu::_hasItemIcon()
{
    QList<QAction *>::iterator it;
    for (it = this->_actions->begin(); it != this->_actions->end(); ++it) {
        QAction * value = *it;
        if(!value->icon().isNull()){
            return true;
        }
    }

    QList<RoundMenu *>::iterator _it;
    for (_it = this->_subMenus->begin(); _it != this->_subMenus->end(); ++it) {
        RoundMenu * value = *_it;
        /*
        if(value->icon()->canConvert<Icon>()){ //TODO:特殊关注，保存的是引用
            if(!value->icon()->value<QIcon>().isNull()){
                return true;
            }
        }else if(value->icon()->canConvert<Icon>()){
            if(!value->icon()->value<Icon>().isNull()){
                return true;
            }
        }
        */
       if(value->icon()->isNull()){
        return true;
       }
    }

    return false;
}

int RoundMenu::_adjustItemText(QListWidgetItem *item, QAction *action)
{
    int sw;
    auto _widget = qobject_cast<ShortcutMenuItemDelegate*>(this->view->itemDelegate());
    if (nullptr != _widget){
        sw = this->_longestShortcutWidth();
        if(sw){
            sw += 22;
        }
    }else{
        sw = 0;
    }

    int w, space;
    if(!this->_hasItemIcon()){
        item->setText(action->text());
        w = 40 + this->view->fontMetrics().width(action->text()) + sw;
    }else{
        item->setText(QString(" ") + action->text());
        space = 4 - this->view->fontMetrics().width(" ");
        w = 60 + this->view->fontMetrics().width(item->text()) + sw + space;
    }

    item->setSizeHint(QSize(w, this->itemHeight));
    return w;
}

int RoundMenu::_longestShortcutWidth()
{
    QFontMetrics *fm = new QFontMetrics(Font().getFont(12, QFont::Normal));
    int r = 0;
    QList<QAction *>::iterator it;
    for (it = this->menuActions()->begin(); it != this->menuActions()->end(); ++it) {
        QAction * value = *it;
        if(fm->width(value->shortcut().toString()) > r){
            r = fm->width(value->shortcut().toString());
        }
    }
    return r;
}


QIcon *RoundMenu::_createItemIcon(QVariant *w)
{
    bool hasIcon = this->_hasItemIcon();
    QIcon *resultIcon;
    FluentIconEngine *fie;
    if(w->canConvert<QAction *>()){
        QAction *qvQaction = w->value<QAction *>();
        QVariant qvIcon = QVariant::fromValue<QIcon>(qvQaction->icon());
        fie = new FluentIconEngine(&qvIcon, false);
        QIcon *icon = new QIcon(fie);
        if(hasIcon && qvQaction->icon().isNull()){
            QPixmap pixmap = QPixmap(this->view->iconSize());
            pixmap.fill(Qt::transparent);
            resultIcon = new QIcon(pixmap);
        }else if(!hasIcon){
            resultIcon = new QIcon();
        }
    }else if(w->canConvert<RoundMenu *>()){
        RoundMenu *qvRoundMenu = w->value<RoundMenu *>();
        QVariant qvIcon;

        if(qvRoundMenu->icon()->canConvert<QIcon>()){
            qvIcon = QVariant::fromValue<QIcon>(qvRoundMenu->icon()->value<QIcon>());
        }else if(qvRoundMenu->icon()->canConvert<FluentIcon>()){
            qvIcon = QVariant::fromValue<FluentIcon>(qvRoundMenu->icon()->value<FluentIcon>());
        }

        fie = new FluentIconEngine(&qvIcon, false);
        QIcon *icon = new QIcon(fie);
        if(hasIcon && qvRoundMenu->icon()->isNull()){
            QPixmap pixmap = QPixmap(this->view->iconSize());
            pixmap.fill(Qt::transparent);
            resultIcon = new QIcon(pixmap);
        }else if(!hasIcon){
            resultIcon = new QIcon();
        }
    }

    return resultIcon;
}


void RoundMenu::insertAction(QAction *before, QAction *action)
{
    if(!this->_actions->contains(before)){
        return;
    }

    QVariant beforeItem = before->property("item");
    if(!beforeItem.isValid()){
        return;
    }

    int index = this->view->row(beforeItem.value<QListWidgetItem *>());
    QListWidgetItem * item = this->_createActionItem(action, before);
    this->view->insertItem(index, item);
    this->adjustSize();
}

void RoundMenu::addActions(QList<QAction *> *actions)
{
    QList<QAction *>::iterator it;
    for (it = actions->begin(); it != actions->end(); ++it) {
        QAction * value = *it;
        this->addAction(value);
    }
}

void RoundMenu::insertActions(QAction *before, QList<QAction *> *actions)
{
    QList<QAction *>::iterator it;
    for (it = actions->begin(); it != actions->end(); ++it) {
        QAction * value = *it;
        this->insertAction(before, value);
    }
}

void RoundMenu::removeAction(QAction *action)
{
    if(!this->_actions->contains(action)){
        return;
    }

    QVariant item = action->property("item");
    this->_actions->removeOne(action);
    action->setProperty("item", QVariant());

    if(!item.isValid()){
        return;
    }

    this->view->takeItem(this->view->row(item.value<QListWidgetItem *>()));
    item.value<QListWidgetItem *>()->setData(Qt::UserRole, QVariant());
    QMenu::removeAction(action);

    QWidget * widget = this->view->itemWidget(item.value<QListWidgetItem *>());
    if(widget){
        widget->deleteLater();
    }
}

void RoundMenu::setDefaultAction(QAction *action)
{
    if(!this->_actions->contains(action)){
        return;
    }
    QVariant item = action->property("item");
    if(item.isValid()){
        this->view->setCurrentItem(item.value<QListWidgetItem *>());
    }

}

void RoundMenu::addMenu(RoundMenu *menu)
{
    std::tuple<QListWidgetItem *, SubMenuItemWidget *> i = this->_createSubMenuItem(menu);
    this->view->addItem(std::get<0>(i));
    this->view->setItemWidget(std::get<0>(i), std::get<1>(i));
    this->adjustSize();
}


void RoundMenu::insertMenu(QAction *before, RoundMenu *menu)
{
    if(!this->_actions->contains(before)){
        return;
    }

    std::tuple<QListWidgetItem *, SubMenuItemWidget *> i = this->_createSubMenuItem(menu);
    this->view->insertItem(this->view->row(before->property("item").value<QListWidgetItem *>()), std::get<0>(i));
    this->view->setItemWidget(std::get<0>(i), std::get<1>(i));
    this->adjustSize();
}

std::tuple<QListWidgetItem *, SubMenuItemWidget*> RoundMenu::_createSubMenuItem(RoundMenu *menu)
{
    this->_subMenus->append(menu);
    QVariant qvRoundMenu = QVariant::fromValue<RoundMenu *>(menu);
    QListWidgetItem item = QListWidgetItem(*(this->_createItemIcon(&qvRoundMenu)), menu->title());
    
    int w;
    if(!this->_hasItemIcon()){
        w = 60 + this->view->fontMetrics().width(menu->title());
    }else{
        item.setText(QString(" ") + item.text());
        w = 72 + this->view->fontMetrics().width(item.text());
    }

    menu->_setParentMenu(this, &item);
    item.setSizeHint(QSize(w, this->itemHeight));
    item.setData(Qt::UserRole, qvRoundMenu);
    SubMenuItemWidget *_w = new SubMenuItemWidget((QMenu *)(&menu), &item, this); //TODO:特殊关注
    connect(_w, &SubMenuItemWidget::showMenuSig, this, &RoundMenu::_showSubMenu);
    _w->resize(item.sizeHint());

    return std::tuple<QListWidgetItem *, SubMenuItemWidget*>(&item, _w);
}


void RoundMenu::_showSubMenu(QListWidgetItem *item)
{
    this->lastHoverItem = item;
    this->lastHoverSubMenuItem = item;
    this->timer->stop();
    this->timer->start();
}

void RoundMenu::_onShowMenuTimeOut()
{
    if(this->lastHoverSubMenuItem == nullptr || !(this->lastHoverItem == this->lastHoverSubMenuItem)){
        return;
    }

    //TODO:没有实现
    //QMenu *w = (QMenu *)(this->view->itemWidget(this->lastHoverSubMenuItem));
}

void RoundMenu::addSeparator()
{
    auto asa = qobject_cast<QAbstractScrollArea*>(this->view);
    QMargins m = QMargins(0, 6, 0, 6);
    
    int w = this->view->width() - m.left() - m.right();

    QListWidgetItem item = QListWidgetItem();
    item.setFlags(Qt::NoItemFlags);
    item.setSizeHint(QSize(w, 9));
    this->view->addItem(&item);
    item.setData(Qt::DecorationRole, QVariant::fromValue<QString>(QString("seperator")));
    this->adjustSize();
}


void RoundMenu::_onItemClicked(QListWidgetItem *item)
{
    QAction *action = item->data(Qt::UserRole).value<QAction *>();
    if(!this->_actions->contains(action) || !action->isEnabled()){
        return;
    }

    if(this->view->itemWidget(item) && !action->property("selectable").isValid()){
        return;
    }

    this->_hideMenu(false);

    if(!this->isSubMenu){
        action->trigger();
        return;
    }

    this->_closeParentMenu();
    action->trigger();
}

void RoundMenu::_closeParentMenu()
{
    RoundMenu *menu = this;
    while(menu){
        menu->close();
        menu = menu->parentMenu;
    } 
}

void RoundMenu::_onItemEntered(QListWidgetItem *item)
{
    this->lastHoverItem = item;
    if(!item->data(Qt::UserRole).canConvert<RoundMenu *>()){
        return;
    }
    this->_showSubMenu(item);
}

void RoundMenu::_hideMenu(bool isHideBySystem = false)
{
    this->isHideBySystem = isHideBySystem;
    this->view->clearSelection();
    if(this->isSubMenu){
        this->hide();
    }else{
        this->close();
    }
}

void RoundMenu::hideEvent(QHideEvent *e)
{
    if(this->isHideBySystem && this->isSubMenu){
        this->_closeParentMenu();
    }

    this->isHideBySystem = true;
    e->accept();
}

void RoundMenu::closeEvent(QCloseEvent *e)
{
    e->accept();
    emit(this->closedSignal());
    this->view->clearSelection();
}

QList<QAction *> *RoundMenu::menuActions()
{
    return this->_actions;
}

void RoundMenu::mousePressEvent(QMouseEvent *e)
{
    QWidget * w = this->childAt(e->pos());
    if(w != this->view && !this->view->isAncestorOf(w)){
        this->_hideMenu(true);
    }
}

void RoundMenu::mouseMoveEvent(QMouseEvent *e)
{
    if(!this->isSubMenu){
        return;
    }

    QPoint pos = e->globalPos();
    MenuActionListWidget *view = this->parentMenu->view;

    //QMargins margin = view->viewportMargins();
    QMargins margin = QMargins(0, 6, 0, 6);
    QRect rect = view->visualItemRect(this->menuItem).translated(view->mapToGlobal(QPoint()));
    rect = rect.translated(margin.left(), margin.top() + 2);
    if(this->parentMenu->geometry().contains(pos) && !rect.contains(pos) && !this->geometry().contains(pos)){
        view->clearSelection();
        this->_hideMenu(false);
    }
}

void RoundMenu::_onActionChanged()
{
    QAction *action = (QAction *)this->sender();
    QListWidgetItem *item = action->property("item").value<QListWidgetItem *>();
    QVariant qvQAction = QVariant::fromValue<QAction *>(action);
    item->setIcon(*(this->_createItemIcon(&qvQAction)));

    this->_adjustItemText(item, action);

    if(action->isEnabled()){
        item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    }else{
        item->setFlags(Qt::NoItemFlags);
    }

    this->view->adjustSize(nullptr, MenuAnimationType::NONE);
    this->adjustSize();
}

void RoundMenu::exec(QPoint *pos, bool ani = true, MenuAnimationType aniType = MenuAnimationType::DROP_DOWN)
{
    this->aniManager = MenuAnimationManager().make(aniType, this);
    this->aniManager->exec(pos);
    this->show();
    if(this->isSubMenu){
        this->menuItem->setSelected(true);
    }
}

void RoundMenu::exec_(QPoint *pos, bool ani, MenuAnimationType aniType)
{
    this->exec(pos, ani, aniType);
}

void RoundMenu::adjustPosition()
{
    QMargins m = this->layout()->contentsMargins();
    QRect rect = QApplication::screenAt(QCursor::pos())->availableGeometry();
    int w = this->layout()->sizeHint().width() + 5;
    int h = this->layout()->sizeHint().height();

    int x = qMin(this->x() - m.left(), rect.right() - w);
    int y = this->y();
    if(y > rect.bottom() - h){
        y = this->y() - h + m.bottom();
    }
    this->move(x, y);
}

void RoundMenu::paintEvent(QPaintEvent *e)
{
    return;
}


MenuActionListWidget::MenuActionListWidget(QWidget *parent) : QListWidget(parent)
{
    this->_itemHeight = 28;
    this->_maxVisibleItems = -1;

    this->setViewportMargins(0, 6, 0, 6);
    this->setTextElideMode(Qt::ElideNone);
    this->setDragEnabled(false);
    this->setMouseTracking(true);
    this->setIconSize(QSize(14, 14));
    this->setItemDelegate(new ShortcutMenuItemDelegate(this));
    this->scrollDelegate = new SmoothScrollDelegate(qobject_cast<QAbstractScrollArea*>(this), false); //TODO:特殊关注
    this->setStyleSheet(QString("MenuActionListWidget{font: 14px \"Segoe UI\", \"Microsoft YaHei\", \"PingFang SC\"}"));
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void MenuActionListWidget::insertItem(int row, QListWidgetItem *item)
{
    QListWidget::insertItem(row, item);
    this->adjustSize(nullptr, MenuAnimationType::NONE);
}

void MenuActionListWidget::addItem(QListWidgetItem *item)
{
    QListWidget::addItem(item);
    this->adjustSize(nullptr, MenuAnimationType::NONE);
}

QListWidgetItem *MenuActionListWidget::takeItem(int row)
{
    QListWidgetItem *item = QListWidget::takeItem(row);
    this->adjustSize(nullptr, MenuAnimationType::NONE);
    return item;
}

void MenuActionListWidget::adjustSize(QPoint *pos = nullptr, MenuAnimationType aniType = MenuAnimationType::NONE)
{
    QSize *size = new QSize();
    for(int i = 0; i < this->count(); i++){
        QSize s = this->item(i)->sizeHint();
        size->setWidth(qMax(qMax(s.width(), size->width()), 1));
        size->setHeight(qMax(size->height() + s.height(), 1));
    }

    std::tuple<int, int> asize = MenuActionListAnimationManager().make(aniType, this)->availableViewSize(pos);
    this->viewport()->adjustSize();

    QMargins m = this->viewportMargins();
    *size += QSize(m.left()+m.right()+2, m.top()+m.bottom());
    size->setHeight(qMin(std::get<1>(asize), size->height() + 3));
    size->setWidth(qMax(qMin(std::get<0>(asize), size->width()), this->minimumWidth()));

    if(this->maxVisibleItems() > 0){
        size->setHeight(qMin(size->height(), this->maxVisibleItems() * this->_itemHeight + m.top() + m.bottom() + 3));
    }

    this->setFixedSize(*size);
}

void MenuActionListWidget::setItemHeight(int height)
{
    if(height == this->_itemHeight){
        return;
    }

    for(int i = 0; i++; i<this->count()){
        QListWidgetItem *item = this->item(i);
        if(!this->itemWidget(item)){
            item->setSizeHint(QSize(item->sizeHint().width(), height));
        }
    }

    this->_itemHeight = height;
    this->adjustSize();
}

void MenuActionListWidget::setMaxVisibleItems(int num)
{
    this->_maxVisibleItems = num;
    this->adjustSize();
}

int MenuActionListWidget::maxVisibleItems()
{
    return this->_maxVisibleItems;
}

int MenuActionListWidget::heightForAnimation(QPoint *pos, MenuAnimationType aniType)
{
    int ih = this->itemsHeight();
    std::tuple<int, int> asize = MenuActionListAnimationManager().make(aniType, this)->availableViewSize(pos);
    return qMin(ih, std::get<1>(asize));
}

int MenuActionListWidget::itemsHeight()
{
    int N = this->maxVisibleItems() ? this->count() : qMin(this->maxVisibleItems(), this->count());
    int h;
    for(int i = 0; i < N; i++){
        h += this->item(i)->sizeHint().height();
    }
    QMargins m = this->viewportMargins();
    return h + m.top() + m.bottom();
}


MenuAnimationManager::MenuAnimationManager(RoundMenu *menu) : QObject()
{
    this->managers = new QMap<MenuAnimationType, QString>();
    this->menu = menu;
    this->ani = new QPropertyAnimation(menu, "pos", menu);
    this->ani->setDuration(250);
    this->ani->setEasingCurve(QEasingCurve::OutQuad);
    connect(this->ani, &QPropertyAnimation::valueChanged, this, &MenuAnimationManager::_onValueChanged);
    connect(this->ani, &QPropertyAnimation::valueChanged, this, &MenuAnimationManager::_updateMenuViewport);
}

std::tuple<int, int> MenuAnimationManager::availableViewSize(QPoint *pos)
{
    QRect ss = QApplication::screenAt(QCursor::pos())->availableGeometry();
    int w = ss.width() - 100;
    int h = ss.height() - 100;
    return std::tuple<int, int>(w, h);
}

void MenuAnimationManager::_updateMenuViewport()
{
    this->menu->view->viewport()->update();
    this->menu->view->setAttribute(Qt::WA_UnderMouse, true);
    QHoverEvent e = QHoverEvent(QEvent::HoverEnter, QPoint(), QPoint(1, 1));
    QApplication::sendEvent(this->menu->view, &e);
}

QPoint *MenuAnimationManager::_endPosition(QPoint *pos)
{
    RoundMenu *m = this->menu;
    QRect rect = QApplication::screenAt(QCursor::pos())->availableGeometry();
    int w = m->width() + 5;
    int h = m->height();
    int x = qMin(pos->x() - m->layout()->contentsMargins().left(), rect.right() - 2);
    int y = qMin(pos->y() - 4, rect.bottom() - h + 10);
    return new QPoint(x, y);
}

std::tuple<int, int> MenuAnimationManager::_menuSize()
{
    QMargins m = this->menu->layout()->contentsMargins();
    int w = this->menu->view->width() + m.left() + m.right() + 120;
    int h = this->menu->view->height() + m.top() + m.bottom() + 20;
    return std::tuple<int, int>(w, h);
}



MenuAnimationManager *MenuAnimationManager::make(MenuAnimationType aniType, RoundMenu *menu)
{
    if(aniType == MenuAnimationType::NONE){
        return new DummyMenuAnimationManager(menu);
    }else if(aniType == MenuAnimationType::DROP_DOWN){
        return new DropDownMenuAnimationManager(menu);
    }else if(aniType == MenuAnimationType::PULL_UP){
        return new PullUpMenuAnimationManager(menu);
    }else if(aniType == MenuAnimationType::FADE_IN_DROP_DOWN){
        return new FadeInDropDownMenuAnimationManager(menu);
    }else if(aniType == MenuAnimationType::FADE_IN_PULL_UP){
        return new FadeInPullUpMenuAnimationManager(menu);
    }
    return nullptr;
}


void DummyMenuAnimationManager::exec(QPoint *pos)
{
    this->menu->move(*(this->_endPosition(pos)));
}

void DropDownMenuAnimationManager::exec(QPoint *pos)
{
    QPoint *_pos = this->_endPosition(pos);
    int h = this->menu->height() + 5;

    QVariant qvPoint = QVariant::fromValue<QPoint>(*_pos - QPoint(0, int(h/2)));
    QVariant qv_pos = QVariant::fromValue<QPoint>(*_pos);
    this->ani->setStartValue(qvPoint);
    this->ani->setEndValue(qv_pos);
    this->ani->start();
}

std::tuple<int, int> DropDownMenuAnimationManager::availableViewSize(QPoint *pos)
{
    QRect ss = QApplication::screenAt(QCursor::pos())->availableGeometry();
    return std::tuple<int, int>(ss.width() - 100, qMax(ss.bottom() - pos->y() - 10, 1));
}

void DropDownMenuAnimationManager::_onValueChanged()
{
    std::tuple<int, int> size = this->_menuSize();
    int w = std::get<0>(size);
    int h = std::get<1>(size);
    int y = this->ani->endValue().value<QRect>().y() - this->ani->currentValue().value<QRect>().y();
    this->menu->setMask(QRegion(0, y, w, h));
}

QPoint *PullUpMenuAnimationManager::_endPosition(QPoint *pos)
{
    RoundMenu *m = this->menu;
    QRect rect = QApplication::screenAt(QCursor::pos())->availableGeometry();
    int w = m->width() + 5;
    int h = m->height();
    int x = qMin(pos->x() - m->layout()->contentsMargins().left(), rect.right() - w);
    int y = qMax(pos->y() - h + 13, 4);
    return new QPoint(x, y);
}

void PullUpMenuAnimationManager::exec(QPoint *pos)
{
    QPoint *_pos = this->_endPosition(pos);
    int h = this->menu->height() + 5;

    QVariant qvPoint = QVariant::fromValue<QPoint>(*_pos + QPoint(0, int(h/2)));
    QVariant qv_pos = QVariant::fromValue<QPoint>(*_pos);
    this->ani->setStartValue(qvPoint);
    this->ani->setEndValue(qv_pos);
    this->ani->start();
}

std::tuple<int, int> PullUpMenuAnimationManager::availableViewSize(QPoint *pos)
{
    QRect ss = QApplication::screenAt(QCursor::pos())->availableGeometry();
    return std::tuple<int, int>(ss.width() - 100, qMax(pos->y() - 28, 1));
}

void PullUpMenuAnimationManager::_onValueChanged()
{
    std::tuple<int, int> size = this->_menuSize();
    int w = std::get<0>(size);
    int h = std::get<1>(size);
    int y = this->ani->endValue().value<QRect>().y() - this->ani->currentValue().value<QRect>().y();
    this->menu->setMask(QRegion(0, y, w, h - 28));
}

FadeInDropDownMenuAnimationManager::FadeInDropDownMenuAnimationManager(RoundMenu *menu) : MenuAnimationManager(menu)
{
    this->opacityAni = new QPropertyAnimation(menu, "windowOpacity", this);
    this->aniGroup = new QParallelAnimationGroup(this);
    this->aniGroup->addAnimation(this->ani);
    this->aniGroup->addAnimation(this->opacityAni);
}

void FadeInDropDownMenuAnimationManager::exec(QPoint *pos)
{
    QPoint *_pos = this->_endPosition(pos);
    this->opacityAni->setStartValue(QVariant::fromValue<int>(0));
    this->opacityAni->setEndValue(QVariant::fromValue<int>(1));
    this->opacityAni->setDuration(150);
    this->opacityAni->setEasingCurve(QEasingCurve::OutQuad);

    this->ani->setStartValue(QVariant::fromValue<QPoint>(*_pos - QPoint(0, 8)));
    this->ani->setEndValue(QVariant::fromValue<QPoint>(*_pos));
    this->ani->setDuration(150);
    this->ani->setEasingCurve(QEasingCurve::OutQuad);

    this->aniGroup->start();
}

std::tuple<int, int> FadeInDropDownMenuAnimationManager::availableViewSize(QPoint *pos)
{
    QRect ss = QApplication::screenAt(QCursor::pos())->availableGeometry();
    return std::tuple<int, int>(ss.width() - 100, qMax(ss.bottom() - pos->y() - 10, 1));
}


FadeInPullUpMenuAnimationManager::FadeInPullUpMenuAnimationManager(RoundMenu *menu) : MenuAnimationManager(menu)
{
    this->opacityAni = new QPropertyAnimation(menu, "windowOpacity", this);
    this->aniGroup = new QParallelAnimationGroup(this);
    this->aniGroup->addAnimation(this->ani);
    this->aniGroup->addAnimation(this->opacityAni);
}

QPoint *FadeInPullUpMenuAnimationManager::_endPosition(QPoint *pos)
{
    RoundMenu *m = this->menu;
    QRect rect = QApplication::screenAt(QCursor::pos())->availableGeometry();
    int w = m->width() + 5;
    int h = m->height();
    int x = qMin(pos->x() - m->layout()->contentsMargins().left(), rect.right() - w);
    int y = qMax(pos->y() - h + 15, 4);
    return new QPoint(x, y);
}

void FadeInPullUpMenuAnimationManager::exec(QPoint *pos)
{
    QPoint *_pos = this->_endPosition(pos);
    this->opacityAni->setStartValue(QVariant::fromValue<int>(0));
    this->opacityAni->setEndValue(QVariant::fromValue<int>(1));
    this->opacityAni->setDuration(150);
    this->opacityAni->setEasingCurve(QEasingCurve::OutQuad);

    this->ani->setStartValue(QVariant::fromValue<QPoint>(*_pos + QPoint(0, 8)));
    this->ani->setEndValue(QVariant::fromValue<QPoint>(*_pos));
    this->ani->setDuration(200);
    this->ani->setEasingCurve(QEasingCurve::OutQuad);

    this->aniGroup->start();
}

std::tuple<int, int> FadeInPullUpMenuAnimationManager::availableViewSize(QPoint *pos)
{
    QRect ss = QApplication::screenAt(QCursor::pos())->availableGeometry();
    return std::tuple<int, int>(ss.width() - 100, pos->y() - 28);
}



/////////////////////////////////////////////////////////////////////////////////////////////////
MenuActionListAnimationManager::MenuActionListAnimationManager(MenuActionListWidget *menu) : QObject()
{
    this->managers = new QMap<MenuAnimationType, QString>();
    this->menu = menu;
    this->ani = new QPropertyAnimation(menu, "pos", menu);
    this->ani->setDuration(250);
    this->ani->setEasingCurve(QEasingCurve::OutQuad);
    //connect(this->ani, &QPropertyAnimation::valueChanged, this, &MenuActionListAnimationManager::_onValueChanged);
    //connect(this->ani, &QPropertyAnimation::valueChanged, this, &MenuActionListAnimationManager::_updateMenuViewport);
}

std::tuple<int, int> MenuActionListAnimationManager::availableViewSize(QPoint *pos)
{
    QRect ss = QApplication::screenAt(QCursor::pos())->availableGeometry();
    int w = ss.width() - 100;
    int h = ss.height() - 100;
    return std::tuple<int, int>(w, h);
}

/*
void MenuActionListAnimationManager::_updateMenuViewport()
{
    this->menu->view->viewport()->update();
    this->menu->view->setAttribute(Qt::WA_UnderMouse, true);
    QHoverEvent e = QHoverEvent(QEvent::HoverEnter, QPoint(), QPoint(1, 1));
    QApplication::sendEvent(this->menu->view, &e);
}
*/

QPoint *MenuActionListAnimationManager::_endPosition(QPoint *pos)
{
    MenuActionListWidget *m = this->menu;
    QRect rect = QApplication::screenAt(QCursor::pos())->availableGeometry();
    int w = m->width() + 5;
    int h = m->height();
    int x = qMin(pos->x() - m->layout()->contentsMargins().left(), rect.right() - 2);
    int y = qMin(pos->y() - 4, rect.bottom() - h + 10);
    return new QPoint(x, y);
}

/*
std::tuple<int, int> MenuActionListAnimationManager::_menuSize()
{
    QMargins m = this->menu->layout()->contentsMargins();
    int w = this->menu->view->width() + m.left() + m.right() + 120;
    int h = this->menu->view->height() + m.top() + m.bottom() + 20;
    return std::tuple<int, int>(w, h);
}
*/



MenuActionListAnimationManager *MenuActionListAnimationManager::make(MenuAnimationType aniType, MenuActionListWidget *menu)
{
    if(aniType == MenuAnimationType::NONE){
        return new DummyMenuActionListAnimationManager(menu);
    }else if(aniType == MenuAnimationType::DROP_DOWN){
        return new DropDownMenuActionListAnimationManager(menu);
    }else if(aniType == MenuAnimationType::PULL_UP){
        return new PullUpMenuActionListAnimationManager(menu);
    }else if(aniType == MenuAnimationType::FADE_IN_DROP_DOWN){
        return new FadeInDropDownMenuActionListAnimationManager(menu);
    }else if(aniType == MenuAnimationType::FADE_IN_PULL_UP){
        return new FadeInPullUpMenuActionListAnimationManager(menu);
    }
    return nullptr;
}






void DummyMenuActionListAnimationManager::exec(QPoint *pos)
{
    this->menu->move(*(this->_endPosition(pos)));
}

void DropDownMenuActionListAnimationManager::exec(QPoint *pos)
{
    QPoint *_pos = this->_endPosition(pos);
    int h = this->menu->height() + 5;

    QVariant qvPoint = QVariant::fromValue<QPoint>(*_pos - QPoint(0, int(h/2)));
    QVariant qv_pos = QVariant::fromValue<QPoint>(*_pos);
    this->ani->setStartValue(qvPoint);
    this->ani->setEndValue(qv_pos);
    this->ani->start();
}

std::tuple<int, int> DropDownMenuActionListAnimationManager::availableViewSize(QPoint *pos)
{
    QRect ss = QApplication::screenAt(QCursor::pos())->availableGeometry();
    return std::tuple<int, int>(ss.width() - 100, qMax(ss.bottom() - pos->y() - 10, 1));
}

/*
void DropDownMenuActionListAnimationManager::_onValueChanged()
{
    std::tuple<int, int> size = this->_menuSize();
    int w = std::get<0>(size);
    int h = std::get<1>(size);
    int y = this->ani->endValue().value<QRect>().y() - this->ani->currentValue().value<QRect>().y();
    this->menu->setMask(QRegion(0, y, w, h));
}
*/

QPoint *PullUpMenuActionListAnimationManager::_endPosition(QPoint *pos)
{
    MenuActionListWidget *m = this->menu;
    QRect rect = QApplication::screenAt(QCursor::pos())->availableGeometry();
    int w = m->width() + 5;
    int h = m->height();
    int x = qMin(pos->x() - m->layout()->contentsMargins().left(), rect.right() - w);
    int y = qMax(pos->y() - h + 13, 4);
    return new QPoint(x, y);
}

void PullUpMenuActionListAnimationManager::exec(QPoint *pos)
{
    QPoint *_pos = this->_endPosition(pos);
    int h = this->menu->height() + 5;

    QVariant qvPoint = QVariant::fromValue<QPoint>(*_pos + QPoint(0, int(h/2)));
    QVariant qv_pos = QVariant::fromValue<QPoint>(*_pos);
    this->ani->setStartValue(qvPoint);
    this->ani->setEndValue(qv_pos);
    this->ani->start();
}

std::tuple<int, int> PullUpMenuActionListAnimationManager::availableViewSize(QPoint *pos)
{
    QRect ss = QApplication::screenAt(QCursor::pos())->availableGeometry();
    return std::tuple<int, int>(ss.width() - 100, qMax(pos->y() - 28, 1));
}

/*
void PullUpMenuActionListAnimationManager::_onValueChanged()
{
    std::tuple<int, int> size = this->_menuSize();
    int w = std::get<0>(size);
    int h = std::get<1>(size);
    int y = this->ani->endValue().value<QRect>().y() - this->ani->currentValue().value<QRect>().y();
    this->menu->setMask(QRegion(0, y, w, h - 28));
}
*/

FadeInDropDownMenuActionListAnimationManager::FadeInDropDownMenuActionListAnimationManager(MenuActionListWidget *menu) : MenuActionListAnimationManager(menu)
{
    this->opacityAni = new QPropertyAnimation(menu, "windowOpacity", this);
    this->aniGroup = new QParallelAnimationGroup(this);
    this->aniGroup->addAnimation(this->ani);
    this->aniGroup->addAnimation(this->opacityAni);
}

void FadeInDropDownMenuActionListAnimationManager::exec(QPoint *pos)
{
    QPoint *_pos = this->_endPosition(pos);
    this->opacityAni->setStartValue(QVariant::fromValue<int>(0));
    this->opacityAni->setEndValue(QVariant::fromValue<int>(1));
    this->opacityAni->setDuration(150);
    this->opacityAni->setEasingCurve(QEasingCurve::OutQuad);

    this->ani->setStartValue(QVariant::fromValue<QPoint>(*_pos - QPoint(0, 8)));
    this->ani->setEndValue(QVariant::fromValue<QPoint>(*_pos));
    this->ani->setDuration(150);
    this->ani->setEasingCurve(QEasingCurve::OutQuad);

    this->aniGroup->start();
}

std::tuple<int, int> FadeInDropDownMenuActionListAnimationManager::availableViewSize(QPoint *pos)
{
    QRect ss = QApplication::screenAt(QCursor::pos())->availableGeometry();
    return std::tuple<int, int>(ss.width() - 100, qMax(ss.bottom() - pos->y() - 10, 1));
}


FadeInPullUpMenuActionListAnimationManager::FadeInPullUpMenuActionListAnimationManager(MenuActionListWidget *menu) : MenuActionListAnimationManager(menu)
{
    this->opacityAni = new QPropertyAnimation(menu, "windowOpacity", this);
    this->aniGroup = new QParallelAnimationGroup(this);
    this->aniGroup->addAnimation(this->ani);
    this->aniGroup->addAnimation(this->opacityAni);
}

QPoint *FadeInPullUpMenuActionListAnimationManager::_endPosition(QPoint *pos)
{
    MenuActionListWidget *m = this->menu;
    QRect rect = QApplication::screenAt(QCursor::pos())->availableGeometry();
    int w = m->width() + 5;
    int h = m->height();
    int x = qMin(pos->x() - m->layout()->contentsMargins().left(), rect.right() - w);
    int y = qMax(pos->y() - h + 15, 4);
    return new QPoint(x, y);
}

void FadeInPullUpMenuActionListAnimationManager::exec(QPoint *pos)
{
    QPoint *_pos = this->_endPosition(pos);
    this->opacityAni->setStartValue(QVariant::fromValue<int>(0));
    this->opacityAni->setEndValue(QVariant::fromValue<int>(1));
    this->opacityAni->setDuration(150);
    this->opacityAni->setEasingCurve(QEasingCurve::OutQuad);

    this->ani->setStartValue(QVariant::fromValue<QPoint>(*_pos + QPoint(0, 8)));
    this->ani->setEndValue(QVariant::fromValue<QPoint>(*_pos));
    this->ani->setDuration(200);
    this->ani->setEasingCurve(QEasingCurve::OutQuad);

    this->aniGroup->start();
}

std::tuple<int, int> FadeInPullUpMenuActionListAnimationManager::availableViewSize(QPoint *pos)
{
    QRect ss = QApplication::screenAt(QCursor::pos())->availableGeometry();
    return std::tuple<int, int>(ss.width() - 100, pos->y() - 28);
}