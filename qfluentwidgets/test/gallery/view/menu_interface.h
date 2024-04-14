#pragma once

#include <QtCore/QPoint>
#include <QtCore/Qt>
#include <QtCore/QStandardPaths>
#include <QtGui/QColor>
#include <QtWidgets/QAction>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QActionGroup>

#include "gallery_interface.h"
#include "../common/translator.h"
#include "../../../common/icon.h"
#include "../../../components/widgets/menu.h"
#include "../../../components/widgets/button.h"
#include "../../../components/widgets/command_bar.h"
#include "../../../common/font.h"
#include "../../../components/widgets/flyout.h"
#include "../../../components/widgets/label.h"
#include "../../../common/config.h"
#include "../../../common/icon.h"





class MenuInterface : public GalleryInterface{
    Q_OBJECT
public:
    MenuInterface(QWidget *parent);
    void createMenu(QPoint pos);
    void createCustomWidgetMenu(QPoint pos);
    CheckableMenu *createCheckableMenu(QPoint pos);
    CommandBar *createCommandBar();

    



    PushButton *button1;
    PushButton *button2;
    PushButton *button3;
    ImageLabel *imageLabel;

public slots:
    void createCommandBarFlyout();
    void saveImage();
};


class ProfileCard : public QWidget{
    Q_OBJECT
public:
    ProfileCard(QString avatarPath, QString name, QString email, QWidget *parent);
    AvatarWidget *avatar;
    BodyLabel *nameLabel;
    CaptionLabel *emailLabel;
    HyperlinkButton *logoutButton;
};