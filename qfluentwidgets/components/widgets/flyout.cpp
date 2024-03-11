#include "flyout.h"

IconWidgetForFlyout::IconWidgetForFlyout(QVariant *icon, QWidget *parent) : IconWidget(icon, parent)
{
    this->setFixedSize(36, 54);
}

IconWidgetForFlyout::IconWidgetForFlyout(FluentIcon icon, QWidget *parent) : IconWidget(icon, parent)
{
    this->setFixedSize(36, 54);
}


IconWidgetForFlyout::IconWidgetForFlyout(QIcon icon, QWidget *parent) : IconWidget(icon, parent)
{
    this->setFixedSize(36, 54);
}


IconWidgetForFlyout::IconWidgetForFlyout(QString icon, QWidget *parent) : IconWidget(icon, parent){
    this->setFixedSize(36, 54);
};

void IconWidgetForFlyout::paintEvent(QPaintEvent *event)
{
    if(!this->_icon->isValid()){
        return;
    }


    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    QRect rect = QRect(8, (this->height() - 20) / 2, 20, 20);
    MIcon().drawIcon(this->_icon, &painter, rect, nullptr, QIcon::State::Off);
}




FlyoutViewBase::FlyoutViewBase(QWidget *parent) : QWidget(parent)
{

}


void FlyoutViewBase::addWidget(QWidget *widget, int stretch, Qt::AlignmentFlag align)
{

}

QColor FlyoutViewBase::backgroundColor()
{
    return isDarkTheme() ? QColor(40, 40, 40) : QColor(248, 248, 248);
}

QColor FlyoutViewBase::borderColor()
{
    return isDarkTheme() ? QColor(0, 0, 0, 45) : QColor(0, 0, 0, 17);
}

void FlyoutViewBase::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    painter.setBrush(this->backgroundColor());
    painter.setPen(this->borderColor());

    QRect rect = this->rect().adjusted(1, 1, -1, -1);
    painter.drawRoundedRect(rect, 8, 8);
}

FlyoutView::FlyoutView(QString title, QString content, QVariant *icon, QVariant *image, bool isClosable = false, QWidget *parent = nullptr) : FlyoutViewBase(parent)
{
    this->icon = icon;
    this->title = title;
    this->image = image;
    this->content = content;
    this->isClosable = isClosable;

    this->vBoxLayout = new QVBoxLayout(this);
    this->viewLayout = new QHBoxLayout();
    this->widgetLayout = new QVBoxLayout();

    this->titleLabel = new QLabel(title, this);
    this->contentLabel = new QLabel(content, this);
    this->iconWidget = new IconWidgetForFlyout(icon, this);
    this->imageLabel = new ImageLabel(this);

    FluentIcon *_icon = new FluentIcon();
    _icon->setIconName(QString("CLOSE"));
    this->closeButton = new TransparentToolButton(_icon, this);

    this->__initWidgets();
}


void FlyoutView::__initWidgets()
{
    this->imageLabel->setImage(this->image);
    
    this->closeButton->setFixedSize(32, 32);
    this->closeButton->setIconSize(QSize(12, 12));
    this->closeButton->setVisible(this->isClosable);
    this->titleLabel->setVisible(!this->title.isEmpty());
    this->contentLabel->setVisible(!this->content.isEmpty());
    this->iconWidget->setHidden(!this->icon->isValid());

    connect(this->closeButton, &TransparentToolButton::clicked, this, &FlyoutView::closed);

    this->titleLabel->setObjectName(QString("titleLabel"));
    this->contentLabel->setObjectName(QString("contentLabel"));
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("TEACHING_TIP"), Theme::AUTO);

    this->__initLayout();
}

void FlyoutView::__initLayout()
{
    this->vBoxLayout->setContentsMargins(1, 1, 1, 1);
    this->widgetLayout->setContentsMargins(0, 8, 0, 8);
    this->viewLayout->setSpacing(4);
    this->widgetLayout->setSpacing(0);
    this->vBoxLayout->setSpacing(0);

    if(this->title.isEmpty() || this->content.isEmpty()){
        this->iconWidget->setFixedHeight(36);
    }

    this->vBoxLayout->addLayout(this->viewLayout);
    this->viewLayout->addWidget(this->iconWidget, 0, Qt::AlignTop);

    this->_adjustText();
    this->widgetLayout->addWidget(this->titleLabel);
    this->widgetLayout->addWidget(this->contentLabel);
    this->viewLayout->addLayout(this->widgetLayout);

    this->closeButton->setVisible(this->isClosable);
    this->viewLayout->addWidget(this->closeButton, 0, Qt::AlignRight | Qt::AlignTop);

    QMargins margins = QMargins(6, 5, 6, 5);
    margins.setLeft(this->icon->isNull() ? 20 : 5);
    margins.setRight(!this->isClosable ? 20 : 6);
    this->viewLayout->setContentsMargins(margins);

    this->_adjustImage();
    this->__addImageToLayout();
}

void FlyoutView::addWidget(QWidget *widget, int stretch, Qt::AlignmentFlag align)
{
    this->widgetLayout->addSpacing(8);
    this->widgetLayout->addWidget(widget, stretch, align);
}

void FlyoutView::__addImageToLayout()
{
    this->imageLabel->setBorderRadius(8, 8, 0, 0);
    this->imageLabel->setHidden(this->imageLabel->isNull());
    this->vBoxLayout->insertWidget(0, this->imageLabel);
}

void FlyoutView::_adjustText()
{
    int w = qMin(900, QApplication::screenAt(QCursor::pos())->geometry().width() - 200);

    int chars = qMax(qMin(w / 20, 120), 30);
    this->titleLabel->setText(std::get<0>(TextWrap::wrap(this->title, chars, false, this->font())));

    chars = qMax(qMin(w / 9, 120), 30);
    this->contentLabel->setText(std::get<0>(TextWrap::wrap(this->content, chars, false, this->font())));
}

void FlyoutView::_adjustImage()
{
    int w = this->vBoxLayout->sizeHint().width() - 2;
    this->imageLabel->scaledToWidth(w);
}

void FlyoutView::showEvent(QShowEvent *event)
{
    FlyoutViewBase::showEvent(event);
    this->_adjustImage();
    this->adjustSize();
}


Flyout::Flyout(FlyoutViewBase *view, QWidget *parent, bool isDeleteOnClose) : QWidget(parent)
{
    this->view = view;
    this->hBoxLayout = new QHBoxLayout(this);
    this->aniManger = nullptr;
    this->isDeleteOnClose = isDeleteOnClose;

    this->hBoxLayout->setContentsMargins(15, 8, 15, 20);
    this->hBoxLayout->addWidget(this->view);
    this->setShadowEffect(35, std::tuple<int,int>(0, 8));

    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
}

void Flyout::setShadowEffect(int blurRadius = 35, std::tuple<int,int> offset = std::tuple<int,int>(0, 8))
{
    QColor color = QColor(0, 0, 0, isDarkTheme() ? 80 : 30);
    this->shadowEffect = new QGraphicsDropShadowEffect(this->view);
    this->shadowEffect->setBlurRadius(blurRadius);
    this->shadowEffect->setOffset(std::get<0>(offset), std::get<1>(offset));
    this->shadowEffect->setColor(color);
    this->view->setGraphicsEffect(nullptr);
    this->view->setGraphicsEffect(this->shadowEffect);
}

void Flyout::closeEvent(QCloseEvent *event)
{
    if(this->isDeleteOnClose){
        this->deleteLater();
    }

    QWidget::closeEvent(event);
    emit(this->close());
}

void Flyout::exec(QPoint pos, FlyoutAnimationType aniType)
{
    this->aniManger = FlyoutAnimationManager::make(aniType, this);
    this->show();
    this->aniManger->exec(pos);
}

Flyout* Flyout::make(FlyoutViewBase *view, QVariant target, QWidget *parent, FlyoutAnimationType aniType = FlyoutAnimationType::PULL_UP, bool isDeleteOnClose= true)
{
    Flyout *w = new Flyout(view, parent, isDeleteOnClose);

    if(target.isNull()){
        return w;
    }

    w->show();


    if(target.canConvert<QWidget*>()){
        QPoint _target = FlyoutAnimationManager::make(aniType, w)->position(target.value<QWidget*>());
        w->exec(_target, aniType);
        return w;
    }else{
        w->exec(target.value<QPoint>(), aniType);
        return w;
    }
}



Flyout* Flyout::create(QString title, QString content, QVariant *icon, QVariant *image, bool isClosable, QVariant target, QWidget *parent, FlyoutAnimationType aniType, bool isDeleteOnClose)
{
    FlyoutView *view = new FlyoutView(title, content, icon, image, isClosable, nullptr);
    Flyout *w = Flyout::make(view, target, parent, aniType, isDeleteOnClose);
    connect(view, &FlyoutView::closed, w, &Flyout::close);
    return w;
}


void Flyout::fadeOut()
{
    this->fadeOutAni = new QPropertyAnimation(this, "windowOpacity", this);
    connect(this->fadeOutAni, &QPropertyAnimation::finished, this, &Flyout::close);
    this->fadeOutAni->setStartValue(1);
    this->fadeOutAni->setEndValue(0);
    this->fadeOutAni->setDuration(120);
    this->fadeOutAni->start();
}


FlyoutAnimationManager::FlyoutAnimationManager(Flyout *flyout) : QObject()
{
    this->flyout = flyout;
    this->aniGroup = new QParallelAnimationGroup(this);
    this->slideAni = new QPropertyAnimation(flyout, "pos", this);
    this->opacityAni = new QPropertyAnimation(flyout, "windowOpacity", this);

    this->slideAni->setDuration(187);
    this->opacityAni->setDuration(187);

    this->opacityAni->setStartValue(0);
    this->opacityAni->setEndValue(1);

    this->slideAni->setEasingCurve(QEasingCurve::OutQuad);
    this->opacityAni->setEasingCurve(QEasingCurve::OutQuad);
    this->aniGroup->addAnimation(this->slideAni);
    this->aniGroup->addAnimation(this->opacityAni);
}



void FlyoutAnimationManager::exec(QPoint pos)
{

}

QPoint FlyoutAnimationManager::_adjustPosition(QPoint pos)
{
    QRect rect = QApplication::screenAt(QCursor::pos())->availableGeometry();
    int w = this->flyout->sizeHint().width() + 5;
    int h = this->flyout->sizeHint().height();
    int x = qMax(rect.left(), qMin(pos.x(), rect.right() - w));
    int y = qMax(rect.top(), qMin(pos.y() - 4, rect.bottom() - h + 5));
    return QPoint(x, y);
}

QPoint FlyoutAnimationManager::position(QWidget *target)
{

}

FlyoutAnimationManager* FlyoutAnimationManager::make(FlyoutAnimationType aniType, Flyout *flyout)
{
    if(aniType == FlyoutAnimationType::PULL_UP){
        return new PullUpFlyoutAnimationManager(flyout);
    }else if(aniType == FlyoutAnimationType::DROP_DOWN){
        return new DropDownFlyoutAnimationManager(flyout);
    }else if(aniType == FlyoutAnimationType::SLIDE_LEFT){
        return new SlideLeftFlyoutAnimationManager(flyout);
    }else if(aniType == FlyoutAnimationType::SLIDE_RIGHT){
        return new SlideRightFlyoutAnimationManager(flyout);
    }else if(aniType == FlyoutAnimationType::FADE_IN){
        return new FadeInFlyoutAnimationManager(flyout);
    }else if(aniType == FlyoutAnimationType::NONE){
        return new DummyFlyoutAnimationManager(flyout);
    }
}



PullUpFlyoutAnimationManager::PullUpFlyoutAnimationManager(Flyout *flyout) : FlyoutAnimationManager(flyout)
{

}

QPoint PullUpFlyoutAnimationManager::position(QWidget *target)
{
    Flyout *w = this->flyout;
    QPoint pos = target->mapToGlobal(QPoint());
    int x = pos.x() + target->width() / 2 - w->sizeHint().width() / 2;
    int y = pos.y() - w->sizeHint().height() + w->layout()->contentsMargins().bottom();
    return QPoint(x, y);
}


void PullUpFlyoutAnimationManager::exec(QPoint pos)
{
    QPoint _pos = this->_adjustPosition(pos);
    this->slideAni->setStartValue(_pos + QPoint(0, 8));
    this->slideAni->setEndValue(_pos);
    this->aniGroup->start();
}


DropDownFlyoutAnimationManager::DropDownFlyoutAnimationManager(Flyout *flyout) : FlyoutAnimationManager(flyout)
{

}


QPoint DropDownFlyoutAnimationManager::position(QWidget *target)
{
    Flyout *w = this->flyout;
    QPoint pos = target->mapToGlobal(QPoint(0, target->height()));
    int x = pos.x() + target->width() / 2 - w->sizeHint().width() / 2;
    int y = pos.y() -  w->layout()->contentsMargins().top() + 8;
    return QPoint(x, y);
}

void DropDownFlyoutAnimationManager::exec(QPoint pos)
{
    QPoint _pos = this->_adjustPosition(pos);
    this->slideAni->setStartValue(_pos - QPoint(0, 8));
    this->slideAni->setEndValue(_pos);
    this->aniGroup->start();
}


SlideLeftFlyoutAnimationManager::SlideLeftFlyoutAnimationManager(Flyout *flyout) : FlyoutAnimationManager(flyout)
{

}


QPoint SlideLeftFlyoutAnimationManager::position(QWidget *target)
{
    Flyout *w = this->flyout;
    QPoint pos = target->mapToGlobal(QPoint(0, 0));
    int x = pos.x() - w->sizeHint().width() + 8;
    int y = pos.y() - w->sizeHint().height() / 2 + target->height() / 2 + w->layout()->contentsMargins().top();
    return QPoint(x, y);
}

void SlideLeftFlyoutAnimationManager::exec(QPoint pos)
{
    QPoint _pos = this->_adjustPosition(pos);
    this->slideAni->setStartValue(_pos + QPoint(8, 0));
    this->slideAni->setEndValue(_pos);
    this->aniGroup->start();
}

SlideRightFlyoutAnimationManager::SlideRightFlyoutAnimationManager(Flyout *flyout) : FlyoutAnimationManager(flyout)
{

}


QPoint SlideRightFlyoutAnimationManager::position(QWidget *target)
{
    Flyout *w = this->flyout;
    QPoint pos = target->mapToGlobal(QPoint(0, 0));
    int x = pos.x() + target->width() - 8;
    int y = pos.y() - w->sizeHint().height() / 2 + target->height() / 2 + w->layout()->contentsMargins().top();
    return QPoint(x, y);
}

void SlideRightFlyoutAnimationManager::exec(QPoint pos)
{
    QPoint _pos = this->_adjustPosition(pos);
    this->slideAni->setStartValue(_pos - QPoint(8, 0));
    this->slideAni->setEndValue(_pos);
    this->aniGroup->start();
}


FadeInFlyoutAnimationManager::FadeInFlyoutAnimationManager(Flyout *flyout) : FlyoutAnimationManager(flyout)
{

}



QPoint FadeInFlyoutAnimationManager::position(QWidget *target)
{
    Flyout *w = this->flyout;
    QPoint pos = target->mapToGlobal(QPoint());
    int x = pos.x() + target->width() / 2 - w->sizeHint().width() / 2;
    int y = pos.y() - w->sizeHint().height()  + w->layout()->contentsMargins().bottom();
    return QPoint(x, y);
}


void FadeInFlyoutAnimationManager::exec(QPoint pos)
{
    this->flyout->move(this->_adjustPosition(pos));
    this->aniGroup->removeAnimation(this->slideAni);
    this->aniGroup->start();
}



DummyFlyoutAnimationManager::DummyFlyoutAnimationManager(Flyout *flyout) : FlyoutAnimationManager(flyout)
{

}

QPoint DummyFlyoutAnimationManager::position(QWidget *target)
{
    QMargins m = this->flyout->hBoxLayout->contentsMargins();
    return target->mapToGlobal(QPoint(-m.left(), -this->flyout->sizeHint().height() + m.bottom() - 8));
}


void DummyFlyoutAnimationManager::exec(QPoint pos)
{
    this->flyout->move(this->_adjustPosition(pos));
}