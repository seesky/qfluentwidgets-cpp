#pragma once

#include <QtCore/Qt>
#include <QtCore/QUrl>
#include <QtGui/QDesktopServices>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include "../../../components/widgets/icon_widget.h"
#include "../../../common/icon.h"
#include "../../../common/auto_wrap.h"
#include "../../../components/widgets/scroll_area.h"
#include "../../../common/style_sheet.h"

class LinkCard : public QFrame{
    Q_OBJECT
public:
    LinkCard(QVariant *icon, QString title, QString content, QString url, QWidget *parent);
    void __initWidget();
    void mouseReleaseEvent(QMouseEvent *event) override;

    QUrl url;
    IconWidget *iconWidget;
    QLabel *titleLabel;
    QLabel *contentLabel;
    IconWidget *urlWidget;
    QVBoxLayout *vBoxLayout;
};


class LinkCardView : public SingleDirectionScrollArea{
    Q_OBJECT
public:
    LinkCardView(QWidget *parent);
    void addCard(QVariant *icon, QString title, QString content, QString url);

    QWidget *view;
    QHBoxLayout *hBoxLayout;
    
};