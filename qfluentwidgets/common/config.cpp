#include "config.h"

#include <algorithm>
#include <vector>
#include <stdexcept>
#include <experimental/filesystem>
#include "json/json.h"

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
                /*
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
                */
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

ConfigItem::ConfigItem(QString group, QString name, QVariant *default_, ConfigValidator *validator, ConfigSerializer *serializer, bool restart)
{
    this->group = group;
    this->name = name;
    this->validator = validator;
    this->serializer = serializer;
    this->__value = default_;
    this->value = default_;
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
        emit valueChanged(v);
    }
}


QString ConfigItem::key()
{
    if(this->name != "")
    {
        return this->group + "." + this->name;
    }else{
        return this->group;
    }
}


QString ConfigItem::getClassName() const
{
    return QString(typeid(*this).name());
}


QString ConfigItem::serialize()
{
    return this->serializer->serialize(this->value)->value<QString>();
}

void ConfigItem::deserializeFrom(QString value)
{
    QVariant QVariantValue = QVariant::fromValue(value);
    this->value = this->serializer->deserialize(&QVariantValue);
}

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
        //TODO:return qconfig.theme == Theme.DARK
        return false;
    }
    
    
//}