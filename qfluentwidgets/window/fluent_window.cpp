#include "fluent_window.h"

FluentWindowBase::FluentWindowBase(QWidget *parent) : WindowsFramelessWindow(parent)
{
    
    this->isHover = false;
    this->isPressed = false;
    //auto obj = qobject_cast<BackgroundAnimationWidget*>(this);
    BackgroundAnimationWidget* bgaw = new BackgroundAnimationWidget();
    //this->bgColorObject = new BackgroundColorObject(bgaw);
    this->bgColorObject = this;
    this->bgColorObject->_backgroundColor = this->_normalBackgroundColor();
    this->backgroundColorAni = new QPropertyAnimation(this->bgColorObject, "backgroundColor", this);
    this->backgroundColorAni->setDuration(120);
    this->installEventFilter(this);

    connect(qconfig, &QConfig::themeChanged, this, &FluentWindowBase::_updateBackgroundColor);
    
    this->_isMicaEnabled = false;
    this->hBoxLayout = new QHBoxLayout(this);
    this->stackedWidget = new StackedWidget(this);
    this->navigationInterface = nullptr;

    this->hBoxLayout->setSpacing(0);
    this->hBoxLayout->setContentsMargins(0, 0, 0, 0);

     FluentStyleSheet().apply(this->stackedWidget, FluentStyleSheetMap.value("FLUENT_WINDOW"), Theme::AUTO);

     this->setMicaEffectEnabled(true);

    connect(qconfig, &QConfig::themeChangedFinished, this, &FluentWindowBase::_onThemeChangedFinished);
    //TOOD: qconfig.themeChanged.connect(self._updateBackgroundColor)
     //TODO:qconfig.themeChangedFinished.connect(self._onThemeChangedFinished)
}

void FluentWindowBase::addSubInterface(QWidget *_interface, QVariant *icon, QString text, NavigationItemPosition position)
{

}

void FluentWindowBase::switchTo(QWidget *_interface)
{
    this->stackedWidget->setCurrentWidget(_interface, false);
}


void FluentWindowBase::_onCurrentInterfaceChanged(int index)
{
    QWidget *widget = this->stackedWidget->widget(index);
    this->navigationInterface->setCurrentItem(widget->objectName());
    qrouter->push(this->stackedWidget, widget->objectName());

    this->_updateStackedBackground();
}


void FluentWindowBase::_updateStackedBackground()
{
    bool isTransparent = this->stackedWidget->currentWidget()->property("isStackedTransparent").value<bool>();
    if(this->stackedWidget->property("isTransparent").value<bool>() == isTransparent){
        return;
    }

    this->stackedWidget->setProperty("isTransparent", QVariant::fromValue<bool>(isTransparent));
    this->stackedWidget->setStyle(QApplication::style());
}

QColor FluentWindowBase::_normalBackgroundColor()
{
    if(!this->isMicaEffctEnabled()){
        return isDarkTheme() ? QColor(32, 32, 32) : QColor(243, 243, 243);
    }

    return QColor(0, 0, 0, 0);
}

void FluentWindowBase::_onThemeChangedFinished()
{
    if(this->isMicaEffctEnabled()){
        this->windowEffect->setMicaEffect((HWND)(this->winId()), isDarkTheme(), false);
    }
}

void FluentWindowBase::paintEvent(QPaintEvent *event)
{
    WindowsFramelessWindow::paintEvent(event);
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(this->backgroundColor());
    painter.drawRect(this->rect());
}


void FluentWindowBase::setMicaEffectEnabled(bool isEnabled)
{
    this->_isMicaEnabled = isEnabled;

    if(isEnabled){
        this->windowEffect->setMicaEffect((HWND)(this->winId()), isDarkTheme(), false);
    }else{
        this->windowEffect->removeBackgroundEffect((HWND)(this->winId()));
    }

    this->setBackgroundColor(this->_normalBackgroundColor());
}


bool FluentWindowBase::isMicaEffctEnabled()
{
    return this->_isMicaEnabled;
}



bool FluentWindowBase::eventFilter(QObject *obj, QEvent *e)
{
    if(obj == this)
    {
        if(e->type() == QEvent::Type::EnabledChange)
        {
            if(this->isEnabled())
            {
                this->setBackgroundColor(this->_normalBackgroundColor());
            }else{
                this->setBackgroundColor(this->_disabledBackgroundColor());
            }
        }
    }
    return WindowsFramelessWindow::eventFilter(obj, e);
}

void FluentWindowBase::mousePressEvent(QMouseEvent *e)
{
    this->isPressed = true;
    this->_updateBackgroundColor();
    WindowsFramelessWindow::mousePressEvent(e);
}

void FluentWindowBase::mouseReleaseEvent(QMouseEvent *e)
{
    this->isPressed = false;
    this->_updateBackgroundColor();
    WindowsFramelessWindow::mouseReleaseEvent(e);
}

void FluentWindowBase::enterEvent(QEnterEvent *e)
{
    this->isHover = true;
    this->_updateBackgroundColor();
}

void FluentWindowBase::leaveEvent(QEvent *e)
{
    this->isHover = false;
    this->_updateBackgroundColor();
}

void FluentWindowBase::focusInEvent(QFocusEvent *e)
{
    WindowsFramelessWindow::focusInEvent(e);
    this->_updateBackgroundColor();
}



QColor FluentWindowBase::_hoverBackgroundColor()
{
    return this->_normalBackgroundColor();
}

QColor FluentWindowBase::_pressedBackgroundColor()
{
    return this->_normalBackgroundColor();
}

QColor FluentWindowBase::_focusInBackgroundColor()
{
    return this->_normalBackgroundColor();
}


QColor FluentWindowBase::_disabledBackgroundColor()
{
    return this->_normalBackgroundColor();
}


void FluentWindowBase::_updateBackgroundColor()
{
    QColor color;
    if(!this->isEnabled())
    {
        color = this->_disabledBackgroundColor();
    }else if(dynamic_cast<QLineEdit*>(this) != nullptr && this->hasFocus()){
        color = this->_focusInBackgroundColor();
    }else if(this->isPressed){
        color = this->_pressedBackgroundColor();
    }else if(this->isHover){
        color = this->_hoverBackgroundColor();
    }else{
        color = this->_normalBackgroundColor();
    }

    this->backgroundColorAni->stop();
    this->backgroundColorAni->setEndValue(color);
    this->backgroundColorAni->start();

}

QColor FluentWindowBase::getBackgroundColor()
{
    return this->bgColorObject->_backgroundColor;
}

void  FluentWindowBase::setBackgroundColor(QColor color)
{
    this->bgColorObject->_backgroundColor = QColor(color);
}


QColor FluentWindowBase::backgroundColor()
{
    return this->getBackgroundColor();
}



FluentTitleBar::FluentTitleBar(QWidget *parent) : TitleBar(parent)
{
    this->setFixedHeight(48);
    this->hBoxLayout->removeWidget(this->minBtn);
    this->hBoxLayout->removeWidget(this->maxBtn);
    this->hBoxLayout->removeWidget(this->closeBtn);

    this->iconLabel = new QLabel(this);
    this->iconLabel->setFixedSize(18, 18);
    this->hBoxLayout->insertWidget(0, this->iconLabel, 0, Qt::AlignLeft | Qt::AlignVCenter);
    connect(this->window(), &QWidget::windowIconChanged, this, [this](QIcon icon){
        this->setIcon(icon);
    });

    this->titleLabel = new QLabel(this);
    this->hBoxLayout->insertWidget(1, this->titleLabel, 0, Qt::AlignLeft | Qt::AlignVCenter);
    this->titleLabel->setObjectName(QString("titleLabel"));
    connect(this->window(), &QWidget::windowTitleChanged, this, [this](QString title){
        this->setTitle(title);
    });

    this->vBoxLayout = new QVBoxLayout();
    this->buttonLayout = new QHBoxLayout();
    this->buttonLayout->setSpacing(0);
    this->buttonLayout->setContentsMargins(0, 0, 0, 0);
    this->buttonLayout->setAlignment(Qt::AlignTop);
    this->buttonLayout->addWidget(this->minBtn);
    this->buttonLayout->addWidget(this->maxBtn);
    this->buttonLayout->addWidget(this->closeBtn);
    this->vBoxLayout->addLayout(this->buttonLayout);
    this->vBoxLayout->addStretch(1);
    this->hBoxLayout->addLayout(this->vBoxLayout, 0);

    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("FLUENT_WINDOW"), Theme::AUTO);
}

void FluentTitleBar::setTitle(QString title)
{
    this->titleLabel->setText(title);
    this->titleLabel->adjustSize();
}

void FluentTitleBar::setIcon(QIcon icon)
{
    this->iconLabel->setPixmap(QIcon(icon).pixmap(18, 18));
}


FluentWindow::FluentWindow(QWidget *parent) : FluentWindowBase(parent)
{
    this->setTitleBar(new FluentTitleBar(this));

    this->navigationInterface = new NavigationInterface(this, true, true, true);
    this->widgetLayout = new QHBoxLayout();

    this->hBoxLayout->addWidget(this->navigationInterface);
    this->hBoxLayout->addLayout(this->widgetLayout);
    this->hBoxLayout->setStretchFactor(this->widgetLayout, 1);

    this->widgetLayout->addWidget(this->stackedWidget);
    this->widgetLayout->setContentsMargins(0, 48, 0, 0);

    connect(this->navigationInterface, &NavigationInterface::displayModeChanged, this->titleBar, [this](){
        this->titleBar->raise();
    });
    this->titleBar->raise();
}

NavigationTreeWidget *FluentWindow::addSubInterface(QWidget *_interface, QVariant *icon, QString text, NavigationItemPosition position, QWidget *parent, bool isTransparent)
{
    if(_interface->objectName().isNull()){
        return nullptr;
    }

    if(parent != nullptr && parent->objectName().isNull()){
        return nullptr;
    }

    _interface->setProperty("isStackedTransparent", isTransparent);
    this->stackedWidget->addWidget(_interface);

    QString routeKey = _interface->objectName();
    NavigationTreeWidget *item = this->navigationInterface->addItem(routeKey, icon, text, 
    [this, _interface](){
        this->switchTo(_interface);
    }, true, position, text, parent != nullptr ? parent->objectName() : QString());

    if(this->stackedWidget->count() == 1){
        connect(this->stackedWidget, &StackedWidget::currentChanged, this, &FluentWindow::_onCurrentInterfaceChanged);
        this->navigationInterface->setCurrentItem(routeKey);
        qrouter->setDefaultRouteKey(this->stackedWidget, routeKey);
    }

    this->_updateStackedBackground();
    return item;
}

void FluentWindow::resizeEvent(QResizeEvent *event)
{
    this->titleBar->move(46, 0);
    this->titleBar->resize(this->width() - 46, this->titleBar->height());
}


MSFluentTitleBar::MSFluentTitleBar(QWidget *parent) : FluentTitleBar(parent)
{
    this->hBoxLayout->insertSpacing(0, 20);
    this->hBoxLayout->insertSpacing(2, 2);
}




MSFluentWindow::MSFluentWindow(QWidget *parent) : WindowsFramelessWindow(parent)
{
    this->isHover = false;
    this->isPressed = false;

    this->bgColorObject = new MSBackgroundColorObject(this);
    this->bgColorObject->_backgroundColor = QColor(this->_normalBackgroundColor());
    this->backgroundColorAni = new QPropertyAnimation(this->bgColorObject, "backgroundColor", this);
    this->backgroundColorAni->setDuration(120);
    this->installEventFilter(this);
    //TOOD: qconfig.themeChanged.connect(self._updateBackgroundColor)

    this->hBoxLayout = new QHBoxLayout(this);
    this->stackedWidget = new StackedWidget(this);
    this->navigationInterface = nullptr;

    this->hBoxLayout->setSpacing(0);
    this->hBoxLayout->setContentsMargins(0, 0, 0, 0);

     FluentStyleSheet().apply(this->stackedWidget, FluentStyleSheetMap.value("FLUENT_WINDOW"), Theme::AUTO);

     this->setMicaEffectEnabled(true);
    

     //TODO:qconfig.themeChangedFinished.connect(self._onThemeChangedFinished)
    this->setTitleBar(new MSFluentTitleBar(this));
    this->navigationInterface = new NavigationBar(this);
    this->hBoxLayout->setContentsMargins(0, 48, 0, 0);
    this->hBoxLayout->addWidget(this->navigationInterface);
    this->hBoxLayout->addWidget(this->stackedWidget, 1);

    this->titleBar->raise();
    this->titleBar->setAttribute(Qt::WA_StyledBackground);
}

NavigationBarPushButton *MSFluentWindow::addSubInterface(QWidget *_interface, QVariant *icon, QString text, QVariant *selectedIcon, NavigationItemPosition position = NavigationItemPosition::TOP, bool isTransparent = true)
{
    if(_interface->objectName().isNull())
    {
        return nullptr;
    }

    _interface->setProperty("isStackedTransparent", isTransparent);
    this->stackedWidget->addWidget(_interface);

    QString routeKey = _interface->objectName();
    NavigationBarPushButton *item = this->navigationInterface->addItem(routeKey, icon, text, [this, _interface](){
        this->switchTo(_interface);
    },
    true, selectedIcon, position);

    if(this->stackedWidget->count() == 1){
        connect(this->stackedWidget, &StackedWidget::currentChanged, this, &MSFluentWindow::_onCurrentInterfaceChanged);
        this->navigationInterface->setCurrentItem(routeKey);
        qrouter->setDefaultRouteKey(this->stackedWidget, routeKey);
    }

    this->_updateStackedBackground();
    return item;
}

void MSFluentWindow::switchTo(QWidget *_interface)
{
    this->stackedWidget->setCurrentWidget(_interface, false);
}


void MSFluentWindow::_onCurrentInterfaceChanged(int index)
{
    QWidget *widget = this->stackedWidget->widget(index);
    this->navigationInterface->setCurrentItem(widget->objectName());
    qrouter->push(this->stackedWidget, widget->objectName());

    this->_updateStackedBackground();
}


void MSFluentWindow::_updateStackedBackground()
{
    bool isTransparent = this->stackedWidget->currentWidget()->property("isStackedTransparent").value<bool>();
    
    if(this->stackedWidget->property("isTransparent").value<bool>() == isTransparent){
        return;
    }
    
    this->stackedWidget->setProperty("isTransparent", QVariant::fromValue<bool>(isTransparent));
    this->stackedWidget->setStyle(QApplication::style());
}

QColor MSFluentWindow::_normalBackgroundColor()
{
    if(!this->isMicaEffctEnabled()){
        return isDarkTheme() ? QColor(32, 32, 32) : QColor(243, 243, 243);
    }

    return QColor(0, 0, 0, 0);
}

void MSFluentWindow::_onThemeChangedFinished()
{
    if(this->isMicaEffctEnabled()){
        this->windowEffect->setMicaEffect((HWND)(this->winId()), isDarkTheme(), false);
    }
}

void MSFluentWindow::paintEvent(QPaintEvent *event)
{
    WindowsFramelessWindow::paintEvent(event);
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#f3f3f3"));
    //painter.setBrush(*(this->backgroundColor()));
    painter.drawRect(this->rect());
}


void MSFluentWindow::setMicaEffectEnabled(bool isEnabled)
{
    this->_isMicaEnabled = isEnabled;

    if(isEnabled){
        this->windowEffect->setMicaEffect((HWND)(this->winId()), isDarkTheme(), false);
    }else{
        this->windowEffect->removeBackgroundEffect((HWND)(this->winId()));
    }

    this->setBackgroundColor(this->_normalBackgroundColor());
}


bool MSFluentWindow::isMicaEffctEnabled()
{
    return this->_isMicaEnabled;
}



bool MSFluentWindow::eventFilter(QObject *obj, QEvent *e)
{
    if(obj == this)
    {
        if(e->type() == QEvent::Type::EnabledChange)
        {
            if(this->isEnabled())
            {
                this->setBackgroundColor(this->_normalBackgroundColor());
            }else{
                this->setBackgroundColor(this->_disabledBackgroundColor());
            }
        }
    }
    return WindowsFramelessWindow::eventFilter(obj, e);
}

void MSFluentWindow::mousePressEvent(QMouseEvent *e)
{
    this->isPressed = true;
    this->_updateBackgroundColor();
    WindowsFramelessWindow::mousePressEvent(e);
}

void MSFluentWindow::mouseReleaseEvent(QMouseEvent *e)
{
    this->isPressed = false;
    this->_updateBackgroundColor();
    WindowsFramelessWindow::mouseReleaseEvent(e);
}

void MSFluentWindow::enterEvent(QEnterEvent *e)
{
    this->isHover = true;
    this->_updateBackgroundColor();
}

void MSFluentWindow::leaveEvent(QEvent *e)
{
    this->isHover = false;
    this->_updateBackgroundColor();
}

void MSFluentWindow::focusInEvent(QFocusEvent *e)
{
    WindowsFramelessWindow::focusInEvent(e);
    this->_updateBackgroundColor();
}



QColor MSFluentWindow::_hoverBackgroundColor()
{
    return this->_normalBackgroundColor();
}

QColor MSFluentWindow::_pressedBackgroundColor()
{
    return this->_normalBackgroundColor();
}

QColor MSFluentWindow::_focusInBackgroundColor()
{
    return this->_normalBackgroundColor();
}


QColor MSFluentWindow::_disabledBackgroundColor()
{
    return this->_normalBackgroundColor();
}


void MSFluentWindow::_updateBackgroundColor()
{
    QColor color;
    if(!this->isEnabled())
    {
        color = this->_disabledBackgroundColor();
    }else if(dynamic_cast<QLineEdit*>(this) != nullptr && this->hasFocus()){
        color = this->_focusInBackgroundColor();
    }else if(this->isPressed){
        color = this->_pressedBackgroundColor();
    }else if(this->isHover){
        color = this->_normalBackgroundColor();
    }

    this->backgroundColorAni->stop();
    this->backgroundColorAni->setEndValue(color);
    this->backgroundColorAni->start();

}

QColor *MSFluentWindow::getBackgroundColor()
{
    return new QColor(this->bgColorObject->getBackgroundColor());
}

void  MSFluentWindow::setBackgroundColor(QColor color)
{
    this->bgColorObject->setBackgroundColor(color);
}


QColor *MSFluentWindow::backgroundColor()
{
    return this->getBackgroundColor();
}


MSBackgroundColorObject::MSBackgroundColorObject(MSFluentWindow *parent) : BackgroundColorObject(nullptr)
{
    this->_backgroundColor = parent->_normalBackgroundColor();
}

QColor MSBackgroundColorObject::getBackgroundColor()
{
    return this->_backgroundColor;
}

void MSBackgroundColorObject::setBackgroundColor(QColor color)
{
    this->_backgroundColor = QColor(color);
    BackgroundColorObject::update();
}


SplitTitleBar::SplitTitleBar(QWidget *parent) : TitleBar(parent)
{
    this->iconLabel = new QLabel(this);
    this->iconLabel->setFixedSize(18, 18);
    this->hBoxLayout->insertSpacing(0, 12);
    this->hBoxLayout->insertWidget(1, this->iconLabel, 0, Qt::AlignLeft | Qt::AlignBottom);
    connect(this->window(), &QWidget::windowIconChanged, this, [this](QIcon i){
        this->setIcon(i);
    });

    this->titleLabel = new QLabel(this);
    this->hBoxLayout->insertWidget(2, this->titleLabel, 0, Qt::AlignLeft | Qt::AlignBottom);
    this->titleLabel->setObjectName(QString("titleLabel"));
    connect(this->window(), &QWidget::windowTitleChanged, this, [this](QString i){
        this->setTitle(i);
    });

    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("FLUENT_WINDOW"), Theme::AUTO);
}

void SplitTitleBar::setTitle(QString title)
{
    this->titleLabel->setText(title);
    this->titleLabel->adjustSize();
}

void SplitTitleBar::setIcon(QIcon icon)
{
    this->iconLabel->setPixmap(QIcon(icon).pixmap(18, 18));
}


SplitFluentWindow::SplitFluentWindow(QWidget *parent) : FluentWindow(parent)
{
    this->setTitleBar(new SplitTitleBar(this));

    this->widgetLayout->setContentsMargins(0, 0, 0, 0);
    this->titleBar->raise();
    connect(this->navigationInterface, &NavigationInterface::displayModeChanged, this, [this](){
        this->titleBar->raise();
    });
}