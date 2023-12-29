#pragma once


#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <QtGui/QColor>
#include <QtCore/QString>
#include <QtCore/QObject>
#include <QVariant>
#include <QFile>
#include <boost/any.hpp>

//namespace Qfw{

enum class Theme{
    LIGHT,
    DARK,
    AUTO
};

const static QMap<QString, QString> ThemeOptionsMap = {
    {"LIGHT", "light"},
    {"DARK", "dark"},
    {"AUTO", "auto"}
};


class ConfigValidator {
public:
    ConfigValidator(){};
    bool validate(QVariant *value);
    QVariant *correct(QVariant *value);
private:
    QVariant *value;
};

class RangeValidator : public ConfigValidator
{
public:
    RangeValidator(int min, int max);
    bool validate(QVariant *value);
    QVariant *correct(QVariant *value);
    int min_value;
    int max_value;
    int range_value[2];
private:

};



class OptionsValidator : public ConfigValidator{
public:
    OptionsValidator(QVariant *options);
    bool validate(QVariant *value);
    QVariant *correct(QVariant *value);
    QList<QVariant *> options;
private:

};

Q_DECLARE_METATYPE(QVariant *)




class BoolValidator : public ConfigValidator
{
public:
    BoolValidator(){};
    bool validate(QVariant *value);
    bool correct(QVariant *value);
private:
    bool options[2] = {true, false};
};


class FolderValidator : public ConfigValidator
{
public:
    bool validate(QVariant *value);
    QString correct(QVariant *value);        
};



class FolderListValidator : public ConfigValidator
{
public:
    bool validate(QVariant *value);
    QList<QString> correct(QVariant *value);        
};



class ColorValidator : public ConfigValidator
{
public:
    ColorValidator(QVariant *default_);
    bool validate(QVariant * value);
    QColor* correct(QVariant * value);
private:
    QColor *default_;
};

class ConfigSerializer {
public:
    //serialize config value
    QVariant *serialize(QVariant *value) {
        return value;
    }

    //deserialize config from config file's value
    QVariant *deserialize(QVariant *value) {
        return value;
    }
};


class MapSerializer : public ConfigSerializer {
public:
    MapSerializer(QMap<QString, QString> value);
    QString serialize(QMap<QString, QString> value);
    QMap<QString, QString> deserialize(QString json);
private:
    QMap<QString, QString> mapClass;
};

class ColorSerializer : public ConfigSerializer {
public:
    QString serialize(QColor value);
    QColor deserialize(QString value);
};

class ConfigItem : public QObject
{
    Q_OBJECT
public:
    ConfigItem(){};
    ConfigItem(QString group, QString name, QVariant *default_, ConfigValidator *validator, ConfigSerializer *serializer, bool restart);
    QVariant *getValue();
    void setValue(QVariant *value);
    QString key();
    QString serialize();
    void deserializeFrom(QString value);
    QString getClassName() const;
    friend std::ostream& operator<<(std::ostream& os, const ConfigItem& obj) {
        os << obj.getClassName().toStdString() << "[value=" << obj.value->String << "]";
        return os;
    }

    QString group;
    QString name;
    ConfigValidator *validator;
    ConfigSerializer *serializer;
    QVariant *__value;
    QVariant *value;
    bool restart;
    QVariant *defaultValue;
private:
    
signals:
    void valueChanged(QVariant *value);
};


class RangeConfigItem : public ConfigItem{
public:
    int* range();
    /*
    QString getClassName() const;
    friend std::ostream& operator<<(std::ostream& os, const RangeConfigItem& obj) {
        os << obj.getClassName().toStdString() << "[range=[" << obj.value->String << "]";
        
        return os;
    }
    */
private:
};

class OptionsConfigItem : public ConfigItem{
public:
    OptionsConfigItem(QString group, QString name, QVariant *default_, bool restart);
    QList<QVariant *> options();
};


class ColorConfigItem : public ConfigItem{
public:
    ColorConfigItem(QString group, QString name, QVariant *default_, bool restart);
};

class QConfig : public QObject{
    Q_OBJECT
public: 
    OptionsConfigItem *themeMode; 
    ColorConfigItem *themeColor;
    QFile *file;
    Theme _theme = Theme::LIGHT;
    QConfig *_cfg;
    QConfig();
    QVariant *get(ConfigItem *item);
    void set(ConfigItem *item, QVariant *value, bool save, bool copy);
    QMap<QString, QString> *toDict(bool serialize);
signals:
    void appRestartSig();
    void themeChanged(Theme theme);
    void themeChangedFinished();
    void themeColorChanged(QColor *color);
};

//static QConfig *qconfig = new QConfig();

bool isDarkTheme();


//}





