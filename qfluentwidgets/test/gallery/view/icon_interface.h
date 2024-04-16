#pragma once

#include <QtCore/Qt>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>

#include "gallery_interface.h"
#include "../common/translator.h"
#include "../../../common/icon.h"
#include "../../../components/widgets/icon_widget.h"
#include "../../../components/layout/flow_layout.h"
#include "../../../common/config.h"
#include "../../../common/style_sheet.h"
#include "../../../components/widgets/scroll_area.h"
#include "../../../components/widgets/line_edit.h"
#include "../../../components/widgets/label.h"

class IconSearchLineEdit : public SearchLineEdit{
    Q_OBJECT
public:
    IconSearchLineEdit(QWidget *parent);
};


class IconCard : public QFrame{
    Q_OBJECT
public:
    IconCard(FluentIcon *icon, QWidget *parent);
    void mouseReleaseEvent(QMouseEvent *event) override;
    void setSelected(bool isSelected, bool force);

    FluentIcon *icon;
    bool isSelected;
    IconWidget *iconWidget;
    QLabel *nameLabel;
    QVBoxLayout *vBoxLayout;

signals:
    void clicked(FluentIcon*);
};


class IconInfoPanel : public QFrame{
    Q_OBJECT
public:
    IconInfoPanel(FluentIcon *icon, QWidget *parent);
    void setIcon(FluentIcon *icon);

    QLabel *nameLabel;
    IconWidget *iconWidget;
    QLabel *iconNameTitleLabel;
    QLabel *iconNameLabel;
    QLabel *enumNameTitleLabel;
    QLabel *enumNameLabel;

    QVBoxLayout *vBoxLayout;
};

/*
class IconCardView : public QWidget{
    Q_OBJECT
public:
    IconCardView(QWidget *parent);
    void __initWidget();
    void addIcon(FluentIcon *icon);
    void setSelectedIcon(FluentIcon *icon);
    void __setQss();
    void search(QString keyWord);
    void showAllIcons();

};


class IconInterface : public GalleryInterface{
    Q_OBJECT
public:
    IconInterface(QWidget *parent);
};
*/