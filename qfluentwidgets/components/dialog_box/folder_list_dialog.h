#pragma once

#include <QtCore/Qt>
#include <QtGui/QBrush>
#include <QtGui/QColor>
#include <QtGui/QFont>
#include <QtGui/QFontMetrics>
#include <QtGui/QMouseEvent>
#include <QtGui/QPainter>
#include <QtGui/QPen>
#include <QtGui/QPixmap>

#include <QtWidgets/QApplication>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>

#include "../../common/config.h"
#include "../../common/icon.h"
#include "../../common/style_sheet.h"
#include "dialog.h"
#include "mask_dialog_base.h"
#include "../widgets/scroll_area.h"


class AddFolderCard;
class FolderCard;
class FolderListDialog : public MaskDialogBase{
    Q_OBJECT
public:
    FolderListDialog(QStringList folderPaths, QString title, QString content, QWidget *parent);
    void __initWidget();
    void __initLayout();

    void __showDeleteFolderCardDialog();
    void __deleteFolderCard(FolderCard *folderCard);
    void __setQss();
    void __adjustWidgetSize();


    QString title;
    QString content;
    QStringList __originalPaths;
    QStringList folderPaths;
    QVBoxLayout *vBoxLayout;
    QLabel *titleLabel;
    QLabel *contentLabel;
    SingleDirectionScrollArea *scrollArea;
    QWidget *scrollWidget;
    QPushButton *completeButton;
    AddFolderCard *addFolderCard;
    QList<FolderCard *> folderCards;
    QVBoxLayout *scrollLayout;


signals:
    void folderChanged(QStringList);

public slots:
    void __onButtonClicked();
    void __showFileDialog();

};


class ClickableWindow : public QWidget{
    Q_OBJECT
public:
    ClickableWindow(QWidget *parent);
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void paintEvent(QPaintEvent *event) override;

    bool _isPressed;
    bool _isEnter;
signals:
    void clicked();

};


class FolderCard : public ClickableWindow{
    Q_OBJECT
public:
    FolderCard(QString folderPath, QWidget *parent);
    void paintEvent(QPaintEvent *event) override;
    void  __drawText(QPainter& painter, int x1, int fontSize1, int x2, int fontSize2);

    QString folderName;
    QPixmap __closeIcon;
    QString folderPath;
};


class AddFolderCard : public ClickableWindow{
    Q_OBJECT
public:
    AddFolderCard(QWidget *parent);
    void paintEvent(QPaintEvent *event) override;

    QPixmap __iconPix;
};