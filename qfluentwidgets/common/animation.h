#pragma once

#include <QtCore>
#include <QtGui>
#include <QtWidgets>


class AnimationBase : public QObject
{
    Q_OBJECT
public:
    explicit AnimationBase(QObject *parent = nullptr);
    ~AnimationBase();

protected:
    //void paintEvent(QPaintEvent *event) override;
    //void mouseReleaseEvent(QMouseEvent *event) override;
    //void mousePressEvent(QMouseEvent *event) override;

    //qreal get_devicePixelRatio(QScreen *screen);
    //QScreen *get_focus_screen();
    //void mouseMoveEvent(QMouseEvent *event) override;

    //void switch_to_window_a();
private:


private slots:

};
