#pragma once

#include <QtCore/Qt>
#include <QtCore/QVariant>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QPoint>
#include <QtCore/QParallelAnimationGroup>
#include <QtCore/QEasingCurve>
#include <QtCore/QMargins>
#include <QtCore/QRectF>
#include <QtCore/QObject>
#include <QtCore/QSize>
#include <QtGui/QPixmap>
#include <QtGui/QPainter>
#include <QtGui/QColor>
#include <QtGui/QCursor>
#include <QtGui/QIcon>
#include <QtGui/QImage>
#include <QtGui/QPainterPath>
#include <QtGui/QBrush>
#include <QtGui/QMovie>
#include <QtGui/QImageReader>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QtWidgets/QLabel>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QApplication>

#include "../../common/auto_wrap.h"
#include "../../common/style_sheet.h"
#include "../../common/icon.h"
#include "icon_widget.h"
#include "button.h"
#include "label.h"

enum class FlyoutAnimationType{
    PULL_UP = 0,
    DROP_DOWN = 1,
    SLIDE_LEFT = 2,
    SLIDE_RIGHT = 3,
    FADE_IN = 4,
    NONE = 5
};

class IconWidgetForFlyout : public IconWidget{
    Q_OBJECT
public:
    IconWidgetForFlyout(QWidget *parent) : IconWidget(parent){
        this->setFixedSize(36, 54);
    };
    IconWidgetForFlyout(QVariant *icon, QWidget *parent);
    IconWidgetForFlyout(FluentIcon icon, QWidget *parent);
    IconWidgetForFlyout(QIcon icon, QWidget *parent);
    IconWidgetForFlyout(QString icon, QWidget *parent);

    void paintEvent(QPaintEvent *event) override;
};


class FlyoutViewBase : public QWidget{
    Q_OBJECT
public:
    FlyoutViewBase(QWidget *parent);
    void addWidget(QWidget *widget, int stretch, Qt::AlignmentFlag align);
    QColor backgroundColor();
    QColor borderColor();
    void paintEvent(QPaintEvent *event) override;
};


class FlyoutView : public FlyoutViewBase{
    Q_OBJECT
public:
    FlyoutView(QString title, QString content, QVariant *icon, QVariant *image, bool isClosable, QWidget *parent);
    void __initWidgets();
    void __initLayout();
    void addWidget(QWidget *widget, int stretch, Qt::AlignmentFlag align);
    void __addImageToLayout();
    void _adjustText();
    void _adjustImage();
    void showEvent(QShowEvent *event) override;

    QVariant *icon;
    QString title;
    QVariant *image;
    QString content;
    bool isClosable;

    QVBoxLayout *vBoxLayout;
    QHBoxLayout *viewLayout;
    QVBoxLayout *widgetLayout;

    QLabel *titleLabel;
    QLabel *contentLabel;
    IconWidgetForFlyout *iconWidget;
    ImageLabel *imageLabel;
    TransparentToolButton *closeButton;
signals:
    void closed();
};

class FlyoutAnimationManager;
class Flyout : public QWidget{
    Q_OBJECT
public:
    Flyout(FlyoutViewBase *view, QWidget *parent, bool isDeleteOnClose);
    void setShadowEffect(int blurRadius, std::tuple<int,int> offset);
    void closeEvent(QCloseEvent *event) override;
    virtual void exec(QPoint pos, FlyoutAnimationType aniType);
    static Flyout* make(FlyoutViewBase *view, QVariant target, QWidget *parent, FlyoutAnimationType aniType, bool isDeleteOnClose);
    static Flyout* create(QString title, QString content, QVariant *icon, QVariant *image, bool isClosable, QVariant target, QWidget *parent, FlyoutAnimationType aniType, bool isDeleteOnClose);
    void fadeOut();

    FlyoutViewBase *view;
    QHBoxLayout *hBoxLayout;
    FlyoutAnimationManager *aniManger;
    bool isDeleteOnClose;
    QPropertyAnimation *fadeOutAni;
    QGraphicsDropShadowEffect *shadowEffect;
signals:
    void closed();
};



class FlyoutAnimationManager : public QObject{
    Q_OBJECT
public:
    FlyoutAnimationManager(Flyout *flyout);
    virtual void exec(QPoint pos);
    QPoint _adjustPosition(QPoint pos);
    virtual QPoint position(QWidget *target);
    static FlyoutAnimationManager* make(FlyoutAnimationType aniType, Flyout *flyout);

    QList<FlyoutAnimationManager*> managers;
    Flyout *flyout;
    QParallelAnimationGroup *aniGroup;
    QPropertyAnimation *slideAni;
    QPropertyAnimation *opacityAni;
};


class PullUpFlyoutAnimationManager : public FlyoutAnimationManager{
    Q_OBJECT
public:
    PullUpFlyoutAnimationManager(Flyout *flyout);
    QPoint position(QWidget *target) override;
    void exec(QPoint pos) override;
};



class DropDownFlyoutAnimationManager : public FlyoutAnimationManager{
    Q_OBJECT
public:
    DropDownFlyoutAnimationManager(Flyout *flyout);
    QPoint position(QWidget *target) override;
    void exec(QPoint pos) override;
};


class SlideLeftFlyoutAnimationManager : public FlyoutAnimationManager{
    Q_OBJECT
public:
    SlideLeftFlyoutAnimationManager(Flyout *flyout);
    QPoint position(QWidget *target) override;
    void exec(QPoint pos) override;
};


class SlideRightFlyoutAnimationManager : public FlyoutAnimationManager{
    Q_OBJECT
public:
    SlideRightFlyoutAnimationManager(Flyout *flyout);
    QPoint position(QWidget *target) override;
    void exec(QPoint pos) override;
};


class FadeInFlyoutAnimationManager : public FlyoutAnimationManager{
    Q_OBJECT
public:
    FadeInFlyoutAnimationManager(Flyout *flyout);
    QPoint position(QWidget *target) override;
    void exec(QPoint pos) override;
};


class DummyFlyoutAnimationManager : public FlyoutAnimationManager{
    Q_OBJECT
public:
    DummyFlyoutAnimationManager(Flyout *flyout);
    QPoint position(QWidget *target) override;
    void exec(QPoint pos) override;
};