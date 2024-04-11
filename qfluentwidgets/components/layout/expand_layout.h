#pragma once

#include <QtCore/QSize>
#include <QtCore/QPoint>
#include <QtCore/Qt>
#include <QtCore/QEvent>
#include <QtCore/QRect>
#include <QtCore/QDebug>
#include <QtGui/QResizeEvent>
#include <QtWidgets/QLayout>
#include <QtWidgets/QWidget>

class ExpandLayout : public QLayout{
    Q_OBJECT
public:
    ExpandLayout(QWidget *parent);
    void addWidget(QWidget *widget);
    void addItem(QLayoutItem *item) override;
    int count() const override;
    QLayoutItem *itemAt(int index) const override;
    QLayoutItem *takeAt(int index) override;
    Qt::Orientations expandingDirections() const override;
    bool hasHeightForWidth() const override;
    int heightForWidth(int width) const override;
    void setGeometry(const QRect& rect) override;
    QSize sizeHint() const;
    QSize minimumSize() const;
    int __doLayout(QRect rect, bool move) const;
    bool eventFilter(QObject *watched, QEvent *event) override;

    QList<QLayoutItem*> __items;
    QList<QWidget*> __widgets;
};