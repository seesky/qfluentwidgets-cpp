#pragma once

#include <QtCore/Qt>
#include <QtCore/QRectF>
#include <QtGui/QPixmap>
#include <QtGui/QPainter>
#include <QtGui/QColor>
#include <QtGui/QBrush>
#include <QtGui/QPainterPath>
#include <QtGui/QLinearGradient>
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>

#include "../../../components/widgets/scroll_area.h"
#include "../../../common/config.h"
#include "../../../common/icon.h"
#include "../components/link_card.h"
#include "../components/sample_card.h"
#include "../../../common/style_sheet.h"

class BannerWidget : public QWidget{
    Q_OBJECT
public:
    BannerWidget(QWidget *parent);
    void paintEvent(QPaintEvent *event) override;

    QVBoxLayout *vBoxLayout;
    QLabel *galleryLabel;
    QPixmap banner;
    LinkCardView *linkCardView;

};


class HomeInterface : public ScrollArea{
    Q_OBJECT
public:
    HomeInterface(QWidget *parent);
    void __initWidget();
    void loadSamples();

    BannerWidget *banner;
    QWidget *view;
    QVBoxLayout *vBoxLayout;
};