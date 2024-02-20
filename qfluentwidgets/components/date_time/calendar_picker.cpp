#include "calendar_picker.h"

CalendarPicker::CalendarPicker(QWidget *parent) : QPushButton(parent)
{
    this->_date = QDate();
    this->_dateFormat = new QVariant(QVariant::fromValue<Qt::DateFormat>(Qt::SystemLocaleDate));

    this->setText(this->tr("Pick a date"));
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("CALENDAR_PICKER"), Theme::AUTO);

    connect(this, &QPushButton::clicked, this, &CalendarPicker::_showCalendarView);
}


CalendarPicker::~CalendarPicker()
{
    delete this->view;
    delete this->_dateFormat;
}


QDate CalendarPicker::getDate()
{
    return this->_date;
}

void CalendarPicker::setDate(QDate date)
{
    this->_onDateChanged(date);
}

QVariant *CalendarPicker::getDateFormat()
{
    return this->_dateFormat;
}

void CalendarPicker::setDateFormat(QVariant *format)
{
    this->_dateFormat = format;
    if(this->getDate().isValid()){
        if(this->_dateFormat->canConvert<Qt::DateFormat>()){
            this->setText(this->getDate().toString(this->_dateFormat->value<Qt::DateFormat>()));
        }else if(this->_dateFormat->canConvert<QString>()){
            this->setText(this->getDate().toString(this->_dateFormat->value<QString>()));
        }   
    }
}

void CalendarPicker::_showCalendarView()
{

    view = new CalendarView(this->window());
    

    
    connect(view, &CalendarView::dateChanged, this, &CalendarPicker::_onDateChanged);

    if(this->getDate().isValid()){ //如果自己的_date是有效的值，则把值设置到CalendarView
        view->setDate(this->getDate());
    }

    int x = int(this->width() / 2 - view->sizeHint().width() / 2);
    int y = this->height();
    view->exec(this->mapToGlobal(QPoint(x, y)), true);
    
}

void CalendarPicker::_onDateChanged(QDate date)
{
    this->_date = QDate(date);
    if(this->_dateFormat->canConvert<Qt::DateFormat>()){
        this->setText(date.toString(this->_dateFormat->value<Qt::DateFormat>()));
    }else if(this->_dateFormat->canConvert<QString>()){
        this->setText(date.toString(this->_dateFormat->value<QString>()));
    }

    this->setProperty("hasDate", true);
    this->setStyle(QApplication::style());
    this->update();

    emit(this->dateChanged(date));
}


void CalendarPicker::paintEvent(QPaintEvent *e)
{
    QPushButton::paintEvent(e);
    QPainter *painter = new QPainter(this);
    painter->setRenderHints(QPainter::Antialiasing);

    if(!this->property("hasDate").value<bool>()){
        painter->setOpacity(0.6);
    }

    int w = 12;
    QRect rect = QRect(this->width() - 23, this->height() / 2 - w / 2, w, w);
    FluentIcon *icon = new FluentIcon();
    icon->setIconName(QString("CALENDAR"));
    icon->render(painter, rect, Theme::AUTO, 0, nullptr);

    painter->end();
    delete icon;
    delete painter;
}