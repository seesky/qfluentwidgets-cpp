#include "expand_setting_card.h"

ExpandButton::ExpandButton(QWidget *parent) : QAbstractButton(parent)
{
    this->setFixedSize(30, 30);
    this->__angle = 0;
    this->isHover = false;
    this->isPressed = false;
    this->rotateAni = new QPropertyAnimation(this, "angle", this);
    connect(this, &ExpandButton::clicked, this, &ExpandButton::__onClicked);
}


void ExpandButton::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter.setPen(Qt::NoPen);

    int r = isDarkTheme() ? 255 : 0;
    QColor color;
    if(this->isPressed){
        color = QColor(r, r, r, 10);
    }else if(this->isHover){
        color = QColor(r, r, r, 14);
    }else{
        color = Qt::transparent;
    }

    painter.setBrush(color);
    painter.drawRoundedRect(this->rect(), 4, 4);

    painter.translate(this->width() / 2, this->height() / 2);
    painter.rotate(this->__angle);
    FluentIcon *icon = new FluentIcon();
    icon->setIconName("ARROW_DOWN");
    icon->render(&painter, QRect(-5, -5, 9.6, 9.6), Theme::AUTO, 0, nullptr);
}


void ExpandButton::enterEvent(QEvent *event)
{
    this->setHover(true);
}   

void ExpandButton::leaveEvent(QEvent *event)
{
    this->setHover(false);
}

void ExpandButton::mousePressEvent(QMouseEvent *event)
{
    QAbstractButton::mousePressEvent(event);
    this->setPressed(true);
}

void ExpandButton::mouseReleaseEvent(QMouseEvent *event)
{
    QAbstractButton::mouseReleaseEvent(event);
    this->setPressed(false);
}

void ExpandButton::setHover(bool isHover)
{
    this->isHover = isHover;
    this->update();
}

void ExpandButton::setPressed(bool isPressed)
{
    this->isPressed = isPressed;
    this->update();
}

void ExpandButton::__onClicked()
{
    this->rotateAni->setEndValue(this->getAngle() < 180 ? 180 : 0);
    this->rotateAni->setDuration(200);
    this->rotateAni->start();
}

float ExpandButton::getAngle()
{
    return this->__angle;
}

void ExpandButton::setAngle(float angle)
{
    this->__angle = angle;
    this->update();
}



SpaceWidget::SpaceWidget(QWidget *parent) : QWidget(parent)
{
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setFixedHeight(1);
}


HeaderSettingCard::HeaderSettingCard(QVariant *icon, QString title, QString content, QWidget *parent) : SettingCard(icon, title, content, parent)
{
    this->expandButton = new ExpandButton(this);

    this->hBoxLayout->addWidget(this->expandButton, 0, Qt::AlignRight);
    this->hBoxLayout->addSpacing(8);

    this->installEventFilter(this);
}


bool HeaderSettingCard::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this){
        if(event->type() == QEvent::Enter){
            this->expandButton->setHover(true);
        }else if(event->type() == QEvent::Leave){
            this->expandButton->setHover(false);
        }else if(event->type() == QEvent::MouseButtonPress){
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            if(mouseEvent->button() == Qt::LeftButton){
                this->expandButton->setPressed(true);
            }
        }else if(event->type() == QEvent::MouseButtonRelease){
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            if(mouseEvent->button() == Qt::LeftButton){
                this->expandButton->setPressed(false);
                this->expandButton->click();
            }
        }
    }

    return SettingCard::eventFilter(watched, event);
}


void HeaderSettingCard::addWidget(QWidget *widget)
{
    int N = this->hBoxLayout->count();
    this->hBoxLayout->removeItem(this->hBoxLayout->itemAt(N - 1));
    this->hBoxLayout->addWidget(widget, 0, Qt::AlignRight);
    this->hBoxLayout->addSpacing(19);
    this->hBoxLayout->addWidget(this->expandButton, 0, Qt::AlignRight);
    this->hBoxLayout->addSpacing(8);
}

void HeaderSettingCard::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    if(isDarkTheme()){
        painter.setBrush(QColor(255, 255, 255, 13));
    }else{
        painter.setBrush(QColor(255, 255, 255, 170));
    }

    ExpandSettingCard *p = (ExpandSettingCard*)this->parent();
    QPainterPath path = QPainterPath();
    path.setFillRule(Qt::WindingFill);
    path.addRoundedRect(QRectF(this->rect().adjusted(1, 1, -1, -1)), 6, 6);

    if(p->isExpand){
        path.addRect(1, this->height() - 8, this->width() - 2, 8);
    }

    painter.drawPath(path.simplified());
}


ExpandBorderWidget::ExpandBorderWidget(QWidget *parent) : QWidget(parent)
{
    this->setAttribute(Qt::WA_TransparentForMouseEvents);
    parent->installEventFilter(this);
}

bool ExpandBorderWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this->parent() && event->type() == QEvent::Resize){
        QResizeEvent *mouseEvent = static_cast<QResizeEvent *>(event);
        this->resize(mouseEvent->size());
    }

    return QWidget::eventFilter(watched, event);
}


void ExpandBorderWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setBrush(Qt::NoBrush);

    if(isDarkTheme()){
        painter.setPen(QColor(0, 0, 0, 50));
    }else{
        painter.setPen(QColor(0, 0, 0, 19));
    }

    ExpandSettingCard *p = (ExpandSettingCard*)this->parent();
    int r = 6;
    int d = 12;
    int ch = p->card->height();
    int h = this->height();
    int w = this->width();

    painter.drawRoundedRect(this->rect().adjusted(1, 1, -1, -1), r, r);

    if(ch < h){
        painter.drawLine(1, ch, w - 1, ch);
    }

}




ExpandSettingCard::ExpandSettingCard(QVariant *icon, QString title, QString content, QWidget *parent) : QScrollArea(parent)
{
    this->isExpand = false;

    this->scrollWidget = new QFrame(this);
    this->view = new QFrame(this->scrollWidget);
    this->card = new HeaderSettingCard(icon, title, content, this);

    this->scrollLayout = new QVBoxLayout(this->scrollWidget);
    this->viewLayout = new QVBoxLayout(this->view);
    this->spaceWidget = new SpaceWidget(this->scrollWidget);
    this->borderWidget = new ExpandBorderWidget(this);

    this->expandAni = new QPropertyAnimation(this->verticalScrollBar(), "value", this);

    this->__initWidget();
}


void ExpandSettingCard::__initWidget()
{
    this->setWidget(this->scrollWidget);
    this->setWidgetResizable(true);
    this->setFixedHeight(this->card->height());
    this->setViewportMargins(0, this->card->height(), 0, 0);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->scrollLayout->setContentsMargins(0, 0, 0, 0);
    this->scrollLayout->setSpacing(0);
    this->scrollLayout->addWidget(this->view);
    this->scrollLayout->addWidget(this->spaceWidget);

    this->expandAni->setEasingCurve(QEasingCurve::OutQuad);
    this->expandAni->setDuration(200);

    this->view->setObjectName("view");
    this->scrollWidget->setObjectName("scrollWidget");
    this->setProperty("isExpand", false);

    FluentStyleSheet().apply(this->card, FluentStyleSheetMap.value("EXPAND_SETTING_CARD"), Theme::AUTO);
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("EXPAND_SETTING_CARD"), Theme::AUTO);

    this->card->installEventFilter(this);
    connect(this->expandAni, &QPropertyAnimation::valueChanged, this, &ExpandSettingCard::_onExpandValueChanged);
    connect(this->card->expandButton, &ExpandButton::clicked, this, &ExpandSettingCard::toggleExpand);
}   


void ExpandSettingCard::addWidget(QWidget *widget)
{
    this->card->addWidget(widget);
}

void ExpandSettingCard::wheelEvent(QWheelEvent *e)
{

}

void ExpandSettingCard::setExpand(bool isExpand)
{
    if(this->isExpand == isExpand){
        return;
    }

    this->isExpand = isExpand;
    this->setProperty("isExpand", isExpand);
    this->setStyle(QApplication::style());

    if(isExpand){
        int h = this->viewLayout->sizeHint().height();
        this->verticalScrollBar()->setValue(h);
        this->expandAni->setStartValue(h);
        this->expandAni->setEndValue(0);
    }else{
        this->expandAni->setStartValue(0);
        this->expandAni->setEndValue(this->verticalScrollBar()->maximum());
    }

    this->expandAni->start();
}


void ExpandSettingCard::toggleExpand()
{
    this->setExpand(!this->isExpand);
}

void ExpandSettingCard::resizeEvent(QResizeEvent *event)
{
    this->card->resize(this->width(), this->card->height());
    this->scrollWidget->resize(this->width(), this->scrollWidget->height());
}

void ExpandSettingCard::_onExpandValueChanged()
{
    int vh = this->viewLayout->sizeHint().height();
    int h = this->viewportMargins().top();
    this->setFixedHeight(qMax(h + vh - this->verticalScrollBar()->value(), h));
}


void ExpandSettingCard::_adjustViewSize()
{
    int h = this->viewLayout->sizeHint().height();
    this->spaceWidget->setFixedHeight(h);

    if(this->isExpand){
        this->setFixedHeight(this->card->height() + h);
    }
}

void ExpandSettingCard::setValue()
{

}


GroupSeparator::GroupSeparator(QWidget *parent) : QWidget(parent)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    if(isDarkTheme()){
        painter.setPen(QColor(0, 0, 0, 50));
    }else{
        painter.setPen(QColor(0, 0, 0, 19));
    }

    painter.drawLine(0, 1, this->width(), 1);
}


void GroupSeparator::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    if(isDarkTheme()){
        painter.setPen(QColor(0, 0, 0, 50));
    }else{
        painter.setPen(QColor(0, 0, 0, 19));
    }

    painter.drawLine(0, 1, this->width(), 1);
}


ExpandGroupSettingCard::ExpandGroupSettingCard(QVariant *icon, QString title, QString content, QWidget *parent) : ExpandSettingCard(icon, title, content, parent)
{

}

void ExpandGroupSettingCard::addGroupWidget(QWidget *widget)
{
    if(this->viewLayout->count() >= 1){
        this->viewLayout->addWidget(new GroupSeparator(this->view));
    }

    widget->setParent(this->view);
    this->viewLayout->addWidget(widget);
    this->_adjustViewSize();
}