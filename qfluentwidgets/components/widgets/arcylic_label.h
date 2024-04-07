#pragma once

#include <QtCore/Qt>
#include <QtCore/QDebug>
#include <QtCore/QVariant>
#include <QtCore/Qt>
#include <QtCore/QThread>
#include <QtCore/QRect>
#include <QtGui/QBrush>
#include <QtGui/QColor>
#include <QtGui/QImage>
#include <QtGui/QPainter>
#include <QtGui/QPixmap>
#include <QtGui/QPainterPath>
#include <QtWidgets/QLabel>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtGui/QScreen>
#include "../../common/image_utils.h"

static bool isAcrylicAvailable = false;  //TODO:需要动态判断是否支持

bool checkAcrylicAvailability();

class BlurCoverThread : public QThread{
    Q_OBJECT
public:
    BlurCoverThread(QObject *parent);
    void run() override;
    void blur(QString imagePath, int blurRadius, std::tuple<int, int> maxSize);

    QString imagePath;
    int blurRadius;
    std::tuple<int,int> maxSize;

signals:
    void blurFinished(QPixmap);
};


class AcrylicTextureLabel : public QLabel{
    Q_OBJECT
public:
    AcrylicTextureLabel(QColor tintColor, QColor luminosityColor, float noiseOpacity, QWidget *parent);
    void setTintColor(QColor color);
    void paintEvent(QPaintEvent *e) override;

    QColor tintColor;
    QColor luminosityColor;
    float nosieOpacity;
    QImage nosizeImage;
};


class AcrylicLabel : public QLabel{
    Q_OBJECT
public:
    AcrylicLabel(int blurRadius, QColor tintColor, QColor luminosityColor, std::tuple<int,int> maxBlurSize, QWidget *parent);
    void __onBlurFinished(QPixmap blurPixmap);
    void setImage(QString imagePath);
    void setTintColor(QColor color);
    void resizeEvent(QResizeEvent *event) override;

    QString imagePath;
    QPixmap blurPixmap;
    int blurRadius;
    std::tuple<int,int> maxBlurSize;
    AcrylicTextureLabel *acrylicTextureLabel;
    BlurCoverThread *blurThread;
};


class AcrylicBrush{
public:
    AcrylicBrush(QWidget *device, int blurRadius, QColor tintColor, QColor luminosityColor, float noiseOpacity);
    void setBlurRadius(int radius);
    void setTintColor(QColor color);
    void setLuminosityColor(QColor color);
    bool isAvailable();
    void grabImage(QRect rect);
    void setImage(QVariant image);
    void setClipPath(QPainterPath path);
    QImage *textureImage();
    void paint();

    QWidget *device;
    int blurRadius;
    QColor tintColor;
    QColor luminosityColor;
    float noiseOpacity;
    QImage noiseImage;
    QPixmap originalImage;
    QPixmap image;
    QPainterPath clipPath;
};