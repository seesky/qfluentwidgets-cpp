#include "style_sheet.h"
#include "config.h"
#include <regex>
#include <QRegExp>
#include <QFile>
#include <QWidget>
#include <QMutableMapIterator>

static StyleSheetManager *styleSheetManager = new StyleSheetManager();

StyleSheetFile::StyleSheetFile(){}

StyleSheetFile::StyleSheetFile(QString path)
{
    this->filePath = path;
}

QString StyleSheetFile::path(Theme theme)
{
    return this->filePath;
}

StyleSheetManager::StyleSheetManager()
{
    this->widgets = new QMap<QWidget*, StyleSheetBase*>();
}

void StyleSheetManager::register_(QVariant source, QWidget *widget, bool reset = true)
{
    StyleSheetBase s;
    if(source.canConvert<QString>()){
        s = StyleSheetFile(source.value<QString>());
    }

    if(this->widgets->find(widget) == this->widgets->end()){
        connect(widget, SIGNAL(widget->destroyed()), SLOT(this->deregister()));
        //widget->installEventFilter()
    }
}

void StyleSheetManager::deregister(QWidget *widget)
{
    if(this->widgets->find(widget) == this->widgets->end()){
        return;
    }
    for(auto w = this->widgets->begin(); w != this->widgets->end();){
        if(w.key() == widget){
            this->widgets->erase(w);
        }
    }
}

QMutableMapIterator<QWidget*, StyleSheetBase*> StyleSheetManager::items()
{
    QMutableMapIterator<QWidget*, StyleSheetBase*> it(*(this->widgets));
    return it;
}

StyleSheetBase *StyleSheetManager::source(QWidget *widget)
{
    QList<StyleSheetBase> *sst = new QList<StyleSheetBase>();
    StyleSheetCompose *ssc = new StyleSheetCompose(sst);
    return this->widgets->value(widget, ssc);
}

QssTemplate::QssTemplate(QString qss)
{
    value = qss;
}

QString QssTemplate::safe_substitute(QMap<QString, QString> mapping)
{
    QString result = QString(this->value);
    QRegularExpression regex(this->delimiter + "(\\w+)");
    QRegularExpressionMatchIterator matchIterator = regex.globalMatch(this->value);
    while (matchIterator.hasNext()) {
        QRegularExpressionMatch match = matchIterator.next();
        QString capturedText = match.captured(0);
        int capturedTextStart = match.capturedStart();
        int capturedTextEnd = match.capturedEnd();
        int capturedTextLength = match.capturedLength();
        if(mapping.find(capturedText) != mapping.end()){
            QRegularExpression regex_(capturedText);
            result.replace(regex_, mapping.key(capturedText));
        }
    }
    return result;
}

QString applyThemeColor(QString qss)
{
    QssTemplate template_ = QssTemplate(qss);
    return template_.safe_substitute(ThemeColorMap);
}

StyleSheetBase::StyleSheetBase()
{
    this->self = this;
}

QString StyleSheetBase::path(Theme theme=Theme::AUTO)
{
    throw std::runtime_error("NotImplementedError");
}

QString getStyleSheetFromFile(QString file)
{
    QFile *f = new QFile(file);

    f->open(QFile::ReadOnly);
    QString qss = QString(f->readAll());
    f->close();
    return qss;
}

QString getStyleSheet(QVariant *source, Theme theme = Theme::AUTO)
{
    StyleSheetBase *s;
    if(source->canConvert<QString>()){
        StyleSheetFile *f = new StyleSheetFile(source->value<QString>());
        s = f;
    }else if(source->canConvert<StyleSheetBase>()){
        StyleSheetBase sst = source->value<StyleSheetBase>();
        s = &sst;
    }
    return applyThemeColor(s->content(theme));
}

void setStyleSheet(QWidget *widget, QVariant source, Theme theme = Theme::AUTO, bool register_ = true)
{
    if(register_){
        styleSheetManager->register_(source, widget);
    }

    widget->setStyleSheet(getStyleSheet(&source, theme));
}

QString StyleSheetBase::content(Theme theme = Theme::AUTO)
{
    return getStyleSheetFromFile(this->path(theme));
}

void StyleSheetBase::apply(QWidget *widget, Theme theme = Theme::AUTO)
{
    setStyleSheet(widget, QVariant::fromValue(*(this->self)), Theme::AUTO, true);
}


QString FluentStyleSheet::path(QString ThemeOptionsName, QString FluentStyleSheetName, Theme theme = Theme::AUTO)
{
    if(theme == Theme::AUTO){
        //TODO:theme = qconfig.theme if theme == Theme.AUTO else theme
        theme = Theme::LIGHT;
    }
    return ":/qfluentwidgets/gss/" + ThemeOptionsMap.key(ThemeOptionsName) + "/" + ThemeColorMap.key(FluentStyleSheetName) + ".qss";
}

void setCustomStyleSheet(QWidget *widget, QString lightQss, QString darkQss)
{
    CustomStyleSheet(widget).setCustomStyleSheet(lightQss, darkQss);
}

void addStyleSheet(QWidget *widget, QVariant *source, Theme theme = Theme::AUTO, bool register_ = true)
{
    QString qss;
    if(register_){
        styleSheetManager->register_(*source, widget, false);
        QVariant qv = QVariant::fromValue(*(styleSheetManager->source(widget)));
        qss = getStyleSheet(&qv, theme);
    }else{
        qss = widget->styleSheet() + "\n" + getStyleSheet(source, theme);
    }

    if(qss.trimmed() != widget->styleSheet().trimmed())
    {
        widget->setStyleSheet(qss);
    }
}

void updateStyleSheet()
{
    QList<QWidget *> removes;
    QMutableMapIterator<QWidget*, StyleSheetBase*> it = styleSheetManager->items();
    while (it.hasNext()) {
        it.next();
        try{
            //TODO:setStyleSheet(widget, file, qconfig.theme)
            setStyleSheet(it.key(), QVariant::fromValue(*(it.value())), Theme::LIGHT);
        }catch(const std::exception& e){
            removes.append(it.key());
        }
    }

    for (QWidget *item : removes) {
        styleSheetManager->deregister(item);
    }
    
}

bool CustomStyleSheetWatcher::eventFilter(QWidget *obj, QEvent *event)
{
    if(event->type() != QEvent::DynamicPropertyChange){
        return QObject::eventFilter(obj, event);
    }

    QString name = QString(((QDynamicPropertyChangeEvent *)event)->propertyName().data());
    if(name == CustomStyleSheetMap.key("LIGHT_QSS_KEY") || name == CustomStyleSheetMap.key("DARK_QSS_KEY"))
    {
        CustomStyleSheet *css = new CustomStyleSheet(obj);
        QVariant qv = QVariant::fromValue(*css);
        addStyleSheet(obj, &qv);
    }

    return QObject::eventFilter(obj, event);
}

StyleSheetCompose::StyleSheetCompose(QList<StyleSheetBase> *sources)
{
    this->sources = sources;
};

QString StyleSheetCompose::content(Theme theme = Theme::AUTO)
{
    QList<StyleSheetBase>::iterator it;
    QString returnValue = "\n";
    for (it = this->sources->begin(); it != this->sources->end(); ++it) {
        returnValue =  returnValue + it->content(theme) + "\n";
    }
    return returnValue;
}

void StyleSheetCompose::add(StyleSheetBase *source)
{
    
    if(source == this || this->sources->contains(*source))
    {
        return;
    }
    this->sources->append(*source);
    
}

void StyleSheetCompose::remove(StyleSheetBase *source)
{
    if(! this->sources->contains(*source))
    {
        return;
    }
    this->sources->removeOne(*source);
}


CustomStyleSheet::CustomStyleSheet(QWidget *widget)
{
    this->widget = widget;
}

QString CustomStyleSheet::path(Theme theme=Theme::AUTO)
{
    return "";
}

CustomStyleSheet *CustomStyleSheet::setCustomStyleSheet(QString lightQss, QString darkQss)
{
    this->setLightStyleSheet(lightQss);
    this->setDarkStyleSheet(darkQss);
    return this;
}

CustomStyleSheet *CustomStyleSheet::setLightStyleSheet(QString qss)
{
    this->widget->setProperty((CustomStyleSheetMap.key("LIGHT_QSS_KEY", "")).toStdString().c_str(), qss);
    return this;
}

CustomStyleSheet *CustomStyleSheet::setDarkStyleSheet(QString qss)
{
    this->widget->setProperty((CustomStyleSheetMap.key("DARK_QSS_KEY", "")).toStdString().c_str(), qss);
}

QString CustomStyleSheet::lightStyleSheet()
{
    return (this->widget->property((CustomStyleSheetMap.key("DARK_QSS_KEY", "")).toStdString().c_str())).value<QString>() != nullptr ? (this->widget->property((CustomStyleSheetMap.key("DARK_QSS_KEY", "")).toStdString().c_str())).value<QString>() : "";
}

QString CustomStyleSheet::darkStyleSheet()
{
    return (this->widget->property((CustomStyleSheetMap.key("DARK_QSS_KEY", "")).toStdString().c_str())).value<QString>() != nullptr ? (this->widget->property((CustomStyleSheetMap.key("DARK_QSS_KEY", "")).toStdString().c_str())).value<QString>() : "";
}

QString CustomStyleSheet::content(Theme theme = Theme::AUTO)
{
    //TODO:theme = qconfig.theme if theme == Theme.AUTO else theme
    if(theme == Theme::LIGHT)
    {
        return this->lightStyleSheet();
    }
    return this->darkStyleSheet();
}

void setTheme(Theme theme, bool save)
{
    
}