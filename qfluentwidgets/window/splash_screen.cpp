#include "splash_screen.h"

SplashScreen::SplashScreen(QVariant *icon, QWidget *parent = nullptr, bool enableShadow = true) : QWidget(parent)
{
    this->_icon = icon;
    this->_iconSize = QSize(96, 96);

    this->titleBar = new TitleBar(this);
    this->iconWidget = new IconWidget(icon, this);
    this->shadowEffect = new QGraphicsDropShadowEffect(this);

    this->iconWidget->setFixedSize(this->_iconSize);
    this->shadowEffect->setColor(QColor(0, 0, 0, 50));
    this->shadowEffect->setBlurRadius(15);
    this->shadowEffect->setOffset(0, 4);

    FluentStyleSheet().apply(this->titleBar, FluentStyleSheetMap.value("FLUENT_WINDOW"), Theme::AUTO);

    if(enableShadow){
        this->iconWidget->setGraphicsEffect(this->shadowEffect);
    }

    if(parent != nullptr){
        parent->installEventFilter(this);
    }
}


void SplashScreen::setIcon(QVariant *icon)
{
    this->_icon = icon;
    this->update();
}

QIcon SplashScreen::icon()
{
    return MIcon().toQIcon(this->_icon);
}

void SplashScreen::setIconSize(QSize size)
{
    this->_iconSize = size;
    this->iconWidget->setFixedSize(size);
    this->update();
}


QSize SplashScreen::iconSize()
{
    return this->_iconSize;
}

void SplashScreen::setTitleBar(QWidget *titleBar)
{
    this->titleBar->deleteLater();
    this->titleBar = titleBar;
    titleBar->setParent(this);
    titleBar->raise();
    this->titleBar->resize(this->width(), this->titleBar->height());
}

bool SplashScreen::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this->parent()){
        if(event->type() == QEvent::Resize){
            QResizeEvent *re = dynamic_cast<QResizeEvent*>(event);
            this->resize(re->size());
        }else if(event->type() == QEvent::ChildAdded){
            this->raise();
        }
    }

    return QWidget::eventFilter(watched, event);
}

void SplashScreen::resizeEvent(QResizeEvent *event)
{
    int iw = this->iconSize().width();
    int ih = this->iconSize().height();
    this->iconWidget->move(this->width() / 2 - iw / 2, this->height() / 2 - ih / 2);
    this->titleBar->resize(this->width(), this->titleBar->height());
}

void SplashScreen::finish()
{
    this->close();
}

void SplashScreen::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);

    int c = isDarkTheme() ? 32 : 255;
    painter.setBrush(QColor(c, c, c));
    painter.drawRect(this->rect());
}