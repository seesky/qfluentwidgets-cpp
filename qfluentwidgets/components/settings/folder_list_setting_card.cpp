#include "folder_list_setting_card.h"


FolderItem::FolderItem(QString folder, QWidget *parent) : QWidget(parent)
{
    this->folder = folder;
    this->hBoxLayout = new QHBoxLayout(this);
    this->folderlabel = new QLabel(folder, this);

    FluentIcon *icon = new FluentIcon();
    icon->setIconName(QString("CLOSE"));
    this->removeButton = new ToolButton(icon, this);

    this->removeButton->setFixedSize(39, 29);
    this->removeButton->setIconSize(QSize(12, 12));

    this->setFixedHeight(53);
    this->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    this->hBoxLayout->setContentsMargins(48, 0, 60, 0);
    this->hBoxLayout->addWidget(this->folderlabel, 0, Qt::AlignLeft);
    this->hBoxLayout->addSpacing(16);
    this->hBoxLayout->addStretch(1);
    this->hBoxLayout->addWidget(this->removeButton, 0, Qt::AlignRight);
    this->hBoxLayout->setAlignment(Qt::AlignVCenter);

    connect(this->removeButton, &ToolButton::clicked, this, [this](){
        emit(this->removed(this));
    });
}


FolderListSettingCard::FolderListSettingCard(QVariant configItem, QString title, QString content, QString directory, QWidget *parent) : ExpandSettingCard(new QVariant(), title, content, parent)
{
    FluentIcon *icon = new FluentIcon();
    icon->setIconName(QString("FOLDER"));
    this->card->iconLabel->setIcon(new QVariant(QVariant::fromValue<FluentIcon>(*icon)));

    this->configItem = configItem;
    this->_dialogDirectory = directory;
    FluentIcon *folderAddIcon = new FluentIcon();
    folderAddIcon->setIconName(QString("FOLDER_ADD"));
    this->addFolderButton = new PushButton(folderAddIcon, this->tr("Add folder"), this);

    this->folders = qconfig->get(configItem).value<QList<QString>>(); //TODO:类型错误
    this->__initWidget();

}


void FolderListSettingCard::__initWidget()
{
    this->addWidget(this->addFolderButton);

    this->viewLayout->setSpacing(0);
    this->viewLayout->setAlignment(Qt::AlignTop);
    this->viewLayout->setContentsMargins(0, 0, 0, 0);
    for(int i = 0; i < this->folders.length(); i++){
        this->__addFolderItem(this->folders.at(i));
    }

    connect(this->addFolderButton, &PushButton::clicked, this, &FolderListSettingCard::__showFolderDialog);
}


void FolderListSettingCard::__showFolderDialog()
{
    QString folder = QFileDialog::getExistingDirectory(this, this->tr("Choose folder"), this->_dialogDirectory);

    if(folder.isEmpty() || this->folders.contains(folder)){
        return;
    }

    this->__addFolderItem(folder);
    this->folders.append(folder);
    qconfig->set(this->configItem, QVariant::fromValue<QList<QString>>(this->folders), true, false);
    emit(this->folderChanged(this->folders));
}


void FolderListSettingCard::__addFolderItem(QString folder)
{
    FolderItem *item = new FolderItem(folder, this->view);
    connect(item, &FolderItem::removed, this, &FolderListSettingCard::__showFolderDialog);
    this->viewLayout->addWidget(item);
    item->show();
    this->_adjustViewSize();
}


void FolderListSettingCard::showConfirmDialog(FolderItem *item)
{
    QString name = QFileInfo(item->folder).fileName();
    QString title = this->tr("Are you sure you want to delete the folder?");
    QString content = this->tr("If you delete the ") + name + this->tr(" folder and remove it from the list, the folder will no longer appear in the list, but will not be deleted.");
    Dialog *w = new Dialog(title, content, this->window());
    connect(w, &Dialog::yesSignal, this, [this, item](){
        this->__removeFolder(item);
    });
    w->exec();
}

void FolderListSettingCard::__removeFolder(FolderItem *item)
{
    if(!this->folders.contains(item->folder)){
        return;
    }

    this->folders.removeOne(item->folder);
    this->viewLayout->removeWidget(item);
    item->deleteLater();
    this->_adjustViewSize();

    emit(this->folderChanged(this->folders));
    qconfig->set(this->configItem, QVariant::fromValue<QList<QString>>(this->folders), true, false);
}