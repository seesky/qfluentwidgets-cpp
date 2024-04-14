#include "combo_box.h"

ComboItem::ComboItem(QString text, QVariant *icon, QVariant *userData)
{
    this->text = text;
    this->userData = userData;
    this->_icon = icon;
}

QIcon ComboItem::getIcon()
{
    if(this->_icon == nullptr){
        return QIcon();
    }

    if(this->_icon->canConvert<QIcon>()){
        return this->_icon->value<QIcon>();
    }

    return *(this->_icon->value<FluentIcon>().icon(Theme::AUTO, nullptr));
}

ComboBox::ComboBox(QWidget *parent) : QPushButton(parent)
{
    this->isHover = false;
    this->isPressed = false;
    this->items = new QList<ComboItem *>();
    this->_currentIndex = -1;
    this->_maxVisibleItems = -1;
    this->dropMenu = nullptr;
    this->_placeholderText = QString();

    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("COMBO_BOX"), Theme::AUTO); //特殊关注
    this->installEventFilter(this);

    this->arrowAni = new TranslateYAnimation(this, 2);
    Font().setFont(this, 14, QFont::Normal);
}

bool ComboBox::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this){
        if(event->type() == QEvent::MouseButtonPress){
            this->isPressed = true;
        }else if(event->type() == QEvent::MouseButtonRelease){
            this->isPressed = false;
        }else if(event->type() == QEvent::Enter){
            this->isHover = true;
        }else if(event->type() == QEvent::Leave){
            this->isHover = false;
        }
    }

    return QObject::eventFilter(watched, event);
}

void ComboBox::addItem(QString text, QVariant *icon, QVariant *userData)
{
    ComboItem *item = new ComboItem(text, icon, userData);
    this->items->append(item);
    if(this->items->length() == 1){
        this->setCurrentIndex(0);
    }
}

void ComboBox::addItems(QList<QString> texts)
{
    for (int i = 0; i < texts.size(); ++i) {
        this->addItem(texts.at(i), nullptr, nullptr);
    }
}

void ComboBox::removeItem(int index)
{
    if(!(index >= 0 && index < items->length())){
        return;
    }

    this->items->removeAt(index);

    if(index < this->currentIndex()){
        this->_onItemClicked(this->_currentIndex - 1);
    }else if(index == this->currentIndex()){
        if(index > 0){
            this->_onItemClicked(this->_currentIndex - 1);
        }else{
            this->setCurrentIndex(0);
            emit(this->currentTextChanged(this->currentText()));
            emit(this->currentIndexChanged(0));
        }
    }

    if(this->count() == 0){
        this->clear();
    }
}


int ComboBox::currentIndex()
{
    return this->_currentIndex;
}

void ComboBox::setCurrentIndex(int index)
{

    if(index < 0){
        this->_currentIndex = -1;
        this->setPlaceholderText(this->_placeholderText);
    }else if(index >=0 && index < this->items->length()){
        this->_updateTextState(false);
        this->_currentIndex = index;
        this->setText(this->items->at(index)->text);
    }

}

void ComboBox::setText(QString text)
{
    QPushButton::setText(text);
    this->adjustSize();
}


QString ComboBox::currentText()
{
    if(!(this->currentIndex() >=0 && this->currentIndex() < this->items->length())){
        return nullptr;
    }

    return this->items->at(this->currentIndex())->text;
}

QVariant *ComboBox::currentData()
{
    if(!(this->currentIndex() >=0 && this->currentIndex() < this->items->length())){
        return nullptr;
    }

    return this->items->at(this->currentIndex())->userData; 
}

void ComboBox::setCurrentText(QString text)
{
    if(text == this->currentText()){
        return;
    }

    int index = this->findText(text);
    if(index >= 0){
        this->setCurrentIndex(index);
    }
}

void ComboBox::setItemText(int index, QString text)
{
    if(!(index >=0 && index < this->items->length())){
        return;
    }

    this->items->at(index)->text = text;
    if(this->currentIndex() == index){
        this->setText(text);
    }
}

QVariant *ComboBox::itemData(int index)
{
    if(!(index >=0 && index < this->items->length())){
        return nullptr;
    }

    return this->items->at(index)->userData;
}

QString ComboBox::itemText(int index)
{
    if(!(index >=0 && index < this->items->length())){
        return nullptr;
    }

    return this->items->at(index)->text;
}

QVariant *ComboBox::itemIcon(int index)
{
    if(!(index >=0 && index < this->items->length())){
        return nullptr;
    }

    return this->items->at(index)->_icon;
}

void ComboBox::setItemData(int index, QVariant *value)
{
    if(!(index >=0 && index < this->items->length())){
        return;
    }

    this->items->at(index)->userData = value;
}


void ComboBox::setItemIcon(int index, QVariant *icon)
{
    if(!(index >=0 && index < this->items->length())){
        return;
    }
    this->items->at(index)->_icon = icon;
}

int ComboBox::findData(QVariant *data)
{
    for(int i = 0; i < this->items->size(); i++){
        if(this->items->at(i)->userData == data){
            return i;
        }
    }
    return -1;
}

int ComboBox::findText(QString text)
{
    for(int i = 0; i < this->items->size(); i++){
        if(this->items->at(i)->text == text){
            return i;
        }
    }
    return -1;
}

void ComboBox::clear()
{
    if(this->currentIndex() >= 0){
        this->setText(QString());
    }

    this->items->clear();
    this->_currentIndex = -1;
}

int ComboBox::count()
{
    return this->items->length();
}

void ComboBox::insertItem(int index, QString text, QVariant *icon = nullptr, QVariant *userData = nullptr)
{
    ComboItem *item = new ComboItem(text, icon, userData);
    this->items->insert(index, item);

    if(index <= this->currentIndex()){
        this->_onItemClicked(this->currentIndex() + 1);
    }
}

void ComboBox::insertItems(int index, QList<QString> texts)
{
    int pos = index;
    for(int i = 0; i < texts.size(); i++){
        ComboItem *item = new ComboItem(texts.at(i), nullptr, nullptr);
        this->items->insert(pos, item);
        pos += 1;
    }

    if(index <= this->currentIndex()){
        this->_onItemClicked(this->currentIndex() + pos - index);
    }
}

void ComboBox::setMaxVisibleItems(int num)
{
    this->_maxVisibleItems = num;
}

int ComboBox::maxVisibleItems()
{
    return this->_maxVisibleItems;
}

void ComboBox::_closeComboMenu()
{
    if(!this->dropMenu){
        return;
    }

    this->dropMenu->close();
    this->dropMenu = nullptr;
}

void ComboBox::_onDropMenuClosed()
{
    #ifdef Q_OS_WIN
        QPoint pos = this->mapFromGlobal(QCursor::pos());
        if(!this->rect().contains(pos)){
            this->dropMenu = nullptr;
        }
    #else
        this->dropMenu = nullptr;
    #endif
}


ComboBoxMenu *ComboBox::_createComboMenu()
{
    return new ComboBoxMenu(this);
}


void ComboBox::_showComboMenu()
{
    if(items->isEmpty()){
        return;
    }

    ComboBoxMenu *menu = this->_createComboMenu();
    for(int i = 0; i < this->items->length(); i++){
        QAction *action = new QAction(this->items->at(i)->getIcon(), this->items->at(i)->text, this);
        connect(action, &QAction::triggered, this, [this, i]() { //特别关注
                ComboBox::_onItemClicked(i);
        });

        menu->addAction(action);
    }

    if(menu->view->width() < this->width()){
        menu->view->setMinimumWidth(this->width());
        menu->adjustSize();
    }

    menu->setMaxVisibleItems(this->maxVisibleItems());
    connect(menu, &ComboBoxMenu::closedSignal, this, &ComboBox::_onDropMenuClosed);
    this->dropMenu = menu;

    if(this->currentIndex() >= 0 && !this->items->isEmpty()){
        menu->setDefaultAction(menu->actions().at(this->currentIndex()));
    }

    int x = -menu->width() / 2 + menu->layout()->contentsMargins().left() + this->width() / 2;
    QPoint pd = this->mapToGlobal(QPoint(x, this->height()));
    int hd = menu->view->heightForAnimation(&pd, MenuAnimationType::DROP_DOWN);

    QPoint pu = this->mapToGlobal(QPoint(x, 0));
    int hu = menu->view->heightForAnimation(&pd, MenuAnimationType::PULL_UP);

    if(hd >= hu){
        menu->view->adjustSize(&pd, MenuAnimationType::DROP_DOWN);
        menu->exec(&pd, true, MenuAnimationType::DROP_DOWN);
    }else{
        menu->view->adjustSize(&pu, MenuAnimationType::PULL_UP);
        menu->exec(&pu, true, MenuAnimationType::PULL_UP);
    }


}


void ComboBox::_toggleComboMenu()
{
    if(this->dropMenu){
        this->_closeComboMenu();
    }else{
        this->_showComboMenu();
    }
}

void ComboBox::_onItemClicked(int index)
{
    if(index == this->currentIndex()){
        return;
    }

    this->setCurrentIndex(index);
    emit(this->currentTextChanged(this->currentText()));
    emit(this->currentIndexChanged(index));
}

void ComboBox::setPlaceholderText(QString text)
{
    this->_placeholderText = text;

    if(this->currentIndex() <= 0){
        this->_updateTextState(true);
        this->setText(text);
    }
}

void ComboBox::_updateTextState(bool isPlaceholder)
{
    if(this->property("isPlaceholderText") == isPlaceholder){
        return;
    }

    this->setProperty("isPlaceholderText", isPlaceholder);
    this->setStyle(QApplication::style());
}


void ComboBox::mouseReleaseEvent(QMouseEvent *e)
{
    QPushButton::mouseReleaseEvent(e);
    this->_toggleComboMenu();
}


void ComboBox::paintEvent(QPaintEvent *e)
{
    QPushButton::paintEvent(e);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    if(this->isPressed){
        painter.setOpacity(0.8);
    }else if(this->isPressed){
        painter.setOpacity(0.7);
    }

    QRect rect = QRect(this->width() - 22, this->height() / 2 - 5 + this->arrowAni->y(), 10, 10);

    if(isDarkTheme()){
        FluentIcon *icon = new FluentIcon();
        icon->setIconName(QString("ARROW_DOWN"));
        icon->render(&painter, rect, Theme::AUTO, 0, nullptr);
    }else{
        FluentIcon *icon = new FluentIcon();
        icon->setIconName(QString("ARROW_DOWN"));
        std::map<QString, QString> attributes;
        attributes[QString("fill")] = QString("#646464");
        icon->render(&painter, rect, Theme::AUTO, 0, &attributes);
    }
}



EditableComboBox::EditableComboBox(QWidget *parent) : LineEdit(parent)
{
    this->isHover = false;
    this->isPressed = false;
    this->items = new QList<ComboItem *>();
    this->_currentIndex = -1;
    this->_maxVisibleItems = -1;
    this->dropMenu = nullptr;
    this->_placeholderText = QString();

    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("LINE_EDIT"), Theme::AUTO); //特殊关注
    this->installEventFilter(this);

    FluentIcon *icon = new FluentIcon();
    icon->setIconName(QString("ARROW_DOWN"));
    QVariant __icon = QVariant::fromValue<FluentIcon>(*icon);
    this->dropButton = new LineEditButton(&__icon, this);

    this->setTextMargins(0, 0, 29, 0);
    this->dropButton->setFixedSize(30, 25);
    this->hBoxLayout->addWidget(this->dropButton, 0, Qt::AlignRight);

    connect(this->dropButton, &LineEditButton::clicked, this, &EditableComboBox::_toggleComboMenu);
    connect(this, &EditableComboBox::textEdited, this, &EditableComboBox::__onTextEdited);
    connect(this, &EditableComboBox::returnPressed, this, &EditableComboBox::_onReturnPressed);

    this->clearButton->disconnect();
    connect(this->clearButton, &LineEditButton::clicked, this, &EditableComboBox::_onClearButtonClicked);
}

bool EditableComboBox::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this){
        if(event->type() == QEvent::MouseButtonPress){
            this->isPressed = true;
        }else if(event->type() == QEvent::MouseButtonRelease){
            this->isPressed = false;
        }else if(event->type() == QEvent::Enter){
            this->isHover = true;
        }else if(event->type() == QEvent::Leave){
            this->isHover = false;
        }
    }

    return QObject::eventFilter(watched, event);
}

void EditableComboBox::addItem(QString text, QVariant *icon, QVariant *userData)
{
    ComboItem *item = new ComboItem(text, icon, userData);
    this->items->append(item);
    if(this->items->length() == 1){
        this->setCurrentIndex(0);
    }
}

void EditableComboBox::addItems(QList<QString> texts)
{
    for (int i = 0; i < texts.size(); ++i) {
        this->addItem(texts.at(i), nullptr, nullptr);
    }
}

void EditableComboBox::removeItem(int index)
{
    if(!(index >= 0 && index < items->length())){
        return;
    }

    this->items->removeAt(index);

    if(index < this->currentIndex()){
        this->_onItemClicked(this->_currentIndex - 1);
    }else if(index == this->currentIndex()){
        if(index > 0){
            this->_onItemClicked(this->_currentIndex - 1);
        }else{
            this->setCurrentIndex(0);
            emit(this->currentTextChanged(this->currentText()));
            emit(this->currentIndexChanged(0));
        }
    }

    if(this->count() == 0){
        this->clear();
    }
}


int EditableComboBox::currentIndex()
{
    return this->_currentIndex;
}

void EditableComboBox::setCurrentIndex(int index)
{
    if(index < 0){
        this->_currentIndex = -1;
        this->setText(QString());
        this->setPlaceholderText(this->_placeholderText);
    }else{
        if(!(index >=0 && index < this->items->length())){
            return;
        }

        this->_currentIndex = index;
        this->setText(this->items->at(index)->text);
    }
}

void EditableComboBox::setText(QString text)
{
    LineEdit::setText(text);
    this->adjustSize();
}


QString EditableComboBox::currentText()
{
    return this->text();
}

QVariant *EditableComboBox::currentData()
{
    if(!(this->currentIndex() >=0 && this->currentIndex() < this->items->length())){
        return nullptr;
    }

    return this->items->at(this->currentIndex())->userData; 
}

void EditableComboBox::setCurrentText(QString text)
{
    if(text == this->currentText()){
        return;
    }

    int index = this->findText(text);
    if(index >= 0){
        this->setCurrentIndex(index);
    }
}

void EditableComboBox::setItemText(int index, QString text)
{
    if(!(index >=0 && index < this->items->length())){
        return;
    }

    this->items->at(index)->text = text;
    if(this->currentIndex() == index){
        this->setText(text);
    }
}

QVariant *EditableComboBox::itemData(int index)
{
    if(!(index >=0 && index < this->items->length())){
        return nullptr;
    }

    return this->items->at(index)->userData;
}

QString EditableComboBox::itemText(int index)
{
    if(!(index >=0 && index < this->items->length())){
        return nullptr;
    }

    return this->items->at(index)->text;
}

QVariant *EditableComboBox::itemIcon(int index)
{
    if(!(index >=0 && index < this->items->length())){
        return nullptr;
    }

    return this->items->at(index)->_icon;
}

void EditableComboBox::setItemData(int index, QVariant *value)
{
    if(!(index >=0 && index < this->items->length())){
        return;
    }

    this->items->at(index)->userData = value;
}


void EditableComboBox::setItemIcon(int index, QVariant *icon)
{
    if(!(index >=0 && index < this->items->length())){
        return;
    }
    this->items->at(index)->_icon = icon;
}

int EditableComboBox::findData(QVariant *data)
{
    for(int i = 0; i < this->items->size(); i++){
        if(this->items->at(i)->userData == data){
            return i;
        }
    }
    return -1;
}

int EditableComboBox::findText(QString text)
{
    for(int i = 0; i < this->items->size(); i++){
        if(this->items->at(i)->text == text){
            return i;
        }
    }
    return -1;
}

void EditableComboBox::clear()
{
    if(this->currentIndex() >= 0){
        this->setText(QString());
    }

    this->items->clear();
    this->_currentIndex = -1;
}

int EditableComboBox::count()
{
    return this->items->length();
}

void EditableComboBox::insertItem(int index, QString text, QVariant *icon = nullptr, QVariant *userData = nullptr)
{
    ComboItem *item = new ComboItem(text, icon, userData);
    this->items->insert(index, item);

    if(index <= this->currentIndex()){
        this->_onItemClicked(this->currentIndex() + 1);
    }
}

void EditableComboBox::insertItems(int index, QList<QString> texts)
{
    int pos = index;
    for(int i = 0; i < texts.size(); i++){
        ComboItem *item = new ComboItem(texts.at(i), nullptr, nullptr);
        this->items->insert(pos, item);
        pos += 1;
    }

    if(index <= this->currentIndex()){
        this->_onItemClicked(this->currentIndex() + pos - index);
    }
}

void EditableComboBox::setMaxVisibleItems(int num)
{
    this->_maxVisibleItems = num;
}

int EditableComboBox::maxVisibleItems()
{
    return this->_maxVisibleItems;
}

void EditableComboBox::_closeComboMenu()
{
    if(!this->dropMenu){
        return;
    }

    this->dropMenu->close();
    this->dropMenu = nullptr;
}

void EditableComboBox::_onDropMenuClosed()
{
    this->dropMenu = nullptr;
}


ComboBoxMenu *EditableComboBox::_createComboMenu()
{
    return new ComboBoxMenu(this);
}


void EditableComboBox::_showComboMenu()
{
    if(items->isEmpty()){
        return;
    }

    ComboBoxMenu *menu = this->_createComboMenu();
    for(int i = 0; i < this->items->length(); i++){
        QAction *action = new QAction(this->items->at(i)->getIcon(), this->items->at(i)->text, this);
        connect(action, &QAction::triggered, this, [this, i]() { //特别关注
                EditableComboBox::_onItemClicked(i);
        });

        menu->addAction(action);
    }

    if(menu->view->width() < this->width()){
        menu->view->setMinimumWidth(this->width());
        menu->adjustSize();
    }

    menu->setMaxVisibleItems(this->maxVisibleItems());
    connect(menu, &ComboBoxMenu::closedSignal, this, &EditableComboBox::_onDropMenuClosed);
    this->dropMenu = menu;

    if(this->currentIndex() >= 0 && !this->items->isEmpty()){
        menu->setDefaultAction(menu->actions().at(this->currentIndex()));
    }

    int x = -menu->width() / 2 + menu->layout()->contentsMargins().left() + this->width() / 2;
    QPoint pd = this->mapToGlobal(QPoint(x, this->height()));
    int hd = menu->view->heightForAnimation(&pd, MenuAnimationType::DROP_DOWN);

    QPoint pu = this->mapToGlobal(QPoint(x, 0));
    int hu = menu->view->heightForAnimation(&pd, MenuAnimationType::PULL_UP);

    if(hd >= hu){
        menu->view->adjustSize(&pd, MenuAnimationType::DROP_DOWN);
        menu->exec(&pd, true, MenuAnimationType::DROP_DOWN);
    }else{
        menu->view->adjustSize(&pu, MenuAnimationType::PULL_UP);
        menu->exec(&pu, true, MenuAnimationType::PULL_UP);
    }


}


void EditableComboBox::_toggleComboMenu()
{
    if(this->dropMenu){
        this->_closeComboMenu();
    }else{
        this->_showComboMenu();
    }
}

void EditableComboBox::_onItemClicked(int index)
{
    if(index == this->currentIndex()){
        return;
    }

    this->setCurrentIndex(index);
    emit(this->currentTextChanged(this->currentText()));
    emit(this->currentIndexChanged(index));
}

void EditableComboBox::setCompleterMenu(CompleterMenu *menu)
{
    LineEdit::setCompleterMenu(menu);
    connect(menu, &CompleterMenu::activated, this, &EditableComboBox::__onActivated);
}

void EditableComboBox::__onActivated(QString text)
{
    int index = this->findText(text);
    if(index >= 0){
        this->setCurrentIndex(index);
    }
}

void EditableComboBox::setPlaceholderText(QString text)
{
    this->_placeholderText = text;
    LineEdit::setPlaceholderText(text);
}


void EditableComboBox::_onReturnPressed()
{
    if(this->text().isEmpty()){
        return;
    }

    int index = this->findText(this->text());
    if(index >= 0 && index != this->currentIndex()){
        this->_currentIndex = index;
        emit(this->currentIndexChanged(index));
    }else if(index == -1){
        this->addItem(this->text(), nullptr, nullptr);
        this->setCurrentIndex(this->count() - 1);
    }
}

void EditableComboBox::_onTextEdited(QString text)
{
    this->_currentIndex = -1;
    emit(this->currentTextChanged(text));

    for(int i = 0; i < this->items->size(); i++){
        if(this->items->at(i)->text == text){
            this->_currentIndex = i;
            emit(this->currentIndexChanged(i));
            return;
        }
    }
}


void EditableComboBox::_onClearButtonClicked()
{
    LineEdit::clear();
    this->_currentIndex = -1;
}


ComboBoxMenu::ComboBoxMenu(QWidget *parent) : RoundMenu(QString(), parent)
{
    this->view->publicSetViewportMargins(0, 2, 0, 6);
    this->view->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->view->setItemDelegate(new IndicatorMenuItemDelegate(nullptr));
    this->view->setObjectName(QString("comboListWidget"));
    this->setItemHeight(33);
}

void ComboBoxMenu::exec(QPoint *pos, bool ani, MenuAnimationType aniType)
{
    this->view->adjustSize(pos, aniType);
    this->adjustSize();
    return RoundMenu::exec(pos, ani, aniType);
}