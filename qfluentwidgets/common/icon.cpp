#include "icon.h"
#include "config.h"
#include <QFile>
#include <QtCore>
#include <QtXml/QDomDocument>

//namespace Qfw{

void drawSvgIcon(QString icon, QPainter *painter, const QRect &rect)
{   
    qDebug() << icon;
    QSvgRenderer *renderer = new QSvgRenderer(icon);
    renderer->render(painter, QRectF(rect));
    /*
    if(icon->canConvert<QString>())
    {
        QSvgRenderer *renderer = new QSvgRenderer(icon->value<QString>());
        renderer->render(painter, QRectF(rect));
    }else if(icon->canConvert<QByteArray>()){
        QSvgRenderer *renderer = new QSvgRenderer(icon->value<QByteArray>());
        renderer->render(painter, QRectF(rect));
    }
    */
}

void drawSvgIcon2engine(QString icon, QPainter *painter, const QRect &rect)
{   
    QSvgRenderer *renderer = new QSvgRenderer(icon.toUtf8());
    renderer->render(painter, QRectF(rect));
    /*
    if(icon->canConvert<QString>())
    {
        QSvgRenderer *renderer = new QSvgRenderer(icon->value<QString>());
        renderer->render(painter, QRectF(rect));
    }else if(icon->canConvert<QByteArray>()){
        QSvgRenderer *renderer = new QSvgRenderer(icon->value<QByteArray>());
        renderer->render(painter, QRectF(rect));
    }
    */
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


QString writeSvg(QString iconPath, int indexes = 0, std::map<QString, QString> attributes = {})
{
    if(!iconPath.endsWith(".svg"))
    {
        return "";
    }
    QFile *f = new QFile(iconPath);
    qDebug() << iconPath;
    f->open(QFile::ReadOnly);

    QDomDocument *dom = new QDomDocument();
    dom->setContent(f->readAll());
    f->close();

    QDomNodeList pathNodes = dom->elementsByTagName("path");
    if(indexes == 0){
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

void MIcon::drawIcon(QVariant *icon, QPainter *painter, QRect rect, std::map<QString, QString> *attributes, QIcon::State state = QIcon::State::Off)
{
    if(icon->canConvert<FluentIcon>())
    {   
        //TODO: icon.render(painter, rect, **attributes)
        icon->value<FluentIcon>().render(painter, rect, Theme::AUTO, 0, attributes);
    }else if(icon->canConvert<Icon>()){
        //icon.value<Icon>().fluentIcon->render(&painter, &rect, Theme::AUTO, 0, attributes);
        icon->value<Icon>().fluentIcon->render(painter, rect, Theme::AUTO, 0, attributes);
    }else if(icon->canConvert<QIcon>()){
        QIcon icon_ = icon->value<QIcon>();
        icon_.paint(painter, QRectF(rect).toRect(), Qt::AlignCenter, QIcon::Normal, state);
    }else{
        QIcon *icon_ = new QIcon(icon->value<QString>());
        icon_->paint(painter, QRectF(rect).toRect(), Qt::AlignCenter, QIcon::Normal, state);
    }
}

QIcon *FluentIcon::icon(Theme theme = Theme::AUTO, QColor color = nullptr)
{
    QString path = this->path(theme);
    qDebug() << path;
    if(!((path.endsWith(".svg") && color != nullptr)))
    {
        QIcon *i = new QIcon(this->path(theme));
        return i;
    }
    color = (new QColor(color))->name();
    std::map<QString, QString> attributes = {
        {"fill", color.name()}
    };
    SvgIconEngine *sie = new SvgIconEngine(writeSvg(path, 0, attributes));
    return new QIcon(sie);
}


QString FluentIcon::path(Theme theme = Theme::AUTO)
{
    QString path = QString("qfluentwidgets/images/icons/" + FluentIconMap.at(this->iconName) + "_" + getIconColor(theme) + ".svg");
    qDebug() << path;
    return path;
}

void FluentIcon::render(QPainter *painter, QRect rect, Theme theme = Theme::AUTO, int indexes = 0, std::map<QString, QString> *attributes = nullptr)
{
    QString iconStr = this->path(theme);
    QIcon *icon;
    if(iconStr.endsWith(".svg")){
        if(attributes){
            iconStr = writeSvg(iconStr, indexes, *attributes);
            drawSvgIcon2engine(iconStr, painter, rect);
        }else{
            drawSvgIcon(iconStr, painter, rect);
        }
    }else{
        icon = new QIcon(iconStr);
        rect = QRectF(rect).toRect();
        painter->drawPixmap(rect, icon->pixmap(QRectF(rect).toRect().size()));
    }
}


SvgIconEngine::SvgIconEngine(QString svg)
{
    this->svg = svg;
}

void SvgIconEngine::paint(QPainter *painter, const QRect &rect, QIcon::Mode mode, QIcon::State state)
{
    drawSvgIcon2engine(this->svg, painter, rect);
}

QIconEngine *SvgIconEngine::clone() const
{
    return new SvgIconEngine(this->svg);
}

QPixmap SvgIconEngine::pixmap(const QSize &size, QIcon::Mode mode, QIcon::State state)
{
    QImage *image = new QImage(size, QImage::Format_ARGB32);
    image->fill(Qt::transparent);
    QPixmap pixmap = QPixmap::fromImage(std::move(*image), Qt::NoFormatConversion);
    QPainter *painter = new QPainter(&pixmap);
    QRect *rect = new QRect(0, 0, size.width(), size.height());
    this->paint(painter, *rect, mode, state);
    return pixmap;
}

void FluentIconBase::setIconName(QString iconName)
{
    this->iconName = iconName;
}

QString FluentIconBase::path(Theme theme = Theme::AUTO)
{  
    throw std::runtime_error("NotImplementedError");
}

QIcon *FluentIconBase::icon(Theme theme = Theme::AUTO, QColor color = nullptr)
{
    QString path = this->path(theme);
    if(!(path.endsWith(".svg") && color != nullptr))
    {
        return new QIcon(this->path(theme));
    }
    color = (new QColor(color))->name();
    std::map<QString, QString> attributes = {
        {"fill", color.name()}
    };
    SvgIconEngine *sie = new SvgIconEngine(writeSvg(path, 0, attributes));
    return new QIcon(sie);
}

QIcon *FluentIconBase::qicon(bool reverse)
{
    //QVariant fib = QVariant::fromValue(this->t);
    //FluentIconEngine *fie = new FluentIconEngine(&fib, reverse); 
    //return &QIcon(FluentIconEngine(QVariant::fromValue(this), reverse);
}

//TODO:这个函数逻辑有问题，实际调试时需要确认
void FluentIconBase::render(QPainter *painter, QRect rect, Theme theme = Theme::AUTO, int indexes = 0, std::map<QString, QString> *attributes = nullptr)
{
    QString iconStr = this->path(theme);
    QIcon *icon;
    if(iconStr.endsWith(".svg")){
        if(attributes){
            iconStr = writeSvg(iconStr, indexes, *attributes);
        }
        drawSvgIcon(iconStr, painter, rect);
    }else{
        icon = new QIcon(iconStr);
        rect = QRectF(rect).toRect();
        painter->drawPixmap(rect, icon->pixmap(QRectF(rect).toRect().size()));
    }
}

Icon::Icon(){}

Icon::Icon(FluentIcon *fluentIcon) : QIcon(fluentIcon->path())
{
    this->fluentIcon = fluentIcon;
}

/*
QString Icon::path(Theme theme = Theme::AUTO)
{
    return ":/qfluentwidgets/images/icons/" + FluentIconMap.at(t) + "_" + getIconColor(theme) + ".svg";
}
*/

FluentIconEngine::FluentIconEngine(QVariant *icon, bool reverse = false)
{
    qDebug() << icon->typeName();
    this->icon = new QVariant(*icon);
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

    qDebug() << this->icon->typeName();
    QVariant *_icon = this->icon;
    Theme theme;

    

    if(!this->isThemeReversed){
        theme = Theme::AUTO;
    }else{
        if(isDarkTheme()){
            theme = Theme::LIGHT;
        }else{
            theme = Theme::DARK;
        }
    }
    
    if(_icon->canConvert<Icon>()){
        icon_QIcon = _icon->value<Icon>().fluentIcon->icon(theme);
        QRect tmp_rect;
        if(rect.x() == 19){
            tmp_rect = rect.adjusted(-1, 0, 0, 0);
        }
        icon_QIcon->paint(painter, tmp_rect, Qt::AlignCenter, QIcon::Normal, state);
    }else if(_icon->canConvert<FluentIcon>()){
        icon_QIcon = _icon->value<FluentIcon>().icon(theme);
        QRect tmp_rect;
        if(rect.x() == 19){
            tmp_rect = rect.adjusted(-1, 0, 0, 0);
        }
        icon_QIcon->paint(painter, tmp_rect, Qt::AlignCenter, QIcon::Normal, state);
    }else if(_icon->canConvert<QIcon>())
    {
        *icon_QIcon = _icon->value<QIcon>();
        QRect tmp_rect;
        if(rect.x() == 19){
            tmp_rect = rect.adjusted(-1, 0, 0, 0);
        }
        icon_QIcon->paint(painter, tmp_rect, Qt::AlignCenter, QIcon::Normal, state);
    }

    painter->restore();
    
}

FluentIconEngine *FluentIconEngine::clone() const
{
    return new FluentIconEngine(this->icon, false);
}


QIcon MIcon::toQIcon(QVariant *icon)
{
    if(icon->canConvert<QString>()){
        return QIcon(icon->value<QString>());
    }

    /*
    if(icon->canConvert<FluentIconBase>()){
        return *(icon->value<FluentIconBase>().icon());
    }
    */

    if(icon->canConvert<FluentIcon>()){
        return *(icon->value<FluentIcon>().icon());
    }

    return icon->value<QIcon>();
}

Action::Action(QObject *parent) : QAction(parent)
{
    this->fluentIcon = nullptr;
}


Action::Action(QString text, QObject *parent) : QAction(text, parent)
{
    this->fluentIcon = nullptr;
}

Action::Action(QIcon icon, QString text, QObject *parent) : QAction(icon, text, parent)
{   
    this->fluentIcon = nullptr;
}

Action::Action(FluentIcon *icon, QString text, QObject *parent) : QAction(*(icon->icon()), text, parent)
{
    this->fluentIcon = icon;
}

QIcon *Action::icon()
{
    if(this->fluentIcon){
        Icon *icon = new Icon(this->fluentIcon);
        return icon;
    }

    return Action::icon();
}

void Action::setIcon(QVariant *icon)
{
    QIcon *_icon;
    if(icon->canConvert<FluentIcon>()){
        FluentIcon fi = icon->value<FluentIcon>();
        this->fluentIcon = &fi;
        _icon = icon->value<FluentIcon>().icon();
        QAction::setIcon(*_icon);
    }else if(icon->canConvert<QIcon>()){
        QIcon i = icon->value<QIcon>();
        QAction::setIcon(i);
    }
}