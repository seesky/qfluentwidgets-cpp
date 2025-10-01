#include "style_sheet.h"
#include "config.h"
#include <regex>
#include <QRegExp>
#include <QFile>
#include <QWidget>
#include <QMutableMapIterator>
#include <math.h>
#include "../components/widgets/button.h"

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
        //connect(widget, SIGNAL(QObject::destroyed), SLOT(this->deregister()));
        connect(widget, &QWidget::destroyed, this, &StyleSheetManager::deregisterWrapper);
        installEventFilter(new CustomStyleSheetWatcher());
        QList<StyleSheetBase> *list = new QList<StyleSheetBase>();
        list->append(s);
        list->append((StyleSheetBase)(CustomStyleSheet(widget)));
        this->widgets->insert(widget, new StyleSheetCompose(list));
    }

    if(!reset){
        ((StyleSheetCompose *)(this->source(widget)))->add(&s);
    }else{
        QList<StyleSheetBase> *list = new QList<StyleSheetBase>();
        list->append(s);
        list->append((StyleSheetBase)(CustomStyleSheet(widget)));
        this->widgets->insert(widget, new StyleSheetCompose(list));
    }
}

void StyleSheetManager::deregister(QWidget *widget)
{
    /*
    if(this->widgets->find(widget) == this->widgets->end()){
        return;
    }
    for(auto w = this->widgets->begin(); w != this->widgets->end();){
        if(w.key() == widget){
            this->widgets->erase(w);
        }
    }
    */
    if(!this->widgets->contains(widget)){
        return;
    }
    this->widgets->remove(widget);
}

void StyleSheetManager::deregisterWrapper(QObject* obj)
{
    if (QWidget* widget = qobject_cast<QWidget*>(obj))
    {
        this->deregister(widget);
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
    ThemeColor *themeColor = new ThemeColor();
    while (matchIterator.hasNext()) {
        QRegularExpressionMatch match = matchIterator.next();
        QString capturedText = match.captured(0);
        QString _capturedText = QString(capturedText);
        _capturedText.remove(0, this->delimiter.length());

        int capturedTextStart = match.capturedStart();
        int capturedTextEnd = match.capturedEnd();
        int capturedTextLength = match.capturedLength();
        if(mapping.find(_capturedText) != mapping.end()){
            QRegularExpression regex_(capturedText);
            result.replace(regex_, themeColor->name(mapping.value(_capturedText)));
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
    //QString *qss = new QString(QString::fromUtf8(f->readAll()).replace("\r", "").replace("\n", ""));
    QString *qss = new QString(QString::fromUtf8(f->readAll()));
    f->close();
    //qDebug() << qss;
    return *qss;
}

QString getStyleSheet(QVariant *source, Theme theme = Theme::AUTO) //这个函数有问题，穿过来的source应该是支持多种类型的，由于c++不支持python的Enum结构，所以不能把Enum和Enum 方法直接传值
{
    StyleSheetBase *s;
    if(source->canConvert<QString>()){
        //qDebug() << source->value<QString>();

        Theme resolvedTheme = theme;
        if(resolvedTheme == Theme::AUTO){
            resolvedTheme = qconfig->getTheme();
        }

        QString themeOptionsName = "LIGHT";
        if(resolvedTheme == Theme::DARK){
            themeOptionsName = "DARK";
        }else if(resolvedTheme == Theme::LIGHT){
            themeOptionsName = "LIGHT";
        }

        QString path = "qfluentwidgets/qss/" + ThemeOptionsMap.value(themeOptionsName, ThemeOptionsMap.value("LIGHT")) + "/" + source->value<QString>() + ".qss";
        //qDebug() << path;
        StyleSheetFile *f = new StyleSheetFile(path);
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
    
    /*
    if (widget->inherits("PrimaryPushButton")) {
        qDebug() << "PrimaryPushButton";
    }
    

    auto _widget = qobject_cast<QPushButton*>(widget);
    if (nullptr != _widget){
        auto _widget = qobject_cast<PrimaryPushButton*>(widget);
        if (nullptr != _widget){
            _widget->setStyleSheet(getStyleSheet(&source, theme));
            return;
        }
        
    }
    */
    widget->setStyleSheet(getStyleSheet(&source, theme));
}

QString StyleSheetBase::content(Theme theme = Theme::AUTO)
{
    return getStyleSheetFromFile(((StyleSheetFile *)this)->path(theme));
}

QString StyleSheetBase::content(QString fluentStyleSheet, Theme theme)
{
    QString themeOptionsName;
    if(theme == Theme::AUTO){
        //TODO:theme = qconfig.theme if theme == Theme.AUTO else theme
        theme = Theme::LIGHT;
        themeOptionsName = "LIGHT";
    }else if(theme == Theme::DARK){
        theme = Theme::DARK;
        themeOptionsName = "DARK";
    }else{
        theme = Theme::LIGHT;
        themeOptionsName = "LIGHT";
    }
    return getStyleSheetFromFile(((FluentStyleSheet *)this)->path(themeOptionsName, fluentStyleSheet, theme));
}

void StyleSheetBase::apply(QWidget *widget, QString fluentStyleSheet, Theme theme = Theme::AUTO)
{
    //qDebug() << fluentStyleSheet;
    setStyleSheet(widget, QVariant::fromValue(fluentStyleSheet), Theme::AUTO, true);
}


QString FluentStyleSheet::path(QString ThemeOptionsName, QString FluentStyleSheetName, Theme theme = Theme::AUTO)
{
    if(theme == Theme::AUTO){
        //TODO:theme = qconfig.theme if theme == Theme.AUTO else theme
        theme = Theme::LIGHT;
    }
    return "qfluentwidgets/qss/" + ThemeOptionsMap.value(ThemeOptionsName) + "/" + FluentStyleSheetMap.value(FluentStyleSheetName) + ".qss";
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
    this->widget->setProperty((CustomStyleSheetMap.key("LIGHT_QSS_KEY", "")).toStdString().c_str(), QVariant::fromValue<QString>(qss));
    return this;
}

CustomStyleSheet *CustomStyleSheet::setDarkStyleSheet(QString qss)
{
    this->widget->setProperty((CustomStyleSheetMap.key("DARK_QSS_KEY", "")).toStdString().c_str(), QVariant::fromValue<QString>(qss));
    return this;
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

/*
void setTheme(Theme theme, bool save)
{
    //qconfig.set(qconfig->themeMode(), theme, save);
}
*/

QString ThemeColor::name(QString themeColorValue)
{
    QString name = this->color(themeColorValue)->name();
    return name;
}

QColor *ThemeColor::color(QString themeColorValue)
{
    //QConfig *qconfig = new QConfig();
    //QColor color = (qconfig->get(qconfig->themeColor))->value<QColor>();
    QColor color = QColor("#009faa");
    qreal h, s, v;
    color.getHsvF(&h, &s, &v);

    if(isDarkTheme())
    {
        s *= 0.84;
        v = 1;
        if(themeColorValue == "DARK_1"){
            v *= 0.9;
        }else if(themeColorValue == "DARK_2"){
            s *= 0.977;
            v *= 0.82;
        }else if(themeColorValue == "DARK_3"){
            s *= 0.95;
            v *= 0.7;
        }else if(themeColorValue == "LIGHT_1"){
            s *= 0.92;
        }else if(themeColorValue == "LIGHT_2"){
            s *= 0.78;
        }else if(themeColorValue == "LIGHT_3"){
            s *= 0.65;
        }
    }else{
        if(themeColorValue == "DARK_1"){
            v *= 0.75;
        }else if(themeColorValue == "DARK_2"){
            s *= 1.05;
            v *= 0.5;
        }else if(themeColorValue == "DARK_3"){
            s *= 1.1;
            v *= 0.4;
        }else if(themeColorValue == "LIGHT_1"){
            s *= 1.05;
        }else if(themeColorValue == "LIGHT_2"){
            s *= 0.75;
            v *= 1.05;
        }else if(themeColorValue == "LIGHT_3"){
            s *= 0.65;
            v *= 1.05;
        }
    }

    QColor *c = new QColor(QColor::fromHsvF(h, qMin(s, 1.00), qMin(v, 1.00)));
    return c;
}

QColor *ThemeColor::themeColor()
{
    return this->color("");
}

/*
void updateStyleSheet(){
    QList<QWidget*> removes = QList<QWidget*>();
    QMutableMapIterator<QWidget *, StyleSheetBase *> iter =  styleSheetManager->items();
    while (iter.hasNext()) {
        iter.next(); 
        QWidget *widget = iter.key();
        StyleSheetBase *styleSheet = iter.value();
        try {
            setStyleSheet(widget, QVariant::fromValue<StyleSheetBase>(*styleSheet), qconfig->getTheme(), true);
        }catch(std::exception& e){
            removes.append(widget);
        }
    }

    for(int i = 0 ; i < removes.length(); i++){
        styleSheetManager->deregister(removes.at(i));
    }
}
*/


void setTheme(Theme theme, bool save)
{
    if(theme == Theme::AUTO){
        qconfig->set(QVariant::fromValue<OptionsConfigItem*>(qconfig->themeMode), QVariant::fromValue<QString>("auto"), save, false);
        updateStyleSheet();
        emit(qconfig->themeChangedFinished());
    }else if(theme == Theme::LIGHT){
        qconfig->set(QVariant::fromValue<OptionsConfigItem*>(qconfig->themeMode), QVariant::fromValue<QString>("light"), save, false);
        updateStyleSheet();
        emit(qconfig->themeChangedFinished());
    }else if(theme == Theme::DARK){
        qconfig->set(QVariant::fromValue<OptionsConfigItem*>(qconfig->themeMode), QVariant::fromValue<QString>("dark"), save, false);
        updateStyleSheet();
        emit(qconfig->themeChangedFinished());
    }
}

void toggleTheme(bool save)
{
    Theme theme = isDarkTheme() ? Theme::LIGHT : Theme::DARK;
    setTheme(theme, save);
}