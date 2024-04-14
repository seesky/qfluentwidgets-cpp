#pragma once

#include <QtCore/QSize>
#include <QtCore/QPoint>
#include <QtCore/Qt>
#include <QtCore/QRect>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QParallelAnimationGroup>
#include <QtCore/QEasingCurve>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLayout>
#include <QtWidgets/QWidgetItem>
#include <QtWidgets/QLayoutItem>


class FlowLayout : public QLayout{
    Q_OBJECT
public:
    FlowLayout(QWidget *parent, bool needAni, bool isTight);
    void addItem(QLayoutItem *item) override;
    void addWidget(QWidget *w);
    void setAnimation(int duration, QEasingCurve ease);
    int count() const override;
    QLayoutItem *itemAt(int index) const override;
    QLayoutItem *takeAt(int index) override;
    QLayoutItem * removeWidget(QWidget *widget);
    void removeAllWidgets();
    void takeAllWidgets();
    Qt::Orientation expandingDirections();
    bool hasHeightForWidth() const;
    int heightForWidth(int width) const;
    void setGeometry(const QRect&) override;
    QSize sizeHint() const override;
    QSize minimumSize() const;
    void setVerticalSpacing(int spacing);
    int verticalSpacing() const;
    void setHorizontalSpacing(int spacing);
    int horizontalSpacing() const;
    int _doLayout(QRect rect, bool move) const;


    QList<QLayoutItem*> _items;
    QList<QPropertyAnimation*> _anis;
    QParallelAnimationGroup *_aniGroup;
    int _verticalSpacing;
    int _horizontalSpacing;
    int duration;
    QEasingCurve ease;
    bool needAni;
    bool isTight;
};


