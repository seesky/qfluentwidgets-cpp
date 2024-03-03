#include "switch_button.h"

Indicator::Indicator(QWidget *parent) : ToolButton(parent)
{
    this->setCheckable(true);
    this->setFixedSize(42, 22);

    this->_sliderX = 5;
    this->slideAni = new QPropertyAnimation(this, "sliderX", this);
    this->slideAni->setDuration(120);

    connect(this, &Indicator::toggled, this, &Indicator::_toggleSlider);
}

void Indicator::mouseReleaseEvent(QMouseEvent *e)
{
    ToolButton::mouseReleaseEvent(e);
    emit(this->checkedChanged(this->isChecked()));
}


void Indicator::_toggleSlider()
{
    this->slideAni->setEndValue(this->isChecked() ? 25 : 5);
    this->slideAni->start();
}

void Indicator::toggle()
{
    this->setChecked(!this->isChecked());
}

void Indicator::setDown(bool isDown)
{
    this->isPressed = isDown;
    ToolButton::setDown(isDown);
}

void Indicator::setHover(bool isHover)
{
    this->isHover = isHover;
    this->update();
}

void Indicator::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    this->_drawBackground(&painter);
    this->_drawCircle(&painter);
}

void Indicator::_drawBackground(QPainter *painter)
{
    int r = this->height() / 2;
    painter->setPen(this->_borderColor());
    painter->setBrush(this->_backgroudColor());
    painter->drawRoundedRect(this->rect().adjusted(1, 1, -1, -1), r, r);
}

void Indicator::_drawCircle(QPainter *painter)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(this->_sliderColor());
    painter->drawEllipse(int(this->_sliderX), 5, 12, 12);
}

QColor Indicator::_backgroudColor()
{
    bool isDark = isDarkTheme();

    if(this->isChecked()){
        if(!this->isEnabled()){
            return isDark ? QColor(255, 255, 255, 41) : QColor(0, 0, 0, 56);
        }

        if(this->isPressed){
            return *(ThemeColor().color(QString("LIGHT_2")));
        }else if(this->isHover){
            return *(ThemeColor().color(QString("LIGHT_1")));
        }

        return *(ThemeColor().color(QString("PRIMARY")));
    }else{
        if(!this->isEnabled()){
            return QColor(0, 0, 0, 0);
        }

        if(this->isPressed){
            return isDark ? QColor(255, 255, 255, 18) : QColor(0, 0, 0, 23);
        }else if(this->isHover){
            return isDark ? QColor(255, 255, 255, 10) : QColor(0, 0, 0, 15);
        }

        return QColor(0, 0, 0, 0);
    }
}


QColor Indicator::_borderColor()
{
    bool isDark = isDarkTheme();

    if(this->isChecked()){
        return this->isEnabled() ? this->_backgroudColor() : QColor(0, 0, 0, 0);
    }else{
        if(this->isEnabled()){
            return isDark ? QColor(255, 255, 255, 153) : QColor(0, 0, 0, 133);
        }

        return isDark ? QColor(255, 255, 255, 41) : QColor(0, 0, 0, 56);
    }
}

QColor Indicator::_sliderColor()
{
    bool isDark = isDarkTheme();

    if(this->isChecked()){
        if(this->isEnabled()){
            return QColor(isDark ? Qt::black : Qt::white);
        }

        return isDark ? QColor(255, 255, 255, 77) : QColor(255, 255, 255);
    }else{
        if(this->isEnabled()){
            return isDark ? QColor(255, 255, 255, 201) : QColor(0, 0, 0, 156);
        }

        return isDark ? QColor(255, 255, 255, 96) : QColor(0, 0, 0, 91);
    }
}

int Indicator::getSliderX()
{
    return this->_sliderX;
}

void Indicator::setSliderX(int x)
{
    this->_sliderX = qMax(x, 5);
    this->update();
}



SwitchButton::SwitchButton(QWidget *parent, IndicatorPosition indicatorPos = IndicatorPosition::LEFT) : QWidget(parent)
{
    this->_text = this->tr("Off");
    this->_offText = this->tr("Off");
    this->_onText = this->tr("On");
    this->__spacing = 12;

    this->indicatorPos = indicatorPos;
    this->hBox = new QHBoxLayout(this);
    this->indicator = new Indicator(this);
    this->label = new QLabel(this->_text, this);
    this->__initWidget();
}

SwitchButton::SwitchButton(QString text, QWidget *parent, IndicatorPosition indicatorPos) : QWidget(parent)
{
    this->_text = this->tr("Off");
    this->_offText = this->tr("Off");
    this->_onText = this->tr("On");
    this->__spacing = 12;

    this->indicatorPos = indicatorPos;
    this->hBox = new QHBoxLayout(this);
    this->indicator = new Indicator(this);
    this->label = new QLabel(this->_text, this);
    this->__initWidget();

    this->_offText = text;
    this->setText(text);
    
}


void SwitchButton::__initWidget()
{
    this->setAttribute(Qt::WA_StyledBackground);
    this->installEventFilter(this);
    this->setFixedHeight(22);

    this->hBox->setSpacing(this->__spacing);
    this->hBox->setContentsMargins(2, 0, 0, 0);

    if(this->indicatorPos == IndicatorPosition::LEFT){
        this->hBox->addWidget(this->indicator);
        this->hBox->addWidget(this->label);
        this->hBox->setAlignment(Qt::AlignRight);
    }else{
        this->hBox->addWidget(this->label, 0, Qt::AlignRight);
        this->hBox->addWidget(this->indicator, 0, Qt::AlignRight);
        this->hBox->setAlignment(Qt::AlignRight);
    }

    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("SWITCH_BUTTON"), Theme::AUTO);

    connect(this->indicator, &Indicator::toggled, this, &SwitchButton::_updateText);
    connect(this->indicator, &Indicator::toggled, this, &SwitchButton::checkedChanged);
}

bool SwitchButton::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this && this->isEnabled()){
        if(event->type() == QEvent::MouseButtonPress){
            this->indicator->setDown(true);
        }else if(event->type() == QEvent::MouseButtonRelease){
            this->indicator->setDown(false);
            this->indicator->toggle();
        }else if(event->type() == QEvent::Enter){
            this->indicator->setHover(true);
        }else if(event->type() == QEvent::Leave){
            this->indicator->setHover(false);
        }
    }

    return QWidget::eventFilter(watched, event);
}

bool SwitchButton::isChecked()
{
    return this->indicator->isChecked();
}

void SwitchButton::setChecked(bool isChecked)
{
    this->_updateText();
    this->indicator->setChecked(isChecked);
}

void SwitchButton::toggleChecked()
{
    this->indicator->setChecked(!this->indicator->isChecked());
}

void SwitchButton::_updateText()
{
    this->setText(this->isChecked() ? this->_onText : this->_offText);
    this->adjustSize();
}

QString SwitchButton::getText()
{
    return this->_text;
}

void SwitchButton::setText(QString text)
{
    this->_text = text;
    this->label->setText(text);
    this->adjustSize();        
}

int SwitchButton::getSpacing()
{
    return this->__spacing;
}

void SwitchButton::setSpacing(int spacing)
{
    this->__spacing = spacing;
    this->hBox->setSpacing(spacing);
    this->update();
}

QString SwitchButton::getOnText()
{
    return this->_onText;
}

void SwitchButton::setOnText(QString text)
{
    this->_onText = text;
    this->_updateText();
}

QString SwitchButton::getOffText()
{
    return this->_offText;
}

void SwitchButton::setOffText(QString text)
{
    this->_onText = text;
    this->_updateText();
}