#include "spin_box.h"


SpinButton::SpinButton(SpinIcon *icon, QWidget *parent) : QToolButton(parent)
{
    this->isPressed = false;
    this->_icon = icon;
    this->setFixedSize(31, 23);
    this->setIconSize(QSize(10, 10));
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("SPIN_BOX"), Theme::AUTO);
}


void SpinButton::mousePressEvent(QMouseEvent *e)
{
    this->isPressed = true;
    QToolButton::mousePressEvent(e);
}


void SpinButton::mouseReleaseEvent(QMouseEvent *e)
{
    this->isPressed = false;
    QToolButton::mouseReleaseEvent(e);
}

void SpinButton::paintEvent(QPaintEvent *e)
{
    QToolButton::paintEvent(e);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    if(this->isPressed){
        painter.setOpacity(0.7);
    }

    this->_icon->render(&painter, QRect(10, 6.5, 11, 11), Theme::AUTO, 0, nullptr);
}


CompactSpinButton::CompactSpinButton(QWidget *parent) : QToolButton(parent)
{
    this->setFixedSize(26, 33);
    this->setCursor(Qt::IBeamCursor);
}


void CompactSpinButton::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    int x = (this->width() - 10) / 2;
    int s = 9;

    SpinIcon *upIcon = new SpinIcon();
    upIcon->setIconName(QString("UP"));
    upIcon->render(&painter, QRect(x, this->height() / 2 - s + 1, s, s), Theme::AUTO, 0, nullptr);

    SpinIcon *downIcon = new SpinIcon();
    downIcon->setIconName(QString("DOWN"));
    downIcon->render(&painter, QRect(x, this->height() / 2, s, s), Theme::AUTO, 0, nullptr);
}


SpinFlyoutView::SpinFlyoutView(QWidget *parent) : FlyoutViewBase(parent)
{
    SpinIcon *upIcon = new SpinIcon();
    upIcon->setIconName(QString("UP"));
    this->upButton = new TransparentToolButton(upIcon, this);

    SpinIcon *downIcon = new SpinIcon();
    downIcon->setIconName(QString("DOWN"));
    this->downButton = new TransparentToolButton(downIcon, this);

    this->vBoxLayout = new QVBoxLayout(this);

    this->upButton->setFixedSize(36, 36);
    this->downButton->setFixedSize(36, 36);
    this->upButton->setIconSize(QSize(13, 13));
    this->downButton->setIconSize(QSize(13, 13));

    this->vBoxLayout->setContentsMargins(6, 6, 6, 6);
    this->vBoxLayout->setSpacing(0);
    this->vBoxLayout->addWidget(this->upButton);
    this->vBoxLayout->addWidget(this->downButton);
}


void SpinFlyoutView::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    painter.setBrush(isDarkTheme() ? QColor(46, 46, 46) : QColor(249, 249, 249));
    painter.setPen(isDarkTheme() ? QColor(0, 0, 0, 51) : QColor(0, 0, 0, 15));

    QRect rect = this->rect().adjusted(1, 1, -1, -1);
    painter.drawRoundedRect(rect, 8, 8);
}


SpinBox::SpinBox(QWidget *parent) : QSpinBox(parent)
{
    this->spinBoxBaseInit();
    this->inlineSpinBoxBaseInit();
}

void SpinBox::spinBoxBaseInit()
{
    this->hBoxLayout = new QHBoxLayout(this);

    this->setProperty("transparent", true);
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("SPIN_BOX"), Theme::AUTO);
    this->setButtonSymbols(QSpinBox::NoButtons);
    this->setFixedHeight(33);
    Font().setFont(this, 14, QFont::Normal);

    this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QSpinBox::customContextMenuRequested, this, &SpinBox::_showContextMenu);
}

void SpinBox::inlineSpinBoxBaseInit()
{
    SpinIcon *upIcon = new SpinIcon();
    upIcon->setIconName(QString("UP"));
    this->upButton = new SpinButton(upIcon, this);

    SpinIcon *downIcon = new SpinIcon();
    downIcon->setIconName(QString("DOWN"));
    this->downButton = new SpinButton(downIcon, this);

    this->hBoxLayout->setContentsMargins(0, 4, 4, 4);
    this->hBoxLayout->setSpacing(5);
    this->hBoxLayout->addWidget(this->upButton, 0, Qt::AlignRight);
    this->hBoxLayout->addWidget(this->downButton, 0, Qt::AlignRight);
    this->hBoxLayout->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    connect(this->upButton, &SpinButton::clicked, this, &SpinBox::stepUp);
    connect(this->downButton, &SpinButton::clicked, this, &SpinBox::stepDown);
}


void SpinBox::_showContextMenu(QPoint pos)
{
    LineEditMenu *menu = new LineEditMenu(this->lineEdit());
    QPoint _pos = this->mapToGlobal(pos);
    menu->exec_(&_pos, true, MenuAnimationType::DROP_DOWN);
}   


void SpinBox::_drawBorderBottom()
{
    if(!this->hasFocus()){
        return;
    }

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    QPainterPath path = QPainterPath();
    int w = this->width();
    int h = this->height();
    path.addRoundedRect(QRectF(0, h - 10, w, 10), 5, 5);

    QPainterPath rectPath = QPainterPath();
    rectPath.addRect(0, h - 10, w, 8);
    path = path.subtracted(rectPath);

    painter.fillPath(path, *(ThemeColor().themeColor()));
}


void SpinBox::paintEvent(QPaintEvent *e)
{
    QSpinBox::paintEvent(e);
    this->_drawBorderBottom();
}


void SpinBox::setAccelerated(bool on)
{
    QSpinBox::setAccelerated(on);
    this->upButton->setAutoRepeat(on);
    this->downButton->setAutoRepeat(on);
}
///////////////CompactSpinBox//////////////////
CompactSpinBox::CompactSpinBox(QWidget *parent) : QSpinBox(parent)
{
    this->spinBoxBaseInit();
    this->compactSpinBoxBaseInit();
}

void CompactSpinBox::spinBoxBaseInit()
{
    this->hBoxLayout = new QHBoxLayout(this);

    this->setProperty("transparent", true);
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("SPIN_BOX"), Theme::AUTO);
    this->setButtonSymbols(QSpinBox::NoButtons);
    this->setFixedHeight(33);
    Font().setFont(this, 14, QFont::Normal);

    this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QSpinBox::customContextMenuRequested, this, &CompactSpinBox::_showContextMenu);
}

void CompactSpinBox::compactSpinBoxBaseInit()
{
    this->compactSpinButton = new CompactSpinButton(this);
    this->spinFlyoutView = new SpinFlyoutView(this);
    this->spinFlyout = new Flyout(this->spinFlyoutView, this, false);

    this->hBoxLayout->setContentsMargins(0, 0, 0, 0);
    this->hBoxLayout->addWidget(this->compactSpinButton, 0, Qt::AlignRight);
    this->hBoxLayout->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    connect(this->compactSpinButton, &CompactSpinButton::clicked, this, &CompactSpinBox::_showFlyout);
    connect(this->spinFlyoutView->upButton, &TransparentToolButton::clicked, this, &CompactSpinBox::stepUp);
    connect(this->spinFlyoutView->downButton, &TransparentToolButton::clicked, this, &CompactSpinBox::stepDown);
    this->spinFlyout->hide();
}


void CompactSpinBox::_showContextMenu(QPoint pos)
{
    LineEditMenu *menu = new LineEditMenu(this->lineEdit());
    QPoint _pos = this->mapToGlobal(pos);
    menu->exec_(&_pos, true, MenuAnimationType::DROP_DOWN);
}   


void CompactSpinBox::_drawBorderBottom()
{
    if(!this->hasFocus()){
        return;
    }

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    QPainterPath path = QPainterPath();
    int w = this->width();
    int h = this->height();
    path.addRoundedRect(QRectF(0, h - 10, w, 10), 5, 5);

    QPainterPath rectPath = QPainterPath();
    rectPath.addRect(0, h - 10, w, 8);
    path = path.subtracted(rectPath);

    painter.fillPath(path, *(ThemeColor().themeColor()));
}


void CompactSpinBox::paintEvent(QPaintEvent *e)
{
    QSpinBox::paintEvent(e);
    this->_drawBorderBottom();
}

void CompactSpinBox::focusInEvent(QFocusEvent *event)
{
    QSpinBox::focusInEvent(event);
    this->_showFlyout();
}


void CompactSpinBox::setAccelerated(bool on)
{
    QSpinBox::setAccelerated(on);
    this->spinFlyoutView->upButton->setAutoRepeat(on);
    this->spinFlyoutView->downButton->setAutoRepeat(on);
}

void CompactSpinBox::_showFlyout()
{
    if(this->spinFlyout->isVisible()){
        return;
    }

    int y = this->compactSpinButton->height() / 2 - 46;
    QPoint pos = this->compactSpinButton->mapToGlobal(QPoint(-12, y));

    this->spinFlyout->exec(pos, FlyoutAnimationType::FADE_IN);
}

///////////////DoubleSpinBox//////////////////
DoubleSpinBox::DoubleSpinBox(QWidget *parent) : QDoubleSpinBox(parent)
{
    this->spinBoxBaseInit();
    this->inlineSpinBoxBaseInit();
}

void DoubleSpinBox::spinBoxBaseInit()
{
    this->hBoxLayout = new QHBoxLayout(this);

    this->setProperty("transparent", true);
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("SPIN_BOX"), Theme::AUTO);
    this->setButtonSymbols(QSpinBox::NoButtons);
    this->setFixedHeight(33);
    Font().setFont(this, 14, QFont::Normal);

    this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QDoubleSpinBox::customContextMenuRequested, this, &DoubleSpinBox::_showContextMenu);
}

void DoubleSpinBox::inlineSpinBoxBaseInit()
{
    SpinIcon *upIcon = new SpinIcon();
    upIcon->setIconName(QString("UP"));
    this->upButton = new SpinButton(upIcon, this);

    SpinIcon *downIcon = new SpinIcon();
    downIcon->setIconName(QString("DOWN"));
    this->downButton = new SpinButton(downIcon, this);

    this->hBoxLayout->setContentsMargins(0, 4, 4, 4);
    this->hBoxLayout->setSpacing(5);
    this->hBoxLayout->addWidget(this->upButton, 0, Qt::AlignRight);
    this->hBoxLayout->addWidget(this->downButton, 0, Qt::AlignRight);
    this->hBoxLayout->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    connect(this->upButton, &SpinButton::clicked, this, &SpinBox::stepUp);
    connect(this->downButton, &SpinButton::clicked, this, &SpinBox::stepDown);
}


void DoubleSpinBox::_showContextMenu(QPoint pos)
{
    LineEditMenu *menu = new LineEditMenu(this->lineEdit());
    QPoint _pos = this->mapToGlobal(pos);
    menu->exec_(&_pos, true, MenuAnimationType::DROP_DOWN);
}   


void DoubleSpinBox::_drawBorderBottom()
{
    if(!this->hasFocus()){
        return;
    }

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    QPainterPath path = QPainterPath();
    int w = this->width();
    int h = this->height();
    path.addRoundedRect(QRectF(0, h - 10, w, 10), 5, 5);

    QPainterPath rectPath = QPainterPath();
    rectPath.addRect(0, h - 10, w, 8);
    path = path.subtracted(rectPath);

    painter.fillPath(path, *(ThemeColor().themeColor()));
}


void DoubleSpinBox::paintEvent(QPaintEvent *e)
{
    QDoubleSpinBox::paintEvent(e);
    this->_drawBorderBottom();
}


void DoubleSpinBox::setAccelerated(bool on)
{
    QDoubleSpinBox::setAccelerated(on);
    this->upButton->setAutoRepeat(on);
    this->downButton->setAutoRepeat(on);
}


///////////////CompactDoubleSpinBox//////////////////
CompactDoubleSpinBox::CompactDoubleSpinBox(QWidget *parent) : QDoubleSpinBox(parent)
{
    this->spinBoxBaseInit();
    this->compactSpinBoxBaseInit();
}

void CompactDoubleSpinBox::spinBoxBaseInit()
{
    this->hBoxLayout = new QHBoxLayout(this);

    this->setProperty("transparent", true);
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("SPIN_BOX"), Theme::AUTO);
    this->setButtonSymbols(QSpinBox::NoButtons);
    this->setFixedHeight(33);
    Font().setFont(this, 14, QFont::Normal);

    this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QDoubleSpinBox::customContextMenuRequested, this, &CompactDoubleSpinBox::_showContextMenu);
}

void CompactDoubleSpinBox::compactSpinBoxBaseInit()
{
    this->compactSpinButton = new CompactSpinButton(this);
    this->spinFlyoutView = new SpinFlyoutView(this);
    this->spinFlyout = new Flyout(this->spinFlyoutView, this, false);

    this->hBoxLayout->setContentsMargins(0, 0, 0, 0);
    this->hBoxLayout->addWidget(this->compactSpinButton, 0, Qt::AlignRight);
    this->hBoxLayout->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    connect(this->compactSpinButton, &CompactSpinButton::clicked, this, &CompactDoubleSpinBox::_showFlyout);
    connect(this->spinFlyoutView->upButton, &TransparentToolButton::clicked, this, &CompactSpinBox::stepUp);
    connect(this->spinFlyoutView->downButton, &TransparentToolButton::clicked, this, &CompactSpinBox::stepDown);
    this->spinFlyout->hide();
}


void CompactDoubleSpinBox::_showContextMenu(QPoint pos)
{
    LineEditMenu *menu = new LineEditMenu(this->lineEdit());
    QPoint _pos = this->mapToGlobal(pos);
    menu->exec_(&_pos, true, MenuAnimationType::DROP_DOWN);
}   


void CompactDoubleSpinBox::_drawBorderBottom()
{
    if(!this->hasFocus()){
        return;
    }

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    QPainterPath path = QPainterPath();
    int w = this->width();
    int h = this->height();
    path.addRoundedRect(QRectF(0, h - 10, w, 10), 5, 5);

    QPainterPath rectPath = QPainterPath();
    rectPath.addRect(0, h - 10, w, 8);
    path = path.subtracted(rectPath);

    painter.fillPath(path, *(ThemeColor().themeColor()));
}


void CompactDoubleSpinBox::paintEvent(QPaintEvent *e)
{
    QDoubleSpinBox::paintEvent(e);
    this->_drawBorderBottom();
}

void CompactDoubleSpinBox::focusInEvent(QFocusEvent *event)
{
    QDoubleSpinBox::focusInEvent(event);
    this->_showFlyout();
}


void CompactDoubleSpinBox::setAccelerated(bool on)
{
    QDoubleSpinBox::setAccelerated(on);
    this->spinFlyoutView->upButton->setAutoRepeat(on);
    this->spinFlyoutView->downButton->setAutoRepeat(on);
}

void CompactDoubleSpinBox::_showFlyout()
{
    if(this->spinFlyout->isVisible()){
        return;
    }

    int y = this->compactSpinButton->height() / 2 - 46;
    QPoint pos = this->compactSpinButton->mapToGlobal(QPoint(-12, y));

    this->spinFlyout->exec(pos, FlyoutAnimationType::FADE_IN);
}



///////////////TimeEdit//////////////////
TimeEdit::TimeEdit(QWidget *parent) : QTimeEdit(parent)
{
    this->spinBoxBaseInit();
    this->inlineSpinBoxBaseInit();
}

void TimeEdit::spinBoxBaseInit()
{
    this->hBoxLayout = new QHBoxLayout(this);

    this->setProperty("transparent", true);
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("SPIN_BOX"), Theme::AUTO);
    this->setButtonSymbols(QSpinBox::NoButtons);
    this->setFixedHeight(33);
    Font().setFont(this, 14, QFont::Normal);

    this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QTimeEdit::customContextMenuRequested, this, &TimeEdit::_showContextMenu);
}

void TimeEdit::inlineSpinBoxBaseInit()
{
    SpinIcon *upIcon = new SpinIcon();
    upIcon->setIconName(QString("UP"));
    this->upButton = new SpinButton(upIcon, this);

    SpinIcon *downIcon = new SpinIcon();
    downIcon->setIconName(QString("DOWN"));
    this->downButton = new SpinButton(downIcon, this);

    this->hBoxLayout->setContentsMargins(0, 4, 4, 4);
    this->hBoxLayout->setSpacing(5);
    this->hBoxLayout->addWidget(this->upButton, 0, Qt::AlignRight);
    this->hBoxLayout->addWidget(this->downButton, 0, Qt::AlignRight);
    this->hBoxLayout->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    connect(this->upButton, &SpinButton::clicked, this, &SpinBox::stepUp);
    connect(this->downButton, &SpinButton::clicked, this, &SpinBox::stepDown);
}


void TimeEdit::_showContextMenu(QPoint pos)
{
    LineEditMenu *menu = new LineEditMenu(this->lineEdit());
    QPoint _pos = this->mapToGlobal(pos);
    menu->exec_(&_pos, true, MenuAnimationType::DROP_DOWN);
}   


void TimeEdit::_drawBorderBottom()
{
    if(!this->hasFocus()){
        return;
    }

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    QPainterPath path = QPainterPath();
    int w = this->width();
    int h = this->height();
    path.addRoundedRect(QRectF(0, h - 10, w, 10), 5, 5);

    QPainterPath rectPath = QPainterPath();
    rectPath.addRect(0, h - 10, w, 8);
    path = path.subtracted(rectPath);

    painter.fillPath(path, *(ThemeColor().themeColor()));
}


void TimeEdit::paintEvent(QPaintEvent *e)
{
    QTimeEdit::paintEvent(e);
    this->_drawBorderBottom();
}


void TimeEdit::setAccelerated(bool on)
{
    QTimeEdit::setAccelerated(on);
    this->upButton->setAutoRepeat(on);
    this->downButton->setAutoRepeat(on);
}



///////////////CompactDoubleSpinBox//////////////////
CompactTimeEdit::CompactTimeEdit(QWidget *parent) : QTimeEdit(parent)
{
    this->spinBoxBaseInit();
    this->compactSpinBoxBaseInit();
}

void CompactTimeEdit::spinBoxBaseInit()
{
    this->hBoxLayout = new QHBoxLayout(this);

    this->setProperty("transparent", true);
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("SPIN_BOX"), Theme::AUTO);
    this->setButtonSymbols(QSpinBox::NoButtons);
    this->setFixedHeight(33);
    Font().setFont(this, 14, QFont::Normal);

    this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QTimeEdit::customContextMenuRequested, this, &CompactTimeEdit::_showContextMenu);
}

void CompactTimeEdit::compactSpinBoxBaseInit()
{
    this->compactSpinButton = new CompactSpinButton(this);
    this->spinFlyoutView = new SpinFlyoutView(this);
    this->spinFlyout = new Flyout(this->spinFlyoutView, this, false);

    this->hBoxLayout->setContentsMargins(0, 0, 0, 0);
    this->hBoxLayout->addWidget(this->compactSpinButton, 0, Qt::AlignRight);
    this->hBoxLayout->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    connect(this->compactSpinButton, &CompactSpinButton::clicked, this, &CompactTimeEdit::_showFlyout);
    connect(this->spinFlyoutView->upButton, &TransparentToolButton::clicked, this, &CompactSpinBox::stepUp);
    connect(this->spinFlyoutView->downButton, &TransparentToolButton::clicked, this, &CompactSpinBox::stepDown);
    this->spinFlyout->hide();
}


void CompactTimeEdit::_showContextMenu(QPoint pos)
{
    LineEditMenu *menu = new LineEditMenu(this->lineEdit());
    QPoint _pos = this->mapToGlobal(pos);
    menu->exec_(&_pos, true, MenuAnimationType::DROP_DOWN);
}   


void CompactTimeEdit::_drawBorderBottom()
{
    if(!this->hasFocus()){
        return;
    }

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    QPainterPath path = QPainterPath();
    int w = this->width();
    int h = this->height();
    path.addRoundedRect(QRectF(0, h - 10, w, 10), 5, 5);

    QPainterPath rectPath = QPainterPath();
    rectPath.addRect(0, h - 10, w, 8);
    path = path.subtracted(rectPath);

    painter.fillPath(path, *(ThemeColor().themeColor()));
}


void CompactTimeEdit::paintEvent(QPaintEvent *e)
{
    QTimeEdit::paintEvent(e);
    this->_drawBorderBottom();
}

void CompactTimeEdit::focusInEvent(QFocusEvent *event)
{
    QTimeEdit::focusInEvent(event);
    this->_showFlyout();
}


void CompactTimeEdit::setAccelerated(bool on)
{
    QTimeEdit::setAccelerated(on);
    this->spinFlyoutView->upButton->setAutoRepeat(on);
    this->spinFlyoutView->downButton->setAutoRepeat(on);
}

void CompactTimeEdit::_showFlyout()
{
    if(this->spinFlyout->isVisible()){
        return;
    }

    int y = this->compactSpinButton->height() / 2 - 46;
    QPoint pos = this->compactSpinButton->mapToGlobal(QPoint(-12, y));

    this->spinFlyout->exec(pos, FlyoutAnimationType::FADE_IN);
}



///////////////DateTimeEdit//////////////////
DateTimeEdit::DateTimeEdit(QWidget *parent) : QDateTimeEdit(parent)
{
    this->spinBoxBaseInit();
    this->inlineSpinBoxBaseInit();
}

void DateTimeEdit::spinBoxBaseInit()
{
    this->hBoxLayout = new QHBoxLayout(this);

    this->setProperty("transparent", true);
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("SPIN_BOX"), Theme::AUTO);
    this->setButtonSymbols(QSpinBox::NoButtons);
    this->setFixedHeight(33);
    Font().setFont(this, 14, QFont::Normal);

    this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QDateTimeEdit::customContextMenuRequested, this, &DateTimeEdit::_showContextMenu);
}

void DateTimeEdit::inlineSpinBoxBaseInit()
{
    SpinIcon *upIcon = new SpinIcon();
    upIcon->setIconName(QString("UP"));
    this->upButton = new SpinButton(upIcon, this);

    SpinIcon *downIcon = new SpinIcon();
    downIcon->setIconName(QString("DOWN"));
    this->downButton = new SpinButton(downIcon, this);

    this->hBoxLayout->setContentsMargins(0, 4, 4, 4);
    this->hBoxLayout->setSpacing(5);
    this->hBoxLayout->addWidget(this->upButton, 0, Qt::AlignRight);
    this->hBoxLayout->addWidget(this->downButton, 0, Qt::AlignRight);
    this->hBoxLayout->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    connect(this->upButton, &SpinButton::clicked, this, &SpinBox::stepUp);
    connect(this->downButton, &SpinButton::clicked, this, &SpinBox::stepDown);
}


void DateTimeEdit::_showContextMenu(QPoint pos)
{
    LineEditMenu *menu = new LineEditMenu(this->lineEdit());
    QPoint _pos = this->mapToGlobal(pos);
    menu->exec_(&_pos, true, MenuAnimationType::DROP_DOWN);
}   


void DateTimeEdit::_drawBorderBottom()
{
    if(!this->hasFocus()){
        return;
    }

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    QPainterPath path = QPainterPath();
    int w = this->width();
    int h = this->height();
    path.addRoundedRect(QRectF(0, h - 10, w, 10), 5, 5);

    QPainterPath rectPath = QPainterPath();
    rectPath.addRect(0, h - 10, w, 8);
    path = path.subtracted(rectPath);

    painter.fillPath(path, *(ThemeColor().themeColor()));
}


void DateTimeEdit::paintEvent(QPaintEvent *e)
{
    QDateTimeEdit::paintEvent(e);
    this->_drawBorderBottom();
}


void DateTimeEdit::setAccelerated(bool on)
{
    QDateTimeEdit::setAccelerated(on);
    this->upButton->setAutoRepeat(on);
    this->downButton->setAutoRepeat(on);
}




///////////////CompactDoubleSpinBox//////////////////
CompactDateTimeEdit::CompactDateTimeEdit(QWidget *parent) : QDateTimeEdit(parent)
{
    this->spinBoxBaseInit();
    this->compactSpinBoxBaseInit();
}

void CompactDateTimeEdit::spinBoxBaseInit()
{
    this->hBoxLayout = new QHBoxLayout(this);

    this->setProperty("transparent", true);
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("SPIN_BOX"), Theme::AUTO);
    this->setButtonSymbols(QSpinBox::NoButtons);
    this->setFixedHeight(33);
    Font().setFont(this, 14, QFont::Normal);

    this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QDateTimeEdit::customContextMenuRequested, this, &CompactDateTimeEdit::_showContextMenu);
}

void CompactDateTimeEdit::compactSpinBoxBaseInit()
{
    this->compactSpinButton = new CompactSpinButton(this);
    this->spinFlyoutView = new SpinFlyoutView(this);
    this->spinFlyout = new Flyout(this->spinFlyoutView, this, false);

    this->hBoxLayout->setContentsMargins(0, 0, 0, 0);
    this->hBoxLayout->addWidget(this->compactSpinButton, 0, Qt::AlignRight);
    this->hBoxLayout->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    connect(this->compactSpinButton, &CompactSpinButton::clicked, this, &CompactDateTimeEdit::_showFlyout);
    connect(this->spinFlyoutView->upButton, &TransparentToolButton::clicked, this, &CompactSpinBox::stepUp);
    connect(this->spinFlyoutView->downButton, &TransparentToolButton::clicked, this, &CompactSpinBox::stepDown);
    this->spinFlyout->hide();
}


void CompactDateTimeEdit::_showContextMenu(QPoint pos)
{
    LineEditMenu *menu = new LineEditMenu(this->lineEdit());
    QPoint _pos = this->mapToGlobal(pos);
    menu->exec_(&_pos, true, MenuAnimationType::DROP_DOWN);
}   


void CompactDateTimeEdit::_drawBorderBottom()
{
    if(!this->hasFocus()){
        return;
    }

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    QPainterPath path = QPainterPath();
    int w = this->width();
    int h = this->height();
    path.addRoundedRect(QRectF(0, h - 10, w, 10), 5, 5);

    QPainterPath rectPath = QPainterPath();
    rectPath.addRect(0, h - 10, w, 8);
    path = path.subtracted(rectPath);

    painter.fillPath(path, *(ThemeColor().themeColor()));
}


void CompactDateTimeEdit::paintEvent(QPaintEvent *e)
{
    QDateTimeEdit::paintEvent(e);
    this->_drawBorderBottom();
}

void CompactDateTimeEdit::focusInEvent(QFocusEvent *event)
{
    QDateTimeEdit::focusInEvent(event);
    this->_showFlyout();
}


void CompactDateTimeEdit::setAccelerated(bool on)
{
    QDateTimeEdit::setAccelerated(on);
    this->spinFlyoutView->upButton->setAutoRepeat(on);
    this->spinFlyoutView->downButton->setAutoRepeat(on);
}

void CompactDateTimeEdit::_showFlyout()
{
    if(this->spinFlyout->isVisible()){
        return;
    }

    int y = this->compactSpinButton->height() / 2 - 46;
    QPoint pos = this->compactSpinButton->mapToGlobal(QPoint(-12, y));

    this->spinFlyout->exec(pos, FlyoutAnimationType::FADE_IN);
}


///////////////DateEdit//////////////////
DateEdit::DateEdit(QWidget *parent) : QDateEdit(parent)
{
    this->spinBoxBaseInit();
    this->inlineSpinBoxBaseInit();
}

void DateEdit::spinBoxBaseInit()
{
    this->hBoxLayout = new QHBoxLayout(this);

    this->setProperty("transparent", true);
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("SPIN_BOX"), Theme::AUTO);
    this->setButtonSymbols(QSpinBox::NoButtons);
    this->setFixedHeight(33);
    Font().setFont(this, 14, QFont::Normal);

    this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QDateEdit::customContextMenuRequested, this, &DateEdit::_showContextMenu);
}

void DateEdit::inlineSpinBoxBaseInit()
{
    SpinIcon *upIcon = new SpinIcon();
    upIcon->setIconName(QString("UP"));
    this->upButton = new SpinButton(upIcon, this);

    SpinIcon *downIcon = new SpinIcon();
    downIcon->setIconName(QString("DOWN"));
    this->downButton = new SpinButton(downIcon, this);

    this->hBoxLayout->setContentsMargins(0, 4, 4, 4);
    this->hBoxLayout->setSpacing(5);
    this->hBoxLayout->addWidget(this->upButton, 0, Qt::AlignRight);
    this->hBoxLayout->addWidget(this->downButton, 0, Qt::AlignRight);
    this->hBoxLayout->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    connect(this->upButton, &SpinButton::clicked, this, &SpinBox::stepUp);
    connect(this->downButton, &SpinButton::clicked, this, &SpinBox::stepDown);
}


void DateEdit::_showContextMenu(QPoint pos)
{
    LineEditMenu *menu = new LineEditMenu(this->lineEdit());
    QPoint _pos = this->mapToGlobal(pos);
    menu->exec_(&_pos, true, MenuAnimationType::DROP_DOWN);
}   


void DateEdit::_drawBorderBottom()
{
    if(!this->hasFocus()){
        return;
    }

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    QPainterPath path = QPainterPath();
    int w = this->width();
    int h = this->height();
    path.addRoundedRect(QRectF(0, h - 10, w, 10), 5, 5);

    QPainterPath rectPath = QPainterPath();
    rectPath.addRect(0, h - 10, w, 8);
    path = path.subtracted(rectPath);

    painter.fillPath(path, *(ThemeColor().themeColor()));
}


void DateEdit::paintEvent(QPaintEvent *e)
{
    QDateEdit::paintEvent(e);
    this->_drawBorderBottom();
}


void DateEdit::setAccelerated(bool on)
{
    QDateEdit::setAccelerated(on);
    this->upButton->setAutoRepeat(on);
    this->downButton->setAutoRepeat(on);
}



///////////////CompactDateEdit//////////////////
CompactDateEdit::CompactDateEdit(QWidget *parent) : QDateEdit(parent)
{
    this->spinBoxBaseInit();
    this->compactSpinBoxBaseInit();
}

void CompactDateEdit::spinBoxBaseInit()
{
    this->hBoxLayout = new QHBoxLayout(this);

    this->setProperty("transparent", true);
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("SPIN_BOX"), Theme::AUTO);
    this->setButtonSymbols(QSpinBox::NoButtons);
    this->setFixedHeight(33);
    Font().setFont(this, 14, QFont::Normal);

    this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QDateEdit::customContextMenuRequested, this, &CompactDateEdit::_showContextMenu);
}

void CompactDateEdit::compactSpinBoxBaseInit()
{
    this->compactSpinButton = new CompactSpinButton(this);
    this->spinFlyoutView = new SpinFlyoutView(this);
    this->spinFlyout = new Flyout(this->spinFlyoutView, this, false);

    this->hBoxLayout->setContentsMargins(0, 0, 0, 0);
    this->hBoxLayout->addWidget(this->compactSpinButton, 0, Qt::AlignRight);
    this->hBoxLayout->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    connect(this->compactSpinButton, &CompactSpinButton::clicked, this, &CompactDateEdit::_showFlyout);
    connect(this->spinFlyoutView->upButton, &TransparentToolButton::clicked, this, &CompactSpinBox::stepUp);
    connect(this->spinFlyoutView->downButton, &TransparentToolButton::clicked, this, &CompactSpinBox::stepDown);
    this->spinFlyout->hide();
}


void CompactDateEdit::_showContextMenu(QPoint pos)
{
    LineEditMenu *menu = new LineEditMenu(this->lineEdit());
    QPoint _pos = this->mapToGlobal(pos);
    menu->exec_(&_pos, true, MenuAnimationType::DROP_DOWN);
}   


void CompactDateEdit::_drawBorderBottom()
{
    if(!this->hasFocus()){
        return;
    }

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    QPainterPath path = QPainterPath();
    int w = this->width();
    int h = this->height();
    path.addRoundedRect(QRectF(0, h - 10, w, 10), 5, 5);

    QPainterPath rectPath = QPainterPath();
    rectPath.addRect(0, h - 10, w, 8);
    path = path.subtracted(rectPath);

    painter.fillPath(path, *(ThemeColor().themeColor()));
}


void CompactDateEdit::paintEvent(QPaintEvent *e)
{
    QDateEdit::paintEvent(e);
    this->_drawBorderBottom();
}


void CompactDateEdit::focusInEvent(QFocusEvent *event)
{
    QDateEdit::focusInEvent(event);
    this->_showFlyout();
}


void CompactDateEdit::setAccelerated(bool on)
{
    QDateEdit::setAccelerated(on);
    this->spinFlyoutView->upButton->setAutoRepeat(on);
    this->spinFlyoutView->downButton->setAutoRepeat(on);
}

void CompactDateEdit::_showFlyout()
{
    if(this->spinFlyout->isVisible()){
        return;
    }

    int y = this->compactSpinButton->height() / 2 - 46;
    QPoint pos = this->compactSpinButton->mapToGlobal(QPoint(-12, y));

    this->spinFlyout->exec(pos, FlyoutAnimationType::FADE_IN);
}