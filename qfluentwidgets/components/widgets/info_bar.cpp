#include "info_bar.h"







InfoIconWidget::InfoIconWidget(InfoBarIcon *icon, QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(36, 36);
    this->icon = icon;
}

void InfoIconWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    QRect rect = QRect(10, 10, 15, 15);
    if(this->icon->iconName != QString("INFORMATION")){
        QVariant *_icon = new QVariant(QVariant::fromValue<InfoBarIcon*>(this->icon));
        MIcon().drawIcon(_icon, &painter, rect, nullptr, QIcon::State::Off);  //TODO:需要确认是否正确的渲染
    }else{
        QVariant *_icon = new QVariant(QVariant::fromValue<InfoBarIcon*>(this->icon));
        //std::map<QString, QString> attributes;
        //qDebug() << QString((ThemeColor().themeColor())->name());
        //attributes[QString("fill")] = QString((ThemeColor().themeColor())->name());
        MIcon().drawIcon(_icon, &painter, rect, nullptr, QIcon::State::Off); 
    }
}



InfoBar::InfoBar(InfoBarIcon *icon, QString title, QString content, Qt::Orientation orient, bool isClosable, int duration, InfoBarPosition position, QWidget *parent) : QFrame(parent)
{
    this->title = title;
    this->content = content;
    this->orient = orient;
    this->icon = icon;
    this->duration = duration;
    this->isClosable = isClosable;
    this->position = position;

    this->titleLabel = new QLabel(this);
    this->contentLabel = new QLabel(this);
    FluentIcon *_icon = new FluentIcon();
    _icon->setIconName(QString("CLOSE"));
    this->closeButton = new TransparentToolButton(_icon, this);
    this->iconWidget = new InfoIconWidget(icon, nullptr);

    this->hBoxLayout = new QHBoxLayout(this);
    if(this->orient == Qt::Horizontal){
        this->textLayout = new QHBoxLayout();
    }else{
        this->textLayout = new QVBoxLayout();
    }

    if(this->orient == Qt::Horizontal){
        this->widgetLayout = new QHBoxLayout();
    }else{
        this->widgetLayout = new QVBoxLayout();
    }

    this->opacityEffect = new QGraphicsOpacityEffect(this);
    this->opacityAni = new QPropertyAnimation(this->opacityEffect, "opacity", this);

    this->lightBackgroundColor = QColor();
    this->darkBackgroundColor = QColor();

    this->__initWidget();

}

void InfoBar::__initWidget()
{
    this->opacityEffect->setOpacity(1);
    this->setGraphicsEffect(this->opacityEffect);

    this->closeButton->setFixedSize(36, 36);
    this->closeButton->setIconSize(QSize(12, 12));
    this->closeButton->setCursor(Qt::PointingHandCursor);
    this->closeButton->setVisible(this->isClosable);

    this->__setQss();
    this->__initLayout();

    connect(this->closeButton, &TransparentToolButton::clicked, this, &InfoBar::close);
}

void InfoBar::__initLayout()
{
    this->hBoxLayout->setContentsMargins(6, 6, 6, 6);
    this->hBoxLayout->setSizeConstraint(QVBoxLayout::SetMinimumSize);
    this->textLayout->setSizeConstraint(QHBoxLayout::SetMinimumSize);
    this->textLayout->setAlignment(Qt::AlignTop);
    this->textLayout->setContentsMargins(1, 8, 0, 8);

    this->hBoxLayout->addWidget(this->iconWidget, 0, Qt::AlignTop | Qt::AlignLeft);

    this->textLayout->addWidget(this->titleLabel, 1, Qt::AlignTop);
    this->titleLabel->setVisible(!this->title.isEmpty());

    if(this->orient == Qt::Horizontal){
        this->textLayout->addSpacing(7);
    }

    this->textLayout->addWidget(this->contentLabel, 1, Qt::AlignTop);
    this->contentLabel->setVisible(!this->content.isEmpty());
    this->hBoxLayout->addLayout(this->textLayout);

    if(this->orient == Qt::Horizontal){
        this->hBoxLayout->addLayout(this->widgetLayout);
        this->widgetLayout->setSpacing(10);
    }else{
        this->textLayout->addLayout(this->widgetLayout);
    }

    this->hBoxLayout->addSpacing(12);
    this->hBoxLayout->addWidget(this->closeButton, 0, Qt::AlignTop | Qt::AlignLeft);

    this->_adjustText();
}

void InfoBar::__setQss()
{
    this->titleLabel->setObjectName(QString("titleLabel"));
    this->contentLabel->setObjectName(QString("contentLabel"));
    this->setProperty("type", QVariant::fromValue<QString>(InfoBarIconMap.value(this->icon->iconName)));
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("INFO_BAR"), Theme::AUTO);
}

void InfoBar::__fadeOut()
{
    this->opacityAni->setDuration(200);
    this->opacityAni->setStartValue(1);
    this->opacityAni->setEndValue(0);
    connect(this->opacityAni, &QPropertyAnimation::finished, this, &InfoBar::close);
    this->opacityAni->start();
}

void InfoBar::_adjustText()
{
    int w = !this->parent() ? 900 : (this->parentWidget()->width() - 50); //TODO:特殊关注

    int chars = qMax(qMin(w / 10, 120), 30);
    this->titleLabel->setText(std::get<0>(TextWrap::wrap(this->title, chars, false, this->font())));

    chars = qMax(qMin(w / 9, 120), 30);
    this->contentLabel->setText(std::get<0>(TextWrap::wrap(this->content, chars, false, this->font())));
    this->adjustSize();
}

void InfoBar::addWidget(QWidget *widget, int stretch= 0)
{
    this->widgetLayout->addSpacing(6);
    Qt::AlignmentFlag align = this->orient == Qt::Vertical ? Qt::AlignTop : Qt::AlignVCenter;
    this->widgetLayout->addWidget(widget, stretch, Qt::AlignLeft | align);
}

void InfoBar::setCustomBackgroundColor(QVariant light, QVariant dark)
{
    if(light.canConvert<QString>()){
        this->lightBackgroundColor = QColor(light.value<QString>());
        this->darkBackgroundColor = QColor(dark.value<QString>());
    }else if(light.canConvert<Qt::GlobalColor>()){
        this->lightBackgroundColor = QColor(light.value<Qt::GlobalColor>());
        this->darkBackgroundColor = QColor(dark.value<Qt::GlobalColor>());       
    }else if(light.canConvert<QColor>()){
        this->lightBackgroundColor = QColor(light.value<QColor>());
        this->darkBackgroundColor = QColor(dark.value<QColor>());
    }
    this->update();
}

bool InfoBar::eventFilter(QObject *obj, QEvent *e)
{
    if(obj == this->parent()){
        if(e->type() == QEvent::Resize || e->type() == QEvent::WindowStateChange){
            this->_adjustText();
        }
    }
    return QFrame::eventFilter(obj, e);
}

void InfoBar::closeEvent(QCloseEvent *event)
{
    emit(this->closedSignal());
    this->deleteLater();
}

void InfoBar::showEvent(QShowEvent *event)
{
    this->_adjustText();
    QFrame::showEvent(event);

    if(this->duration >= 0){
        QTimer::singleShot(this->duration, this, &InfoBar::__fadeOut);
    }

    if(this->position != InfoBarPosition::NONE){
        InfoBarManager *manager = InfoBarManager::make(this->position);
        manager->add(this);
    }

    if(this->parent()){
        this->parent()->installEventFilter(this);
    }
}

void InfoBar::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);
    if(this->lightBackgroundColor == QColor()){
        return;
    }

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    if(isDarkTheme()){
        painter.setBrush(this->darkBackgroundColor);
    }else{
        painter.setBrush(this->lightBackgroundColor);
    }

    QRect rect = this->rect().adjusted(1, 1, -1, -1);
    painter.drawRoundRect(rect, 6, 6);
}


InfoBar* InfoBar::_new(InfoBarIcon *icon, QString title, QString content, Qt::Orientation orient, bool isCloseable, int duration, InfoBarPosition position, QWidget *parent)
{
    InfoBar *w = new InfoBar(icon, title, content, orient, isCloseable, duration, position, parent);
    w->show();
    return w;
}

InfoBar* InfoBar::success(QString title, QString content, Qt::Orientation orient, bool isClosable, int duration, InfoBarPosition position, QWidget *parent)
{
    InfoBarIcon *_icon = new InfoBarIcon();
    _icon->setIconName(QString("SUCCESS"));
    return InfoBar::_new(_icon, title, content, orient, isClosable, duration, position, parent);
}

InfoBar* InfoBar::info(QString title, QString content, Qt::Orientation orient, bool isClosable, int duration, InfoBarPosition position, QWidget *parent)
{
    InfoBarIcon *_icon = new InfoBarIcon();
    _icon->setIconName(QString("INFORMATION"));
    return InfoBar::_new(_icon, title, content, orient, isClosable, duration, position, parent);
}

InfoBar* InfoBar::warning(QString title, QString content, Qt::Orientation orient, bool isClosable, int duration, InfoBarPosition position, QWidget *parent)
{
    InfoBarIcon *_icon = new InfoBarIcon();
    _icon->setIconName(QString("WARNING"));
    return InfoBar::_new(_icon, title, content, orient, isClosable, duration, position, parent);
}

InfoBar* InfoBar::error(QString title, QString content, Qt::Orientation orient, bool isClosable, int duration, InfoBarPosition position, QWidget *parent)
{
    InfoBarIcon *_icon = new InfoBarIcon();
    _icon->setIconName(QString("ERROR"));
    return InfoBar::_new(_icon, title, content, orient, isClosable, duration, position, parent);
}



InfoBarManager::InfoBarManager() : QObject()
{
    /*
    if(this->__initialized){
        return;
    }
    */

    this->spacing = 16;
    this->margin = 24;
    this->infoBars = QMap<QObject*, QList<InfoBar*>*>();
    this->aniGroups = QMap<QObject*, QParallelAnimationGroup*>();
    this->slideAnis = QList<QPropertyAnimation*>();
    this->dropAnis = QList<QPropertyAnimation*>();
    //this->__initialized = true;
}


void InfoBarManager::add(InfoBar *infoBar)
{
    QObject *p = infoBar->parent(); //TODO:特殊关注

    if(!p){
        return;
    }

    if(!this->infoBars.contains(p)){
        p->installEventFilter(this);
        this->infoBars.insert(p, new QList<InfoBar*>());
        this->aniGroups.insert(p, new QParallelAnimationGroup(this));
    }

    if(this->infoBars.value(p)->contains(infoBar)){
        return;
    }

    if(!this->infoBars.value(p)->isEmpty()){
        QPropertyAnimation *dropAni = new QPropertyAnimation(infoBar, "pos");
        dropAni->setDuration(200);
        this->aniGroups.value(p)->addAnimation(dropAni);
        this->dropAnis.append(dropAni);
        infoBar->setProperty("dropAni", QVariant::fromValue<QPropertyAnimation*>(dropAni));
    }

    QList<InfoBar*> *_infoBars = this->infoBars.value(p);
    _infoBars->append(infoBar);
    //this->infoBars.value(p)->append(infoBar);
    QPropertyAnimation *slideAni = this->_createSlideAni(infoBar);
    this->slideAnis.append(slideAni);

    infoBar->setProperty("slideAni", QVariant::fromValue<QPropertyAnimation*>(slideAni));
    connect(infoBar, &InfoBar::closedSignal, this, [this, infoBar](){
        this->remove(infoBar);
    });

    slideAni->start();
}

void InfoBarManager::remove(InfoBar *infoBar)
{
    QObject *p = infoBar->parent();
    if(!this->infoBars.contains(p)){
        return;
    }

    if(!this->infoBars.value(p)->contains(infoBar)){
        return;
    }

    QList<InfoBar*> *_infoBars = this->infoBars.value(p);
    _infoBars->append(infoBar);
    _infoBars->removeOne(infoBar);
    //this->infoBars.value(p)->removeOne(infoBar);

    QVariant dropAniQVariant = infoBar->property("dropAni");
    QPropertyAnimation *dropAni = dropAniQVariant.value<QPropertyAnimation*>();
    if(dropAni){
        this->aniGroups.value(p)->removeAnimation(dropAni);
        this->dropAnis.removeOne(dropAni);
    }

    QVariant slideAniQVariant = infoBar->property("dropAni");
    QPropertyAnimation *slideAni = slideAniQVariant.value<QPropertyAnimation*>();
    if(slideAni){
        this->slideAnis.removeOne(slideAni);
    }

    this->_updateDropAni(p);
    this->aniGroups.value(p)->start();
}



QPropertyAnimation *InfoBarManager::_createSlideAni(InfoBar *infoBar)
{
    QPropertyAnimation *slideAni = new QPropertyAnimation(infoBar, "pos");
    slideAni->setEasingCurve(QEasingCurve::OutQuad);
    slideAni->setDuration(200);

    slideAni->setStartValue(this->_slideStartPos(infoBar));
    slideAni->setEndValue(this->_pos(infoBar, QSize()));

    return slideAni;
}


void InfoBarManager::_updateDropAni(QObject *parent)
{
    QList<InfoBar*>* _infoBars = this->infoBars.value(parent);
    for(int i = 0; i < _infoBars->length(); i++){
        InfoBar *bar = this->infoBars.value(parent)->at(i);
        QVariant aniQVariant = bar->property("dropAni");
        QPropertyAnimation *ani = aniQVariant.value<QPropertyAnimation *>();
        if(!ani){
            continue;
        }
        ani->setStartValue(bar->pos());
        ani->setEndValue(this->_pos(bar, QSize()));
    }
}


QPoint InfoBarManager::_pos(InfoBar *infoBar, QSize parentSize)
{

}

QPoint InfoBarManager::_slideStartPos(InfoBar *infoBar)
{

}


bool InfoBarManager::eventFilter(QObject *obj, QEvent *e)
{
    if(!this->infoBars.contains(obj)){
        return false;
    }

    if(e->type() == QEvent::Resize || e->type() == QEvent::WindowStateChange){
        if(e->type() == QEvent::Resize){
            QResizeEvent *re = dynamic_cast<QResizeEvent*>(e);
            QSize size = re->size();
            for(int i = 0; i < this->infoBars.value(obj)->length(); i++){
                InfoBar *bar = this->infoBars.value(obj)->at(i);
                bar->move(this->_pos(bar, size));
            }
        }else{
            QSize size = QSize();
            for(int i = 0; i < this->infoBars.value(obj)->length(); i++){
                InfoBar *bar = this->infoBars.value(obj)->at(i);
                bar->move(this->_pos(bar, size));
            }
        }
    }

    return QObject::eventFilter(obj, e);
}

InfoBarManager *InfoBarManager::make(InfoBarPosition position)
{
    if(position == InfoBarPosition::TOP){
        return new TopInfoBarManager();
    }else if(position == InfoBarPosition::TOP_RIGHT){
        return new TopRightInfoBarManager();
    }else if(position == InfoBarPosition::BOTTOM_RIGHT){
        return new BottomRightInfoBarManager();
    }else if(position == InfoBarPosition::TOP_LEFT){
        return new TopLeftInfoBarManager();
    }else if(position == InfoBarPosition::BOTTOM_LEFT){
        return new BottomLeftInfoBarManager();
    }else if(position == InfoBarPosition::BOTTOM){
        return new BottomInfoBarManager();
    }
    return nullptr;
}



TopInfoBarManager::TopInfoBarManager() : InfoBarManager()
{

}

QPoint TopInfoBarManager::_pos(InfoBar *infoBar, QSize parentSize = QSize())
{
    QObject *p = infoBar->parent();
    QSize _parentSize;


    int x = (((QWidget *)infoBar->parent())->width() - ((QWidget *)infoBar)->width()) / 2;
    int y = this->margin;

    int index = this->infoBars.value(p)->indexOf(infoBar);
    for(int i = 0; i < index; i++){
        InfoBar *bar = this->infoBars.value(p)->at(i);
        y += (bar->height() + this->spacing);
    }

    return QPoint(x, y);
}

QPoint TopInfoBarManager::_slideStartPos(InfoBar *infoBar)
{
    QPoint pos = this->_pos(infoBar, QSize());
    return QPoint(pos.x(), pos.y() - 16);
}


TopRightInfoBarManager::TopRightInfoBarManager() : InfoBarManager()
{

}


QPoint TopRightInfoBarManager::_pos(InfoBar *infoBar, QSize parentSize)
{
    QObject *p = infoBar->parent();
    QSize _parentSize;
    if(parentSize == QSize()){
        _parentSize = ((QWidget *)p)->size();  //TODO:特殊关注
    }else{
        _parentSize = parentSize;
    }
    //QSize parentSize = parentSize == QSize() ? p->size() : parentSize;

    int x = _parentSize.width() - infoBar->width() - this->margin;
    int y = this->margin;

    int index = this->infoBars.value(p)->indexOf(infoBar);
    for(int i = 0; i < index; i++){
        InfoBar *bar = this->infoBars.value(p)->at(i);
        y += (bar->height() + this->spacing);
    }

    return QPoint(x, y);
}


QPoint TopRightInfoBarManager::_slideStartPos(InfoBar *infoBar)
{
    return QPoint(((QWidget*)infoBar->parent())->width(), this->_pos(infoBar, QSize()).y());
}   


BottomRightInfoBarManager::BottomRightInfoBarManager() : InfoBarManager()
{

}


QPoint BottomRightInfoBarManager::_pos(InfoBar *infoBar, QSize parentSize)
{
    QObject *p = infoBar->parent();
    //QSize parentSize = parentSize == QSize() ? p->size() : parentSize;
    QSize _parentSize;
    if(parentSize == QSize()){
        _parentSize = ((QWidget *)p)->size();  //TODO:特殊关注
    }else{
        _parentSize = parentSize;
    }

    int x = _parentSize.width() - ((QWidget*)infoBar)->width() - this->margin;
    int y = _parentSize.height() - infoBar->height() - this->margin;

    int index = this->infoBars.value(p)->indexOf(infoBar);
    for(int i = 0; i < index; i++){
        InfoBar *bar = this->infoBars.value(p)->at(i);
        y -= (bar->height() + this->spacing);
    }

    return QPoint(x, y);
}


QPoint BottomRightInfoBarManager::_slideStartPos(InfoBar *infoBar)
{
    return QPoint(((QWidget*)infoBar->parent())->width(), this->_pos(infoBar, QSize()).y());
}

TopLeftInfoBarManager::TopLeftInfoBarManager() : InfoBarManager()
{

}

QPoint TopLeftInfoBarManager::_pos(InfoBar *infoBar, QSize parentSize)
{
    QObject *p = infoBar->parent();
    //QSize parentSize = parentSize == QSize() ? p->size() : parentSize;
    QSize _parentSize;
    if(parentSize == QSize()){
        _parentSize = ((QWidget *)p)->size();  //TODO:特殊关注
    }else{
        _parentSize = parentSize;
    }

    int y = this->margin;
    int index = this->infoBars.value(p)->indexOf(infoBar);

    for(int i = 0; i < index; i++){
        InfoBar *bar = this->infoBars.value(p)->at(i);
        y += (bar->height() + this->spacing);
    }

    return QPoint(this->margin, y);
}


QPoint TopLeftInfoBarManager::_slideStartPos(InfoBar *infoBar)
{
    return QPoint(-infoBar->width(), this->_pos(infoBar, QSize()).y());
}


BottomLeftInfoBarManager::BottomLeftInfoBarManager() : InfoBarManager()
{

}


QPoint BottomLeftInfoBarManager::_pos(InfoBar *infoBar, QSize parentSize)
{
    QObject *p = infoBar->parent();
    //QSize parentSize = parentSize == QSize() ? p->size() : parentSize;
    QSize _parentSize;
    if(parentSize == QSize()){
        _parentSize = ((QWidget *)p)->size();  //TODO:特殊关注
    }else{
        _parentSize = parentSize;
    }

    int y = _parentSize.height() - infoBar->height() - this->margin;
    int index = this->infoBars.value(p)->indexOf(infoBar);

    for(int i = 0; i < index; i++){
        InfoBar *bar = this->infoBars.value(p)->at(i);
        y -= (bar->height() + this->spacing);
    }

    return QPoint(this->margin, y);
}



QPoint BottomLeftInfoBarManager::_slideStartPos(InfoBar *infoBar)
{
    return QPoint(-infoBar->width(), this->_pos(infoBar, QSize()).y());
}


BottomInfoBarManager::BottomInfoBarManager() : InfoBarManager()
{

}


QPoint BottomInfoBarManager::_pos(InfoBar *infoBar, QSize parentSize)
{
    QObject *p = infoBar->parent();  //TODO:特殊关注
    //QSize parentSize = parentSize == QSize() ? p->size() : parentSize;
    QSize _parentSize;
    if(parentSize == QSize()){
        _parentSize = ((QWidget *)p)->size();  //TODO:特殊关注
    }else{
        _parentSize = parentSize;
    }

    int x = (_parentSize.width() - infoBar->width()) / 2;
    int y = _parentSize.height() - infoBar->height() - this->margin;
    int index = this->infoBars.value(p)->indexOf(infoBar);

    for(int i = 0; i < index; i++){
        InfoBar *bar = this->infoBars.value(p)->at(i);
        y -= (bar->height() + this->spacing);
    }

    return QPoint(x, y);
}


QPoint BottomInfoBarManager::_slideStartPos(InfoBar *infoBar)
{
    QPoint pos = this->_pos(infoBar, QSize());
    return QPoint(pos.x(), pos.y() + 16);
}