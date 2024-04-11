#pragma once

#include <QtCore/Qt>
#include <QtCore/QSize>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSizePolicy>
#include <QtGui/QPainter>
#include <QtGui/QIcon>

#include "../../components/widgets/button.h"
#include "../../common/config.h"
#include "../../common/icon.h"
#include "../../components/dialog_box/dialog.h"
#include "expand_setting_card.h"

class FolderItem : public QWidget{
    Q_OBJECT
public:
    FolderItem(QString folder, QWidget *parent);

    QString folder;
    QHBoxLayout *hBoxLayout;
    QLabel *folderlabel;
    ToolButton *removeButton;

signals:
    void removed(QWidget*);
};


class FolderListSettingCard : public ExpandSettingCard{
    Q_OBJECT
public:
    FolderListSettingCard(QVariant configItem, QString title, QString content, QString directory, QWidget *parent);
    void __initWidget();
    
    void __addFolderItem(QString folder);
    
    void __removeFolder(FolderItem *item);

    QVariant configItem;
    QString _dialogDirectory;
    PushButton *addFolderButton;
    QList<QString> folders;

signals:
    void folderChanged(QList<QString>);

public slots:
    void __showFolderDialog();
    void showConfirmDialog(FolderItem *item);
};