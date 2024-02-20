#include "calendar_view.h"


void ScrollButton::_drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state)
{
    return;
}

void ScrollButton::paintEvent(QPaintEvent *event)
{
    TransparentToolButton::paintEvent(event);
    QPainter *painter = new QPainter(this);
    painter->setRenderHints(QPainter::Antialiasing);

    int w, h;
    if(!this->isPressed){
        w = 10;
        h = 10;
    }else{
        w = 9;
        h = 9;
    }

    int x = (this->width() - w) / 2;
    int y = (this->width() - h) / 2;

    if(!isDarkTheme()){
        std::map<QString, QString> attributes;
        attributes[QString("fill")] = QString("#5e5e5e");
        this->_icon->value<FluentIcon>().render(painter, QRect(x, y, w, h), Theme::AUTO, 0, &attributes);
    }else{
        std::map<QString, QString> attributes;
        attributes[QString("fill")] = QString("#9c9c9c");
        this->_icon->value<FluentIcon>().render(painter, QRect(x, y, w, h), Theme::AUTO, 0, &attributes);
    }

    painter->end();
}


ScrollItemDelegate::ScrollItemDelegate(QVariant min, QVariant max, QObject *parent) : QStyledItemDelegate(parent)
{
    this->setRange(min, max);
    this->font = Font().getFont(14, QFont::Normal);
    this->pressedIndex = QModelIndex();
    this->currentIndex = QModelIndex();
    this->selectedIndex = QModelIndex();
}

void ScrollItemDelegate::setRange(QVariant min, QVariant max)
{
    this->min = min;
    this->max = max;
}


void ScrollItemDelegate::setPressedIndex(QModelIndex index)
{
    this->pressedIndex = index;
}

void ScrollItemDelegate::setCurrentIndex(QModelIndex index)
{
    this->currentIndex = index;
}

void ScrollItemDelegate::setSelectedIndex(QModelIndex index)
{
    this->selectedIndex = index;
}

void ScrollItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    this->_drawBackground(painter, option, index);
    this->_drawText(painter, option, index);
}

void ScrollItemDelegate::_drawBackground(QPainter *painter, QStyleOptionViewItem option, QModelIndex index) const
{
    painter->save();

    if(index != this->selectedIndex){
        painter->setPen(Qt::NoPen);
    }else{
        painter->setPen(*(ThemeColor().themeColor()));
    }

    if(index == this->currentIndex){
        if(index == this->pressedIndex){
            painter->setBrush(*(ThemeColor().color(QString("LIGHT_2"))));
        }else if(option.state & QStyle::State_MouseOver){
            painter->setBrush(*(ThemeColor().color(QString("LIGHT_1"))));
        }else{
            painter->setBrush(*(ThemeColor().themeColor()));
        }
    }else{
        int c = isDarkTheme() ? 255 : 0;
        if(index == this->pressedIndex){
            painter->setBrush(QColor(c, c, c, 7));
        }else if(option.state & QStyle::State_MouseOver){
            painter->setBrush(QColor(c, c, c, 9));
        }else{
            painter->setBrush(Qt::transparent);
        }
    }

    int m = this->_itemMargin();
    painter->drawEllipse(option.rect.adjusted(m, m, -m, -m));
    painter->restore();
}


void ScrollItemDelegate::_drawText(QPainter *painter, QStyleOptionViewItem option, QModelIndex index) const
{
    painter->save();
    painter->setFont(this->font);

    if(index == this->currentIndex){
        int c = isDarkTheme() ? 0 : 255;
        painter->setPen(QColor(c, c, c));
    }else{
        painter->setPen(isDarkTheme() ? Qt::white : Qt::black);

        if(this->min.canConvert<QDate>() && this->max.canConvert<QDate>()){
            if(!  (((this->min.value<QDate>() <= index.data(Qt::UserRole).value<QDate>()  &&  index.data(Qt::UserRole).value<QDate>() <= this->max.value<QDate>()) || option.state & QStyle::State_MouseOver) || (index == this->pressedIndex)) ){
                painter->setOpacity(0.6);
            }
        }else if(this->min.canConvert<int>() && this->max.canConvert<int>()){
            if(!  (((this->min.value<int>() <= index.data(Qt::UserRole).value<int>()  &&  index.data(Qt::UserRole).value<int>() <= this->max.value<int>()) || option.state & QStyle::State_MouseOver) || (index == this->pressedIndex)) ){
                painter->setOpacity(0.6);
            }
        }

        
    }

    QString text = index.data(Qt::DisplayRole).value<QString>();
    painter->drawText(option.rect, Qt::AlignCenter, text);
    painter->restore();
}


int ScrollItemDelegate::_itemMargin() const
{
    return 0;
}


int YearScrollItemDelegate::_itemMargin() const
{
    return 8;
}



int DayScrollItemDelegate::_itemMargin() const
{
    return 3;
}


ScrollViewBase::ScrollViewBase(QWidget *parent) : QListWidget(parent)
{
    this->cols = 4;
    this->pageRows = 3;
    this->currentPage = 0;
    this->vScrollBar = new SmoothScrollBar(Qt::Vertical, this);


    this->currentDate = QDate::currentDate();
    this->date = QDate::currentDate();

    this->minYear = this->currentDate.year() - 100;
    this->maxYear = this->currentDate.year() + 100;

    this->setUniformItemSizes(true);

    //TODO:self._initItems()  加到自类中实现
    //this->__initWidget();
}


void ScrollViewBase::__initWidget()
{
    this->setSpacing(0);
    this->setMovement(QListWidget::Static);
    this->setGridSize(this->gridSize());
    this->setViewportMargins(0, 0, 0, 0);
    this->setItemDelegate(this->delegate);
    this->setViewMode(QListWidget::IconMode);
    this->setResizeMode(QListWidget::Adjust);
    
    connect(this->vScrollBar->ani, &QPropertyAnimation::finished, this, &ScrollViewBase::_onFirstScrollFinished);
    
    this->vScrollBar->setScrollAnimation(1, QEasingCurve::OutCubic);
    this->setDate(this->date);
    this->vScrollBar->setForceHidden(true);
    this->setVerticalScrollMode(this->ScrollPerPixel);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void ScrollViewBase::_onFirstScrollFinished()
{
    this->vScrollBar->setScrollAnimation(300, QEasingCurve::OutQuad);
    this->vScrollBar->ani->disconnect();
}


void ScrollViewBase::scrollUp()
{
    this->scrollToPage(this->currentPage - 1);
}

void ScrollViewBase::scrollDown()
{
    this->scrollToPage(this->currentPage + 1);
}

void ScrollViewBase::scrollToPage(int page)
{
    if(!(0 <= page && qCeil(this->model()->rowCount() / (this->pageRows * this->cols)))){
        return;
    }

    this->currentPage = page;

    int y = this->gridSize().height() * this->pageRows * page;
    this->vScrollBar->setValue(y, true);
    this->delegate->setRange(std::get<0>(this->currentPageRange()), std::get<1>(this->currentPageRange())); 
}


std::tuple<QVariant, QVariant> ScrollViewBase::currentPageRange()
{
    return std::tuple<QVariant, QVariant>(QVariant::fromValue<int>(0), QVariant::fromValue<int>(0));
}


void ScrollViewBase::setDate(QDate date)
{
    this->scrollToDate(date);
}

void ScrollViewBase::scrollToDate(QDate date)
{
    return;
}

void ScrollViewBase::_setPressedIndex(QModelIndex index)
{
    this->delegate->setSelectedIndex(index);
    this->viewport()->update();
}

void ScrollViewBase::_setSelectedIndex(QModelIndex index)
{
    this->delegate->setSelectedIndex(index);
    this->viewport()->update();
}

void ScrollViewBase::wheelEvent(QWheelEvent *e)
{
    if(this->vScrollBar->ani->state() == QPropertyAnimation::Running){
        return;
    }

    if(e->angleDelta().y() < 0){
        this->scrollDown();
    }else{
        this->scrollUp();
    }
}


void ScrollViewBase::mousePressEvent(QMouseEvent *event)
{
    QListWidget::mousePressEvent(event);
    if(event->button() == Qt::LeftButton && this->indexAt(event->pos()).row() >= 0){
        this->_setPressedIndex(this->currentIndex());
    }
}

void ScrollViewBase::mouseReleaseEvent(QMouseEvent *event)
{
    QListWidget::mouseReleaseEvent(event);
    this->_setPressedIndex(QModelIndex());
}

QSize ScrollViewBase::gridSize()
{
    return QSize(76, 76);
}

CalendarViewBase::CalendarViewBase(QWidget *parent) : QFrame(parent)
{
    
    this->titleButton = new QPushButton(this);
    
    
    //FluentIcon *care_up_solid_icon = new FluentIcon();
    QScopedPointer<FluentIcon> care_up_solid_icon(new FluentIcon());
    care_up_solid_icon->setIconName("CARE_UP_SOLID");
    this->upButton = new ScrollButton(care_up_solid_icon.data(), this);

    
    //FluentIcon *care_down_solid_icon = new FluentIcon();
    QScopedPointer<FluentIcon> care_down_solid_icon(new FluentIcon());
    care_down_solid_icon->setIconName("CARE_DOWN_SOLID");
    this->downButton = new ScrollButton(care_down_solid_icon.data(), this);
    
    this->scrollView = nullptr;

    this->hBoxLayout = new QHBoxLayout(); //TODO:特殊关注
    this->vBoxLayout = new QVBoxLayout(this);

    this->__initWidget();
    
}

CalendarViewBase::~CalendarViewBase()
{
    delete this->upButton;
    delete this->downButton;
    delete this->titleButton;
    delete this->scrollView;
    delete this->hBoxLayout;
    delete this->vBoxLayout;
}

void CalendarViewBase::__initWidget()
{
    
    this->setFixedSize(314, 355);
    
    this->upButton->setFixedSize(32, 34);
    this->downButton->setFixedSize(32, 34);
    this->titleButton->setFixedHeight(34);

    
    this->hBoxLayout->setContentsMargins(9, 8, 9, 8);
    this->hBoxLayout->setSpacing(7);
    this->hBoxLayout->addWidget(this->titleButton, 1, Qt::AlignVCenter);
    this->hBoxLayout->addWidget(this->upButton, 0, Qt::AlignVCenter);
    this->hBoxLayout->addWidget(this->downButton, 0, Qt::AlignVCenter);

    
    this->vBoxLayout->setContentsMargins(0, 0, 0, 0);
    this->vBoxLayout->setSpacing(0);
    this->vBoxLayout->addLayout(this->hBoxLayout);
    this->vBoxLayout->setAlignment(Qt::AlignTop);
    
    
    this->titleButton->setObjectName(QString("titleButton"));
    FluentStyleSheet fss = FluentStyleSheet();
    fss.apply(this, FluentStyleSheetMap.value("CALENDAR_PICKER"), Theme::AUTO);

    connect(this->titleButton, &QPushButton::clicked, this, &CalendarViewBase::titleClicked);
    connect(this->upButton, &ScrollButton::clicked, this, &CalendarViewBase::_onScrollUp);
    connect(this->downButton, &ScrollButton::clicked, this, &CalendarViewBase::_onScrollDown);
}

void CalendarViewBase::itemClickedEmit(QListWidgetItem *item)
{
    emit(this->itemClicked(QDate(item->data(Qt::UserRole).value<QDate>()))); //特殊关注
}

void CalendarViewBase::setScrollView(ScrollViewBase *view)
{
    this->scrollView = view;
    connect(this->scrollView, &ScrollViewBase::itemClicked, this, &CalendarViewBase::itemClickedEmit); //特殊关注
    this->vBoxLayout->addWidget(view);
    this->_updateTitle();
}

void CalendarViewBase::setDate(QDate date)
{
    this->scrollView->setDate(date);
    this->_updateTitle();
}


void CalendarViewBase::setTitle(QString title)
{
    this->titleButton->setText(title);
}

QDate CalendarViewBase::currentPageDate()
{
    throw std::runtime_error("NotImplementedError");
}


void CalendarViewBase::_onScrollUp()
{
    this->scrollView->scrollUp();
    this->_updateTitle();
}

void CalendarViewBase::_onScrollDown()
{
    this->scrollView->scrollDown();
    this->_updateTitle();
}

void CalendarViewBase::_updateTitle()
{
    return;
}


YearScrollView::YearScrollView(QWidget *parent) : ScrollViewBase(parent)
{
    this->delegate = new YearScrollItemDelegate(QVariant::fromValue<int>(0), QVariant::fromValue<int>(0), this);
    this->_initItems();
    ScrollViewBase::__initWidget();
}

void YearScrollView::_initItems()
{
    QStringList yearRange;
    for (int year = minYear; year <= maxYear + 1; year++) {
        yearRange.append(QString::number(year));
    }
    this->addItems(yearRange);

    for(int i = 0; i < yearRange.size(); i++){
        QListWidgetItem *item = this->item(i);
        item->setData(Qt::UserRole, QVariant::fromValue<QDate>(QDate(yearRange.at(i).toInt(), 1, 1)));
        item->setSizeHint(this->sizeHint());
        if(yearRange.at(i).toInt() == this->currentDate.year()){
            this->delegate->setCurrentIndex(this->indexFromItem(item));
        }
    }
}


void YearScrollView::scrollToDate(QDate date)
{
    int page = (date.year() - this->minYear) / 12;
    this->scrollToPage(page);
}

std::tuple<QVariant, QVariant> YearScrollView::currentPageRange()
{
    int pageSize = this->pageRows * this->cols;
    int left = this->currentPage * pageSize + this->minYear;

    QMap<int, int> years;
    for(int i = left; i < left + 16; i++){
        int y = i / 10 * 10;
        if(years.contains(y)){
            years.insert(y, years.value(y) + 1);
        }else{
            years.insert(y, 1);
        }
    }

    auto maxElement = std::max_element(years.begin(), years.end(),
        [](const auto& lhs, const auto& rhs) {
            return lhs < rhs;
    });

    int mostCommonYear;
    if (maxElement != years.end()) {
        mostCommonYear = maxElement.key();
    }

    return std::tuple<QVariant, QVariant>(QVariant::fromValue<QDate>(QDate(mostCommonYear, 1, 1)), QVariant::fromValue<QDate>(QDate(mostCommonYear + 10, 1, 1)));
}


YearCalendarView::YearCalendarView(QWidget *parent) : CalendarViewBase(parent)
{
    this->setScrollView(new YearScrollView(this));
    this->titleButton->setEnabled(false);
}

void YearCalendarView::_updateTitle()
{
    std::tuple<QVariant, QVariant> value = this->scrollView->currentPageRange();
    this->setTitle(QString::number(std::get<0>(value).value<QDate>().year()) + QString("-") + QString::number(std::get<1>(value).value<QDate>().year()));
}


MonthScrollView::MonthScrollView(QWidget *parent) : ScrollViewBase(parent)
{
    this->delegate = new YearScrollItemDelegate(QVariant::fromValue<int>(0), QVariant::fromValue<int>(0), parent);
    this->_initItems();
    ScrollViewBase::__initWidget();
}

void MonthScrollView::_initItems()
{
    this->months = QStringList();

    for (int i = 0; i < 201; ++i) {
        this->months.append(this->tr("Jan"));
        this->months.append(this->tr("Feb"));
        this->months.append(this->tr("Mar"));
        this->months.append(this->tr("Apr"));
        this->months.append(this->tr("May"));
        this->months.append(this->tr("Jun"));
        this->months.append(this->tr("Jul"));
        this->months.append(this->tr("Aug"));
        this->months.append(this->tr("Sep"));
        this->months.append(this->tr("Oct"));
        this->months.append(this->tr("Nov"));
        this->months.append(this->tr("Dec"));
    }

    this->addItems(this->months);

    for(int i = 0; i < 12 * 201; i++)
    {
        int year = i / 12 + this->minYear;
        int m = i % 12 + 1;
        QListWidgetItem *item = this->item(i);
        item->setData(Qt::UserRole, QVariant::fromValue<QDate>(QDate(year, m, 1)));
        item->setSizeHint(this->gridSize());

        if(year == this->currentDate.year() && m == this->currentDate.month()){
            this->delegate->setCurrentIndex(this->indexFromItem(item));
        }
    }
}


void MonthScrollView::scrollToDate(QDate date)
{
    int page = date.year() - this->minYear;
    this->scrollToPage(page);
}


std::tuple<QVariant, QVariant> MonthScrollView::currentPageRange()
{
    int year = this->minYear + this->currentPage;
    return std::tuple<QVariant, QVariant>(QVariant::fromValue<QDate>(QDate(year, 1, 1)), QVariant::fromValue<QDate>(QDate(year, 12, 31)));
}


MonthCalendarView::MonthCalendarView(QWidget *parent) : CalendarViewBase(parent)
{
    this->setScrollView(new MonthScrollView(this));
}

void MonthCalendarView::_updateTitle()
{
    std::tuple<QVariant, QVariant> date = this->scrollView->currentPageRange();
    this->setTitle(QString::number(std::get<0>(date).value<QDate>().year()));
}

QDate MonthCalendarView::currentPageDate()
{
    std::tuple<QVariant, QVariant> date = this->scrollView->currentPageRange();
    QListWidgetItem *item = this->scrollView->currentItem();
    int month = item != nullptr ? item->data(Qt::UserRole).value<QDate>().month() : 1;
    return QDate(std::get<0>(date).value<QDate>().year(), month, 1);
}


DayScrollView::DayScrollView(QWidget *parent) : ScrollViewBase(parent)
{
    
    this->delegate = new DayScrollItemDelegate(QVariant::fromValue<int>(0), QVariant::fromValue<int>(0), this);
    
    this->_initItems();
    


    this->cols = 7;
    this->pageRows = 4;

    ScrollViewBase::__initWidget();
    this->vBoxLayout = new QHBoxLayout(this);

    this->weekDays = QStringList();
    weekDays.append(this->tr("Mo"));
    weekDays.append(this->tr("Tu"));
    weekDays.append(this->tr("We"));
    weekDays.append(this->tr("Th"));
    weekDays.append(this->tr("Fr"));
    weekDays.append(this->tr("Sa"));
    weekDays.append(this->tr("Su"));

    this->weekDayGroup = new QWidget(this);
    this->weekDayLayout = new QHBoxLayout(this->weekDayGroup);
    this->weekDayGroup->setObjectName(QString("weekDayGroup"));
    for(int i = 0; i < this->weekDays.size(); i++){
        QLabel *label = new QLabel(this->weekDays.at(i), this);
        label->setObjectName(QString("weekDayLabel"));
        this->weekDayLayout->addWidget(label, 1, Qt::AlignHCenter);
    }

    this->setViewportMargins(0, 38, 0, 0);
    this->vBoxLayout->setAlignment(Qt::AlignTop);
    this->vBoxLayout->setContentsMargins(0, 0, 0, 0);
    this->weekDayLayout->setSpacing(0);
    this->weekDayLayout->setContentsMargins(3, 12, 3, 12);
    this->vBoxLayout->addWidget(this->weekDayGroup);
    
    
}


QSize DayScrollView::gridSize()
{
    return QSize(44, 44);
}

void DayScrollView::_initItems()
{

    QDate startDate = QDate(this->minYear, 1, 1);
    QDate endDate = QDate(this->maxYear, 12, 31);

    this->currentDate = startDate;

    
    int bias = this->currentDate.dayOfWeek() - 1;
    for(int i = 0; i < bias; i++){
        QListWidgetItem *item = new QListWidgetItem(this);
        item->setFlags(Qt::NoItemFlags);
        this->addItem(item);
    }


    
    QStringList items = QStringList();
    QList<QDate> dates = QList<QDate>();

    
    while(this->currentDate <= endDate){
        items.append(QString::number(this->currentDate.day()));
        dates.append(this->currentDate);
        this->currentDate = this->currentDate.addDays(1);
    }
    
    
    this->addItems(items);
    
    for(int i = bias; i < this->count(); i++){
        QListWidgetItem *item = this->item(i);
        item->setData(Qt::UserRole, QVariant::fromValue<QDate>(dates.at(i - bias)));
        item->setSizeHint(this->gridSize());
    }
    

    this->delegate->setCurrentIndex(this->model()->index(this->_dateToRow(this->currentDate), 0));
}


void DayScrollView::setDate(QDate date)
{
    
    this->scrollToDate(date);
    this->setCurrentIndex(this->model()->index(this->_dateToRow(date), 0));
    this->delegate->setSelectedIndex(this->currentIndex());
}


void DayScrollView::scrollToDate(QDate date)
{
    
    int page = (date.year() - this->minYear) * 12 + date.month() - 1;
    
    this->scrollToPage(page);
}

void DayScrollView::scrollToPage(int page)
{
    if(!(0 <= page && page <= 201 * 12 - 1)){
        return;
    }
    
    this->currentPage = page;
    
    int index = this->_dateToRow(this->_pageToDate());

    int y = index / this->cols * this->gridSize().height();
    
    this->vScrollBar->scrollTo(y, true);
    
    this->delegate->setRange(std::get<0>(this->currentPageRange()), std::get<1>(this->currentPageRange()));
}


std::tuple<QVariant, QVariant> DayScrollView::currentPageRange()
{
    QDate date = this->_pageToDate();
    return std::tuple<QVariant, QVariant>(QVariant::fromValue<QDate>(date), QVariant::fromValue<QDate>(date.addMonths(1).addDays(-1)));
}

QDate DayScrollView::_pageToDate()
{
    int year = this->currentPage / 12 + this->minYear;
    int month = this->currentPage % 12 + 1;
    return QDate(year, month, 1);
}

int DayScrollView::_dateToRow(QDate date)
{
    QDate startDate = QDate(this->minYear, 1, 1);
    qint64 days =  startDate.daysTo(date);
    return days + startDate.dayOfWeek() - 1;
}

void DayScrollView::mouseReleaseEvent(QMouseEvent *event)
{
    ScrollViewBase::mouseReleaseEvent(event);
    this->_setSelectedIndex(this->currentIndex());
}


DayCalendarView::DayCalendarView(QWidget *parent) : CalendarViewBase(parent)
{
    this->setScrollView(new DayScrollView(this));
}

void DayCalendarView::_updateTitle()
{
    QDate date = this->currentPageDate();
    QString name = QCalendar().monthName(this->locale(), date.month(), date.year());
    this->setTitle(QString(name) + QString::number(date.year()));
}

QDate DayCalendarView::currentPageDate()
{
    std::tuple<QVariant, QVariant> date = this->scrollView->currentPageRange();
    return std::get<0>(date).value<QDate>();
}

void DayCalendarView::scrollToDate(QDate date)
{
    this->scrollView->scrollToDate(date);
    this->_updateTitle();
}



CalendarView::CalendarView(QWidget *parent) : QWidget(parent)
{
    
    this->hBoxLayout = new QHBoxLayout(this); //水平布局管理器
    
    
    this->date = QDate(); 
    
    
    this->stackedWidget = new QStackedWidget(this);
    
    this->yearView = new YearCalendarView(this);
    
    this->monthView = new MonthCalendarView(this);
    
    this->dayView = new DayCalendarView(this);
    
    
    
    this->opacityAni = new QPropertyAnimation(this, QString("windowOpacity").toUtf8(), this);
    this->slideAni = new QPropertyAnimation(this, QString("geometry").toUtf8(), this);
    this->aniGroup = new QParallelAnimationGroup(this);

    this->__initWidget();
    
    
}

CalendarView::~CalendarView()
{
    delete this->shadowEffect;
    delete this->slideAni;
    delete this->opacityAni;
    delete this->aniGroup;
    delete this->dayView;
    delete this->monthView;
    delete this->yearView;
    delete this->stackedWidget;
    delete this->hBoxLayout;
}


void CalendarView::__initWidget()
{
    
    this->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setAttribute(Qt::WA_DeleteOnClose, true);

    this->stackedWidget->addWidget(this->dayView);
    this->stackedWidget->addWidget(this->monthView);
    this->stackedWidget->addWidget(this->yearView);

    this->hBoxLayout->setContentsMargins(12, 8, 12, 20);
    this->hBoxLayout->addWidget(this->stackedWidget);

    
    this->setShadowEffect(30, std::tuple<int, int>(0, 8), QColor(0, 0, 0, 30));

    this->dayView->setDate(QDate::currentDate());

    this->aniGroup->addAnimation(this->opacityAni);
    this->aniGroup->addAnimation(this->slideAni);

    connect(this->dayView, &DayCalendarView::titleClicked, this, &CalendarView::_onDayViewTitleClicked);
    connect(this->monthView, &MonthCalendarView::titleClicked, this, &CalendarView::_onMonthTitleClicked);

    connect(this->monthView, &MonthCalendarView::itemClicked, this, &CalendarView::_onMonthItemClicked);
    connect(this->yearView, &YearCalendarView::itemClicked, this, &CalendarView::_onYearItemClicked);
    connect(this->dayView, &DayCalendarView::itemClicked, this, &CalendarView::_onDayItemClicked);
    
}


void CalendarView::setShadowEffect(int blurRadius = 30, std::tuple<int, int> offset = std::tuple<int, int>(0, 8), QColor color = QColor(0, 0, 0, 30))
{
    this->shadowEffect = new QGraphicsDropShadowEffect(this->stackedWidget);
    this->shadowEffect->setBlurRadius(blurRadius);
    this->shadowEffect->setOffset(std::get<0>(offset), std::get<1>(offset));
    this->shadowEffect->setColor(color);
    this->stackedWidget->setGraphicsEffect(nullptr);
    this->stackedWidget->setGraphicsEffect(this->shadowEffect);
}

void CalendarView::_onDayViewTitleClicked()
{
    this->stackedWidget->setCurrentWidget(this->monthView);
    qDebug() << this->dayView->currentPageDate();
    this->monthView->setDate(this->dayView->currentPageDate());
}

void CalendarView::_onMonthTitleClicked()
{
    this->stackedWidget->setCurrentWidget(this->yearView);
    this->yearView->setDate(this->monthView->currentPageDate());
}

void CalendarView::_onMonthItemClicked(QDate date)
{
    this->stackedWidget->setCurrentWidget(this->dayView);
    this->dayView->scrollToDate(date);
}

void CalendarView::_onYearItemClicked(QDate date)
{
    this->stackedWidget->setCurrentWidget(this->monthView);
    this->monthView->setDate(date);
}

void CalendarView::_onDayItemClicked(QDate date)
{
    this->close();
    if(date != this->date){
        this->date = date;
        emit(this->dateChanged(date));
    }
}



void CalendarView::setDate(QDate date)
{
    this->dayView->setDate(date);
    this->date = date;
}

void CalendarView::exec(QPoint pos, bool ani = true)
{
    if(this->isVisible()){
        return;
    }

    QRect rect = QApplication::screenAt(QCursor::pos())->availableGeometry();
    int w = this->sizeHint().width() + 5;
    int h = this->sizeHint().height();

    pos.setX(qMax(rect.left(), qMin(pos.x(), rect.right() - w)));
    pos.setY(qMax(rect.top(), qMin(pos.y() - 4, rect.bottom() - h + 5)));
    this->move(pos);

    if(!ani){
        return this->show();
    }

    
    this->opacityAni->setStartValue(0);
    this->opacityAni->setEndValue(1);
    this->opacityAni->setDuration(150);
    this->opacityAni->setEasingCurve(QEasingCurve::OutQuad);

    this->slideAni->setStartValue(QRect(pos - QPoint(0, 8), this->sizeHint()));
    this->slideAni->setEndValue(QRect(pos, this->sizeHint()));
    this->slideAni->setDuration(150);
    this->slideAni->setEasingCurve(QEasingCurve::OutQuad);
    this->aniGroup->start();
    
    this->show();
}

/*
void CalendarView::closeEvent(QCloseEvent *event)
{
    this->close();
}
*/