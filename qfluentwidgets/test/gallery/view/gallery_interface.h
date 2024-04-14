#pragma once

#include <QtCore/Qt>
#include <QtCore/QUrl>
#include <QtCore/QEvent>
#include <QtGui/QDesktopServices>
#include <QtGui/QPainter>
#include <QtGui/QPen>
#include <QtGui/QColor>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QFrame>

#include "../config/gallery_config.h"
#include "../common/style_sheet.h"
#include "../../../common/icon.h"
#include "../../../common/config.h"
#include "../../../common/style_sheet.h"
#include "../../../common/signal_bus.h"
#include "../../../components/widgets/scroll_area.h"
#include "../../../components/widgets/button.h"
#include "../../../components/widgets/icon_widget.h"
#include "../../../components/widgets/tool_tip.h"
#include "../../../components/widgets/label.h"

class GallerySeparatorWidget : public QWidget{
    Q_OBJECT
public:
    GallerySeparatorWidget(QWidget *parent);
    void paintEvent(QPaintEvent *event) override;
};


class ToolBar : public QWidget{
    Q_OBJECT
public:
    ToolBar(QString title, QString subtitle, QWidget *parent);
    void __initWidget();

    TitleLabel *titleLabel;
    CaptionLabel *subtitleLabel;
    PushButton *documentButton;
    PushButton *sourceButton;
    ToolButton *themeButton;
    GallerySeparatorWidget *separator;
    ToolButton *supportButton;
    ToolButton *feedbackButton;
    QVBoxLayout *vBoxLayout;
    QHBoxLayout *buttonLayout;
};


class ExampleCard : public QWidget{
    Q_OBJECT
public:
    ExampleCard(QString title, QWidget *widget, QString sourcePath, int stretch, QWidget *parent);
    void __initWidget();
    void __initLayout();
    bool eventFilter(QObject *watched, QEvent *event) override;

    QWidget *widget;
    int stretch;
    StrongBodyLabel *titleLabel;
    QFrame *card;
    QFrame *sourceWidget;
    QString sourcePath;
    BodyLabel *sourcePathLabel;
    IconWidget *linkIcon;
    QVBoxLayout *vBoxLayout;
    QVBoxLayout *cardLayout;
    QHBoxLayout *topLayout;
    QHBoxLayout *bottomLayout;
};


class GalleryInterface : public ScrollArea{
    Q_OBJECT
public:
    GalleryInterface(QString title, QString subtitle, QWidget *parent);
    ExampleCard *addExampleCard(QString title, QWidget *widget, QString sourcePath, int stretch);
    void scrollToCard(int index);
    void resizeEvent(QResizeEvent *e) override;

    QWidget *view;
    ToolBar *toolBar;
    QVBoxLayout *vBoxLayout;

};