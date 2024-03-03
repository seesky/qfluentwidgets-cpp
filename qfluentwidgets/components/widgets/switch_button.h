#pragma once

#include <QtCore/Qt>
#include <QtCore/QTimer>
#include <QtCore/QEvent>
#include <QtCore/QPoint>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QEasingCurve>
#include <QtGui/QColor>
#include <QtGui/QPainter>
#include <QtGui/QHoverEvent>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

#include "../../common/style_sheet.h"
#include "button.h"


enum class IndicatorPosition{
    LEFT = 0,
    RIGHT = 1
};

class Indicator : public ToolButton{
    Q_OBJECT
    Q_PROPERTY(int sliderX READ getSliderX WRITE setSliderX)
public:
    Indicator(QWidget *parent);
    void mouseReleaseEvent(QMouseEvent *e) override;
    void toggle();
    void setDown(bool isDown);
    void setHover(bool isHover);
    void paintEvent(QPaintEvent *event) override;
    void _drawBackground(QPainter *painter);
    void _drawCircle(QPainter *painter);
    QColor _backgroudColor();
    QColor _borderColor();
    QColor _sliderColor();
    int getSliderX();
    void setSliderX(int x);

    int _sliderX;
    QPropertyAnimation *slideAni;

signals:
    void checkedChanged(bool);

public slots:
    void _toggleSlider();
};


class SwitchButton : public QWidget{
    Q_OBJECT
    Q_PROPERTY(int spacing READ getSpacing WRITE setSpacing)
    Q_PROPERTY(bool checked READ isChecked WRITE setChecked)
    Q_PROPERTY(QString text READ getText WRITE setText)
    Q_PROPERTY(QString onText READ getOnText WRITE setOnText)
    Q_PROPERTY(QString offText READ getOffText WRITE setOffText)
public:
    SwitchButton(QWidget *parent, IndicatorPosition indicatorPos);
    SwitchButton(QString text, QWidget *parent, IndicatorPosition indicatorPos);
    void __initWidget();
    bool eventFilter(QObject *watched, QEvent *event) override;
    bool isChecked();
    void setChecked(bool isChecked);
    void toggleChecked();
    
    QString getText();
    void setText(QString text);
    int getSpacing();
    void setSpacing(int spacing);
    QString getOnText();
    void setOnText(QString text);
    QString getOffText();
    void setOffText(QString text);

    QString _text;
    QString _offText;
    QString _onText;
    int __spacing;
    IndicatorPosition indicatorPos;
    QHBoxLayout *hBox;
    Indicator *indicator;
    QLabel *label;

signals:
    void checkedChanged(bool);


public slots:
    void _updateText();
};