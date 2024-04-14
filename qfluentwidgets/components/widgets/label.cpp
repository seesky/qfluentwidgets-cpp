#include "label.h"

PixmapLabel::PixmapLabel(QWidget *parent) : QLabel(parent)
{
    this->__pixmap = new QPixmap();
}

void PixmapLabel::setPixmap(QPixmap *pixmap)
{
    this->__pixmap = pixmap;
    this->setFixedSize(pixmap->size());
    this->update();
}

QPixmap *PixmapLabel::pixmap()
{
    return this->__pixmap;
}

void PixmapLabel::paintEvent(QPaintEvent *e)
{
    if(this->__pixmap->isNull()){
        return QLabel::paintEvent(e);
    }

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    painter.setPen(Qt::NoPen);
    painter.drawPixmap(this->rect(), *(this->__pixmap));
}


FluentLabelBase::FluentLabelBase(QWidget *parent) : QLabel(parent)
{
    //this->_init();
}

FluentLabelBase::FluentLabelBase(QString text, QWidget *parent) : QLabel(parent)
{
    //this->_init();
    this->setText(text);
}

void FluentLabelBase::_init()
{
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("LABEL"), Theme::AUTO);
    this->setFont(this->getFont());
    this->setTextColor(QColor(0, 0, 0), QColor(255, 255, 255));

    /* //TODO需要实现config
    QMetaObject::Connection conn = connect(qconfig, &QConfig::themeChanged, this, [this](){
        this->setTextColor(this->getLightColor(), this->getDarkColor());
    });

    connect(this, &FluentLabelBase::destroy, this, [](){
        disconnect(conn);
    });
    */
}


void FluentLabelBase::setTextColor(QColor light = QColor(0, 0, 0), QColor dark = QColor(255, 255, 255))
{
    this->_lightColor = QColor(light);
    this->_darkColor = QColor(dark);

    setCustomStyleSheet(this, 
                        QString("FluentLabelBase{{color:{%1}}}").arg(this->getLightColor().name()),
                        QString("FluentLabelBase{{color:{%1}}}").arg(this->getDarkColor().name())
    );
                    
}

QColor FluentLabelBase::getLightColor()
{
    return this->_lightColor;
}

void FluentLabelBase::setLightColor(QColor color)
{
    this->setTextColor(color, this->getDarkColor());
}

QColor FluentLabelBase::getDarkColor()
{
    return this->_darkColor;
}

void FluentLabelBase::setDarkColor(QColor color)
{
    this->setTextColor(this->getLightColor(), color);
}

int FluentLabelBase::getPixelFontSize()
{
    return this->font().pixelSize();
}

void FluentLabelBase::setPixelFontSize(int size)
{
    QFont font = this->font();
    font.setPixelSize(size);
    this->setFont(font);
}

bool FluentLabelBase::getStrikeOut()
{
    return this->font().strikeOut();
}

void FluentLabelBase::setStrikeOut(bool isStrikeOut)
{
    QFont font = this->font();
    font.setStrikeOut(isStrikeOut);
    this->setFont(font);
}

bool FluentLabelBase::getUnderline()
{
    return this->font().underline();
}

void FluentLabelBase::setUnderline(bool isUnderline)
{
    QFont font = this->font();
    //font.setStyle();  //TODO:特殊关注
    font.setUnderline(isUnderline);
    this->setFont(font);
}

CaptionLabel::CaptionLabel(QWidget *parent) : FluentLabelBase(parent)
{
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("LABEL"), Theme::AUTO);
    this->setFont(this->getFont());
    this->setTextColor(QColor(0, 0, 0), QColor(255, 255, 255));
}

CaptionLabel::CaptionLabel(QString text, QWidget *parent) : FluentLabelBase(text, parent)
{
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("LABEL"), Theme::AUTO);
    this->setFont(this->getFont());
    this->setTextColor(QColor(0, 0, 0), QColor(255, 255, 255));
}


QFont CaptionLabel::getFont()
{
    return Font().getFont(12, QFont::Normal);
}


BodyLabel::BodyLabel(QWidget *parent) : FluentLabelBase(parent)
{
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("LABEL"), Theme::AUTO);
    this->setFont(this->getFont());
    this->setTextColor(QColor(0, 0, 0), QColor(255, 255, 255));
}


BodyLabel::BodyLabel(QString text, QWidget *parent) : FluentLabelBase(text, parent)
{
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("LABEL"), Theme::AUTO);
    this->setFont(this->getFont());
    this->setTextColor(QColor(0, 0, 0), QColor(255, 255, 255));
}


QFont BodyLabel::getFont()
{
    return Font().getFont(14, QFont::Normal);
}


StrongBodyLabel::StrongBodyLabel(QWidget *parent) : FluentLabelBase(parent)
{
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("LABEL"), Theme::AUTO);
    this->setFont(this->getFont());
    this->setTextColor(QColor(0, 0, 0), QColor(255, 255, 255));
}

StrongBodyLabel::StrongBodyLabel(QString text, QWidget *parent) : FluentLabelBase(text, parent)
{
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("LABEL"), Theme::AUTO);
    this->setFont(this->getFont());
    this->setTextColor(QColor(0, 0, 0), QColor(255, 255, 255));
}


QFont StrongBodyLabel::getFont()
{
    return Font().getFont(14, QFont::DemiBold);
}

SubtitleLabel::SubtitleLabel(QWidget *parent) : FluentLabelBase(parent)
{
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("LABEL"), Theme::AUTO);
    this->setFont(this->getFont());
    this->setTextColor(QColor(0, 0, 0), QColor(255, 255, 255));
}

SubtitleLabel::SubtitleLabel(QString text, QWidget *parent) : FluentLabelBase(text, parent)
{
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("LABEL"), Theme::AUTO);
    this->setFont(this->getFont());
    this->setTextColor(QColor(0, 0, 0), QColor(255, 255, 255));
}

QFont SubtitleLabel::getFont()
{
    return Font().getFont(20, QFont::DemiBold);
}


TitleLabel::TitleLabel(QWidget *parent) : FluentLabelBase(parent)
{
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("LABEL"), Theme::AUTO);
    this->setFont(this->getFont());
    this->setTextColor(QColor(0, 0, 0), QColor(255, 255, 255));
}


TitleLabel::TitleLabel(QString text, QWidget *parent) : FluentLabelBase(text, parent)
{
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("LABEL"), Theme::AUTO);
    this->setFont(this->getFont());
    this->setTextColor(QColor(0, 0, 0), QColor(255, 255, 255));
}


QFont TitleLabel::getFont()
{
    return Font().getFont(28, QFont::DemiBold);
}


LargeTitleLabel::LargeTitleLabel(QWidget *parent) : FluentLabelBase(parent)
{
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("LABEL"), Theme::AUTO);
    this->setFont(this->getFont());
    this->setTextColor(QColor(0, 0, 0), QColor(255, 255, 255));
}

LargeTitleLabel::LargeTitleLabel(QString text, QWidget *parent) : FluentLabelBase(text, parent)
{
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("LABEL"), Theme::AUTO);
    this->setFont(this->getFont());
    this->setTextColor(QColor(0, 0, 0), QColor(255, 255, 255));
}

QFont LargeTitleLabel::getFont()
{
    return Font().getFont(40, QFont::DemiBold);
}


DisplayLabel::DisplayLabel(QWidget *parent) : FluentLabelBase(parent)
{
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("LABEL"), Theme::AUTO);
    this->setFont(this->getFont());
    this->setTextColor(QColor(0, 0, 0), QColor(255, 255, 255));
}


DisplayLabel::DisplayLabel(QString text, QWidget *parent) : FluentLabelBase(text, parent)
{
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("LABEL"), Theme::AUTO);
    this->setFont(this->getFont());
    this->setTextColor(QColor(0, 0, 0), QColor(255, 255, 255));
}


QFont DisplayLabel::getFont()
{
    return Font().getFont(68, QFont::DemiBold);
}

ImageLabel::ImageLabel(QWidget *parent) : QLabel(parent)
{
    this->image = QImage();
    this->setBorderRadius(0, 0, 0, 0);
    this->_postInit();
}

ImageLabel::ImageLabel(QString image, QWidget *parent) : QLabel(parent)
{
    this->image = QImage();
    this->setBorderRadius(0, 0, 0, 0);
    QVariant *imageQVariant = new QVariant(QVariant::fromValue<QString>(image));
    this->setImage(imageQVariant);
    this->_postInit();
}

ImageLabel::ImageLabel(QImage image, QWidget *parent) : QLabel(parent)
{
    this->image = QImage();
    this->setBorderRadius(0, 0, 0, 0);
    QVariant *imageQVariant = new QVariant(QVariant::fromValue<QImage>(image));
    this->setImage(imageQVariant);
    this->_postInit();
}

ImageLabel::ImageLabel(QPixmap image, QWidget *parent) : QLabel(parent)
{
    this->image = QImage();
    this->setBorderRadius(0, 0, 0, 0);
    QVariant *imageQVariant = new QVariant(QVariant::fromValue<QPixmap>(image));
    //qDebug() << QString(imageQVariant->typeName());
    this->setImage(imageQVariant);
    this->_postInit();
}


void ImageLabel::_onFrameChanged(int index)
{
    this->image = this->movie()->currentImage();
    this->update();
}

void ImageLabel::setBorderRadius(int topLeft, int topRight, int bottomLeft, int bottomRight)
{
    this->_topLeftRadius = topLeft;
    this->_topRightRadius = topRight;
    this->_bottomLeftRadius = bottomLeft;
    this->_bottomRightRadius = bottomRight;
    this->update();
}

void ImageLabel::setImage(QVariant* image)
{

    if(image->canConvert<QString>()){
        //qDebug() << image->value<QString>();
        QImageReader reader(image->value<QString>());
        if(reader.supportsAnimation()){
            QMovie* _m = new QMovie(image->value<QString>());
            this->setMovie(_m);
        }else{
            this->image = reader.read();
        }
    }else if(image->canConvert<QPixmap>()){
        this->image = image->value<QPixmap>().toImage();
    }

    this->setFixedSize(this->image.size());
    this->update();
}


void ImageLabel::scaledToWidth(int width)
{
    if(this->isNull()){
        return;
    }

    int _width = this->image.width();
    int _height = this->image.height();
    int h = int((float)width / this->image.width() * this->image.height()); //TODO:特殊关注
    this->setFixedSize(width, h);

    if(this->movie()){
        this->movie()->setScaledSize(QSize(width, h));
    }
}


void ImageLabel::scaledToHeight(int height)
{
    if(this->isNull()){
        return;
    }

    int w = int(float(height) / this->image.height() * this->image.width());
    this->setFixedSize(w, height);

    if(this->movie()){
        this->movie()->setScaledSize(QSize(w, height));
    }
}

bool ImageLabel::isNull()
{
    return this->image.isNull();
}

void ImageLabel::mouseReleaseEvent(QMouseEvent *event)
{
    QLabel::mouseReleaseEvent(event);
    emit(this->clicked());
}

void ImageLabel::setPixmap(QPixmap pixmap)
{
    QVariant *imageQVariant = new QVariant(QVariant::fromValue<QPixmap>(pixmap));
    this->setImage(imageQVariant);
}

QPixmap ImageLabel::pixmap()
{
    return QPixmap::fromImage(this->image);
}

void ImageLabel::setMovie(QMovie *movie)
{
    QLabel::setMovie(movie);
    this->movie()->start();
    this->image = this->movie()->currentImage();
    connect(this->movie(), &QMovie::frameChanged, this, &ImageLabel::_onFrameChanged);
}


void ImageLabel::paintEvent(QPaintEvent *e)
{
    if(this->isNull()){
        return;
    }

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    QPainterPath path = QPainterPath();
    int w = this->width();
    int h = this->height();

    path.moveTo(this->getTopLeftRadius(), 0);
    path.lineTo(w - this->getTopRightRadius(), 0);

    int d = this->getTopRightRadius() * 2;
    path.arcTo(w - d, 0, d, d, 90, -90);

    path.lineTo(w, h - this->getBottomRightRadius());

    d = this->getBottomRightRadius() * 2;
    path.arcTo(w - d, h - d, d, d, 0, -90);

    path.lineTo(this->getBottomLeftRadius(), h);

    d = this->getBottomLeftRadius() * 2;
    path.arcTo(0, h - d, d, d, -90, -90);

    path.lineTo(0, this->getTopLeftRadius());

    d = this->getTopLeftRadius() * 2;
    path.arcTo(0, 0, d, d, -180, -90);

    QImage _image = this->image.scaled(this->size() * this->devicePixelRatioF(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    painter.setPen(Qt::NoPen);
    painter.setClipPath(path);
    painter.drawImage(this->rect(), _image);
}

int ImageLabel::getTopLeftRadius()
{
    return this->_topLeftRadius;
}

void ImageLabel::setTopLeftRadius(int radius)
{
    this->setBorderRadius(radius, this->getTopRightRadius(), this->getBottomLeftRadius(), this->getBottomRightRadius());
}

int ImageLabel::getTopRightRadius()
{
    return this->_topRightRadius;
}

void ImageLabel::setTopRightRadius(int radius)
{
    this->setBorderRadius(this->getTopLeftRadius(), radius, this->getBottomLeftRadius(), this->getBottomRightRadius());
}

int ImageLabel::getBottomLeftRadius()
{
    return this->_bottomLeftRadius;
}

void ImageLabel::setBottomLeftRadius(int radius)
{
    this->setBorderRadius(this->getTopLeftRadius(), this->getTopRightRadius(), radius, this->getBottomLeftRadius());
}

int ImageLabel::getBottomRightRadius()
{
    return this->_bottomRightRadius;
}

void ImageLabel::setBottomRightRadius(int radius)
{
    this->setBorderRadius(this->getTopLeftRadius(), this->getTopRightRadius(), this->getBottomLeftRadius(), radius);
}


void AvatarWidget::_postInit()
{
    this->setRadius(48);
}

int AvatarWidget::getRadius()
{
    return this->_radius;
}

void AvatarWidget::setRadius(int radius)
{
    this->_radius = radius;
    this->setFixedSize(2 * radius, 2 * radius);
    this->update();
}

void AvatarWidget::paintEvent(QPaintEvent *e)
{
    if(this->isNull()){
        return;
    }

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    QImage _image = this->image.scaled(this->size()*this->devicePixelRatioF(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

    int iw = _image.width();
    int ih = _image.height();
    int d = this->getRadius() * 2 * this->devicePixelRatioF();
    int x = (iw - d) / 2;
    int y = (ih - d) / 2;
    _image = _image.copy(int(x), int(y), int(d), int(d));

    QPainterPath path = QPainterPath();
    path.addEllipse(QRectF(this->rect()));

    painter.setPen(Qt::NoPen);
    painter.setClipPath(path);
    painter.drawImage(this->rect(), _image);

}


HyperlinkLabel::HyperlinkLabel(QWidget *parent) : QPushButton(parent)
{
    this->_url = QUrl();

    Font().setFont(this, 14, QFont::Normal);
    this->setUnderlineVisible(false);
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("LABEL"), Theme::AUTO);
    this->setCursor(Qt::PointingHandCursor);
    connect(this, &HyperlinkLabel::clicked, this, &HyperlinkLabel::_onClicked);
}

HyperlinkLabel::HyperlinkLabel(QString text, QWidget *parent) : QPushButton(parent)
{
    this->_url = QUrl();

    Font().setFont(this, 14, QFont::Normal);
    this->setUnderlineVisible(false);
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("LABEL"), Theme::AUTO);
    this->setCursor(Qt::PointingHandCursor);
    connect(this, &HyperlinkLabel::clicked, this, &HyperlinkLabel::_onClicked);
    this->setText(text);
}

HyperlinkLabel::HyperlinkLabel(QUrl url, QString text, QWidget *parent) : QPushButton(parent)
{
    this->_url = QUrl();

    Font().setFont(this, 14, QFont::Normal);
    this->setUnderlineVisible(false);
    FluentStyleSheet().apply(this, FluentStyleSheetMap.value("LABEL"), Theme::AUTO);
    this->setCursor(Qt::PointingHandCursor);
    connect(this, &HyperlinkLabel::clicked, this, &HyperlinkLabel::_onClicked);
    
    this->setText(text);
    this->_url = url;
}

QUrl HyperlinkLabel::getUrl()
{
    return this->_url;
}

void HyperlinkLabel::setUrl(QVariant url)
{
    if(url.canConvert<QString>()){
        this->_url = QUrl(url.value<QString>());
    }else if(url.canConvert<QUrl>()){
        this->_url = QUrl(url.value<QUrl>());
    }
}

bool HyperlinkLabel::isUnderlineVisible()
{
    return this->_isUnderlineVisible;
}

void HyperlinkLabel::setUnderlineVisible(bool isVisible)
{
    this->_isUnderlineVisible = isVisible;
    this->setProperty("underline", isVisible);
    this->setStyle(QApplication::style());
}

void HyperlinkLabel::_onClicked()
{
    if(this->getUrl().isValid()){
        QDesktopServices::openUrl(this->getUrl());
    }
}

