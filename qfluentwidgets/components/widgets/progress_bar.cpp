#include "progress_bar.h"

ProgressBar::ProgressBar(QWidget *parent, bool useAni) : QProgressBar(parent)
{
    this->_val = 0;
    this->setFixedHeight(4);

    this->_useAni = useAni;
    this->lightBackgroundColor = QColor(0, 0, 0, 155);
    this->darkBackgroundColor = QColor(255, 255, 255, 155);
    this->_lightBarColor = QColor();
    this->_darkBarColor = QColor();
    this->ani = new QPropertyAnimation(this, "val", this);

    this->_isPaused = false;
    this->_isError = false;
    connect(this, &ProgressBar::valueChanged, this, &ProgressBar::_onValueChanged);
    this->setVal(0);
}

float ProgressBar::getVal()
{
    return this->_val;
}

void ProgressBar::setVal(float v)
{
    this->_val = v;
    this->update();
}

bool ProgressBar::isUseAni()
{
    return this->_useAni;
}   

void ProgressBar::setUseAni(bool isUse)
{
    this->_useAni = isUse;
}

void ProgressBar::_onValueChanged(float value)
{
    if(!this->_useAni){
        this->_val = value;
        return;
    }

    this->ani->stop();
    this->ani->setEndValue(value);
    this->ani->setDuration(150);
    this->ani->start();
    QProgressBar::setValue(value);
}


QColor ProgressBar::lightBarColor()
{
    return this->_lightBarColor.isValid() ? this->_lightBarColor : *(ThemeColor().themeColor());
}

QColor ProgressBar::darkBarColor()
{
    return this->_darkBarColor.isValid() ? this->_darkBarColor : *(ThemeColor().themeColor());
}

void ProgressBar::setCustomBarColor(QVariant *light, QVariant *dark)
{
    this->_lightBarColor = QColor(light->value<QString>()); //TODO:特殊关注
    this->_darkBarColor = QColor(dark->value<QString>());
    this->update();
}

void ProgressBar::setCustomBackgroundColor(QVariant *light, QVariant *dark)
{
    this->lightBackgroundColor = QColor(light->value<QString>()); //TODO:特殊关注
    this->darkBackgroundColor = QColor(dark->value<QString>());
    this->update();
}

void ProgressBar::resume()
{
    this->_isPaused = false;
    this->_isError = false;
    this->update();
}

void ProgressBar::pause()
{
    this->_isPaused = true;
    this->update();
}

void ProgressBar::setPaused(bool isPaused)
{
    this->_isPaused = isPaused;
    this->update();
}

bool ProgressBar::isPaused()
{
    return this->_isPaused;
}

void ProgressBar::error()
{
    this->_isError = true;
    this->update();
}

void ProgressBar::setError(bool isError)
{
    this->_isError = isError;
    if(isError){
        this->error();
    }else{
        this->resume();
    }
}


bool ProgressBar::isError()
{
    return this->_isError;
}

QColor ProgressBar::barColor()
{
    if(this->isPaused()){
        return isDarkTheme() ? QColor(252, 225, 0) : QColor(157, 93, 0);
    }

    if(this->isError()){
        return isDarkTheme() ? QColor(255, 153, 164) : QColor(196, 43, 28);
    }

    return isDarkTheme() ? this->darkBarColor() : this->lightBarColor();
}

QString ProgressBar::valText()
{
    if(this->maximum() <= this->minimum()){
        return QString("");
    }

    int total = this->maximum() - this->minimum();
    QString result = this->format();
    QLocale locale =  this->locale();
    locale.setNumberOptions(locale.numberOptions() | QLocale::OmitGroupSeparator);
    result = result.replace("%m", locale.toString(total));
    result = result.replace("%v", locale.toString(this->getVal()));

    if(total == 0){
        return result.replace("%p", locale.toString(100));
    }

    int progress = (this->getVal() - this->minimum()) * 100 / total; //TODO：确认是否是小数
    return result.replace("%p", locale.toString(progress));
}


void ProgressBar::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    QColor bc = isDarkTheme() ? this->darkBackgroundColor : this->lightBackgroundColor;
    painter.setPen(bc);
    double y = floor(float(this->height()) / 2);
    painter.drawLine(0, y, this->width(), y);

    if(this->minimum() >= this->maximum()){
        return;
    }

    painter.setPen(Qt::NoPen);
    QColor _themeColor = this->barColor();
    painter.setBrush(this->barColor());

    int w = this->getVal() / (this->maximum() - this->minimum()) * this->width();
    float r = float(this->height()) / 2;
    painter.drawRoundedRect(0, 0, w, this->height(), r, r); 
}


IndeterminateProgressBar::IndeterminateProgressBar(QWidget *parent, bool start = true) : QProgressBar(parent)
{
    this->_shortPos = 0;
    this->_longPos = 0;
    this->shortBarAni = new QPropertyAnimation(this, "shortPos", this);
    this->longBarAni = new QPropertyAnimation(this, "longPos", this);

    this->_lightBarColor = QColor();
    this->_darkBarColor = QColor();

    this->_isError = false;

    this->aniGroup = new QParallelAnimationGroup(this);
    this->longBarAniGroup = new QSequentialAnimationGroup(this);

    this->shortBarAni->setDuration(833);
    this->longBarAni->setDuration(1167);
    this->shortBarAni->setStartValue(0);
    this->longBarAni->setStartValue(0);
    this->shortBarAni->setEndValue(1.45);
    this->longBarAni->setEndValue(1.75);
    this->longBarAni->setEasingCurve(QEasingCurve::OutQuad);

    this->aniGroup->addAnimation(this->shortBarAni);
    this->longBarAniGroup->addPause(785);
    this->longBarAniGroup->addAnimation(this->longBarAni);
    this->aniGroup->addAnimation(this->longBarAniGroup);
    this->aniGroup->setLoopCount(-1);

    this->setFixedHeight(4);

    if(start){
        this->start();
    }
}


QColor IndeterminateProgressBar::lightBarColor()
{
    return this->_lightBarColor.isValid() ? this->_lightBarColor : *(ThemeColor().themeColor());
}


QColor IndeterminateProgressBar::darkBarColor()
{
    return this->_darkBarColor.isValid() ? this->_darkBarColor : this->_darkBarColor;
}   

void IndeterminateProgressBar::setCustomBarColor(QVariant *light, QVariant *dark)
{
    this->_lightBarColor = QColor(light->value<QString>());
    this->_darkBarColor = QColor(dark->value<QString>());
    this->update();
}

float IndeterminateProgressBar::getShortPos()
{
    return this->_shortPos;
}

void IndeterminateProgressBar::setShortPos(float p)
{
    this->_shortPos = p;
    this->update();
}

float IndeterminateProgressBar::getLongPos()
{
    return this->_longPos;
}

void IndeterminateProgressBar::setLongPos(float p)
{
    this->_longPos = p;
    this->update();
}

void IndeterminateProgressBar::start()
{
    this->setShortPos(0);
    this->setLongPos(0);
    this->aniGroup->start();
    this->update();
}

void IndeterminateProgressBar::stop()
{
    this->aniGroup->stop();
    this->setShortPos(0);
    this->setLongPos(0);
    this->update();
}

bool IndeterminateProgressBar::isStarted()
{
    return this->aniGroup->state() == QParallelAnimationGroup::Running;
}

void IndeterminateProgressBar::pause()
{
    this->aniGroup->pause();
    this->update();
}

void IndeterminateProgressBar::resume()
{
    this->aniGroup->resume();
    this->update();
}

void IndeterminateProgressBar::setPaused(bool isPaused)
{
    this->aniGroup->setPaused(isPaused);
    this->update();
}

bool IndeterminateProgressBar::isPaused()
{
    return this->aniGroup->state() == QParallelAnimationGroup::Paused;
}

void IndeterminateProgressBar::error()
{
    this->_isError = true;
    this->aniGroup->stop();
    this->update();
}

void IndeterminateProgressBar::setError(bool isError)
{
    this->_isError = isError;
    if(isError){
        this->error();
    }else{
        this->start();
    }
}


bool IndeterminateProgressBar::isError()
{
    return this->_isError;
}

QColor IndeterminateProgressBar::barColor()
{
    if(this->isError()){
        return isDarkTheme() ? QColor(255, 153, 164) : QColor(196, 43, 28);
    }

    if(this->isPaused()){
        return isDarkTheme() ? QColor(252, 225, 0) : QColor(157, 93, 0);
    }

    return isDarkTheme() ? this->darkBarColor() : this->lightBarColor();
}


void IndeterminateProgressBar::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    painter.setPen(Qt::NoPen);
    painter.setBrush(this->barColor());

    int x = (this->getShortPos() - 0.4) * this->width();
    int w = 0.4 * this->width();
    float r = float(this->height()) / 2;
    painter.drawRoundedRect(x, 0, w, this->height(), r, r);

    x = (this->getLongPos() - 0.6) * this->width();
    w = 0.6 * this->width();
    r = float(this->height()) / 2;
    painter.drawRoundedRect(x, 0, w, this->height(), r, r);
}