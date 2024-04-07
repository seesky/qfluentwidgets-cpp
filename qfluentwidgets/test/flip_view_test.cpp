#include <QtCore/QModelIndex>
#include <QtCore/Qt>
#include <QtCore/QRect>
#include <QtCore/QSize>
#include <QtGui/QIcon>
#include <QtGui/QPainter>
#include <QtGui/QFont>
#include <QtGui/QColor>
#include <QtWidgets/QApplication>
#include <QtWidgets/QStyleOptionViewItem>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>

#include "../common/config.h"
#include "../common/style_sheet.h"
#include "../common/font.h"
#include "../components/widgets/pips_pager.h"
#include "../components/widgets/flip_view.h"

class CustomFlipItemDelegate : public FlipImageDelegate{
public:
    CustomFlipItemDelegate(QWidget *parent) : FlipImageDelegate(parent){

    }
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override{
        FlipImageDelegate::paint(painter, option, index);
        painter->save();

        painter->setBrush(QColor(255, 255, 255, 200));
        painter->setPen(Qt::NoPen);
        QRect rect = option.rect;
        rect = QRect(rect.x(), rect.y(), 200, rect.height());
        painter->drawRect(rect);

        painter->setPen(Qt::black);
        painter->setFont(Font().getFont(16, QFont::Bold));
        painter->drawText(rect, Qt::AlignCenter, QString("🥰\n硝子酱一级棒卡哇伊"));

        painter->restore();
    }
};


class Demo : public QWidget{
public:
    Demo(QWidget *parent) : QWidget(parent){
        this->flipView = new HorizontalFlipView(this);
        this->pager = new HorizontalPipsPager(this);

        this->flipView->setAspectRatioMode(Qt::AspectRatioMode::KeepAspectRatio);

        QList<QVariant *> flipImageList = QList<QVariant *>();
        flipImageList.append(new QVariant(QVariant::fromValue<QString>(QString("resource/shoko1.jpg"))));
        flipImageList.append(new QVariant(QVariant::fromValue<QString>(QString("resource/shoko2.jpg"))));
        flipImageList.append(new QVariant(QVariant::fromValue<QString>(QString("resource/shoko3.jpg"))));
        flipImageList.append(new QVariant(QVariant::fromValue<QString>(QString("resource/shoko4.jpg"))));
        this->flipView->addImages(flipImageList);

        this->pager->setPageNumber(this->flipView->count());

        connect(this->pager, &HorizontalPipsPager::currentIndexChanged, this->flipView, &HorizontalFlipView::setCurrentIndex);
        connect(this->flipView,&HorizontalFlipView::currentIndexChanged, this->pager, &HorizontalPipsPager::setCurrentIndex);

        this->vBoxLayout = new QVBoxLayout(this);
        this->vBoxLayout->addWidget(this->flipView, 0, Qt::AlignCenter);
        this->vBoxLayout->addWidget(this->pager, 0, Qt::AlignCenter);
        this->vBoxLayout->setAlignment(Qt::AlignCenter);
        this->vBoxLayout->setSpacing(20);
        this->resize(600, 600);
    }

    HorizontalFlipView *flipView;
    HorizontalPipsPager *pager;
    QVBoxLayout *vBoxLayout;
};


int main(int argc, char *argv[])
{
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    
    QApplication *app = new QApplication(argc, argv);
    Demo *w = new Demo(nullptr);
    w->show();
    return app->exec();
}