#pragma once

#include <QtCore/Qt>
#include <QtCore/QModelIndex>
#include <QtCore/QPoint>
#include <QtCore/QSize>
#include <QtCore/QRectF>
#include <QtGui/QPixmap>
#include <QtGui/QPainter>
#include <QtGui/QColor>
#include <QtWidgets/QStyleOptionViewItem>
#include <QtWidgets/QStyle>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QListWidgetItem>
#include <QtWidgets/QStyledItemDelegate>
#include <QtWidgets/QToolButton>

#include "../../common/icon.h"
#include "../../common/style_sheet.h"
#include "button.h"
#include "tool_tip.h"
#include "scroll_bar.h"

enum class PipsScrollButtonDisplayMode{
    ALWAYS = 0,
    ON_HOVER = 1,
    NEVER = 2
};

class PipPagerScrollButton : public ToolButton{
    Q_OBJECT
public:
    PipPagerScrollButton(QWidget *parent);
    PipPagerScrollButton(FluentIcon *icon, QWidget *parent);
    PipPagerScrollButton(SpinIcon *icon, QWidget *parent);
    PipPagerScrollButton(QIcon *icon, QWidget *parent);
    PipPagerScrollButton(QString icon, QWidget *parent);
    void _postInit();
    void paintEvent(QPaintEvent *event);
};

class PipsPager;
class PipsDelegate : public QStyledItemDelegate{
    Q_OBJECT
public:
    PipsDelegate(QWidget *parent);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setPressedRow(int row);
    void setHoveredRow(int row);

    int hoveredRow;
    int pressedRow;
};


class PipsPager : public QListWidget{
    Q_OBJECT
    Q_PROPERTY(int visibleNumber READ getVisibleNumber WRITE setVisibleNumber)
    Q_PROPERTY(int pageNumber READ getPageNumber WRITE setPageNumber)
public:
    PipsPager(QWidget *parent);
    PipsPager(Qt::Orientation orientation, QWidget *parent);
    void _postInit();
    void setPageNumber(int n);
    int getPageNumber();
    int getVisibleNumber();
    void setVisibleNumber(int n);
    void scrollToItem(QListWidgetItem *item, QListWidget::ScrollHint hint);
    void adjustSize();
    bool isHorizontal();
    void setCurrentIndex(int index);
    bool isPreviousButtonVisible();
    bool isNextButtonVisible();
    int currentIndex();
    void setPreviousButtonDisplayMode(PipsScrollButtonDisplayMode mode);
    void setNextButtonDisplayMode(PipsScrollButtonDisplayMode mode);
    void mouseReleaseEvent(QMouseEvent *e) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void _updateScrollButtonVisibility();
    void wheelEvent(QWheelEvent *e) override;
    void resizeEvent(QResizeEvent *event) override;

    Qt::Orientation orientation;
    int _visibleNumber;
    bool isHover;
    PipsDelegate *delegate;
    SmoothScrollBar *scrollBar;
    PipPagerScrollButton *preButton;
    PipPagerScrollButton *nextButton;
    PipsScrollButtonDisplayMode previousButtonDisplayMode;
    PipsScrollButtonDisplayMode nextButtonDisplayMode;
signals:
    void currentIndexChanged(int);

public slots:
    void scrollNext();
    void scrollPrevious();    
    void _setPressedItem(QListWidgetItem *item);
    void _setHoveredItem(QListWidgetItem *item);
};


class HorizontalPipsPager : public PipsPager{
    Q_OBJECT
public:
    HorizontalPipsPager(QWidget *parent);
};


class VerticalPipsPager : public PipsPager{
    Q_OBJECT
public:
    VerticalPipsPager(QWidget *parent);
};