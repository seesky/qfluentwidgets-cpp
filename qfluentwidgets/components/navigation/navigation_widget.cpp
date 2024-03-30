#include "navigation_widget.h"

NavigationWidget::NavigationWidget(bool isSelectable, QWidget *parent) : QWidget(parent)
{
    this->isCompacted = true;
    this->isSelected = false;
    this->isPressed = false;
    this->isEnter = false;
    this->isSelectable = isSelectable;
    this->treeParent = nullptr;
    this->nodeDepth = 0;
    this->setFixedSize(40, 36);
}


void NavigationWidget::enterEvent(QEvent *event)
{
    this->isEnter = true;
    this->update();
}

void NavigationWidget::leaveEvent(QEvent *event)
{
    this->isEnter = false;
    this->isPressed = false;
    this->update();
}

void NavigationWidget::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    this->isPressed = true;
    this->update();
}

void NavigationWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
    this->isPressed = false;
    this->update();
    emit(this->clicked(true));
}


void NavigationWidget::click()
{
    emit(this->clicked(true));
}


void NavigationWidget::setCompacted(bool isCompacted)
{
    if(isCompacted == this->isCompacted){
        return;
    }

    this->isCompacted = isCompacted;
    if(isCompacted){
        this->setFixedSize(40, 36);
    }else{
        this->setFixedSize(EXPAND_WIDTH, 36);
    }

    this->update();
}


void NavigationWidget::setSelected(bool isSelected)
{
    if(!this->isSelectable){
        return;
    }

    this->isSelected = isSelected;
    this->update();
    emit(this->selectedChanged(isSelected));
}



NavigationPushButton::NavigationPushButton(QVariant *icon, QString text, bool isSelectable, QWidget *parent) : NavigationWidget(isSelectable, parent)
{
    this->_icon = icon;
    this->_text = text;

    Font().setFont(this, 14, QFont::Normal);
}


QString NavigationPushButton::text()
{
    return this->_text;
}

void NavigationPushButton::setText(QString text)
{
    this->_text = text;
    this->update();
}


QIcon NavigationPushButton::icon()
{
    return MIcon().toQIcon(this->_icon);
}


void NavigationPushButton::setIcon(QVariant *icon)
{
    this->_icon = icon;
    this->update();
}   


QMargins NavigationPushButton::_margins()
{
    return QMargins(0, 0, 0, 0);
}


bool NavigationPushButton::_canDrawIndicator()
{
    return this->isSelected;
}


void NavigationPushButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
    painter.setPen(Qt::NoPen);

    if(this->isPressed){
        painter.setOpacity(0.7);
    }

    if(!this->isEnabled()){
        painter.setOpacity(0.4);
    }

    int c = isDarkTheme() ? 255 : 0;
    QMargins m = this->_margins();
    int pl = m.left();
    int pr = m.right();
    QRect globalRect(this->mapToGlobal(QPoint()), this->size());

    if(this->_canDrawIndicator()){
        painter.setBrush(QColor(c, c, c, this->isEnter ? 6 : 10));
        painter.drawRoundedRect(this->rect(), 5, 5);

        painter.setBrush(*(ThemeColor().themeColor()));
        painter.drawRoundedRect(pl, 10, 3, 16, 1.5, 1.5);
    }else if(this->isEnter && this->isEnabled() && globalRect.contains(QCursor::pos())){
        painter.setBrush(QColor(c, c, c, 10));
        painter.drawRoundedRect(this->rect(), 5, 5);
    }

    MIcon().drawIcon(this->_icon, &painter, QRect(11.5 + pl, 10, 16, 16), nullptr, QIcon::State::Off);

    if(this->isCompacted){
        return;
    }

    painter.setFont(this->font());
    painter.setPen(QColor(c, c, c));
    int left = !this->icon().isNull() ? 44 + pl : pl + 16;
    painter.drawText(QRectF(left, 0, this->width() - 13 - left - pr, this->height()), Qt::AlignVCenter, this->text());
}


NavigationToolButton::NavigationToolButton(QVariant *icon, QWidget *parent) : NavigationPushButton(icon, QString(""), false, parent)
{

}

void NavigationToolButton::setCompacted(bool isCompacted)
{
    this->setFixedSize(40, 36);
}

/*
void NavigationToolButton::setText(QString text)
{
    this->setFixedSize(40, 36);
}
*/

NavigationSeparator::NavigationSeparator(QWidget *parent) : NavigationWidget(false, parent)
{
    this->setCompacted(true);
}


void NavigationSeparator::setCompacted(bool isCompacted)
{
    if(isCompacted){
        this->setFixedSize(48, 3);
    }else{
        this->setFixedSize(EXPAND_WIDTH + 10, 3);
    }
    this->update();
}

void NavigationSeparator::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    int c = isDarkTheme() ? 255 : 0;
    QPen pen(QColor(c, c, c, 15));
    pen.setCosmetic(true);
    painter.setPen(pen);
    painter.drawLine(0, 1, this->width(), 1);
}



NavigationTreeItem::NavigationTreeItem(QVariant *icon, QString text, bool isSelectable, QWidget *parent) : NavigationPushButton(icon, text, isSelectable, parent)
{
    this->_arrowAngle = 0;
    this->rotateAni = new QPropertyAnimation(this, "arrowAngle", this);
}

void NavigationTreeItem::setExpanded(bool isExpanded)
{
    this->rotateAni->stop();
    this->rotateAni->setEndValue(isExpanded ? 180 : 0);
    this->rotateAni->setDuration(150);
    this->rotateAni->start();
}

void NavigationTreeItem::mouseReleaseEvent(QMouseEvent *event)
{
    NavigationPushButton::mouseReleaseEvent(event);
    bool clickArrow = QRectF(this->width() - 30, 8, 20, 20).contains(event->pos());
    emit(this->itemClicked(true, clickArrow && !((NavigationTreeWidget*)this->parent())->isLeaf()));  //TODO:特殊关注
    this->update();
}


bool NavigationTreeItem::_canDrawIndicator()
{
    NavigationTreeWidget *p = (NavigationTreeWidget *)(this->parent());
    if(p->isLeaf() || p->isSelected){
        return p->isSelected;
    }

    for(int i = 0; i < p->treeChildren.length(); i++){
        if(p->treeChildren.at(i)->itemWidget->_canDrawIndicator() && !p->treeChildren.at(i)->isVisible()){
            return true;
        }
    }

    return false;
}


QMargins NavigationTreeItem::_margins()
{
    NavigationTreeWidget *p = static_cast<NavigationTreeWidget *>(this->parent());
    return QMargins(p->nodeDepth * 28, 0, p->treeChildren.isEmpty() ? 0 : 20, 0);
}


void NavigationTreeItem::paintEvent(QPaintEvent *event)
{
    NavigationPushButton::paintEvent(event);
    if(this->isCompacted || ((NavigationTreeWidget*)(this->parent()))->treeChildren.isEmpty()){ //TODO:特殊关注
        return;
    }

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    if(this->isPressed){
        painter.setOpacity(0.7);
    }

    if(!this->isEnabled()){
        painter.setOpacity(0.4);
    }

    painter.translate(this->width() - 20, 18);
    painter.rotate(this->getArrowAngle());

    FluentIcon *icon = new FluentIcon();
    icon->setIconName(QString("ARROW_DOWN"));
    icon->render(&painter, QRect(-5, -5, 9.6, 9.6), Theme::AUTO, 0, nullptr);
}


float NavigationTreeItem::getArrowAngle()
{
    return this->_arrowAngle;
}

void NavigationTreeItem::setArrowAngle(float angle)
{
    this->_arrowAngle = angle;
    this->update();
}



NavigationTreeWidget::NavigationTreeWidget(QVariant *icon, QString text, bool isSelectable, QWidget *parent) :NavigationTreeWidgetBase(isSelectable, parent)
{
    this->treeChildren = QList<NavigationTreeWidget*>();
    this->isExpanded = false;
    this->_icon = icon;

    this->itemWidget = new NavigationTreeItem(icon, text, isSelectable, this);
    this->vBoxLayout = new QVBoxLayout(this);
    this->expandAni = new QPropertyAnimation(this, "geometry", this);

    this->__initWidget();
}

void NavigationTreeWidget::__initWidget()
{
    this->vBoxLayout->setSpacing(4);
    this->vBoxLayout->setContentsMargins(0, 0, 0, 0);
    this->vBoxLayout->addWidget(this->itemWidget, 0, Qt::AlignTop);

    connect(this->itemWidget, &NavigationTreeItem::itemClicked, this, &NavigationTreeWidget::_onClicked);
    this->setAttribute(Qt::WA_TranslucentBackground);
    connect(this->expandAni, &QPropertyAnimation::valueChanged, this, [this](QVariant g){ //TODO:特殊关注
        this->setFixedSize(g.value<QRect>().size());  
    });


    connect(this->expandAni, &QPropertyAnimation::valueChanged, this, [this](){ //TODO:特殊关注
        emit(this->expanded());
    });

}



void NavigationTreeWidget::addChild(NavigationTreeWidgetBase *child)
{
    this->insertChild(-1, child);
}

QString NavigationTreeWidget::text()
{
    return this->itemWidget->text();
}

QIcon NavigationTreeWidget::icon()
{
    return this->itemWidget->icon();
}

void NavigationTreeWidget::setText(QString text)
{
    this->itemWidget->setText(text);
}

void NavigationTreeWidget::setIcon(QVariant *icon)
{
    this->itemWidget->setIcon(icon);
}

void NavigationTreeWidget::setFont(QFont font)
{
    NavigationTreeWidgetBase::setFont(font);
    this->itemWidget->setFont(font);
}


NavigationTreeWidget *NavigationTreeWidget::clone()
{
    NavigationTreeWidget *root = new NavigationTreeWidget(this->_icon, this->text(), this->isSelectable, (QWidget*)this->parent());  //TODO:特殊关注
    root->setSelected(this->isSelected);
    root->setFixedSize(this->size());
    root->nodeDepth = this->nodeDepth;

    connect(root, &NavigationTreeWidget::clicked, [this](bool b){
        emit(this->clicked(b));
    });

    connect(this, &NavigationTreeWidget::selectedChanged, root, &NavigationTreeWidget::setSelected);

    for(int i = 0; i < this->treeChildren.length(); i++){
        root->addChild(this->treeChildren.at(i)->clone());
    }

    return root;
}


int NavigationTreeWidget::suitableWidth()
{
    QMargins m = this->itemWidget->_margins();
    int left = !this->icon().isNull() ? 57 + m.left() : m.left() + 29;
    int tw = this->itemWidget->fontMetrics().boundingRect(this->text()).width();
    return left + tw + m.right();
}


void NavigationTreeWidget::insertChild(int index, NavigationWidget *child)
{
    if(this->treeChildren.contains((NavigationTreeWidget*)child)){ //TODO:特殊关注
        return;
    }

    child->treeParent = this;
    child->nodeDepth = this->nodeDepth + 1;
    child->setVisible(this->isExpanded);
    connect(((NavigationTreeWidget*)child)->expandAni, &QPropertyAnimation::valueChanged, this, [this](){  //TODO:特殊关注类型转换
        this->setFixedSize(this->sizeHint());
    });

    connect(((NavigationTreeWidget*)child)->expandAni, &QPropertyAnimation::valueChanged, this, [this](){
        emit(this->expanded());
    });
 
    NavigationTreeWidget *p = static_cast<NavigationTreeWidget *>(this->treeParent);  //TODO:特殊关注类型转换
    while(p != nullptr){
        connect(((NavigationTreeWidget*)child)->expandAni, &QPropertyAnimation::valueChanged, this, [this](QVariant g){ //TODO:特殊关注
            g.value<NavigationTreeWidget*>()->setFixedSize(g.value<NavigationTreeWidget*>()->sizeHint());  
        });
        p = (NavigationTreeWidget*)p->treeParent;
    }

    if(index < 0){
        index = this->treeChildren.length();
    }

    index += 1;
    this->treeChildren.insert(index, (NavigationTreeWidget*)child);
    this->vBoxLayout->insertWidget(index, child, 0, Qt::AlignTop);
}


void NavigationTreeWidget::removeChild(NavigationWidget *child)
{
    this->treeChildren.removeOne((NavigationTreeWidget*)child);
    this->vBoxLayout->removeWidget(child);
}

QList<NavigationTreeWidget*> NavigationTreeWidget::childItems()
{
    return this->treeChildren;
}

void NavigationTreeWidget::setExpanded(bool isExpanded, bool ani)
{
    if(isExpanded == this->isExpanded){
        return;
    }

    this->isExpanded = isExpanded;
    this->itemWidget->setExpanded(isExpanded);

    for(int i = 0; i < this->treeChildren.length(); i++){
        this->treeChildren.at(i)->setVisible(isExpanded);
        this->treeChildren.at(i)->setFixedSize(this->treeChildren.at(i)->sizeHint());
    }

    if(ani){
        this->expandAni->stop();
        this->expandAni->setStartValue(this->geometry());
        this->expandAni->setEndValue(QRect(this->pos(), this->sizeHint()));
        this->expandAni->setDuration(120);
        this->expandAni->setEasingCurve(QEasingCurve::OutQuad);
        this->expandAni->start();
    }else{
        this->setFixedSize(this->sizeHint());
    }
}


bool NavigationTreeWidget::isRoot()
{
    return this->treeParent == nullptr;
}

bool NavigationTreeWidget::isLeaf()
{
    return this->treeChildren.length() == 0;
}

void NavigationTreeWidget::setSelected(bool isSelected)
{
    NavigationTreeWidgetBase::setSelected(isSelected);
    this->itemWidget->setSelected(isSelected);
}

void NavigationTreeWidget::mouseReleaseEvent(QMouseEvent *event)
{

}


void NavigationTreeWidget::setCompacted(bool isCompacted)
{
    NavigationTreeWidgetBase::setCompacted(isCompacted);
    this->itemWidget->setCompacted(isCompacted);
}

void NavigationTreeWidget::_onClicked(bool triggerByUser, bool clickArrow)
{
    if(!this->isCompacted){
        if(this->isSelectable && !this->isSelected && !clickArrow){
            this->setExpanded(true, true);
        }else{
            this->setExpanded(!this->isExpanded, true);
        }
    }

    if(!clickArrow || this->isCompacted){
        emit(this->clicked(triggerByUser));
    }
}


NavigationAvatarWidget::NavigationAvatarWidget(QString name, QVariant *avatar, QWidget *parent) : NavigationWidget(false, parent)
{
    this->name = name;
    this->setAvatar(avatar);
    Font().setFont(this, 14, QFont::Normal);
}

void NavigationAvatarWidget::setName(QString name)
{
    this->name = name;
    this->update();
}


void NavigationAvatarWidget::setAvatar(QVariant *avatar)
{
    if(avatar->canConvert<QString>()){
        QImage _avatar = QImage(avatar->value<QString>());
        this->avatar = _avatar.scaled(24, 24, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }else if(avatar->canConvert<QPixmap>()){
        QImage _avatar = avatar->value<QPixmap>().toImage();
        this->avatar = _avatar.scaled(24, 24, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }else{
        this->avatar = avatar->value<QImage>().scaled(24, 24, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }
}

void NavigationAvatarWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    if(this->isPressed){
        painter.setOpacity(0.7);
    }

    if(this->isEnter){
        int c = isDarkTheme() ? 255 : 0;
        painter.setBrush(QColor(c, c, c, 10));
        painter.drawRoundedRect(this->rect(), 5, 5);
    }

    painter.setBrush(QBrush(this->avatar));
    painter.translate(8, 6);
    painter.drawEllipse(0, 0, 24, 24);
    painter.translate(-8, -6);

    if(!this->isCompacted){
        painter.setPen(isDarkTheme() ? Qt::white : Qt::black);
        painter.setFont(this->font());
        painter.drawText(QRect(44, 0, 255, 36), Qt::AlignVCenter, this->name);
    }
}


NavigationFlyoutMenu::NavigationFlyoutMenu(NavigationTreeWidget *tree, QWidget *parent) : ScrollArea(parent)
{
    this->view = new QWidget(this);

    this->treeWidget = tree;
    this->treeChildren = QList<NavigationTreeWidget*>();

    this->vBoxLayout = new QVBoxLayout(this->view);

    this->setWidget(this->view);
    this->setWidgetResizable(true);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setStyleSheet(QString("ScrollArea{border:none;background:transparent}"));
    this->view->setStyleSheet(QString("QWidget{border:none;background:transparent}"));

    this->vBoxLayout->setSpacing(5);
    this->vBoxLayout->setContentsMargins(5, 8, 5, 8);

    for(int i = 0; i < this->treeChildren.length(); i++){
        NavigationTreeWidget *node = this->treeChildren.at(i)->clone();
        connect(node, &NavigationTreeWidget::expanded, this, [this](){
            this->_adjustViewSize(true);
        });

        this->treeChildren.append(node);
        this->vBoxLayout->addWidget(node);
    }

    this->_initNode(this);
    this->_adjustViewSize(false);
}

void NavigationFlyoutMenu::_initNode(NavigationFlyoutMenu *root)
{
    for(int i = 0; i < root->treeChildren.length(); i++){
        root->treeChildren.at(i)->nodeDepth -= 1;
        root->treeChildren.at(i)->setCompacted(false);

        if(root->treeChildren.at(i)->isLeaf()){
            connect(root->treeChildren.at(i), &NavigationTreeWidget::clicked, this->window(), [this](){
                ((Flyout*)this->window())->fadeOut(); //TODO:特殊关注是Flyout类型吗
            });
        }
    }
}


int NavigationFlyoutMenu::_suitableWidth()
{
    int w = 0;
    for(int i = 0; i < this->visibleTreeNodes()->length(); i++){
        if(!this->visibleTreeNodes()->at(i)->isHidden()){
            w = qMax(w, this->visibleTreeNodes()->at(i)->suitableWidth() + 10);
        }
    }

    QWidget *window = (QWidget *)this->window()->parent();
    return qMin(window->width() / 2 -25, w) + 10;
}

QList<NavigationTreeWidget *> *NavigationFlyoutMenu::visibleTreeNodes()
{
    QList<NavigationTreeWidget*> *nodes  = new QList<NavigationTreeWidget*>();
    QQueue<NavigationTreeWidget*> queue = QQueue<NavigationTreeWidget*>();
    queue.append(this->treeChildren);

    while(!queue.isEmpty()){
        NavigationTreeWidget *node = queue.takeFirst();
        queue.pop_front();
        nodes->append(node);
        for(int i = 0; i < node->treeChildren.length(); i++){
            if(!node->treeChildren.at(i)->isHidden()){
                queue.push_back(node->treeChildren.at(i));
            }
        }
    }

    return nodes;
}


void NavigationFlyoutMenu::_adjustViewSize(bool _emit)
{
    int w = this->_suitableWidth();

    for(int i = 0; i < this->visibleTreeNodes()->length(); i++){
        this->visibleTreeNodes()->at(i)->setFixedWidth(w - 10);
        this->visibleTreeNodes()->at(i)->itemWidget->setFixedWidth(w - 10);
    }

    this->view->setFixedSize(w, this->view->sizeHint().height());

    int h = qMin(((QWidget*)this->window()->parent())->height() - 48, this->view->height());

    this->setFixedSize(w, h);

    if(_emit){
        emit(this->expanded());
    }
}