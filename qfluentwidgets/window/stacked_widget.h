#pragma once

#include <QtCore/Qt>
#include <QtCore/QEasingCurve>
#include <QtWidgets/QFrame>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QAbstractScrollArea>
#include "../components/widgets/stacked_widget.h"

class StackedWidget : public QStackedWidget{
    Q_OBJECT
public:
    StackedWidget(QWidget *parent);
    void addWidget(QWidget *widget);
    QWidget *widget(int index);
    void setCurrentWidget(QWidget *widget, bool popOut);
    void setCurrentIndex(int index, bool popOut);
    int currentIndex();
    QWidget *currentWidget();
    int indexOf(QWidget *widget);
    int count();

    QHBoxLayout *hBoxLayout;
    PopUpAniStackedWidget *view;

signals:
    void currentChanged(int);
};