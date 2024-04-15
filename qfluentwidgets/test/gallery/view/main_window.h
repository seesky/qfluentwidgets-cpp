#pragma once

#include <QtCore/Qurl>
#include <QtCore/QSize>
#include <QtGui/QIcon>
#include <QtGui/QDesktopServices>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>

#include "../../../components/navigation/navigation_widget.h"
#include "../../../components/navigation/navigation_panel.h"
#include "../../../components/dialog_box/dialog.h"
#include "../../../window/fluent_window.h"
#include "../../../window/splash_screen.h"
#include "../../../common/icon.h"
#include "../../../common/config.h"
#include "../../../common/signal_bus.h"
#include "../common/translator.h"
#include "../config/gallery_config.h"
#include "basic_input_interface.h"
#include "date_time_interface.h"
#include "dialog_interface.h"
#include "layout_interface.h"
#include "material_interface.h"
#include "menu_interface.h"
#include "navigation_view_interface.h"


class MainWindow : public FluentWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent);
    void connectSignalToSlot();
    void initNavigation();
    void initWindow();
    void resizeEvent(QResizeEvent *event);

    SplashScreen *splashScreen;
    BasicInputInterface *basicInputInterface;
    DateTimeInterface *dateTimeInterface;
    DialogInterface *dialogInterface;
    LayoutInterface *layoutInterface;
    MaterialInterface *materialInterface;
    MenuInterface *menuInterface;
    NavigationViewInterface *navigationViewInterface;

public slots:
    void switchToSample(QString routeKey, int index);
    void onSupport();
};
