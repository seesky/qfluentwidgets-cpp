#pragma once

#include <QtCore/Qt>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include "../../../components/widgets/card_widget.h"
#include "../../../components/widgets/icon_widget.h"
#include "../../../components/layout/flow_layout.h"
#include "../../../common/auto_wrap.h"
#include "../../../common/signal_bus.h"


class SampleCard : public CardWidget{
    Q_OBJECT
public:
    SampleCard(QVariant *icon, QString title, QString content, QString routeKey, int index, QWidget *parent);
    void mouseReleaseEvent(QMouseEvent *e) override;

    int index;
    QString routeKey;
    IconWidget *iconWidget;
    QLabel *titleLabel;
    QLabel *contentLabel;
    QHBoxLayout *hBoxLayout;
    QVBoxLayout *vBoxLayout;
};


class SampleCardView : public QWidget{
    Q_OBJECT
public:
    SampleCardView(QString title, QWidget *parent);
    void addSampleCard(QVariant *icon, QString title, QString content, QString routeKey, int index);

    QLabel *titleLabel;
    QVBoxLayout *vBoxLayout;
    FlowLayout *flowLayout;
};