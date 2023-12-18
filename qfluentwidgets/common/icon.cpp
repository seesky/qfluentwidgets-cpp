#include "icon.h"
#include "config.h"
#include <QFile>
#include <QtXml/QDomDocument>

//namespace Qfw{

void drawSvgIcon(QVariant *icon, QPainter *painter, QRect *rect)
{   
    if(icon->canConvert<QString>())
    {
        QSvgRenderer *renderer = new QSvgRenderer(icon->value<QString>());
        renderer->render(painter, QRectF(*rect));
    }else if(icon->canConvert<QByteArray>()){
        QSvgRenderer *renderer = new QSvgRenderer(icon->value<QByteArray>());
        renderer->render(painter, QRectF(*rect));
    }
}

QString getIconColor(Theme theme = Theme::AUTO, bool reverse = false)
{
    QColor *color;
    QString lc,dc;
    if(!reverse){
        lc = "black";
        dc = "white";
    }else{
        lc = "white";
        dc = "black";
    }

    if(theme == Theme::AUTO)
    {
        if(isDarkTheme())
        {
            return dc;
        }else{
            return lc;
        }
    }else{
        if(theme == Theme::DARK)
        {
            return dc;
        }else{
            return lc;
        }
    }
}

QString writeSvg(QString iconPath, int indexes, std::map<QString, QString> attributes)
{
    if(!iconPath.endsWith(".svg"))
    {
        return "";
    }

    QFile *f = new QFile(iconPath);
    f->open(QFile::ReadOnly);

    QDomDocument *dom = new QDomDocument();
    dom->setContent(f->readAll());
    f->close();

    QDomNodeList pathNodes = dom->elementsByTagName("path");
    if(!indexes){
        indexes = pathNodes.length();
    }

    for(int i = 0; i < indexes; i++){
        QDomElement element = pathNodes.at(i).toElement();
        for (auto it = attributes.begin(); it != attributes.end(); ++it) {
            element.setAttribute(it->first, it->second);
        }
    }

    return dom->toString();
}

void drawIcon(QVariant icon, QPainter painter, QRect rect, std::map<QString, QString> attributes, QIcon::State state = QIcon::State::Off)
{
    if(icon.canConvert<FluentIconBase>())
    {   //TODO: icon.render(painter, rect, **attributes)
        //icon.value<FluentIconBase>().render(&painter, &rect, Theme::AUTO, attributes);
    }else if(icon.canConvert<Icon>()){
        icon.value<Icon>().fluentIcon->render(&painter, &rect, Theme::AUTO, 0, attributes);
    }
}

QString FluentIcon::path(QString fluentIconName, Theme theme = Theme::AUTO)
{
    return ":/qfluentwidgets/images/icons/" + FluentIconMap.at(fluentIconName) + "_" + getIconColor(theme) + ".svg";
}

SvgIconEngine::SvgIconEngine(QVariant *svg)
{
    this->svg = svg;
}

void SvgIconEngine::paint(QPainter *painter, QRect *rect, QIcon::Mode mode, QIcon::State state)
{
    drawSvgIcon(this->svg, painter, rect);
}

SvgIconEngine *SvgIconEngine::clone()
{
    return new SvgIconEngine(this->svg);
}

QPixmap *SvgIconEngine::pixmap(QSize size, QIcon::Mode mode, QIcon::State state)
{
    QImage *image = new QImage(size, QImage::Format_ARGB32);
    image->fill(Qt::transparent);
    QPixmap pixmap = QPixmap::fromImage(std::move(*image), Qt::NoFormatConversion);
    QPainter *painter = new QPainter(&pixmap);
    QRect *rect = new QRect(0, 0, size.width(), size.height());
    this->paint(painter, rect, mode, state);
    return &pixmap;
}

QString FluentIconBase::path(Theme theme)
{  
    throw std::runtime_error("NotImplementedError");
}

QIcon *FluentIconBase::icon(Theme theme, QColor color)
{
    QString path = this->path(theme);
    if(!(path.endsWith(".svg") && color != nullptr))
    {
        return new QIcon(this->path(theme));
    }
    color = (new QColor(color))->name();
    
}

Icon::Icon(FluentIcon *fluentIcon)
{
    this->fluentIcon = fluentIcon;
}

/*
bool endsWith(const std::string& str, const std::string& suffix) {
    if (str.length() < suffix.length()) {
        return false;
    }
    return str.substr(str.length() - suffix.length()) == suffix;
}




FluentIconEngine::FluentIconEngine(Icon *icon, bool reverse)
{
    this->icon = icon;
    this->isThemeReversed = reverse;
}

void FluentIconEngine::paint(QPainter *painter, const QRect &rect, QIcon::Mode mode, QIcon::State state)
{
    painter->save();

    if(mode == QIcon::Disabled)
    {
        painter->setOpacity(0.5);
    }else if(mode == QIcon::Selected){
        painter->setOpacity(0.7);
    }

    
    QIcon icon = this->icon;

    if(!this->isThemeReversed){
        icon = this->icon
    }
    
  
}
     */
//}