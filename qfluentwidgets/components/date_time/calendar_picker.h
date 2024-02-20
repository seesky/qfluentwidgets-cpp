#pragma once

#include <QtCore/Qt>
#include <QtCore/QRectF>
#include <QtCore/QDate>
#include <QtCore/QPoint>
#include <QtGui/QPainter>
#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QApplication>

#include "../../common/style_sheet.h"
#include "../../common/icon.h"
#include "calendar_view.h"

class CalendarPicker : public QPushButton{
    Q_OBJECT
    Q_PROPERTY(QDate date READ getDate WRITE setDate)
    Q_PROPERTY(QVariant * dateFormat READ getDateFormat WRITE setDateFormat)
public:
    CalendarPicker(QWidget *parent);
    ~CalendarPicker();
    QDate getDate();
    void setDate(QDate date);
    QVariant *getDateFormat();
    void setDateFormat(QVariant *format);
    void _showCalendarView();

    void paintEvent(QPaintEvent *e);

    QDate _date;
    QVariant *_dateFormat;
    CalendarView *view;
signals:
    void dateChanged(QDate);

public slots:
    void _onDateChanged(QDate);
};