#pragma once

#include <QtCore/Qt>

#include "../../../components/date_time/date_picker.h"
#include "../../../components/date_time/time_picker.h"
#include "../../../components/date_time/calendar_picker.h"
#include "gallery_interface.h"
#include "../common/translator.h"


class DateTimeInterface : public GalleryInterface{
    Q_OBJECT
public:
    DateTimeInterface(QWidget *parent);
};