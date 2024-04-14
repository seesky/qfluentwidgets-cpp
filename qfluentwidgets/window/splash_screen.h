#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWIdgets/QGraphicsDropShadowEffect>

#include "../common/icon.h"
#include "../common/style_sheet.h"
#include "../components/widgets/icon_widget.h"
#include "../qframelesswindow/titlebar/titlebar.h"

class SplashScreen : public QWidget{
    Q_OBJECT
public:
    SplashScreen(QVariant *icon, QWidget *parent, bool enableShadow);
    void setIcon(QVariant *icon);
    QIcon icon();
    void setIconSize(QSize size);
    QSize iconSize();
    void setTitleBar(QWidget *titleBar);
    bool eventFilter(QObject *watched, QEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void finish();
    void paintEvent(QPaintEvent *event) override;

    QVariant *_icon;
    QSize _iconSize;
    QWidget *titleBar;
    IconWidget *iconWidget;
    QGraphicsDropShadowEffect *shadowEffect;
};