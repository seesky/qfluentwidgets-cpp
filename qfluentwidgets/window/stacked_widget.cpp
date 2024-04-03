#include "stacked_widget.h"


StackedWidget::StackedWidget(QWidget *parent) : QStackedWidget(parent)
{
    QWidget *container = new QWidget();
    this->hBoxLayout = new QHBoxLayout(container);
    this->view = new PopUpAniStackedWidget(this);

    this->hBoxLayout->setContentsMargins(0, 0, 0, 0);
    this->hBoxLayout->addWidget(this->view);

    connect(this->view, &PopUpAniStackedWidget::currentChanged, this, [this](int a){
        emit(this->currentChanged(a));
    });

    QStackedWidget::addWidget(container);
    //this->addWidget(container);

    this->setAttribute(Qt::WA_StyledBackground);
}


void StackedWidget::addWidget(QWidget *widget)
{
    this->view->addWidget(widget, 0, 76);
}

QWidget *StackedWidget::widget(int index)
{
    return this->view->widget(index);
}

void StackedWidget::setCurrentWidget(QWidget *widget, bool popOut)
{
    auto _widget = qobject_cast<QAbstractScrollArea*>(widget);
    if(_widget != nullptr){
        _widget->verticalScrollBar()->setValue(0);
    }

    if(!popOut){
        this->view->setCurrentWidget(widget, false, false, 300, QEasingCurve::OutQuad);
    }else{
        this->view->setCurrentWidget(widget, true, false, 200, QEasingCurve::InQuad);
    }
}

void StackedWidget::setCurrentIndex(int index, bool popOut = true)
{
    this->setCurrentWidget(this->view->widget(index), popOut);
}


int StackedWidget::currentIndex()
{
    return this->view->currentIndex();
}

QWidget *StackedWidget::currentWidget()
{
    return this->view->currentWidget();
}

int StackedWidget::indexOf(QWidget *widget)
{
    return this->view->indexOf(widget);
}

int StackedWidget::count()
{
    return this->view->count();
}

