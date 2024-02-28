#include "image_utils.h"


/*
QPixmap gaussianBlur(QVariant image, int blurRadius, int brightFactor, std::tuple<int,int> blurPicSize)
{
    QImage _image;
    if(image.canConvert<QString>()){
        _image = QImage(image.value<QString>());
    }else if(image.canConvert<QPixmap>()){
        _image = image.value<QPixmap>().toImage();
    }else if(image.canConvert<QImage>()){
        _image = QImage(image.value<QImage>());
    }

    if(std::get<0>(blurPicSize) != 0 && std::get<1>(blurPicSize) != 0){
        int w = _image.width();
        int h = _image.height();
        int ratio = qMin(std::get<0>(blurPicSize) / w, std::get<1>(blurPicSize) / h);
        int w_ = w * ratio;
        int h_ = h * ratio;

        if(w_ < w){
            _image = _image.scaled(QSize(w_, h_), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        }
    }

    if(_image.format() == QImage::Format_Indexed8 || _image.format() == QImage::Format_Grayscale8){
        _image = _image.convertToFormat(QImage::Format_RGB888);
    }

    cv::Mat cvImage = cv::Mat(_image.height(), _image.width(), CV_8UC3, const_cast<uchar*>(_image.bits()), _image.bytesPerLine());
    
    for(int i = 0; i < cvImage.channels(); ++i){
        cv::Mat channel = cvImage.clone();
        cv::GaussianBlur(channel, channel, cv::Size(blurRadius, blurRadius), 0, 0);
        cvImage = brightFactor * channel;
    }
    
    QImage qImage(cvImage.data, cvImage.cols, cvImage.rows, cvImage.step, QImage::Format_RGB888);
    return QPixmap::fromImage(qImage);

}
*/


QPixmap gaussianBlur(QVariant image, int blurRadius, int brightFactor, std::tuple<int,int> blurPicSize)
{
    QImage _image;
    if(image.canConvert<QString>()){
        _image = QImage(image.value<QString>());
    }else if(image.canConvert<QPixmap>()){
        _image = image.value<QPixmap>().toImage();
    }else if(image.canConvert<QImage>()){
        _image = QImage(image.value<QImage>());
    }

    return QPixmap::fromImage(_image);
}
