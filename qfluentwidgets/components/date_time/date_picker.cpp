#include "date_picker.h"

MonthFormatter::MonthFormatter() : PickerColumnFormatter()
{
    this->months = new QList<QString>();
    this->months->append(this->tr("January"));
    this->months->append(this->tr("February"));
    this->months->append(this->tr("March"));
    this->months->append(this->tr("April"));
    this->months->append(this->tr("May"));
    this->months->append(this->tr("June"));
    this->months->append(this->tr("July"));
    this->months->append(this->tr("August"));
    this->months->append(this->tr("September"));
    this->months->append(this->tr("October"));
    this->months->append(this->tr("November"));
    this->months->append(this->tr("December"));
}

QString MonthFormatter::encode(QVariant value)
{
    if(value.canConvert<QString>()){
        //qDebug() << value.value<QString>();
        return this->months->at(value.value<QString>().toInt() - 1);
    }else if(value.canConvert<int>()){
        return this->months->at(value.value<int>() - 1);
    }
}

QVariant MonthFormatter::decode(QString value)
{
    return QVariant::fromValue<int>(this->months->indexOf(value) + 1);
}

DatePickerBase::DatePickerBase(QWidget *parent) : PickerBase(parent)
{
    this->_date = new QDate();
    this->calendar = new QCalendar();
    this->_yearFormatter = nullptr;
    this->_monthFormatter = nullptr;
    this->_dayFormatter = nullptr;
}

QDate *DatePickerBase::getDate()
{
    return this->_date;
}

void DatePickerBase::setDate(QDate *date)
{

}

void DatePickerBase::setYearFormatter(PickerColumnFormatter *formatter)
{
    this->_yearFormatter = formatter;
}

void DatePickerBase::setMonthFormatter(PickerColumnFormatter *formatter)
{
    this->_monthFormatter = formatter;
}

void DatePickerBase::setDayFormatter(PickerColumnFormatter *formatter)
{
    this->_dayFormatter = formatter;
}

PickerColumnFormatter *DatePickerBase::yearFormatter()
{
    if(this->_yearFormatter != nullptr){
        return this->_yearFormatter;
    }else{
        return new DigitFormatter();
    }
}

PickerColumnFormatter *DatePickerBase::dayFormatter()
{
    if(this->_dayFormatter != nullptr){
        return this->_dayFormatter;
    }else{
        return new DigitFormatter();
    }
}

PickerColumnFormatter *DatePickerBase::monthFormatter()
{
    if(this->_monthFormatter != nullptr){
        return this->_monthFormatter;
    }else{
        return new MonthFormatter();
    }
}


DatePicker::DatePicker(QWidget *parent, int format = DatePicker::MM_DD_YYYY, bool isMonthTight = true) : DatePickerBase(parent)
{
    this->MONTH = this->tr("month");
    this->YEAR = this->tr("year");
    this->DAY = this->tr("day");
    this->isMonthTight = isMonthTight;
    this->setDateFormat(format);
}

void DatePicker::setDateFormat(int format)
{
    this->clearColumns();
    int y = QDate::currentDate().year();
    this->dateFormat = format;

    if(format == this->MM_DD_YYYY){
        this->monthIndex = 0;
        this->dayIndex = 1;
        this->yearIndex = 2;

        QList<QString> *monthList = new QList<QString>();
            for(int i = 1; i < 13; i++){
            monthList->append(QString::number(i));
        }
        this->addColumn(this->MONTH, monthList, 80, Qt::AlignLeft, this->monthFormatter());

        QList<QString> *dayList = new QList<QString>();
        for(int i = 1; i < 32; i++){
            dayList->append(QString::number(i));
        }
        this->addColumn(this->DAY, dayList, 80, Qt::AlignCenter, this->dayFormatter());

        QList<QString> *yearList = new QList<QString>();
        for(int i = y - 100; i < y + 101; i++){
            yearList->append(QString::number(i));
        }
        this->addColumn(this->YEAR, yearList, 80, Qt::AlignCenter, this->yearFormatter());

    }else if(format == this->YYYY_MM_DD){
        this->monthIndex = 1;
        this->dayIndex = 2;
        this->yearIndex = 0;

        QList<QString> *yearList = new QList<QString>();
        for(int i = y - 100; i < y + 101; i++){
            yearList->append(QString::number(i));
        }
        this->addColumn(this->YEAR, yearList, 80, Qt::AlignCenter, this->yearFormatter());

        QList<QString> *monthList = new QList<QString>();
        for(int i = 1; i < 13; i++){
            monthList->append(QString::number(i));
        }
        this->addColumn(this->MONTH, monthList, 80, Qt::AlignLeft, this->monthFormatter());

        QList<QString> *dayList = new QList<QString>();
        for(int i = 1; i < 32; i++){
            dayList->append(QString::number(i));
        }
        this->addColumn(this->DAY, dayList, 80, Qt::AlignCenter, this->dayFormatter());

        
    }

    this->setColumnWidth(this, this->monthIndex, this->_monthColumnWidth());

}

QList<QString> * DatePicker::panelInitialValue()
{
    for(int i = 0; i < this->value()->length(); i++){
        if(!this->value()->at(i).isEmpty()){
            return this->value();
        }
    }

    QDate date = QDate::currentDate();
    QString y = this->encodeValue(this, this->yearIndex, QString::number(date.year()));
    QString m = this->encodeValue(this, this->monthIndex, QString::number(date.month()));
    QString d = this->encodeValue(this, this->dayIndex, QString::number(date.day()));

    QList<QString> *list = new QList<QString>();
    if(this->dateFormat == this->YYYY_MM_DD){
        list->append(y);
        list->append(m);
        list->append(d);
    }else{
        list->append(m);
        list->append(d);
        list->append(y);
    }

    return list;
}

void DatePicker::setMonthTight(bool isTight)
{
    if(this->isMonthTight == isTight){
        return;
    }

    this->isMonthTight = isTight;
    this->setColumnWidth(this, this->monthIndex, this->_monthColumnWidth());
}

int DatePicker::_monthColumnWidth()
{
    QFontMetrics fm = this->fontMetrics();
    int wm = 0;
    for(int i = 0; i < this->columns->at(this->monthIndex)->items()->length(); i++){
        if(this->columns->at(this->monthIndex)->items()->at(i).value<int>() > wm){
            wm = this->columns->at(this->monthIndex)->items()->at(i).value<int>();
        }
    }
    wm = wm + 20;

    if(this->MONTH == QString("month")){
        return wm + 49;
    }

    return this->isMonthTight ? qMax(80, wm) : wm + 49;
}

void DatePicker::_onColumnValueChanged(PickerPanel *panel, int index, QString value)
{
    if(index == this->dayIndex){
        return;
    }

    QString month = this->decodeValue(this, this->monthIndex, panel->columnValue(this->monthIndex)).value<QString>();
    QString year = this->decodeValue(this, this->yearIndex, panel->columnValue(this->yearIndex)).value<QString>();
    int days = this->calendar->daysInMonth(month.toInt(), year.toInt());

    CycleListWidget *c = panel->column(this->dayIndex);
    QString day = c->currentItem()->text();

    QList<QString> *dayList = new QList<QString>();
    for(int i = 1; i < days + 1; i++){
        dayList->append(QString::number(i));
    }
    this->setColumnItems(this, this->dayIndex, dayList);

    c->setItems(this->columns->at(this->dayIndex)->items());

    c->setSelectedItem(day);
}

void DatePicker::_onConfirmed(QList<QString> *value)
{
    QString year = this->decodeValue(this, this->yearIndex, value->at(this->yearIndex)).value<QString>();
    QString month = this->decodeValue(this, this->monthIndex, value->at(this->monthIndex)).value<QString>();
    QString day = this->decodeValue(this, this->dayIndex, value->at(this->dayIndex)).value<QString>();
    QDate *date = new QDate(year.toInt(), month.toInt(), day.toInt());
    QDate *od = this->_date;

    this->setDate(date);

    if(*od != *date){
        emit(this->dateChanged(*date));
    }
}


QDate *DatePicker::getDate()
{
    return this->_date;
}

void DatePicker::setDate(QDate *date)
{
    if(!date->isValid() || date->isNull()){
        return;
    }

    this->_date = date;
    //qDebug() << *date;
    this->setColumnValue(this, this->monthIndex, QString::number(date->month()));
    this->setColumnValue(this, this->dayIndex, QString::number(date->day()));
    this->setColumnValue(this, this->yearIndex, QString::number(date->year()));

    QList<QString> *list = new QList<QString>();
    for(int i = 1; i < date->daysInMonth() + 1; i++){
        list->append(QString::number(i));
    }

    this->setColumnItems(this, this->dayIndex, list);
}

QString ZhFormatter::encode(QVariant value)
{
    if(value.canConvert<QString>()){
        return value.value<QString>() + this->suffix;
    }else if(value.canConvert<int>()){
        return QString::number(value.value<int>()) + this->suffix;
    }
}

QVariant ZhFormatter::decode(QString value)
{
    return value.left(value.length() - 1).toInt();
}


ZhDatePicker::ZhDatePicker(QWidget *parent) : DatePicker(parent, DatePicker::YYYY_MM_DD, true)
{
    this->MONTH = "月";
    this->YEAR = "年";
    this->DAY = "日";
    this->setDayFormatter(new ZhDayFormatter());
    this->setYearFormatter(new ZhYearFormatter());
    this->setMonthFormatter(new ZhMonthFormatter());
    this->setDateFormat(this->YYYY_MM_DD);
}