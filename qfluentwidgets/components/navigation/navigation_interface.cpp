#include "navigation_interface.h"


NavigationInterface::NavigationInterface(QWidget *parent, bool showMenuButton, bool showReturnButton, bool collapsible) : QWidget(parent)
{
    this->panel = new NavigationPanel(this, false);
    this->panel->setMenuButtonVisible(showMenuButton && collapsible);
    this->panel->setReturnButtonVisible(showReturnButton);
    this->panel->setCollapsible(collapsible);
    this->panel->installEventFilter(this);
    connect(this->panel, &NavigationPanel::displayModeChanged, this, &NavigationInterface::displayModeChanged);

    this->resize(48, this->height());
    this->setMinimumWidth(48);
    this->setAttribute(Qt::WA_TranslucentBackground);
}


NavigationTreeWidget *NavigationInterface::addItem(QString routeKey, QVariant *icon, QString text, std::function<void()> onClick, bool selectable, NavigationItemPosition position, QString tooltip, QString parentRouteKey)
{
    return this->insertItem(-1, routeKey, icon, text, onClick, selectable, position, tooltip, parentRouteKey);
}

void NavigationInterface::addWidget(QString routeKey, NavigationWidget *widget, std::function<void()> onClick, NavigationItemPosition position, QString tooltip, QString parentRouteKey)
{
    this->insertWidget(-1, routeKey, widget, onClick, position, tooltip, parentRouteKey);
}

NavigationTreeWidget *NavigationInterface::insertItem(int index, QString routeKey, QVariant *icon, QString text, std::function<void()> onClick, bool selectable, NavigationItemPosition position, QString tooltip, QString parentRouteKey)
{
    NavigationTreeWidget *w = this->panel->insertItem(index, routeKey, icon, text, onClick, selectable, position, tooltip, parentRouteKey);
    this->setMinimumHeight(this->panel->layoutMinHeight());
    return w;
}

void NavigationInterface::insertWidget(int index, QString routeKey, NavigationWidget *widget, std::function<void()> onClick, NavigationItemPosition position, QString tooltip, QString parentRouteKey)
{
    this->panel->insertWidget(index, routeKey, widget, onClick, position, tooltip, parentRouteKey);
    this->setMinimumHeight(this->panel->layoutMinHeight());
}


void NavigationInterface::addSeparator(NavigationItemPosition position)
{
    this->insertSeparator(-1, position);
}

void NavigationInterface::insertSeparator(int index, NavigationItemPosition position)
{
    this->panel->insertSeparator(index, position);
    this->setMinimumHeight(this->panel->layoutMinHeight());
}

void NavigationInterface::removeWidget(QString routeKey)
{
    this->panel->removeWidget(routeKey);
}

void NavigationInterface::setCurrentItem(QString name)
{
    this->panel->setCurrentItem(name);
}

void NavigationInterface::setExpandWidth(int width)
{
    this->panel->setExpandWidth(width);
}

void NavigationInterface::setMenuButtonVisible(bool isVisible)
{
    this->panel->setMenuButtonVisible(isVisible);
}

void NavigationInterface::setReturnButtonVisible(bool isVisible)
{
    this->panel->setReturnButtonVisible(isVisible);
}

void NavigationInterface::setCollapsible(bool collapsible)
{
    this->panel->setCollapsible(collapsible);
}

bool NavigationInterface::isAcrylicEnabled()
{
    return this->panel->isAcrylicEnabled();
}

void NavigationInterface::setAcrylicEnabled(bool isEnabled)
{
    this->panel->setAcrylicEnabled(isEnabled);
}

NavigationWidget *NavigationInterface::widget(QString routeKey)
{
    return (NavigationWidget *)this->panel->widget(routeKey);
}

bool NavigationInterface::eventFilter(QObject *obj, QEvent *e)
{
    if(obj != this->panel || e->type() != QEvent::Resize){
        return QWidget::eventFilter(obj, e);
    }

    if(this->panel->displayMode != NavigationDisplayMode::MENU){
        QResizeEvent *re = dynamic_cast<QResizeEvent*>(e);
        if(re->oldSize().width() != re->size().width()){
            this->setFixedWidth(re->size().width());
        }
    }

    return QWidget::eventFilter(obj, e);
}

void NavigationInterface::resizeEvent(QResizeEvent *event)
{
    if(event->oldSize().height() != this->height()){
        this->panel->setFixedHeight(this->height());
    }
}