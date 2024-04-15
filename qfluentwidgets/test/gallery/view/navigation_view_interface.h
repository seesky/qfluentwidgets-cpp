#pragma once

#include <QtWidgets/QWidget>

#include "gallery_interface.h"
#include "../common/translator.h"
#include "../../../components/navigation/breadcrumb.h"
#include "../../../components/navigation/segmented_widget.h"
#include "../../../components/navigation/pivot.h"
#include "../../../components/widgets/tab_view.h"
#include "../../../components/widgets/check_box.h"
#include "../../../components/widgets/label.h"
#include "../../../components/widgets/spin_box.h"
#include "../../../components/widgets/combo_box.h"

class NavigationViewInterface : public GalleryInterface{
    Q_OBJECT
public:
    NavigationViewInterface(QWidget *parent);
    QWidget* createToggleToolWidget();
};


class PivotInterface : public QWidget{
    Q_OBJECT
public:
    PivotInterface(QWidget *parent);
    void addSubInterface(QLabel *widget, QString objectName, QString text);

    Pivot *pivot;
    QStackedWidget *stackedWidget;
    QVBoxLayout *vBoxLayout;
    QLabel *songInterface;
    QLabel *albumInterface;
    QLabel *artistInterface;

public slots:
    void onCurrentIndexChanged(int index);
};


class SegmentedInterface : public QWidget{
    Q_OBJECT
public:
    SegmentedInterface(QWidget *parent);
    void addSubInterface(QLabel *widget, QString objectName, QString text);

    SegmentedWidget *pivot;
    QStackedWidget *stackedWidget;
    QVBoxLayout *vBoxLayout;
    QLabel *songInterface;
    QLabel *albumInterface;
    QLabel *artistInterface;

public slots:
    void onCurrentIndexChanged(int index);
};




class TabInterface : public QWidget{
    Q_OBJECT
public:
    TabInterface(QWidget *parent);
    void __initWidget();
    void connectSignalToSlot();
    void initLayout();
    void addSubInterface(QLabel *widget, QString objectName, QString text, QVariant *icon);

    int tabCount;
    TabBar *tabBar;
    QStackedWidget *stackedWidget;
    QWidget *tabView;
    QFrame *controlPanel;
    CheckBox *movableCheckBox;
    CheckBox *scrollableCheckBox;
    CheckBox *shadowEnabledCheckBox;
    BodyLabel *tabMaxWidthLabel;
    SpinBox *tabMaxWidthSpinBox;
    BodyLabel *closeDisplayModeLabel;
    ComboBox *closeDisplayModeComboBox;

    QHBoxLayout *hBoxLayout;
    QVBoxLayout *vBoxLayout;
    QVBoxLayout *panelLayout;

    QLabel *songInterface;
    QLabel *albumInterface;
    QLabel *artistInterface;

public slots:
    void onDisplayModeChanged(int index);
    void onCurrentIndexChanged(int index);
    void addTab();
    void removeTab(int index);
};