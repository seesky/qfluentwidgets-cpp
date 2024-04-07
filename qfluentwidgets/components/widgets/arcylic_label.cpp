#include "arcylic_label.h"

bool checkAcrylicAvailability()
{
    if(!isAcrylicAvailable){
        qDebug() << QString("`AcrylicLabel` is not supported in current qfluentwidgets.");
    }
    
    return isAcrylicAvailable;   
}


BlurCoverThread::BlurCoverThread(QObject *parent) : QThread(parent)
{
    this->imagePath = QString();
    this->blurRadius = 7;
    this->maxSize = std::make_tuple(0, 0);
}

void BlurCoverThread::run()
{
    if(this->imagePath.isNull()){
        return;
    }

    QPixmap pixmap = gaussianBlur(QVariant::fromValue<QString>(this->imagePath), this->blurRadius, 0.85, this->maxSize);
    emit(this->blurFinished(pixmap));
}

void BlurCoverThread::blur(QString imagePath, int blurRadius, std::tuple<int, int> maxSize = std::tuple<int,int>(450,450))
{
    this->imagePath = imagePath;
    this->blurRadius = blurRadius;
    this->maxSize = maxSize;
    this->start();
}

AcrylicTextureLabel::AcrylicTextureLabel(QColor tintColor, QColor luminosityColor, float noiseOpacity, QWidget *parent) : QLabel(parent)
{
    this->tintColor = QColor(tintColor);
    this->luminosityColor = QColor(luminosityColor);
    this->nosieOpacity = nosieOpacity;
    this->nosizeImage = QImage("qfluentwidgets/images/acrylic/noise.png");
    this->setAttribute(Qt::WA_TranslucentBackground);
}


void AcrylicTextureLabel::setTintColor(QColor color)
{
    this->tintColor = color;
    this->update();
}

void AcrylicTextureLabel::paintEvent(QPaintEvent *e)
{
    QImage acrylicTexture = QImage(64, 64, QImage::Format_ARGB32_Premultiplied);

    acrylicTexture.fill(this->luminosityColor);

    QPainter *painter = new QPainter(&acrylicTexture);
    painter->fillRect(acrylicTexture.rect(), this->tintColor);

    painter->setOpacity(this->nosieOpacity);
    painter->drawImage(acrylicTexture.rect(), this->nosizeImage);

    QBrush acrylicBrush = QBrush(acrylicTexture);
    painter->end();

    painter = new QPainter(this);
    painter->fillRect(this->rect(), acrylicBrush);
    painter->end();
}


AcrylicLabel::AcrylicLabel(int blurRadius, QColor tintColor, QColor luminosityColor, std::tuple<int,int> maxBlurSize, QWidget *parent) : QLabel(parent)
{
    checkAcrylicAvailability();
    this->imagePath = QString();
    this->blurPixmap = QPixmap();
    this->blurRadius = blurRadius;
    this->maxBlurSize = maxBlurSize;
    this->acrylicTextureLabel = new AcrylicTextureLabel(tintColor, luminosityColor, 0.03, this);
    this->blurThread = new BlurCoverThread(this);
    connect(this->blurThread, &BlurCoverThread::blurFinished, this, &AcrylicLabel::__onBlurFinished);
}

void AcrylicLabel::__onBlurFinished(QPixmap blurPixmap)
{
    this->blurPixmap = blurPixmap;
    this->setPixmap(this->blurPixmap);
    this->adjustSize();
}

void AcrylicLabel::setImage(QString imagePath)
{
    this->imagePath = imagePath;
    this->blurThread->blur(imagePath, this->blurRadius, this->maxBlurSize);
}

void AcrylicLabel::setTintColor(QColor color)
{
    this->acrylicTextureLabel->setTintColor(color);
}

void AcrylicLabel::resizeEvent(QResizeEvent *event)
{
    QLabel::resizeEvent(event);
    this->acrylicTextureLabel->resize(this->size());

    if(!this->blurPixmap.isNull() && this->blurPixmap.size() != this->size()){
        this->setPixmap(this->blurPixmap.scaled(this->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
    }
}

AcrylicBrush::AcrylicBrush(QWidget *device, int blurRadius, QColor tintColor = QColor(242, 242, 242, 150), QColor luminosityColor = QColor(255, 255, 255, 10), float noiseOpacity=0.03)
{
    this->device = device;
    this->blurRadius = blurRadius;
    this->tintColor = QColor(tintColor);
    this->luminosityColor = QColor(luminosityColor);
    this->noiseOpacity = noiseOpacity;
    this->noiseImage = QImage("qfluentwidgets/images/acrylic/noise.png");
    this->originalImage = QPixmap();
    this->image = QPixmap();
    this->clipPath = QPainterPath();
}

void AcrylicBrush::setBlurRadius(int radius)
{  
    if(radius == this->blurRadius){
        return;
    }

    this->blurRadius = radius;
    this->setImage(this->originalImage);
}

void AcrylicBrush::setTintColor(QColor color)
{
    this->tintColor = QColor(color);
    this->device->update();
}

void AcrylicBrush::setLuminosityColor(QColor color)
{
    this->luminosityColor = QColor(color);
    this->device->update();
}

bool AcrylicBrush::isAvailable()
{
    return isAcrylicAvailable;
}

void AcrylicBrush::grabImage(QRect rect)
{
    QScreen *screen = QApplication::screenAt(this->device->window()->pos());
    if(screen == nullptr){
        screen = QApplication::screens()[0];
    }

    int x = rect.x();
    int y = rect.y();
    int w = rect.width();
    int h = rect.height();

    this->setImage(screen->grabWindow(0, x, y, w, h));
}

void AcrylicBrush::setImage(QVariant image)
{
    QPixmap _image;
    if(image.canConvert<QString>()){
        _image = QPixmap(image.value<QString>());
    }else if(image.canConvert<QPixmap>()){
        _image = image.value<QPixmap>();
    }else{
        _image = QPixmap::fromImage(image.value<QImage>());
    }

    this->originalImage = _image;
    if(!_image.isNull()){
        checkAcrylicAvailability();
        this->image = gaussianBlur(_image, this->blurRadius, 1, std::tuple<int,int>(0,0));
    }

    this->device->update();
}

void AcrylicBrush::setClipPath(QPainterPath path)
{
    this->clipPath = path;
    this->device->update();
}

QImage *AcrylicBrush::textureImage()
{
    QImage *texture = new QImage(64, 64, QImage::Format_ARGB32_Premultiplied);
    texture->fill(this->luminosityColor);

    //QPainter *painter = new QPainter(&texture);
    QPainter painter(texture);
    painter.fillRect(texture->rect(), this->tintColor);

    painter.setOpacity(this->noiseOpacity);
    painter.drawImage(texture->rect(), this->noiseImage);

    return texture;
}

void AcrylicBrush::paint()
{
    QWidget *device = this->device;

    //QPainter *painter = new QPainter(device);
    QPainter painter(device);
    painter.setRenderHints(QPainter::Antialiasing);

    if(!this->clipPath.isEmpty()){
        painter.setClipPath(this->clipPath);
    }

    QSize ds = device->size();
    QPixmap image = this->image.scaled(ds, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    painter.drawPixmap(0, 0, image);

    QRect r = device->rect();
    QBrush b = QBrush(*(this->textureImage()));
    painter.fillRect(r, b);
}

