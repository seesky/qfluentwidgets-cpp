#pragma once

#include <QtCore/Qt>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

#include "../../common/style_sheet.h"
#include "../../common/font.h"
#include "../layout/expand_layout.h"

class SettingCardGroup : public QWidget{
    Q_OBJECT
public:
    SettingCardGroup(QString title, QWidget *parent);
    void addSettingCard(QWidget *card);
    void addSettingCards(QList<QWidget*> cards);
    void adjustSize();

    QLabel *titleLabel;
    QVBoxLayout *vBoxLayout;
    ExpandLayout *cardLayout;
};