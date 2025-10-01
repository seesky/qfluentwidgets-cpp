# Components API Reference / 组件 API 参考

> This document lists every public API exposed by headers inside `qfluentwidgets/components`. Each section mirrors the directory structure and enumerates class properties, functions, signals, and slots.

> 本文档罗列了 `qfluentwidgets/components` 目录下头文件对外提供的全部 API。文档按照目录结构组织，逐一列出类的属性、函数、信号与槽。

## Date & Time Components / 日期与时间组件

### `date_time/calendar_picker.h`

#### CalendarPicker

- **Declaration / 声明**: `class CalendarPicker : public QPushButton{`
- **Inherits / 继承**: `public QPushButton`

**Properties / 属性**
- `Q_PROPERTY(QDate date READ getDate WRITE setDate)`
- `Q_PROPERTY(QVariant * dateFormat READ getDateFormat WRITE setDateFormat)`

**Public Members / 公有成员**
- `CalendarPicker(QWidget *parent)`
- `~CalendarPicker()`
- `QDate getDate()`
- `void setDate(QDate date)`
- `QVariant *getDateFormat()`
- `void setDateFormat(QVariant *format)`
- `void _showCalendarView()`
- `void paintEvent(QPaintEvent *e)`
- `QDate _date`
- `QVariant *_dateFormat`
- `CalendarView *view`

**Signals / 信号**
- `void dateChanged(QDate)`

**Public Slots / 公共槽函数**
- `void _onDateChanged(QDate)`


### `date_time/calendar_view.h`

#### ScrollButton

- **Declaration / 声明**: `class ScrollButton : public TransparentToolButton{`
- **Inherits / 继承**: `public TransparentToolButton`

**Public Members / 公有成员**
- `ScrollButton(FluentIcon *icon, QWidget *parent) : TransparentToolButton(icon, parent){}`
- `void _drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state) override`
- `void paintEvent(QPaintEvent *event) override`

#### ScrollItemDelegate

- **Declaration / 声明**: `class ScrollItemDelegate : public QStyledItemDelegate{`
- **Inherits / 继承**: `public QStyledItemDelegate`

**Public Members / 公有成员**
- `ScrollItemDelegate(QVariant min, QVariant max, QObject *parent)`
- `void setRange(QVariant min, QVariant max)`
- `void setPressedIndex(QModelIndex index)`
- `void setCurrentIndex(QModelIndex index)`
- `void setSelectedIndex(QModelIndex index)`
- `void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const`
- `void _drawBackground(QPainter *painter, QStyleOptionViewItem option, QModelIndex index) const`
- `void _drawText(QPainter *painter, QStyleOptionViewItem option, QModelIndex index) const`
- `virtual int _itemMargin() const`
- `QFont font`
- `QModelIndex pressedIndex`
- `QModelIndex currentIndex`
- `QModelIndex selectedIndex`
- `QVariant min`
- `QVariant max`

#### YearScrollItemDelegate

- **Declaration / 声明**: `class YearScrollItemDelegate : public ScrollItemDelegate{`
- **Inherits / 继承**: `public ScrollItemDelegate`

**Public Members / 公有成员**
- `YearScrollItemDelegate(QVariant min, QVariant max, QObject *parent) : ScrollItemDelegate(min, max, parent){}`
- `int _itemMargin() const override`

#### DayScrollItemDelegate

- **Declaration / 声明**: `class DayScrollItemDelegate : public ScrollItemDelegate{`
- **Inherits / 继承**: `public ScrollItemDelegate`

**Public Members / 公有成员**
- `DayScrollItemDelegate(QVariant min, QVariant max, QObject *parent) : ScrollItemDelegate(min, max, parent){}`
- `int _itemMargin() const override`

#### ScrollViewBase

- **Declaration / 声明**: `class ScrollViewBase : public QListWidget{`
- **Inherits / 继承**: `public QListWidget`

**Public Slots / 公共槽函数**
- `void _onFirstScrollFinished()`

#### CalendarViewBase

- **Declaration / 声明**: `class CalendarViewBase : public QFrame{`
- **Inherits / 继承**: `public QFrame`

**Public Members / 公有成员**
- `CalendarViewBase(QWidget *parent)`
- `void __initWidget()`
- `void setScrollView(ScrollViewBase *view)`
- `void setDate(QDate date)`
- `void setTitle(QString title)`
- `virtual QDate currentPageDate()`
- `virtual void _updateTitle()`
- `~CalendarViewBase()`
- `QPushButton *titleButton`
- `ScrollButton *upButton`
- `ScrollButton *downButton`
- `ScrollViewBase *scrollView`
- `QHBoxLayout *hBoxLayout`
- `QVBoxLayout *vBoxLayout`

**Signals / 信号**
- `void titleClicked()`
- `void itemClicked(QDate)`

**Public Slots / 公共槽函数**
- `void _onScrollUp()`
- `void _onScrollDown()`
- `void itemClickedEmit(QListWidgetItem *)`

#### YearScrollView

- **Declaration / 声明**: `class YearScrollView : public ScrollViewBase{`
- **Inherits / 继承**: `public ScrollViewBase`

**Public Members / 公有成员**
- `YearScrollView(QWidget *parent)`
- `void _initItems()`
- `void scrollToDate(QDate date) override`
- `std::tuple<QVariant, QVariant> currentPageRange() override`

#### YearCalendarView

- **Declaration / 声明**: `class YearCalendarView : public CalendarViewBase{`
- **Inherits / 继承**: `public CalendarViewBase`

**Public Members / 公有成员**
- `YearCalendarView(QWidget *parent)`
- `void _updateTitle() override`

#### MonthScrollView

- **Declaration / 声明**: `class MonthScrollView : public ScrollViewBase{`
- **Inherits / 继承**: `public ScrollViewBase`

**Public Members / 公有成员**
- `MonthScrollView(QWidget *parent)`
- `void _initItems()`
- `void scrollToDate(QDate date) override`
- `std::tuple<QVariant, QVariant> currentPageRange() override`
- `QStringList months`

#### MonthCalendarView

- **Declaration / 声明**: `class MonthCalendarView : public CalendarViewBase{`
- **Inherits / 继承**: `public CalendarViewBase`

**Public Members / 公有成员**
- `MonthCalendarView(QWidget *parent)`
- `void _updateTitle() override`
- `QDate currentPageDate() override`

#### DayScrollView

- **Declaration / 声明**: `class DayScrollView : public ScrollViewBase{`
- **Inherits / 继承**: `public ScrollViewBase`

**Public Members / 公有成员**
- `DayScrollView(QWidget *parent)`
- `QSize gridSize() override`
- `void _initItems()`
- `void setDate(QDate date) override`
- `void scrollToDate(QDate date) override`
- `void scrollToPage(int page) override`
- `virtual std::tuple<QVariant, QVariant> currentPageRange()`
- `QDate _pageToDate()`
- `int _dateToRow(QDate date)`
- `void mouseReleaseEvent(QMouseEvent *event)`
- `int cols`
- `int pageRows`
- `QHBoxLayout *vBoxLayout`
- `QStringList weekDays`
- `QWidget *weekDayGroup`
- `QHBoxLayout *weekDayLayout`

#### DayCalendarView

- **Declaration / 声明**: `class DayCalendarView : public CalendarViewBase{`
- **Inherits / 继承**: `public CalendarViewBase`

**Public Members / 公有成员**
- `DayCalendarView(QWidget *parent)`
- `void _updateTitle() override`
- `QDate currentPageDate() override`
- `void scrollToDate(QDate date)`

#### CalendarView

- **Declaration / 声明**: `class CalendarView : public QWidget{`
- **Inherits / 继承**: `public QWidget`

**Public Members / 公有成员**
- `CalendarView(QWidget *parent)`
- `~CalendarView()`
- `void __initWidget()`
- `void setShadowEffect(int blurRadius, std::tuple<int, int> offset, QColor color)`
- `void setDate(QDate date)`
- `void exec(QPoint pos, bool ani)`
- `QHBoxLayout *hBoxLayout`
- `QDate date`
- `QStackedWidget *stackedWidget`
- `YearCalendarView *yearView`
- `MonthCalendarView *monthView`
- `DayCalendarView *dayView`
- `QPropertyAnimation *opacityAni`
- `QPropertyAnimation *slideAni`
- `QParallelAnimationGroup *aniGroup`
- `QGraphicsDropShadowEffect *shadowEffect`

**Signals / 信号**
- `void dateChanged(QDate)`

**Public Slots / 公共槽函数**
- `void _onDayViewTitleClicked()`
- `void _onMonthTitleClicked()`
- `void _onMonthItemClicked(QDate date)`
- `void _onYearItemClicked(QDate date)`
- `void _onDayItemClicked(QDate date)`


### `date_time/date_picker.h`

#### MonthFormatter

- **Declaration / 声明**: `class MonthFormatter : public PickerColumnFormatter{`
- **Inherits / 继承**: `public PickerColumnFormatter`

**Public Members / 公有成员**
- `MonthFormatter()`
- `QString encode(QVariant value) override`
- `QVariant decode(QString value) override`
- `QList<QString> *months`

#### DatePickerBase

- **Declaration / 声明**: `class DatePickerBase : public PickerBase{`
- **Inherits / 继承**: `public PickerBase`

**Public Members / 公有成员**
- `DatePickerBase(QWidget *parent)`
- `virtual QDate *getDate()`
- `virtual void setDate(QDate *date)`
- `void setYearFormatter(PickerColumnFormatter *formatter)`
- `void setMonthFormatter(PickerColumnFormatter *formatter)`
- `void setDayFormatter(PickerColumnFormatter *formatter)`
- `PickerColumnFormatter *yearFormatter()`
- `PickerColumnFormatter *dayFormatter()`
- `PickerColumnFormatter *monthFormatter()`
- `QDate *_date`
- `QCalendar *calendar`
- `PickerColumnFormatter *_yearFormatter`
- `PickerColumnFormatter *_monthFormatter`
- `PickerColumnFormatter *_dayFormatter`

**Signals / 信号**
- `void dateChanged(QDate)`

#### DatePicker

- **Declaration / 声明**: `class DatePicker : public DatePickerBase{`
- **Inherits / 继承**: `public DatePickerBase`

**Public Members / 公有成员**
- `DatePicker(QWidget *parent, int format, bool isMonthTight)`
- `void setDateFormat(int format)`
- `QList<QString> * panelInitialValue() override`
- `void setMonthTight(bool isTight)`
- `int _monthColumnWidth()`
- `void _onColumnValueChanged(PickerPanel *panel, int index, QString value)`
- `void _onConfirmed(QList<QString> *value) override`
- `QDate *getDate()`
- `void setDate(QDate *date)`
- `const static int MM_DD_YYYY = 0`
- `const static int YYYY_MM_DD = 1`
- `QString MONTH`
- `QString YEAR`
- `QString DAY`
- `bool isMonthTight`
- `int dateFormat`
- `int monthIndex`
- `int dayIndex`
- `int yearIndex`

#### ZhFormatter

- **Declaration / 声明**: `class ZhFormatter : public PickerColumnFormatter{`
- **Inherits / 继承**: `public PickerColumnFormatter`

**Public Members / 公有成员**
- `ZhFormatter(){this->suffix = ""`
- `} QString encode(QVariant value) override`
- `QVariant decode(QString value) override`
- `QString suffix`

#### ZhYearFormatter

- **Declaration / 声明**: `class ZhYearFormatter : public ZhFormatter{`
- **Inherits / 继承**: `public ZhFormatter`

**Public Members / 公有成员**
- `ZhYearFormatter(){this->suffix = "年"`

#### ZhMonthFormatter

- **Declaration / 声明**: `class ZhMonthFormatter : public ZhFormatter{`
- **Inherits / 继承**: `public ZhFormatter`

**Public Members / 公有成员**
- `ZhMonthFormatter(){this->suffix = "月"`

#### ZhDayFormatter

- **Declaration / 声明**: `class ZhDayFormatter : public ZhFormatter{`
- **Inherits / 继承**: `public ZhFormatter`

**Public Members / 公有成员**
- `ZhDayFormatter(){this->suffix = "日"`

#### ZhDatePicker

- **Declaration / 声明**: `class ZhDatePicker : public DatePicker{`
- **Inherits / 继承**: `public DatePicker`

**Public Members / 公有成员**
- `ZhDatePicker(QWidget *parent)`


### `date_time/picker_base.h`

#### SeparatorWidget

- **Declaration / 声明**: `class SeparatorWidget : public QWidget{`
- **Inherits / 继承**: `public QWidget`

**Public Members / 公有成员**
- `SeparatorWidget(Qt::Orientation orient, QWidget *parent)`

#### ItemMaskWidget

- **Declaration / 声明**: `class ItemMaskWidget : public QWidget{`
- **Inherits / 继承**: `public QWidget`

**Public Members / 公有成员**
- `ItemMaskWidget(QList<CycleListWidget *> *listWidgets, QWidget *parent)`
- `void paintEvent(QPaintEvent *event) override`
- `void _drawText(QListWidgetItem *item, QPainter *painter, int y)`
- `QList<CycleListWidget *> *listWidgets`

#### PickerColumnFormatter

- **Declaration / 声明**: `class PickerColumnFormatter : public QObject{`
- **Inherits / 继承**: `public QObject`

**Public Members / 公有成员**
- `PickerColumnFormatter() : QObject(){}`
- `virtual QString encode(QVariant value)`
- `virtual QVariant decode(QString value)`

#### DigitFormatter

- **Declaration / 声明**: `class DigitFormatter : public PickerColumnFormatter{`
- **Inherits / 继承**: `public PickerColumnFormatter`

**Public Members / 公有成员**
- `QVariant decode(QString value) override`

#### PickerColumnButton

- **Declaration / 声明**: `class PickerColumnButton : public QPushButton{`
- **Inherits / 继承**: `public QPushButton`

**Public Members / 公有成员**
- `PickerColumnButton(QString name, QList<QString> *items, int width, Qt::AlignmentFlag align, PickerColumnFormatter *formatter, QWidget *parent)`
- `Qt::AlignmentFlag align()`
- `void setAlignment(Qt::AlignmentFlag align)`
- `QString value()`
- `void setValue(QString v)`
- `QList<QVariant> *items()`
- `void setItems(QList<QString> *items)`
- `PickerColumnFormatter* formatter()`
- `void setFormatter(PickerColumnFormatter *formatter)`
- `QString name()`
- `void setName(QString name)`
- `QString _name`
- `QString _value`
- `Qt::AlignmentFlag _align`
- `bool hasBorder`
- `QList<QString> *_items`
- `PickerColumnFormatter *_formatter`

#### PickerBase

- **Declaration / 声明**: `class PickerBase : public QPushButton{`
- **Inherits / 继承**: `public QPushButton`

**Public Members / 公有成员**
- `PickerBase(QWidget *parent)`
- `void addColumn(QString name, QList<QString> *items, int width, Qt::AlignmentFlag align, PickerColumnFormatter *formatter)`
- `void setColumnAlignment(PickerBase *picker, int index, Qt::AlignmentFlag align)`
- `void setColumnWidth(PickerBase *picker, int index, int width)`
- `void setColumnTight(PickerBase *picker, int index)`
- `void setColumnVisible(PickerBase *picker, int index, bool isVisible)`
- `QList<QString> *value()`
- `QList<QString> *initialValue()`
- `void setColumnValue(PickerBase *picker, int index, QString value)`
- `void setColumnInitialValue(PickerBase *picker, int index, QString value)`
- `void setColumnFormatter(PickerBase *picker, int index, PickerColumnFormatter *formatter)`
- `void setColumnItems(PickerBase *picker, int index, QList<QString> *items)`
- `QString encodeValue(PickerBase *picker, int index, QString value)`
- `QVariant decodeValue(PickerBase *picker, int index, QString value)`
- `void setColumn(PickerBase *picker, int index, QString name, QList<QString> items, int width, Qt::AlignmentFlag align)`
- `void clearColumns()`
- `void enterEvent(QEvent *event) override`
- `void leaveEvent(QEvent *event) override`
- `void mousePressEvent(QMouseEvent *e) override`
- `void mouseReleaseEvent(QMouseEvent *e) override`
- `void _setButtonProperty(const char *name, bool value)`
- `virtual QList<QString> * panelInitialValue()`
- `virtual void _onConfirmed(QList<QString> *value)`
- `QList<PickerColumnButton *> *columns`
- `QHBoxLayout *hBoxLayout`

**Public Slots / 公共槽函数**
- `void _showPanel()`
- `void _onColumnValueChanged(PickerPanel *panel, int index, QString value)`

#### PickerToolButton

- **Declaration / 声明**: `class PickerToolButton : public TransparentToolButton{`
- **Inherits / 继承**: `public TransparentToolButton`

**Public Members / 公有成员**
- `PickerToolButton(FluentIcon *icon, QWidget *parent) : TransparentToolButton(icon, parent){}`
- `PickerToolButton(QIcon *icon, QWidget *parent) : TransparentToolButton(icon, parent){}`
- `PickerToolButton(QString icon, QWidget *parent) : TransparentToolButton(icon, parent){}`
- `void _drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state) override`

#### PickerPanel

- **Declaration / 声明**: `class PickerPanel : public QWidget{`
- **Inherits / 继承**: `public QWidget`

**Public Members / 公有成员**
- `PickerPanel(QWidget *parent)`
- `void __initWidget()`
- `void setShadowEffect(int blurRadius, std::tuple<int,int> offset, QColor color)`
- `void addColumn(QList<QVariant> *items, int width, Qt::AlignmentFlag align)`
- `void resizeEvent(QResizeEvent *event)`
- `QList<QString> *value()`
- `void setValue(QList<QString> *list)`
- `QString columnValue(int index)`
- `void setColumnValue(int index, QString value)`
- `CycleListWidget *column(int index)`
- `void exec(QPoint pos, bool ani)`
- `int itemHeight`
- `QList<CycleListWidget *> *listWidgets`
- `QFrame *view`
- `ItemMaskWidget *itemMaskWidget`
- `SeparatorWidget *hSeparatorWidget`
- `PickerToolButton *yesButton`
- `PickerToolButton *cancelButton`
- `QHBoxLayout *hBoxLayout`
- `QHBoxLayout *listLayout`
- `QHBoxLayout *buttonLayout`
- `QVBoxLayout *vBoxLayout`
- `QGraphicsDropShadowEffect *shadowEffect`
- `bool isExpanded`
- `QPropertyAnimation *ani`

**Signals / 信号**
- `void confirmed(QList<QString> *)`
- `void columnValueChanged(int, QString)`

**Public Slots / 公共槽函数**
- `void _onAniValueChanged(QVariant opacity)`
- `void _fadeOut()`


### `date_time/time_picker.h`

#### TimePickerBase

- **Declaration / 声明**: `class TimePickerBase : public PickerBase{`
- **Inherits / 继承**: `public PickerBase`

**Public Members / 公有成员**
- `TimePickerBase(QWidget *parent, bool showSeconds)`
- `virtual QTime *getTime()`
- `virtual void setTime(QTime *time){}`
- `bool isSecondVisible()`
- `virtual void setSecondVisible(bool isVisible){}`
- `QTime *_time`
- `bool _isSecondVisible`

**Signals / 信号**
- `void timeChanged(QTime)`

#### MiniuteFormatter

- **Declaration / 声明**: `class MiniuteFormatter : public DigitFormatter{`
- **Inherits / 继承**: `public DigitFormatter`

**Public Members / 公有成员**
- `QString encode(QVariant value) override`

#### AMHourFormatter

- **Declaration / 声明**: `class AMHourFormatter : public DigitFormatter{`
- **Inherits / 继承**: `public DigitFormatter`

**Public Members / 公有成员**
- `QString encode(QVariant value) override`

#### AMPMFormatter

- **Declaration / 声明**: `class AMPMFormatter : public PickerColumnFormatter{`
- **Inherits / 继承**: `public PickerColumnFormatter`

**Public Members / 公有成员**
- `AMPMFormatter()`
- `QString encode(QVariant value) override`
- `QString AM`
- `QString PM`

#### TimePicker

- **Declaration / 声明**: `class TimePicker : public TimePickerBase{`
- **Inherits / 继承**: `public TimePickerBase`

**Properties / 属性**
- `Q_PROPERTY(QTime* time READ getTime WRITE setTime)`
- `Q_PROPERTY(bool secondVisible READ isSecondVisible WRITE setSecondVisible)`

**Public Members / 公有成员**
- `TimePicker(QWidget *parent, bool showSeconds)`
- `void setTime(QTime *time) override`
- `void setSecondVisible(bool isVisible) override`
- `void _onConfirmed(QList<QString> *value)`
- `QList<QString> *panelInitialValue()`
- `QTime *getTime() override`
- `bool isSecondVisible()`

#### AMTimePicker

- **Declaration / 声明**: `class AMTimePicker : public TimePickerBase{`
- **Inherits / 继承**: `public TimePickerBase`

**Properties / 属性**
- `Q_PROPERTY(QTime* time READ getTime WRITE setTime)`
- `Q_PROPERTY(bool secondVisible READ isSecondVisible WRITE setSecondVisible)`

**Public Members / 公有成员**
- `AMTimePicker(QWidget *parent, bool showSeconds)`
- `void setSecondVisible(bool isVisible) override`
- `void setTime(QTime *time) override`
- `void _onConfirmed(QList<QString> *value)`
- `QList<QString> *panelInitialValue()`
- `QTime *getTime() override`
- `bool isSecondVisible()`
- `QString AM`
- `QString PM`



## Dialog Box Components / 对话框组件

### `dialog_box/color_dialog.h`

#### HuePanel

- **Declaration / 声明**: `class HuePanel : public QWidget{`
- **Inherits / 继承**: `public QWidget`

**Public Members / 公有成员**
- `HuePanel(QColor color, QWidget *parent)`
- `void mousePressEvent(QMouseEvent *event) override`
- `void mouseMoveEvent(QMouseEvent *event) override`
- `void setPickerPosition(QPoint pos)`
- `void setColor(QColor color)`
- `int hue()`
- `int saturation()`
- `void paintEvent(QPaintEvent *event) override`
- `QPixmap huePixmap`
- `QPoint pickerPos`
- `QColor color`

**Signals / 信号**
- `void colorChanged(QColor)`

#### BrightnessSlider

- **Declaration / 声明**: `class BrightnessSlider : public ClickableSlider{`
- **Inherits / 继承**: `public ClickableSlider`

**Public Members / 公有成员**
- `BrightnessSlider(QColor color, QWidget *parent)`
- `void setColor(QColor color)`
- `QColor color`

**Signals / 信号**
- `void colorChanged(QColor)`

**Public Slots / 公共槽函数**
- `void __onValueChanged(int value)`

#### ColorCard

- **Declaration / 声明**: `class ColorCard : public QWidget{`
- **Inherits / 继承**: `public QWidget`

**Public Members / 公有成员**
- `ColorCard(QColor color, QWidget *parent, bool enableAlpha)`
- `QPixmap _createTitledBackground()`
- `void setColor(QColor color)`
- `void paintEvent(QPaintEvent *event) override`
- `bool enableAlpha`
- `QPixmap titledPixmap`
- `QColor color`

#### ColorLineEdit

- **Declaration / 声明**: `class ColorLineEdit : public LineEdit{`
- **Inherits / 继承**: `public LineEdit`

**Public Members / 公有成员**
- `ColorLineEdit(int value, QWidget *parent)`
- `void _onTextEdited(QString text)`

**Signals / 信号**
- `void valueChanged(QString)`

#### HexColorLineEdit

- **Declaration / 声明**: `class HexColorLineEdit : public ColorLineEdit{`
- **Inherits / 继承**: `public ColorLineEdit`

**Public Members / 公有成员**
- `HexColorLineEdit(QColor color, QWidget *parent, bool enableAlpha)`
- `void setColor(QColor color)`
- `QColor::NameFormat colorFormat`
- `QLabel *prefixLabel`

#### OpacityLineEdit

- **Declaration / 声明**: `class OpacityLineEdit : public ColorLineEdit{`
- **Inherits / 继承**: `public ColorLineEdit`

**Public Members / 公有成员**
- `OpacityLineEdit(int value, QWidget *parent, bool enableAlpha)`
- `void showEvent(QShowEvent *event) override`
- `void _adjustSuffixPos()`
- `QLabel *suffixLabel`

#### ColorDialog

- **Declaration / 声明**: `class ColorDialog : public MaskDialogBase{`
- **Inherits / 继承**: `public MaskDialogBase`

**Public Members / 公有成员**
- `ColorDialog(QColor color, QString title, QWidget *parent, bool enableAlpha)`
- `void __initWidget()`
- `void __initLayout()`
- `void __setQss()`
- `void setColor(QColor color, bool movePicker)`
- `void updateStyle()`
- `void showEvent(QShowEvent *event) override`
- `bool enableAlpha`
- `QColor oldColor`
- `QColor color`
- `SingleDirectionScrollArea *scrollArea`
- `QWidget *scrollWidget`
- `QFrame *buttonGroup`
- `PrimaryPushButton *yesButton`
- `QPushButton *cancelButton`
- `QLabel *titleLabel`
- `HuePanel *huePanel`
- `ColorCard *newColorCard`
- `ColorCard *oldColorCard`
- `BrightnessSlider *brightSlider`
- `QLabel *editLabel`
- `QLabel *redLabel`
- `QLabel *blueLabel`
- `QLabel *greenLabel`
- `QLabel *opacityLabel`
- `HexColorLineEdit *hexLineEdit`
- `ColorLineEdit *redLineEdit`
- `ColorLineEdit *greenLineEdit`
- `ColorLineEdit *blueLineEdit`
- `OpacityLineEdit *opacityLineEdit`
- `QVBoxLayout *vBoxLayout`

**Signals / 信号**
- `void colorChanged(QColor)`

**Public Slots / 公共槽函数**
- `void __onHueChanged(QColor color)`
- `void __onBrightnessChanged(QColor color)`
- `void __onRedChanged(QString red)`
- `void __onBlueChanged(QString blue)`
- `void __onGreenChanged(QString green)`
- `void __onOpacityChanged(QString opacity)`
- `void __onHexColorChanged(QString color)`
- `void __onYesButtonClicked()`
- `void __connectSignalToSlot()`


### `dialog_box/dialog.h`

#### Dialog

- **Declaration / 声明**: `class Dialog : public FramelessDialog{`
- **Inherits / 继承**: `public FramelessDialog`

**Public Members / 公有成员**
- `Dialog(QString title, QString content, QWidget *parent)`
- `void _setUpUi(QString title, QString content, QWidget *parent)`
- `void __initWidget()`
- `void _adjustText()`
- `void __initLayout()`
- `void __setQss()`
- `void setContentCopyable(bool isCopyable)`
- `void setTitleBarVisible(bool isVisible)`
- `QString content`
- `QLabel *titleLabel`
- `QLabel *contentLabel`
- `QLabel *windowTitleLabel`
- `QFrame *buttonGroup`
- `PrimaryPushButton *yesButton`
- `QPushButton *cancelButton`
- `QVBoxLayout *vBoxLayout`
- `QVBoxLayout *textLayout`
- `QHBoxLayout *buttonLayout`

**Signals / 信号**
- `void yesSignal()`
- `void cancelSignal()`

**Public Slots / 公共槽函数**
- `void __onCancelButtonClicked()`
- `void __onYesButtonClicked()`

#### MessageBoxF

- **Declaration / 声明**: `class MessageBoxF : public MaskDialogBase{`
- **Inherits / 继承**: `public MaskDialogBase`

**Public Members / 公有成员**
- `MessageBoxF(QString title, QString content, QWidget *parent)`
- `void _setUpUi(QString title, QString content, QWidget *parent)`
- `void __initWidget()`
- `void _adjustText()`
- `void __initLayout()`
- `void __setQss()`
- `void setContentCopyable(bool isCopyable)`
- `bool eventFilter(QObject *obj, QEvent *e) override`
- `QString content`
- `QLabel *titleLabel`
- `QLabel *contentLabel`
- `QLabel *windowTitleLabel`
- `QFrame *buttonGroup`
- `PrimaryPushButton *yesButton`
- `QPushButton *cancelButton`
- `QVBoxLayout *vBoxLayout`
- `QVBoxLayout *textLayout`
- `QHBoxLayout *buttonLayout`

**Signals / 信号**
- `void yesSignal()`
- `void cancelSignal()`

**Public Slots / 公共槽函数**
- `void __onCancelButtonClicked()`
- `void __onYesButtonClicked()`


### `dialog_box/folder_list_dialog.h`

#### FolderListDialog

- **Declaration / 声明**: `class FolderListDialog : public MaskDialogBase{`
- **Inherits / 继承**: `public MaskDialogBase`

**Public Members / 公有成员**
- `FolderListDialog(QStringList folderPaths, QString title, QString content, QWidget *parent)`
- `void __initWidget()`
- `void __initLayout()`
- `void __showDeleteFolderCardDialog()`
- `void __deleteFolderCard(FolderCard *folderCard)`
- `void __setQss()`
- `void __adjustWidgetSize()`
- `QString title`
- `QString content`
- `QStringList __originalPaths`
- `QStringList folderPaths`
- `QVBoxLayout *vBoxLayout`
- `QLabel *titleLabel`
- `QLabel *contentLabel`
- `SingleDirectionScrollArea *scrollArea`
- `QWidget *scrollWidget`
- `QPushButton *completeButton`
- `AddFolderCard *addFolderCard`
- `QList<FolderCard *> folderCards`
- `QVBoxLayout *scrollLayout`

**Signals / 信号**
- `void folderChanged(QStringList)`

**Public Slots / 公共槽函数**
- `void __onButtonClicked()`
- `void __showFileDialog()`

#### ClickableWindow

- **Declaration / 声明**: `class ClickableWindow : public QWidget{`
- **Inherits / 继承**: `public QWidget`

**Public Members / 公有成员**
- `ClickableWindow(QWidget *parent)`
- `void enterEvent(QEvent *event) override`
- `void leaveEvent(QEvent *event) override`
- `void mouseReleaseEvent(QMouseEvent *e) override`
- `void mousePressEvent(QMouseEvent *e) override`
- `void paintEvent(QPaintEvent *event) override`
- `bool _isPressed`
- `bool _isEnter`

**Signals / 信号**
- `void clicked()`

#### FolderCard

- **Declaration / 声明**: `class FolderCard : public ClickableWindow{`
- **Inherits / 继承**: `public ClickableWindow`

**Public Members / 公有成员**
- `FolderCard(QString folderPath, QWidget *parent)`
- `void paintEvent(QPaintEvent *event) override`
- `void __drawText(QPainter& painter, int x1, int fontSize1, int x2, int fontSize2)`
- `QString folderName`
- `QPixmap __closeIcon`
- `QString folderPath`

#### AddFolderCard

- **Declaration / 声明**: `class AddFolderCard : public ClickableWindow{`
- **Inherits / 继承**: `public ClickableWindow`

**Public Members / 公有成员**
- `AddFolderCard(QWidget *parent)`
- `void paintEvent(QPaintEvent *event) override`
- `QPixmap __iconPix`


### `dialog_box/mask_dialog_base.h`

#### MaskDialogBase

- **Declaration / 声明**: `class MaskDialogBase : public QDialog{`
- **Inherits / 继承**: `public QDialog`

**Public Members / 公有成员**
- `MaskDialogBase(QWidget *parent)`
- `void setShadowEffect(int blurRadius, std::tuple<int,int> offset, QColor color)`
- `void setMaskColor(QColor color)`
- `void showEvent(QShowEvent *e) override`
- `void done(int code) override`
- `void resizeEvent(QResizeEvent *e) override`
- `bool eventFilter(QObject *obj, QEvent *e) override`
- `QHBoxLayout *_hBoxLayout`
- `QWidget *windowMask`
- `QFrame *widget`


### `dialog_box/message_box_base.h`

#### MessageBoxBase

- **Declaration / 声明**: `class MessageBoxBase : public MaskDialogBase{`
- **Inherits / 继承**: `public MaskDialogBase`

**Public Members / 公有成员**
- `MessageBoxBase(QWidget *parent)`
- `void __initWidget()`
- `void __initLayout()`
- `void __setQss()`
- `void hideYesButton()`
- `void hideCancelButton()`
- `QFrame *buttonGroup`
- `PrimaryPushButton *yesButton`
- `QPushButton *cancelButton`
- `QVBoxLayout *vBoxLayout`
- `QVBoxLayout *viewLayout`
- `QHBoxLayout *buttonLayout`

**Signals / 信号**
- `void accepted()`
- `void rejected()`

**Public Slots / 公共槽函数**
- `void __onCancelButtonClicked()`
- `void __onYesButtonClicked()`


### `dialog_box/message_dialog.h`

#### MessageDialog

- **Declaration / 声明**: `class MessageDialog : public MaskDialogBase{`
- **Inherits / 继承**: `public MaskDialogBase`

**Public Members / 公有成员**
- `MessageDialog(QString title, QString content, QWidget *parent)`
- `void __initWidget()`
- `void __initLayout()`
- `void __setQss()`
- `QString content`
- `QLabel *titleLabel`
- `QLabel *contentLabel`
- `QPushButton *yesButton`
- `QPushButton *cancelButton`

**Signals / 信号**
- `void yesSignal()`
- `void cancelSignal()`

**Public Slots / 公共槽函数**
- `void __onCancelButtonClicked()`
- `void __onYesButtonClicked()`



## Layout Components / 布局组件

### `layout/expand_layout.h`

#### ExpandLayout

- **Declaration / 声明**: `class ExpandLayout : public QLayout{`
- **Inherits / 继承**: `public QLayout`

**Public Members / 公有成员**
- `ExpandLayout(QWidget *parent)`
- `void addWidget(QWidget *widget)`
- `void addItem(QLayoutItem *item) override`
- `int count() const override`
- `QLayoutItem *itemAt(int index) const override`
- `QLayoutItem *takeAt(int index) override`
- `Qt::Orientations expandingDirections() const override`
- `bool hasHeightForWidth() const override`
- `int heightForWidth(int width) const override`
- `void setGeometry(const QRect& rect) override`
- `QSize sizeHint() const`
- `QSize minimumSize() const`
- `int __doLayout(QRect rect, bool move) const`
- `bool eventFilter(QObject *watched, QEvent *event) override`
- `QList<QLayoutItem*> __items`
- `QList<QWidget*> __widgets`


### `layout/flow_layout.h`

#### FlowLayout

- **Declaration / 声明**: `class FlowLayout : public QLayout{`
- **Inherits / 继承**: `public QLayout`

**Public Members / 公有成员**
- `FlowLayout(QWidget *parent, bool needAni, bool isTight)`
- `void addItem(QLayoutItem *item) override`
- `void addWidget(QWidget *w)`
- `void setAnimation(int duration, QEasingCurve ease)`
- `int count() const override`
- `QLayoutItem *itemAt(int index) const override`
- `QLayoutItem *takeAt(int index) override`
- `QLayoutItem * removeWidget(QWidget *widget)`
- `void removeAllWidgets()`
- `void takeAllWidgets()`
- `Qt::Orientation expandingDirections()`
- `bool hasHeightForWidth() const`
- `int heightForWidth(int width) const`
- `void setGeometry(const QRect&) override`
- `QSize sizeHint() const override`
- `QSize minimumSize() const`
- `void setVerticalSpacing(int spacing)`
- `int verticalSpacing() const`
- `void setHorizontalSpacing(int spacing)`
- `int horizontalSpacing() const`
- `int _doLayout(QRect rect, bool move) const`
- `QList<QLayoutItem*> _items`
- `QList<QPropertyAnimation*> _anis`
- `QParallelAnimationGroup *_aniGroup`
- `int _verticalSpacing`
- `int _horizontalSpacing`
- `int duration`
- `QEasingCurve ease`
- `bool needAni`
- `bool isTight`


### `layout/v_box_layout.h`

#### VBoxLayout

- **Declaration / 声明**: `class VBoxLayout : public QVBoxLayout{`
- **Inherits / 继承**: `public QVBoxLayout`

**Public Members / 公有成员**
- `VBoxLayout(QWidget *parent)`
- `void addWidgets(QList<QWidget*> widgets, int stretch, Qt::Alignment alignment)`
- `void addWidget(QWidget *widget, int stretch, Qt::Alignment alignment)`
- `void removeWidget(QWidget *widget)`
- `void deleteWidget(QWidget *widget)`
- `void removeAllWidget()`
- `QList<QWidget*> widgets`



## Material Components / 亚克力材质组件

### `material/acrylic_flyout.h`

#### AcrylicFlyoutViewBase

- **Declaration / 声明**: `class AcrylicFlyoutViewBase : public FlyoutViewBase{`
- **Inherits / 继承**: `public FlyoutViewBase`

**Public Members / 公有成员**
- `AcrylicFlyoutViewBase(QWidget* parent)`
- `QPainterPath acrylicClipPath()`
- `void paintEvent(QPaintEvent *event) override`
- `void _drawAcrylic(QPainter *painter)`
- `void _updateAcrylicColor()`
- `AcrylicBrush *acrylicBrush`

#### AcrylicFlyoutView

- **Declaration / 声明**: `class AcrylicFlyoutView : public FlyoutView{`
- **Inherits / 继承**: `public FlyoutView`

**Public Members / 公有成员**
- `AcrylicFlyoutView(QString title, QString content, QVariant *icon, QVariant *image, bool isClosable, QWidget *parent)`
- `QPainterPath acrylicClipPath()`
- `void paintEvent(QPaintEvent *event) override`
- `void _drawAcrylic(QPainter *painter)`
- `void _updateAcrylicColor()`
- `AcrylicBrush *acrylicBrush`

#### AcrylicFlyout

- **Declaration / 声明**: `class AcrylicFlyout : public Flyout{`
- **Inherits / 继承**: `public Flyout`

**Public Members / 公有成员**
- `AcrylicFlyout(FlyoutViewBase *view, QWidget *parent, bool isDeleteOnClose)`
- `static AcrylicFlyout* create(QString title, QString content, QVariant *icon, QVariant *image, bool isClosable, QVariant target, QWidget *parent, FlyoutAnimationType aniType, bool isDeleteOnClose)`
- `static AcrylicFlyout* make(FlyoutViewBase *view, QVariant target, QWidget *parent, FlyoutAnimationType aniType, bool isDeleteOnClose)`
- `void exec(QPoint pos, FlyoutAnimationType aniType) override`


### `material/acrylic_line_edit.h`

#### AcrylicLineEdit

- **Declaration / 声明**: `class AcrylicLineEdit : public LineEdit{`
- **Inherits / 继承**: `public LineEdit`

**Public Members / 公有成员**
- `AcrylicLineEdit(QWidget *parent)`
- `void setCompleter(QCompleter *completer) override`
- `void contextMenuEvent(QContextMenuEvent *e) override`

#### AcrylicSearchLineEdit

- **Declaration / 声明**: `class AcrylicSearchLineEdit : public SearchLineEdit{`
- **Inherits / 继承**: `public SearchLineEdit`

**Public Members / 公有成员**
- `AcrylicSearchLineEdit(QWidget *parent)`
- `void setCompleter(QCompleter *completer) override`
- `void contextMenuEvent(QContextMenuEvent *e) override`


### `material/acrylic_menu.h`

#### AcrylicMenuActionListWidget

- **Declaration / 声明**: `class AcrylicMenuActionListWidget : public MenuActionListWidget{`
- **Inherits / 继承**: `public MenuActionListWidget`

**Public Members / 公有成员**
- `AcrylicMenuActionListWidget(QWidget *parent)`
- `void _updateAcrylicColor()`
- `int _topMargin()`
- `int _bottomMargin()`
- `void setItemHeight(int height)`
- `void addItem(QListWidgetItem *item)`
- `QListWidgetItem *createPlaceholderItem(int height)`
- `virtual QPainterPath clipPath()`
- `void paintEvent(QPaintEvent *event) override`
- `AcrylicBrush *acrylicBrush`

#### AcrylicMenu

- **Declaration / 声明**: `class AcrylicMenu : public RoundMenu{`
- **Inherits / 继承**: `public RoundMenu`

**Public Members / 公有成员**
- `AcrylicMenu(QString title, QWidget *parent)`
- `void setUpMenu(AcrylicMenuActionListWidget *view)`
- `void exec(QPoint *pos, bool ani, MenuAnimationType aniType) override`

#### AcrylicCompleterMenuActionListWidget

- **Declaration / 声明**: `class AcrylicCompleterMenuActionListWidget : public AcrylicMenuActionListWidget{`
- **Inherits / 继承**: `public AcrylicMenuActionListWidget`

**Public Members / 公有成员**
- `AcrylicCompleterMenuActionListWidget(QWidget *parent) : AcrylicMenuActionListWidget(parent){}`
- `QPainterPath clipPath() override`

#### AcrylicCompleterMenu

- **Declaration / 声明**: `class AcrylicCompleterMenu : public CompleterMenu{`
- **Inherits / 继承**: `public CompleterMenu`

**Public Members / 公有成员**
- `AcrylicCompleterMenu(LineEdit *lineEdit)`
- `void setItems(QStringList *items)`
- `void setUpMenu(AcrylicCompleterMenuActionListWidget *view)`
- `void exec(QPoint *pos, bool ani, MenuAnimationType aniType) override`

#### AcrylicLineEditMenu

- **Declaration / 声明**: `class AcrylicLineEditMenu : public LineEditMenu{`
- **Inherits / 继承**: `public LineEditMenu`

**Public Members / 公有成员**
- `AcrylicLineEditMenu(QLineEdit *parent)`
- `void setUpMenu(AcrylicMenuActionListWidget *view)`
- `void exec(QPoint *pos, bool ani, MenuAnimationType aniType) override`

#### AcrylicCheckableMenu

- **Declaration / 声明**: `class AcrylicCheckableMenu : public CheckableMenu{`
- **Inherits / 继承**: `public CheckableMenu`

**Public Members / 公有成员**
- `AcrylicCheckableMenu(QString title, QWidget *parent, MenuIndicatorType indicatorType)`
- `void setUpMenu(AcrylicMenuActionListWidget *view)`
- `void exec(QPoint *pos, bool ani, MenuAnimationType aniType) override`

#### AcrylicSystemTrayMenu

- **Declaration / 声明**: `class AcrylicSystemTrayMenu : public AcrylicMenu{`
- **Inherits / 继承**: `public AcrylicMenu`

**Public Members / 公有成员**
- `void showEvent(QShowEvent *event)`

#### AcrylicCheckableSystemTrayMenu

- **Declaration / 声明**: `class AcrylicCheckableSystemTrayMenu : public AcrylicCheckableMenu{`
- **Inherits / 继承**: `public AcrylicCheckableMenu`

**Public Members / 公有成员**
- `void showEvent(QShowEvent *event)`



## Navigation Components / 导航组件

### `navigation/breadcrumb.h`

#### BreadcrumbWidget

- **Declaration / 声明**: `class BreadcrumbWidget : public QWidget{`
- **Inherits / 继承**: `public QWidget`

**Public Members / 公有成员**
- `BreadcrumbWidget(QWidget *parent)`
- `void mousePressEvent(QMouseEvent *event) override`
- `void mouseReleaseEvent(QMouseEvent *event) override`
- `void enterEvent(QEvent *event) override`
- `void leaveEvent(QEvent *event) override`
- `bool isHover`
- `bool isPressed`

**Signals / 信号**
- `void clicked()`

#### ElideButton

- **Declaration / 声明**: `class ElideButton : public BreadcrumbWidget{`
- **Inherits / 继承**: `public BreadcrumbWidget`

**Public Members / 公有成员**
- `ElideButton(QWidget *parent)`
- `void paintEvent(QPaintEvent *event) override`
- `void clearState()`

#### BreadcrumbItem

- **Declaration / 声明**: `class BreadcrumbItem : public BreadcrumbWidget{`
- **Inherits / 继承**: `public BreadcrumbWidget`

**Public Members / 公有成员**
- `BreadcrumbItem(QString routeKey, QString text, int index, QWidget *parent)`
- `void setText(QString text)`
- `bool isRoot()`
- `void setSelected(bool isSelected)`
- `void setFont(QFont font)`
- `void setSpacing(int spacing)`
- `void paintEvent(QPaintEvent *event) override`
- `QString text`
- `QString routeKey`
- `bool isSelected`
- `int index`
- `int spacing`

#### BreadcrumbBar

- **Declaration / 声明**: `class BreadcrumbBar : public QWidget{`
- **Inherits / 继承**: `public QWidget`

**Properties / 属性**
- `Q_PROPERTY(int spacing READ getSpacing WRITE setSpacing)`

**Public Members / 公有成员**
- `BreadcrumbBar(QWidget *parent)`
- `void addItem(QString routeKey, QString text)`
- `void setCurrentIndex(int index)`
- `void setCurrentItem(QString routeKey)`
- `BreadcrumbItem *item(QString routeKey)`
- `int currentIndex()`
- `BreadcrumbItem *currentItem()`
- `void resizeEvent(QResizeEvent *event) override`
- `void clear()`
- `void popItem()`
- `void updateGeometry()`
- `bool isElideVisible()`
- `void setFont(QFont font)`
- `int getSpacing()`
- `void setSpacing(int spacing)`
- `QMap<QString, BreadcrumbItem*> itemMap`
- `QList<BreadcrumbItem*> items`
- `QList<BreadcrumbItem*> hiddenItems`
- `int _spacing`
- `int _currentIndex`
- `ElideButton *elideButton`

**Signals / 信号**
- `void currentItemChanged(QString)`
- `void currentIndexChanged(int)`

**Public Slots / 公共槽函数**
- `void _showHiddenItemsMenu()`


### `navigation/navigation_bar.h`

#### IconSlideAnimation

- **Declaration / 声明**: `class IconSlideAnimation : public QPropertyAnimation{`
- **Inherits / 继承**: `public QPropertyAnimation`

**Properties / 属性**
- `Q_PROPERTY(float offset READ getOffset WRITE setOffset)`

**Public Members / 公有成员**
- `IconSlideAnimation(QWidget *parent)`
- `float getOffset()`
- `void setOffset(float value)`
- `void slideDown()`
- `void slideUp()`
- `float _offset`
- `int maxOffset`

#### NavigationBarPushButton

- **Declaration / 声明**: `class NavigationBarPushButton : public NavigationPushButton{`
- **Inherits / 继承**: `public NavigationPushButton`

**Public Members / 公有成员**
- `NavigationBarPushButton(QVariant *icon, QString text, bool isSelectable, QVariant *selectedIcon, QWidget *parent)`
- `QIcon selectedIcon()`
- `void setSelectedIcon(QVariant *icon)`
- `void setSelectedTextVisible(bool isVisible)`
- `void paintEvent(QPaintEvent *event) override`
- `void setSelected(bool isSelected)`
- `IconSlideAnimation *iconAni`
- `QVariant *_selectedIcon`
- `bool _isSelectedTextVisible`

#### NavigationBar

- **Declaration / 声明**: `class NavigationBar : public QWidget{`
- **Inherits / 继承**: `public QWidget`

**Public Members / 公有成员**
- `NavigationBar(QWidget *parent)`
- `void __initWidget()`
- `void __initLayout()`
- `NavigationWidget *widget(QString routeKey)`
- `NavigationBarPushButton *addItem(QString routeKey, QVariant *icon, QString text, std::function<void()> onClick, bool selectable, QVariant *selectedIcon, NavigationItemPosition position)`
- `void addWidget(QString routeKey, NavigationWidget *widget, std::function<void()> onClick, NavigationItemPosition position)`
- `NavigationBarPushButton *insertItem(int index, QString routeKey, QVariant *icon, QString text, std::function<void()> onClick, bool selectable, QVariant *selectedIcon, NavigationItemPosition position)`
- `void insertWidget(int index, QString routeKey, NavigationWidget *widget, std::function<void()> onClick, NavigationItemPosition position)`
- `void _registerWidget(QString routeKey, NavigationWidget *widget, std::function<void()> onClick)`
- `void _insertWidgetToLayout(int index, NavigationWidget *widget, NavigationItemPosition position)`
- `void removeWidget(QString routeKey)`
- `void setCurrentItem(QString routeKey)`
- `void setFont(QFont font)`
- `void setSelectedTextVisible(bool isVisible)`
- `QList<NavigationWidget*> buttons()`
- `SingleDirectionScrollArea *scrollArea`
- `QWidget *scrollWidget`
- `QVBoxLayout *vBoxLayout`
- `QVBoxLayout *topLayout`
- `QVBoxLayout *bottomLayout`
- `QVBoxLayout *scrollLayout`
- `QMap<QString, NavigationWidget*> items`
- `Router *history`

**Public Slots / 公共槽函数**
- `void _onWidgetClicked()`


### `navigation/navigation_interface.h`

#### NavigationInterface

- **Declaration / 声明**: `class NavigationInterface : public QWidget{`
- **Inherits / 继承**: `public QWidget`

**Public Members / 公有成员**
- `NavigationInterface(QWidget *parent, bool showMenuButton, bool showReturnButton, bool collapsible)`
- `NavigationTreeWidget *addItem(QString routeKey, QVariant *icon, QString text, std::function<void()> onClick, bool selectable, NavigationItemPosition position, QString tooltip, QString parentRouteKey)`
- `void addWidget(QString routeKey, NavigationWidget *widget, std::function<void()> onClick, NavigationItemPosition position, QString tooltip, QString parentRouteKey)`
- `NavigationTreeWidget *insertItem(int index, QString routeKey, QVariant *icon, QString text, std::function<void()> onClick, bool selectable, NavigationItemPosition position, QString tooltip, QString parentRouteKey)`
- `void insertWidget(int index, QString routeKey, NavigationWidget *widget, std::function<void()> onClick, NavigationItemPosition position, QString tooltip, QString parentRouteKey)`
- `void addSeparator(NavigationItemPosition position)`
- `void insertSeparator(int index, NavigationItemPosition position)`
- `void removeWidget(QString routeKey)`
- `void setCurrentItem(QString name)`
- `void setExpandWidth(int width)`
- `void setMenuButtonVisible(bool isVisible)`
- `void setReturnButtonVisible(bool isVisible)`
- `void setCollapsible(bool collapsible)`
- `bool isAcrylicEnabled()`
- `void setAcrylicEnabled(bool isEnabled)`
- `NavigationWidget *widget(QString routeKey)`
- `bool eventFilter(QObject *obj, QEvent *e) override`
- `void resizeEvent(QResizeEvent *event) override`
- `NavigationPanel *panel`

**Signals / 信号**
- `void displayModeChanged(NavigationDisplayMode)`


### `navigation/navigation_panel.h`

#### NavigationToolTipFilter

- **Declaration / 声明**: `class NavigationToolTipFilter : public ToolTipFilter{`
- **Inherits / 继承**: `public ToolTipFilter`

**Public Members / 公有成员**
- `NavigationToolTipFilter(QWidget *parent, int showDelay, ToolTipPosition position)`
- `bool _canShowToolTip() override`

#### NavigationItem

- **Declaration / 声明**: `class NavigationItem{`

**Public Members / 公有成员**
- `NavigationItem(QString routeKey, QString parentRouteKey, NavigationWidget *widget)`
- `QString routeKey`
- `QString parentRouteKey`
- `NavigationWidget *widget`

#### NavigationPanel

- **Declaration / 声明**: `class NavigationPanel : public QFrame{`
- **Inherits / 继承**: `public QFrame`

**Public Members / 公有成员**
- `NavigationPanel(QWidget *parent, bool isMinimalEnabled)`
- `void __initWidget()`
- `void __initLayout()`
- `void _updateAcrylicColor()`
- `NavigationWidget *widget(QString routeKey)`
- `NavigationTreeWidget *addItem(QString routeKey, QVariant *icon, QString text, std::function<void()> onClick, bool selectable, NavigationItemPosition position, QString tooltip, QString parentRouteKey)`
- `void addWidget(QString routeKey, NavigationWidget *widget, std::function<void()> onClick, NavigationItemPosition position, QString tooltip, QString parentRouteKey)`
- `NavigationTreeWidget *insertItem(int index, QString routeKey, QVariant *icon, QString text, std::function<void()> onClick, bool selectable, NavigationItemPosition position, QString tooltip, QString parentRouteKey)`
- `void insertWidget(int index, QString routeKey, NavigationWidget *widget, std::function<void()> onClick, NavigationItemPosition position, QString tooltip, QString parentRouteKey)`
- `void addSeparator(NavigationItemPosition position)`
- `void insertSeparator(int index, NavigationItemPosition position)`
- `void _registerWidget(QString routeKey, QString parentRouteKey, NavigationWidget *widget, std::function<void()>onClick, QString tooltip)`
- `void _insertWidgetToLayout(int index, NavigationWidget *widget, NavigationItemPosition position)`
- `void removeWidget(QString routeKey)`
- `void setMenuButtonVisible(bool isVisible)`
- `void setReturnButtonVisible(bool isVisible)`
- `void setCollapsible(bool on)`
- `void setExpandWidth(int width)`
- `void setAcrylicEnabled(bool isEnabled)`
- `bool isAcrylicEnabled()`
- `void expand(bool useAni)`
- `void collapse()`
- `void setCurrentItem(QString routeKey)`
- `void _showFlyoutNavigationMenu(NavigationTreeWidget *widget)`
- `void _adjustFlyoutMenuSize(Flyout *flyout, NavigationTreeWidget *widget, NavigationFlyoutMenu *menu)`
- `bool isCollapsed()`
- `void resizeEvent(QResizeEvent *event) override`
- `bool eventFilter(QObject *obj, QEvent *e) override`
- `void _setWidgetCompacted(bool isCompacted)`
- `int layoutMinHeight()`
- `bool _canDrawAcrylic()`
- `void paintEvent(QPaintEvent *event) override`
- `QWidget *_parent`
- `bool _isMenuButtonVisible`
- `bool _isReturnButtonVisible`
- `bool _isCollapsible`
- `bool _isAcrylicEnabled`
- `AcrylicBrush * acrylicBrush`
- `SingleDirectionScrollArea *scrollArea`
- `QWidget *scrollWidget`
- `NavigationToolButton *menuButton`
- `NavigationToolButton *returnButton`
- `NavigationItemLayout *vBoxLayout`
- `NavigationItemLayout *topLayout`
- `NavigationItemLayout *bottomLayout`
- `NavigationItemLayout *scrollLayout`
- `QMap<QString, NavigationItem*> items`
- `Router *history`
- `QPropertyAnimation *expandAni`
- `int expandWidth`
- `bool isMinimalEnabled`
- `NavigationDisplayMode displayMode`

**Signals / 信号**
- `void displayModeChanged(NavigationDisplayMode)`

**Public Slots / 公共槽函数**
- `void _onWidgetClicked()`
- `void _onExpandAniFinished()`
- `void toggle()`

#### NavigationItemLayout

- **Declaration / 声明**: `class NavigationItemLayout : public QVBoxLayout{`
- **Inherits / 继承**: `public QVBoxLayout`

**Public Members / 公有成员**
- `NavigationItemLayout(QWidget *parent) : QVBoxLayout(parent){}`
- `void setGeometry(const QRect& rect) override`


### `navigation/navigation_widget.h`

#### NavigationWidget

- **Declaration / 声明**: `class NavigationWidget : public QWidget{`
- **Inherits / 继承**: `public QWidget`

**Public Members / 公有成员**
- `NavigationWidget(bool isSelectable, QWidget *parent)`
- `void enterEvent(QEvent *event) override`
- `void leaveEvent(QEvent *event) override`
- `void mousePressEvent(QMouseEvent *event) override`
- `void mouseReleaseEvent(QMouseEvent *event) override`
- `void click()`
- `virtual void setCompacted(bool isCompacted)`
- `bool isCompacted`
- `bool isSelected`
- `bool isPressed`
- `bool isEnter`
- `bool isSelectable`
- `QWidget *treeParent`
- `int nodeDepth`

**Signals / 信号**
- `void clicked(bool)`
- `void selectedChanged(bool)`

**Public Slots / 公共槽函数**
- `virtual void setSelected(bool isSelected)`

#### NavigationPushButton

- **Declaration / 声明**: `class NavigationPushButton : public NavigationWidget{`
- **Inherits / 继承**: `public NavigationWidget`

**Public Members / 公有成员**
- `NavigationPushButton(QVariant *icon, QString text, bool isSelectable, QWidget *parent)`
- `QString text()`
- `virtual void setText(QString text)`
- `QIcon icon()`
- `void setIcon(QVariant *icon)`
- `virtual QMargins _margins()`
- `virtual bool _canDrawIndicator()`
- `void paintEvent(QPaintEvent *event) override`
- `QVariant *_icon`
- `QString _text`

#### NavigationToolButton

- **Declaration / 声明**: `class NavigationToolButton : public NavigationPushButton{`
- **Inherits / 继承**: `public NavigationPushButton`

**Public Members / 公有成员**
- `NavigationToolButton(QVariant *icon, QWidget *parent)`
- `void setCompacted(bool isCompacted)`

#### NavigationSeparator

- **Declaration / 声明**: `class NavigationSeparator : public NavigationWidget{`
- **Inherits / 继承**: `public NavigationWidget`

**Public Members / 公有成员**
- `NavigationSeparator(QWidget *parent)`
- `void setCompacted(bool isCompacted)`
- `void paintEvent(QPaintEvent *event) override`

#### NavigationTreeItem

- **Declaration / 声明**: `class NavigationTreeItem : public NavigationPushButton{`
- **Inherits / 继承**: `public NavigationPushButton`

**Properties / 属性**
- `Q_PROPERTY(float arrowAngle READ getArrowAngle WRITE setArrowAngle)`

**Public Members / 公有成员**
- `NavigationTreeItem(QVariant *icon, QString text, bool isSelectable, QWidget *parent)`
- `void setExpanded(bool isExpanded)`
- `void mouseReleaseEvent(QMouseEvent *event) override`
- `bool _canDrawIndicator() override`
- `QMargins _margins() override`
- `void paintEvent(QPaintEvent *event) override`
- `float getArrowAngle()`
- `void setArrowAngle(float angle)`
- `float _arrowAngle`
- `QPropertyAnimation *rotateAni`

**Signals / 信号**
- `void itemClicked(bool, bool)`

#### NavigationTreeWidgetBase

- **Declaration / 声明**: `class NavigationTreeWidgetBase : public NavigationWidget{`
- **Inherits / 继承**: `public NavigationWidget`

**Public Members / 公有成员**
- `NavigationTreeWidgetBase(bool isSelectable, QWidget *parent): NavigationWidget(isSelectable, parent){}`
- `void addChild(NavigationWidget *child){}`
- `void insertChild(int index, NavigationWidget *child){}`
- `void removeChild(NavigationWidget *child){}`
- `bool isRoot(){ return true`
- `virtual bool isLeaf(){ return true`
- `virtual void setExpanded(bool isExpanded){}`
- `QList<NavigationWidget*> childItems(){ }`

#### NavigationTreeWidget

- **Declaration / 声明**: `class NavigationTreeWidget : public NavigationTreeWidgetBase{`
- **Inherits / 继承**: `public NavigationTreeWidgetBase`

**Public Members / 公有成员**
- `NavigationTreeWidget(QVariant *icon, QString text, bool isSelectable, QWidget *parent)`
- `void __initWidget()`
- `void addChild(NavigationTreeWidgetBase *child)`
- `QString text()`
- `QIcon icon()`
- `void setText(QString text)`
- `void setIcon(QVariant *icon)`
- `void setFont(QFont font)`
- `NavigationTreeWidget *clone()`
- `int suitableWidth()`
- `void insertChild(int index, NavigationWidget *child)`
- `void removeChild(NavigationWidget *child)`
- `QList<NavigationTreeWidget*> childItems()`
- `void setExpanded(bool isExpanded, bool ani)`
- `bool isRoot()`
- `bool isLeaf()`
- `void mouseReleaseEvent(QMouseEvent *event)`
- `void setCompacted(bool isCompacted)`
- `QList<NavigationTreeWidget*> treeChildren`
- `bool isExpanded`
- `QVariant *_icon`
- `NavigationTreeItem *itemWidget`
- `QVBoxLayout *vBoxLayout`
- `QPropertyAnimation *expandAni`

**Signals / 信号**
- `void expanded()`

**Public Slots / 公共槽函数**
- `void _onClicked(bool triggerByUser, bool clickArrow)`
- `void setSelected(bool isSelected) override`

#### NavigationAvatarWidget

- **Declaration / 声明**: `class NavigationAvatarWidget : public NavigationWidget{`
- **Inherits / 继承**: `public NavigationWidget`

**Public Members / 公有成员**
- `NavigationAvatarWidget(QString name, QVariant *avatar, QWidget *parent)`
- `void setName(QString name)`
- `void setAvatar(QVariant *avatar)`
- `void paintEvent(QPaintEvent *event) override`
- `QString name`
- `QImage avatar`

#### NavigationFlyoutMenu

- **Declaration / 声明**: `class NavigationFlyoutMenu : public ScrollArea{`
- **Inherits / 继承**: `public ScrollArea`

**Public Members / 公有成员**
- `NavigationFlyoutMenu(NavigationTreeWidget *tree, QWidget *parent)`
- `void _initNode(QVariant *root)`
- `int _suitableWidth()`
- `QList<NavigationTreeWidget *> *visibleTreeNodes()`
- `QWidget *view`
- `NavigationTreeWidget *treeWidget`
- `QList<NavigationTreeWidget*> treeChildren`
- `QVBoxLayout *vBoxLayout`

**Signals / 信号**
- `void expanded()`

**Public Slots / 公共槽函数**
- `void _adjustViewSize(bool _emit)`


### `navigation/pivot.h`

#### PivotItem

- **Declaration / 声明**: `class PivotItem : public PushButton{`
- **Inherits / 继承**: `public PushButton`

**Public Members / 公有成员**
- `PivotItem(){ this->_postInit()`
- `PivotItem(QWidget *parent) : PushButton(parent){ this->_postInit()`
- `PivotItem(QString text, QWidget *parent, QVariant *icon): PushButton(text, parent, icon){ this->_postInit()`
- `PivotItem(QIcon *icon, QString text, QWidget *parent): PushButton(icon, text, parent){ this->_postInit()`
- `PivotItem(FluentIcon *icon, QString text, QWidget *parent): PushButton(icon, text, parent){ this->_postInit()`
- `void _postInit()`
- `void setSelected(bool isSelected)`
- `bool isSelected`

**Signals / 信号**
- `void itemClicked(bool)`

#### Pivot

- **Declaration / 声明**: `class Pivot : public QWidget{`
- **Inherits / 继承**: `public QWidget`

**Public Members / 公有成员**
- `Pivot(QWidget *parent)`
- `PivotItem *addItem(QString routeKey, QString text, std::function<void()> onClick, QVariant *icon)`
- `void addWidget(QString routeKey, PivotItem *widget, std::function<void()> onClick)`
- `PivotItem *insertItem(int index, QString routeKey, QString text, std::function<void()> onClick, QVariant *icon)`
- `void insertWidget(int index, QString routeKey, PivotItem *widget, std::function<void()> onClick)`
- `void removeWidget(QString routeKey)`
- `void clear()`
- `PivotItem *currentItem()`
- `void setCurrentItem(QString routeKey)`
- `void setItemFontSize(int size)`
- `PivotItem *widget(QString routeKey)`
- `void resizeEvent(QResizeEvent *event) override`
- `void paintEvent(QPaintEvent *event) override`
- `QMap<QString, PivotItem*> *items`
- `QString _currentRouteKey`
- `QHBoxLayout *hBoxLayout`
- `FluentAnimation *slideAni`

**Public Slots / 公共槽函数**
- `void _onItemClicked()`


### `navigation/segmented_widget.h`

#### SegmentedItem

- **Declaration / 声明**: `class SegmentedItem : public PivotItem{`
- **Inherits / 继承**: `public PivotItem`

**Public Members / 公有成员**
- `SegmentedItem()`
- `SegmentedItem(QWidget *parent)`
- `SegmentedItem(QString text, QWidget *parent, QVariant *icon)`
- `SegmentedItem(QIcon *icon, QString text, QWidget *parent)`
- `SegmentedItem(FluentIcon *icon, QString text, QWidget *parent)`
- `void _postInit() override`

#### SegmentedToolItem

- **Declaration / 声明**: `class SegmentedToolItem : public ToolButton{`
- **Inherits / 继承**: `public ToolButton`

**Public Members / 公有成员**
- `SegmentedToolItem(QWidget *parent)`
- `SegmentedToolItem(FluentIcon *icon, QWidget *parent)`
- `SegmentedToolItem(SpinIcon *icon, QWidget *parent)`
- `SegmentedToolItem(QIcon *icon, QWidget *parent)`
- `SegmentedToolItem(QString icon, QWidget *parent)`
- `void _postInit() override`
- `void setSelected(bool isSelected)`
- `bool isSelected`

**Signals / 信号**
- `void itemClicked(bool)`

#### SegmentedToggleToolItem

- **Declaration / 声明**: `class SegmentedToggleToolItem : public TransparentToolButton{`
- **Inherits / 继承**: `public TransparentToolButton`

**Public Members / 公有成员**
- `SegmentedToggleToolItem(QWidget *parent)`
- `SegmentedToggleToolItem(FluentIcon *icon, QWidget *parent)`
- `SegmentedToggleToolItem(SpinIcon *icon, QWidget *parent)`
- `SegmentedToggleToolItem(QIcon *icon, QWidget *parent)`
- `SegmentedToggleToolItem(QString icon, QWidget *parent)`
- `void _postInit() override`
- `void setSelected(bool isSelected)`
- `void _drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state) override`
- `bool isSelected`

**Signals / 信号**
- `void itemClicked(bool)`

#### SegmentedWidget

- **Declaration / 声明**: `class SegmentedWidget : public Pivot{`
- **Inherits / 继承**: `public Pivot`

**Public Members / 公有成员**
- `SegmentedWidget(QWidget *parent)`
- `SegmentedItem *insertItem(int index, QString routeKey, QString text, std::function<void()> onClick, QVariant *icon)`
- `void paintEvent(QPaintEvent *event) override`

#### SegmentedToolWidget

- **Declaration / 声明**: `class SegmentedToolWidget : public SegmentedWidget{`
- **Inherits / 继承**: `public SegmentedWidget`

**Public Members / 公有成员**
- `SegmentedToolWidget(QWidget *parent)`
- `SegmentedToolItem *addItem(QString routeKey, QVariant *icon, std::function<void()> onClick)`
- `void addWidget(QString routeKey, SegmentedToolItem *widget, std::function<void()> onClick)`
- `SegmentedToolItem *insertItem(int index, QString routeKey, QVariant *icon, std::function<void()> onClick)`
- `void insertWidget(int index, QString routeKey, SegmentedToolItem *widget, std::function<void()> onClick)`
- `void removeWidget(QString routeKey)`
- `void clear()`
- `SegmentedToolItem *currentItem()`
- `SegmentedToolItem *_createItem(QVariant *icon)`
- `void setCurrentItem(QString routeKey)`
- `void setItemFontSize(int size)`
- `SegmentedToolItem *widget(QString routeKey)`
- `void resizeEvent(QResizeEvent *event) override`
- `QMap<QString, SegmentedToolItem*> *items`

**Public Slots / 公共槽函数**
- `void _onItemClicked()`

#### SegmentedToggleToolWidget

- **Declaration / 声明**: `class SegmentedToggleToolWidget : public SegmentedToolWidget{`
- **Inherits / 继承**: `public SegmentedToolWidget`

**Public Members / 公有成员**
- `SegmentedToggleToolWidget(QWidget *parent)`
- `SegmentedToggleToolItem *addItem(QString routeKey, QVariant *icon, std::function<void()> onClick)`
- `void addWidget(QString routeKey, SegmentedToggleToolItem *widget, std::function<void()> onClick)`
- `SegmentedToggleToolItem *insertItem(int index, QString routeKey, QVariant *icon, std::function<void()> onClick)`
- `void insertWidget(int index, QString routeKey, SegmentedToggleToolItem *widget, std::function<void()> onClick)`
- `void removeWidget(QString routeKey)`
- `void clear()`
- `SegmentedToggleToolItem *currentItem()`
- `SegmentedToggleToolItem *_createItem(QVariant *icon)`
- `void setCurrentItem(QString routeKey)`
- `void setItemFontSize(int size)`
- `SegmentedToggleToolItem *widget(QString routeKey)`
- `void resizeEvent(QResizeEvent *event) override`
- `void paintEvent(QPaintEvent *event) override`
- `QMap<QString, SegmentedToggleToolItem*> *items`

**Public Slots / 公共槽函数**
- `void _onItemClicked()`



## Settings Components / 设置组件

### `settings/custom_color_setting_card.h`

#### CustomColorSettingCard

- **Declaration / 声明**: `class CustomColorSettingCard : public ExpandGroupSettingCard{`
- **Inherits / 继承**: `public ExpandGroupSettingCard`

**Public Members / 公有成员**
- `CustomColorSettingCard(QVariant configItem, QVariant *icon, QString title, QString content, QWidget *parent, bool enableAlpha)`
- `void __initWidget()`
- `void __initLayout()`
- `bool enableAlpha`
- `QVariant configItem`
- `QColor defaultColor`
- `QColor customColor`
- `QLabel *choiceLabel`
- `QWidget *radioWidget`
- `QVBoxLayout *radioLayout`
- `RadioButton *defaultRadioButton`
- `RadioButton *customRadioButton`
- `QButtonGroup *buttonGroup`
- `QWidget *customColorWidget`
- `QHBoxLayout *customColorLayout`
- `QLabel *customLabel`
- `QPushButton *chooseColorButton`

**Signals / 信号**
- `void colorChanged(QColor color)`

**Public Slots / 公共槽函数**
- `void __onRadioButtonClicked(RadioButton *button)`
- `void __showColorDialog()`
- `void __onCustomColorChanged(QColor color)`


### `settings/expand_setting_card.h`

#### ExpandButton

- **Declaration / 声明**: `class ExpandButton : public QAbstractButton{`
- **Inherits / 继承**: `public QAbstractButton`

**Properties / 属性**
- `Q_PROPERTY(float angle READ getAngle WRITE setAngle)`

**Public Members / 公有成员**
- `ExpandButton(QWidget *parent)`
- `void paintEvent(QPaintEvent *e) override`
- `void enterEvent(QEvent *event) override`
- `void leaveEvent(QEvent *event) override`
- `void mousePressEvent(QMouseEvent *event) override`
- `void mouseReleaseEvent(QMouseEvent *event) override`
- `void setHover(bool isHover)`
- `void setPressed(bool isPressed)`
- `float getAngle()`
- `void setAngle(float angle)`
- `bool isHover`
- `bool isPressed`
- `QPropertyAnimation *rotateAni`
- `float __angle`

**Public Slots / 公共槽函数**
- `void __onClicked()`

#### SpaceWidget

- **Declaration / 声明**: `class SpaceWidget : public QWidget{`
- **Inherits / 继承**: `public QWidget`

**Public Members / 公有成员**
- `SpaceWidget(QWidget *parent)`

#### HeaderSettingCard

- **Declaration / 声明**: `class HeaderSettingCard : public SettingCard{`
- **Inherits / 继承**: `public SettingCard`

**Public Members / 公有成员**
- `HeaderSettingCard(QVariant *icon, QString title, QString content, QWidget *parent)`
- `bool eventFilter(QObject *watched, QEvent *event) override`
- `void addWidget(QWidget *widget)`
- `void paintEvent(QPaintEvent *event) override`
- `ExpandButton *expandButton`

#### ExpandBorderWidget

- **Declaration / 声明**: `class ExpandBorderWidget : public QWidget{`
- **Inherits / 继承**: `public QWidget`

**Public Members / 公有成员**
- `ExpandBorderWidget(QWidget *parent)`
- `bool eventFilter(QObject *watched, QEvent *event) override`
- `void paintEvent(QPaintEvent *event) override`

#### ExpandSettingCard

- **Declaration / 声明**: `class ExpandSettingCard : public QScrollArea{`
- **Inherits / 继承**: `public QScrollArea`

**Public Members / 公有成员**
- `ExpandSettingCard(QVariant *icon, QString title, QString content, QWidget *parent)`
- `void __initWidget()`
- `void addWidget(QWidget *widget)`
- `void wheelEvent(QWheelEvent *e) override`
- `void setExpand(bool isExpand)`
- `void resizeEvent(QResizeEvent *event) override`
- `void _adjustViewSize()`
- `void setValue()`
- `bool isExpand`
- `QFrame *scrollWidget`
- `QFrame *view`
- `HeaderSettingCard *card`
- `QVBoxLayout *scrollLayout`
- `QVBoxLayout *viewLayout`
- `SpaceWidget *spaceWidget`
- `ExpandBorderWidget *borderWidget`
- `QPropertyAnimation *expandAni`

**Public Slots / 公共槽函数**
- `void _onExpandValueChanged()`
- `void toggleExpand()`

#### GroupSeparator

- **Declaration / 声明**: `class GroupSeparator : public QWidget{`
- **Inherits / 继承**: `public QWidget`

**Public Members / 公有成员**
- `GroupSeparator(QWidget *parent)`
- `void paintEvent(QPaintEvent *e) override`

#### ExpandGroupSettingCard

- **Declaration / 声明**: `class ExpandGroupSettingCard : public ExpandSettingCard{`
- **Inherits / 继承**: `public ExpandSettingCard`

**Public Members / 公有成员**
- `ExpandGroupSettingCard(QVariant *icon, QString title, QString content, QWidget *parent)`
- `void addGroupWidget(QWidget *widget)`


### `settings/folder_list_setting_card.h`

#### FolderItem

- **Declaration / 声明**: `class FolderItem : public QWidget{`
- **Inherits / 继承**: `public QWidget`

**Public Members / 公有成员**
- `FolderItem(QString folder, QWidget *parent)`
- `QString folder`
- `QHBoxLayout *hBoxLayout`
- `QLabel *folderlabel`
- `ToolButton *removeButton`

**Signals / 信号**
- `void removed(QWidget*)`

#### FolderListSettingCard

- **Declaration / 声明**: `class FolderListSettingCard : public ExpandSettingCard{`
- **Inherits / 继承**: `public ExpandSettingCard`

**Public Members / 公有成员**
- `FolderListSettingCard(QVariant configItem, QString title, QString content, QString directory, QWidget *parent)`
- `void __initWidget()`
- `void __addFolderItem(QString folder)`
- `void __removeFolder(FolderItem *item)`
- `QVariant configItem`
- `QString _dialogDirectory`
- `PushButton *addFolderButton`
- `QList<QString> folders`

**Signals / 信号**
- `void folderChanged(QList<QString>)`

**Public Slots / 公共槽函数**
- `void __showFolderDialog()`
- `void showConfirmDialog(FolderItem *item)`


### `settings/options_setting_card.h`

#### OptionsSettingCard

- **Declaration / 声明**: `class OptionsSettingCard : public ExpandSettingCard{`
- **Inherits / 继承**: `public ExpandSettingCard`

**Public Members / 公有成员**
- `OptionsSettingCard(QVariant configItem, QVariant *icon, QString title, QString content, QList<QString> texts, QWidget *parent)`
- `void setValue(QString value)`
- `QList<QString> texts`
- `QVariant configItem`
- `QString configName`
- `QLabel *choiceLabel`
- `QButtonGroup *buttonGroup`

**Signals / 信号**
- `void optionChanged(OptionsConfigItem*)`

**Public Slots / 公共槽函数**
- `void __onButtonClicked(RadioButton *button)`


### `settings/setting_card.h`

#### SettingCard

- **Declaration / 声明**: `class SettingCard : public QFrame{`
- **Inherits / 继承**: `public QFrame`

**Public Members / 公有成员**
- `SettingCard(QVariant *icon, QString title, QString content, QWidget *parent)`
- `void setTitle(QString title)`
- `void setContent(QString content)`
- `void paintEvent(QPaintEvent *event) override`
- `IconWidget *iconLabel`
- `QLabel *titleLabel`
- `QLabel *contentLabel`
- `QHBoxLayout *hBoxLayout`
- `QVBoxLayout *vBoxLayout`

**Public Slots / 公共槽函数**
- `virtual void setValue(QString value)`

#### SwitchSettingCard

- **Declaration / 声明**: `class SwitchSettingCard : public SettingCard{`
- **Inherits / 继承**: `public SettingCard`

**Public Members / 公有成员**
- `SwitchSettingCard(QVariant *icon, QString title, QString content, QVariant configItem, QWidget *parent)`
- `void setChecked(bool isChecked)`
- `bool isChecked()`
- `QVariant configItem`
- `SwitchButton *switchButton`

**Signals / 信号**
- `void checkedChanged(bool)`

**Public Slots / 公共槽函数**
- `void __onCheckedChanged(bool isChecked)`
- `void setValue(bool isChecked)`

#### RangeSettingCard

- **Declaration / 声明**: `class RangeSettingCard : public SettingCard{`
- **Inherits / 继承**: `public SettingCard`

**Public Members / 公有成员**
- `RangeSettingCard(QVariant configItem, QVariant *icon, QString title, QString content, QWidget *parent)`
- `QVariant configItem`
- `Slider *slider`
- `QLabel *valueLabel`

**Signals / 信号**
- `void valueChanged(int)`

**Public Slots / 公共槽函数**
- `void __onValueChanged(int value)`
- `void setValue(int value)`

#### PushSettingCard

- **Declaration / 声明**: `class PushSettingCard : public SettingCard{`
- **Inherits / 继承**: `public SettingCard`

**Public Members / 公有成员**
- `PushSettingCard(QString text, QVariant *icon, QString title, QString content, QWidget *parent)`
- `QPushButton *button`

**Signals / 信号**
- `void clicked()`

#### PrimaryPushSettingCard

- **Declaration / 声明**: `class PrimaryPushSettingCard : public PushSettingCard{`
- **Inherits / 继承**: `public PushSettingCard`

**Public Members / 公有成员**
- `PrimaryPushSettingCard(QString text, QVariant *icon, QString title, QString content, QWidget *parent)`

#### HyperlinkCard

- **Declaration / 声明**: `class HyperlinkCard : public SettingCard{`
- **Inherits / 继承**: `public SettingCard`

**Public Members / 公有成员**
- `HyperlinkCard(QString url, QString text, QVariant *icon, QString title, QString content, QWidget *parent)`
- `HyperlinkButton *linkButton`

#### ColorPickerButton

- **Declaration / 声明**: `class ColorPickerButton : public QToolButton{`
- **Inherits / 继承**: `public QToolButton`

**Public Members / 公有成员**
- `ColorPickerButton(QColor color, QString title, QWidget *parent, bool enableAlpha)`
- `void setColor(QColor color)`
- `void paintEvent(QPaintEvent *event) override`
- `QString title`
- `bool enableAlpha`
- `QColor color`

**Signals / 信号**
- `void colorChanged(QColor)`

**Public Slots / 公共槽函数**
- `void __showColorDialog()`
- `void __onColorChanged(QColor color)`

#### ColorSettingCard

- **Declaration / 声明**: `class ColorSettingCard : public SettingCard{`
- **Inherits / 继承**: `public SettingCard`

**Public Members / 公有成员**
- `ColorSettingCard(QVariant item, QVariant *icon, QString title, QString content, QWidget *parent, bool enableAlpha)`
- `QVariant configItem`
- `ColorPickerButton *colorPicker`

**Signals / 信号**
- `void colorChanged(QColor)`

**Public Slots / 公共槽函数**
- `void __onColorChanged(QColor color)`
- `void setValue(QColor color)`

#### ComboBoxSettingCard

- **Declaration / 声明**: `class ComboBoxSettingCard : public SettingCard{`
- **Inherits / 继承**: `public SettingCard`

**Public Members / 公有成员**
- `ComboBoxSettingCard(QVariant configItem, QVariant *icon, QString title, QString content, QList<QString> texts, QWidget *parent)`
- `QVariant configItem`
- `ComboBox *comboBox`
- `QMap<QString, QString> optionToText`

**Public Slots / 公共槽函数**
- `void _onCurrentIndexChanged(int index)`
- `void setValue(QString value)`


### `settings/setting_card_group.h`

#### SettingCardGroup

- **Declaration / 声明**: `class SettingCardGroup : public QWidget{`
- **Inherits / 继承**: `public QWidget`

**Public Members / 公有成员**
- `SettingCardGroup(QString title, QWidget *parent)`
- `void addSettingCard(QWidget *card)`
- `void addSettingCards(QList<QWidget*> cards)`
- `void adjustSize()`
- `QLabel *titleLabel`
- `QVBoxLayout *vBoxLayout`
- `ExpandLayout *cardLayout`



## Widget Components / 通用控件组件

### `widgets/arcylic_label.h`

#### BlurCoverThread

- **Declaration / 声明**: `class BlurCoverThread : public QThread{`
- **Inherits / 继承**: `public QThread`

**Public Members / 公有成员**
- `BlurCoverThread(QObject *parent)`
- `void run() override`
- `void blur(QString imagePath, int blurRadius, std::tuple<int, int> maxSize)`
- `QString imagePath`
- `int blurRadius`
- `std::tuple<int,int> maxSize`

**Signals / 信号**
- `void blurFinished(QPixmap)`

#### AcrylicTextureLabel

- **Declaration / 声明**: `class AcrylicTextureLabel : public QLabel{`
- **Inherits / 继承**: `public QLabel`

**Public Members / 公有成员**
- `AcrylicTextureLabel(QColor tintColor, QColor luminosityColor, float noiseOpacity, QWidget *parent)`
- `void setTintColor(QColor color)`
- `void paintEvent(QPaintEvent *e) override`
- `QColor tintColor`
- `QColor luminosityColor`
- `float nosieOpacity`
- `QImage nosizeImage`

#### AcrylicLabel

- **Declaration / 声明**: `class AcrylicLabel : public QLabel{`
- **Inherits / 继承**: `public QLabel`

**Public Members / 公有成员**
- `AcrylicLabel(int blurRadius, QColor tintColor, QColor luminosityColor, std::tuple<int,int> maxBlurSize, QWidget *parent)`
- `void __onBlurFinished(QPixmap blurPixmap)`
- `void setImage(QString imagePath)`
- `void setTintColor(QColor color)`
- `void resizeEvent(QResizeEvent *event) override`
- `QString imagePath`
- `QPixmap blurPixmap`
- `int blurRadius`
- `std::tuple<int,int> maxBlurSize`
- `AcrylicTextureLabel *acrylicTextureLabel`
- `BlurCoverThread *blurThread`

#### AcrylicBrush

- **Declaration / 声明**: `class AcrylicBrush{`

**Public Members / 公有成员**
- `AcrylicBrush(QWidget *device, int blurRadius, QColor tintColor, QColor luminosityColor, float noiseOpacity)`
- `void setBlurRadius(int radius)`
- `void setTintColor(QColor color)`
- `void setLuminosityColor(QColor color)`
- `bool isAvailable()`
- `void grabImage(QRect rect)`
- `void setImage(QVariant image)`
- `void setClipPath(QPainterPath path)`
- `QImage *textureImage()`
- `void paint()`
- `QWidget *device`
- `int blurRadius`
- `QColor tintColor`
- `QColor luminosityColor`
- `float noiseOpacity`
- `QImage noiseImage`
- `QPixmap originalImage`
- `QPixmap image`
- `QPainterPath clipPath`


### `widgets/button.h`

#### PushButton

- **Declaration / 声明**: `class PushButton : public QPushButton{`
- **Inherits / 继承**: `public QPushButton`

**Public Members / 公有成员**
- `PushButton(){}`
- `PushButton(QWidget *parent)`
- `void initialize(QWidget *parent)`
- `PushButton(QString text, QWidget *parent, QVariant *icon)`
- `PushButton(QIcon *icon, QString text, QWidget *parent)`
- `PushButton(FluentIcon *icon, QString text, QWidget *parent)`
- `void setIcon(QVariant *icon)`
- `bool setProperty(QString name, QVariant *value)`
- `virtual void _postInit(){}`
- `QIcon icon()`
- `void mousePressEvent(QMouseEvent *e) override`
- `void mouseReleaseEvent(QMouseEvent *e) override`
- `void enterEvent(QEvent *event) override`
- `void leaveEvent(QEvent *event) override`
- `void paintEvent(QPaintEvent *event) override`
- `virtual void _drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state)`
- `bool isPressed`
- `bool isHover`
- `QVariant *_icon`

#### PrimaryPushButton

- **Declaration / 声明**: `class PrimaryPushButton : public PushButton{`
- **Inherits / 继承**: `public PushButton`

**Public Members / 公有成员**
- `PrimaryPushButton(QWidget *parent) : PushButton(parent){}`
- `PrimaryPushButton(QString text, QWidget *parent, QVariant *icon)`
- `PrimaryPushButton(FluentIcon *icon, QString text, QWidget *parent)`
- `void _postInit() override {}`
- `void _drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state) override`

#### TransparentPushButton

- **Declaration / 声明**: `class TransparentPushButton : public PushButton{`
- **Inherits / 继承**: `public PushButton`

**Public Members / 公有成员**
- `TransparentPushButton(QWidget *parent) : PushButton(parent){}`
- `TransparentPushButton(QString text, QWidget *parent, QVariant *icon) : PushButton(text, parent, icon) {}`
- `TransparentPushButton(FluentIcon *icon, QString text, QWidget *parent) : PushButton(icon, text, parent){}`
- `void _postInit() override {}`

#### ToggleButton

- **Declaration / 声明**: `class ToggleButton : public PushButton{`
- **Inherits / 继承**: `public PushButton`

**Public Members / 公有成员**
- `ToggleButton(QWidget *parent) : PushButton(parent){}`
- `ToggleButton(QString text, QWidget *parent, QVariant *icon) : PushButton(text, parent, icon){ this->_postInit()`
- `ToggleButton(FluentIcon *icon, QString text, QWidget *parent) : PushButton(icon, text, parent){ this->_postInit()`
- `void _postInit() override`
- `void _drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state) override`

#### TransparentTogglePushButton

- **Declaration / 声明**: `class TransparentTogglePushButton : public ToggleButton{`
- **Inherits / 继承**: `public ToggleButton`

**Public Members / 公有成员**
- `TransparentTogglePushButton(QWidget *parent) : ToggleButton(parent){}`
- `TransparentTogglePushButton(QString text, QWidget *parent, QVariant *icon) : ToggleButton(text, parent, icon){}`
- `TransparentTogglePushButton(FluentIcon *icon, QString text, QWidget *parent) : ToggleButton(icon, text, parent){}`

#### HyperlinkButton

- **Declaration / 声明**: `class HyperlinkButton : public PushButton{`
- **Inherits / 继承**: `public PushButton`

**Public Members / 公有成员**
- `void initialize(QWidget *parent)`
- `HyperlinkButton(QVariant *url, QString text, QWidget *parent, QVariant *icon)`
- `HyperlinkButton(QIcon *icon, QVariant *url, QString text, QWidget *parent)`
- `HyperlinkButton(FluentIcon *icon, QVariant *url, QString text, QWidget *parent)`
- `QUrl *getUrl()`
- `void setUrl(QVariant *url)`
- `void _onClicked()`
- `void _drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state) override`
- `QUrl *_url`

#### RadioButton

- **Declaration / 声明**: `class RadioButton : public QRadioButton{`
- **Inherits / 继承**: `public QRadioButton`

**Public Members / 公有成员**
- `void initialize(QWidget *parent)`
- `RadioButton(QString text, QWidget *parent)`

#### ToolButton

- **Declaration / 声明**: `class ToolButton : public QToolButton{`
- **Inherits / 继承**: `public QToolButton`

**Public Members / 公有成员**
- `void initialize(QWidget *parent)`
- `ToolButton(QWidget *parent)`
- `ToolButton(FluentIcon *icon, QWidget *parent)`
- `ToolButton(SpinIcon *icon, QWidget *parent)`
- `ToolButton(QIcon *icon, QWidget *parent)`
- `ToolButton(QString icon, QWidget *parent)`
- `~ToolButton()`
- `virtual void _postInit()`
- `void setIcon(QVariant *icon)`
- `QIcon icon()`
- `bool setProperty(QString name, QVariant *value)`
- `void mousePressEvent(QMouseEvent *e) override`
- `void mouseReleaseEvent(QMouseEvent *e) override`
- `void enterEvent(QEvent *event) override`
- `void leaveEvent(QEvent *event) override`
- `void paintEvent(QPaintEvent *event) override`
- `virtual void _drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state)`
- `bool isPressed`
- `bool isHover`
- `QVariant *_icon`

#### TransparentToolButton

- **Declaration / 声明**: `class TransparentToolButton : public ToolButton{`
- **Inherits / 继承**: `public ToolButton`

**Public Members / 公有成员**
- `TransparentToolButton(QWidget *parent) : ToolButton(parent){}`
- `TransparentToolButton(FluentIcon *icon, QWidget *parent)`
- `TransparentToolButton(SpinIcon *icon, QWidget *parent)`
- `TransparentToolButton(QIcon *icon, QWidget *parent)`
- `TransparentToolButton(QString icon, QWidget *parent)`

#### PrimaryToolButton

- **Declaration / 声明**: `class PrimaryToolButton : public ToolButton{`
- **Inherits / 继承**: `public ToolButton`

**Public Members / 公有成员**
- `PrimaryToolButton(QWidget *parent) : ToolButton(parent){}`
- `PrimaryToolButton(FluentIcon *icon, QWidget *parent)`
- `PrimaryToolButton(QIcon *icon, QWidget *parent)`
- `PrimaryToolButton(QString icon, QWidget *parent)`
- `void _postInit() override {}`
- `void _drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state) override`

#### ToggleToolButton

- **Declaration / 声明**: `class ToggleToolButton : public ToolButton{`
- **Inherits / 继承**: `public ToolButton`

**Public Members / 公有成员**
- `ToggleToolButton(QWidget *parent) : ToolButton(parent){}`
- `ToggleToolButton(FluentIcon *icon, QWidget *parent)`
- `ToggleToolButton(QIcon *icon, QWidget *parent)`
- `ToggleToolButton(QString icon, QWidget *parent)`
- `void _postInit() override`
- `void _drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state) override`

#### TransparentToggleToolButton

- **Declaration / 声明**: `class TransparentToggleToolButton : public ToggleToolButton{`
- **Inherits / 继承**: `public ToggleToolButton`

**Public Members / 公有成员**
- `TransparentToggleToolButton(QWidget *parent) : ToggleToolButton(parent){}`
- `TransparentToggleToolButton(FluentIcon *icon, QWidget *parent) : ToggleToolButton(icon, parent){}`
- `TransparentToggleToolButton(QIcon *icon, QWidget *parent) : ToggleToolButton(icon, parent){}`
- `TransparentToggleToolButton(QString icon, QWidget *parent) : ToggleToolButton(icon, parent){}`

#### DropDownButtonBase

- **Declaration / 声明**: `class DropDownButtonBase{`

**Public Members / 公有成员**
- `DropDownButtonBase()`
- `void setMenu(RoundMenu *menu)`
- `RoundMenu *menu()`
- `void _showMenu()`
- `void _hideMenu()`
- `void _drawDropDownIcon(QPainter *painter, QRect rect)`
- `void paintEvent(QPaintEvent *event)`
- `RoundMenu *_menu`
- `TranslateYAnimation *arrowAni`
- `bool isHover`
- `bool isPressed`

#### DropDownPushButton

- **Declaration / 声明**: `class DropDownPushButton : public PushButton{`
- **Inherits / 继承**: `public PushButton`

**Public Members / 公有成员**
- `DropDownPushButton(QString text, QWidget *parent, QVariant *icon) : PushButton(text, parent, icon){ this->_menu = nullptr`
- `this->arrowAni = new TranslateYAnimation(this, 2)`
- `DropDownPushButton(FluentIcon *icon, QString text, QWidget *parent) : PushButton(icon, text, parent){ this->_menu = nullptr`
- `this->arrowAni = new TranslateYAnimation(this, 2)`
- `void mouseReleaseEvent(QMouseEvent *e)`
- `void paintEvent(QPaintEvent *event)`
- `void setMenu(RoundMenu *menu)`
- `RoundMenu *menu()`
- `void _showMenu()`
- `void _hideMenu()`
- `void _drawDropDownIcon(QPainter *painter, QRect rect)`
- `RoundMenu *_menu`
- `TranslateYAnimation *arrowAni`
- `bool isHover`
- `bool isPressed`

#### TransparentDropDownPushButton

- **Declaration / 声明**: `class TransparentDropDownPushButton : public DropDownPushButton{`
- **Inherits / 继承**: `public DropDownPushButton`

**Public Members / 公有成员**
- `TransparentDropDownPushButton(QString text, QWidget *parent, QVariant *icon) : DropDownPushButton(text, parent, icon){}`
- `TransparentDropDownPushButton(FluentIcon *icon, QString text, QWidget *parent) : DropDownPushButton(icon, text, parent){}`

#### DropDownToolButton

- **Declaration / 声明**: `class DropDownToolButton : public ToolButton{`
- **Inherits / 继承**: `public ToolButton`

**Public Members / 公有成员**
- `DropDownToolButton(FluentIcon *icon, QWidget *parent): ToolButton(icon, parent){ this->_menu = nullptr`
- `this->arrowAni = new TranslateYAnimation(this, 2)`
- `DropDownToolButton(QString icon, QWidget *parent) : ToolButton(icon, parent){ this->_menu = nullptr`
- `this->arrowAni = new TranslateYAnimation(this, 2)`
- `void mouseReleaseEvent(QMouseEvent *e) override`
- `void _drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state) override`
- `void paintEvent(QPaintEvent *event) override`
- `void setMenu(RoundMenu *menu)`
- `RoundMenu *menu()`
- `void _showMenu()`
- `void _hideMenu()`
- `void _drawDropDownIcon(QPainter *painter, QRect rect)`
- `RoundMenu *_menu`
- `TranslateYAnimation *arrowAni`
- `bool isHover`
- `bool isPressed`

#### TransparentDropDownToolButton

- **Declaration / 声明**: `class TransparentDropDownToolButton : public DropDownToolButton{`
- **Inherits / 继承**: `public DropDownToolButton`

**Public Members / 公有成员**
- `TransparentDropDownToolButton(FluentIcon *icon, QWidget *parent): DropDownToolButton(icon, parent){}`
- `TransparentDropDownToolButton(QString icon, QWidget *parent) : DropDownToolButton(icon, parent){}`

#### PrimaryDropDownPushButton

- **Declaration / 声明**: `class PrimaryDropDownPushButton : public PrimaryPushButton{`
- **Inherits / 继承**: `public PrimaryPushButton`

**Public Members / 公有成员**
- `PrimaryDropDownPushButton(QString text, QWidget *parent, QVariant *icon) : PrimaryPushButton(text, parent, icon){ this->_menu = nullptr`
- `this->arrowAni = new TranslateYAnimation(this, 2)`
- `PrimaryDropDownPushButton(FluentIcon *icon, QString text, QWidget *parent) : PrimaryPushButton(icon, text, parent){ this->_menu = nullptr`
- `this->arrowAni = new TranslateYAnimation(this, 2)`
- `void mouseReleaseEvent(QMouseEvent *e)`
- `void paintEvent(QPaintEvent *event)`
- `void setMenu(RoundMenu *menu)`
- `RoundMenu *menu()`
- `void _showMenu()`
- `void _hideMenu()`
- `void _drawDropDownIcon(QPainter *painter, QRect rect)`
- `RoundMenu *_menu`
- `TranslateYAnimation *arrowAni`
- `bool isHover`
- `bool isPressed`

#### PrimaryDropDownToolButton

- **Declaration / 声明**: `class PrimaryDropDownToolButton : public PrimaryToolButton{`
- **Inherits / 继承**: `public PrimaryToolButton`

**Public Members / 公有成员**
- `PrimaryDropDownToolButton(QWidget *parent) : PrimaryToolButton(parent){}`
- `PrimaryDropDownToolButton(FluentIcon *icon, QWidget *parent): PrimaryToolButton(icon, parent){ this->_menu = nullptr`
- `this->arrowAni = new TranslateYAnimation(this, 2)`
- `void mouseReleaseEvent(QMouseEvent *e)`
- `void paintEvent(QPaintEvent *event)`
- `void setMenu(RoundMenu *menu)`
- `RoundMenu *menu()`
- `void _showMenu()`
- `void _hideMenu()`
- `void _drawDropDownIcon(QPainter *painter, QRect rect)`
- `void _drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state) override`
- `RoundMenu *_menu`
- `TranslateYAnimation *arrowAni`
- `bool isHover`
- `bool isPressed`

#### SplitDropButton

- **Declaration / 声明**: `class SplitDropButton : public ToolButton{`
- **Inherits / 继承**: `public ToolButton`

**Public Members / 公有成员**
- `SplitDropButton(QWidget *parent) : ToolButton(parent){ this->_postInit()`
- `SplitDropButton(FluentIcon *icon, QWidget *parent) : ToolButton(icon, parent){ this->_postInit()`
- `SplitDropButton(QIcon *icon, QWidget *parent) : ToolButton(icon, parent){ this->_postInit()`
- `SplitDropButton(QString icon, QWidget *parent) : ToolButton(icon, parent){ this->_postInit()`
- `void _drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state) override`
- `void _postInit() override`
- `TranslateYAnimation *arrowAni`

#### PrimarySplitDropButton

- **Declaration / 声明**: `class PrimarySplitDropButton : public PrimaryToolButton{`
- **Inherits / 继承**: `public PrimaryToolButton`

**Public Members / 公有成员**
- `PrimarySplitDropButton(QWidget *parent) : PrimaryToolButton(parent){ this->_menu = nullptr`
- `this->arrowAni = new TranslateYAnimation(this, 2)`
- `PrimarySplitDropButton(FluentIcon *icon, QWidget *parent): PrimaryToolButton(icon, parent){ this->_menu = nullptr`
- `this->arrowAni = new TranslateYAnimation(this, 2)`
- `void mouseReleaseEvent(QMouseEvent *e)`
- `void paintEvent(QPaintEvent *event)`
- `void setMenu(RoundMenu *menu)`
- `RoundMenu *menu()`
- `void _showMenu()`
- `void _hideMenu()`
- `void _drawDropDownIcon(QPainter *painter, QRect rect)`
- `void _drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state) override`
- `void _postInit() override`
- `RoundMenu *_menu`
- `TranslateYAnimation *arrowAni`

#### SplitWidgetBase

- **Declaration / 声明**: `class SplitWidgetBase : public QWidget{`
- **Inherits / 继承**: `public QWidget`

**Public Members / 公有成员**
- `SplitWidgetBase(){}`
- `SplitWidgetBase(QWidget *parent)`
- `void setWidget(QWidget *widget)`
- `void setDropButton(SplitDropButton *button)`
- `void setDropIcon(QVariant *icon)`
- `void setDropIconSize(QSize *size)`
- `void setFlyout(QWidget *flyout)`
- `SplitDropButton *dropButton`
- `QHBoxLayout *hBoxLayout`
- `QWidget *flyout`

**Signals / 信号**
- `void dropDownClicked()`

**Public Slots / 公共槽函数**
- `void showFlyout()`

#### SplitPushButton

- **Declaration / 声明**: `class SplitPushButton : public SplitWidgetBase{`
- **Inherits / 继承**: `public SplitWidgetBase`

**Public Members / 公有成员**
- `SplitPushButton(){}`
- `SplitPushButton(QWidget *parent)`
- `SplitPushButton(QString text, QWidget *parent, QVariant *icon)`
- `SplitPushButton(QIcon *icon, QString text, QWidget *parent)`
- `SplitPushButton(FluentIcon *icon, QString text, QWidget *parent)`
- `void _postInit(){}`
- `QString text()`
- `void setText(QString text)`
- `QIcon *icon()`
- `void setIcon(QVariant *icon)`
- `void setIconSize(QSize *size)`
- `PushButton *button`

**Signals / 信号**
- `void clicked()`

#### SplitWidgetBase2PrimaryButton

- **Declaration / 声明**: `class SplitWidgetBase2PrimaryButton : public QWidget{`
- **Inherits / 继承**: `public QWidget`

**Public Members / 公有成员**
- `SplitWidgetBase2PrimaryButton(){}`
- `SplitWidgetBase2PrimaryButton(QWidget *parent)`
- `void setWidget(QWidget *widget)`
- `void setDropButton(PrimarySplitDropButton *button)`
- `void setDropIcon(QVariant *icon)`
- `void setDropIconSize(QSize *size)`
- `void setFlyout(QWidget *flyout)`
- `PrimarySplitDropButton *dropButton`
- `QHBoxLayout *hBoxLayout`
- `QWidget *flyout`

**Signals / 信号**
- `void dropDownClicked()`

**Public Slots / 公共槽函数**
- `void showFlyout()`

#### PrimarySplitPushButton

- **Declaration / 声明**: `class PrimarySplitPushButton : public SplitWidgetBase2PrimaryButton{`
- **Inherits / 继承**: `public SplitWidgetBase2PrimaryButton`

**Public Members / 公有成员**
- `PrimarySplitPushButton(QWidget *parent)`
- `PrimarySplitPushButton(QString text, QWidget *parent, QVariant *icon)`
- `PrimarySplitPushButton(QIcon *icon, QString text, QWidget *parent)`
- `PrimarySplitPushButton(FluentIcon *icon, QString text, QWidget *parent)`
- `void _postInit(){}`
- `QString text()`
- `void setText(QString text)`
- `QIcon *icon()`
- `void setIcon(QVariant *icon)`
- `void setIconSize(QSize *size)`
- `PrimaryPushButton *button`

**Signals / 信号**
- `void clicked()`

#### SplitToolButton

- **Declaration / 声明**: `class SplitToolButton : public SplitWidgetBase{`
- **Inherits / 继承**: `public SplitWidgetBase`

**Public Members / 公有成员**
- `SplitToolButton(){}`
- `SplitToolButton(QWidget *parent)`
- `SplitToolButton(QWidget *parent, QVariant *icon)`
- `SplitToolButton(QIcon *icon, QWidget *parent)`
- `SplitToolButton(FluentIcon *icon, QWidget *parent)`
- `void _postInit(){}`
- `QString text()`
- `void setText(QString text)`
- `QIcon *icon()`
- `void setIcon(QVariant *icon)`
- `void setIconSize(QSize *size)`
- `ToolButton *button`

**Signals / 信号**
- `void clicked()`

#### PrimarySplitToolButton

- **Declaration / 声明**: `class PrimarySplitToolButton : public SplitWidgetBase2PrimaryButton{`
- **Inherits / 继承**: `public SplitWidgetBase2PrimaryButton`

**Public Members / 公有成员**
- `PrimarySplitToolButton(){}`
- `PrimarySplitToolButton(QWidget *parent)`
- `PrimarySplitToolButton(QWidget *parent, QVariant *icon)`
- `PrimarySplitToolButton(QIcon *icon, QWidget *parent)`
- `PrimarySplitToolButton(FluentIcon *icon, QWidget *parent)`
- `void _postInit(){}`
- `QString text()`
- `void setText(QString text)`
- `QIcon *icon()`
- `void setIcon(QVariant *icon)`
- `void setIconSize(QSize *size)`
- `PrimaryToolButton *button`

**Signals / 信号**
- `void clicked()`

#### PillPushButton

- **Declaration / 声明**: `class PillPushButton : public ToggleButton{`
- **Inherits / 继承**: `public ToggleButton`

**Public Members / 公有成员**
- `PillPushButton(QWidget *parent) : ToggleButton(parent){}`
- `PillPushButton(QString text, QWidget *parent, QVariant *icon) : ToggleButton(text, parent, icon){}`
- `PillPushButton(FluentIcon *icon, QString text, QWidget *parent) : ToggleButton(icon, text, parent){}`
- `void paintEvent(QPaintEvent *event) override`

#### PillToolButton

- **Declaration / 声明**: `class PillToolButton : public ToggleToolButton{`
- **Inherits / 继承**: `public ToggleToolButton`

**Public Members / 公有成员**
- `PillToolButton(FluentIcon *icon, QWidget *parent) : ToggleToolButton(icon, parent){}`
- `PillToolButton(QIcon *icon, QWidget *parent) : ToggleToolButton(icon, parent){}`
- `PillToolButton(QString icon, QWidget *parent) : ToggleToolButton(icon, parent){}`
- `void paintEvent(QPaintEvent *event) override`


### `widgets/card_widget.h`

#### CardBackgroundColorObject

- **Declaration / 声明**: `class CardBackgroundColorObject : public BackgroundColorObject{`
- **Inherits / 继承**: `public BackgroundColorObject`

**Public Members / 公有成员**
- `CardBackgroundColorObject(CardWidget *parent)`
- `QColor getBackgroundColor() override`
- `void setBackgroundColor(QColor color) override`

#### CardWidget

- **Declaration / 声明**: `class CardWidget : public QFrame{`
- **Inherits / 继承**: `public QFrame`

**Properties / 属性**
- `Q_PROPERTY(int borderRadius READ getBorderRadius WRITE setBorderRadius)`

**Public Members / 公有成员**
- `CardWidget(QWidget *parent)`
- `bool eventFilter(QObject *obj, QEvent *e) override`
- `void mousePressEvent(QMouseEvent *e) override`
- `void mouseReleaseEvent(QMouseEvent *e) override`
- `void enterEvent(QEvent *e) override`
- `void leaveEvent(QEvent *e) override`
- `void focusInEvent(QFocusEvent *e) override`
- `virtual QColor _normalBackgroundColor()`
- `virtual QColor _hoverBackgroundColor()`
- `virtual QColor _pressedBackgroundColor()`
- `QColor _focusInBackgroundColor()`
- `QColor _disabledBackgroundColor()`
- `void _updateBackgroundColor()`
- `QColor getBackgroundColor()`
- `void setBackgroundColor(QColor color)`
- `QColor backgroundColor()`
- `void setClickEnabled(bool isEnabled)`
- `bool isClickEnabled()`
- `void setBorderRadius(int radius)`
- `int getBorderRadius()`
- `void paintEvent(QPaintEvent *event) override`
- `bool isHover`
- `bool isPressed`
- `CardBackgroundColorObject *bgColorObject`
- `QPropertyAnimation *backgroundColorAni`
- `bool _isClickEnabled`
- `int _borderRadius`

**Signals / 信号**
- `void clicked()`

#### SimpleCardWidget

- **Declaration / 声明**: `class SimpleCardWidget : public CardWidget{`
- **Inherits / 继承**: `public CardWidget`

**Public Members / 公有成员**
- `SimpleCardWidget(QWidget *parent)`
- `QColor _normalBackgroundColor() override`
- `QColor _hoverBackgroundColor() override`
- `QColor _pressedBackgroundColor() override`
- `void paintEvent(QPaintEvent *event) override`

#### ElevatedCardWidget

- **Declaration / 声明**: `class ElevatedCardWidget : public SimpleCardWidget{`
- **Inherits / 继承**: `public SimpleCardWidget`

**Public Members / 公有成员**
- `ElevatedCardWidget(QWidget *parent)`
- `void enterEvent(QEvent *e) override`
- `void leaveEvent(QEvent *e) override`
- `void mousePressEvent(QMouseEvent *e) override`
- `void _startElevateAni(QPoint start, QPoint end)`
- `QColor _hoverBackgroundColor() override`
- `QColor _pressedBackgroundColor() override`
- `DropShadowAnimation *shadowAni`
- `QPropertyAnimation *elevatedAni`
- `QPoint _originalPos`

#### CardSeparator

- **Declaration / 声明**: `class CardSeparator : public QWidget{`
- **Inherits / 继承**: `public QWidget`

**Public Members / 公有成员**
- `CardSeparator(QWidget *parent)`
- `void paintEvent(QPaintEvent *event) override`

#### HeaderCardWidget

- **Declaration / 声明**: `class HeaderCardWidget : public SimpleCardWidget{`
- **Inherits / 继承**: `public SimpleCardWidget`

**Properties / 属性**
- `Q_PROPERTY(QString title READ getTitle WRITE setTitle)`

**Public Members / 公有成员**
- `HeaderCardWidget(QWidget *parent)`
- `HeaderCardWidget(QString title, QWidget *parent)`
- `QString getTitle()`
- `void setTitle(QString title)`
- `QWidget *headerView`
- `QLabel *headerLabel`
- `CardSeparator *separator`
- `QWidget *view`
- `QVBoxLayout *vBoxLayout`
- `QHBoxLayout *headerLayout`
- `QHBoxLayout *viewLayout`


### `widgets/check_box.h`

#### CheckBoxIcon

- **Declaration / 声明**: `class CheckBoxIcon : public FluentIconBase{`
- **Inherits / 继承**: `public FluentIconBase`

**Public Members / 公有成员**
- `QString path(Theme theme) override`

#### CheckBox

- **Declaration / 声明**: `class CheckBox : public QCheckBox{`
- **Inherits / 继承**: `public QCheckBox`

**Public Members / 公有成员**
- `CheckBox(QWidget *parent)`
- `CheckBox(QString text, QWidget *parent)`
- `void paintEvent(QPaintEvent *e)`


### `widgets/combo_box.h`

#### ComboItem

- **Declaration / 声明**: `class ComboItem{`

**Public Members / 公有成员**
- `ComboItem(QString text, QVariant *icon, QVariant *userData)`
- `QIcon getIcon()`
- `void setIcon()`
- `QString text`
- `QVariant *userData`
- `QVariant *_icon`

#### ComboBox

- **Declaration / 声明**: `class ComboBox : public QPushButton{`
- **Inherits / 继承**: `public QPushButton`

**Public Members / 公有成员**
- `ComboBox(QWidget *parent)`
- `bool eventFilter(QObject *watched, QEvent *event)`
- `void addItem(QString text, QVariant *icon, QVariant *userData)`
- `void addItems(QList<QString> texts)`
- `void removeItem(int index)`
- `int currentIndex()`
- `void setCurrentIndex(int index)`
- `void setText(QString text)`
- `QString currentText()`
- `QVariant *currentData()`
- `void setCurrentText(QString text)`
- `void setItemText(int index, QString text)`
- `QVariant *itemData(int index)`
- `QString itemText(int index)`
- `QVariant *itemIcon(int index)`
- `void setItemData(int index, QVariant *value)`
- `void setItemIcon(int index, QVariant *icon)`
- `int findData(QVariant *data)`
- `int findText(QString text)`
- `void clear()`
- `int count()`
- `void insertItem(int index, QString text, QVariant *icon, QVariant *userData)`
- `void insertItems(int index, QList<QString> texts)`
- `void setMaxVisibleItems(int num)`
- `int maxVisibleItems()`
- `void _closeComboMenu()`
- `ComboBoxMenu *_createComboMenu()`
- `void _showComboMenu()`
- `void _toggleComboMenu()`
- `void setPlaceholderText(QString text)`
- `void _updateTextState(bool isPlaceholder)`
- `void mouseReleaseEvent(QMouseEvent *e)`
- `void paintEvent(QPaintEvent *e)`
- `bool isHover`
- `bool isPressed`
- `QList<ComboItem *> *items`
- `int _currentIndex`
- `int _maxVisibleItems`
- `ComboBoxMenu *dropMenu`
- `QString _placeholderText`
- `TranslateYAnimation *arrowAni`

**Signals / 信号**
- `void currentIndexChanged(int)`
- `void currentTextChanged(QString)`

**Public Slots / 公共槽函数**
- `void _onItemClicked(int index)`
- `void _onDropMenuClosed()`

#### EditableComboBox

- **Declaration / 声明**: `class EditableComboBox : public LineEdit{`
- **Inherits / 继承**: `public LineEdit`

**Public Members / 公有成员**
- `EditableComboBox(QWidget *parent)`
- `bool eventFilter(QObject *watched, QEvent *event)`
- `void addItem(QString text, QVariant *icon, QVariant *userData)`
- `void addItems(QList<QString> texts)`
- `void removeItem(int index)`
- `int currentIndex()`
- `void setCurrentIndex(int index)`
- `void setText(QString text)`
- `QString currentText()`
- `QVariant *currentData()`
- `void setCurrentText(QString text)`
- `void setItemText(int index, QString text)`
- `QVariant *itemData(int index)`
- `QString itemText(int index)`
- `QVariant *itemIcon(int index)`
- `void setItemData(int index, QVariant *value)`
- `void setItemIcon(int index, QVariant *icon)`
- `int findData(QVariant *data)`
- `int findText(QString text)`
- `void clear()`
- `int count()`
- `void insertItem(int index, QString text, QVariant *icon, QVariant *userData)`
- `void insertItems(int index, QList<QString> texts)`
- `void setMaxVisibleItems(int num)`
- `int maxVisibleItems()`
- `void _closeComboMenu()`
- `ComboBoxMenu *_createComboMenu()`
- `void _showComboMenu()`
- `void _toggleComboMenu()`
- `void setCompleterMenu(CompleterMenu *menu)`
- `void setPlaceholderText(QString text)`
- `bool isHover`
- `bool isPressed`
- `QList<ComboItem *> *items`
- `int _currentIndex`
- `int _maxVisibleItems`
- `ComboBoxMenu *dropMenu`
- `QString _placeholderText`
- `LineEditButton *dropButton`

**Signals / 信号**
- `void currentIndexChanged(int)`
- `void currentTextChanged(QString)`

**Public Slots / 公共槽函数**
- `void _onItemClicked(int index)`
- `void _onDropMenuClosed()`
- `void _onReturnPressed()`
- `void _onClearButtonClicked()`
- `void __onActivated(QString text)`
- `void _onTextEdited(QString text)`

#### ComboBoxMenu

- **Declaration / 声明**: `class ComboBoxMenu : public RoundMenu{`
- **Inherits / 继承**: `public RoundMenu`

**Public Members / 公有成员**
- `ComboBoxMenu(QWidget *parent)`
- `void exec(QPoint *pos, bool ani, MenuAnimationType aniType)`


### `widgets/command_bar.h`

#### CommandButton

- **Declaration / 声明**: `class CommandButton : public TransparentToggleToolButton{`
- **Inherits / 继承**: `public TransparentToggleToolButton`

**Public Members / 公有成员**
- `CommandButton(QWidget *parent) : TransparentToggleToolButton(parent){ this->_postInit()`
- `CommandButton(FluentIcon *icon, QWidget *parent) : TransparentToggleToolButton(icon, parent){ this->_postInit()`
- `CommandButton(QIcon *icon, QWidget *parent) : TransparentToggleToolButton(icon, parent){ this->_postInit()`
- `CommandButton(QString icon, QWidget *parent) : TransparentToggleToolButton(icon, parent){ this->_postInit()`
- `void _postInit() override`
- `void setTight(bool isTight)`
- `bool isTight() const`
- `QSize sizeHint() const override`
- `bool isIconOnly() const`
- `void _drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state) override`
- `QString text() const`
- `void setText(QString text)`
- `void setAction(QAction *action)`
- `QAction *action()`
- `void paintEvent(QPaintEvent *event) override`
- `QString _text`
- `QAction *_action`
- `bool _isTight`

**Public Slots / 公共槽函数**
- `void _onActionChanged()`

#### CommandToolTipFilter

- **Declaration / 声明**: `class CommandToolTipFilter : public ToolTipFilter{`
- **Inherits / 继承**: `public ToolTipFilter`

**Public Members / 公有成员**
- `CommandToolTipFilter(QWidget *parent, int showDelay, ToolTipPosition position)`
- `bool _canShowToolTip() override`

#### MoreActionsButton

- **Declaration / 声明**: `class MoreActionsButton : public CommandButton{`
- **Inherits / 继承**: `public CommandButton`

**Public Members / 公有成员**
- `MoreActionsButton(QWidget *parent) : CommandButton(parent){ this->_postInit()`
- `MoreActionsButton(FluentIcon *icon, QWidget *parent) : CommandButton(icon, parent){ this->_postInit()`
- `MoreActionsButton(QIcon *icon, QWidget *parent) : CommandButton(icon, parent){ this->_postInit()`
- `MoreActionsButton(QString icon, QWidget *parent) : CommandButton(icon, parent){ this->_postInit()`
- `void _postInit()`
- `QSize sizeHint() const override`
- `void clearState()`

#### CommandSeparator

- **Declaration / 声明**: `class CommandSeparator : public QWidget{`
- **Inherits / 继承**: `public QWidget`

**Public Members / 公有成员**
- `CommandSeparator(QWidget *parent)`
- `void paintEvent(QPaintEvent *e) override`

#### CommandMenu

- **Declaration / 声明**: `class CommandMenu : public RoundMenu{`
- **Inherits / 继承**: `public RoundMenu`

**Public Members / 公有成员**
- `CommandMenu(QWidget *parent)`

#### CommandBar

- **Declaration / 声明**: `class CommandBar : public QFrame{`
- **Inherits / 继承**: `public QFrame`

**Public Members / 公有成员**
- `CommandBar(QWidget *parent)`
- `void setSpaing(int spacing)`
- `int spacing()`
- `CommandButton* addAction(QAction *action)`
- `void addActions(QList<QAction*> actions)`
- `void addHiddenAction(QAction *action)`
- `void addHiddenActions(QList<QAction*> actions)`
- `CommandButton* insertAction(QAction *before, QAction *action)`
- `void addSeparator()`
- `void insertSeparator(int index)`
- `void addWidget(QWidget *widget)`
- `void removeAction(QAction *action)`
- `void removeWidget(QWidget *widget)`
- `void removeHiddenAction(QAction *action)`
- `void setToolButtonStyle(Qt::ToolButtonStyle style)`
- `Qt::ToolButtonStyle toolButtonStyle()`
- `void setButtonTight(bool isThight)`
- `bool isButtonTight()`
- `void setIconSize(QSize size)`
- `QSize iconSize()`
- `void resizeEvent(QResizeEvent *event) override`
- `CommandButton* _createButton(QAction *action)`
- `void _insertWidgetToLayout(int index, QWidget *widget)`
- `QSize minimumSizeHint()`
- `void updateGeometry()`
- `QList<QWidget*> _visibleWidgets()`
- `int suitableWidth()`
- `void resizeToSuitableWidth()`
- `void setFont(QFont font)`
- `QList<CommandButton*> commandButtons()`
- `virtual void setMenuDropDown(bool down)`
- `virtual bool isMenuDropDown()`
- `QList<QWidget*> _widgets`
- `QList<QWidget*> _hiddenWidgets`
- `QList<QAction*> _hiddenActions`
- `MenuAnimationType _menuAnimation`
- `Qt::ToolButtonStyle _toolButtonStyle`
- `QSize _iconSize`
- `bool _isButtonTight`
- `int _spacing`
- `MoreActionsButton *moreButton`

**Public Slots / 公共槽函数**
- `virtual void _showMoreActionsMenu()`

#### CommandViewMenu

- **Declaration / 声明**: `class CommandViewMenu : public CommandMenu{`
- **Inherits / 继承**: `public CommandMenu`

**Public Members / 公有成员**
- `CommandViewMenu(QWidget *parent)`
- `void setDropDown(bool down, bool _long)`

#### CommandViewBar

- **Declaration / 声明**: `class CommandViewBar : public CommandBar{`
- **Inherits / 继承**: `public CommandBar`

**Public Members / 公有成员**
- `CommandViewBar(QWidget *parent)`
- `void setMenuDropDown(bool down) override`
- `bool isMenuDropDown() override`

**Public Slots / 公共槽函数**
- `void _showMoreActionsMenu() override`

#### CommandBarView

- **Declaration / 声明**: `class CommandBarView : public FlyoutViewBase{`
- **Inherits / 继承**: `public FlyoutViewBase`

**Public Members / 公有成员**
- `CommandBarView(QWidget *parent)`
- `void setMenuVisible(bool isVisible)`
- `void addWidget(QWidget *widget)`
- `void setSpaing(int spacing)`
- `int spacing()`
- `CommandButton *addAction(QAction *action)`
- `void addActions(QList<QAction*> actions)`
- `void addHiddenAction(QAction *action)`
- `void addHiddenActions(QList<QAction*> actions)`
- `CommandButton *insertAction(QAction *before, QAction *action)`
- `void addSeparator()`
- `void insertSeparator(int index)`
- `void removeAction(QAction *action)`
- `void removeWidget(QWidget *widget)`
- `void removeHiddenAction(QAction *action)`
- `void setToolButtonStyle(Qt::ToolButtonStyle style)`
- `Qt::ToolButtonStyle toolButtonStyle()`
- `void setButtonTight(bool isThight)`
- `bool isButtonTight()`
- `void setIconSize(QSize size)`
- `QSize iconSize()`
- `void setFont(QFont font)`
- `virtual void setMenuDropDown(bool down)`
- `int suitableWidth()`
- `void resizeToSuitableWidth()`
- `QList<QAction *> actions()`
- `void paintEvent(QPaintEvent *e) override`
- `CommandViewBar *bar`
- `QHBoxLayout *hBoxLayout`
- `bool _isMenuVisible`


### `widgets/cycle_list_widget.h`

#### ScrollButtonC

- **Declaration / 声明**: `class ScrollButtonC : public QToolButton{`
- **Inherits / 继承**: `public QToolButton`

**Public Members / 公有成员**
- `ScrollButtonC(FluentIcon *icon, QWidget *parent)`
- `bool eventFilter(QObject *watched, QEvent *event) override`
- `void paintEvent(QPaintEvent *e) override`
- `FluentIcon *_icon`
- `bool isPressed`

#### CycleListWidget

- **Declaration / 声明**: `class CycleListWidget : public QListWidget{`
- **Inherits / 继承**: `public QListWidget`

**Public Members / 公有成员**
- `CycleListWidget(QList<QVariant> *items, QSize *itemSize, Qt::Alignment align, QWidget *parent)`
- `void setItems(QList<QVariant> *items)`
- `void _createItems(QList<QVariant> *items)`
- `void _addColumnItems(QList<QVariant> *items, bool disabled)`
- `void _onItemClicked(QListWidgetItem *item)`
- `void setSelectedItem(QString text)`
- `void scrollToItem(QListWidgetItem *item, ScrollHint hint)`
- `void wheelEvent(QWheelEvent *e) override`
- `void scrollDown()`
- `void scrollUp()`
- `void enterEvent(QEvent *event) override`
- `void leaveEvent(QEvent *event) override`
- `void resizeEvent(QResizeEvent *event) override`
- `bool eventFilter(QObject *watched, QEvent *event) override`
- `QListWidgetItem *currentItem()`
- `int currentIndex()`
- `void setCurrentIndex(int index)`
- `QSize *itemSize`
- `Qt::Alignment align`
- `ScrollButtonC *upButton`
- `ScrollButtonC *downButton`
- `int scrollDuration`
- `QList<QVariant> *originItems`
- `SmoothScrollBar *vScrollBar`
- `int visibleNumber`
- `bool isCycle`
- `int _currentIndex`

**Signals / 信号**
- `void currentItemChanged(QListWidgetItem *item)`


### `widgets/flip_view.h`

#### FlipScrollButton

- **Declaration / 声明**: `class FlipScrollButton : public ToolButton{`
- **Inherits / 继承**: `public ToolButton`

**Properties / 属性**
- `Q_PROPERTY(float opacity READ getOpacity WRITE setOpacity)`

**Public Members / 公有成员**
- `Q_PROPERTY(float opacity READ getOpacity WRITE setOpacity) FlipScrollButton(QWidget *parent)`
- `FlipScrollButton(FluentIcon *icon, QWidget *parent)`
- `FlipScrollButton(SpinIcon *icon, QWidget *parent)`
- `FlipScrollButton(QIcon *icon, QWidget *parent)`
- `FlipScrollButton(QString icon, QWidget *parent)`
- `void _postInit() override`
- `float getOpacity()`
- `void setOpacity(float o)`
- `bool isTransparent()`
- `void fadeIn()`
- `void fadeOut()`
- `void paintEvent(QPaintEvent *event) override`
- `float _opacity`
- `QPropertyAnimation *opacityAni`

#### FlipImageDelegate

- **Declaration / 声明**: `class FlipImageDelegate : public QStyledItemDelegate{`
- **Inherits / 继承**: `public QStyledItemDelegate`

**Public Members / 公有成员**
- `FlipImageDelegate(QWidget *parent)`
- `QSize itemSize(int index) const`
- `void setBorderRadius(int radius)`
- `void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override`
- `int borderRadius`

#### FlipView

- **Declaration / 声明**: `class FlipView : public QListWidget{`
- **Inherits / 继承**: `public QListWidget`

**Properties / 属性**
- `Q_PROPERTY(QSize itemSize READ getItemSize WRITE setItemSize)`
- `Q_PROPERTY(int borderRadius READ getBorderRadius WRITE setBorderRadius)`
- `Q_PROPERTY(Qt::AspectRatioMode aspectRatioMode READ getAspectRatioMode WRITE setAspectRatioMode)`

**Public Members / 公有成员**
- `FlipView(QWidget *parent)`
- `FlipView(Qt::Orientation orientation, QWidget *parent)`
- `void _postInit()`
- `bool isHorizontal()`
- `void setItemSize(QSize size)`
- `QSize getItemSize()`
- `void setBorderRadius(int radius)`
- `int getBorderRadius()`
- `void setCurrentIndex(int index)`
- `void scrollToIndex(int index)`
- `int currentIndex()`
- `QImage image(int index)`
- `void addImage(QVariant *image)`
- `void addImages(QList<QVariant*> images)`
- `void setItemImage(int index, QVariant *image)`
- `void _adjustItemSize(QListWidgetItem *item)`
- `QImage itemImage(int index)`
- `void resizeEvent(QResizeEvent *event) override`
- `void enterEvent(QEvent *event) override`
- `void leaveEvent(QEvent *event) override`
- `void showEvent(QShowEvent *event) override`
- `void wheelEvent(QWheelEvent *e) override`
- `Qt::AspectRatioMode getAspectRatioMode()`
- `void setAspectRatioMode(Qt::AspectRatioMode mode)`
- `Qt::Orientation orientation`
- `bool isHover`
- `int _currentIndex`
- `Qt::AspectRatioMode _aspectRatioMode`
- `QSize _itemSize`
- `FlipImageDelegate *delegate`
- `SmoothScrollBar *scrollBar`
- `FlipScrollButton *preButton`
- `FlipScrollButton *nextButton`

**Signals / 信号**
- `void currentIndexChanged(int)`

**Public Slots / 公共槽函数**
- `void scrollPrevious()`
- `void scrollNext()`

#### HorizontalFlipView

- **Declaration / 声明**: `class HorizontalFlipView : public FlipView{`
- **Inherits / 继承**: `public FlipView`

**Public Members / 公有成员**
- `HorizontalFlipView(QWidget *parent)`

#### VerticalFlipView

- **Declaration / 声明**: `class VerticalFlipView : public FlipView{`
- **Inherits / 继承**: `public FlipView`

**Public Members / 公有成员**
- `VerticalFlipView(QWidget *parent)`


### `widgets/flyout.h`

#### IconWidgetForFlyout

- **Declaration / 声明**: `class IconWidgetForFlyout : public IconWidget{`
- **Inherits / 继承**: `public IconWidget`

**Public Members / 公有成员**
- `IconWidgetForFlyout(QWidget *parent) : IconWidget(parent){ this->setFixedSize(36, 54)`
- `IconWidgetForFlyout(QVariant *icon, QWidget *parent)`
- `IconWidgetForFlyout(FluentIcon icon, QWidget *parent)`
- `IconWidgetForFlyout(QIcon icon, QWidget *parent)`
- `IconWidgetForFlyout(QString icon, QWidget *parent)`
- `void paintEvent(QPaintEvent *event) override`

#### FlyoutViewBase

- **Declaration / 声明**: `class FlyoutViewBase : public QWidget{`
- **Inherits / 继承**: `public QWidget`

**Public Members / 公有成员**
- `FlyoutViewBase(QWidget *parent)`
- `void addWidget(QWidget *widget, int stretch, Qt::AlignmentFlag align)`
- `QColor backgroundColor()`
- `QColor borderColor()`
- `void paintEvent(QPaintEvent *event) override`

#### FlyoutView

- **Declaration / 声明**: `class FlyoutView : public FlyoutViewBase{`
- **Inherits / 继承**: `public FlyoutViewBase`

**Public Members / 公有成员**
- `FlyoutView(QString title, QString content, QVariant *icon, QVariant *image, bool isClosable, QWidget *parent)`
- `void __initWidgets()`
- `void __initLayout()`
- `void addWidget(QWidget *widget, int stretch, Qt::AlignmentFlag align)`
- `void __addImageToLayout()`
- `void _adjustText()`
- `void _adjustImage()`
- `void showEvent(QShowEvent *event) override`
- `QVariant *icon`
- `QString title`
- `QVariant *image`
- `QString content`
- `bool isClosable`
- `QVBoxLayout *vBoxLayout`
- `QHBoxLayout *viewLayout`
- `QVBoxLayout *widgetLayout`
- `QLabel *titleLabel`
- `QLabel *contentLabel`
- `IconWidgetForFlyout *iconWidget`
- `ImageLabel *imageLabel`
- `TransparentToolButton *closeButton`

**Signals / 信号**
- `void closed()`

#### Flyout

- **Declaration / 声明**: `class Flyout : public QWidget{`
- **Inherits / 继承**: `public QWidget`

**Public Members / 公有成员**
- `Flyout(FlyoutViewBase *view, QWidget *parent, bool isDeleteOnClose)`
- `void setShadowEffect(int blurRadius, std::tuple<int,int> offset)`
- `void closeEvent(QCloseEvent *event) override`
- `virtual void exec(QPoint pos, FlyoutAnimationType aniType)`
- `static Flyout* make(FlyoutViewBase *view, QVariant target, QWidget *parent, FlyoutAnimationType aniType, bool isDeleteOnClose)`
- `static Flyout* create(QString title, QString content, QVariant *icon, QVariant *image, bool isClosable, QVariant target, QWidget *parent, FlyoutAnimationType aniType, bool isDeleteOnClose)`
- `void fadeOut()`
- `FlyoutViewBase *view`
- `QHBoxLayout *hBoxLayout`
- `FlyoutAnimationManager *aniManger`
- `bool isDeleteOnClose`
- `QPropertyAnimation *fadeOutAni`
- `QGraphicsDropShadowEffect *shadowEffect`

**Signals / 信号**
- `void closed()`

#### FlyoutAnimationManager

- **Declaration / 声明**: `class FlyoutAnimationManager : public QObject{`
- **Inherits / 继承**: `public QObject`

**Public Members / 公有成员**
- `FlyoutAnimationManager(Flyout *flyout)`
- `virtual void exec(QPoint pos)`
- `QPoint _adjustPosition(QPoint pos)`
- `virtual QPoint position(QWidget *target)`
- `static FlyoutAnimationManager* make(FlyoutAnimationType aniType, Flyout *flyout)`
- `QList<FlyoutAnimationManager*> managers`
- `Flyout *flyout`
- `QParallelAnimationGroup *aniGroup`
- `QPropertyAnimation *slideAni`
- `QPropertyAnimation *opacityAni`

#### PullUpFlyoutAnimationManager

- **Declaration / 声明**: `class PullUpFlyoutAnimationManager : public FlyoutAnimationManager{`
- **Inherits / 继承**: `public FlyoutAnimationManager`

**Public Members / 公有成员**
- `PullUpFlyoutAnimationManager(Flyout *flyout)`
- `QPoint position(QWidget *target) override`
- `void exec(QPoint pos) override`

#### DropDownFlyoutAnimationManager

- **Declaration / 声明**: `class DropDownFlyoutAnimationManager : public FlyoutAnimationManager{`
- **Inherits / 继承**: `public FlyoutAnimationManager`

**Public Members / 公有成员**
- `DropDownFlyoutAnimationManager(Flyout *flyout)`
- `QPoint position(QWidget *target) override`
- `void exec(QPoint pos) override`

#### SlideLeftFlyoutAnimationManager

- **Declaration / 声明**: `class SlideLeftFlyoutAnimationManager : public FlyoutAnimationManager{`
- **Inherits / 继承**: `public FlyoutAnimationManager`

**Public Members / 公有成员**
- `SlideLeftFlyoutAnimationManager(Flyout *flyout)`
- `QPoint position(QWidget *target) override`
- `void exec(QPoint pos) override`

#### SlideRightFlyoutAnimationManager

- **Declaration / 声明**: `class SlideRightFlyoutAnimationManager : public FlyoutAnimationManager{`
- **Inherits / 继承**: `public FlyoutAnimationManager`

**Public Members / 公有成员**
- `SlideRightFlyoutAnimationManager(Flyout *flyout)`
- `QPoint position(QWidget *target) override`
- `void exec(QPoint pos) override`

#### FadeInFlyoutAnimationManager

- **Declaration / 声明**: `class FadeInFlyoutAnimationManager : public FlyoutAnimationManager{`
- **Inherits / 继承**: `public FlyoutAnimationManager`

**Public Members / 公有成员**
- `FadeInFlyoutAnimationManager(Flyout *flyout)`
- `QPoint position(QWidget *target) override`
- `void exec(QPoint pos) override`

#### DummyFlyoutAnimationManager

- **Declaration / 声明**: `class DummyFlyoutAnimationManager : public FlyoutAnimationManager{`
- **Inherits / 继承**: `public FlyoutAnimationManager`

**Public Members / 公有成员**
- `DummyFlyoutAnimationManager(Flyout *flyout)`
- `QPoint position(QWidget *target) override`
- `void exec(QPoint pos) override`


### `widgets/icon_widget.h`

#### IconWidget

- **Declaration / 声明**: `class IconWidget : public QWidget{`
- **Inherits / 继承**: `public QWidget`

**Public Members / 公有成员**
- `IconWidget(QWidget *parent)`
- `IconWidget(QVariant *icon, QWidget *parent)`
- `IconWidget(FluentIcon icon, QWidget *parent)`
- `IconWidget(InfoBarIcon *icon, QWidget *parent)`
- `IconWidget(QIcon icon, QWidget *parent)`
- `IconWidget(QString icon, QWidget *parent)`
- `QIcon getIcon()`
- `void setIcon(QVariant *icon)`
- `void paintEvent(QPaintEvent *event) override`
- `QVariant *_icon`


### `widgets/info_badge.h`

#### InfoBadge

- **Declaration / 声明**: `class InfoBadge : public QLabel{`
- **Inherits / 继承**: `public QLabel`

**Public Members / 公有成员**
- `InfoBadge(QWidget *parent, QString level)`
- `InfoBadge(QString text, QWidget *parent, QString level)`
- `InfoBadge(int num, QWidget *parent, QString level)`
- `InfoBadge(float num, QWidget *parent, QString level)`
- `void setLevel(QString level)`
- `void setProperty(const char *name, QVariant *value)`
- `void setCustomBackgroundColor(QVariant *light, QVariant *dark)`
- `void paintEvent(QPaintEvent *e) override`
- `QColor _backgroundColor()`
- `static InfoBadge* make(QVariant *text, QWidget *parent, QString level, QWidget *target, InfoBadgePosition position)`
- `static InfoBadge* info(QVariant *text, QWidget *parent, QWidget *target, InfoBadgePosition postion)`
- `static InfoBadge* success(QVariant *text, QWidget *parent, QWidget *target, InfoBadgePosition postion)`
- `static InfoBadge* attension(QVariant *text, QWidget *parent, QWidget *target, InfoBadgePosition postion)`
- `static InfoBadge* warning(QVariant *text, QWidget *parent, QWidget *target, InfoBadgePosition postion)`
- `static InfoBadge* error(QVariant *text, QWidget *parent, QWidget *target, InfoBadgePosition postion)`
- `static InfoBadge* custom(QVariant *text, QColor light, QColor dark, QWidget *parent, QWidget *target, InfoBadgePosition postion)`
- `QString level`
- `QColor lightBackgroundColor`
- `QColor darkBackgroundColor`
- `InfoBadgeManager *manager`

#### DotInfoBadge

- **Declaration / 声明**: `class DotInfoBadge : public InfoBadge{`
- **Inherits / 继承**: `public InfoBadge`

**Public Members / 公有成员**
- `DotInfoBadge(QWidget *parent, QString level)`
- `void paintEvent(QPaintEvent *e) override`
- `static DotInfoBadge* make(QWidget *parent, QString level, QWidget *target, InfoBadgePosition position)`
- `static DotInfoBadge* info(QWidget *parent, QWidget *target, InfoBadgePosition position)`
- `static DotInfoBadge* success(QWidget *parent, QWidget *target, InfoBadgePosition position)`
- `static DotInfoBadge* attension(QWidget *parent, QWidget *target, InfoBadgePosition position)`
- `static DotInfoBadge* warning(QWidget *parent, QWidget *target, InfoBadgePosition position)`
- `static DotInfoBadge* error(QWidget *parent, QWidget *target, InfoBadgePosition position)`
- `static DotInfoBadge* custom(QColor light, QColor dark, QWidget *parent, QWidget *target, InfoBadgePosition position)`

#### IconInfoBadge

- **Declaration / 声明**: `class IconInfoBadge : public InfoBadge{`
- **Inherits / 继承**: `public InfoBadge`

**Public Members / 公有成员**
- `IconInfoBadge(QWidget *parent, QString level)`
- `IconInfoBadge(FluentIcon *icon, QWidget *parent, QString level)`
- `IconInfoBadge(QIcon *icon, QWidget *parent, QString level)`
- `void setIcon(QVariant *icon)`
- `QIcon icon()`
- `QSize iconSize()`
- `void setIconSize(QSize size)`
- `void paintEvent(QPaintEvent *e) override`
- `static IconInfoBadge* make(QVariant *icon, QWidget *parent, QString level, QWidget *target, InfoBadgePosition position)`
- `static IconInfoBadge* info(QVariant *icon, QWidget *parent, QWidget *target, InfoBadgePosition position)`
- `static IconInfoBadge* success(QVariant *icon, QWidget *parent, QWidget *target, InfoBadgePosition position)`
- `static IconInfoBadge* attension(QVariant *icon, QWidget *parent, QWidget *target, InfoBadgePosition position)`
- `static IconInfoBadge* warning(QVariant *icon, QWidget *parent, QWidget *target, InfoBadgePosition position)`
- `static IconInfoBadge* error(QVariant *icon, QWidget *parent, QWidget *target, InfoBadgePosition position)`
- `static IconInfoBadge* custom(QVariant *icon, QColor light, QColor dark, QWidget *parent, QWidget *target, InfoBadgePosition position)`
- `QVariant *_icon`
- `QSize _iconSize`

#### InfoBadgeManager

- **Declaration / 声明**: `class InfoBadgeManager : public QObject{`
- **Inherits / 继承**: `public QObject`

**Public Members / 公有成员**
- `InfoBadgeManager(QWidget *target, InfoBadge *badge)`
- `bool eventFilter(QObject *watched, QEvent *event) override`
- `static InfoBadgeManager *make(InfoBadgePosition postion, QWidget *target, InfoBadge *badge)`
- `virtual QPoint position()`
- `QWidget *target`
- `InfoBadge *badge`

#### NavigationItemInfoBadgeManager

- **Declaration / 声明**: `class NavigationItemInfoBadgeManager : public InfoBadgeManager{`
- **Inherits / 继承**: `public InfoBadgeManager`

**Public Members / 公有成员**
- `NavigationItemInfoBadgeManager(QWidget *target, InfoBadge *badge) : InfoBadgeManager(target, badge){}`
- `bool eventFilter(QObject *watched, QEvent *event) override`
- `QPoint position() override`

#### TopRightInfoBadgeManager

- **Declaration / 声明**: `class TopRightInfoBadgeManager : public InfoBadgeManager{`
- **Inherits / 继承**: `public InfoBadgeManager`

**Public Members / 公有成员**
- `TopRightInfoBadgeManager(QWidget *target, InfoBadge *badge) : InfoBadgeManager(target, badge){}`
- `QPoint position() override`

#### RightInfoBadgeManager

- **Declaration / 声明**: `class RightInfoBadgeManager : public InfoBadgeManager{`
- **Inherits / 继承**: `public InfoBadgeManager`

**Public Members / 公有成员**
- `RightInfoBadgeManager(QWidget *target, InfoBadge *badge) : InfoBadgeManager(target, badge){}`
- `QPoint position() override`

#### BottomRightInfoBadgeManager

- **Declaration / 声明**: `class BottomRightInfoBadgeManager : public InfoBadgeManager{`
- **Inherits / 继承**: `public InfoBadgeManager`

**Public Members / 公有成员**
- `BottomRightInfoBadgeManager(QWidget *target, InfoBadge *badge) : InfoBadgeManager(target, badge){}`
- `QPoint position() override`

#### TopLeftInfoBadgeManager

- **Declaration / 声明**: `class TopLeftInfoBadgeManager : public InfoBadgeManager{`
- **Inherits / 继承**: `public InfoBadgeManager`

**Public Members / 公有成员**
- `TopLeftInfoBadgeManager(QWidget *target, InfoBadge *badge) : InfoBadgeManager(target, badge){}`
- `QPoint position() override`

#### LeftInfoBadgeManager

- **Declaration / 声明**: `class LeftInfoBadgeManager : public InfoBadgeManager{`
- **Inherits / 继承**: `public InfoBadgeManager`

**Public Members / 公有成员**
- `LeftInfoBadgeManager(QWidget *target, InfoBadge *badge) : InfoBadgeManager(target, badge){}`
- `QPoint position() override`

#### BottomLeftInfoBadgeManager

- **Declaration / 声明**: `class BottomLeftInfoBadgeManager : public InfoBadgeManager{`
- **Inherits / 继承**: `public InfoBadgeManager`

**Public Members / 公有成员**
- `BottomLeftInfoBadgeManager(QWidget *target, InfoBadge *badge) : InfoBadgeManager(target, badge){}`
- `QPoint position() override`


### `widgets/info_bar.h`

#### InfoIconWidget

- **Declaration / 声明**: `class InfoIconWidget : public QWidget{`
- **Inherits / 继承**: `public QWidget`

**Public Members / 公有成员**
- `InfoIconWidget(InfoBarIcon *icon, QWidget *parent)`
- `void paintEvent(QPaintEvent *event) override`
- `InfoBarIcon *icon`

#### InfoBar

- **Declaration / 声明**: `class InfoBar : public QFrame{`
- **Inherits / 继承**: `public QFrame`

**Public Members / 公有成员**
- `InfoBar(InfoBarIcon *icon, QString title, QString content, Qt::Orientation orient, bool isClosable, int duration, InfoBarPosition position, QWidget *parent)`
- `void __initWidget()`
- `void __initLayout()`
- `void __setQss()`
- `void __fadeOut()`
- `void _adjustText()`
- `void addWidget(QWidget *widget, int stretch)`
- `void setCustomBackgroundColor(QVariant light, QVariant dark)`
- `bool eventFilter(QObject *obj, QEvent *e) override`
- `void closeEvent(QCloseEvent *event) override`
- `void showEvent(QShowEvent *event) override`
- `void paintEvent(QPaintEvent *event) override`
- `static InfoBar* _new(InfoBarIcon *, QString title, QString content, Qt::Orientation orient, bool isCloseable, int duration, InfoBarPosition position, QWidget *parent)`
- `static InfoBar* success(QString title, QString content, Qt::Orientation orient, bool isClosable, int duration, InfoBarPosition position, QWidget *parent)`
- `static InfoBar* info(QString title, QString content, Qt::Orientation orient, bool isClosable, int duration, InfoBarPosition position, QWidget *parent)`
- `static InfoBar* warning(QString title, QString content, Qt::Orientation orient, bool isClosable, int duration, InfoBarPosition position, QWidget *parent)`
- `static InfoBar* error(QString title, QString content, Qt::Orientation orient, bool isClosable, int duration, InfoBarPosition position, QWidget *parent)`
- `QString title`
- `QString content`
- `Qt::Orientation orient`
- `InfoBarIcon *icon`
- `int duration`
- `bool isClosable`
- `InfoBarPosition position`
- `QLabel *titleLabel`
- `QLabel *contentLabel`
- `TransparentToolButton *closeButton`
- `InfoIconWidget *iconWidget`
- `QHBoxLayout *hBoxLayout`
- `QBoxLayout *textLayout`
- `QBoxLayout *widgetLayout`
- `QGraphicsOpacityEffect *opacityEffect`
- `QPropertyAnimation *opacityAni`
- `QColor lightBackgroundColor`
- `QColor darkBackgroundColor`

**Signals / 信号**
- `void closedSignal()`

#### InfoBarManager

- **Declaration / 声明**: `class InfoBarManager : public QObject{`
- **Inherits / 继承**: `public QObject`

**Public Members / 公有成员**
- `InfoBarManager()`
- `void add(InfoBar *infoBar)`
- `void remove(InfoBar *infoBar)`
- `QPropertyAnimation *_createSlideAni(InfoBar *infoBar)`
- `void _updateDropAni(QObject *parent)`
- `virtual QPoint _pos(InfoBar *infoBar, QSize parentSize)`
- `virtual QPoint _slideStartPos(InfoBar *infoBar)`
- `bool eventFilter(QObject *obj, QEvent *e) override`
- `static InfoBarManager *make(InfoBarPosition position)`
- `int spacing`
- `int margin`
- `QMap<QObject*, QList<InfoBar*>*> infoBars`
- `QMap<QObject*, QParallelAnimationGroup*> aniGroups`
- `QList<QPropertyAnimation*> slideAnis`
- `QList<QPropertyAnimation*> dropAnis`
- `bool __initialized`

#### TopInfoBarManager

- **Declaration / 声明**: `class TopInfoBarManager : public InfoBarManager{`
- **Inherits / 继承**: `public InfoBarManager`

**Public Members / 公有成员**
- `TopInfoBarManager()`
- `QPoint _pos(InfoBar *infoBar, QSize parentSize) override`
- `QPoint _slideStartPos(InfoBar *infoBar) override`

#### TopRightInfoBarManager

- **Declaration / 声明**: `class TopRightInfoBarManager : public InfoBarManager{`
- **Inherits / 继承**: `public InfoBarManager`

**Public Members / 公有成员**
- `TopRightInfoBarManager()`
- `QPoint _pos(InfoBar *infoBar, QSize parentSize) override`
- `QPoint _slideStartPos(InfoBar *infoBar) override`

#### BottomRightInfoBarManager

- **Declaration / 声明**: `class BottomRightInfoBarManager : public InfoBarManager{`
- **Inherits / 继承**: `public InfoBarManager`

**Public Members / 公有成员**
- `BottomRightInfoBarManager()`
- `QPoint _pos(InfoBar *infoBar, QSize parentSize) override`
- `QPoint _slideStartPos(InfoBar *infoBar) override`

#### TopLeftInfoBarManager

- **Declaration / 声明**: `class TopLeftInfoBarManager : public InfoBarManager{`
- **Inherits / 继承**: `public InfoBarManager`

**Public Members / 公有成员**
- `TopLeftInfoBarManager()`
- `QPoint _pos(InfoBar *infoBar, QSize parentSize) override`
- `QPoint _slideStartPos(InfoBar *infoBar) override`

#### BottomLeftInfoBarManager

- **Declaration / 声明**: `class BottomLeftInfoBarManager : public InfoBarManager{`
- **Inherits / 继承**: `public InfoBarManager`

**Public Members / 公有成员**
- `BottomLeftInfoBarManager()`
- `QPoint _pos(InfoBar *infoBar, QSize parentSize) override`
- `QPoint _slideStartPos(InfoBar *infoBar) override`

#### BottomInfoBarManager

- **Declaration / 声明**: `class BottomInfoBarManager : public InfoBarManager{`
- **Inherits / 继承**: `public InfoBarManager`

**Public Members / 公有成员**
- `BottomInfoBarManager()`
- `QPoint _pos(InfoBar *infoBar, QSize parentSize) override`
- `QPoint _slideStartPos(InfoBar *infoBar) override`


### `widgets/label.h`

#### PixmapLabel

- **Declaration / 声明**: `class PixmapLabel : public QLabel{`
- **Inherits / 继承**: `public QLabel`

**Public Members / 公有成员**
- `PixmapLabel(QWidget *parent)`
- `void setPixmap(QPixmap *pixmap)`
- `QPixmap *pixmap()`
- `void paintEvent(QPaintEvent *e)`
- `QPixmap *__pixmap`

#### FluentLabelBase

- **Declaration / 声明**: `class FluentLabelBase : public QLabel{`
- **Inherits / 继承**: `public QLabel`

**Public Members / 公有成员**
- `FluentLabelBase(QWidget *parent)`
- `FluentLabelBase(QString text, QWidget *parent)`
- `void _init()`
- `virtual QFont getFont(){}`
- `void setTextColor(QColor light, QColor dark)`
- `QColor getLightColor()`
- `void setLightColor(QColor color)`
- `QColor getDarkColor()`
- `void setDarkColor(QColor color)`
- `int getPixelFontSize()`
- `void setPixelFontSize(int size)`
- `bool getStrikeOut()`
- `void setStrikeOut(bool isStrikeOut)`
- `bool getUnderline()`
- `void setUnderline(bool isUnderline)`
- `QColor _lightColor`
- `QColor _darkColor`

#### CaptionLabel

- **Declaration / 声明**: `class CaptionLabel : public FluentLabelBase{`
- **Inherits / 继承**: `public FluentLabelBase`

**Public Members / 公有成员**
- `CaptionLabel(QWidget *parent)`
- `CaptionLabel(QString text, QWidget *parent)`
- `QFont getFont() override`

#### BodyLabel

- **Declaration / 声明**: `class BodyLabel : public FluentLabelBase{`
- **Inherits / 继承**: `public FluentLabelBase`

**Public Members / 公有成员**
- `BodyLabel(QWidget *parent)`
- `BodyLabel(QString text, QWidget *parent = nullptr)`
- `QFont getFont() override`

#### StrongBodyLabel

- **Declaration / 声明**: `class StrongBodyLabel : public FluentLabelBase{`
- **Inherits / 继承**: `public FluentLabelBase`

**Public Members / 公有成员**
- `StrongBodyLabel(QWidget *parent)`
- `StrongBodyLabel(QString text, QWidget *parent)`
- `QFont getFont() override`

#### SubtitleLabel

- **Declaration / 声明**: `class SubtitleLabel : public FluentLabelBase{`
- **Inherits / 继承**: `public FluentLabelBase`

**Public Members / 公有成员**
- `SubtitleLabel(QWidget *parent)`
- `SubtitleLabel(QString text, QWidget *parent)`
- `QFont getFont() override`

#### TitleLabel

- **Declaration / 声明**: `class TitleLabel : public FluentLabelBase{`
- **Inherits / 继承**: `public FluentLabelBase`

**Public Members / 公有成员**
- `TitleLabel(QWidget *parent)`
- `TitleLabel(QString text, QWidget *parent)`
- `QFont getFont() override`

#### LargeTitleLabel

- **Declaration / 声明**: `class LargeTitleLabel : public FluentLabelBase{`
- **Inherits / 继承**: `public FluentLabelBase`

**Public Members / 公有成员**
- `LargeTitleLabel(QWidget *parent)`
- `LargeTitleLabel(QString text, QWidget *parent)`
- `QFont getFont() override`

#### DisplayLabel

- **Declaration / 声明**: `class DisplayLabel : public FluentLabelBase{`
- **Inherits / 继承**: `public FluentLabelBase`

**Public Members / 公有成员**
- `DisplayLabel(QWidget *parent)`
- `DisplayLabel(QString text, QWidget *parent)`
- `QFont getFont() override`

#### ImageLabel

- **Declaration / 声明**: `class ImageLabel : public QLabel{`
- **Inherits / 继承**: `public QLabel`

**Public Members / 公有成员**
- `ImageLabel(QWidget *parent)`
- `ImageLabel(QString image, QWidget *parent)`
- `ImageLabel(QImage image, QWidget *parent)`
- `ImageLabel(QPixmap image, QWidget *parent)`
- `virtual void _postInit(){}`
- `void setBorderRadius(int topLeft, int topRight, int bottomLeft, int bottomRight)`
- `void setImage(QVariant *image)`
- `void scaledToWidth(int width)`
- `void scaledToHeight(int height)`
- `bool isNull()`
- `void mouseReleaseEvent(QMouseEvent *event) override`
- `void setPixmap(QPixmap pixmap)`
- `QPixmap pixmap()`
- `void setMovie(QMovie *movie)`
- `void paintEvent(QPaintEvent *e) override`
- `int getTopLeftRadius()`
- `void setTopLeftRadius(int radius)`
- `int getTopRightRadius()`
- `void setTopRightRadius(int radius)`
- `int getBottomLeftRadius()`
- `void setBottomLeftRadius(int radius)`
- `int getBottomRightRadius()`
- `void setBottomRightRadius(int radius)`
- `QImage image`
- `int _topLeftRadius`
- `int _topRightRadius`
- `int _bottomLeftRadius`
- `int _bottomRightRadius`

**Signals / 信号**
- `void clicked()`

**Public Slots / 公共槽函数**
- `void _onFrameChanged(int index)`

#### AvatarWidget

- **Declaration / 声明**: `class AvatarWidget : public ImageLabel{`
- **Inherits / 继承**: `public ImageLabel`

**Properties / 属性**
- `Q_PROPERTY(int radius READ getRadius WRITE setRadius)`

**Public Members / 公有成员**
- `AvatarWidget(QWidget *parent) : ImageLabel(parent){}`
- `AvatarWidget(QString image, QWidget *parent) : ImageLabel(image, parent){}`
- `AvatarWidget(QImage image, QWidget *parent) : ImageLabel(image, parent){}`
- `AvatarWidget(QPixmap image, QWidget *parent) : ImageLabel(image, parent){}`
- `void _postInit() override`
- `int getRadius()`
- `void setRadius(int radius)`
- `void paintEvent(QPaintEvent *e) override`
- `int _radius`

#### HyperlinkLabel

- **Declaration / 声明**: `class HyperlinkLabel : public QPushButton{`
- **Inherits / 继承**: `public QPushButton`

**Properties / 属性**
- `Q_PROPERTY(QUrl url READ getUrl WRITE setUrl)`
- `Q_PROPERTY(bool underlineVisible READ isUnderlineVisible WRITE setUnderlineVisible)`

**Public Members / 公有成员**
- `HyperlinkLabel(QWidget *parent)`
- `HyperlinkLabel(QString text, QWidget *parent)`
- `HyperlinkLabel(QUrl url, QString text, QWidget *parent)`
- `QUrl getUrl()`
- `void setUrl(QVariant url)`
- `bool isUnderlineVisible()`
- `void setUnderlineVisible(bool isVisible)`
- `QUrl _url`
- `bool _isUnderlineVisible`

**Public Slots / 公共槽函数**
- `void _onClicked()`


### `widgets/line_edit.h`

#### LineEditButton

- **Declaration / 声明**: `class LineEditButton : public QToolButton{`
- **Inherits / 继承**: `public QToolButton`

**Public Members / 公有成员**
- `LineEditButton(QVariant *icon, QWidget *parent)`
- `void mousePressEvent(QMouseEvent *e)`
- `void mouseReleaseEvent(QMouseEvent *e)`
- `void paintEvent(QPaintEvent *e)`
- `QVariant *_icon`
- `bool isPressed`
- `CompleterMenu *_completerMenu`

#### LineEdit

- **Declaration / 声明**: `class LineEdit : public QLineEdit{`
- **Inherits / 继承**: `public QLineEdit`

**Public Members / 公有成员**
- `LineEdit(QWidget *parent)`
- `void setClearButtonEnabled(bool enable)`
- `bool isClearButtonEnabled()`
- `virtual void setCompleter(QCompleter *completer)`
- `QCompleter *completer()`
- `void focusOutEvent(QFocusEvent *e)`
- `void focusInEvent(QFocusEvent *e)`
- `void setCompleterMenu(CompleterMenu *menu)`
- `void _showCompleterMenu()`
- `void contextMenuEvent(QContextMenuEvent *e) override`
- `void paintEvent(QPaintEvent *e)`
- `bool _isClearButtonEnabled`
- `CompleterMenu *_completerMenu`
- `QCompleter *_completer`
- `QHBoxLayout *hBoxLayout`
- `LineEditButton *clearButton`

**Public Slots / 公共槽函数**
- `void __onTextChanged(QString text)`
- `void __onTextEdited(QString text)`

#### CompleterMenu

- **Declaration / 声明**: `class CompleterMenu : public RoundMenu{`
- **Inherits / 继承**: `public RoundMenu`

**Public Members / 公有成员**
- `CompleterMenu(LineEdit *lineEdit)`
- `bool setCompletion(QAbstractItemModel *model)`
- `void setItems(QStringList *items)`
- `bool eventFilter(QObject *watched, QEvent *event)`
- `void __onItemSelected(QString text)`
- `bool popup()`
- `QStringList *items`
- `LineEdit *lineEdit`

**Signals / 信号**
- `void activated(const QString &text)`

**Public Slots / 公共槽函数**
- `void _onItemClicked(QListWidgetItem *item)`

#### SearchLineEdit

- **Declaration / 声明**: `class SearchLineEdit : public LineEdit{`
- **Inherits / 继承**: `public LineEdit`

**Public Members / 公有成员**
- `SearchLineEdit(QWidget *parent)`
- `void search()`
- `void setClearButtonEnabled(bool enable)`
- `LineEditButton *searchButton`

**Signals / 信号**
- `void searchSignal(QString)`
- `void clearSignal()`

#### EditLayer

- **Declaration / 声明**: `class EditLayer : public QWidget{`
- **Inherits / 继承**: `public QWidget`

**Public Members / 公有成员**
- `EditLayer(QWidget *parent)`
- `bool eventFilter(QObject *watched, QEvent *event)`
- `void paintEvent(QPaintEvent *event)`

#### TextEdit

- **Declaration / 声明**: `class TextEdit : public QTextEdit{`
- **Inherits / 继承**: `public QTextEdit`

**Public Members / 公有成员**
- `TextEdit(QWidget *parent)`
- `void contextMenuEvent(QContextMenuEvent *e)`
- `SmoothScrollDelegate *scrollDelegate`
- `EditLayer *layer`

#### PlainTextEdit

- **Declaration / 声明**: `class PlainTextEdit : public QPlainTextEdit{`
- **Inherits / 继承**: `public QPlainTextEdit`

**Public Members / 公有成员**
- `PlainTextEdit(QWidget *parent)`
- `void contextMenuEvent(QContextMenuEvent *e)`
- `SmoothScrollDelegate *scrollDelegate`
- `EditLayer *layer`

#### PasswordLineEdit

- **Declaration / 声明**: `class PasswordLineEdit : public LineEdit{`
- **Inherits / 继承**: `public LineEdit`

**Public Members / 公有成员**
- `PasswordLineEdit(QWidget *parent)`
- `void setPasswordVisible(bool isVisible)`
- `bool isPasswordVisible()`
- `void setClearButtonEnabled(bool enable)`
- `void setViewPasswordButtonVisible(bool isVisible)`
- `bool eventFilter(QObject *watched, QEvent *event)`
- `LineEditButton *viewButton`


### `widgets/list_view.h`

#### ListItemDelegate

- **Declaration / 声明**: `class ListItemDelegate : public QStyledItemDelegate{`
- **Inherits / 继承**: `public QStyledItemDelegate`

**Public Members / 公有成员**
- `ListItemDelegate(QListView *parent)`
- `void setHoverRow(int row)`
- `void setPressedRow(int row)`
- `void setSelectedRows(QList<QModelIndex> indexes)`
- `QSize sizeHint(QStyleOptionViewItem *option, QModelIndex *index)`
- `QWidget *createEditor(QWidget *parent, QStyleOptionViewItem *option, QModelIndex *index)`
- `void updateEditorGeometry(QWidget *editor, QStyleOptionViewItem *option, QModelIndex *index)`
- `virtual void _drawbackground(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const`
- `virtual void _drawIndicator(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const`
- `void initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const override`
- `void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override`
- `int margin`
- `int hoverRow`
- `int pressedRow`
- `QList<int> selectedRows`

#### ListWidget

- **Declaration / 声明**: `class ListWidget : public QListWidget{`
- **Inherits / 继承**: `public QListWidget`

**Properties / 属性**
- `Q_PROPERTY(bool selectRightClickedRow READ isSelectRightClickedRow WRITE setSelectRightClickedRow)`

**Public Members / 公有成员**
- `ListWidget(QWidget *parent)`
- `void _setHoverRow(int row)`
- `void _setPressedRow(int row)`
- `void _setSelectedRows(QList<QModelIndex> indexes)`
- `void leaveEvent(QEvent *event) override`
- `void resizeEvent(QResizeEvent *event) override`
- `void keyPressEvent(QKeyEvent *e) override`
- `void mousePressEvent(QMouseEvent *e) override`
- `void mouseReleaseEvent(QMouseEvent *e) override`
- `void setItemDelegate(ListItemDelegate *delegate)`
- `void clearSelection()`
- `void setCurrentIndex(QModelIndex index)`
- `void updateSelectedRows()`
- `void setCurrentItem(QListWidgetItem *item, QItemSelectionModel::SelectionFlag command)`
- `void setCurrentItem(QListWidgetItem *item, QItemSelectionModel::SelectionFlags command)`
- `void setCurrentRow(int row, QItemSelectionModel::SelectionFlag command)`
- `void setCurrentRow(int row, QItemSelectionModel::SelectionFlags command)`
- `bool isSelectRightClickedRow()`
- `void setSelectRightClickedRow(bool isSelect)`
- `ListItemDelegate *delegate`
- `SmoothScrollDelegate *scrollDelegate`
- `bool _isSelectRightClickedRow`

#### ListView

- **Declaration / 声明**: `class ListView : public QListView{`
- **Inherits / 继承**: `public QListView`

**Properties / 属性**
- `Q_PROPERTY(bool selectRightClickedRow READ isSelectRightClickedRow WRITE setSelectRightClickedRow)`

**Public Members / 公有成员**
- `ListView(QWidget *parent)`
- `void _setHoverRow(int row)`
- `void _setPressedRow(int row)`
- `void _setSelectedRows(QList<QModelIndex> indexes)`
- `void leaveEvent(QEvent *event) override`
- `void resizeEvent(QResizeEvent *event) override`
- `void keyPressEvent(QKeyEvent *e) override`
- `void mousePressEvent(QMouseEvent *e) override`
- `void mouseReleaseEvent(QMouseEvent *e) override`
- `void setItemDelegate(ListItemDelegate *delegate)`
- `void clearSelection()`
- `void setCurrentIndex(QModelIndex index)`
- `void updateSelectedRows()`
- `bool isSelectRightClickedRow()`
- `void setSelectRightClickedRow(bool isSelect)`
- `ListItemDelegate *delegate`
- `SmoothScrollDelegate *scrollDelegate`
- `bool _isSelectRightClickedRow`


### `widgets/menu.h`

#### SlotForwarder

- **Declaration / 声明**: `class SlotForwarder : public QObject {`
- **Inherits / 继承**: `public QObject`

**Public Members / 公有成员**
- `typedef void (*Function)()`
- `SlotForwarder(Function function, QObject* parent = 0) : QObject(parent) , m_fptr(function) {}`

**Public Slots / 公共槽函数**
- `void forward() { m_fptr()`

**Private Members / 私有成员**
- `Function m_fptr`

#### CustomMenuStyle

- **Declaration / 声明**: `class CustomMenuStyle : public QProxyStyle{`
- **Inherits / 继承**: `public QProxyStyle`

**Public Members / 公有成员**
- `CustomMenuStyle(int iconSize)`
- `int pixelMetric(PixelMetric metric, QStyleOption *option, QWidget *widget)`
- `int iconSize`

#### DWMMenu

- **Declaration / 声明**: `class DWMMenu : public QMenu{`
- **Inherits / 继承**: `public QMenu`

**Public Members / 公有成员**
- `DWMMenu(QString title, QWidget *parent)`
- `bool event(QEvent *e)`
- `WindowsWindowEffect *windowEffect`

#### SubMenuItemWidget

- **Declaration / 声明**: `class SubMenuItemWidget : public QWidget{`
- **Inherits / 继承**: `public QWidget`

**Public Members / 公有成员**
- `SubMenuItemWidget(QMenu *menu, QListWidgetItem *item, QWidget *parent)`
- `void enterEvent(QEvent *event)`
- `void paintEvent(QPaintEvent *event)`
- `QMenu *menu`
- `QListWidgetItem *item`

**Signals / 信号**
- `void showMenuSig(QListWidgetItem *)`

#### MenuItemDelegate

- **Declaration / 声明**: `class MenuItemDelegate : public QStyledItemDelegate{`
- **Inherits / 继承**: `public QStyledItemDelegate`

**Public Members / 公有成员**
- `MenuItemDelegate(QObject *parent) : QStyledItemDelegate(parent){}`
- `bool _isSeparator(QModelIndex index) const`
- `void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override`

#### ShortcutMenuItemDelegate

- **Declaration / 声明**: `class ShortcutMenuItemDelegate : public MenuItemDelegate{`
- **Inherits / 继承**: `public MenuItemDelegate`

**Public Members / 公有成员**
- `ShortcutMenuItemDelegate(QObject *parent) : MenuItemDelegate(parent){}`
- `void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override`

#### MenuActionListWidget

- **Declaration / 声明**: `class MenuActionListWidget : public QListWidget{`
- **Inherits / 继承**: `public QListWidget`

**Public Members / 公有成员**
- `MenuActionListWidget(QWidget *parent)`
- `void insertItem(int row, QListWidgetItem *item)`
- `void addItem(QListWidgetItem *item)`
- `QListWidgetItem *takeItem(int row)`
- `void adjustSize(QPoint *pos, MenuAnimationType aniType)`
- `void setItemHeight(int height)`
- `void setMaxVisibleItems(int num)`
- `QMargins getPublicViewportMargins()`
- `void publicSetViewportMargins(int left, int top, int right, int bottom)`
- `bool publicEvent(QEvent *e)`
- `bool event(QEvent *e) override`
- `int maxVisibleItems()`
- `int heightForAnimation(QPoint *pos, MenuAnimationType aniType)`
- `int itemsHeight()`
- `int _itemHeight`
- `int _maxVisibleItems`
- `SmoothScrollDelegate *scrollDelegate`

#### RoundMenu

- **Declaration / 声明**: `class RoundMenu : public QMenu{`
- **Inherits / 继承**: `public QMenu`

**Public Members / 公有成员**
- `RoundMenu(QString title, QWidget *parent)`
- `void __initWidgets()`
- `void setMaxVisibleItems(int num)`
- `void setItemHeight(int height)`
- `void setShadowEffect(int blurRadius, std::tuple<int, int> offset, QColor *color)`
- `void _setParentMenu(RoundMenu *parent, QListWidgetItem *item)`
- `void adjustSize()`
- `QVariant *icon()`
- `QString title()`
- `void clear()`
- `void setIcon(QVariant *icon)`
- `void addAction(QAction *action)`
- `void addWidget(QWidget *widget, bool selectable, SlotForwarder *onClick)`
- `QListWidgetItem *_createActionItem(QAction *action, QAction *before)`
- `bool _hasItemIcon()`
- `virtual int _adjustItemText(QListWidgetItem *item, QAction *action)`
- `int _longestShortcutWidth()`
- `QIcon *_createItemIcon(QVariant *w)`
- `void insertAction(QAction *before, QAction *action)`
- `void addActions(QList<QAction *> *actions)`
- `void insertActions(QAction *before, QList<QAction *> *actions)`
- `void removeAction(QAction *action)`
- `void setDefaultAction(QAction *action)`
- `void addMenu(RoundMenu *menu)`
- `void insertMenu(QAction *before, RoundMenu *menu)`
- `std::tuple<QListWidgetItem *, SubMenuItemWidget*> _createSubMenuItem(RoundMenu *menu)`
- `QAction *addSeparator()`
- `void _closeParentMenu()`
- `void _hideMenu(bool isHideBySystem)`
- `void hideEvent(QHideEvent *e)`
- `void closeEvent(QCloseEvent *e)`
- `QList<QAction *> *menuActions()`
- `void mousePressEvent(QMouseEvent *e)`
- `void mouseMoveEvent(QMouseEvent *e)`
- `virtual void exec(QPoint *pos, bool ani, MenuAnimationType aniType)`
- `void exec_(QPoint *pos, bool ani, MenuAnimationType aniType)`
- `void adjustPosition()`
- `void paintEvent(QPaintEvent *e)`
- `void cut(){}`
- `void copy(){}`
- `void paste(){}`
- `void undo(){}`
- `void selectAll(){}`
- `QString _title`
- `QVariant *_icon`
- `QList<QAction *> *_actions`
- `QList<RoundMenu *> *_subMenus`
- `bool isSubMenu`
- `RoundMenu *parentMenu`
- `QListWidgetItem *menuItem`
- `QListWidgetItem *lastHoverItem`
- `QListWidgetItem *lastHoverSubMenuItem`
- `bool isHideBySystem`
- `int itemHeight`
- `QHBoxLayout *hBoxLayout`
- `MenuActionListWidget *view`
- `MenuAnimationManager *aniManager`
- `QTimer *timer`
- `QGraphicsDropShadowEffect *shadowEffect`
- `FluentIconEngine *fie`

**Signals / 信号**
- `void closedSignal()`

**Public Slots / 公共槽函数**
- `void _showSubMenu(QListWidgetItem *item)`
- `void _onActionChanged()`
- `virtual void _onItemClicked(QListWidgetItem *item)`
- `void _onItemEntered(QListWidgetItem *item)`
- `void _onShowMenuTimeOut()`

#### MenuAnimationManager

- **Declaration / 声明**: `class MenuAnimationManager : public QObject{`
- **Inherits / 继承**: `public QObject`

**Public Members / 公有成员**
- `MenuAnimationManager() : QObject(){}`
- `MenuAnimationManager(RoundMenu *menu)`
- `virtual std::tuple<int, int> availableViewSize(QPoint *pos)`
- `virtual QPoint *_endPosition(QPoint *pos)`
- `virtual std::tuple<int, int> _menuSize()`
- `virtual void exec(QPoint *pos){}`
- `MenuAnimationManager *make(MenuAnimationType aniType, RoundMenu *menu)`
- `QMap<MenuAnimationType, QString> *managers`
- `RoundMenu *menu`
- `QPropertyAnimation *ani`

**Public Slots / 公共槽函数**
- `virtual void _onValueChanged(){}`
- `virtual void _updateMenuViewport()`

#### DummyMenuAnimationManager

- **Declaration / 声明**: `class DummyMenuAnimationManager : public MenuAnimationManager{`
- **Inherits / 继承**: `public MenuAnimationManager`

**Public Members / 公有成员**
- `DummyMenuAnimationManager(RoundMenu *menu) : MenuAnimationManager(menu){}`
- `void exec(QPoint *pos) override`

#### DropDownMenuAnimationManager

- **Declaration / 声明**: `class DropDownMenuAnimationManager : public MenuAnimationManager{`
- **Inherits / 继承**: `public MenuAnimationManager`

**Public Members / 公有成员**
- `DropDownMenuAnimationManager(RoundMenu *menu) : MenuAnimationManager(menu){}`
- `void exec(QPoint *pos) override`
- `std::tuple<int, int> availableViewSize(QPoint *pos) override`

**Public Slots / 公共槽函数**
- `void _onValueChanged() override`

#### PullUpMenuAnimationManager

- **Declaration / 声明**: `class PullUpMenuAnimationManager : public MenuAnimationManager{`
- **Inherits / 继承**: `public MenuAnimationManager`

**Public Members / 公有成员**
- `PullUpMenuAnimationManager(RoundMenu *menu) : MenuAnimationManager(menu){} void exec(QPoint *pos) override`
- `std::tuple<int, int> availableViewSize(QPoint *pos) override`
- `QPoint *_endPosition(QPoint *pos) override`

**Public Slots / 公共槽函数**
- `void _onValueChanged() override`

#### FadeInDropDownMenuAnimationManager

- **Declaration / 声明**: `class FadeInDropDownMenuAnimationManager : public MenuAnimationManager{`
- **Inherits / 继承**: `public MenuAnimationManager`

**Public Members / 公有成员**
- `FadeInDropDownMenuAnimationManager(RoundMenu *menu)`
- `void exec(QPoint *pos) override`
- `std::tuple<int, int> availableViewSize(QPoint *pos) override`
- `QPropertyAnimation *opacityAni`
- `QParallelAnimationGroup *aniGroup`

#### FadeInPullUpMenuAnimationManager

- **Declaration / 声明**: `class FadeInPullUpMenuAnimationManager : public MenuAnimationManager{`
- **Inherits / 继承**: `public MenuAnimationManager`

**Public Members / 公有成员**
- `FadeInPullUpMenuAnimationManager(RoundMenu *menu)`
- `void exec(QPoint *pos) override`
- `std::tuple<int, int> availableViewSize(QPoint *pos) override`
- `QPoint *_endPosition(QPoint *pos) override`
- `QPropertyAnimation *opacityAni`
- `QParallelAnimationGroup *aniGroup`

#### MenuActionListAnimationManager

- **Declaration / 声明**: `class MenuActionListAnimationManager : public QObject{`
- **Inherits / 继承**: `public QObject`

**Public Members / 公有成员**
- `MenuActionListAnimationManager() : QObject(){}`
- `MenuActionListAnimationManager(MenuActionListWidget *menu)`
- `virtual std::tuple<int, int> availableViewSize(QPoint *pos)`
- `virtual QPoint *_endPosition(QPoint *pos)`
- `virtual void exec(QPoint *pos){}`
- `MenuActionListAnimationManager *make(MenuAnimationType aniType, MenuActionListWidget *menu)`
- `QMap<MenuAnimationType, QString> *managers`
- `MenuActionListWidget *menu`
- `QPropertyAnimation *ani`

#### DummyMenuActionListAnimationManager

- **Declaration / 声明**: `class DummyMenuActionListAnimationManager : public MenuActionListAnimationManager{`
- **Inherits / 继承**: `public MenuActionListAnimationManager`

**Public Members / 公有成员**
- `DummyMenuActionListAnimationManager(MenuActionListWidget *menu) : MenuActionListAnimationManager(menu){}`
- `void exec(QPoint *pos) override`

#### DropDownMenuActionListAnimationManager

- **Declaration / 声明**: `class DropDownMenuActionListAnimationManager : public MenuActionListAnimationManager{`
- **Inherits / 继承**: `public MenuActionListAnimationManager`

**Public Members / 公有成员**
- `DropDownMenuActionListAnimationManager(MenuActionListWidget *menu) : MenuActionListAnimationManager(menu){}`
- `void exec(QPoint *pos) override`
- `std::tuple<int, int> availableViewSize(QPoint *pos) override`

#### PullUpMenuActionListAnimationManager

- **Declaration / 声明**: `class PullUpMenuActionListAnimationManager : public MenuActionListAnimationManager{`
- **Inherits / 继承**: `public MenuActionListAnimationManager`

**Public Members / 公有成员**
- `PullUpMenuActionListAnimationManager(MenuActionListWidget *menu) : MenuActionListAnimationManager(menu){} void exec(QPoint *pos) override`
- `std::tuple<int, int> availableViewSize(QPoint *pos) override`
- `QPoint *_endPosition(QPoint *pos) override`

#### FadeInDropDownMenuActionListAnimationManager

- **Declaration / 声明**: `class FadeInDropDownMenuActionListAnimationManager : public MenuActionListAnimationManager{`
- **Inherits / 继承**: `public MenuActionListAnimationManager`

**Public Members / 公有成员**
- `FadeInDropDownMenuActionListAnimationManager(MenuActionListWidget *menu)`
- `void exec(QPoint *pos) override`
- `std::tuple<int, int> availableViewSize(QPoint *pos) override`
- `QPropertyAnimation *opacityAni`
- `QParallelAnimationGroup *aniGroup`

#### FadeInPullUpMenuActionListAnimationManager

- **Declaration / 声明**: `class FadeInPullUpMenuActionListAnimationManager : public MenuActionListAnimationManager{`
- **Inherits / 继承**: `public MenuActionListAnimationManager`

**Public Members / 公有成员**
- `FadeInPullUpMenuActionListAnimationManager(MenuActionListWidget *menu)`
- `void exec(QPoint *pos) override`
- `std::tuple<int, int> availableViewSize(QPoint *pos) override`
- `QPoint *_endPosition(QPoint *pos) override`
- `QPropertyAnimation *opacityAni`
- `QParallelAnimationGroup *aniGroup`

#### EditMenu

- **Declaration / 声明**: `class EditMenu : public RoundMenu{`
- **Inherits / 继承**: `public RoundMenu`

**Public Members / 公有成员**
- `EditMenu(QString title, QWidget *parent)`
- `void createActions()`
- `QString _parentText(){}`
- `QString _parentSelectedText(){}`
- `void exec(QPoint *pos, bool ani, MenuAnimationType aniType)`
- `QAction *cutAct`
- `QAction *copyAct`
- `QAction *pasteAct`
- `QAction *cancelAct`
- `QAction *selectAllAct`
- `QList<QAction *> *action_list`

#### LineEditMenu

- **Declaration / 声明**: `class LineEditMenu : public EditMenu{`
- **Inherits / 继承**: `public EditMenu`

**Public Members / 公有成员**
- `LineEditMenu(QLineEdit *parent)`
- `QString _parentText()`
- `QString _parentSelectedText()`
- `int selectionStart`
- `int selectionLength`

**Public Slots / 公共槽函数**
- `void _onItemClicked(QListWidgetItem *item)`

#### TextEditMenu

- **Declaration / 声明**: `class TextEditMenu : public EditMenu{`
- **Inherits / 继承**: `public EditMenu`

**Public Members / 公有成员**
- `TextEditMenu(QTextEdit *parent)`
- `QString _parentText()`
- `QString _parentSelectedText()`
- `int selectionStart`
- `int selectionLength`

**Public Slots / 公共槽函数**
- `void _onItemClicked(QListWidgetItem *item)`

#### TextEditMenu2QPlainTextEdit

- **Declaration / 声明**: `class TextEditMenu2QPlainTextEdit : public EditMenu{`
- **Inherits / 继承**: `public EditMenu`

**Public Members / 公有成员**
- `TextEditMenu2QPlainTextEdit(QPlainTextEdit *parent)`
- `QString _parentText()`
- `QString _parentSelectedText()`
- `int selectionStart`
- `int selectionLength`

**Public Slots / 公共槽函数**
- `void _onItemClicked(QListWidgetItem *item)`

#### IndicatorMenuItemDelegate

- **Declaration / 声明**: `class IndicatorMenuItemDelegate : public MenuItemDelegate{`
- **Inherits / 继承**: `public MenuItemDelegate`

**Public Members / 公有成员**
- `IndicatorMenuItemDelegate(QObject *parent) : MenuItemDelegate(parent){}`
- `void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override`

#### CheckableMenuItemDelegate

- **Declaration / 声明**: `class CheckableMenuItemDelegate : public ShortcutMenuItemDelegate{`
- **Inherits / 继承**: `public ShortcutMenuItemDelegate`

**Public Members / 公有成员**
- `CheckableMenuItemDelegate(QObject *parent) : ShortcutMenuItemDelegate(parent){}`
- `void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override`
- `virtual void _drawIndicator(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const{ }`

#### RadioIndicatorMenuItemDelegate

- **Declaration / 声明**: `class RadioIndicatorMenuItemDelegate : public CheckableMenuItemDelegate{`
- **Inherits / 继承**: `public CheckableMenuItemDelegate`

**Public Members / 公有成员**
- `RadioIndicatorMenuItemDelegate(QObject *parent) : CheckableMenuItemDelegate(parent){}`
- `void _drawIndicator(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override`

#### CheckIndicatorMenuItemDelegate

- **Declaration / 声明**: `class CheckIndicatorMenuItemDelegate : public CheckableMenuItemDelegate{`
- **Inherits / 继承**: `public CheckableMenuItemDelegate`

**Public Members / 公有成员**
- `CheckIndicatorMenuItemDelegate(QObject *parent) : CheckableMenuItemDelegate(parent){}`
- `void _drawIndicator(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override`

#### CheckableMenu

- **Declaration / 声明**: `class CheckableMenu : public RoundMenu{`
- **Inherits / 继承**: `public RoundMenu`

**Public Members / 公有成员**
- `CheckableMenu(QString title, QWidget *parent, MenuIndicatorType indicator)`
- `int _adjustItemText(QListWidgetItem *item, QAction *action) override`

#### SystemTrayMenu

- **Declaration / 声明**: `class SystemTrayMenu : public RoundMenu{`
- **Inherits / 继承**: `public RoundMenu`

**Public Members / 公有成员**
- `SystemTrayMenu(QString title, QWidget *parent) : RoundMenu(title, parent){}`
- `void showEvent(QShowEvent *event)`

#### CheckableSystemTrayMenu

- **Declaration / 声明**: `class CheckableSystemTrayMenu : public CheckableMenu{`
- **Inherits / 继承**: `public CheckableMenu`

**Public Members / 公有成员**
- `void showEvent(QShowEvent *event) override`


### `widgets/pips_pager.h`

#### PipPagerScrollButton

- **Declaration / 声明**: `class PipPagerScrollButton : public ToolButton{`
- **Inherits / 继承**: `public ToolButton`

**Public Members / 公有成员**
- `PipPagerScrollButton(QWidget *parent)`
- `PipPagerScrollButton(FluentIcon *icon, QWidget *parent)`
- `PipPagerScrollButton(SpinIcon *icon, QWidget *parent)`
- `PipPagerScrollButton(QIcon *icon, QWidget *parent)`
- `PipPagerScrollButton(QString icon, QWidget *parent)`
- `void _postInit()`
- `void paintEvent(QPaintEvent *event)`

#### PipsDelegate

- **Declaration / 声明**: `class PipsDelegate : public QStyledItemDelegate{`
- **Inherits / 继承**: `public QStyledItemDelegate`

**Public Members / 公有成员**
- `PipsDelegate(QWidget *parent)`
- `void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override`
- `void setPressedRow(int row)`
- `void setHoveredRow(int row)`
- `int hoveredRow`
- `int pressedRow`

#### PipsPager

- **Declaration / 声明**: `class PipsPager : public QListWidget{`
- **Inherits / 继承**: `public QListWidget`

**Properties / 属性**
- `Q_PROPERTY(int visibleNumber READ getVisibleNumber WRITE setVisibleNumber)`
- `Q_PROPERTY(int pageNumber READ getPageNumber WRITE setPageNumber)`

**Public Members / 公有成员**
- `PipsPager(QWidget *parent)`
- `PipsPager(Qt::Orientation orientation, QWidget *parent)`
- `void _postInit()`
- `void setPageNumber(int n)`
- `int getPageNumber()`
- `int getVisibleNumber()`
- `void setVisibleNumber(int n)`
- `void scrollToItem(QListWidgetItem *item, QListWidget::ScrollHint hint)`
- `void adjustSize()`
- `bool isHorizontal()`
- `void setCurrentIndex(int index)`
- `bool isPreviousButtonVisible()`
- `bool isNextButtonVisible()`
- `int currentIndex()`
- `void setPreviousButtonDisplayMode(PipsScrollButtonDisplayMode mode)`
- `void setNextButtonDisplayMode(PipsScrollButtonDisplayMode mode)`
- `void mouseReleaseEvent(QMouseEvent *e) override`
- `void enterEvent(QEvent *event) override`
- `void leaveEvent(QEvent *event) override`
- `void _updateScrollButtonVisibility()`
- `void wheelEvent(QWheelEvent *e) override`
- `void resizeEvent(QResizeEvent *event) override`
- `Qt::Orientation orientation`
- `int _visibleNumber`
- `bool isHover`
- `PipsDelegate *delegate`
- `SmoothScrollBar *scrollBar`
- `PipPagerScrollButton *preButton`
- `PipPagerScrollButton *nextButton`
- `PipsScrollButtonDisplayMode previousButtonDisplayMode`
- `PipsScrollButtonDisplayMode nextButtonDisplayMode`

**Signals / 信号**
- `void currentIndexChanged(int)`

**Public Slots / 公共槽函数**
- `void scrollNext()`
- `void scrollPrevious()`
- `void _setPressedItem(QListWidgetItem *item)`
- `void _setHoveredItem(QListWidgetItem *item)`

#### HorizontalPipsPager

- **Declaration / 声明**: `class HorizontalPipsPager : public PipsPager{`
- **Inherits / 继承**: `public PipsPager`

**Public Members / 公有成员**
- `HorizontalPipsPager(QWidget *parent)`

#### VerticalPipsPager

- **Declaration / 声明**: `class VerticalPipsPager : public PipsPager{`
- **Inherits / 继承**: `public PipsPager`

**Public Members / 公有成员**
- `VerticalPipsPager(QWidget *parent)`


### `widgets/progress_bar.h`

#### ProgressBar

- **Declaration / 声明**: `class ProgressBar : public QProgressBar{`
- **Inherits / 继承**: `public QProgressBar`

**Properties / 属性**
- `Q_PROPERTY(bool useAni READ isUseAni WRITE setUseAni)`
- `Q_PROPERTY(float val READ getVal WRITE setVal)`

**Public Members / 公有成员**
- `ProgressBar(QWidget *parent, bool useAni)`
- `float getVal()`
- `void setVal(float v)`
- `bool isUseAni()`
- `void setUseAni(bool isUse)`
- `QColor lightBarColor()`
- `QColor darkBarColor()`
- `void setCustomBarColor(QVariant *light, QVariant *dark)`
- `void setCustomBackgroundColor(QVariant *light, QVariant *dark)`
- `void resume()`
- `void pause()`
- `void setPaused(bool isPaused)`
- `bool isPaused()`
- `void error()`
- `void setError(bool isError)`
- `bool isError()`
- `QColor barColor()`
- `QString valText()`
- `void paintEvent(QPaintEvent *e) override`
- `float _val`
- `bool _useAni`
- `QColor lightBackgroundColor`
- `QColor darkBackgroundColor`
- `QColor _lightBarColor`
- `QColor _darkBarColor`
- `QPropertyAnimation *ani`
- `bool _isPaused`
- `bool _isError`

**Public Slots / 公共槽函数**
- `void _onValueChanged(float value)`

#### IndeterminateProgressBar

- **Declaration / 声明**: `class IndeterminateProgressBar : public QProgressBar{`
- **Inherits / 继承**: `public QProgressBar`

**Properties / 属性**
- `Q_PROPERTY(float shortPos READ getShortPos WRITE setShortPos)`
- `Q_PROPERTY(float longPos READ getLongPos WRITE setLongPos)`

**Public Members / 公有成员**
- `IndeterminateProgressBar(QWidget *parent, bool start)`
- `QColor lightBarColor()`
- `QColor darkBarColor()`
- `void setCustomBarColor(QVariant *light, QVariant *dark)`
- `float getShortPos()`
- `void setShortPos(float p)`
- `float getLongPos()`
- `void setLongPos(float p)`
- `void start()`
- `void stop()`
- `bool isStarted()`
- `void pause()`
- `void resume()`
- `void setPaused(bool isPaused)`
- `bool isPaused()`
- `void error()`
- `void setError(bool isError)`
- `bool isError()`
- `QColor barColor()`
- `void paintEvent(QPaintEvent *e) override`
- `float _shortPos`
- `float _longPos`
- `QPropertyAnimation *shortBarAni`
- `QPropertyAnimation *longBarAni`
- `QColor _lightBarColor`
- `QColor _darkBarColor`
- `bool _isError`
- `QParallelAnimationGroup *aniGroup`
- `QSequentialAnimationGroup *longBarAniGroup`


### `widgets/progress_ring.h`

#### ProgressRing

- **Declaration / 声明**: `class ProgressRing : public ProgressBar{`
- **Inherits / 继承**: `public ProgressBar`

**Properties / 属性**
- `Q_PROPERTY(int strokeWidth READ getStrokeWidth WRITE setStrokeWidth)`

**Public Members / 公有成员**
- `ProgressRing(QWidget *parent, bool useAni)`
- `int getStrokeWidth()`
- `void setStrokeWidth(int w)`
- `void _drawText(QPainter *painter, QString text)`
- `void paintEvent(QPaintEvent *e) override`
- `int _strokeWidth`

#### IndeterminateProgressRing

- **Declaration / 声明**: `class IndeterminateProgressRing : public QProgressBar{`
- **Inherits / 继承**: `public QProgressBar`

**Properties / 属性**
- `Q_PROPERTY(int strokeWidth READ getStrokeWidth WRITE setStrokeWidth)`
- `Q_PROPERTY(int startAngle READ getStartAngle WRITE setStartAngle)`
- `Q_PROPERTY(int spanAngle READ getSpanAngle WRITE setSpanAngle)`

**Public Members / 公有成员**
- `IndeterminateProgressRing(QWidget *parent, bool start)`
- `int getStartAngle()`
- `void setStartAngle(int angle)`
- `int getSpanAngle()`
- `void setSpanAngle(int angle)`
- `int getStrokeWidth()`
- `void setStrokeWidth(int w)`
- `void start()`
- `void stop()`
- `QColor lightBarColor()`
- `QColor darkBarColor()`
- `void setCustomBarColor(QVariant *light, QVariant *dark)`
- `void setCustomBackgroundColor(QVariant *light, QVariant *dark)`
- `void paintEvent(QPaintEvent *e) override`
- `QColor lightBackgroundColor`
- `QColor darkBackgroundColor`
- `QColor _lightBarColor`
- `QColor _darkBarColor`
- `int _strokeWidth`
- `int _startAngle`
- `int _spanAngle`
- `QPropertyAnimation *startAngleAni1`
- `QPropertyAnimation *startAngleAni2`
- `QPropertyAnimation *spanAngleAni1`
- `QPropertyAnimation *spanAngleAni2`
- `QSequentialAnimationGroup *startAngleAniGroup`
- `QSequentialAnimationGroup *spanAngleAniGroup`
- `QParallelAnimationGroup *aniGroup`


### `widgets/scroll_area.h`

#### ScrollArea

- **Declaration / 声明**: `class ScrollArea : public QScrollArea{`
- **Inherits / 继承**: `public QScrollArea`

**Public Members / 公有成员**
- `ScrollArea(QWidget *parent)`
- `SmoothScrollDelegate *scrollDelagate`

#### SingleDirectionScrollArea

- **Declaration / 声明**: `class SingleDirectionScrollArea : public QScrollArea{`
- **Inherits / 继承**: `public QScrollArea`

**Public Members / 公有成员**
- `SingleDirectionScrollArea(QWidget *parent, Qt::Orientation orient)`
- `void setVerticalScrollBarPolicy(Qt::ScrollBarPolicy policy)`
- `void setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy policy)`
- `void setSmoothMode(SmoothMode mode)`
- `void keyPressEvent(QKeyEvent *e) override`
- `void wheelEvent(QWheelEvent *e) override`
- `void publicSetViewportMargins(int left, int top, int right, int bottom)`
- `Qt::Orientation orient`
- `SmoothScroll *smoothScroll`
- `SmoothScrollBar *vScrollBar`
- `SmoothScrollBar *hScrollBar`

#### SmoothScrollArea

- **Declaration / 声明**: `class SmoothScrollArea : public QScrollArea{`
- **Inherits / 继承**: `public QScrollArea`

**Public Members / 公有成员**
- `SmoothScrollArea(QWidget *parent)`
- `void setScrollAnimation(Qt::Orientation orient, int duration, QEasingCurve easing)`
- `SmoothScrollDelegate *delegate`


### `widgets/scroll_bar.h`

#### ArrowButton

- **Declaration / 声明**: `class ArrowButton : public QToolButton{`
- **Inherits / 继承**: `public QToolButton`

**Public Members / 公有成员**
- `ArrowButton(FluentIcon *icon, QWidget *parent)`
- `void paintEvent(QPaintEvent *e)`
- `FluentIcon *_icon`

#### ScrollBarGroove

- **Declaration / 声明**: `class ScrollBarGroove : public QWidget{`
- **Inherits / 继承**: `public QWidget`

**Public Members / 公有成员**
- `ScrollBarGroove(Qt::Orientation orient, QWidget *parent)`
- `void fadeIn()`
- `void fadeOut()`
- `void paintEvent(QPaintEvent *e)`
- `ArrowButton *upButton`
- `ArrowButton *downButton`
- `QGraphicsOpacityEffect *opacityEffect`
- `QPropertyAnimation *opacityAni`

#### ScrollBarHandle

- **Declaration / 声明**: `class ScrollBarHandle : public QWidget{`
- **Inherits / 继承**: `public QWidget`

**Public Members / 公有成员**
- `ScrollBarHandle(Qt::Orientation orient, QWidget *parent)`
- `void paintEvent(QPaintEvent *e)`
- `Qt::Orientation orient`

#### ScrollBar

- **Declaration / 声明**: `class ScrollBar : public QWidget{`
- **Inherits / 继承**: `public QWidget`

**Properties / 属性**
- `Q_PROPERTY(int val READ getVal WRITE setVal)`

**Public Members / 公有成员**
- `ScrollBar(){}`
- `ScrollBar(Qt::Orientation orient, QAbstractScrollArea *parent)`
- `void __initWidget(QWidget *parent)`
- `int value()`
- `int getVal()`
- `void setVal(int value)`
- `int minimum()`
- `int maximum()`
- `Qt::Orientation orientation()`
- `int pageStep()`
- `int singleStep()`
- `bool isSliderDown()`
- `void setValue(int value)`
- `void setMinimum(int min)`
- `void setMaximum(int max)`
- `void setPageStep(int step)`
- `void setSingleStep(int step)`
- `void setSliderDown(bool isDown)`
- `void expand()`
- `void collapse()`
- `void enterEvent(QEvent *event) override`
- `void leaveEvent(QEvent *event) override`
- `bool eventFilter(QObject *watched, QEvent *event) override`
- `void resizeEvent(QResizeEvent *event) override`
- `void mousePressEvent(QMouseEvent *event) override`
- `void mouseReleaseEvent(QMouseEvent *event) override`
- `void mouseMoveEvent(QMouseEvent *event) override`
- `void _adjustPos(QSize size)`
- `void _adjustHandleSize()`
- `void _adjustHandlePos()`
- `int _grooveLength()`
- `int _slideLength()`
- `bool _isSlideResion(QPoint pos)`
- `void setForceHidden(bool isHidden)`
- `void wheelEvent(QWheelEvent *event)`
- `ScrollBarGroove *groove`
- `ScrollBarHandle *handle`
- `QTimer *timer`
- `Qt::Orientation _orientation`
- `int _singleStep`
- `int _pageStep`
- `int _padding`
- `int _minimum`
- `int _maximum`
- `int _value`
- `bool _isPressed`
- `bool _isEnter`
- `bool _isExpanded`
- `QPoint _pressedPos`
- `bool _isForceHidden`
- `QScrollBar *partnerBar`

**Signals / 信号**
- `void rangeChanged(std::tuple<int, int> value)`
- `void valueChanged(int value)`
- `void sliderPressed()`
- `void sliderReleased()`
- `void sliderMoved()`

**Public Slots / 公共槽函数**
- `void _onPageUp()`
- `void _onPageDown()`
- `void _onOpacityAniValueChanged()`
- `void setRange(int min, int max)`
- `void _onValueChanged(int value)`

#### SmoothScrollBar

- **Declaration / 声明**: `class SmoothScrollBar : public ScrollBar{`
- **Inherits / 继承**: `public ScrollBar`

**Public Members / 公有成员**
- `SmoothScrollBar(Qt::Orientation orient, QAbstractScrollArea *parent)`
- `void setValue(int value, bool useAni)`
- `void scrollValue(int value, bool useAni)`
- `void scrollTo(int value, bool useAni)`
- `void resetValue(int value)`
- `void mousePressEvent(QMouseEvent *event)`
- `void mouseMoveEvent(QMouseEvent *event)`
- `void setScrollAnimation(int duration, QEasingCurve easing)`
- `int duration`
- `QPropertyAnimation *ani`
- `int __value`

#### MQAbstractItemView

- **Declaration / 声明**: `class MQAbstractItemView : public QAbstractItemView{`
- **Inherits / 继承**: `public QAbstractItemView`

#### SmoothScrollDelegate

- **Declaration / 声明**: `class SmoothScrollDelegate : public QObject{`
- **Inherits / 继承**: `public QObject`

**Public Members / 公有成员**
- `SmoothScrollDelegate(QAbstractScrollArea *parent, bool useAni)`
- `bool eventFilter(QObject *watched, QEvent *event) override`
- `void setVerticalScrollBarPolicy(Qt::ScrollBarPolicy policy)`
- `void setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy policy)`
- `bool useAni`
- `SmoothScrollBar *vScrollBar`
- `SmoothScrollBar *hScrollBar`
- `SmoothScroll *verticalSmoothScroll`
- `SmoothScroll *horizonSmoothScroll`


### `widgets/separator.h`

#### HorizontalSeparator

- **Declaration / 声明**: `class HorizontalSeparator : public QWidget{`
- **Inherits / 继承**: `public QWidget`

**Public Members / 公有成员**
- `HorizontalSeparator(QWidget *parent)`
- `void paintEvent(QPaintEvent *event) override`

#### VerticalSeparator

- **Declaration / 声明**: `class VerticalSeparator : public QWidget{`
- **Inherits / 继承**: `public QWidget`

**Public Members / 公有成员**
- `VerticalSeparator(QWidget *parent)`
- `void paintEvent(QPaintEvent *event) override`


### `widgets/slider.h`

#### SliderHandle

- **Declaration / 声明**: `class SliderHandle : public QWidget{`
- **Inherits / 继承**: `public QWidget`

**Properties / 属性**
- `Q_PROPERTY(float radius READ radius WRITE setRadius)`

**Public Members / 公有成员**
- `SliderHandle(QWidget *parent)`
- `float radius()`
- `void setRadius(float r)`
- `void enterEvent(QEvent *event)`
- `void leaveEvent(QEvent *event)`
- `void mousePressEvent(QMouseEvent *event)`
- `void _startAni(float radius)`
- `void paintEvent(QPaintEvent *event)`
- `float _radius`
- `QPropertyAnimation *radiusAni`

**Signals / 信号**
- `void pressed()`
- `void released()`

#### Slider

- **Declaration / 声明**: `class Slider : public QSlider{`
- **Inherits / 继承**: `public QSlider`

**Public Members / 公有成员**
- `Slider(QWidget *parent)`
- `Slider(Qt::Orientation orientation, QWidget *parent)`
- `void _postInit()`
- `void setOrientation(Qt::Orientation orientation)`
- `void mousePressEvent(QMouseEvent *event)`
- `void mouseMoveEvent(QMouseEvent *ev)`
- `int grooveLength()`
- `float _posToValue(QPoint *pos)`
- `void paintEvent(QPaintEvent *event)`
- `void _drawHorizonGroove(QPainter *painter)`
- `void _drawVerticalGroove(QPainter *painter)`
- `void resizeEvent(QResizeEvent *event)`
- `SliderHandle *handle`
- `QPoint *_pressedPos`

**Signals / 信号**
- `void clicked(int)`

**Public Slots / 公共槽函数**
- `void _adjustHandlePos()`

#### ClickableSlider

- **Declaration / 声明**: `class ClickableSlider : public QSlider{`
- **Inherits / 继承**: `public QSlider`

**Public Members / 公有成员**
- `ClickableSlider(Qt::Orientation orientation, QWidget *parent) : QSlider(orientation, parent){}`
- `ClickableSlider(QWidget *parent) : QSlider(parent){}`
- `void mousePressEvent(QMouseEvent *event)`

**Signals / 信号**
- `void clicked(int)`

#### HollowHandleStyle

- **Declaration / 声明**: `class HollowHandleStyle : public QProxyStyle{`
- **Inherits / 继承**: `public QProxyStyle`

**Public Members / 公有成员**
- `HollowHandleStyle(QMap<QString, QVariant*> *config, QStyle *style)`
- `QRect subControlRect(ComplexControl cc, const QStyleOptionComplex *opt, SubControl sc, const QWidget *widget) const`
- `void drawComplexControl(ComplexControl cc, const QStyleOptionComplex *opt, QPainter *painter, const QWidget *widget) const`
- `QMap<QString, QVariant*> *config`


### `widgets/spin_box.h`

#### SpinButton

- **Declaration / 声明**: `class SpinButton : public QToolButton{`
- **Inherits / 继承**: `public QToolButton`

**Public Members / 公有成员**
- `SpinButton(SpinIcon *icon, QWidget *parent)`
- `void mousePressEvent(QMouseEvent *e) override`
- `void mouseReleaseEvent(QMouseEvent *e) override`
- `void paintEvent(QPaintEvent *e) override`
- `bool isPressed`
- `SpinIcon *_icon`

#### CompactSpinButton

- **Declaration / 声明**: `class CompactSpinButton : public QToolButton{`
- **Inherits / 继承**: `public QToolButton`

**Public Members / 公有成员**
- `CompactSpinButton(QWidget *parent)`
- `void paintEvent(QPaintEvent *e) override`

#### SpinFlyoutView

- **Declaration / 声明**: `class SpinFlyoutView : public FlyoutViewBase{`
- **Inherits / 继承**: `public FlyoutViewBase`

**Public Members / 公有成员**
- `SpinFlyoutView(QWidget *parent)`
- `void paintEvent(QPaintEvent *e) override`
- `TransparentToolButton *upButton`
- `TransparentToolButton *downButton`
- `QVBoxLayout *vBoxLayout`

#### SpinBox

- **Declaration / 声明**: `class SpinBox : public QSpinBox{`
- **Inherits / 继承**: `public QSpinBox`

**Public Members / 公有成员**
- `SpinBox(QWidget *parent)`
- `void spinBoxBaseInit()`
- `void inlineSpinBoxBaseInit()`
- `void _drawBorderBottom()`
- `void paintEvent(QPaintEvent *e) override`
- `void setAccelerated(bool on)`
- `QHBoxLayout *hBoxLayout`
- `SpinButton *upButton`
- `SpinButton *downButton`

**Public Slots / 公共槽函数**
- `void _showContextMenu(QPoint pos)`

#### CompactSpinBox

- **Declaration / 声明**: `class CompactSpinBox : public QSpinBox{`
- **Inherits / 继承**: `public QSpinBox`

**Public Members / 公有成员**
- `CompactSpinBox(QWidget *parent)`
- `void spinBoxBaseInit()`
- `void compactSpinBoxBaseInit()`
- `void _drawBorderBottom()`
- `void paintEvent(QPaintEvent *e) override`
- `void focusInEvent(QFocusEvent *event) override`
- `void setAccelerated(bool on)`
- `QHBoxLayout *hBoxLayout`
- `CompactSpinButton *compactSpinButton`
- `SpinFlyoutView *spinFlyoutView`
- `Flyout *spinFlyout`

**Public Slots / 公共槽函数**
- `void _showContextMenu(QPoint pos)`
- `void _showFlyout()`

#### DoubleSpinBox

- **Declaration / 声明**: `class DoubleSpinBox : public QDoubleSpinBox{`
- **Inherits / 继承**: `public QDoubleSpinBox`

**Public Members / 公有成员**
- `DoubleSpinBox(QWidget *parent)`
- `void spinBoxBaseInit()`
- `void inlineSpinBoxBaseInit()`
- `void _drawBorderBottom()`
- `void paintEvent(QPaintEvent *e) override`
- `void setAccelerated(bool on)`
- `QHBoxLayout *hBoxLayout`
- `SpinButton *upButton`
- `SpinButton *downButton`

**Public Slots / 公共槽函数**
- `void _showContextMenu(QPoint pos)`

#### CompactDoubleSpinBox

- **Declaration / 声明**: `class CompactDoubleSpinBox : public QDoubleSpinBox{`
- **Inherits / 继承**: `public QDoubleSpinBox`

**Public Members / 公有成员**
- `CompactDoubleSpinBox(QWidget *parent)`
- `void spinBoxBaseInit()`
- `void compactSpinBoxBaseInit()`
- `void _drawBorderBottom()`
- `void paintEvent(QPaintEvent *e) override`
- `void focusInEvent(QFocusEvent *event) override`
- `void setAccelerated(bool on)`
- `QHBoxLayout *hBoxLayout`
- `CompactSpinButton *compactSpinButton`
- `SpinFlyoutView *spinFlyoutView`
- `Flyout *spinFlyout`

**Public Slots / 公共槽函数**
- `void _showContextMenu(QPoint pos)`
- `void _showFlyout()`

#### TimeEdit

- **Declaration / 声明**: `class TimeEdit : public QTimeEdit{`
- **Inherits / 继承**: `public QTimeEdit`

**Public Members / 公有成员**
- `TimeEdit(QWidget *parent)`
- `void spinBoxBaseInit()`
- `void inlineSpinBoxBaseInit()`
- `void _drawBorderBottom()`
- `void paintEvent(QPaintEvent *e) override`
- `void setAccelerated(bool on)`
- `QHBoxLayout *hBoxLayout`
- `SpinButton *upButton`
- `SpinButton *downButton`

**Public Slots / 公共槽函数**
- `void _showContextMenu(QPoint pos)`

#### CompactTimeEdit

- **Declaration / 声明**: `class CompactTimeEdit : public QTimeEdit{`
- **Inherits / 继承**: `public QTimeEdit`

**Public Members / 公有成员**
- `CompactTimeEdit(QWidget *parent)`
- `void spinBoxBaseInit()`
- `void compactSpinBoxBaseInit()`
- `void _drawBorderBottom()`
- `void paintEvent(QPaintEvent *e) override`
- `void focusInEvent(QFocusEvent *event) override`
- `void setAccelerated(bool on)`
- `QHBoxLayout *hBoxLayout`
- `CompactSpinButton *compactSpinButton`
- `SpinFlyoutView *spinFlyoutView`
- `Flyout *spinFlyout`

**Public Slots / 公共槽函数**
- `void _showContextMenu(QPoint pos)`
- `void _showFlyout()`

#### DateTimeEdit

- **Declaration / 声明**: `class DateTimeEdit : public QDateTimeEdit{`
- **Inherits / 继承**: `public QDateTimeEdit`

**Public Members / 公有成员**
- `DateTimeEdit(QWidget *parent)`
- `void spinBoxBaseInit()`
- `void inlineSpinBoxBaseInit()`
- `void _drawBorderBottom()`
- `void paintEvent(QPaintEvent *e) override`
- `void setAccelerated(bool on)`
- `QHBoxLayout *hBoxLayout`
- `SpinButton *upButton`
- `SpinButton *downButton`

**Public Slots / 公共槽函数**
- `void _showContextMenu(QPoint pos)`

#### CompactDateTimeEdit

- **Declaration / 声明**: `class CompactDateTimeEdit : public QDateTimeEdit{`
- **Inherits / 继承**: `public QDateTimeEdit`

**Public Members / 公有成员**
- `CompactDateTimeEdit(QWidget *parent)`
- `void spinBoxBaseInit()`
- `void compactSpinBoxBaseInit()`
- `void _drawBorderBottom()`
- `void paintEvent(QPaintEvent *e) override`
- `void focusInEvent(QFocusEvent *event) override`
- `void setAccelerated(bool on)`
- `QHBoxLayout *hBoxLayout`
- `CompactSpinButton *compactSpinButton`
- `SpinFlyoutView *spinFlyoutView`
- `Flyout *spinFlyout`

**Public Slots / 公共槽函数**
- `void _showContextMenu(QPoint pos)`
- `void _showFlyout()`

#### DateEdit

- **Declaration / 声明**: `class DateEdit : public QDateEdit{`
- **Inherits / 继承**: `public QDateEdit`

**Public Members / 公有成员**
- `DateEdit(QWidget *parent)`
- `void spinBoxBaseInit()`
- `void inlineSpinBoxBaseInit()`
- `void _drawBorderBottom()`
- `void paintEvent(QPaintEvent *e) override`
- `void setAccelerated(bool on)`
- `QHBoxLayout *hBoxLayout`
- `SpinButton *upButton`
- `SpinButton *downButton`

**Public Slots / 公共槽函数**
- `void _showContextMenu(QPoint pos)`

#### CompactDateEdit

- **Declaration / 声明**: `class CompactDateEdit : public QDateEdit{`
- **Inherits / 继承**: `public QDateEdit`

**Public Members / 公有成员**
- `CompactDateEdit(QWidget *parent)`
- `void spinBoxBaseInit()`
- `void compactSpinBoxBaseInit()`
- `void _drawBorderBottom()`
- `void paintEvent(QPaintEvent *e) override`
- `void focusInEvent(QFocusEvent *event) override`
- `void setAccelerated(bool on)`
- `QHBoxLayout *hBoxLayout`
- `CompactSpinButton *compactSpinButton`
- `SpinFlyoutView *spinFlyoutView`
- `Flyout *spinFlyout`

**Public Slots / 公共槽函数**
- `void _showContextMenu(QPoint pos)`
- `void _showFlyout()`


### `widgets/stacked_widget.h`

#### OpacityAniStackedWidget

- **Declaration / 声明**: `class OpacityAniStackedWidget : public QStackedWidget{`
- **Inherits / 继承**: `public QStackedWidget`

**Public Members / 公有成员**
- `OpacityAniStackedWidget(QWidget *parent)`
- `void addWidget(QWidget *w)`
- `void setCurrentIndex(int index)`
- `void setCurrentWidget(QWidget *w)`
- `int __nextIndex`
- `QList<QGraphicsOpacityEffect *> __effects`
- `QList<QPropertyAnimation *> __anis`
- `QGraphicsOpacityEffect *effect`
- `QPropertyAnimation *ani`

**Public Slots / 公共槽函数**
- `void __onAniFinished()`

#### PopUpAniInfo

- **Declaration / 声明**: `class PopUpAniInfo{`

**Public Members / 公有成员**
- `PopUpAniInfo(QWidget *widget, int deltaX, int deltaY, QPropertyAnimation *ani)`
- `QWidget *widget`
- `int deltaX`
- `int deltaY`
- `QPropertyAnimation *ani`

#### PopUpAniStackedWidget

- **Declaration / 声明**: `class PopUpAniStackedWidget : public QStackedWidget{`
- **Inherits / 继承**: `public QStackedWidget`

**Public Members / 公有成员**
- `PopUpAniStackedWidget(QWidget *parent)`
- `void addWidget(QWidget *widget, int deltaX, int deltaY)`
- `void setCurrentIndex(int index, bool needPopOut, bool showNextWidgetDirectly, int duration, QEasingCurve easingCurve)`
- `void setCurrentWidget(QWidget *widget, bool needPopOut, bool showNextWidgetDirectly, int duration, QEasingCurve easingCurve)`
- `QList<PopUpAniInfo*> aniInfos`
- `int _nextIndex`
- `QPropertyAnimation *_ani`

**Signals / 信号**
- `void aniFinished()`
- `void aniStart()`

**Public Slots / 公共槽函数**
- `void __setAnimation(QPropertyAnimation *ani, QPoint startValue, QPoint endValue, int duration, QEasingCurve easingCurve)`
- `void __onAniFinished()`


### `widgets/state_tool_tip.h`

#### StateCloseButton

- **Declaration / 声明**: `class StateCloseButton : public QToolButton{`
- **Inherits / 继承**: `public QToolButton`

**Public Members / 公有成员**
- `StateCloseButton(QWidget *parent)`
- `void enterEvent(QEvent *event) override`
- `void leaveEvent(QEvent *event) override`
- `void mousePressEvent(QMouseEvent *event) override`
- `void mouseReleaseEvent(QMouseEvent *event) override`
- `void paintEvent(QPaintEvent *event) override`
- `bool isPressed`
- `bool isEnter`

#### StateToolTip

- **Declaration / 声明**: `class StateToolTip : public QWidget{`
- **Inherits / 继承**: `public QWidget`

**Public Members / 公有成员**
- `StateToolTip(QString title, QString content, QWidget *parent)`
- `void __initWidget()`
- `void __initLayout()`
- `void __setQss()`
- `void setTitle(QString title)`
- `void setContent(QString content)`
- `void setState(bool isDone)`
- `QPoint getSuitablePos()`
- `void paintEvent(QPaintEvent *event) override`
- `QString title`
- `QString content`
- `QLabel *titleLabel`
- `QLabel *contentLabel`
- `QTimer *rotateTimer`
- `QGraphicsOpacityEffect *opacityEffect`
- `QPropertyAnimation *animation`
- `StateCloseButton *closeButton`
- `bool isDone`
- `int rotateAngle`
- `int deltaAngle`

**Signals / 信号**
- `void closedSignal()`

**Public Slots / 公共槽函数**
- `void __onCloseButtonClicked()`
- `void __fadeOut()`
- `void __rotateTimerFlowSlot()`


### `widgets/switch_button.h`

#### Indicator

- **Declaration / 声明**: `class Indicator : public ToolButton{`
- **Inherits / 继承**: `public ToolButton`

**Properties / 属性**
- `Q_PROPERTY(int sliderX READ getSliderX WRITE setSliderX)`

**Public Members / 公有成员**
- `Indicator(QWidget *parent)`
- `void mouseReleaseEvent(QMouseEvent *e) override`
- `void toggle()`
- `void setDown(bool isDown)`
- `void setHover(bool isHover)`
- `void paintEvent(QPaintEvent *event) override`
- `void _drawBackground(QPainter *painter)`
- `void _drawCircle(QPainter *painter)`
- `QColor _backgroudColor()`
- `QColor _borderColor()`
- `QColor _sliderColor()`
- `int getSliderX()`
- `void setSliderX(int x)`
- `int _sliderX`
- `QPropertyAnimation *slideAni`

**Signals / 信号**
- `void checkedChanged(bool)`

**Public Slots / 公共槽函数**
- `void _toggleSlider()`

#### SwitchButton

- **Declaration / 声明**: `class SwitchButton : public QWidget{`
- **Inherits / 继承**: `public QWidget`

**Properties / 属性**
- `Q_PROPERTY(int spacing READ getSpacing WRITE setSpacing)`
- `Q_PROPERTY(bool checked READ isChecked WRITE setChecked)`
- `Q_PROPERTY(QString text READ getText WRITE setText)`
- `Q_PROPERTY(QString onText READ getOnText WRITE setOnText)`
- `Q_PROPERTY(QString offText READ getOffText WRITE setOffText)`

**Public Members / 公有成员**
- `SwitchButton(QWidget *parent, IndicatorPosition indicatorPos)`
- `SwitchButton(QString text, QWidget *parent, IndicatorPosition indicatorPos)`
- `void __initWidget()`
- `bool eventFilter(QObject *watched, QEvent *event) override`
- `bool isChecked()`
- `void setChecked(bool isChecked)`
- `void toggleChecked()`
- `QString getText()`
- `void setText(QString text)`
- `int getSpacing()`
- `void setSpacing(int spacing)`
- `QString getOnText()`
- `void setOnText(QString text)`
- `QString getOffText()`
- `void setOffText(QString text)`
- `QString _text`
- `QString _offText`
- `QString _onText`
- `int __spacing`
- `IndicatorPosition indicatorPos`
- `QHBoxLayout *hBox`
- `Indicator *indicator`
- `QLabel *label`

**Signals / 信号**
- `void checkedChanged(bool)`

**Public Slots / 公共槽函数**
- `void _updateText()`


### `widgets/tab_view.h`

#### TabToolButton

- **Declaration / 声明**: `class TabToolButton : public TransparentToolButton{`
- **Inherits / 继承**: `public TransparentToolButton`

**Public Members / 公有成员**
- `TabToolButton(QWidget *parent)`
- `TabToolButton(FluentIcon *icon, QWidget *parent)`
- `TabToolButton(SpinIcon *icon, QWidget *parent)`
- `TabToolButton(QIcon *icon, QWidget *parent)`
- `TabToolButton(QString icon, QWidget *parent)`
- `void _postInit() override`
- `void _drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state) override`

#### TabItem

- **Declaration / 声明**: `class TabItem : public PushButton{`
- **Inherits / 继承**: `public PushButton`

**Public Members / 公有成员**
- `TabItem(){}`
- `TabItem(QWidget *parent)`
- `TabItem(QString text, QWidget *parent, QVariant *icon)`
- `TabItem(QIcon *icon, QString text, QWidget *parent)`
- `TabItem(FluentIcon *icon, QString text, QWidget *parent)`
- `void _postInit() override`
- `void __initWidget()`
- `void slideTo(int x, int duration)`
- `void setShadowEnabled(bool isEnabled)`
- `bool _canShowShadow()`
- `void setRouteKey(QString key)`
- `QString routeKey()`
- `void setBorderRadius(int radius)`
- `void setSelected(bool isSelected)`
- `void setCloseButtonDisplayMode(TabCloseButtonDisplayMode mode)`
- `void setTextColor(QColor color)`
- `void setSelectedBackgroundColor(QColor light, QColor dark)`
- `void resizeEvent(QResizeEvent *event) override`
- `void enterEvent(QEvent *event) override`
- `void leaveEvent(QEvent *event) override`
- `void mousePressEvent(QMouseEvent *event)`
- `void mouseMoveEvent(QMouseEvent *event)`
- `void mouseReleaseEvent(QMouseEvent *e) override`
- `void _forwardMouseEvent(QMouseEvent *e)`
- `QSize sizeHint()`
- `void paintEvent(QPaintEvent *event) override`
- `void _drawSelectedBackground(QPainter *painter)`
- `void _drawNotSelectedBackground(QPainter *painter)`
- `void _drawText(QPainter *painter)`
- `int borderRadius`
- `bool isSelected`
- `bool isShadowEnabled`
- `TabCloseButtonDisplayMode closeButtonDisplayMode`
- `QString _routeKey`
- `QColor textColor`
- `QColor lightSelectedBackgroundColor`
- `QColor darkSelectedBackgroundColor`
- `TabToolButton *closeButton`
- `QGraphicsDropShadowEffect *shadowEffect`
- `QPropertyAnimation *slideAni`

**Signals / 信号**
- `void closed()`

#### TabBar

- **Declaration / 声明**: `class TabBar : public SingleDirectionScrollArea{`
- **Inherits / 继承**: `public SingleDirectionScrollArea`

**Properties / 属性**
- `Q_PROPERTY(bool movable READ isMovable WRITE setMovable)`
- `Q_PROPERTY(bool scrollable READ isScrollable WRITE setScrollable)`
- `Q_PROPERTY(int tabMaxWidth READ tabMaximumWidth WRITE setTabMaximumWidth)`
- `Q_PROPERTY(int tabMinWidth READ tabMinimumWidth WRITE setTabMinimumWidth)`
- `Q_PROPERTY(bool tabShadowEnabled READ isTabShadowEnabled WRITE setTabShadowEnabled)`

**Public Members / 公有成员**
- `TabBar(QWidget *parent)`
- `void __initWidget()`
- `void __initLayout()`
- `void setAddButtonVisible(bool isVisible)`
- `TabItem *addTab(QString routeKey, QString text, QVariant *icon, std::function<void()> onClick)`
- `TabItem *insertTab(int index, QString routeKey, QString text, QVariant *icon, std::function<void()> onClick)`
- `void removeTab(int index)`
- `void removeTabByKey(QString routeKey)`
- `void setCurrentIndex(int index)`
- `void setCurrentTab(QString routeKey)`
- `int currentIndex()`
- `TabItem *currentTab()`
- `void setCloseButtonDisplayMode(TabCloseButtonDisplayMode mode)`
- `TabItem *tabItem(int index)`
- `TabItem *tab(QString routeKey)`
- `QRect tabRegion()`
- `QRect tabRect(int index)`
- `QString tabText(int index)`
- `QIcon tabIcon(int index)`
- `QString tabToolTip(int index)`
- `void setTabsClosable(bool isClosable)`
- `bool tabsClosable()`
- `void setTabIcon(int index, QVariant *icon)`
- `void setTabText(int index, QString text)`
- `void setTabVisible(int index, bool isVisible)`
- `void setTabTextColor(int index, QColor color)`
- `void setTabToolTip(int index, QString toolTip)`
- `void setTabSelectedBackgroundColor(QColor light, QColor dark)`
- `void setTabShadowEnabled(bool isEnabled)`
- `bool isTabShadowEnabled()`
- `void paintEvent(QPaintEvent *event) override`
- `void setMovable(bool movable)`
- `bool isMovable()`
- `void setScrollable(bool scrollable)`
- `void setTabMaximumWidth(int width)`
- `void setTabMinimumWidth(int width)`
- `int tabMaximumWidth()`
- `int tabMinimumWidth()`
- `bool isScrollable()`
- `int count()`
- `void mousePressEvent(QMouseEvent *event) override`
- `void mouseMoveEvent(QMouseEvent *event) override`
- `void mouseReleaseEvent(QMouseEvent *e) override`
- `void _swapItem(int index)`
- `QList<TabItem*> items`
- `QMap<QString, TabItem*> itemMap`
- `int _currentIndex`
- `bool _isMovable`
- `bool _isScrollable`
- `bool _isTabShadowEnabled`
- `int _tabMaxWidth`
- `int _tabMinWidth`
- `QPoint dragPos`
- `bool isDraging`
- `QColor lightSelectedBackgroundColor`
- `QColor darkSelectedBackgroundColor`
- `TabCloseButtonDisplayMode closeButtonDisplayMode`
- `QWidget *view`
- `QHBoxLayout *hBoxLayout`
- `QHBoxLayout *itemLayout`
- `QHBoxLayout *widgetLayout`
- `TabToolButton *addButton`

**Signals / 信号**
- `void currentChanged(int)`
- `void tabBarClicked(int)`
- `void tabCloseRequested(int)`
- `void tabAddRequested()`

**Public Slots / 公共槽函数**
- `void _onItemPressed()`
- `void _adjustLayout()`


### `widgets/table_view.h`

#### TableItemDelegate

- **Declaration / 声明**: `class TableItemDelegate : public QStyledItemDelegate{`
- **Inherits / 继承**: `public QStyledItemDelegate`

**Public Members / 公有成员**
- `TableItemDelegate(QTableView *parent)`
- `void setHoverRow(int row)`
- `void setPressedRow(int row)`
- `void setSelectedRows(QList<QModelIndex> indexes)`
- `QSize sizeHint(QStyleOptionViewItem *option, QModelIndex *index)`
- `QWidget *createEditor(QWidget *parent, QStyleOptionViewItem *option, QModelIndex *index)`
- `void updateEditorGeometry(QWidget *editor, QStyleOptionViewItem *option, QModelIndex *index)`
- `virtual void _drawbackground(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const`
- `virtual void _drawIndicator(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const`
- `void initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const override`
- `void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override`
- `int margin`
- `int hoverRow`
- `int pressedRow`
- `QList<int> selectedRows`

#### TableWidget

- **Declaration / 声明**: `class TableWidget : public QTableWidget{`
- **Inherits / 继承**: `public QTableWidget`

**Properties / 属性**
- `Q_PROPERTY(bool selectRightClickedRow READ isSelectRightClickedRow WRITE setSelectRightClickedRow)`

**Public Members / 公有成员**
- `TableWidget(QWidget *parent)`
- `void showEvent(QShowEvent *event)`
- `void setBorderVisible(bool isVisible)`
- `void setBorderRadius(int radius)`
- `void _setHoverRow(int row)`
- `void _setPressedRow(int row)`
- `void _setSelectedRows(QList<QModelIndex> indexes)`
- `void leaveEvent(QEvent *event) override`
- `void resizeEvent(QResizeEvent *event) override`
- `void keyPressEvent(QKeyEvent *e) override`
- `void mousePressEvent(QMouseEvent *e) override`
- `void mouseReleaseEvent(QMouseEvent *event)`
- `void setItemDelegate(TableItemDelegate *delegate)`
- `void selectAll()`
- `void clearSelection()`
- `void setCurrentIndex(QModelIndex *index)`
- `void updateSelectedRows()`
- `void setCurrentCell(int row, int column, QItemSelectionModel::SelectionFlag command)`
- `void setCurrentCell(int row, int column, QItemSelectionModel::SelectionFlags command)`
- `void setCurrentItem(QTableWidgetItem *item, QItemSelectionModel::SelectionFlag command)`
- `void setCurrentItem(QTableWidgetItem *item, QItemSelectionModel::SelectionFlags command)`
- `bool isSelectRightClickedRow()`
- `void setSelectRightClickedRow(bool isSelect)`
- `TableItemDelegate *delegate`
- `SmoothScrollDelegate *scrollDelagate`
- `bool _isSelectRightClickedRow`

**Public Slots / 公共槽函数**
- `void selectRow(int row)`

#### TableView

- **Declaration / 声明**: `class TableView : public QTableView{`
- **Inherits / 继承**: `public QTableView`

**Properties / 属性**
- `Q_PROPERTY(bool selectRightClickedRow READ isSelectRightClickedRow WRITE setSelectRightClickedRow)`

**Public Members / 公有成员**
- `TableView(QWidget *parent)`
- `void showEvent(QShowEvent *event)`
- `void setBorderVisible(bool isVisible)`
- `void setBorderRadius(int radius)`
- `void _setHoverRow(int row)`
- `void _setPressedRow(int row)`
- `void _setSelectedRows(QList<QModelIndex> indexes)`
- `void leaveEvent(QEvent *event) override`
- `void resizeEvent(QResizeEvent *event) override`
- `void keyPressEvent(QKeyEvent *e) override`
- `void mousePressEvent(QMouseEvent *e) override`
- `void mouseReleaseEvent(QMouseEvent *event)`
- `void setItemDelegate(TableItemDelegate *delegate)`
- `void selectAll()`
- `void clearSelection()`
- `void setCurrentIndex(QModelIndex *index)`
- `void updateSelectedRows()`
- `bool isSelectRightClickedRow()`
- `void setSelectRightClickedRow(bool isSelect)`
- `TableItemDelegate *delegate`
- `SmoothScrollDelegate *scrollDelagate`
- `bool _isSelectRightClickedRow`

**Public Slots / 公共槽函数**
- `void selectRow(int row)`


### `widgets/teaching_tip.h`

#### TeachingTipView

- **Declaration / 声明**: `class TeachingTipView : public FlyoutView{`
- **Inherits / 继承**: `public FlyoutView`

**Public Members / 公有成员**
- `TeachingTipView(QString title, QString content, QVariant *icon, QVariant *image, bool isClosable, TeachingTipTailPosition tailPosition, QWidget *parent)`
- `void _adjustImage()`
- `void _addImageToLayout()`
- `void paintEvent(QPaintEvent *event) override`
- `TeachingTipManager *manager`
- `QHBoxLayout *hBoxLayout`

#### TeachTipBubble

- **Declaration / 声明**: `class TeachTipBubble : public QWidget{`
- **Inherits / 继承**: `public QWidget`

**Public Members / 公有成员**
- `TeachTipBubble(FlyoutViewBase *view, TeachingTipTailPosition tailPosition, QWidget *parent)`
- `void setView(FlyoutViewBase *view)`
- `void paintEvent(QPaintEvent *event) override`
- `TeachingTipManager *manager`
- `QHBoxLayout *hBoxLayout`
- `FlyoutViewBase *view`

#### TeachingTip

- **Declaration / 声明**: `class TeachingTip : public QWidget{`
- **Inherits / 继承**: `public QWidget`

**Public Members / 公有成员**
- `TeachingTip(FlyoutViewBase *view, QWidget *target, int duration, TeachingTipTailPosition tailPosition, QWidget *parent, bool isDeleteOnClose)`
- `void setShadowEffect(int blurRadius, std::tuple<int, int> offset)`
- `void _fadeOut()`
- `void showEvent(QShowEvent *event) override`
- `void closeEvent(QCloseEvent *event) override`
- `bool eventFilter(QObject *watched, QEvent *event) override`
- `void addWidget(QWidget *widget, int stretch, Qt::AlignmentFlag align)`
- `FlyoutViewBase *getView()`
- `void setView(FlyoutViewBase *view)`
- `static TeachingTip *make(FlyoutViewBase *view, QWidget *target, int duration, TeachingTipTailPosition tailPosition, QWidget *parent, bool isDeleteOnClose)`
- `static TeachingTip *create(QWidget *target, QString title, QString content, QVariant *icon, QVariant *image, bool isClosable, int duration, TeachingTipTailPosition tailPostion, QWidget *parent, bool isDeleteOnClose)`
- `QWidget *target`
- `int duration`
- `bool isDeleteOnClose`
- `TeachingTipManager *manager`
- `QHBoxLayout *hBoxLayout`
- `QPropertyAnimation *opacityAni`
- `TeachTipBubble *bubble`
- `QGraphicsDropShadowEffect *shadowEffect`

#### PopupTeachingTip

- **Declaration / 声明**: `class PopupTeachingTip : public TeachingTip{`
- **Inherits / 继承**: `public TeachingTip`

**Public Members / 公有成员**
- `PopupTeachingTip(FlyoutViewBase *view, QWidget *target, int duration, TeachingTipTailPosition tailPosition, QWidget *parent, bool isDeleteOnClose)`

#### TeachingTipManager

- **Declaration / 声明**: `class TeachingTipManager : public QObject{`
- **Inherits / 继承**: `public QObject`

**Public Members / 公有成员**
- `TeachingTipManager()`
- `virtual void doLayout(TeachTipBubble *tip)`
- `virtual ImagePosition imagePosition()`
- `QPoint position(TeachingTip *tip)`
- `virtual void draw(TeachTipBubble *tip, QPainter *painter)`
- `virtual QPoint _pos(TeachingTip *tip)`
- `static TeachingTipManager *make(TeachingTipTailPosition position)`

#### TopTailTeachingTipManager

- **Declaration / 声明**: `class TopTailTeachingTipManager : public TeachingTipManager{`
- **Inherits / 继承**: `public TeachingTipManager`

**Public Members / 公有成员**
- `TopTailTeachingTipManager()`
- `void doLayout(TeachTipBubble *tip) override`
- `ImagePosition imagePosition() override`
- `void draw(TeachTipBubble *tip, QPainter *painter) override`
- `QPoint _pos(TeachingTip *tip) override`

#### BottomTailTeachingTipManager

- **Declaration / 声明**: `class BottomTailTeachingTipManager : public TeachingTipManager{`
- **Inherits / 继承**: `public TeachingTipManager`

**Public Members / 公有成员**
- `BottomTailTeachingTipManager()`
- `void doLayout(TeachTipBubble *tip) override`
- `void draw(TeachTipBubble *tip, QPainter *painter) override`
- `QPoint _pos(TeachingTip *tip) override`

#### LeftTailTeachingTipManager

- **Declaration / 声明**: `class LeftTailTeachingTipManager : public TeachingTipManager{`
- **Inherits / 继承**: `public TeachingTipManager`

**Public Members / 公有成员**
- `LeftTailTeachingTipManager()`
- `void doLayout(TeachTipBubble *tip) override`
- `ImagePosition imagePosition() override`
- `void draw(TeachTipBubble *tip, QPainter *painter) override`
- `QPoint _pos(TeachingTip *tip) override`

#### RightTailTeachingTipManager

- **Declaration / 声明**: `class RightTailTeachingTipManager : public TeachingTipManager{`
- **Inherits / 继承**: `public TeachingTipManager`

**Public Members / 公有成员**
- `RightTailTeachingTipManager()`
- `void doLayout(TeachTipBubble *tip) override`
- `ImagePosition imagePosition() override`
- `void draw(TeachTipBubble *tip, QPainter *painter) override`
- `QPoint _pos(TeachingTip *tip) override`

#### TopLeftTailTeachingTipManager

- **Declaration / 声明**: `class TopLeftTailTeachingTipManager : public TopTailTeachingTipManager{`
- **Inherits / 继承**: `public TopTailTeachingTipManager`

**Public Members / 公有成员**
- `TopLeftTailTeachingTipManager()`
- `void draw(TeachTipBubble *tip, QPainter *painter) override`
- `QPoint _pos(TeachingTip *tip) override`

#### TopRightTailTeachingTipManager

- **Declaration / 声明**: `class TopRightTailTeachingTipManager : public TopTailTeachingTipManager{`
- **Inherits / 继承**: `public TopTailTeachingTipManager`

**Public Members / 公有成员**
- `TopRightTailTeachingTipManager()`
- `void draw(TeachTipBubble *tip, QPainter *painter) override`
- `QPoint _pos(TeachingTip *tip) override`

#### BottomLeftTailTeachingTipManager

- **Declaration / 声明**: `class BottomLeftTailTeachingTipManager : public BottomTailTeachingTipManager{`
- **Inherits / 继承**: `public BottomTailTeachingTipManager`

**Public Members / 公有成员**
- `BottomLeftTailTeachingTipManager()`
- `void draw(TeachTipBubble *tip, QPainter *painter) override`
- `QPoint _pos(TeachingTip *tip) override`

#### BottomRightTailTeachingTipManager

- **Declaration / 声明**: `class BottomRightTailTeachingTipManager : public BottomTailTeachingTipManager{`
- **Inherits / 继承**: `public BottomTailTeachingTipManager`

**Public Members / 公有成员**
- `BottomRightTailTeachingTipManager()`
- `void draw(TeachTipBubble *tip, QPainter *painter) override`
- `QPoint _pos(TeachingTip *tip) override`

#### LeftTopTailTeachingTipManager

- **Declaration / 声明**: `class LeftTopTailTeachingTipManager : public LeftTailTeachingTipManager{`
- **Inherits / 继承**: `public LeftTailTeachingTipManager`

**Public Members / 公有成员**
- `LeftTopTailTeachingTipManager()`
- `ImagePosition imagePosition() override`
- `void draw(TeachTipBubble *tip, QPainter *painter) override`
- `QPoint _pos(TeachingTip *tip) override`

#### LeftBottomTailTeachingTipManager

- **Declaration / 声明**: `class LeftBottomTailTeachingTipManager : public LeftTailTeachingTipManager{`
- **Inherits / 继承**: `public LeftTailTeachingTipManager`

**Public Members / 公有成员**
- `LeftBottomTailTeachingTipManager()`
- `ImagePosition imagePosition() override`
- `void draw(TeachTipBubble *tip, QPainter *painter) override`
- `QPoint _pos(TeachingTip *tip) override`

#### RightTopTailTeachingTipManager

- **Declaration / 声明**: `class RightTopTailTeachingTipManager : public RightTailTeachingTipManager{`
- **Inherits / 继承**: `public RightTailTeachingTipManager`

**Public Members / 公有成员**
- `RightTopTailTeachingTipManager()`
- `ImagePosition imagePosition() override`
- `void draw(TeachTipBubble *tip, QPainter *painter) override`
- `QPoint _pos(TeachingTip *tip) override`

#### RightBottomTailTeachingTipManager

- **Declaration / 声明**: `class RightBottomTailTeachingTipManager : public RightTailTeachingTipManager{`
- **Inherits / 继承**: `public RightTailTeachingTipManager`

**Public Members / 公有成员**
- `RightBottomTailTeachingTipManager()`
- `ImagePosition imagePosition() override`
- `void draw(TeachTipBubble *tip, QPainter *painter) override`
- `QPoint _pos(TeachingTip *tip) override`


### `widgets/tool_tip.h`

#### ToolTip

- **Declaration / 声明**: `class ToolTip : public QFrame{`
- **Inherits / 继承**: `public QFrame`

**Public Members / 公有成员**
- `ToolTip(QString text, QWidget *parent)`
- `QString text()`
- `void setText(QString text)`
- `int duration()`
- `void setDuration(int duration)`
- `void __setQss()`
- `QFrame *_createContainer()`
- `void showEvent(QShowEvent *event) override`
- `void hideEvent(QHideEvent *event) override`
- `void adjustPos(QWidget *widget, ToolTipPosition position)`
- `QString __text`
- `int __duration`
- `QFrame *container`
- `QTimer *timer`
- `QHBoxLayout *containerLayout`
- `QLabel *label`
- `QPropertyAnimation *opacityAni`
- `QGraphicsDropShadowEffect *shadowEffect`

#### ToolTipPositionManager

- **Declaration / 声明**: `class ToolTipPositionManager{`

**Public Members / 公有成员**
- `QPoint position(ToolTip *tooltip, QWidget *parent)`
- `virtual QPoint _pos(ToolTip *tooltip, QWidget *parent)`
- `static ToolTipPositionManager* make(ToolTipPosition position)`

#### TopToolTipManager

- **Declaration / 声明**: `class TopToolTipManager : public ToolTipPositionManager{`
- **Inherits / 继承**: `public ToolTipPositionManager`

**Public Members / 公有成员**
- `QPoint _pos(ToolTip *tooltip, QWidget *parent) override`

#### BottomToolTipManager

- **Declaration / 声明**: `class BottomToolTipManager : public ToolTipPositionManager{`
- **Inherits / 继承**: `public ToolTipPositionManager`

**Public Members / 公有成员**
- `QPoint _pos(ToolTip *tooltip, QWidget *parent) override`

#### LeftToolTipManager

- **Declaration / 声明**: `class LeftToolTipManager : public ToolTipPositionManager{`
- **Inherits / 继承**: `public ToolTipPositionManager`

**Public Members / 公有成员**
- `QPoint _pos(ToolTip *tooltip, QWidget *parent) override`

#### RightToolTipManager

- **Declaration / 声明**: `class RightToolTipManager : public ToolTipPositionManager{`
- **Inherits / 继承**: `public ToolTipPositionManager`

**Public Members / 公有成员**
- `QPoint _pos(ToolTip *tooltip, QWidget *parent) override`

#### TopRightToolTipManager

- **Declaration / 声明**: `class TopRightToolTipManager : public ToolTipPositionManager{`
- **Inherits / 继承**: `public ToolTipPositionManager`

**Public Members / 公有成员**
- `QPoint _pos(ToolTip *tooltip, QWidget *parent) override`

#### TopLeftToolTipManager

- **Declaration / 声明**: `class TopLeftToolTipManager : public ToolTipPositionManager{`
- **Inherits / 继承**: `public ToolTipPositionManager`

**Public Members / 公有成员**
- `QPoint _pos(ToolTip *tooltip, QWidget *parent) override`

#### BottomRightToolTipManager

- **Declaration / 声明**: `class BottomRightToolTipManager : public ToolTipPositionManager{`
- **Inherits / 继承**: `public ToolTipPositionManager`

**Public Members / 公有成员**
- `QPoint _pos(ToolTip *tooltip, QWidget *parent) override`

#### BottomLeftToolTipManager

- **Declaration / 声明**: `class BottomLeftToolTipManager : public ToolTipPositionManager{`
- **Inherits / 继承**: `public ToolTipPositionManager`

**Public Members / 公有成员**
- `QPoint _pos(ToolTip *tooltip, QWidget *parent) override`

#### ToolTipFilter

- **Declaration / 声明**: `class ToolTipFilter : public QObject{`
- **Inherits / 继承**: `public QObject`

**Public Members / 公有成员**
- `ToolTipFilter(QWidget *parent, int showDelay, ToolTipPosition position)`
- `bool eventFilter(QObject *watched, QEvent *event) override`
- `ToolTip *_createToolTip()`
- `void hideToolTip()`
- `void showToolTip()`
- `void setToolTipDelay(int delay)`
- `virtual bool _canShowToolTip()`
- `bool isEnter`
- `ToolTip *_tooltip`
- `int _tooltipDelay`
- `ToolTipPosition position`
- `QTimer *timer`


### `widgets/tree_view.h`

#### TreeItemDelegate

- **Declaration / 声明**: `class TreeItemDelegate : public QStyledItemDelegate{`
- **Inherits / 继承**: `public QStyledItemDelegate`

**Public Members / 公有成员**
- `TreeItemDelegate(QTreeView *parent)`
- `void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override`
- `void initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const override`

#### TreeWidget

- **Declaration / 声明**: `class TreeWidget : public QTreeWidget{`
- **Inherits / 继承**: `public QTreeWidget`

**Public Members / 公有成员**
- `TreeWidget(QWidget *parent)`
- `void drawBranches(QPainter *painter, const QRect &rect, const QModelIndex &index) const override`
- `void setBorderVisible(bool isVisible)`
- `void setBorderRadius(int radius)`
- `SmoothScrollDelegate *scrollDelagate`

#### TreeView

- **Declaration / 声明**: `class TreeView : public QTreeView{`
- **Inherits / 继承**: `public QTreeView`

**Public Members / 公有成员**
- `TreeView(QWidget *parent)`
- `void drawBranches(QPainter *painter, const QRect &rect, const QModelIndex &index) const override`
- `void setBorderVisible(bool isVisible)`
- `void setBorderRadius(int radius)`
- `SmoothScrollDelegate *scrollDelagate`
