#include "time_picker.h"

TimePickerBase::TimePickerBase(QWidget *parent, bool showSeconds) : PickerBase(parent)
{
    this->_isSecondVisible = showSeconds;
    this->_time = new QTime();
}

QTime *TimePickerBase::getTime()
{
    return this->_time;
}

bool TimePickerBase::isSecondVisible()
{
    return this->_isSecondVisible;
}


QString MiniuteFormatter::encode(QVariant value)
{
    if(value.canConvert<QString>()){
        return value.value<QString>().rightJustified(2, QChar('0'));
    }else if(value.canConvert<int>()){
        return QString::number(value.value<int>()).rightJustified(2, QChar('0'));
    }
}


QString AMHourFormatter::encode(QVariant value)
{
    if(value.canConvert<QString>()){
        int hour = value.value<QString>().toInt();
        if(0 == hour || hour == 12){
            return QString("12");
        }
        return QString::number(hour % 12);
    }else if(value.canConvert<int>()){
        int hour = value.value<int>();
        if(0 == hour || hour == 12){
            return QString("12");
        }
        return QString::number(hour % 12);
    }
}



AMPMFormatter::AMPMFormatter() : PickerColumnFormatter()
{
    this->AM = this->tr("AM");
    this->PM = this->tr("PM");
}

QString AMPMFormatter::encode(QVariant value)
{
    if(value.canConvert<QString>()){
        bool isNumeric = false;
        value.value<QString>().toInt(&isNumeric);
        if(!isNumeric){
            return value.value<QString>();
        }
    }

    int hour = value.value<int>();
    return hour < 12 ? this->AM : this->PM;
}


TimePicker::TimePicker(QWidget *parent, bool showSeconds) : TimePickerBase(parent, showSeconds)
{
    int w = showSeconds ? 80 : 120;

    //add hour column
    QList<QString> *hourList = new QList<QString>();
    for(int i = 0; i < 24; i++){
        hourList->append(QString::number(i));
    }
    this->addColumn(this->tr("hour"), hourList, w, Qt::AlignCenter, new DigitFormatter());

    //add minute column
    QList<QString> *minuteList = new QList<QString>();
    for(int i = 0; i < 60; i++){
        minuteList->append(QString::number(i));
    }
    this->addColumn(this->tr("minute"), minuteList, w, Qt::AlignCenter, new MiniuteFormatter());

    //add seconds column
    QList<QString> *secondList = new QList<QString>();
    for(int i = 0; i < 60; i++){
        secondList->append(QString::number(i));
    }
    this->addColumn(this->tr("second"), secondList, w, Qt::AlignCenter, new MiniuteFormatter());

    this->setColumnVisible(this, 2, showSeconds);
}


void TimePicker::setTime(QTime *time)
{
    if(!time->isValid() || time->isNull()){
        return;
    }

    this->_time = time;
    this->setColumnValue(this, 0, QString::number(time->hour()));
    this->setColumnValue(this, 1, QString::number(time->minute()));
    this->setColumnValue(this, 2, QString::number(time->second()));
}

void TimePicker::setSecondVisible(bool isVisible)
{
    this->_isSecondVisible = isVisible;
    this->setColumnVisible(this, 2, isVisible);

    int w = isVisible ? 80 : 120;
    for(int i = 0; i < this->columns->length(); i++){
        this->columns->at(i)->setFixedWidth(w);
    }
}

void TimePicker::_onConfirmed(QList<QString> *value)
{
    TimePickerBase::_onConfirmed(value);
    int h = this->decodeValue(this, 0, value->at(0)).value<int>();
    int m = this->decodeValue(this, 1, value->at(1)).value<int>();
    int s = value->length() == 2 ? 0 : this->decodeValue(this, 2, value->at(2)).value<int>();

    QTime *time = new QTime(h, m, s);
    QTime *ot = this->getTime(); //TODO:特殊关注
    this->setTime(time);

    if(*ot != *time){
        emit this->timeChanged(*time);
    }

    delete ot; //TODO:特殊关注
}


QList<QString> *TimePicker::panelInitialValue()
{
    for(int i = 0; i < this->value()->length(); i++){
        if(this->value()->at(i).isEmpty()){
            return this->value();
        }
    }

    QTime time = QTime::currentTime();
    int h = this->decodeValue(this, 0, QString::number(time.hour())).value<int>();
    int m = this->decodeValue(this, 1, QString::number(time.minute())).value<int>();
    int s = this->decodeValue(this, 2, QString::number(time.second())).value<int>();

    QList<QString> *list = new QList<QString>();
    if(this->isSecondVisible()){
        list->append(QString::number(h));
        list->append(QString::number(m));
        list->append(QString::number(s));
    }else{
        list->append(QString::number(h));
        list->append(QString::number(m));
    }

    return list;
}

QTime *TimePicker::getTime()
{
    return this->_time;
}

bool TimePicker::isSecondVisible()
{
    return this->_isSecondVisible;
}


AMTimePicker::AMTimePicker(QWidget *parent, bool showSeconds) : TimePickerBase(parent, showSeconds)
{
    this->AM = this->tr("AM");
    this->PM = this->tr("PM");

    //add hour column
    QList<QString> *hourList = new QList<QString>();
    for(int i = 1; i < 13; i++){
        hourList->append(QString::number(i));
    }
    this->addColumn(this->tr("hour"), hourList, 80, Qt::AlignCenter, new AMHourFormatter());

    //add minute column
    QList<QString> *minuteList = new QList<QString>();
    for(int i = 0; i < 60; i++){
        minuteList->append(QString::number(i));
    }
    this->addColumn(this->tr("minute"), minuteList, 80, Qt::AlignCenter, new MiniuteFormatter());

    //add second column
    QList<QString> *secondList = new QList<QString>();
    for(int i = 0; i < 60; i++){
        secondList->append(QString::number(i));
    }
    this->addColumn(this->tr("second"), secondList, 80, Qt::AlignCenter, new MiniuteFormatter());

    this->setColumnVisible(this, 2, showSeconds);

    //add AM/PM column
    QList<QString> *apList = new QList<QString>();
    apList->append(this->AM);
    apList->append(this->PM);
    this->addColumn(this->AM, apList, 80, Qt::AlignCenter, new AMPMFormatter());
}


void AMTimePicker::setSecondVisible(bool isVisible)
{
    this->_isSecondVisible = isVisible;
    this->setColumnVisible(this, 2, isVisible);
}

void AMTimePicker::setTime(QTime *time)
{
    if(!time->isValid() || time->isNull()){
        return;
    }

    this->_time = time;
    this->setColumnValue(this, 0, QString::number(time->hour()));
    this->setColumnValue(this, 1, QString::number(time->minute()));
    this->setColumnValue(this, 2, QString::number(time->second()));
    this->setColumnValue(this, 3, QString::number(time->hour()));
}

void AMTimePicker::_onConfirmed(QList<QString> *value)
{
    TimePickerBase::_onConfirmed(value);

    QString h,m,s,p;
    if(value->length() == 3){
        h = value->at(0);
        m = value->at(1);
        p = value->at(2);
        s = QString::number(0);
    }else{
        h = value->at(0);
        m = value->at(1);
        s = value->at(2);
        p = value->at(3);
        s = this->decodeValue(this, 2, s).value<QString>();
    }

    h = this->decodeValue(this, 0, h).value<QString>();
    m = this->decodeValue(this, 1, m).value<QString>();

    if(p == this->AM){
        h = h.toInt() == 12 ? QString::number(0) : h;
    }else if(p == this->PM){
        h = h.toInt() == 12 ? h : QString::number(h.toInt() + 12);
    }

    QTime *time = new QTime(h.toInt(), m.toInt(), s.toInt());
    QTime *ot = this->getTime();
    this->setTime(time);

    if(*ot != *time){
        emit this->timeChanged(*time);
    }

    delete ot; //TODO:特殊关注
}

QList<QString> *AMTimePicker::panelInitialValue()
{
    for(int i = 0; i < this->value()->length(); i++){
        if(this->value()->at(i).isEmpty()){
            return this->value();
        }
    }

    QTime time = QTime::currentTime();
    int h = this->decodeValue(this, 0, QString::number(time.hour())).value<int>();
    int m = this->decodeValue(this, 1, QString::number(time.minute())).value<int>();
    int s = this->decodeValue(this, 2, QString::number(time.second())).value<int>();
    int p = this->decodeValue(this, 3, QString::number(time.hour())).value<int>();

    QList<QString> *list = new QList<QString>();
    if(this->isSecondVisible()){
        list->append(QString::number(h));
        list->append(QString::number(m));
        list->append(QString::number(s));
        list->append(QString::number(p));
    }else{
        list->append(QString::number(h));
        list->append(QString::number(m));
        list->append(QString::number(p));
    }

    return list;
}


QTime *AMTimePicker::getTime()
{
    return this->_time;
}

bool AMTimePicker::isSecondVisible()
{
    return this->_isSecondVisible;
}