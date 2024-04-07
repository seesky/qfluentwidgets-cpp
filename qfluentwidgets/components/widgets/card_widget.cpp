#include "card_widget.h"


CardBackgroundColorObject::CardBackgroundColorObject(CardWidget *parent) : BackgroundColorObject(nullptr)
{
    this->_backgroundColor = QColor(parent->_normalBackgroundColor());
}

QColor  CardBackgroundColorObject::getBackgroundColor()
{
    return this->_backgroundColor;
}

void CardBackgroundColorObject::setBackgroundColor(QColor color)
{
    this->_backgroundColor = QColor(color);
    BackgroundColorObject::update();
}


CardWidget::CardWidget(QWidget *parent) : QFrame(parent)
{
    this->isHover = false;
    this->isPressed = false;
    this->bgColorObject = new CardBackgroundColorObject(this);
    this->backgroundColorAni = new QPropertyAnimation(this->bgColorObject, "backgroundColor", this);
    this->backgroundColorAni->setDuration(120);
    this->installEventFilter(this);

    this->_isClickEnabled = false;
    this->_borderRadius = 5;
}



bool CardWidget::eventFilter(QObject *obj, QEvent *e)
{
    if(obj == this)
    {
        if(e->type() == QEvent::Type::EnabledChange)
        {
            if(this->isEnabled())
            {
                this->setBackgroundColor(QColor(this->_normalBackgroundColor()));
            }else{
                this->setBackgroundColor(QColor(this->_disabledBackgroundColor()));
            }
        }
    }
    return QFrame::eventFilter(obj, e);
}

void CardWidget::mousePressEvent(QMouseEvent *e)
{
    this->isPressed = true;
    this->_updateBackgroundColor();
    QFrame::mousePressEvent(e);
}

void CardWidget::mouseReleaseEvent(QMouseEvent *e)
{
    QFrame::mouseReleaseEvent(e);
    this->isPressed = false;
    this->_updateBackgroundColor();
    
    emit(this->clicked());
}

void CardWidget::enterEvent(QEvent *e)
{
    this->isHover = true;
    this->_updateBackgroundColor();
}

void CardWidget::leaveEvent(QEvent *e)
{
    this->isHover = false;
    this->_updateBackgroundColor();
}

void CardWidget::focusInEvent(QFocusEvent *e)
{
    QFrame::focusInEvent(e);
    this->_updateBackgroundColor();
}

QColor CardWidget::_normalBackgroundColor()
{
    return QColor(255, 255, 255, isDarkTheme() ? 13 : 170);
}

QColor CardWidget::_hoverBackgroundColor()
{
    return QColor(255, 255, 255, isDarkTheme() ? 21 : 64);
}

QColor CardWidget::_pressedBackgroundColor()
{
    return QColor(255, 255, 255, isDarkTheme() ? 8 : 64);
}

QColor CardWidget::_focusInBackgroundColor()
{
    return this->_normalBackgroundColor();
}


QColor CardWidget::_disabledBackgroundColor()
{
    return this->_normalBackgroundColor();
}


void CardWidget::_updateBackgroundColor()
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

QColor CardWidget::getBackgroundColor()
{
    return this->bgColorObject->getBackgroundColor();
}

void  CardWidget::setBackgroundColor(QColor color)
{
    this->bgColorObject->setBackgroundColor(color);
}


QColor CardWidget::backgroundColor()
{
    return this->getBackgroundColor();
}


void CardWidget::setClickEnabled(bool isEnabled)
{
    this->_isClickEnabled = isEnabled;
    this->update();
}


bool CardWidget::isClickEnabled()
{
    return this->_isClickEnabled;
}


int CardWidget::getBorderRadius()
{
    return this->_borderRadius;
}

void CardWidget::setBorderRadius(int radius)
{
    this->_borderRadius = radius;
    this->update();
}


void CardWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    int w = this->width();
    int h = this->height();
    int r = this->_borderRadius;
    int d = 2 * r;

    bool isDark = isDarkTheme();

    QPainterPath path = QPainterPath();

    path.arcMoveTo(1, h - d - 1, d, d, 240);
    path.arcTo(1, h - d - 1, d, d, 225, -60);
    path.lineTo(1, r);
    path.arcTo(1, 1, d, d, -180, -90);
    path.lineTo(w - r, 1);
    path.arcTo(w - d - 1, 1, d, d, 90, -90);
    path.lineTo(w - 1, h - r);
    path.arcTo(w - d - 1, h - d - 1, d, d, 0, -60);

    QColor topBorderColor = QColor(0, 0, 0, 20);
    if(isDark){
        if(this->isPressed){
            topBorderColor = QColor(255, 255, 255, 18);
        }else if(this->isHover){
            topBorderColor = QColor(255, 255, 255, 13);
        }
    }else{
        topBorderColor = QColor(0, 0, 0, 15);
    }

    painter.strokePath(path, topBorderColor);

    path = QPainterPath();
    path.arcMoveTo(1, h - d - 1, d, d, 240);
    path.arcTo(1, h - d - 1, d, d, 240, 30);
    path.lineTo(w - r - 1, h - 1);
    path.arcTo(w - d - 1, h - d - 1, d, d, 270, 30);

    QColor bottomBorderColor = topBorderColor;

    if(!isDark && this->isHover && !this->isPressed){
        bottomBorderColor = QColor(0, 0, 0, 27);
    }

    painter.strokePath(path, bottomBorderColor);

    painter.setPen(Qt::NoPen);
    QRect rect = this->rect().adjusted(1, 1, -1, -1);
    painter.setBrush(this->backgroundColor());
    painter.drawRoundedRect(rect, r, r);
}



SimpleCardWidget::SimpleCardWidget(QWidget *parent) : CardWidget(parent)
{

}

QColor SimpleCardWidget::_normalBackgroundColor()
{
    return QColor(255, 255, 255, isDarkTheme() ? 13 : 170);
}

QColor SimpleCardWidget::_hoverBackgroundColor()
{
    return this->_normalBackgroundColor();
}

QColor SimpleCardWidget::_pressedBackgroundColor()
{
    return this->_normalBackgroundColor();
}


void SimpleCardWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setBrush(this->backgroundColor());

    if(isDarkTheme()){
        painter.setPen(QColor(0, 0, 0, 48));
    }else{
        painter.setPen(QColor(0, 0, 0, 12));
    }

    int r = this->getBorderRadius();
    painter.drawRoundedRect(this->rect().adjusted(1, 1, -1, -1), r, r);
}



ElevatedCardWidget::ElevatedCardWidget(QWidget *parent) : SimpleCardWidget(parent)
{
    this->shadowAni = new DropShadowAnimation(this, new QColor(0, 0, 0, 0), new QColor(0, 0, 0, 20));
    this->shadowAni->setOffset(0, 5);
    this->shadowAni->setBlurRadius(38);

    this->elevatedAni = new QPropertyAnimation(this, "pos", this);
    this->elevatedAni->setDuration(100);

    this->_originalPos = this->pos();
    this->setBorderRadius(8);
}


void ElevatedCardWidget::enterEvent(QEvent *e)
{
    SimpleCardWidget::enterEvent(e);
    
    if(this->elevatedAni->state() != QPropertyAnimation::Running){
        this->_originalPos = this->pos();
    }
    
    this->_startElevateAni(this->pos(), this->pos() - QPoint(0, 3));
    
}


void ElevatedCardWidget::leaveEvent(QEvent *e)
{
    SimpleCardWidget::leaveEvent(e);
    
    this->_startElevateAni(this->pos(), this->_originalPos);
    
}


void ElevatedCardWidget::mousePressEvent(QMouseEvent *e)
{
    SimpleCardWidget::mousePressEvent(e);
    this->_startElevateAni(this->pos(), this->_originalPos);
}


void ElevatedCardWidget::_startElevateAni(QPoint start, QPoint end)
{
    this->elevatedAni->setStartValue(start);
    this->elevatedAni->setEndValue(end);
    this->elevatedAni->start();
}   


QColor ElevatedCardWidget::_hoverBackgroundColor()
{
    return isDarkTheme() ? QColor(255, 255, 255, 16) : QColor(255, 255, 255);
}

QColor ElevatedCardWidget::_pressedBackgroundColor()
{
    return QColor(255, 255, 255, isDarkTheme() ? 6 : 118);
}


CardSeparator::CardSeparator(QWidget *parent) : QWidget(parent)
{
    this->setFixedHeight(3);
}

void CardSeparator::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    if(isDarkTheme()){
        painter.setPen(QColor(255, 255, 255, 46));
    }else{
        painter.setPen(QColor(0, 0, 0, 12));
    }

    painter.drawLine(2, 1, this->width() - 2, 1);
}


HeaderCardWidget::HeaderCardWidget(QWidget *parent) : SimpleCardWidget(parent)
{
    this->headerView = new QWidget(this);
    this->headerLabel = new QLabel(this);
    this->separator = new CardSeparator(this);
    this->view = new QWidget(this);

    this->vBoxLayout = new QVBoxLayout(this);
    this->headerLayout = new QHBoxLayout(this->headerView);
    this->viewLayout = new QHBoxLayout(this->view);

    this->headerLayout->addWidget(this->headerLabel);
    this->headerLayout->setContentsMargins(24, 0, 16, 0);
    this->headerView->setFixedHeight(48);

    this->vBoxLayout->setSpacing(0);
    this->vBoxLayout->setContentsMargins(0, 0, 0, 0);
    this->vBoxLayout->addWidget(this->headerView);
    this->vBoxLayout->addWidget(this->separator);
    this->vBoxLayout->addWidget(this->view);

    this->viewLayout->setContentsMargins(24, 24, 24, 24);
    Font().setFont(this->headerLabel, 15, QFont::DemiBold);

    this->view->setObjectName(QString("view"));
    this->headerView->setObjectName(QString("headerView"));
    this->headerLabel->setObjectName(QString("headerLabel"));
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("CARD_WIDGET"), Theme::AUTO);
}


HeaderCardWidget::HeaderCardWidget(QString title, QWidget *parent) : SimpleCardWidget(parent)
{
    this->headerView = new QWidget(this);
    this->headerLabel = new QLabel(this);
    this->separator = new CardSeparator(this);
    this->view = new QWidget(this);

    this->vBoxLayout = new QVBoxLayout(this);
    this->headerLayout = new QHBoxLayout(this->headerView);
    this->viewLayout = new QHBoxLayout(this->view);

    this->headerLayout->addWidget(this->headerLabel);
    this->headerLayout->setContentsMargins(24, 0, 16, 0);
    this->headerView->setFixedHeight(48);

    this->vBoxLayout->setSpacing(0);
    this->vBoxLayout->setContentsMargins(0, 0, 0, 0);
    this->vBoxLayout->addWidget(this->headerView);
    this->vBoxLayout->addWidget(this->separator);
    this->vBoxLayout->addWidget(this->view);

    this->viewLayout->setContentsMargins(24, 24, 24, 24);
    Font().setFont(this->headerLabel, 15, QFont::DemiBold);

    this->view->setObjectName(QString("view"));
    this->headerView->setObjectName(QString("headerView"));
    this->headerLabel->setObjectName(QString("headerLabel"));
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("CARD_WIDGET"), Theme::AUTO);

    this->setTitle(title);
}

QString HeaderCardWidget::getTitle()
{
    return this->headerLabel->text();
}

void HeaderCardWidget::setTitle(QString title)
{
    this->headerLabel->setText(title);
}