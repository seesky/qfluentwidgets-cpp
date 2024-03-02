#include "color_dialog.h"


HuePanel::HuePanel(QColor color, QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(256, 256);
    this->huePixmap = QPixmap("/qfluentwidgets/images/color_dialog/HuePanel.png");
    this->setColor(color);
}

void HuePanel::mousePressEvent(QMouseEvent *event)
{
    this->setPickerPosition(event->pos());
}

void HuePanel::mouseMoveEvent(QMouseEvent *event)
{
    this->setPickerPosition(event->pos());
}

void HuePanel::setPickerPosition(QPoint pos)
{
    this->pickerPos = QPoint(pos);
    this->color.setHsv(int(qMax(0, qMin(1, pos.x() / this->width())) * 360), int(qMax(0, qMin(1, (this->height() - pos.y()) / this->height())) * 255), 255); //TODO:特殊关注
    this->update();
    emit(this->colorChanged(this->color));
}

void HuePanel::setColor(QColor color)
{
    this->color = QColor(color);
    this->color.setHsv(this->color.hue(), this->color.saturation(), 255);
    this->pickerPos = QPoint(int(this->hue() / 360 * this->width()), int(255 - this->saturation()) / 255 * this->height());
    this->update();
}

int HuePanel::hue()
{
    return this->color.hue();
}

int HuePanel::saturation()
{
    return this->color.saturation();
}

void HuePanel::paintEvent(QPaintEvent *event)
{
    QPainter *painter = new QPainter(this);
    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    painter->setBrush(QBrush(this->huePixmap));
    painter->setPen(QPen(QColor(0, 0, 0, 15), 2.4));
    painter->drawRoundedRect(this->rect(), 5.6, 5.6);


    QColor color;
    if(this->saturation() > 153 || (40 < this->hue() && this->hue() < 180)){
        color = Qt::black;
    }else{
        color = QColor(255, 253, 254);
    }

    painter->setPen(QPen(color, 3));
    painter->setBrush(Qt::NoBrush);
    painter->drawEllipse(this->pickerPos.x() - 8, this->pickerPos.y() - 8, 16, 16);
}

BrightnessSlider::BrightnessSlider(QColor color, QWidget *parent) : ClickableSlider(parent)
{
    this->setRange(0, 255);
    this->setSingleStep(1);
    this->setColor(color);
    connect(this, &BrightnessSlider::valueChanged, this, &BrightnessSlider::__onValueChanged);
}

void BrightnessSlider::setColor(QColor color)
{
    this->color = QColor(color);
    this->setValue(this->color.value());
    QString qss =  StyleSheetFile(FluentStyleSheetMap.value("COLOR_DIALOG")).content(Theme::AUTO);
    qss = qss.replace("--slider-hue", QString::number(this->color.hue()));
    qss = qss.replace("--slider-saturation", QString::number(this->color.saturation()));
    this->setStyleSheet(qss);
}

void BrightnessSlider::__onValueChanged(int value)
{
    this->color.setHsv(this->color.hue(), this->color.saturation(), value, this->color.alpha());
    this->setColor(this->color);
    emit(this->colorChanged(this->color));
}

ColorCard::ColorCard(QColor color, QWidget *parent, bool enableAlpha) : QWidget(parent)
{
    this->setFixedSize(44, 128);
    this->setColor(color);
    this->enableAlpha = enableAlpha;
    this->titledPixmap = this->_createTitledBackground();
}

QPixmap ColorCard::_createTitledBackground()
{
    QPixmap pixmap = QPixmap(8, 8);
    pixmap.fill(Qt::transparent);
    QPainter *painter = new QPainter(&pixmap);

    int c = isDarkTheme() ? 255 : 0;
    QColor color = QColor(c, c, c, 26);
    painter->fillRect(4, 0, 4, 4, color);
    painter->fillRect(0, 4, 4, 4, color);
    painter->end();
    return pixmap;
}

void ColorCard::setColor(QColor color)
{
    this->color = QColor(color);
    this->update();
}

void ColorCard::paintEvent(QPaintEvent *event)
{
    QPainter painter = QPainter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    if(this->enableAlpha){
        painter.setBrush(QBrush(this->titledPixmap));
        painter.setPen(QColor(0, 0, 0, 13));
        painter.drawRoundedRect(this->rect(), 4, 4);
    }

    painter.setBrush(this->color);
    painter.setPen(QColor(0, 0, 0, 13));
    painter.drawRoundedRect(this->rect(), 4, 4);

}


ColorLineEdit::ColorLineEdit(int value, QWidget *parent) : LineEdit(parent)
{
    this->setText(QString::number(value));
    this->setFixedSize(136, 33);
    this->setClearButtonEnabled(true);
    this->setValidator(new QIntValidator(0, 255, this));
    connect(this, &ColorLineEdit::textEdited, this, &ColorLineEdit::_onTextEdited);
}

void ColorLineEdit::_onTextEdited(QString text)
{
    int flag = 0;
    QValidator::State state = this->validator()->validate(text, flag);
    if(state == QIntValidator::Acceptable){
        emit(this->valueChanged(text));
    }
}


HexColorLineEdit::HexColorLineEdit(QColor color, QWidget *parent, bool enableAlpha) : ColorLineEdit(enableAlpha ? QColor::HexArgb : QColor::HexRgb, parent)
{
    this->colorFormat = enableAlpha ? QColor::HexArgb : QColor::HexRgb;

    if(enableAlpha){
        this->setValidator(new QRegExpValidator(QRegExp("[A-Fa-f0-9]{8}")));
    }else{
        this->setValidator(new QRegExpValidator(QRegExp("[A-Fa-f0-9]{6}")));
    }
    this->setTextMargins(4, 0, 33, 0);
    this->prefixLabel = new QLabel(QString("#"), this);
    this->prefixLabel->move(7, 2);
    this->prefixLabel->setObjectName(QString("prefixLabel"));
}


void HexColorLineEdit::setColor(QColor color)
{
    this->setText(color.name(this->colorFormat).remove(0, 1));
}


OpacityLineEdit::OpacityLineEdit(int value, QWidget *parent, bool enableAlpha = false) : ColorLineEdit(int(value/255*100), parent)
{
    this->setValidator(new QRegExpValidator(QRegExp("[0-9][0-9]{0,1}|100")));
    this->setTextMargins(4, 0, 33, 0);
    this->suffixLabel = new QLabel(QString("%"), this);
    this->suffixLabel->setObjectName(QString("suffixLabel"));
    connect(this, &OpacityLineEdit::textChanged, this, &OpacityLineEdit::_adjustSuffixPos);
}

void OpacityLineEdit::showEvent(QShowEvent *event)
{
    OpacityLineEdit::showEvent(event);
    this->_adjustSuffixPos();
}



void OpacityLineEdit::_adjustSuffixPos()
{
    int x = this->fontMetrics().width(this->text()) + 18;
    this->suffixLabel->move(x, 2);
}



ColorDialog::ColorDialog(QColor color, QString title, QWidget *parent, bool enableAlpha) : MaskDialogBase(parent)
{
    this->enableAlpha = enableAlpha;
    QColor _color;
    if(!enableAlpha){
        _color = QColor(color);
        _color.setAlpha(255);
    }

    this->oldColor = QColor(_color);
    this->color = QColor(_color);

    this->scrollArea = new SingleDirectionScrollArea(this->widget, Qt::Vertical);
    this->scrollWidget = new QWidget(this->scrollArea);

    this->buttonGroup = new QFrame(this->widget);
    this->yesButton = new PrimaryPushButton(this->tr("OK"), this->buttonGroup, nullptr);
    this->cancelButton = new QPushButton(this->tr("Cancel"), this->buttonGroup);

    this->titleLabel = new QLabel(title, this->scrollWidget);
    this->huePanel = new HuePanel(_color, this->scrollWidget);
    this->newColorCard = new ColorCard(_color, this->scrollWidget, enableAlpha);
    this->oldColorCard = new ColorCard(_color, this->scrollWidget, enableAlpha);
    this->brightSlider = new BrightnessSlider(_color, this->scrollWidget);

    this->editLabel = new QLabel(this->tr("Edit Color"), this->scrollWidget);
    this->redLabel = new QLabel(this->tr("Red"), this->scrollWidget);
    this->blueLabel = new QLabel(this->tr("Blue"), this->scrollWidget);
    this->greenLabel = new QLabel(this->tr("Green"), this->scrollWidget);
    this->opacityLabel = new QLabel(this->tr("Opacity"), this->scrollWidget);
    this->hexLineEdit = new HexColorLineEdit(this->color.red(), this->scrollWidget, enableAlpha);
    this->redLineEdit = new ColorLineEdit(this->color.red(), this->scrollWidget);
    this->greenLineEdit = new ColorLineEdit(this->color.blue(), this->scrollWidget);
    this->opacityLineEdit = new OpacityLineEdit(this->color.alpha(), this->scrollWidget, false);
    
    this->vBoxLayout = new QVBoxLayout(this->widget);
    this->__initWidget();
}


void ColorDialog::__initWidget()
{
    this->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->scrollArea->publicSetViewportMargins(48, 24, 0, 24);
    this->scrollArea->setWidget(this->scrollWidget);

    this->widget->setMaximumSize(488, 696+40*this->enableAlpha);
    this->widget->resize(488, 696+40*this->enableAlpha);
    this->scrollWidget->resize(440, 560+40*this->enableAlpha);
    this->buttonGroup->setFixedSize(486, 81);
    this->yesButton->setFixedWidth(216);
    this->cancelButton->setFixedWidth(216);

    this->setShadowEffect(60, std::tuple<int,int>(0, 10), QColor(0, 0, 0, 80));
    this->setMaskColor(QColor(0, 0, 0, 76));

    this->__setQss();
    this->__initLayout();
    this->__connectSignalToSlot();
}

void ColorDialog::__initLayout()
{
    this->huePanel->move(0, 46);
    this->newColorCard->move(288, 46);
    this->oldColorCard->move(288, this->newColorCard->geometry().bottom() + 1);
    this->brightSlider->move(0, 324);

    this->editLabel->move(0, 385);
    this->redLineEdit->move(0, 426);
    this->greenLineEdit->move(0, 470);
    this->blueLineEdit->move(0, 515);
    this->redLabel->move(144, 434);
    this->greenLabel->move(144, 478);
    this->blueLabel->move(144, 524);
    this->hexLineEdit->move(196, 381);

    if(this->enableAlpha){
        this->opacityLineEdit->move(0, 560);
        this->opacityLabel->move(144, 567);
    }else{
        this->opacityLineEdit->hide();
        this->opacityLabel->hide();
    }

    this->vBoxLayout->setSpacing(0);
    this->vBoxLayout->setAlignment(Qt::AlignTop);
    this->vBoxLayout->setContentsMargins(0, 0, 0, 0);
    this->vBoxLayout->addWidget(this->scrollArea, 1);
    this->vBoxLayout->addWidget(this->buttonGroup, 0, Qt::AlignBottom);
}

void ColorDialog::__setQss()
{
    this->editLabel->setObjectName(QString("editLabel"));
    this->titleLabel->setObjectName(QString("titleLabel"));
    this->yesButton->setObjectName(QString("yesButton"));
    this->cancelButton->setObjectName(QString("cancelButton"));
    this->buttonGroup->setObjectName(QString("buttonGroup"));
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("COLOR_DIALOG"), Theme::AUTO);
    this->titleLabel->adjustSize();
    this->editLabel->adjustSize();
}


void ColorDialog::setColor(QColor color, bool movePicker = true)
{
    this->color = QColor(color);
    this->brightSlider->setColor(color);
    this->newColorCard->setColor(color);
    this->hexLineEdit->setColor(color);
    this->redLineEdit->setText(QString::number(color.red()));
    this->blueLineEdit->setText(QString::number(color.blue()));
    this->greenLineEdit->setText(QString::number(color.green()));
    if(movePicker){
        this->huePanel->setColor(color);
    }
}


void ColorDialog::__onHueChanged(QColor color)
{
    this->color.setHsv(color.hue(), color.saturation(), this->color.value(), this->color.alpha());
    this->setColor(this->color);
}

void ColorDialog::__onBrightnessChanged(QColor color)
{
    this->color.setHsv(this->color.hue(), this->color.saturation(), color.value(), color.alpha());
    this->setColor(this->color, false);
}

void ColorDialog::__onRedChanged(int red)
{
    this->color.setRed(red);
    this->setColor(this->color);
}

void ColorDialog::__onBlueChanged(int blue)
{
    this->color.setBlue(blue);
    this->setColor(this->color);
}

void ColorDialog::__onGreenChanged(int green)
{
    this->color.setGreen(green);
    this->setColor(this->color);
}

void ColorDialog::__onOpacityChanged(float opacity)
{
    this->color.setAlpha(int(int(opacity)/100*255));
    this->setColor(this->color);
}

void ColorDialog::__onHexColorChanged(QString color)
{
    this->color.setNamedColor(QString("#") + color);
    this->setColor(this->color);
}

void ColorDialog::__onYesButtonClicked()
{
    this->accept();
    if(this->color != this->oldColor){
        emit(this->colorChanged(this->color));
    }
}

void ColorDialog::updateStyle()
{
    this->setStyle(QApplication::style());
    this->titleLabel->adjustSize();
    this->editLabel->adjustSize();
    this->redLabel->adjustSize();
    this->greenLabel->adjustSize();
    this->blueLabel->adjustSize();
    this->opacityLabel->adjustSize();
}

void ColorDialog::showEvent(QShowEvent *event)
{
    this->updateStyle();
    MaskDialogBase::showEvent(event);
}

void ColorDialog::__connectSignalToSlot()
{
    connect(this->cancelButton, &QPushButton::clicked, this, &ColorDialog::reject);
    connect(this->yesButton, &PrimaryPushButton::clicked, this, &ColorDialog::__onYesButtonClicked);

    connect(this->huePanel, &HuePanel::colorChanged, this, &ColorDialog::__onHueChanged);
    connect(this->brightSlider, &BrightnessSlider::colorChanged, this, &ColorDialog::__onBrightnessChanged);

    connect(this->redLineEdit, &ColorLineEdit::valueChanged, this, &ColorDialog::__onRedChanged);
    connect(this->blueLineEdit, &ColorLineEdit::valueChanged, this, &ColorDialog::__onBlueChanged);
    connect(this->greenLineEdit, &ColorLineEdit::valueChanged, this, &ColorDialog::__onGreenChanged);
    connect(this->hexLineEdit, &HexColorLineEdit::valueChanged, this, &ColorDialog::__onHexColorChanged);
    connect(this->opacityLineEdit, &OpacityLineEdit::valueChanged, this, &ColorDialog::__onOpacityChanged);
}