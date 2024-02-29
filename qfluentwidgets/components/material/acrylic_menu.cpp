#include "acrylic_menu.h"

AcrylicMenuActionListWidget::AcrylicMenuActionListWidget(QWidget *parent) : MenuActionListWidget(parent)
{
    this->acrylicBrush = new AcrylicBrush(this->viewport(), 35, QColor(242, 242, 242, 150), QColor(255, 255, 255, 10), 0.03);
    this->setViewportMargins(0, 0, 0, 0);
    this->setProperty("transparent", true);

    MenuActionListWidget::addItem(this->createPlaceholderItem(this->_topMargin()));
    MenuActionListWidget::addItem(this->createPlaceholderItem(this->_bottomMargin()));
}

void AcrylicMenuActionListWidget::_updateAcrylicColor()
{
    QColor tintColor;
    QColor luminosityColor;
    if(isDarkTheme()){
        tintColor = QColor(32, 32, 32, 200);
        luminosityColor = QColor(0, 0, 0, 0);
    }else{
        tintColor = QColor(255, 255, 255, 160);
        luminosityColor = QColor(255, 255, 255, 50);
    }

    this->acrylicBrush->tintColor = tintColor;
    this->acrylicBrush->luminosityColor = luminosityColor;
}

int AcrylicMenuActionListWidget::_topMargin()
{
    return 6;
}

int AcrylicMenuActionListWidget::_bottomMargin()
{
    return 6;
}

void AcrylicMenuActionListWidget::setItemHeight(int height)
{
    if(height == this->_itemHeight){
        return;
    }

    for(int i = 1; i < this->count() - 1; i++){
        QListWidgetItem *item = this->item(i);
        if(!this->itemWidget(item)){
            item->setSizeHint(QSize(item->sizeHint().width(), height));
        }
    }

    this->_itemHeight = height;
    this->adjustSize(nullptr, MenuAnimationType::NONE);
}


void AcrylicMenuActionListWidget::addItem(QListWidgetItem *item)
{
    return MenuActionListWidget::insertItem(this->count() - 1, item);
}

QListWidgetItem *AcrylicMenuActionListWidget::createPlaceholderItem(int height)
{
    QListWidgetItem *item = new QListWidgetItem();
    item->setSizeHint(QSize(1, height));
    item->setFlags(Qt::ItemFlag::NoItemFlags);
    return item;
}

QPainterPath AcrylicMenuActionListWidget::clipPath()
{
    QPainterPath path = QPainterPath();
    path.addRoundedRect(QRectF(this->rect()).adjusted(0, 0, -2.5, -2.5), 8, 8, Qt::AbsoluteSize);
    return path;
}

void AcrylicMenuActionListWidget::paintEvent(QPaintEvent *event)
{
    QPainter *painter = new QPainter(this->viewport());
    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    this->acrylicBrush->clipPath = this->clipPath();
    this->_updateAcrylicColor();
    this->acrylicBrush->paint();

    MenuActionListWidget::paintEvent(event);
}


AcrylicMenu::AcrylicMenu(QString title, QWidget *parent) : RoundMenu(title, parent)
{
    this->setUpMenu(new AcrylicMenuActionListWidget(this));
}

void AcrylicMenu::setUpMenu(AcrylicMenuActionListWidget *view)
{
    this->hBoxLayout->removeWidget(this->view);
    this->view->deleteLater();

    this->view = view;
    this->hBoxLayout->addWidget(this->view);

    this->setShadowEffect(30, std::tuple<int, int>(0, 8), new QColor(0, 0, 0, 30));

    connect(this->view, &MenuActionListWidget::itemClicked, this, &AcrylicMenu::_onItemClicked);
    connect(this->view, &MenuActionListWidget::itemEntered, this, &AcrylicMenu::_onItemEntered);
}

void AcrylicMenu::exec(QPoint *pos, bool ani, MenuAnimationType aniType)
{
    QPoint *p =  MenuAnimationManager().make(aniType, this)->_endPosition(pos);
    auto _view = qobject_cast<AcrylicMenuActionListWidget*>(this->view);
    _view->acrylicBrush->grabImage(QRect(*p, this->layout()->sizeHint()));
    RoundMenu::exec(pos, ani, aniType);
}

QPainterPath AcrylicCompleterMenuActionListWidget::clipPath()
{
    QPainterPath path = QPainterPath();
    path.setFillRule(Qt::FillRule::WindingFill);
    path.addRoundRect(QRectF(this->rect()).adjusted(1, 1, -2.5, -2.5), 8, 8);

    if(this->property("dropDown").value<bool>()){
        path.addRect(1, 1, 11, 11);
        path.addRect(this->width() - 12, 1, 11, 11);
    }else{
        path.addRect(1, this->height() - 11, 11, 11);
        path.addRect(this->width() - 12, this->height() - 11, 11, 11);
    }
    return path;
}

AcrylicCompleterMenu::AcrylicCompleterMenu(LineEdit *lineEdit) : CompleterMenu(lineEdit)
{
    this->setUpMenu(new AcrylicCompleterMenuActionListWidget(this));

    this->view->setObjectName(QString("completerListWidget"));
    this->view->setItemDelegate(new IndicatorMenuItemDelegate(this));
    this->view->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->setItemHeight(33);
}

void AcrylicCompleterMenu::setItems(QStringList *items)
{
    this->view->clear();

    this->items = items;

    auto _view = qobject_cast<AcrylicMenuActionListWidget*>(this->view);
    //QListWidget::addItem(new QListWidget());


}

void AcrylicCompleterMenu::setUpMenu(AcrylicCompleterMenuActionListWidget *view)
{
    this->hBoxLayout->removeWidget(this->view);
    this->view->deleteLater();

    this->view = view;
    this->hBoxLayout->addWidget(this->view);

    this->setShadowEffect(30, std::tuple<int, int>(0, 8), new QColor(0, 0, 0, 30));

    connect(this->view, &MenuActionListWidget::itemClicked, this, &AcrylicMenu::_onItemClicked);
    connect(this->view, &MenuActionListWidget::itemEntered, this, &AcrylicMenu::_onItemEntered);
}

void AcrylicCompleterMenu::exec(QPoint *pos, bool ani, MenuAnimationType aniType)
{
    QPoint *p =  MenuAnimationManager().make(aniType, this)->_endPosition(pos);
    auto _view = qobject_cast<AcrylicMenuActionListWidget*>(this->view);
    _view->acrylicBrush->grabImage(QRect(*p, this->layout()->sizeHint()));
    RoundMenu::exec(pos, ani, aniType);
}