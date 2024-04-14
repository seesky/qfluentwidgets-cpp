#pragma once

#include <QtCore/Qt>
#include <QtCore/QRectF>
#include <QtCore/QSize>
#include <QtCore/QModelIndex>
#include <QtCore/QDate>
#include <QtCore/QCalendar>
#include <QtCore/QEasingCurve>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QParallelAnimationGroup>
#include <QtCore/Qpoint>
#include <QtCore/QRect>
#include <QtCore/QStringListModel>
#include <QtGui/QPainter>
#include <QtGui/QColor>
#include <QtGui/QCursor>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QListWidgetItem>
#include <QtWidgets/QStyledItemDelegate>
#include <QtWidgets/QStyle>
#include <QtWidgets/QStyleOptionViewItem>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QtWidgets/QListView>
#include <QtWidgets/QLabel>
#include <QtCore/QSharedPointer>
#include <QtCore/QtMath>
#include <QtGui/QScreen>

#include "../../common/icon.h"
#include "../../common/style_sheet.h"
#include "../../common/font.h"
#include "../widgets/button.h"
#include "../widgets/scroll_bar.h"

class ScrollButton : public TransparentToolButton{
    Q_OBJECT
public:
    ScrollButton(FluentIcon *icon, QWidget *parent) : TransparentToolButton(icon, parent){};
    //ScrollButton(QIcon *icon, QWidget *parent) : TransparentToolButton(icon, parent){};
    //ScrollButton(QString icon, QWidget *parent) : TransparentToolButton(icon, parent){};
    
    /*
    ~ScrollButton(){
        delete this->_icon; //特殊关注
    };
    */
    void _drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state) override;
    void paintEvent(QPaintEvent *event) override;
};


class ScrollItemDelegate : public QStyledItemDelegate{
    Q_OBJECT
public:
    ScrollItemDelegate(QVariant min, QVariant max, QObject *parent);
    void setRange(QVariant min, QVariant max);
    void setPressedIndex(QModelIndex index);
    void setCurrentIndex(QModelIndex index);
    void setSelectedIndex(QModelIndex index);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void _drawBackground(QPainter *painter, QStyleOptionViewItem option, QModelIndex index) const;
    void _drawText(QPainter *painter, QStyleOptionViewItem option, QModelIndex index) const;
    virtual int _itemMargin() const;

    QFont font;
    QModelIndex pressedIndex;
    QModelIndex currentIndex;
    QModelIndex selectedIndex;
    QVariant min;
    QVariant max;
};


class YearScrollItemDelegate : public ScrollItemDelegate{
    Q_OBJECT
public:
    YearScrollItemDelegate(QVariant min, QVariant max, QObject *parent) : ScrollItemDelegate(min, max, parent){};
    int _itemMargin() const override;
};


class DayScrollItemDelegate : public ScrollItemDelegate{
    Q_OBJECT
public:
    DayScrollItemDelegate(QVariant min, QVariant max, QObject *parent) : ScrollItemDelegate(min, max, parent){};
    int _itemMargin() const override;
};


class ScrollViewBase : public QListWidget{
    Q_OBJECT
public:public:

    ScrollViewBase(QWidget *parent);
    void __initWidget();
    void scrollUp();
    void scrollDown();
    virtual void scrollToPage(int page);
    virtual std::tuple<QVariant, QVariant> currentPageRange();
    virtual void setDate(QDate date);
    virtual void scrollToDate(QDate date);
    void _setPressedIndex(QModelIndex index);
    void _setSelectedIndex(QModelIndex index);
    void wheelEvent(QWheelEvent *e);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    virtual QSize gridSize();

    int cols;
    int pageRows;
    int currentPage;
    SmoothScrollBar *vScrollBar;
    ScrollItemDelegate *delegate;
    QDate currentDate;
    QDate date;
    int minYear;
    int maxYear;

public slots:
    void _onFirstScrollFinished();
};


class CalendarViewBase : public QFrame{
    Q_OBJECT
public:
    CalendarViewBase(QWidget *parent);
    void __initWidget();
    void setScrollView(ScrollViewBase *view);
    void setDate(QDate date);
    void setTitle(QString title);
    virtual QDate currentPageDate();
    virtual void _updateTitle();
    ~CalendarViewBase();
    QPushButton *titleButton;
    ScrollButton *upButton;
    ScrollButton *downButton;

    ScrollViewBase *scrollView;

    QHBoxLayout *hBoxLayout;
    QVBoxLayout *vBoxLayout;
signals:
    void titleClicked();
    void itemClicked(QDate);

public slots:
    void _onScrollUp();
    void _onScrollDown();
    void itemClickedEmit(QListWidgetItem *);
};


class YearScrollView : public ScrollViewBase{
    Q_OBJECT
public:
    YearScrollView(QWidget *parent);
    void _initItems();
    void scrollToDate(QDate date) override;
    std::tuple<QVariant, QVariant> currentPageRange() override;
};

class YearCalendarView : public CalendarViewBase{
    Q_OBJECT
public:
    YearCalendarView(QWidget *parent);
    void _updateTitle() override;
};


class MonthScrollView : public ScrollViewBase{
    Q_OBJECT
public:
    MonthScrollView(QWidget *parent);
    void _initItems();
    void scrollToDate(QDate date) override;
    std::tuple<QVariant, QVariant> currentPageRange() override;

    QStringList months;
};


class MonthCalendarView : public CalendarViewBase{
    Q_OBJECT
public:
    MonthCalendarView(QWidget *parent);
    void _updateTitle() override;
    QDate currentPageDate() override;
};


class DayScrollView : public ScrollViewBase{
    Q_OBJECT
public:
    DayScrollView(QWidget *parent);
    QSize gridSize() override;
    void _initItems();
    void setDate(QDate date) override;
    void scrollToDate(QDate date) override;
    void scrollToPage(int page) override;
    virtual std::tuple<QVariant, QVariant> currentPageRange() ;
    QDate _pageToDate();
    int _dateToRow(QDate date);
    void mouseReleaseEvent(QMouseEvent *event);

    int cols;
    int pageRows;
    QHBoxLayout *vBoxLayout;
    QStringList weekDays;

    QWidget *weekDayGroup;
    QHBoxLayout *weekDayLayout;
};

class DayCalendarView : public CalendarViewBase{
    Q_OBJECT
public:
    DayCalendarView(QWidget *parent);
    void _updateTitle() override;
    QDate currentPageDate() override;
    void scrollToDate(QDate date);
};


class CalendarView : public QWidget{
    Q_OBJECT
public:
    CalendarView(QWidget *parent);
    ~CalendarView();
    void __initWidget();
    void setShadowEffect(int blurRadius, std::tuple<int, int> offset, QColor color);
    void setDate(QDate date);
    void exec(QPoint pos, bool ani);
    //void closeEvent(QCloseEvent *event) override;
    QHBoxLayout *hBoxLayout;
    QDate date;
    QStackedWidget *stackedWidget;
    YearCalendarView *yearView;
    MonthCalendarView *monthView;
    DayCalendarView *dayView;
    QPropertyAnimation *opacityAni;
    QPropertyAnimation *slideAni;
    QParallelAnimationGroup *aniGroup;
    QGraphicsDropShadowEffect *shadowEffect;
signals:
    void dateChanged(QDate);

public slots:
    void _onDayViewTitleClicked();
    void _onMonthTitleClicked();
    void _onMonthItemClicked(QDate date);
    void _onYearItemClicked(QDate date);
    void _onDayItemClicked(QDate date);
};