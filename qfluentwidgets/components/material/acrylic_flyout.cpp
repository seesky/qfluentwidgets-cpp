#include "acrylic_flyout.h"

AcrylicFlyoutViewBase::AcrylicFlyoutViewBase(QWidget* parent) : FlyoutViewBase(parent)
{
    this->acrylicBrush = new AcrylicBrush(this, 30, QColor(242, 242, 242, 150), QColor(255, 255, 255, 10), 0.03);
}

QPainterPath AcrylicFlyoutViewBase::acrylicClipPath()
{
    QPainterPath path = QPainterPath();
    path.addRoundedRect(QRectF(this->rect().adjusted(1, 1, -1, -1)), 8, 8);
    return path;
}

void AcrylicFlyoutViewBase::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    this->_drawAcrylic(&painter);

    painter.setBrush(Qt::NoBrush);
    painter.setPen(this->borderColor());
    QRectF rect = QRectF(this->rect()).adjusted(1, 1, -1, -1);
    painter.drawRoundedRect(rect, 8, 8);
}


void AcrylicFlyoutViewBase::_drawAcrylic(QPainter *painter)
{
    QPainterPath path = this->acrylicClipPath();
    if(!path.isEmpty()){
        this->acrylicBrush->clipPath = this->acrylicClipPath();
    }

    this->_updateAcrylicColor();
    this->acrylicBrush->paint();
}

void AcrylicFlyoutViewBase::_updateAcrylicColor()
{
    QColor tintColor;
    QColor luminosityColor;
    if(isDarkTheme()){
        tintColor = QColor(32, 32, 32, 200);
        luminosityColor = QColor(0, 0, 0, 0);
    }else{
        tintColor = QColor(255, 255, 255, 180);
        luminosityColor = QColor(255, 255, 255, 255);
    }

    this->acrylicBrush->tintColor = tintColor;
    this->acrylicBrush->luminosityColor = luminosityColor;
}


AcrylicFlyoutView::AcrylicFlyoutView(QString title, QString content, QVariant *icon, QVariant *image, bool isClosable, QWidget *parent) : FlyoutView(title, content, icon, image, isClosable, parent)
{
    this->acrylicBrush = new AcrylicBrush(this, 30, QColor(242, 242, 242, 150), QColor(255, 255, 255, 10), 0.03);
}


QPainterPath AcrylicFlyoutView::acrylicClipPath()
{
    QPainterPath path = QPainterPath();
    path.addRoundedRect(QRectF(this->rect().adjusted(1, 1, -1, -1)), 8, 8);
    return path;
}

void AcrylicFlyoutView::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    this->_drawAcrylic(&painter);

    painter.setBrush(Qt::NoBrush);
    painter.setPen(this->borderColor());
    QRectF rect = this->rect().adjusted(1, 1, -1, -1);
    painter.drawRoundedRect(rect, 8, 8);
}


void AcrylicFlyoutView::_drawAcrylic(QPainter *painter)
{
    QPainterPath path = this->acrylicClipPath();
    if(!path.isEmpty()){
        this->acrylicBrush->clipPath = this->acrylicClipPath();
    }

    this->_updateAcrylicColor();
    this->acrylicBrush->paint();
}

void AcrylicFlyoutView::_updateAcrylicColor()
{
    QColor tintColor;
    QColor luminosityColor;
    if(isDarkTheme()){
        tintColor = QColor(32, 32, 32, 200);
        luminosityColor = QColor(0, 0, 0, 0);
    }else{
        tintColor = QColor(255, 255, 255, 180);
        luminosityColor = QColor(255, 255, 255, 255);
    }

    this->acrylicBrush->tintColor = tintColor;
    this->acrylicBrush->luminosityColor = luminosityColor;
}


AcrylicFlyout::AcrylicFlyout(FlyoutViewBase *view, QWidget *parent, bool isDeleteOnClose) : Flyout(view, parent, isDeleteOnClose)
{

}

AcrylicFlyout* AcrylicFlyout::create(QString title, QString content, QVariant *icon, QVariant *image, bool isClosable, QVariant target, QWidget *parent, FlyoutAnimationType aniType, bool isDeleteOnClose)
{
    AcrylicFlyoutView *view = new AcrylicFlyoutView(title, content, icon, image, isClosable, nullptr);
    AcrylicFlyout *w = AcrylicFlyout::make(view, target, parent, aniType, isDeleteOnClose);
    connect(view, &AcrylicFlyoutView::closed, w, &Flyout::close);
    return w;
}

AcrylicFlyout* AcrylicFlyout::make(FlyoutViewBase *view, QVariant target, QWidget *parent, FlyoutAnimationType aniType, bool isDeleteOnClose)
{
    AcrylicFlyout *w = new AcrylicFlyout(view, parent, isDeleteOnClose);

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


void AcrylicFlyout::exec(QPoint pos, FlyoutAnimationType aniType)
{
    this->aniManger = FlyoutAnimationManager::make(aniType, this);

    auto _view = qobject_cast<AcrylicFlyoutViewBase*>(this->view);
    auto __view = qobject_cast<AcrylicFlyoutView*>(this->view);

    QPoint _pos;
    if(_view){
        _pos = this->aniManger->_adjustPosition(pos);
        _view->acrylicBrush->grabImage(QRect(pos, this->layout()->sizeHint()));
    }else if(__view){
        _pos = this->aniManger->_adjustPosition(pos);
        __view->acrylicBrush->grabImage(QRect(pos, this->layout()->sizeHint()));
    }else{
        _pos = pos;
    }

    this->show();
    this->aniManger->exec(_pos);
}