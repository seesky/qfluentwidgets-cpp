#pragma once

#include <QtCore/Qt>
#include <QtCore/QPoint>
#include <QtCore/QObject>
#include <QtCore/QPointF>
#include <QtCore/QTimer>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QEvent>
#include <QtGui/QPainter>
#include <QtGui/QColor>
#include <QtGui/QPainterPath>
#include <QtGui/QIcon>
#include <QtGui/QCursor>
#include <QtGui/QPolygonF>
#include <QtGui/QPixmap>
#include <QtGui/QImage>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsDropShadowEffect>
#include "../../common/icon.h"
#include "../../common/style_sheet.h"
#include "flyout.h"

enum class TeachingTipTailPosition{
    TOP = 0,
    BOTTOM = 1,
    LEFT = 2,
    RIGHT = 3,
    TOP_LEFT = 4,
    TOP_RIGHT = 5,
    BOTTOM_LEFT = 6,
    BOTTOM_RIGHT = 7,
    LEFT_TOP = 8,
    LEFT_BOTTOM = 9,
    RIGHT_TOP = 10,
    RIGHT_BOTTOM = 11,
    NONE = 12
};


enum class ImagePosition{
    TOP = 0,
    BOTTOM = 1,
    LEFT = 2,
    RIGHT = 3
};

class TeachingTipManager;
class TeachingTipView : public FlyoutView{
    Q_OBJECT
public:
    TeachingTipView(QString title, QString content, QVariant *icon, QVariant *image, bool isClosable, TeachingTipTailPosition tailPosition, QWidget *parent);
    void _adjustImage();
    void _addImageToLayout();
    void paintEvent(QPaintEvent *event) override;

    TeachingTipManager *manager;
    QHBoxLayout *hBoxLayout;
};


class TeachTipBubble : public QWidget{
    Q_OBJECT
public:
    TeachTipBubble(FlyoutViewBase *view, TeachingTipTailPosition tailPosition, QWidget *parent);
    void setView(FlyoutViewBase *view);
    void paintEvent(QPaintEvent *event) override;

    TeachingTipManager *manager;
    QHBoxLayout *hBoxLayout;
    FlyoutViewBase *view;
};




class TeachingTip : public QWidget{
    Q_OBJECT
public:
    TeachingTip(FlyoutViewBase *view, QWidget *target, int duration, TeachingTipTailPosition tailPosition, QWidget *parent, bool isDeleteOnClose);
    void setShadowEffect(int blurRadius, std::tuple<int, int> offset);
    void _fadeOut();
    void showEvent(QShowEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;
    void addWidget(QWidget *widget, int stretch, Qt::AlignmentFlag align);
    FlyoutViewBase *getView();
    void setView(FlyoutViewBase *view);
    static TeachingTip *make(FlyoutViewBase *view, QWidget *target, int duration, TeachingTipTailPosition tailPosition, QWidget *parent, bool isDeleteOnClose);
    static TeachingTip *create(QWidget *target, QString title, QString content, QVariant *icon, QVariant *image, bool isClosable, int duration, TeachingTipTailPosition tailPostion, QWidget *parent, bool isDeleteOnClose);

    QWidget *target;
    int duration;
    bool isDeleteOnClose;
    TeachingTipManager *manager;
    QHBoxLayout *hBoxLayout;
    QPropertyAnimation *opacityAni;
    TeachTipBubble *bubble;
    QGraphicsDropShadowEffect *shadowEffect;
};

class PopupTeachingTip : public TeachingTip{
    Q_OBJECT
public:
    PopupTeachingTip(FlyoutViewBase *view, QWidget *target, int duration, TeachingTipTailPosition tailPosition, QWidget *parent, bool isDeleteOnClose);
};



class TeachingTipManager : public QObject{
    Q_OBJECT
public:
    TeachingTipManager();
    virtual void doLayout(TeachTipBubble *tip);
    virtual ImagePosition imagePosition();
    QPoint position(TeachingTip *tip);
    virtual void draw(TeachTipBubble *tip, QPainter *painter);
    virtual QPoint _pos(TeachingTip *tip);
    static TeachingTipManager *make(TeachingTipTailPosition position);
};


class TopTailTeachingTipManager : public TeachingTipManager{
    Q_OBJECT
public:
    TopTailTeachingTipManager();
    void doLayout(TeachTipBubble *tip) override;
    ImagePosition imagePosition() override;
    void draw(TeachTipBubble *tip, QPainter *painter) override;
    QPoint _pos(TeachingTip *tip) override;
};




class BottomTailTeachingTipManager : public TeachingTipManager{
    Q_OBJECT
public:
    BottomTailTeachingTipManager();
    void doLayout(TeachTipBubble *tip) override;
    void draw(TeachTipBubble *tip, QPainter *painter) override;
    QPoint _pos(TeachingTip *tip) override;
};


class LeftTailTeachingTipManager : public TeachingTipManager{
    Q_OBJECT
public:
    LeftTailTeachingTipManager();
    void doLayout(TeachTipBubble *tip) override;
    ImagePosition imagePosition() override;
    void draw(TeachTipBubble *tip, QPainter *painter) override;
    QPoint _pos(TeachingTip *tip) override;
};



class RightTailTeachingTipManager : public TeachingTipManager{
    Q_OBJECT
public:
    RightTailTeachingTipManager();
    void doLayout(TeachTipBubble *tip) override;
    ImagePosition imagePosition() override;
    void draw(TeachTipBubble *tip, QPainter *painter) override;
    QPoint _pos(TeachingTip *tip) override;
};



class TopLeftTailTeachingTipManager : public TopTailTeachingTipManager{
    Q_OBJECT
public:
    TopLeftTailTeachingTipManager();
    void draw(TeachTipBubble *tip, QPainter *painter) override;
    QPoint _pos(TeachingTip *tip) override;
};


class TopRightTailTeachingTipManager : public TopTailTeachingTipManager{
    Q_OBJECT
public:
    TopRightTailTeachingTipManager();
    void draw(TeachTipBubble *tip, QPainter *painter) override;
    QPoint _pos(TeachingTip *tip) override;
};



class BottomLeftTailTeachingTipManager : public BottomTailTeachingTipManager{
    Q_OBJECT
public:
    BottomLeftTailTeachingTipManager();
    void draw(TeachTipBubble *tip, QPainter *painter) override;
    QPoint _pos(TeachingTip *tip) override;
};


class BottomRightTailTeachingTipManager : public BottomTailTeachingTipManager{
    Q_OBJECT
public:
    BottomRightTailTeachingTipManager();
    void draw(TeachTipBubble *tip, QPainter *painter) override;
    QPoint _pos(TeachingTip *tip) override;
};


class LeftTopTailTeachingTipManager : public LeftTailTeachingTipManager{
    Q_OBJECT
public:
    LeftTopTailTeachingTipManager();
    ImagePosition imagePosition() override;
    void draw(TeachTipBubble *tip, QPainter *painter) override;
    QPoint _pos(TeachingTip *tip) override;
};



class LeftBottomTailTeachingTipManager : public LeftTailTeachingTipManager{
    Q_OBJECT
public:
    LeftBottomTailTeachingTipManager();
    ImagePosition imagePosition() override;
    void draw(TeachTipBubble *tip, QPainter *painter) override;
    QPoint _pos(TeachingTip *tip) override;
};



class RightTopTailTeachingTipManager : public RightTailTeachingTipManager{
    Q_OBJECT
public:
    RightTopTailTeachingTipManager();
    ImagePosition imagePosition() override;
    void draw(TeachTipBubble *tip, QPainter *painter) override;
    QPoint _pos(TeachingTip *tip) override;
};


class RightBottomTailTeachingTipManager : public RightTailTeachingTipManager{
    Q_OBJECT
public:
    RightBottomTailTeachingTipManager();
    ImagePosition imagePosition() override;
    void draw(TeachTipBubble *tip, QPainter *painter) override;
    QPoint _pos(TeachingTip *tip) override;
};




