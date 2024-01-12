#include "title_bar_buttons.h"

TitleBarButton::TitleBarButton(QWidget *parent) : QAbstractButton(parent)
{
    setCursor(Qt::ArrowCursor);
    setFixedSize(46, 32);
    this->_state = TitleBarButtonState::NORMAL;

    this->_normalColor = new QColor(0, 0, 0);
    this->_hoverColor = new QColor(0, 0, 0);
    this->_pressedClor = new QColor(0, 0, 0);

    this->_normalBgColor = new QColor(0, 0, 0, 0);
    this->_hoverBgColor = new QColor(0, 0, 0, 26);
    this->_PressedBgColor = new QColor(0, 0, 0, 51);
}

void TitleBarButton::setState(TitleBarButtonState state)
{
    this->_state = state;
    this->update();
}

bool TitleBarButton::isPressed()
{
    return this->_state == TitleBarButtonState::PRESSED;
}

QColor *TitleBarButton::getNormalColor()
{
    return this->_normalColor;
}

void TitleBarButton::setHoverColor(QColor *color)
{
    this->_hoverColor = color;
    this->update();
}

void TitleBarButton::setPressedColor(QColor *color)
{
    this->_pressedClor = color;
    this->update();
}

void TitleBarButton::setNormalBackgroundColor(QColor *color)
{
    this->_normalBgColor = color;
    this->update();
}

void TitleBarButton::setHoverBackgroundColor(QColor *color)
{
    this->_hoverBgColor = color;
    this->update();
}

void TitleBarButton::setPressedBackgroundColor(QColor *color)
{
    this->_PressedBgColor = color;
    this->update();
}

void TitleBarButton::enterEvent(QEvent *event)
{
    setState(TitleBarButtonState::HOVER);
    QAbstractButton::enterEvent(event);
}

void TitleBarButton::leaveEvent(QEvent *event)
{
    setState(TitleBarButtonState::NORMAL);
    QAbstractButton::leaveEvent(event);
}

void TitleBarButton::mousePressEvent(QMouseEvent *event)
{
    if(event->button() != Qt::LeftButton)
    {
        return;
    }
    setState(TitleBarButtonState::PRESSED);
    QAbstractButton::mousePressEvent(event);
}

std::tuple<QColor*, QColor*> TitleBarButton::_getColors()
{
    if(this->_state == TitleBarButtonState::NORMAL){
        return std::tuple<QColor *, QColor *>(this->_normalColor, this->_normalBgColor);
    }else if(this->_state == TitleBarButtonState::HOVER){
        return std::tuple<QColor *, QColor *>(this->_hoverColor, this->_hoverBgColor);
    }
    return std::tuple<QColor *, QColor *>(this->_pressedClor, this->_PressedBgColor);
}


SvgTitleBarButton::SvgTitleBarButton(QString iconPath, QWidget *parent) : TitleBarButton(parent)
{
    this->_svgDom = new QDomDocument();
    setIcon(iconPath);
}

void SvgTitleBarButton::setIcon(QString iconPath)
{
    QFile *f = new QFile(iconPath);
    f->open(QFile::ReadOnly);
    this->_svgDom->setContent(f->readAll());
    f->close();
}

void SvgTitleBarButton::paintEvent(QPaintEvent *e)
{
    QPainter *painter = new QPainter(this);
    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    std::tuple<QColor *, QColor *> c = this->_getColors();
    QColor *color = std::get<0>(c);
    QColor *bgColor = std::get<1>(c);

    painter->setBrush(*bgColor);
    painter->setPen(Qt::NoPen);
    painter->drawRect(this->rect());

    QString color_name = color->name();
    QDomNodeList pathNodes = this->_svgDom->elementsByTagName("path");
    int indexes = pathNodes.length();
    for(int i = 0; i < indexes; i++){
        QDomElement element = pathNodes.at(i).toElement();
        element.setAttribute("stroke", color_name);
    }

    QSvgRenderer *renderer = new QSvgRenderer(this->_svgDom->toByteArray());
    renderer->render(painter, QRectF(this->rect()));
    painter->end();
}


void MinimizeButton::paintEvent(QPaintEvent *e)
{
    QPainter *painter = new QPainter(this);
    std::tuple<QColor *, QColor *> c = this->_getColors();
    QColor *color = std::get<0>(c);
    QColor *bgColor = std::get<1>(c);

    painter->setBrush(*bgColor);
    painter->setPen(Qt::NoPen);
    painter->drawRect(this->rect());

    painter->setBrush(Qt::NoBrush);
    QPen *pen = new QPen(*color, 1);
    pen->setCosmetic(true);
    painter->setPen(*pen);
    painter->drawLine(18, 16, 28, 16);
    painter->end();
}

MaximizeButton::MaximizeButton(QWidget *parent) : TitleBarButton(parent)
{
    this->_isMax = false;
}

void MaximizeButton::setMaxState(bool isMax)
{
    if(this->_isMax == isMax)
        return;
    
    this->_isMax = isMax;
    setState(TitleBarButtonState::NORMAL);
}

void MaximizeButton::paintEvent(QPaintEvent *e)
{
    QPainter *painter = new QPainter(this);
    std::tuple<QColor *, QColor *> c = this->_getColors();
    QColor *color = std::get<0>(c);
    QColor *bgColor = std::get<1>(c);

    painter->setBrush(*bgColor);
    painter->setPen(Qt::NoPen);
    painter->drawRect(this->rect());

    painter->setBrush(Qt::NoBrush);
    QPen *pen = new QPen(*color, 1);
    pen->setCosmetic(true);
    painter->setPen(*pen);

    float r = devicePixelRatioF();
    painter->scale(1/r, 1/r);
    if(!this->_isMax){
        painter->drawRect(int(18*r), int(11*r), int(10*r), int(10*r));
    }else{
        painter->drawRect(int(18*r), int(13*r), int(8*r), int(8*r));
        int x0 = int(18*r) + int(2*r);
        int y0 = 13*r;
        int dw = int(2*r);
        QPainterPath path = QPainterPath(QPointF(x0, y0));
        path.lineTo(x0, y0 - dw);
        path.lineTo(x0+8*r, y0-dw);
        path.lineTo(x0+8*r, y0-dw+8*r);
        path.lineTo(x0+8*r-dw, y0-dw+8*r);
        painter->drawPath(path);
    }
    painter->end();

}

CloseButton::CloseButton(QWidget *parent) : SvgTitleBarButton("qfluentwidgets/images/close.svg", parent)
{
    setHoverColor(new QColor(Qt::white));
    setPressedColor(new QColor(Qt::white));
    setHoverBackgroundColor(new QColor(232, 17, 35));
    setPressedBackgroundColor(new QColor(241, 112, 122));
}