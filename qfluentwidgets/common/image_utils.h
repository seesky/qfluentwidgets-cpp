#pragma once

#include <QtGui/QImage>
#include <QtGui/QPixmap>
#include <QtCore/QVariant>
//#include "opencv.hpp"

QPixmap gaussianBlur(QVariant image, int blurRadius, int brightFactor, std::tuple<int,int> blurPicSize);

//TODO: class DominantColor