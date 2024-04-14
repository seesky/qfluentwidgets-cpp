#include "config.h"

#include <algorithm>
#include <vector>
#include <stdexcept>
#include <experimental/filesystem>
//#include "json/json.h"

IniSettings* IniSettings::instance = nullptr;
QConfig* QConfig::instance = nullptr; 

IniSettings::IniSettings()
{
    this->instance = nullptr;
    QString fileName;
	fileName = QCoreApplication::applicationDirPath();
	fileName += QString("qfluentwidgets/config/config.ini");
    this->settings_init(fileName);
}

IniSettings* IniSettings::getInstance()
{
    if(instance == nullptr){
        instance = new IniSettings();
    }
    return instance;
}

void IniSettings::settings_init(const QString &path)
{
    //qDebug() << path;
	m_iniFile = QSharedPointer<QSettings>(new QSettings(path, QSettings::IniFormat));
	m_iniFile->setIniCodec(QTextCodec::codecForName("UTF-8"));
}

void IniSettings::setValue(const QString &section, const QString &key, const QVariant &value)
{
	m_iniFile->beginGroup(section);     // 设置节点名
	m_iniFile->setValue(key, value);    //设置键名和键值
	m_iniFile->endGroup();              // 结束当前节的操作
}

void IniSettings::removeNode(const QString &section)
{
	m_iniFile->remove(section);
}

void IniSettings::removeKey(const QString &section, const QString &key)
{
	m_iniFile->beginGroup(section);
	m_iniFile->remove(key);
	m_iniFile->endGroup();
}

QVariant IniSettings::getValue(const QString &section, const QString &key, const QVariant &defaultValue)
{
	QString path = QString("%1/%2").arg(section).arg(key);
	QVariant result = m_iniFile->value(path, defaultValue);
	return result;
}



/*

bool ConfigValidator::validate(QVariant *value)
{
    return true;
}

QVariant *ConfigValidator::correct(QVariant *value){
    return this->value;
}


RangeValidator::RangeValidator(int min, int max)
{
    this->min_value = min;
    this->max_value = max;
    this->range_value[0] = min;
    this->range_value[1] = max;
}

bool RangeValidator::validate(QVariant *value)
{
    return (this->min_value <= value->toInt()) && (value->toInt() <= this->max_value);
}


QVariant * RangeValidator::correct(QVariant *value)
{
    QVariant c = QVariant::fromValue(std::min(std::max(this->min_value, value->toInt()), this->max_value));
    return &c;
}

OptionsValidator::OptionsValidator(QVariant *options)
{
    if(!options)
    {
        throw std::runtime_error("The `options` can't be empty.");
    }

    if(options->canConvert<QMap<QString,QString>>())
    {
        QMap<QString,QString> q = options->value<QMap<QString,QString>>();
        QMutableMapIterator<QString, QString> it(q);
        while (it.hasNext()) {
            it.next();
            QVariant q = QVariant::fromValue(it.value());
            this->options.append(&q);
        }
    }

    
    if(options->canConvert<QList<QVariant *>>())
    {
        this->options = options->value<QList<QVariant *>>();
    }
    
}

bool OptionsValidator::validate(QVariant *value)
{
    for (const QVariant *item : this->options) {
        if(value->canConvert<QString>())
        {
            if(item->canConvert<QString>()){
                if(value->value<QString>() == item->value<QString>()){
                    return true;
                }
            }
        }
    }

}

QVariant *OptionsValidator::correct(QVariant *value)
{
    if(this->validate(value)){
        return value;
    }else{
        return this->options.at(0);
    }
}

bool BoolValidator::validate(QVariant *value)
{
    if(value->canConvert<bool>())
    {
        return true;
    }
    
}


bool BoolValidator::correct(QVariant *value)
{
    return value->value<bool>();
}



bool FolderValidator::validate(QVariant *value)
{
    QDir directory(value->value<QString>());
    return directory.exists();
}

    

QString FolderValidator::correct(QVariant *value)
{
    QDir directory(value->value<QString>());
    directory.mkpath(value->value<QString>());
    QString absolutePath = directory.absolutePath().replace("\\", "/");
    return absolutePath;
}




bool FolderListValidator::validate(QVariant *value)
{
    QList<QString> directorys = value->value<QList<QString>>();


    QList<QString>::iterator it;
    for (it = directorys.begin(); it != directorys.end(); ++it) {
        QDir directory(*it);
        if(directory.exists()){
            continue;
        }else{
            return false;
        }
    }

    return true;
}




QList<QString> FolderListValidator::correct(QVariant *value)
{
    QList<QString> folders;

    QList<QString>::iterator it;
    for (it = value->value<QList<QString>>().begin(); it != value->value<QList<QString>>().end(); ++it) {
        QDir directory(*it);
        if(directory.exists())
        {
            QString absolutePath = directory.absolutePath().replace("\\", "/");
            folders.append(absolutePath);
        }
    
    }

    return folders;
}

ColorValidator::ColorValidator(QVariant *default_)
{
    if(default_->canConvert<QString>()){
        this->default_ = new QColor(default_->value<QString>());
    }else if(default_->canConvert<QColor>()){
        this->default_ = new QColor(default_->value<QColor>());
    }
}

bool ColorValidator::validate(QVariant * value)
{
    if(value->canConvert<QString>()){
        return QColor(value->value<QString>()).isValid();
    }else if(value->canConvert<QColor>()){
        return QColor(value->value<QColor>()).isValid();
    }else{
        return false;
    }
}

QColor* ColorValidator::correct(QVariant * value)
{
    if(this->validate(value)){
        if(value->canConvert<QString>()){
            return new QColor(value->value<QString>());
        }else if(value->canConvert<QColor>()){
            return new QColor(value->value<QColor>());
        }
    }else{
        return this->default_;
    }
}


MapSerializer::MapSerializer(QMap<QString, QString> value)
{
    this->mapClass = value;
}

    
QString MapSerializer::serialize(QMap<QString, QString> value)
{
    
    Json::Value jObject;
    
    for(auto it = value.begin(); it != value.end(); ++it)
    {
        jObject[it.key().toStdString()] = it.value().toStdString();
    }
    
    QString json_str = QString::fromStdString(jObject.asString());
    return json_str;

}



std::string itoa_self(int i)
{
    std::stringstream ss;
    ss << i;
    return ss.str();
}


QMap<QString, QString> MapSerializer::deserialize(QString json)
{
    Json::Reader reader;
    Json::Value value;
    QMap<QString, QString> maps;

    if (json.length() > 0)
    {
        if (reader.parse(json.toStdString(), value))
        {
            Json::Value::Members members = value.getMemberNames();
            for (Json::Value::Members::iterator it = members.begin(); it != members.end(); it++)
            { 
                Json::ValueType vt = value[*it].type();
                switch (vt)
                {
                case Json::stringValue:
                {
                    maps.insert(QString::fromStdString(value[*it].asString()), QString::fromStdString(value[*it].asString()));
                    break;
                }
                
                case Json::intValue:
                {
                    int intTmp = value[*it].asInt();
                    maps.insert(std::pair<std::string, std::string>(*it, itoa_self(intTmp)));
                    break;
                }
                case Json::arrayValue:
                    {
                        std::string strid;
                        for (unsigned int i = 0; i < value[*it].size(); i++)
                        {
                            strid +=value[*it][i].asString();
                            strid +=",";
                        }
                        if(!strid.empty())
                        {
                            strid = strid.substr(0,strid.size()-1);
                        }
                        maps.insert(std::pair<std::string, std::string>(*it, strid));
                        break;
                    }
                
                default:
                    {
                        break;
                    }
                }//end switch
            }//end for
        }//end if
    }

    return maps;
}


QString ColorSerializer::serialize(QColor value)
{
    return value.name(QColor::HexArgb);
}


QColor ColorSerializer::deserialize(QString value)
{
    return QColor(value);
}

ConfigItem::ConfigItem(QString group, QString name, QVariant *default_, bool restart)
{
    this->group = group;
    this->name = name;
    this->__value = default_;
    this->restart = restart;
    this->defaultValue = this->validator->correct(default_);
}



QVariant *ConfigItem::getValue()
{
    return this->__value;
}



void ConfigItem::setValue(QVariant *value)
{
    QVariant *v = this->validator->correct(value);
    QVariant *ov = this->__value;
    this->__value = v;
    if(ov != v)
    {
        emit(this->valueChanged(v));
    }
}


QString ConfigItem::key()
{
    if(!this->name.isNull())
    {
        return this->group + "." + this->name;
    }else{
        return this->group;
    }
}


QString ConfigItem::__str__() 
{
    return QString("%1[value=%2]").arg(this->objectName()).arg(this->getValue()->value<QString>());
}
*/

RangeConfigItem::RangeConfigItem(QString group, QString name, int default_, int min, int max, bool restart)
{
    this->group = group;
    this->name = name;
    this->min_value = min;
    this->max_value = max;
    this->defaultValue = default_;
    this->restart = restart;
    this->range_value[0] = min;
    this->range_value[1] = max;
}

int RangeConfigItem::getValue()
{
    return this->__value;
}

void RangeConfigItem::setValue(int value)
{
    int v = this->correct(value);
    int ov = this->__value;
    this->__value = v;
    if(ov != v){
        emit(this->valueChanged(v));
    }
}

QString RangeConfigItem::key()
{
    if(!this->name.isNull())
    {
        return this->group + "." + this->name;
    }else{
        return this->group;
    }
}


QString RangeConfigItem::__str__()
{
    return QString("%1[value=%2]").arg(this->objectName()).arg(QString::number(this->getValue()));

}


bool RangeConfigItem::validate(int value)
{
    return (this->min_value <= value) && (value <= this->max_value);
}

int RangeConfigItem::correct(int value)
{
    return qMin(qMax(this->min_value, value), this->max_value);
}

int *RangeConfigItem::range()
{
    return this->range_value;
}


OptionsConfigItem::OptionsConfigItem(QString group, QString name, QString default_, const QList<QString> options, bool restart) : QObject()
{
    this->group = group;
    this->name = name;
    this->defaultValue = default_;
    this->restart = restart;
    this->_options = options;
}

QString OptionsConfigItem::getValue()
{
    return this->__value;
}

void OptionsConfigItem::setValue(QString value)
{
    QString v = this->correct(value);
    QString ov = this->__value;
    this->__value = v;
    if(ov != v){
        emit(this->valueChanged(v));
    }
}



QString OptionsConfigItem::key()
{
    if(!this->name.isNull())
    {
        return this->group + "." + this->name;
    }else{
        return this->group;
    }
}


QString OptionsConfigItem::__str__()
{
    return QString("%1[options=%2]").arg(this->objectName()).arg(this->getValue());

}


bool OptionsConfigItem::validate(QString value)
{
    return this->_options.contains(value);
}

QString OptionsConfigItem::correct(QString value)
{
    return this->validate(value) ? value : this->_options[0];
}

QList<QString> OptionsConfigItem::options()
{
    return this->_options;
}


ColorConfigItem::ColorConfigItem(QString group, QString name, QColor default_, bool restart)
{
    this->group = group;
    this->name = name;
    this->defaultValue = default_;
    this->restart = restart;
}

QColor ColorConfigItem::getValue()
{
    return this->__value;
}

void ColorConfigItem::setValue(QColor value)
{
    QColor v = this->correct(value);
    QColor ov = this->__value;
    this->__value = v;
    if(ov != v){
        emit(this->valueChanged(v));
    }
}


QString ColorConfigItem::key()
{
    if(!this->name.isNull())
    {
        return this->group + "." + this->name;
    }else{
        return this->group;
    }
}


QString ColorConfigItem::__str__()
{
    return QString("%1[value=%2]").arg(this->objectName()).arg(this->getValue().name());
}


bool ColorConfigItem::validate(QColor value)
{
    return value.isValid();
}

QColor ColorConfigItem::correct(QColor value)
{
    return this->validate(value) ? QColor(value) : this->defaultValue;
}


QConfig::QConfig(QObject *parent) : QObject(parent)
{
    this->_theme = Theme::LIGHT;
    this->_themeOptionsList = {"light", "dark", "auto"};
    this->themeMode = new OptionsConfigItem(QString("QFluentWidgets"), QString("ThemeMode"), QString("light"), this->_themeOptionsList, false);
    this->themeColor = new ColorConfigItem(QString("QFluentWidgets"), QString("ThemeColor"), QColor("#009faa"), false);
    QList<QString> languageList = {"chinese simplified", "chinese traditional", "english", "auto"};
    this->language = new OptionsConfigItem("MainWindow", "Language", "auto", languageList, true);
}


QConfig* QConfig::getInstance()
{
    if(instance == nullptr){
        instance = new QConfig(nullptr);
    }
    return instance;
}


QVariant QConfig::get(QVariant item)
{
    if(item.canConvert<RangeConfigItem*>()){
        QVariant v = iniSettings->getValue(item.value<RangeConfigItem*>()->group, item.value<RangeConfigItem*>()->name, item.value<RangeConfigItem*>()->defaultValue);
        return v;
    }else if(item.canConvert<OptionsConfigItem*>()){
        QVariant v = iniSettings->getValue(item.value<OptionsConfigItem*>()->group, item.value<OptionsConfigItem*>()->name, item.value<OptionsConfigItem*>()->defaultValue);
        return v;
    }else if(item.canConvert<ColorConfigItem*>()){
        QVariant v = iniSettings->getValue(item.value<ColorConfigItem*>()->group, item.value<ColorConfigItem*>()->name, item.value<ColorConfigItem*>()->defaultValue);
        return v;
    }
}


Theme QConfig::getTheme()
{
    return this->_theme;
}


bool isWindowsDarkModeActive() {
    // Windows注册表路径，用于存储个性化设置
    const QString regKey = "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize";
    const QString regValue = "AppsUseLightTheme"; // 当此值为0时，表示暗模式

    QSettings settings(regKey, QSettings::NativeFormat);

    // 查询注册表中的AppsUseLightTheme值
    QVariant value = settings.value(regValue, 1); // 默认为1，即亮模式

    // 如果值为0，则表示 Windows 处于暗模式
    return value.toInt() == 0;
}

void QConfig::setTheme(Theme t)
{
    if(t == Theme::AUTO){
        t = isWindowsDarkModeActive() ? Theme::DARK : Theme::LIGHT;
    }

    this->_theme = t;
}


void QConfig::set(QVariant item, QVariant value, bool save, bool copy)
{
    if(item.canConvert<RangeConfigItem*>()){
        if(item.value<RangeConfigItem*>()->getValue() == value.value<int>()){
            return;
        }

        item.value<RangeConfigItem*>()->setValue(value.value<int>());

        if(save){
            iniSettings->setValue(item.value<RangeConfigItem*>()->group, item.value<RangeConfigItem*>()->name, value);
        }

        if(item.value<RangeConfigItem*>()->restart){
            emit(this->appRestartSig());
        }
    }else if(item.canConvert<OptionsConfigItem*>()){
        if(item.value<OptionsConfigItem*>()->getValue() == value.value<QString>()){
            return;
        }

        item.value<OptionsConfigItem*>()->setValue(value.value<QString>());

        if(save){
            iniSettings->setValue(item.value<OptionsConfigItem*>()->group, item.value<OptionsConfigItem*>()->name, value);
        }

        if(item.value<OptionsConfigItem*>()->restart){
            emit(this->appRestartSig());
        }

        if(item.value<OptionsConfigItem*>()->group == QString("ThemeMode")){
            if(item.value<OptionsConfigItem*>()->getValue() == QString("auto")){
                this->setTheme(Theme::AUTO);
                emit(this->themeChanged(Theme::AUTO));
            }else if(item.value<OptionsConfigItem*>()->getValue() == QString("dark")){
                this->setTheme(Theme::DARK);
                emit(this->themeChanged(Theme::DARK));
            }else if(item.value<OptionsConfigItem*>()->getValue() == QString("light")){
                this->setTheme(Theme::LIGHT);
                emit(this->themeChanged(Theme::LIGHT));
            }
        }
    }else if(item.canConvert<ColorConfigItem*>()){
        if(item.value<ColorConfigItem*>()->getValue() == value.value<QColor>()){
            return;
        }

        item.value<ColorConfigItem*>()->setValue(value.value<QColor>());

        if(save){
            iniSettings->setValue(item.value<ColorConfigItem*>()->group, item.value<ColorConfigItem*>()->name, value);
        }

        if(item.value<ColorConfigItem*>()->restart){
            emit(this->appRestartSig());
        }

        emit(this->themeColorChanged(item.value<ColorConfigItem*>()->getValue()));
    }
}






/*

int* RangeConfigItem::range()
{
    return ((RangeValidator *)this->validator)->range_value;
}

OptionsConfigItem::OptionsConfigItem(QString group, QString name, QVariant *default_, bool restart) 
    : ConfigItem(group, name, default_, new OptionsValidator(default_), new MapSerializer(ThemeOptionsMap), restart)
{
    
}

QList<QVariant *> OptionsConfigItem::options()
{
    return ((OptionsValidator *)this->validator)->options;
}

ColorConfigItem::ColorConfigItem(QString group, QString name, QVariant *default_, bool restart) 
    : ConfigItem(group, name, default_, new ColorValidator(default_), new ColorSerializer(), restart)
{

}



QConfig::QConfig()
{
    this->file = new QFile("config/config.json");
    this->_theme = Theme::LIGHT;
    this->_cfg = this;

    //QVariant qvariantThemeOptionsMap = QVariant::fromValue<QMap<QString,QString>>(ThemeOptionsMap);
    QVariant defaultModeTheme = QVariant::fromValue<QString>("LIGHT");
    this->themeMode = new OptionsConfigItem(QString("QFluentWidgets"), QString("ThemeMode"), &defaultModeTheme, true);

    QVariant defaultColorTheme = QVariant::fromValue<QString>("009faa");
    this->themeColor = new ColorConfigItem("QFluentWidgets", "ThemeColor", &defaultColorTheme, true);

}

QVariant *QConfig::get(ConfigItem *item)
{
    return item->value;
}

QVariant* deepcopy(QVariant *value)
{
    QVariant copyValue;
    
    if(value->canConvert<QString>()){
        copyValue = QVariant::fromValue<QString>(value->value<QString>());
    }

    if(value->canConvert<int>()){
        copyValue = QVariant::fromValue<int>(value->value<int>());
    }

    if(value->canConvert<QMap<QString, QString>>()){
        copyValue = QVariant::fromValue<QMap<QString, QString>>(value->value<QMap<QString, QString>>());
    }

    return &copyValue;
}

void QConfig::set(ConfigItem *item, QVariant *value, bool save, bool copy)
{
    if(item->value == value)
    {
        return;
    }

    try{
        if(copy){
            item->value = deepcopy(value);
        }else{
            item->value = value;
        }
    }catch(std::exception e){
        item->value = value;
    }

    if(save){
        //TODO:this->save()
    }

    if(item->restart)
    {
        //TODO:this->_cfg->appRestartSig.emit()
    }

    if(item == this->_cfg->themeMode)
    {
        //this->theme(value)
        //self._cfg.themeChanged.emit(value)
    }

    if(item == this->_cfg->themeColor)
    {
        //TODO:self._cfg.themeColorChanged.emit(value)
    }
}


QMap<QString, QString> *toDict(bool serialize)
{
    QMap<QString, QString> *items = new QMap<QString, QString>();

}
*/

/*
ColorConfigItem::ColorConfigItem(QString group, QString name, QVariant *default_, bool restart)
{
    //ConfigItem::ConfigItem(group, name, default_, ColorValidator(default_), ColorSerializer(), restart);
}
*/
/*







    template<typename T>
    ThemeOptionValidator<T>::ThemeOptionValidator(std::map<std::string, std::string> *options)
    {
        if(options == nullptr)
        {
            throw std::invalid_argument("The options can't be empty.");
        }

        this->options = options;
    }

    template<typename T>
    bool ThemeOptionValidator<T>::validate(std::string value)
    {
        auto it = this->options->find(value);
        if(it != this->options->end())
        {
            return true;
        }else{
            return false;
        }
    }

    template<typename T>
    std::string ThemeOptionValidator<T>::correct(std::string value)
    {
        if(this->validate(value)){
            return value;
        }else{
            auto it = this->options->begin();
            return (std::string)it->first;
        }
    }

    //脱裤子放屁
    template<typename T>
    BoolValidator<T>::BoolValidator()
    {
        this->options = {true, false};
    }

    template<typename T>
    bool BoolValidator<T>::validate(bool value)
    {
        return true;
    }

    template<typename T>
    bool BoolValidator<T>::correct(bool value)
    {
        return value;
    }

    
    

    template<typename T>
    ColorValidator<T>::ColorValidator(std::string value)
    {
        this->defaultColor = QColor(value);
    }

    
    template<typename T>
    bool ColorValidator<T>::validate(std::string value)
    {
        try {
            return QColor(value).isValid();
        } catch (std::exception& e) {
            return false;
        }
    }

    template<typename T>
    QColor ColorValidator<T>::correct(std::string value)
    {
        if(this->validate(value))
        {
            return QColor(value);
        }else{
            return this->defaultColor;
        }
    }
    
    
    


    
    
    */
    
    /*
    
    */





    
    
    bool isDarkTheme()
    {
        //qconfig->set(QVariant::fromValue<OptionsConfigItem*>(qconfig->themeMode), QVariant::fromValue<QString>(QString("dark")), true, false);
        //TODO:return qconfig.theme == Theme.DARK
        QString _themeString =  qconfig->get(QVariant::fromValue<OptionsConfigItem*>(qconfig->themeMode)).value<QString>();
        if(_themeString == QString("dark")){
            return true;
        }else{
            return false;
        }
    }
    


    
//}