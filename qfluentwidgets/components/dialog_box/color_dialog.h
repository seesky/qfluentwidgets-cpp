#pragma once

#include <QtCore/Qt>
#include <QtCore/QPoint>
#include <QtCore/QRegExp>
#include <QtCore/QSize>
#include <QtGui/QBrush>
#include <QtGui/QColor>
#include <QtGui/QPixmap>
#include <QtGui/QPainter>
#include <QtGui/QPen>
#include <QtGui/QIntValidator>
#include <QtGui/QRegExpValidator>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QFrame>
#include <QtWidgets/QVBoxLayout>
#include "../../common/style_sheet.h"
#include "../widgets/slider.h"
#include "../widgets/scroll_area.h"
#include "../widgets/button.h"
#include "../widgets/line_edit.h"
#include "mask_dialog_base.h"


class HuePanel : public QWidget{
    Q_OBJECT
public:
    HuePanel(QColor color, QWidget *parent);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void setPickerPosition(QPoint pos);
    void setColor(QColor color);
    int hue();
    int saturation();
    void paintEvent(QPaintEvent *event) override;

    QPixmap huePixmap;
    QPoint pickerPos;
    QColor color;
signals:
    void colorChanged(QColor);
};


class BrightnessSlider : public ClickableSlider{
    Q_OBJECT
public:
    BrightnessSlider(QColor color, QWidget *parent);
    void setColor(QColor color);

    QColor color;
signals:
    void colorChanged(QColor);

public slots:
    void __onValueChanged(int value);
};


class ColorCard : public QWidget{
    Q_OBJECT
public:
    ColorCard(QColor color, QWidget *parent, bool enableAlpha);
    QPixmap _createTitledBackground();
    void setColor(QColor color);
    void paintEvent(QPaintEvent *event) override;

    bool enableAlpha;
    QPixmap titledPixmap;
    QColor color;
};

class ColorLineEdit : public LineEdit{
    Q_OBJECT
public:
    ColorLineEdit(int value, QWidget *parent);
    void _onTextEdited(QString text);
    
signals:
    void valueChanged(QString);
};

class HexColorLineEdit : public ColorLineEdit{
    Q_OBJECT
public:
    HexColorLineEdit(QColor color, QWidget *parent, bool enableAlpha);
    void setColor(QColor color);

    QColor::NameFormat colorFormat;
    QLabel *prefixLabel;
};

class OpacityLineEdit : public ColorLineEdit{
    Q_OBJECT
public:
    OpacityLineEdit(int value, QWidget *parent, bool enableAlpha);
    void showEvent(QShowEvent *event) override;
    void _adjustSuffixPos();

    QLabel *suffixLabel;
};


class ColorDialog : public MaskDialogBase{
    Q_OBJECT
public:
    ColorDialog(QColor color, QString title, QWidget *parent, bool enableAlpha);
    void __initWidget();
    void __initLayout();
    void __setQss();
    void setColor(QColor color, bool movePicker);
    void updateStyle();
    void showEvent(QShowEvent *event) override;
    

    bool enableAlpha;
    QColor oldColor;
    QColor color;
    SingleDirectionScrollArea *scrollArea;
    QWidget *scrollWidget;
    QFrame *buttonGroup;
    PrimaryPushButton *yesButton;
    QPushButton *cancelButton;

    QLabel *titleLabel;
    HuePanel *huePanel;
    ColorCard *newColorCard;
    ColorCard *oldColorCard;
    BrightnessSlider *brightSlider;
    QLabel *editLabel;
    QLabel *redLabel;
    QLabel *blueLabel;
    QLabel *greenLabel;
    QLabel *opacityLabel;
    HexColorLineEdit *hexLineEdit;
    ColorLineEdit *redLineEdit;
    ColorLineEdit *greenLineEdit;
    ColorLineEdit *blueLineEdit;
    OpacityLineEdit *opacityLineEdit;
    QVBoxLayout *vBoxLayout;
signals:
    void colorChanged(QColor);

public slots:
    void __onHueChanged(QColor color);
    void __onBrightnessChanged(QColor color);
    void __onRedChanged(int red);
    void __onBlueChanged(int blue);
    void __onGreenChanged(int green);
    void __onOpacityChanged(float opacity);
    void __onHexColorChanged(QString color);
    void __onYesButtonClicked();
    void __connectSignalToSlot();
};