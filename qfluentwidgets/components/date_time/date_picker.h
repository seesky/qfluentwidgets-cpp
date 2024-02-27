#pragma once

#include <QtCore/Qt>
#include <QtCore/QDate>
#include <QtCore/QCalendar>
#include "picker_base.h"

class MonthFormatter : public PickerColumnFormatter{
    Q_OBJECT
public:
    MonthFormatter();
    QString encode(QVariant value) override;
    QVariant decode(QString value) override;

    QList<QString> *months;
};

class DatePickerBase : public PickerBase{
    Q_OBJECT
public:
    DatePickerBase(QWidget *parent);
    virtual QDate *getDate();
    virtual void setDate(QDate *date);
    void setYearFormatter(PickerColumnFormatter *formatter);
    void setMonthFormatter(PickerColumnFormatter *formatter);
    void setDayFormatter(PickerColumnFormatter *formatter);
    PickerColumnFormatter *yearFormatter();
    PickerColumnFormatter *dayFormatter();
    PickerColumnFormatter *monthFormatter();

    QDate *_date;
    QCalendar *calendar;
    PickerColumnFormatter *_yearFormatter;
    PickerColumnFormatter *_monthFormatter;
    PickerColumnFormatter *_dayFormatter;

signals:
    void dateChanged(QDate);
};


class DatePicker : public DatePickerBase{
    Q_OBJECT
public:
    DatePicker(QWidget *parent, int format, bool isMonthTight);
    void setDateFormat(int format);
    QList<QString> * panelInitialValue() override;
    void setMonthTight(bool isTight);
    int _monthColumnWidth();
    void _onColumnValueChanged(PickerPanel *panel, int index, QString value);
    void _onConfirmed(QList<QString> *value) override;
    QDate *getDate();
    void setDate(QDate *date);

    const static int MM_DD_YYYY = 0;
    const static int YYYY_MM_DD = 1;
    QString MONTH;
    QString YEAR;
    QString DAY;
    bool isMonthTight;
    int dateFormat;
    int monthIndex;
    int dayIndex;
    int yearIndex;
};


class ZhFormatter : public PickerColumnFormatter{
    Q_OBJECT
public:
    ZhFormatter(){this->suffix = "";}
    QString encode(QVariant value) override;
    QVariant decode(QString value) override;

    QString suffix;
};


class ZhYearFormatter : public ZhFormatter{
    Q_OBJECT
public:
    ZhYearFormatter(){this->suffix = "年";};
};

class ZhMonthFormatter : public ZhFormatter{
    Q_OBJECT
public:
    ZhMonthFormatter(){this->suffix = "月";};
};

class ZhDayFormatter : public ZhFormatter{
    Q_OBJECT
public:
    ZhDayFormatter(){this->suffix = "日";};
};


class ZhDatePicker : public DatePicker{
    Q_OBJECT
public:
    ZhDatePicker(QWidget *parent);
};