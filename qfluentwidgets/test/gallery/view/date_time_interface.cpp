#include "date_time_interface.h"

DateTimeInterface::DateTimeInterface(QWidget *parent) : GalleryInterface(Translator(nullptr).dateTime, "fluentwidgets.components.time_picker", parent)
{
    this->setObjectName("dateTimeInterface");

    this->addExampleCard(
        this->tr("A simple CalendarPicker"),
        new CalendarPicker(this),
        "http://www.github.com", 0
    );

    CalendarPicker *calendarPicker = new CalendarPicker(this);
    calendarPicker->setDateFormat(new QVariant(Qt::TextDate));
    this->addExampleCard(
        this->tr("A CalendarPicker in another format"),
        calendarPicker,
        "http://www.github.com", 0
    );

    this->addExampleCard(
        this->tr("A simple DatePicker"),
        new DatePicker(this, DatePicker::MM_DD_YYYY, true),
        "http://www.github.com", 0
    );

    this->addExampleCard(
        this->tr("A DatePicker in another format"),
        new ZhDatePicker(this),
        "http://www.github.com", 0
    );

    this->addExampleCard(
        this->tr("A simple TimePicker"),
        new AMTimePicker(this, false),
        "http://www.github.com", 0
    );

    this->addExampleCard(
        this->tr("A TimePicker using a 24-hour clock"),
        new TimePicker(this, true),
        "http://www.github.com", 0
    );

    this->addExampleCard(
        this->tr("A TimePicker with seconds column"),
        new TimePicker(this, true),
        "http://www.github.com", 0
    );
}