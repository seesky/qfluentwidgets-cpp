#include "line_edit.h"

LineEditButton::LineEditButton(QVariant *icon, QWidget *parent) : QToolButton(parent)
{
    this->_icon = new QVariant(*icon);
    this->isPressed = false;
    this->setFixedSize(31, 23);
    this->setIconSize(QSize(10, 10));
    this->setCursor(Qt::PointingHandCursor);
    this->setObjectName(QString("lineEditButton"));
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("LINE_EDIT"), Theme::AUTO);
}

void LineEditButton::mousePressEvent(QMouseEvent *e)
{
    this->isPressed = true;
    QToolButton::mousePressEvent(e);
}

void LineEditButton::mouseReleaseEvent(QMouseEvent *e)
{
    this->isPressed = false;
    QToolButton::mouseReleaseEvent(e);
}

void LineEditButton::paintEvent(QPaintEvent *e)
{
    QToolButton::paintEvent(e);
    QPainter painter(this);

    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    int iw = this->iconSize().width();
    int ih = this->iconSize().height();

    int w = this->width();
    int h = this->height();

    QRect *rect = new QRect((w - iw)/2, (h - ih)/2, iw, ih);

    if(this->isPressed){
        painter.setOpacity(0.7);
    }

    if(isDarkTheme()){
        MIcon().drawIcon(this->_icon, &painter, *rect, nullptr,  QIcon::State::Off);
    }else{
        std::map<QString, QString> attributes;
        attributes[QString("fill")] = QString("#656565");
        MIcon().drawIcon(this->_icon, &painter, *rect, &attributes,  QIcon::State::Off);
    }
}

LineEdit::LineEdit(QWidget *parent) : QLineEdit(parent)
{
    this->_isClearButtonEnabled = false;
    this->_completer = nullptr;
    this->_completerMenu = nullptr;

    this->setProperty("transparent", true);
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("LINE_EDIT"), Theme::AUTO);
    this->setFixedHeight(33);
    this->setAttribute(Qt::WA_MacShowFocusRect, false);
    Font().setFont(this, 14, QFont::Normal);

    this->hBoxLayout = new QHBoxLayout(this);

    FluentIcon *icon = new FluentIcon();
    icon->setIconName("CLOSE");
    QVariant __icon = QVariant::fromValue<FluentIcon>(*icon);
    this->clearButton = new LineEditButton(&__icon, this);

    this->clearButton->setFixedSize(29, 25);
    this->clearButton->hide();

    this->hBoxLayout->setSpacing(3);
    this->hBoxLayout->setContentsMargins(4, 4, 4, 4);
    this->hBoxLayout->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    this->hBoxLayout->addWidget(this->clearButton, 0, Qt::AlignRight);

    connect(this->clearButton, &QToolButton::clicked, this, &QLineEdit::clear);
    connect(this, &QLineEdit::textChanged, this, &LineEdit::__onTextChanged);
    connect(this, &QLineEdit::textEdited, this, &LineEdit::__onTextEdited);
}


void LineEdit::setClearButtonEnabled(bool enable)
{
    this->_isClearButtonEnabled = enable;
    this->setTextMargins(0, 0, 28 * enable, 0);
}

bool LineEdit::isClearButtonEnabled()
{
    return this->_isClearButtonEnabled;
}

void LineEdit::setCompleter(QCompleter *completer)
{
    this->_completer = completer;
}

QCompleter *LineEdit::completer()
{
    return this->_completer;
}

void LineEdit::focusOutEvent(QFocusEvent *e)
{
    QLineEdit::focusOutEvent(e);
    this->clearButton->hide();
}

void LineEdit::focusInEvent(QFocusEvent *e)
{
    QLineEdit::focusInEvent(e);
    if(this->isClearButtonEnabled()){
        this->clearButton->setVisible(!this->text().isEmpty());
    }
}

void LineEdit::__onTextChanged(QString text)
{
    if(this->isClearButtonEnabled()){
        this->clearButton->setVisible(!text.isEmpty() && this->hasFocus());
    }  
}

void LineEdit::__onTextEdited(QString text)
{
    if(!this->completer()){
        return;
    }

    if(!this->text().isEmpty()){
        QTimer().singleShot(50, this, &LineEdit::_showCompleterMenu);
    }else if(this->_completerMenu){
        this->_completerMenu->close();
    }
}

void LineEdit::setCompleterMenu(CompleterMenu *menu)
{
    connect(menu, &CompleterMenu::activated, this->_completer, QOverload<const QString&>::of(&QCompleter::activated)); //特殊关注
    //QObject::connect(menu, &CompleterMenu::activated, this->_completer, &QCompleter::activated);
    //connect(menu, &CompleterMenu::activated, this->_completer, &QCompleter::activated);
    this->_completerMenu = menu;
}

void LineEdit::_showCompleterMenu()
{
    if(!this->completer() || this->text().isEmpty()){
        return;
    }

    if(!this->_completerMenu){
        this->setCompleterMenu(new CompleterMenu(this));
    }

    this->completer()->setCompletionPrefix(this->text());
    QAbstractItemModel *itemModel = this->completer()->completionModel();
    bool changed = this->_completerMenu->setCompletion(itemModel);
    this->_completerMenu->setMaxVisibleItems(this->completer()->maxVisibleItems());

    if(changed){
        this->_completerMenu->popup();
    }
}



void LineEdit::contextMenuEvent(QContextMenuEvent *e)
{
    LineEditMenu *menu = new LineEditMenu(this);
    QPoint *qp = new QPoint(e->globalPos());
    menu->exec_(qp, true, MenuAnimationType::DROP_DOWN);
}


void LineEdit::paintEvent(QPaintEvent *e)
{
    
    QLineEdit::paintEvent(e);
    if(!this->hasFocus()){
        return;
    }

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    QMargins m = this->contentsMargins();
    QPainterPath *path = new QPainterPath();
    int w = this->width() - m.left() - m.right();
    int h = this->height();

    path->addRoundedRect(QRectF(m.left(), h - 10, w, 10), 5, 5);
    QPainterPath rectPath = QPainterPath();
    rectPath.addRect(m.left(), h - 10, w, 8);
    QPainterPath _path = path->subtracted(rectPath);
    painter.fillPath(_path, *(ThemeColor().themeColor()));
}


CompleterMenu::CompleterMenu(LineEdit *lineEdit) : RoundMenu(QString(), nullptr)
{
    this->items = new QStringList();
    this->lineEdit = lineEdit;

    this->view->publicSetViewportMargins(0, 2, 0, 6);
    this->view->setObjectName(QString("completerListWidget"));
    this->view->setItemDelegate(new IndicatorMenuItemDelegate(nullptr));
    this->view->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    this->installEventFilter(this);
    this->setItemHeight(33);
}

bool CompleterMenu::setCompletion(QAbstractItemModel *model)
{
    QStringList *items = new QStringList();
    for(int i = 0; i < model->rowCount(); i++){
        for(int j = 0; j < model->columnCount(); j++){
            items->append(model->data(model->index(i, j)).value<QString>()); //特殊关注
        }
    }

    if(this->items == items && this->isVisible()){
        return false;
    }

    this->setItems(items);
    return true;
}


void CompleterMenu::setItems(QStringList *items)
{
    this->view->clear();
    this->items = items;
    this->view->addItems(*items);

    for(int i = 0; i < this->view->count(); i++){
        QListWidgetItem *item = this->view->item(i);
        item->setSizeHint(QSize(1, this->itemHeight));
    }
}

void CompleterMenu::_onItemClicked(QListWidgetItem *item)
{
    this->_hideMenu(false);
    this->__onItemSelected(item->text());
}

bool CompleterMenu::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() != QEvent::KeyPress){
        return RoundMenu::eventFilter(watched, event);
    }

    this->lineEdit->event(event);
    this->view->event(event);

    QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
    if(keyEvent->key() == Qt::Key_Escape){
        this->close();
    }

    if((keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Return) && this->view->currentRow() >= 0){
        this->__onItemSelected(this->view->currentItem()->text());
        this->close();
    }
    return RoundMenu::eventFilter(watched, event);
}

void CompleterMenu::__onItemSelected(QString text)
{
    this->lineEdit->setText(text);
    emit(this->activated(text));
}

bool CompleterMenu::popup()
{
    if(this->items->isEmpty()){
        return this->close();
    }

    LineEdit *p = this->lineEdit;
    if(this->view->width() < p->width()){
        this->view->setMinimumWidth(p->width());
        this->adjustSize();
    }

    int x = -this->width() / 2 + this->layout()->contentsMargins().left() + p->width() / 2;
    int y = p->height() - this->layout()->contentsMargins().top() + 2;
    QPoint pd = p->mapToGlobal(QPoint(x, y));
    int hd = this->view->heightForAnimation(&pd, MenuAnimationType::FADE_IN_DROP_DOWN);

    QPoint pu = p->mapToGlobal(QPoint(x, 7));
    int hu = this->view->heightForAnimation(&pd, MenuAnimationType::FADE_IN_PULL_UP);

    QPoint *pos;
    MenuAnimationType aniType;
    if(hd >= hu){
        pos = new QPoint(pd);
        aniType = MenuAnimationType::FADE_IN_DROP_DOWN;
    }else{
        pos = new QPoint(pu);
        aniType = MenuAnimationType::FADE_IN_PULL_UP;
    }

    this->view->adjustSize(pos, aniType);

    this->view->setProperty("dropDown", QVariant::fromValue<MenuAnimationType>(aniType));
    this->view->setStyle(QApplication::style());
    this->view->update();

    this->adjustSize();
    this->exec(pos, true, aniType);

    this->view->setFocusPolicy(Qt::NoFocus);
    this->setFocusPolicy(Qt::NoFocus);
    p->setFocus();
    return true;
}

SearchLineEdit::SearchLineEdit(QWidget *parent) : LineEdit(parent)
{
    FluentIcon *icon = new FluentIcon();
    icon->setIconName(QString("SEARCH"));
    QVariant __icon = QVariant::fromValue<FluentIcon>(*icon);
    this->searchButton = new LineEditButton(&__icon, this);

    this->hBoxLayout->addWidget(this->searchButton, 0, Qt::AlignRight);
    this->setClearButtonEnabled(true);
    this->setTextMargins(0, 0, 59, 0);

    connect(this->searchButton, &LineEditButton::clicked, this, &SearchLineEdit::search);
    connect(this->clearButton, &LineEditButton::clicked, this, &SearchLineEdit::clearSignal);
}

void SearchLineEdit::search()
{
    QString text = this->text().trimmed();
    if(!text.isEmpty()){
        emit(this->searchSignal(text));
    }else{
        emit(this->clearSignal());
    }
}

void SearchLineEdit::setClearButtonEnabled(bool enable)
{
    this->_isClearButtonEnabled = enable;
    this->setTextMargins(0, 0, 28*enable+30, 0);
}

EditLayer::EditLayer(QWidget *parent) : QWidget(parent)
{
    this->setAttribute(Qt::WA_TransparentForMouseEvents);
    parent->installEventFilter(this);
}

bool EditLayer::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this->parent() && event->type() == QEvent::Resize){
        QResizeEvent *keyEvent = static_cast<QResizeEvent*>(event);
        this->resize(keyEvent->size());
    }
    return QWidget::eventFilter(watched, event);
}

void EditLayer::paintEvent(QPaintEvent *event)
{
    if(!((QWidget *)this->parent())->hasFocus()){
        return;
    }

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    QMargins m = this->contentsMargins();
    QPainterPath *path = new QPainterPath();
    int w = this->width() - m.left() - m.right();
    int h = this->height();
    path->addRoundedRect(QRectF(m.left(), h - 10, w, 10), 5, 5);

    QPainterPath *rectPath = new QPainterPath();
    rectPath->addRect(m.left(), h - 10, w, 7.5);
    QPainterPath _path = path->subtracted(*rectPath);
    painter.fillPath(_path, *(ThemeColor().themeColor())); 

}


TextEdit::TextEdit(QWidget *parent) : QTextEdit(parent)
{
    this->layer = new EditLayer(this);
    this->scrollDelegate = new SmoothScrollDelegate(this, false);
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("LINE_EDIT"), Theme::AUTO);
    Font().setFont(this, 14, QFont::Normal);
}

void TextEdit::contextMenuEvent(QContextMenuEvent *e)
{
    TextEditMenu *menu = new TextEditMenu(this);
    QPoint point = e->globalPos();
    menu->exec_(&point, true, MenuAnimationType::DROP_DOWN);
}

PlainTextEdit::PlainTextEdit(QWidget *parent) : QPlainTextEdit(parent)
{
    this->layer = new EditLayer(this);
    this->scrollDelegate = new SmoothScrollDelegate(this, false);
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("LINE_EDIT"), Theme::AUTO);
    Font().setFont(this, 14, QFont::Normal);
}

void PlainTextEdit::contextMenuEvent(QContextMenuEvent *e)
{
    TextEditMenu2QPlainTextEdit *menu = new TextEditMenu2QPlainTextEdit(this);
    QPoint point = e->globalPos();
    menu->exec_(&point, true, MenuAnimationType::DROP_DOWN);
}

PasswordLineEdit::PasswordLineEdit(QWidget *parent) : LineEdit(parent)
{
    FluentIcon *icon = new FluentIcon();
    icon->setIconName("VIEW");
    QVariant __icon = QVariant::fromValue<FluentIcon>(*icon);
    this->viewButton = new LineEditButton(&__icon, this);

    this->setEchoMode(QLineEdit::Password);
    this->setContextMenuPolicy(Qt::NoContextMenu);
    this->hBoxLayout->addWidget(this->viewButton, 0, Qt::AlignRight);
    this->setClearButtonEnabled(false);

    this->viewButton->installEventFilter(this);
    this->viewButton->setIconSize(QSize(13, 13));
    this->viewButton->setFixedSize(29, 25);
}

void PasswordLineEdit::setPasswordVisible(bool isVisible)
{
    if(isVisible){
        this->setEchoMode(QLineEdit::Normal);
    }else{
        this->setEchoMode(QLineEdit::Password);
    }
}

bool PasswordLineEdit::isPasswordVisible()
{
    return this->echoMode() == QLineEdit::Normal;
}

void PasswordLineEdit::setClearButtonEnabled(bool enable)
{
    this->_isClearButtonEnabled = enable;

    if(this->viewButton->isHidden()){
        this->setTextMargins(0, 0, 28*enable, 0);
    }else{
        this->setTextMargins(0, 0, 28*enable + 30, 0);
    }
}

void PasswordLineEdit::setViewPasswordButtonVisible(bool isVisible)
{
    this->viewButton->setVisible(isVisible);
}

bool PasswordLineEdit::eventFilter(QObject *watched, QEvent *event)
{
    if(watched != this->viewButton){
        return LineEdit::eventFilter(watched, event);
    }

    if(event->type() == QEvent::MouseButtonPress){
        this->setPasswordVisible(true);
    }else if(event->type() == QEvent::MouseButtonRelease){
        this->setPasswordVisible(false);
    }

    return LineEdit::eventFilter(watched, event);
}