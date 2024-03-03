#include "picker_base.h"

SeparatorWidget::SeparatorWidget(Qt::Orientation orient, QWidget *parent) : QWidget(parent)
{
    if(orient == Qt::Horizontal){
        this->setFixedHeight(1);
    }else{
        this->setFixedWidth(1);
    }

    this->setAttribute(Qt::WA_StyledBackground);
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("TIME_PICKER"), Theme::AUTO);
}


ItemMaskWidget::ItemMaskWidget(QList<CycleListWidget *> *listWidgets, QWidget *parent) : QWidget(parent)
{
    this->listWidgets = listWidgets;
    this->setFixedHeight(37);
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("TIME_PICKER"), Theme::AUTO);
}


void ItemMaskWidget::paintEvent(QPaintEvent *event)
{
    QPainter *painter = new QPainter(this);
    painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    painter->setPen(Qt::NoPen);
    painter->setBrush(*(ThemeColor().themeColor()));
    painter->drawRoundedRect(this->rect().adjusted(4, 0, -3, 0), 5, 5);

    painter->setPen(isDarkTheme() ? Qt::black : Qt::white);
    painter->setFont(this->font());
    int w = 0;
    int h = this->height();

    for(int i = 0; i < this->listWidgets->length(); i++){
        painter->save();

        int x = this->listWidgets->at(i)->itemSize->width() / 2 + 4 + this->x();
        QListWidgetItem *item1 = this->listWidgets->at(i)->itemAt(QPoint(x, this->y() + 6));
        if(item1 == nullptr){
            painter->restore();
            continue;
        }

        int iw = item1->sizeHint().width();
        int y = this->listWidgets->at(i)->visualItemRect(item1).y();
        painter->translate(w, y - this->y() + 7);
        this->_drawText(item1, painter, 0);

        QListWidgetItem *item2 = this->listWidgets->at(i)->itemAt(this->pos() + QPoint(x, h - 6));
        this->_drawText(item2, painter, h);

        painter->restore();

        w += (iw + 8);
    }

    painter->end();
}


void ItemMaskWidget::_drawText(QListWidgetItem *item, QPainter *painter, int y)
{
    int align = item->textAlignment();
    int w = item->sizeHint().width();
    int h = item->sizeHint().height();

    QRectF rect;

    if(align & Qt::AlignLeft){
        rect = QRectF(15, y, w, h);
    }else if(align & Qt::AlignRight){
        rect = QRectF(4, y, w - 15, h);
    }else if(align & Qt::AlignCenter){
        rect = QRectF(4, y, w, h);
    }

    painter->drawText(rect, align, item->text());
}


QString PickerColumnFormatter::encode(QVariant value)
{
    if(value.canConvert<QString>()){ //TODO:是否能处理所有的数据类型？
        return value.value<QString>(); 
    }else if(value.canConvert<int>()){
        return QString::number(value.value<int>());
    }
}

QVariant PickerColumnFormatter::decode(QString value)
{
    return QVariant::fromValue<QString>(value);
}

QVariant DigitFormatter::decode(QString value)
{
    return QVariant::fromValue<int>(value.toInt());
}


PickerColumnButton::PickerColumnButton(QString name, QList<QString> *items, int width, Qt::AlignmentFlag align, PickerColumnFormatter *formatter, QWidget *parent) : QPushButton(name, parent)
{
    this->_name = name;
    //this->_value = nullptr;

    this->setItems(items);
    this->setAlignment(align);
    this->setFormatter(formatter);
    this->setFixedSize(width, 30);
    this->setObjectName(QString("pickerButton"));
    this->setProperty("hasBorder", false);
    this->setAttribute(Qt::WA_TransparentForMouseEvents);
}

Qt::AlignmentFlag PickerColumnButton::align()
{
    return this->_align;
}


void PickerColumnButton::setAlignment(Qt::AlignmentFlag align)
{
    if(align == Qt::AlignLeft){
        this->setProperty("align", QString("left"));
    }else if(align == Qt::AlignRight){
        this->setProperty("align", QString("right"));
    }else{
        this->setProperty("align", QString("center"));
    }

    this->_align = align;
    this->setStyle(QApplication::style());
}


QString PickerColumnButton::value()
{
    if(this->_value.isNull()){
        return QString();
    }
    PickerColumnFormatter *p = this->formatter();
    return this->formatter()->encode(QVariant::fromValue<QString>(this->_value));
}

void PickerColumnButton::setValue(QString v)
{
    qDebug() << v;
    this->_value = v;
    if(v.isEmpty()){
        this->setText(this->name());
        this->setProperty("hasValue", false);
    }else{
        this->setText(this->value());
        this->setProperty("hasValue", true);
    }

    this->setStyle(QApplication::style());
}

QList<QVariant> *PickerColumnButton::items()
{
    QList<QVariant> *list = new QList<QVariant>();
    for(int i = 0; i < this->_items->length(); i++){
        qDebug() << this->_items->at(i);
        list->append(this->_formatter->encode(QVariant::fromValue<QString>(this->_items->at(i))));
    }
    return list;
}

void PickerColumnButton::setItems(QList<QString> *items)
{
    this->_items = items;
}


PickerColumnFormatter* PickerColumnButton::formatter()
{
    return this->_formatter;
}

void PickerColumnButton::setFormatter(PickerColumnFormatter *formatter)
{
    if(formatter != nullptr){
        this->_formatter = formatter;
    }else{
        this->_formatter = new PickerColumnFormatter();
    }
}

QString PickerColumnButton::name()
{
    return this->_name;
}

void PickerColumnButton::setName(QString name)
{
    if(this->text() == this->name()){
        this->setText(name);
    }

    this->_name = name;
}


PickerBase::PickerBase(QWidget *parent) : QPushButton(parent)
{
    this->columns = new QList<PickerColumnButton *>();
    this->hBoxLayout = new QHBoxLayout(this);

    this->hBoxLayout->setSpacing(0);
    this->hBoxLayout->setContentsMargins(0, 0, 0, 0);
    this->hBoxLayout->setSizeConstraint(QHBoxLayout::SetFixedSize);


    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("TIME_PICKER"), Theme::AUTO);
    connect(this, &QPushButton::clicked, this, &PickerBase::_showPanel);
}

void PickerBase::addColumn(QString name, QList<QString> *items, int width, Qt::AlignmentFlag align, PickerColumnFormatter *formatter)
{
    PickerColumnButton *button = new PickerColumnButton(name, items, width, align, formatter, this);
    this->columns->append(button);

    this->hBoxLayout->addWidget(button, 0, Qt::AlignLeft);

    for(int i = 0; i < this->columns->length() - 1; i++){
        this->columns->at(i)->setProperty("hasBorder", true);
        this->columns->at(i)->setStyle(QApplication::style());
    }
}

void PickerBase::setColumnAlignment(PickerBase *picker, int index, Qt::AlignmentFlag align)
{
    if(!(index >=0 && index < picker->columns->length())){
        return;
    }

    this->columns->at(index)->setAlignment(align);
}

void PickerBase::setColumnWidth(PickerBase *picker, int index, int width)
{
    if(!(index >=0 && index < picker->columns->length())){
        return;
    }
    this->columns->at(index)->setFixedWidth(width);
}

void PickerBase::setColumnTight(PickerBase *picker, int index)
{
    if(!(index >=0 && index < picker->columns->length())){
        return;
    }
    
    QFontMetrics fm = this->fontMetrics();
    
    int b = 0;
    for(int i = 0; i < this->columns->at(index)->items()->length(); i++){
        if(fm.width(i) > b){
            b = fm.width(i);
        }
    }
    int w = b + 30;
    this->setColumnWidth(picker, index, w);
}

void PickerBase::setColumnVisible(PickerBase *picker, int index, bool isVisible)
{
    if(!(index >=0 && index < picker->columns->length())){
        return;
    }

    this->columns->at(index)->setVisible(isVisible);
}

QList<QString> *PickerBase::value()
{
    QList<QString> *list = new QList<QString>();
    for(int i = 0; i < this->columns->length(); i++){
        if(this->columns->at(i)->isVisible()){
            list->append(this->columns->at(i)->value());
        }
    }
    return list;
}

QList<QString> *PickerBase::initialValue()
{
    //TODO:return [c.initialValue() for c in self.columns if c.isVisible()] 函数未使用
}

void PickerBase::setColumnValue(PickerBase *picker, int index, QString value)
{
    if(!(index >=0 && index < picker->columns->length())){
        return;
    }

    this->columns->at(index)->setValue(value);
}

void PickerBase::setColumnInitialValue(PickerBase *picker, int index, QString value)
{
    //TODO:self.columns[index].setInitialValue(value) 函数未使用
}

void PickerBase::setColumnFormatter(PickerBase *picker, int index, PickerColumnFormatter *formatter)
{
    if(!(index >=0 && index < picker->columns->length())){
        return;
    }

    this->columns->at(index)->setFormatter(formatter);
}


void PickerBase::setColumnItems(PickerBase *picker, int index, QList<QString> *items)
{
    if(!(index >=0 && index < picker->columns->length())){
        return;
    }
    this->columns->at(index)->setItems(items);
}

QString PickerBase::encodeValue(PickerBase *picker, int index, QString value)
{
    if(!(index >=0 && index < picker->columns->length())){
        return QString();
    }
    return this->columns->at(index)->formatter()->encode(QVariant::fromValue<QString>(value));
}

QVariant PickerBase::decodeValue(PickerBase *picker, int index, QString value)
{
    if(!(index >=0 && index < picker->columns->length())){
        return QString();
    }
    return this->columns->at(index)->formatter()->decode(value);
}

void PickerBase::setColumn(PickerBase *picker, int index, QString name, QList<QString> items, int width, Qt::AlignmentFlag align)
{
    if(!(index >=0 && index < picker->columns->length())){
        return;
    }
    PickerColumnButton *button = this->columns->at(index);
    button->setText(name);
    button->setFixedWidth(width);
    button->setAlignment(align);
}

void PickerBase::clearColumns()
{
    while(!columns->isEmpty()){
        PickerColumnButton *button = this->columns->back();
        this->hBoxLayout->removeWidget(button);
        this->columns->pop_back(); //TODO:特别关注删除顺序
        button->deleteLater();
    }
}

void PickerBase::enterEvent(QEvent *event)
{
    this->_setButtonProperty("enter", true);
}

void PickerBase::leaveEvent(QEvent *event)
{
    this->_setButtonProperty("enter", false);
}

void PickerBase::mousePressEvent(QMouseEvent *e)
{
    this->_setButtonProperty("pressed", true);
    QPushButton::mousePressEvent(e);
    this->_showPanel();
}

void PickerBase::mouseReleaseEvent(QMouseEvent *e)
{
    this->_setButtonProperty("pressed", false);
    QPushButton::mousePressEvent(e);
}

void PickerBase::_setButtonProperty(const char *name, bool value)
{
    for(int i = 0; i < this->columns->length(); i++){
        PickerColumnButton *button = this->columns->at(i);
        button->setProperty(name, QVariant::fromValue<bool>(value));
        button->setStyle(QApplication::style());
    }
}


QList<QString> * PickerBase::panelInitialValue()
{
    return this->value();
}

void PickerBase::_showPanel()
{
    PickerPanel *panel = new PickerPanel(this);
    for(int i = 0; i < this->columns->length(); i++){
        if(this->columns->at(i)->isVisible()){
            panel->addColumn(this->columns->at(i)->items(), this->columns->at(i)->width(), this->columns->at(i)->align());
        }
    }

    panel->setValue(this->panelInitialValue());

    connect(panel, &PickerPanel::confirmed, this, &PickerBase::_onConfirmed);
    connect(panel, &PickerPanel::columnValueChanged, this, [this, panel](int i, const QString &v) { //TODO:特别关注
        this->_onColumnValueChanged(panel, i, v);
    });

    int w = panel->vBoxLayout->sizeHint().width() - this->width();
    panel->exec(this->mapToGlobal(QPoint(-w / 2, -37 * 4)), true);

}


void PickerBase::_onConfirmed(QList<QString> *value)
{
    for(int i = 0; i < value->length(); i++){
        qDebug() << value->at(i);
        this->setColumnValue(this, i, value->at(i));
    }
}

void PickerBase::_onColumnValueChanged(PickerPanel *panel, int index, QString value)
{
    return;
}

void PickerToolButton::_drawIcon(QVariant *icon, QPainter *painter, QRect rect, QIcon::State state)
{
    if(this->isPressed){
        painter->setOpacity(1);
    }
    TransparentToolButton::_drawIcon(icon, painter, rect, QIcon::State::Off);
}

PickerPanel::PickerPanel(QWidget *parent) : QWidget(parent)
{
    this->itemHeight = 37;
    this->listWidgets = new QList<CycleListWidget *>();

    this->view = new QFrame(this);
    this->itemMaskWidget = new ItemMaskWidget(this->listWidgets, this);
    this->hSeparatorWidget = new SeparatorWidget(Qt::Horizontal, this->view);

    FluentIcon *iconYesButton = new FluentIcon();
    iconYesButton->setIconName(QString("ACCEPT"));
    this->yesButton = new PickerToolButton(iconYesButton, this->view);

    FluentIcon *iconCancelButton = new FluentIcon();
    iconCancelButton->setIconName(QString("CLOSE"));
    this->cancelButton = new PickerToolButton(iconCancelButton, this->view);

    this->hBoxLayout = new QHBoxLayout(this);
    this->listLayout = new QHBoxLayout();
    this->buttonLayout = new QHBoxLayout();
    this->vBoxLayout = new QVBoxLayout(this->view);

    this->__initWidget();
}


void PickerPanel::__initWidget()
{
    this->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    this->setShadowEffect(30, std::tuple<int, int>(0, 8), QColor(0, 0, 0, 30));
    this->yesButton->setIconSize(QSize(16, 16));
    this->cancelButton->setIconSize(QSize(13, 13));
    this->yesButton->setFixedHeight(33);
    this->cancelButton->setFixedHeight(33);

    this->hBoxLayout->setContentsMargins(12, 8, 12, 20);
    this->hBoxLayout->addWidget(this->view, 1, Qt::AlignCenter);
    this->hBoxLayout->setSizeConstraint(QHBoxLayout::SetMinimumSize);

    this->vBoxLayout->setSpacing(0);
    this->vBoxLayout->setContentsMargins(0, 0, 0, 0);
    this->vBoxLayout->addLayout(this->listLayout, 1);
    this->vBoxLayout->addWidget(this->hSeparatorWidget);
    this->vBoxLayout->addLayout(this->buttonLayout, 1);
    this->vBoxLayout->setSizeConstraint(QVBoxLayout::SetMinimumSize);

    this->buttonLayout->setSpacing(6);
    this->buttonLayout->setContentsMargins(3, 3, 3, 3);
    this->buttonLayout->addWidget(this->yesButton);
    this->buttonLayout->addWidget(this->cancelButton);
    this->yesButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->cancelButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    connect(this->yesButton, &PickerToolButton::clicked, this, &PickerPanel::_fadeOut);
    
    connect(this->yesButton, &PickerToolButton::clicked, this, [this]() {
        emit confirmed(this->value());
    });
    
    connect(this->cancelButton, &PickerToolButton::clicked, this, &PickerPanel::_fadeOut);

    this->view->setObjectName(QString("view"));
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("TIME_PICKER"), Theme::AUTO);
}


void PickerPanel::setShadowEffect(int blurRadius, std::tuple<int,int> offset, QColor color)
{
    this->shadowEffect = new QGraphicsDropShadowEffect(this->view);
    this->shadowEffect->setBlurRadius(blurRadius);
    this->shadowEffect->setOffset(std::get<0>(offset), std::get<1>(offset));
    this->shadowEffect->setColor(color);
    this->view->setGraphicsEffect(nullptr);
    this->view->setGraphicsEffect(this->shadowEffect);
}

void PickerPanel::addColumn(QList<QVariant> *items, int width, Qt::AlignmentFlag align)
{
    if(this->listWidgets != nullptr){
        this->listLayout->addWidget(new SeparatorWidget(Qt::Vertical, nullptr));
    }

    CycleListWidget *w = new CycleListWidget(items, new QSize(width, this->itemHeight), align, this);
    connect(w->vScrollBar, &SmoothScrollBar::valueChanged, this->itemMaskWidget, [this](){  //特殊关注绑定情况
        emit this->itemMaskWidget->update();
    });

    int N = this->listWidgets->length();
    connect(w, &CycleListWidget::currentItemChanged, this, [=](QListWidgetItem *item) {  //特殊关注绑定情况
        int n = N; // 捕获局部变量 N
        emit columnValueChanged(n, item->text());
    });

    this->listWidgets->append(w);
    this->listLayout->addWidget(w);
}

void PickerPanel::resizeEvent(QResizeEvent *event)
{
    this->itemMaskWidget->resize(this->view->width() - 3, this->itemHeight);
    QMargins m =  this->hBoxLayout->contentsMargins();
    this->itemMaskWidget->move(m.left() + 2, m.top() + 148);
}

QList<QString> *PickerPanel::value()
{
    QList<QString> *list = new QList<QString>();
    for(int i = 0; i < this->listWidgets->length(); i++){
        list->append(this->listWidgets->at(i)->currentItem()->text());
    }
    return list;
}

void PickerPanel::setValue(QList<QString> *list)
{
    if(list->length() != this->listWidgets->length()){
        return;
    }

    for(int i = 0; i < list->length(); i++){
        this->listWidgets->at(i)->setSelectedItem(list->at(i));
    }
}

QString PickerPanel::columnValue(int index)
{
    if(!(index >= 0 && this->listWidgets->length() > index)){
        return QString();
    }

    return this->listWidgets->at(index)->currentItem()->text();
}

void PickerPanel::setColumnValue(int index, QString value)
{
    if(!(index >= 0 && this->listWidgets->length() > index)){
        return;
    }
    this->listWidgets->at(index)->setSelectedItem(value);
}

CycleListWidget * PickerPanel::column(int index)
{
    return this->listWidgets->at(index);
}

void PickerPanel::exec(QPoint pos, bool ani)
{
    if(this->isVisible()){
        return;
    }

    this->show();

    QRect rect = QApplication::screenAt(QCursor::pos())->availableGeometry();
    int w = this->width() + 5;
    int h = this->height();
    pos.setX(qMin(pos.x() - this->layout()->contentsMargins().left(), rect.right() - w));
    pos.setY(qMax(rect.top(), qMin(pos.y() - 4, rect.bottom() - h +5)));
    this->move(pos);

    if(!ani){
        return;
    }

    this->isExpanded = false;
    this->ani = new QPropertyAnimation(this->view, QString("windowOpacity").toUtf8(), this);
    connect(this->ani, &QPropertyAnimation::valueChanged, this, &PickerPanel::_onAniValueChanged);
    this->ani->setStartValue(0);
    this->ani->setEndValue(1);
    this->ani->setDuration(150);
    this->ani->setEasingCurve(QEasingCurve::OutQuad);
    this->ani->start();
}



void PickerPanel::_onAniValueChanged(QVariant opacity)
{
    float op = opacity.value<float>();
    QMargins m = this->layout()->contentsMargins();
    int w = this->view->width() + m.left() + m.right() + 120;
    float h = this->view->height() + m.top() + m.bottom() + 12;

    if(!this->isExpanded){
        int y = int(h / 2 * (1 - op));
        this->setMask(QRegion(0, y, w, h - y * 2));
    }else{
        int y = int(h / 3 * (1 - op));
        this->setMask(QRegion(0, y, w, h-y*2));
    }
}

void PickerPanel::_fadeOut()
{
    this->isExpanded = true;
    this->ani = new QPropertyAnimation(this, QString("windowOpacity").toUtf8(), this);
    connect(this->ani, &QPropertyAnimation::valueChanged, this, &PickerPanel::_onAniValueChanged);
    connect(this->ani, &QPropertyAnimation::finished, this, &PickerPanel::deleteLater);
    this->ani->setStartValue(1);
    this->ani->setEndValue(0);
    this->ani->setDuration(150);
    this->ani->setEasingCurve(QEasingCurve::OutQuad);
    this->ani->start();
}