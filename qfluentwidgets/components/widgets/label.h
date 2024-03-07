#pragma once

#include <QtCore/Qt>
#include <QtCore/QPoint>
#include <QtCore/QSize>
#include <QtCore/QRectF>
#include <QtCore/QUrl>
#include <QtGui/QPixmap>
#include <QtGui/QPainter>
#include <QtGui/QPalette>
#include <QtGui/QColor>
#include <QtGui/QFont>
#include <QtGui/QImage>
#include <QtGui/QPainterPath>
#include <QtGui/QImageReader>
#include <QtGui/QBrush>
#include <QtGui/QMovie>
#include <QtGui/QDesktopServices>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>

#include "../../common/font.h"
#include "../../common/style_sheet.h"
#include "../../common/config.h"

class PixmapLabel : public QLabel{
    Q_OBJECT
public:
    PixmapLabel(QWidget *parent);
    void setPixmap(QPixmap *pixmap);
    QPixmap *pixmap();
    void paintEvent(QPaintEvent *e);

    QPixmap *__pixmap;
};


class FluentLabelBase : public QLabel{
    Q_OBJECT
public:
    FluentLabelBase(QWidget *parent);
    FluentLabelBase(QString text, QWidget *parent);
    void _init();
    virtual QFont getFont(){};
    void setTextColor(QColor light, QColor dark);
    QColor getLightColor();
    void setLightColor(QColor color);
    QColor getDarkColor();
    void setDarkColor(QColor color);
    int getPixelFontSize();
    void setPixelFontSize(int size);
    bool getStrikeOut();
    void setStrikeOut(bool isStrikeOut);
    bool getUnderline();
    void setUnderline(bool isUnderline);

    QColor _lightColor;
    QColor _darkColor;
};


class CaptionLabel : public FluentLabelBase{
    Q_OBJECT
public:
    CaptionLabel(QWidget *parent) : FluentLabelBase(parent){};
    CaptionLabel(QString text, QWidget *parent) : FluentLabelBase(text, parent){};

    QFont getFont() override; 
};


class BodyLabel : public FluentLabelBase{
    Q_OBJECT
public:
    BodyLabel(QWidget *parent) : FluentLabelBase(parent){};
    BodyLabel(QString text, QWidget *parent) : FluentLabelBase(text, parent){};

    QFont getFont() override; 
};


class StrongBodyLabel : public FluentLabelBase{
    Q_OBJECT
public:
    StrongBodyLabel(QWidget *parent) : FluentLabelBase(parent){};
    StrongBodyLabel(QString text, QWidget *parent) : FluentLabelBase(text, parent){};

    QFont getFont() override; 
};


class SubtitleLabel : public FluentLabelBase{
    Q_OBJECT
public:
    SubtitleLabel(QWidget *parent) : FluentLabelBase(parent){};
    SubtitleLabel(QString text, QWidget *parent);

    QFont getFont() override; 
};


class TitleLabel : public FluentLabelBase{
    Q_OBJECT
public:
    TitleLabel(QWidget *parent) : FluentLabelBase(parent){};
    TitleLabel(QString text, QWidget *parent) : FluentLabelBase(text, parent){};

    QFont getFont() override; 
};


class LargeTitleLabel : public FluentLabelBase{
    Q_OBJECT
public:
    LargeTitleLabel(QWidget *parent) : FluentLabelBase(parent){};
    LargeTitleLabel(QString text, QWidget *parent) : FluentLabelBase(text, parent){};

    QFont getFont() override; 
};

class DisplayLabel : public FluentLabelBase{
    Q_OBJECT
public:
    DisplayLabel(QWidget *parent) : FluentLabelBase(parent){};
    DisplayLabel(QString text, QWidget *parent) : FluentLabelBase(text, parent){};

    QFont getFont() override; 
};


class ImageLabel : public QLabel{
    Q_OBJECT
public:
    ImageLabel(QWidget *parent);
    ImageLabel(QString image, QWidget *parent);
    ImageLabel(QImage image, QWidget *parent);
    ImageLabel(QPixmap image, QWidget *parent);
    virtual void _postInit(){};
    void setBorderRadius(int topLeft, int topRight, int bottomLeft, int bottomRight);
    void setImage(QVariant image);
    void scaledToWidth(int width);
    void scaledToHeight(int height);
    bool isNull();
    void mouseReleaseEvent(QMouseEvent *event) override;
    void setPixmap(QPixmap pixmap);
    QPixmap pixmap();
    void setMovie(QMovie *movie);
    void paintEvent(QPaintEvent *e) override;
    int getTopLeftRadius();
    void setTopLeftRadius(int radius);
    int getTopRightRadius();
    void setTopRightRadius(int radius);
    int getBottomLeftRadius();
    void setBottomLeftRadius(int radius);
    int getBottomRightRadius();
    void setBottomRightRadius(int radius);

    QImage image;
    int _topLeftRadius;
    int _topRightRadius;
    int _bottomLeftRadius;
    int _bottomRightRadius;
signals:
    void clicked(); 

public slots:
    void _onFrameChanged(int index);
};


class AvatarWidget : public ImageLabel{
    Q_OBJECT
    Q_PROPERTY(int radius READ getRadius WRITE setRadius)
public:
    AvatarWidget(QWidget *parent) : ImageLabel(parent){};
    AvatarWidget(QString image, QWidget *parent) : ImageLabel(image, parent){};
    AvatarWidget(QImage image, QWidget *parent) : ImageLabel(image, parent){};
    AvatarWidget(QPixmap image, QWidget *parent) : ImageLabel(image, parent){};

    void _postInit() override;
    int getRadius();
    void setRadius(int radius);
    void paintEvent(QPaintEvent *e) override;

    int _radius; 
};


class HyperlinkLabel : public QPushButton{
    Q_OBJECT
    Q_PROPERTY(QUrl url READ getUrl WRITE setUrl)
    Q_PROPERTY(bool underlineVisible READ isUnderlineVisible WRITE setUnderlineVisible)
public:
    HyperlinkLabel(QWidget *parent);
    HyperlinkLabel(QString text, QWidget *parent);
    HyperlinkLabel(QUrl url, QString text, QWidget *parent);

    QUrl getUrl();
    void setUrl(QVariant url);
    bool isUnderlineVisible();
    void setUnderlineVisible(bool isVisible);

    QUrl _url;
    bool _isUnderlineVisible;
public slots:
    void _onClicked();
};