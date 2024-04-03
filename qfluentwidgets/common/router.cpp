#include "router.h"

Router* Router::instance = nullptr;

RouteItem::RouteItem(QStackedWidget *stacked, QString routeKey)
{
    this->stacked = stacked;
    this->routeKey = routeKey;
}

bool RouteItem::__eq__(RouteItem *other)
{
    if(other == nullptr){
        return false;
    }

    return other->stacked == this->stacked && this->routeKey == other->routeKey;
}


StackedHistory::StackedHistory(QStackedWidget *stacked)
{
    this->stacked = stacked;
    this->defaultRouteKey = QString();
    this->history = QList<QString>();
    this->history.append(this->defaultRouteKey);
}

int StackedHistory::__len__()
{
    return this->history.length();
}

bool StackedHistory::isEmpty()
{
    return this->__len__() <= 1;
}

bool StackedHistory::push(QString routeKey)
{
    if(this->history.last() == routeKey){
        return false;
    }

    this->history.append(routeKey);
    return true;
}

void StackedHistory::pop()
{
    if(this->isEmpty()){
        return;
    }

    this->history.pop_back();
    this->goToTop();
}

void StackedHistory::remove(QString routeKey)
{
    if(!this->history.contains(routeKey)){
        return;
    }

    // 删除除第一个元素以外的所有 routeKey 实例  TODO:特别关注
    for (auto it = history.begin() + 1; it != history.end();) {
        if (*it == routeKey) {
            it = history.erase(it);
        } else {
            ++it;
        }
    }

    // 移除重复的相邻元素
    auto last = std::unique(history.begin(), history.end());
    history.erase(last, history.end());

    this->goToTop();
}


QString StackedHistory::top()
{
    return this->history.last();
}

void StackedHistory::setDefaultRouteKey(QString routeKey)
{
    this->defaultRouteKey = routeKey;
    this->history.replace(0, routeKey);
}

void StackedHistory::goToTop()
{
    QWidget *w = this->stacked->findChild<QWidget*>(this->top());
    if((w) != nullptr){
        this->stacked->setCurrentWidget(w);
    }
}

Router::Router(QWidget *parent) : QObject(parent)
{
    instance = nullptr;
    this->history = QList<RouteItem*>();
    this->stackHistories = new QMap<QStackedWidget*, StackedHistory*>();
}


Router* Router::getInstance()
{
    if(instance == nullptr){
        instance = new Router(nullptr);
    }
    return instance;
}

void Router::setDefaultRouteKey(QStackedWidget *stacked, QString routeKey)
{
    if(!this->stackHistories->contains(stacked)){
        this->stackHistories->insert(stacked, new StackedHistory(stacked));
    }

    this->stackHistories->value(stacked)->setDefaultRouteKey(routeKey);
}


void Router::push(QStackedWidget *stacked, QString routeKey)
{
    RouteItem *item = new RouteItem(stacked, routeKey);

    if(!this->stackHistories->contains(stacked)){
        this->stackHistories->insert(stacked, new StackedHistory(stacked));
    }

    bool success = this->stackHistories->value(stacked)->push(routeKey);
    if(success){
        this->history.append(item);
    }

    emit(this->emptyChanged(this->history.isEmpty()));
}


void Router::pop()
{
    if(this->history.isEmpty()){
        return;
    }
    
    RouteItem *item = this->history.takeLast();
    //this->history.pop_back();
    emit(this->emptyChanged(this->history.isEmpty()));
    this->stackHistories->value(item->stacked)->pop();
}

bool Router::remove(QString routeKey) //TODO:特殊关注，不知道对错
{
    // Remove items with the given routeKey
    auto new_end = std::remove_if(history.begin(), history.end(),
                                  [&routeKey](const RouteItem* item) {
                                      return item->routeKey == routeKey;
                                  });
    history.erase(new_end, history.end());

    // Remove duplicate items, keeping the first occurrence
    auto last = std::unique(history.begin(), history.end(),
                            [](const RouteItem* a, const RouteItem* b) {
                                return a->routeKey == b->routeKey;
                            });
    history.erase(last, history.end());

    // Emit the signal for emptyChanged
    emit emptyChanged(history.isEmpty());

// Iterate through the stackHistories to find and remove the routeKey
    QMap<QStackedWidget*, StackedHistory*>::iterator it;
    for (it = stackHistories->begin(); it != stackHistories->end(); ++it) {
        QStackedWidget* stacked = it.key();
        StackedHistory* history = it.value();
        QWidget* w = stacked->findChild<QWidget*>(routeKey);
        if (w) {
            history->remove(routeKey);
            return true;
        }
    }
    return false;
}