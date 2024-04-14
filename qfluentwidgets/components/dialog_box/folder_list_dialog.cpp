#include "folder_list_dialog.h"

FolderListDialog::FolderListDialog(QStringList folderPaths, QString title, QString content, QWidget *parent) : MaskDialogBase(parent)
{
    this->title = title;
    this->content = content;
    this->__originalPaths = folderPaths;
    this->folderPaths = QStringList(folderPaths);

    this->vBoxLayout = new QVBoxLayout(this->widget);
    this->titleLabel = new QLabel(title, this->widget);
    this->contentLabel = new QLabel(content, this->widget);
    this->scrollArea = new SingleDirectionScrollArea(this->widget, Qt::Vertical);
    this->scrollWidget = new QWidget(this->scrollArea);
    this->completeButton = new QPushButton(this->tr("Done"), this->widget);
    this->addFolderCard = new AddFolderCard(this->scrollWidget);
    this->folderCards = QList<FolderCard *>();
    for(int i = 0; i < folderPaths.length(); i++){
        this->folderCards.append(new FolderCard(folderPaths.at(i), this->scrollWidget));
    }

    this->__initWidget();
}



void FolderListDialog::__initWidget()
{
    this->__setQss();

    int w = qMax(qMax(this->titleLabel->width() + 48, this->contentLabel->width()+48), 352);
    this->widget->setFixedWidth(w);
    this->scrollArea->resize(294, 72);
    this->scrollWidget->resize(292, 72);
    this->scrollArea->setFixedWidth(294);
    this->scrollWidget->setFixedWidth(292);
    this->scrollArea->setMaximumHeight(400);
    this->scrollArea->publicSetViewportMargins(0, 0, 0, 0);
    this->scrollArea->setWidgetResizable(true);
    this->scrollArea->setWidget(this->scrollWidget);
    this->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->scrollArea->hScrollBar->setForceHidden(true);
    this->__initLayout();

    connect(this->addFolderCard, &AddFolderCard::clicked, this, &FolderListDialog::__showFileDialog);
    connect(this->completeButton, &QPushButton::clicked, this, &FolderListDialog::__onButtonClicked);
    for(int i = 0; i < this->folderCards.length(); i++){
        connect(this->folderCards.at(i), &FolderCard::clicked, this, &FolderListDialog::__showDeleteFolderCardDialog);
    }
}

void FolderListDialog::__initLayout()
{
    this->vBoxLayout->setContentsMargins(24, 24, 24, 24);
    this->vBoxLayout->setSizeConstraint(QVBoxLayout::SetFixedSize);
    this->vBoxLayout->setAlignment(Qt::AlignTop);
    this->vBoxLayout->setSpacing(0);

    QVBoxLayout *layout_1 = new QVBoxLayout();
    layout_1->setContentsMargins(0, 0, 0, 0);
    layout_1->setSpacing(6);
    layout_1->addWidget(this->titleLabel, 0, Qt::AlignTop);
    layout_1->addWidget(this->contentLabel, 0, Qt::AlignTop);
    this->vBoxLayout->addLayout(layout_1, 0);
    this->vBoxLayout->addSpacing(12);

    QHBoxLayout *layout_2 = new QHBoxLayout();
    layout_2->setAlignment(Qt::AlignCenter);
    layout_2->setContentsMargins(4, 0, 4, 0);
    layout_2->addWidget(this->scrollArea, 0, Qt::AlignCenter);
    this->vBoxLayout->addLayout(layout_2, 1);
    this->vBoxLayout->addSpacing(24);

    this->scrollLayout = new QVBoxLayout(this->scrollWidget);
    this->scrollLayout->setAlignment(Qt::AlignTop);
    this->scrollLayout->setContentsMargins(0, 0, 0, 0);
    this->scrollLayout->setSpacing(8);
    this->scrollLayout->addWidget(this->addFolderCard, 0, Qt::AlignTop);
    for(int i = 0; i < this->folderCards.length(); i++){
        this->scrollLayout->addWidget(this->folderCards.at(i), 0, Qt::AlignTop);
    }

    QHBoxLayout *layout_3 = new QHBoxLayout();
    layout_3->setContentsMargins(0, 0, 0, 0);
    layout_3->addStretch(1);
    layout_3->addWidget(this->completeButton);
    this->vBoxLayout->addLayout(layout_3, 0);

    this->__adjustWidgetSize();
}


void FolderListDialog::__showFileDialog()
{
    QString path = QFileDialog::getExistingDirectory(this, this->tr("Choose folder"), QString("./"));

    if(path.isNull() || this->folderPaths.contains(path)){
        return;
    }

    FolderCard *card = new FolderCard(path, this->scrollWidget);
    this->scrollLayout->addWidget(card, 0, Qt::AlignTop);
    connect(card, &FolderCard::clicked, this, &FolderListDialog::__showDeleteFolderCardDialog);
    card->show();

    this->folderPaths.append(path);
    this->folderCards.append(card);

    this->__adjustWidgetSize();
}

void FolderListDialog::__showDeleteFolderCardDialog()
{
    QObject *sender = this->sender();
    QString title = this->tr("Are you sure you want to delete the folder?");
    QString content = this->tr("If you delete the ") + QString(((FolderCard *)sender)->folderName) + this->tr(" folder and remove it from the list, the folder will no longer appear in the list, but will not be deleted.");
    Dialog *dialog = new Dialog(title, content, this->window());
    connect(dialog, &Dialog::yesSignal, this, [this, sender](){
        this->__deleteFolderCard((FolderCard *)sender);
    });
    //dialog->exec_();
    dialog->exec();
}


void FolderListDialog::__deleteFolderCard(FolderCard *folderCard)
{
    this->scrollLayout->removeWidget(folderCard);
    int index = this->folderCards.indexOf(folderCard);
    this->folderCards.removeAt(index);
    this->folderPaths.removeAt(index);
    folderCard->deleteLater();

    this->__adjustWidgetSize();
}

void FolderListDialog::__setQss()
{
    this->titleLabel->setObjectName(QString("titleLabel"));
    this->contentLabel->setObjectName(QString("contentLabel"));
    this->completeButton->setObjectName(QString("completeButton"));
    this->scrollWidget->setObjectName(QString("scrollWidget"));

    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("FOLDER_LIST_DIALOG"), Theme::AUTO);
    this->setStyle(QApplication::style());

    this->titleLabel->adjustSize();
    this->contentLabel->adjustSize();
    this->completeButton->adjustSize();
}

void FolderListDialog::__onButtonClicked()
{   
    if(this->__originalPaths.toSet() != this->folderPaths.toSet()){
        this->setEnabled(false);
        QApplication::processEvents();
        emit(this->folderChanged(this->folderPaths));
    }

    this->close();
}

void FolderListDialog::__adjustWidgetSize()
{
    int N = this->folderCards.length();
    int h = 72*(N+1) + 8 * N;
    this->scrollArea->setFixedHeight(qMin(h, 400));
}


ClickableWindow::ClickableWindow(QWidget *parent) : QWidget(parent)
{
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setFixedSize(292, 72);
    this->_isPressed = false;
    this->_isEnter = false;
}

void ClickableWindow::enterEvent(QEvent *event)
{
    this->_isEnter = true;
    this->update();
}

void ClickableWindow::leaveEvent(QEvent *event)
{
    this->_isEnter = false;
    this->update();
}

void ClickableWindow::mouseReleaseEvent(QMouseEvent *e)
{
    this->_isPressed = false;
    this->update();
    if(e->button() == Qt::LeftButton){
        emit(this->clicked());
    }
}

void ClickableWindow::mousePressEvent(QMouseEvent *e)
{
    this->_isPressed = true;
    this->update();
}

void ClickableWindow::paintEvent(QPaintEvent *event) 
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    bool isDark = isDarkTheme();
    int bg = isDark ? 51 : 204;
    QBrush brush = QBrush(QColor(bg, bg, bg));
    painter.setPen(Qt::NoPen);

    if(!this->_isEnter){
        painter.setBrush(brush);
        painter.drawRoundedRect(this->rect(), 4, 4);
    }else{
        painter.setPen(QPen(QColor(bg, bg, bg), 2));
        painter.drawRect(1, 1, this->width() - 2, this->height() - 2);
        painter.setPen(Qt::NoPen);
        if(!this->_isPressed){
            bg = isDark ? 24 : 230;
            brush.setColor(QColor(bg, bg, bg));
            painter.setBrush(brush);
            painter.drawRect(2, 2, this->width() - 4, this->height() - 4);
        }else{
            bg = isDark ? 102 : 230;
            brush.setColor(QColor(153, 153, 153));
            painter.setBrush(brush);
            painter.drawRoundedRect(5, 1, this->width() - 10, this->height() - 2, 2, 2);
        }
    }
}


FolderCard::FolderCard(QString folderPath, QWidget *parent) : ClickableWindow(parent)
{
    this->folderPath = folderPath;
    this->folderName = QFileInfo(folderPath).fileName();

    QString c = getIconColor(Theme::AUTO, false);
    //qDebug() << QString("qfluentwidgets/images/folder_list_dialog/Close_%1.png").arg(c);
    this->__closeIcon = QPixmap(QString("qfluentwidgets/images/folder_list_dialog/Close_%1.png").arg(c)).scaled(12, 12, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

void FolderCard::paintEvent(QPaintEvent *event)
{
    ClickableWindow::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHints(QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform | QPainter::Antialiasing);

    QColor color = isDarkTheme() ? Qt::white : Qt::black;
    painter.setPen(color);
    if(this->_isPressed){
        this->__drawText(painter, 12, 8, 12, 7);
        painter.drawPixmap(this->width() - 26, 18, this->__closeIcon);
    }else{
        this->__drawText(painter, 10, 9, 10, 8);
        painter.drawPixmap(this->width() - 24, 20, this->__closeIcon);
    }
}

void  FolderCard::__drawText(QPainter& painter, int x1, int fontSize1, int x2, int fontSize2)
{
    QFont font1 = QFont(QString("Microsoft YaHei"), fontSize1, 75);
    painter.setFont(font1);
    QString name = QFontMetrics(font1).elidedText(this->folderName, Qt::ElideRight, this->width() - 48);
    painter.drawText(x1, 30, name);

    QFont font2 = QFont(QString("Microsoft YaHei"), fontSize2);
    painter.setFont(font2);
    QString path = QFontMetrics(font2).elidedText(this->folderPath, Qt::ElideRight, this->width() - 24);
    painter.drawText(x2, 37, this->width() - 16, 18, Qt::AlignLeft, path);
}



AddFolderCard::AddFolderCard(QWidget *parent) : ClickableWindow(parent)
{
    QString c = getIconColor(Theme::AUTO, false);
    //qDebug() << QString("qfluentwidgets/images/folder_list_dialog/Add_%1.png").arg(c);
    this->__iconPix = QPixmap(QString("qfluentwidgets/images/folder_list_dialog/Add_%1.png").arg(c)).scaled(22, 22, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}


void AddFolderCard::paintEvent(QPaintEvent *event)
{
    ClickableWindow::paintEvent(event);
    QPainter painter(this);
    int w = this->width();
    int h = this->height();
    int pw = this->__iconPix.width();
    int ph = this->__iconPix.height();
    if(!this->_isPressed){
        painter.drawPixmap(int(w/2 - pw/2), int(h/2 - ph/2), this->__iconPix);
    }else{
        painter.drawPixmap(int(w/2 - (pw - 4)/2), int(h/2 - (ph-4)/2), pw - 4, ph - 4, this->__iconPix);
    }
}
