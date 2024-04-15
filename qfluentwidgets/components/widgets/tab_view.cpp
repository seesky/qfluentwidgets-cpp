#include "tab_view.h"

TabToolButton::TabToolButton(QWidget *parent) : TransparentToolButton(parent)
{
    this->_postInit();
}

TabToolButton::TabToolButton(FluentIcon *icon, QWidget *parent) : TransparentToolButton(icon, parent)
{
    this->_postInit();
}


TabToolButton::TabToolButton(SpinIcon *icon, QWidget *parent) : TransparentToolButton(icon, parent)
{
    this->_postInit();
}

TabToolButton::TabToolButton(QIcon *icon, QWidget *parent) : TransparentToolButton(icon, parent)
{
    this->_postInit();
}

TabToolButton::TabToolButton(QString icon, QWidget *parent) : TransparentToolButton(icon, parent)
{
    this->_postInit();
}

void TabToolButton::_postInit()
{
    this->setFixedSize(32, 24);
    this->setIconSize(QSize(12, 12));
}

void TabToolButton::_drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state)
{
    QString color = isDarkTheme() ? QString("#eaeaea") : QString("#484848");

    if(icon->canConvert<FluentIcon>()){
        icon->value<FluentIcon>().icon(Theme::AUTO, QColor(color));
    }

    TransparentToolButton::_drawIcon(icon, painter, rect, state);
    
}



TabItem::TabItem(QWidget *parent) : PushButton(parent)
{
    this->_postInit();
}

TabItem::TabItem(QString text, QWidget *parent, QVariant *icon) : PushButton(text, parent, icon)
{
    this->_postInit();
}

TabItem::TabItem(QIcon *icon, QString text, QWidget *parent) : PushButton(icon, text, parent)
{
    this->_postInit();
}

TabItem::TabItem(FluentIcon *icon, QString text, QWidget *parent) : PushButton(icon, text, parent)
{
    this->_postInit();
}

void TabItem::_postInit()
{
    PushButton::_postInit();
    this->borderRadius = 5;
    this->isSelected = true;
    this->closeButtonDisplayMode = TabCloseButtonDisplayMode::ALWAYS;

    this->_routeKey = QString();
    this->textColor = QColor();

    this->lightSelectedBackgroundColor = QColor(249, 249, 249);
    this->darkSelectedBackgroundColor = QColor(40, 40, 40);

    FluentIcon *closeIcon = new FluentIcon();
    closeIcon->setIconName(QString("CLOSE"));
    this->closeButton = new TabToolButton(closeIcon, this);
    this->shadowEffect = new QGraphicsDropShadowEffect(this);

    this->slideAni = new QPropertyAnimation(this, "pos", this);

    this->__initWidget();

}


void TabItem::__initWidget()
{
    Font().setFont(this, 12, QFont::Normal);
    this->setFixedHeight(36);
    this->setMaximumWidth(240);
    this->setMinimumWidth(64);
    this->installEventFilter(new ToolTipFilter(this, 1000, ToolTipPosition::TOP));
    this->setAttribute(Qt::WA_LayoutUsesWidgetRect);

    this->closeButton->setIconSize(QSize(10, 10));

    this->shadowEffect->setBlurRadius(5);
    this->shadowEffect->setOffset(0, 1);
    this->setGraphicsEffect(this->shadowEffect);
    this->setSelected(false);

    connect(this->closeButton, &TabToolButton::clicked, this, [this](){
        emit(this->closed());
    });

}


void TabItem::slideTo(int x, int duration = 250)
{
    this->slideAni->setStartValue(this->pos());
    this->slideAni->setEndValue(QPoint(x, this->y()));
    this->slideAni->setDuration(duration);
    this->slideAni->setEasingCurve(QEasingCurve::InOutQuad);
    this->slideAni->start();
}


void TabItem::setShadowEnabled(bool isEnabled)
{
    if(isEnabled == this->isShadowEnabled){
        return;
    }

    this->isShadowEnabled = isEnabled;
    this->shadowEffect->setColor(QColor(0, 0, 0, 50 * this->_canShowShadow()));
}

bool TabItem::_canShowShadow()
{
    return this->isSelected && this->isShadowEnabled;
}


void TabItem::setRouteKey(QString key)
{
    this->_routeKey = key;
}

QString TabItem::routeKey()
{
    return this->_routeKey;
}

void TabItem::setBorderRadius(int radius)
{
    this->borderRadius = radius;
    this->update();
}

void TabItem::setSelected(bool isSelected)
{
    this->isSelected = isSelected;

    this->shadowEffect->setColor(QColor(0, 0, 0, 50 * this->_canShowShadow()));
    this->update();

    if(isSelected){
        this->raise();
    }

    if(this->closeButtonDisplayMode == TabCloseButtonDisplayMode::ON_HOVER){
        this->closeButton->setVisible(isSelected);
    }
}


void TabItem::setCloseButtonDisplayMode(TabCloseButtonDisplayMode mode)
{
    if(mode == this->closeButtonDisplayMode){
        return;
    }

    this->closeButtonDisplayMode = mode;

    if(mode == TabCloseButtonDisplayMode::NEVER){
        this->closeButton->hide();
    }else if(mode == TabCloseButtonDisplayMode::ALWAYS){
        this->closeButton->show();
    }else{
        this->closeButton->setVisible(this->isHover || this->isSelected);
    }
}


void TabItem::setTextColor(QColor color)
{
    this->textColor == QColor(color);
    this->update();
}



void TabItem::setSelectedBackgroundColor(QColor light, QColor dark)
{
    this->lightSelectedBackgroundColor = QColor(light);
    this->darkSelectedBackgroundColor = QColor(dark);
    this->update();
}


void TabItem::resizeEvent(QResizeEvent *event)
{
    this->closeButton->move(this->width() - 6 - this->closeButton->width(), this->height() / 2 - this->closeButton->height() / 2);
}

void TabItem::enterEvent(QEvent *event)
{
    PushButton::enterEvent(event);
    if(this->closeButtonDisplayMode == TabCloseButtonDisplayMode::ON_HOVER){
        this->closeButton->show();
    }
}

void TabItem::leaveEvent(QEvent *event)
{
    PushButton::leaveEvent(event);
    if(this->closeButtonDisplayMode == TabCloseButtonDisplayMode::ON_HOVER && !this->isSelected){
        this->closeButton->hide();
    }
}


void TabItem::mousePressEvent(QMouseEvent *event)
{
    PushButton::mousePressEvent(event);
    this->_forwardMouseEvent(event);
}


void TabItem::mouseMoveEvent(QMouseEvent *event)
{
    PushButton::mouseMoveEvent(event);
    this->_forwardMouseEvent(event);
}


void TabItem::mouseReleaseEvent(QMouseEvent *e)
{
    PushButton::mouseReleaseEvent(e);
    this->_forwardMouseEvent(e);
}

void TabItem::_forwardMouseEvent(QMouseEvent *e)
{
    QPoint pos = this->mapToParent(e->pos());
    QMouseEvent *event = new QMouseEvent(e->type(), pos, e->button(), e->buttons(), e->modifiers());
    QApplication::sendEvent(this->parent(), event);
}


QSize TabItem::sizeHint()
{
    return QSize(this->maximumWidth(), 36);
}

void TabItem::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    if(this->isSelected){
        this->_drawSelectedBackground(&painter);
    }else{
        this->_drawNotSelectedBackground(&painter);
    }

    if(!this->isSelected){
        painter.setOpacity(isDarkTheme() ? 0.79 : 0.61);
    }

    MIcon().drawIcon(this->_icon, &painter, QRect(10, 10, 16, 16), nullptr,  QIcon::State::Off);

    this->_drawText(&painter);
}


void TabItem::_drawSelectedBackground(QPainter *painter)
{
    int w = this->width();
    int h = this->height();
    int r = this->borderRadius;
    int d = 2 * r;

    bool isDark = isDarkTheme();

    QPainterPath *path = new QPainterPath();
    path->arcMoveTo(1, h - d - 1, d, d, 225);
    path->arcTo(1, h - d - 1, d, d, 225, -45);
    path->lineTo(1, r);
    path->arcTo(1, 1, d, d, -180, -90);
    path->lineTo(w - r, 1);
    path->arcTo(w - d - 1, 1, d, d, 90, -90);
    path->lineTo(w - 1, h - r);
    path->arcTo(w - d - 1, h - d - 1, d, d, 0, -45);

    QColor topBorderColor = QColor(0, 0, 0, 20);
    if(isDark){
        if(this->isPressed){
            topBorderColor = QColor(255, 255, 255, 18);
        }else if(this->isHover){
            topBorderColor = QColor(255, 255, 255, 13);
        }
    }else{
        topBorderColor = QColor(0, 0, 0, 16);
    }

    painter->strokePath(*path, topBorderColor);

    QPainterPath *path2 = new QPainterPath();
    path2->arcMoveTo(1, h - d - 1, d, d, 225);
    path2->arcTo(1, h - d - 1, d, d, 225, 45);
    path2->lineTo(w - r - 1, h - 1);
    path2->arcTo(w - d - 1, h - d - 1, d, d, 270, 45);

    QColor bottomBorderColor = topBorderColor;
    if(!isDark){
        bottomBorderColor = QColor(0, 0, 0, 63);
    }

    painter->strokePath(*path2, bottomBorderColor);

    painter->setPen(Qt::NoPen);

    QRect rect = this->rect().adjusted(1, 1, -1, -1);
    painter->setBrush(isDark ? this->darkSelectedBackgroundColor : this->lightSelectedBackgroundColor);
    painter->drawRoundedRect(rect, r, r);
}



void TabItem::_drawNotSelectedBackground(QPainter *painter)
{
    if(!(this->isPressed || this->isHover)){
        return;
    }

    bool isDark = isDarkTheme();

    QColor color;
    if(this->isPressed){
        color = isDark ? QColor(255, 255, 255, 12) : QColor(0, 0, 0, 7);
    }else{
        color = isDark ? QColor(255, 255, 255, 15) : QColor(0, 0, 0, 10);
    }

    painter->setBrush(color);
    painter->setPen(Qt::NoPen);
    painter->drawRoundedRect(this->rect().adjusted(1, 1, -1, -1), this->borderRadius, this->borderRadius);
}


void TabItem::_drawText(QPainter *painter)
{
    //qDebug() << this->width();
    int tw = this->fontMetrics().width(this->text());

    int dw;
    QRectF rect;
    if(this->icon().isNull()){
        dw = this->closeButton->isVisible() ? 47 : 20;
        rect = QRectF(10, 0, this->width() - dw, this->height());
    }else{
        dw = this->closeButton->isVisible() ? 70 : 45;
        rect = QRectF(33, 0, this->width() - dw, this->height());
    }

    QPen pen = QPen();
    QColor color = isDarkTheme() ? Qt::white : Qt::black;
    color = this->textColor.isValid() ? this->textColor : color;
    int rw = rect.width();

    pen.setColor(color);

    /*
    QLinearGradient gradient;
    if(tw > rw){
        gradient = QLinearGradient(rect.x(), 0, tw + rect.x(), 0);
        gradient.setColorAt(0, color);
        gradient.setColorAt(qMax(0, (rw - 10) / tw), color);
        gradient.setColorAt(qMax(0, rw / tw), Qt::transparent);
        gradient.setColorAt(1, Qt::transparent);
        pen.setBrush(QBrush(gradient));
    }else{
        pen.setColor(color);
    }
    */
   
    painter->setPen(pen);
    painter->setFont(this->font());
    painter->drawText(rect, Qt::AlignVCenter | Qt::AlignLeft, this->text());
}


TabBar::TabBar(QWidget *parent) : SingleDirectionScrollArea(parent, Qt::Horizontal)
{
    this->items = QList<TabItem*>();
    this->itemMap = QMap<QString, TabItem*>();

    this->_currentIndex = -1;

    this->_isMovable = false;
    this->_isScrollable = false;
    this->_isTabShadowEnabled = true;

    this->_tabMaxWidth = 240;
    this->_tabMinWidth = 64;

    this->dragPos = QPoint();
    this->isDraging = false;

    this->lightSelectedBackgroundColor = QColor(249, 249, 249);
    this->darkSelectedBackgroundColor = QColor(40, 40, 40);
    this->closeButtonDisplayMode = TabCloseButtonDisplayMode::ALWAYS;

    this->view = new QWidget(this);
    this->hBoxLayout = new QHBoxLayout(this->view);
    this->itemLayout = new QHBoxLayout();
    this->widgetLayout = new QHBoxLayout();

    FluentIcon *icon = new FluentIcon();
    icon->setIconName(QString("ADD"));
    this->addButton = new TabToolButton(icon, this);

    this->__initWidget();
}


void TabBar::__initWidget()
{
    this->setFixedHeight(46);
    this->setWidget(this->view);
    this->setWidgetResizable(true);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->hBoxLayout->setSizeConstraint(QHBoxLayout::SetMaximumSize);

    connect(this->addButton, &TabToolButton::clicked, this, [this](){
        emit(this->tabAddRequested());
    });

    this->view->setObjectName(QString("view"));
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("TAB_VIEW"), Theme::AUTO);
    FluentStyleSheet().apply(this->view, FluentStyleSheetMap.value("TAB_VIEW"), Theme::AUTO);

    this->__initLayout();
}


void TabBar::__initLayout()
{
    this->hBoxLayout->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    this->itemLayout->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    this->widgetLayout->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    this->itemLayout->setContentsMargins(5, 5, 5, 5);
    this->widgetLayout->setContentsMargins(0, 0, 0, 0);
    this->hBoxLayout->setContentsMargins(0, 0, 0, 0);

    this->itemLayout->setSizeConstraint(QHBoxLayout::SetMinAndMaxSize);

    this->hBoxLayout->setSpacing(0);
    this->itemLayout->setSpacing(0);

    this->hBoxLayout->addLayout(this->itemLayout);
    this->hBoxLayout->addSpacing(3);

    this->widgetLayout->addWidget(this->addButton, 0, Qt::AlignLeft);
    this->hBoxLayout->addLayout(this->widgetLayout);
    this->hBoxLayout->addStretch(1);

}


void TabBar::setAddButtonVisible(bool isVisible)
{
    this->addButton->setVisible(isVisible);
}

TabItem *TabBar::addTab(QString routeKey, QString text, QVariant *icon, std::function<void()> onClick)
{
    return this->insertTab(-1, routeKey, text, icon, onClick);
}

TabItem *TabBar::insertTab(int index, QString routeKey, QString text, QVariant *icon, std::function<void()> onClick)
{
    if(this->itemMap.contains(routeKey)){
        QString error = QString("The route key %1 is duplicated.").arg(routeKey);
        throw std::invalid_argument(error.toUtf8());
    }

    if(index == -1){
        index = this->items.length();
    }

    if(index <= this->currentIndex() && this->currentIndex() >= 0){
        this->_currentIndex += 1;
    }

    TabItem *item = new TabItem(text, this->view, icon);
    item->setRouteKey(routeKey);

    int w = this->isScrollable() ? this->tabMaximumWidth() : this->tabMinimumWidth();
    item->setMinimumWidth(w);
    item->setMaximumWidth(this->tabMaximumWidth());

    item->setShadowEnabled(this->isTabShadowEnabled());
    item->setCloseButtonDisplayMode(this->closeButtonDisplayMode);
    item->setSelectedBackgroundColor(this->lightSelectedBackgroundColor, this->darkSelectedBackgroundColor);

    connect(item, &TabItem::pressed, this, &TabBar::_onItemPressed);
    connect(item, &TabItem::closed, this, [this, item](){
        emit(this->tabCloseRequested(this->items.indexOf(item)));
    });

    if(onClick != nullptr){
        connect(item, &TabItem::pressed, this, [onClick](){
            onClick();
        });
    }

    this->itemLayout->insertWidget(index, item, 1);
    this->items.insert(index, item);
    this->itemMap[routeKey] = item;

    if(this->items.length() == 1){
        this->setCurrentIndex(0);
    }

    return item;
}


void TabBar::removeTab(int index)
{
    //qDebug() << "index:" << index << " items length:" << this->items.length();
    if(!(0 <= index && index < this->items.length())){
        return;
    }

    if(index < this->currentIndex()){
        this->_currentIndex -= 1;
    }else if(index == this->currentIndex()){
        if(this->currentIndex() > 0){
            this->setCurrentIndex(this->currentIndex() - 1);
            emit(this->currentChanged(this->currentIndex()));
        }else if(this->items.length() == 1){
            this->_currentIndex = -1;
        }else{
            this->setCurrentIndex(1);
            this->_currentIndex = 0;
            emit(this->currentChanged(0));
        }
    }

    TabItem *item = this->items.takeLast(); 

    this->itemMap.remove(item->routeKey());
    this->hBoxLayout->removeWidget(item);
    qrouter->remove(item->routeKey());
    item->deleteLater();

    this->update();

}


void TabBar::removeTabByKey(QString routeKey)
{
    if(!this->itemMap.contains(routeKey)){
        return;
    }

    this->removeTab(this->items.indexOf(this->tab(routeKey)));
}


void TabBar::setCurrentIndex(int index)
{
    if(index == this->_currentIndex){
        return;
    }

    if(this->currentIndex() >= 0){
        this->items[this->currentIndex()]->setSelected(false);
    }

    this->_currentIndex = index;
    this->items[index]->setSelected(true);
}


void TabBar::setCurrentTab(QString routeKey)
{
    if(!this->itemMap.contains(routeKey)){
        return;
    }

    this->setCurrentIndex(this->items.indexOf(this->tab(routeKey)));
}

int TabBar::currentIndex()
{
    return this->_currentIndex;
}

TabItem *TabBar::currentTab()
{
    return this->tabItem(this->currentIndex());
}


void TabBar::_onItemPressed()
{
    for(int i = 0; i < this->items.length(); i++){
        this->items.at(i)->setSelected(this->items.at(i) == this->sender());
    }

    int index = this->items.indexOf((TabItem *)this->sender());
    emit(this->tabBarClicked(index));

    if(index != this->currentIndex()){
        this->setCurrentIndex(index);
        emit(this->currentChanged(index));
    }
}


void TabBar::setCloseButtonDisplayMode(TabCloseButtonDisplayMode mode)
{
    if(mode == this->closeButtonDisplayMode){
        return;
    }

    this->closeButtonDisplayMode = mode;
    for(int i = 0; i < this->items.length(); i++){
        this->items.at(i)->setCloseButtonDisplayMode(mode);
    }
}


TabItem *TabBar::tabItem(int index)
{
    return this->items[index];
}

TabItem *TabBar::tab(QString routeKey)
{
    return this->itemMap.value(routeKey, nullptr);
}

QRect TabBar::tabRegion()
{
    return this->itemLayout->geometry();
}   

QRect TabBar::tabRect(int index)
{
    int x = 0;
    for(int i = 0; i < index; i++){
        x += this->tabItem(i)->width();
    }

    QRect rect = this->tabItem(index)->geometry();
    rect.moveLeft(x);
    return rect;
}

QString TabBar::tabText(int index)
{
    return this->tabItem(index)->text();
}

QIcon TabBar::tabIcon(int index)
{
    return this->tabItem(index)->icon();
}



QString TabBar::tabToolTip(int index)
{
    return this->tabItem(index)->toolTip();
}

void TabBar::setTabsClosable(bool isClosable)
{
    if(isClosable){
        this->setCloseButtonDisplayMode(TabCloseButtonDisplayMode::ALWAYS);
    }else{
        this->setCloseButtonDisplayMode(TabCloseButtonDisplayMode::NEVER);
    }
}

bool TabBar::tabsClosable()
{
    return this->closeButtonDisplayMode != TabCloseButtonDisplayMode::NEVER;
}

void TabBar::setTabIcon(int index, QVariant *icon)
{
    this->tabItem(index)->setIcon(icon);
}

void TabBar::setTabText(int index, QString text)
{
    this->tabItem(index)->setText(text);
}

void TabBar::setTabVisible(int index, bool isVisible)
{
    this->tabItem(index)->setVisible(isVisible);

    if(isVisible && this->currentIndex() < 0){
        this->setCurrentIndex(0);
    }else if(!isVisible){
        if(this->currentIndex() > 0){
            this->setCurrentIndex(this->currentIndex() - 1);
            emit(this->currentChanged(this->currentIndex()));
        }else if(this->items.length() == 1){
            this->_currentIndex = -1;
        }else{
            this->setCurrentIndex(1);
            this->_currentIndex = 0;
            emit(this->currentChanged(0));
        }
    }
}


void TabBar::setTabTextColor(int index, QColor color)
{
    this->tabItem(index)->setTextColor(color);
}


void TabBar::setTabToolTip(int index, QString toolTip)
{
    this->tabItem(index)->setToolTip(toolTip);
}


void TabBar::setTabSelectedBackgroundColor(QColor light, QColor dark)
{
    this->lightSelectedBackgroundColor = QColor(light);
    this->darkSelectedBackgroundColor = QColor(dark);

    for(int i = 0; i < this->items.length(); i++){
        this->items.at(i)->setSelectedBackgroundColor(light, dark);
    }
}


void TabBar::setTabShadowEnabled(bool isEnabled)
{
    if(isEnabled == this->isTabShadowEnabled()){
        return;
    }

    this->_isTabShadowEnabled = isEnabled;
    for(int i = 0; i < this->items.length(); i++){
        this->items.at(i)->setShadowEnabled(isEnabled);
    }
}

bool TabBar::isTabShadowEnabled()
{
    return this->_isTabShadowEnabled;
}


void TabBar::paintEvent(QPaintEvent *event)
{
    QPainter painter(this->viewport());
    painter.setRenderHints(QPainter::Antialiasing);

    QColor color;
    if(isDarkTheme()){
        color = QColor(255, 255, 255, 21);
    }else{
        color = QColor(0, 0, 0, 15);
    }

    painter.setPen(color);

    for(int i = 0; i < this->items.length(); i++){
        TabItem *item = this->items.at(i);
        bool canDraw = !(item->isHover || item->isSelected);
        if(i < this->items.length() - 1){
            TabItem *nextItem = this->items.at(i + 1);
            if(nextItem->isHover || nextItem->isSelected){
                canDraw = false;
            }
        }

        if(canDraw){
            int x = item->geometry().right();
            int y = this->height() / 2 - 8;
            painter.drawLine(x, y, x, y + 16);
        }
    }
}

void TabBar::setMovable(bool movable)
{
    this->_isMovable = movable;
}

bool TabBar::isMovable()
{
    return this->_isMovable;
}

void TabBar::setScrollable(bool scrollable)
{
    this->_isScrollable = scrollable;
    int w = scrollable ? this->_tabMaxWidth : this->_tabMinWidth;
    for(int i = 0; i < this->items.length(); i++){
        TabItem *item = this->items.at(i);
        item->setMinimumWidth(w);
    }
}


void TabBar::setTabMaximumWidth(int width)
{
    qDebug() << width;
    if(width == this->_tabMaxWidth){
        return;
    }

    this->_tabMaxWidth = width;
    for(int i = 0; i < this->items.length(); i++){
        TabItem *item = this->items.at(i);
        item->setMaximumWidth(width);
    }
}


void TabBar::setTabMinimumWidth(int width)
{
    if(width == this->_tabMinWidth){
        return;
    }

    this->_tabMinWidth = width;
    if(!this->isScrollable()){
        for(int i = 0; i < this->items.length(); i++){
            TabItem *item = this->items.at(i);
            item->setMinimumWidth(width);
        }
    }
}


int TabBar::tabMaximumWidth()
{
    return this->_tabMaxWidth;
}

int TabBar::tabMinimumWidth()
{
    return this->_tabMinWidth;
}

bool TabBar::isScrollable()
{
    return this->_isScrollable;
}

int TabBar::count()
{
    return this->items.length();
}

void TabBar::mousePressEvent(QMouseEvent *event)
{
    SingleDirectionScrollArea::mousePressEvent(event);
    if(!this->isMovable() || event->button() != Qt::LeftButton || !this->itemLayout->geometry().contains(event->pos())){
        return;
    }

    this->dragPos = event->pos();
}


void TabBar::mouseMoveEvent(QMouseEvent *event)
{
    SingleDirectionScrollArea::mouseMoveEvent(event);

    if(!this->isMovable() || this->count() <= 1 || !this->itemLayout->geometry().contains(event->pos())){
        return;
    }

    int index = this->currentIndex();
    TabItem *item = this->tabItem(index);
    int dx = event->pos().x() - this->dragPos.x();
    this->dragPos = event->pos();

    if(index == 0 && dx < 0 && item->x() <= 0){
        return;
    }

    if(index == this->count() - 1 && dx > 0 and item->geometry().right() >= this->itemLayout->sizeHint().width()){
        return;
    }

    item->move(item->x() + dx, item->y());
    this->isDraging = true;
    int siblingIndex;
    if(dx < 0 && index > 0){
        siblingIndex = index - 1;

        if(item->x() < this->tabItem(siblingIndex)->geometry().center().x()){
            this->_swapItem(siblingIndex);
        }
    }else if(dx > 0 && index < this->count() - 1){
        siblingIndex = index + 1;
        if(item->geometry().right() > this->tabItem(siblingIndex)->geometry().center().x()){
            this->_swapItem(siblingIndex);
        }
    }
}


void TabBar::mouseReleaseEvent(QMouseEvent *e)
{
    SingleDirectionScrollArea::mouseReleaseEvent(e);

    if(!this->isMovable() || !this->isDraging){
        return;
    }

    this->isDraging = false;

    TabItem *item = this->tabItem(this->currentIndex());
    int x = this->tabRect(this->currentIndex()).x();
    int duration = qAbs(item->x() - x) * 250 / item->width();
    item->slideTo(x, duration);
    connect(item->slideAni, &QPropertyAnimation::finished, this, &TabBar::_adjustLayout);
}

void TabBar::_adjustLayout()
{
    this->sender()->disconnect();

    for(int i = 0; i < this->items.length(); i++){
        TabItem *item = this->items.at(i);
        this->itemLayout->removeWidget(item);
    }

    
    for(int i = 0; i < this->items.length(); i++){
        TabItem *item = this->items.at(i);
        this->itemLayout->addWidget(item);
    }
    
}


void TabBar::_swapItem(int index)
{
    //QList<TabItem *> items = this->items;
    TabItem *swappedItem = this->tabItem(index);
    int x = this->tabRect(this->currentIndex()).x();
    //qDebug() << x;

    // 假设 currentIndex() 返回当前选中项的索引
    int currentIdx = currentIndex();
    int otherIdx = index; // 这是你想交换的另一个项的索引

    // 确保索引在有效范围内
    if (currentIdx >= 0 && currentIdx < this->items.size() && otherIdx >= 0 && otherIdx < this->items.size()) {
        // 使用 std::swap 来交换两个元素
        //std::swap(items[currentIdx], items[otherIdx]);
        //qDebug() << "currentIdx:" << currentIdx << "  otherIdx:" << otherIdx; 


        for(int i = 0; i < this->items.length(); i++){
            TabItem *item = this->items.at(i);
            //qDebug() << item->_routeKey;
        }

        this->items.swapItemsAt(currentIdx, otherIdx);

        for(int i = 0; i < this->items.length(); i++){
            TabItem *item = this->items.at(i);
            //qDebug() << item->_routeKey;
        }
    }

    this->_currentIndex = index;
    swappedItem->slideTo(x);
}