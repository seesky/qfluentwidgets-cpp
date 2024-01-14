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

    QListWidgetItem *item = new QListWidgetItem(*(this->_createItemIcon(action)), action->text());
    this->_adjustItemText(item, action);

    if(!action->isEnabled())
        item->setFlags(Qt::NoItemFlags);
    
    item->setData(Qt::UserRole, QVariant::fromValue<QAction *>(action));
    action->setProperty("item", QVariant::fromValue<QListWidgetItem *>(item));
    connect(action, &QAction::changed, this, &RoundMenu::_onActionChanged);
    return item;
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

    
}

