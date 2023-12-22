#pragma once


#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <QtGui/QColor>
#include <QtCore/QString>
#include <QtCore/QObject>
#include <QVariant>
#include <boost/any.hpp>

//namespace Qfw{

enum class Theme{
    LIGHT,
    DARK,
    AUTO
};

const static QMap<QString, QString> ThemeOptionsMap = {
    {"LIGHT", "LIGHT"},
    {"DARK", "DARK"},
    {"AUTO", "AUTO"}
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

private:
    int min_value;
    int max_value;
    int range_value[2];
};



class OptionsValidator : public ConfigValidator{
public:
    OptionsValidator(QVariant *options);
    bool validate(QVariant *value);
    QVariant *correct(QVariant *value);
private:
    QList<QVariant *> options;
};

/*

    template<typename T>
    class BoolValidator : public ConfigValidator<T>
    {
    public:
        BoolValidator();
        ~BoolValidator();
        bool validate(bool value) override;
        bool correct(bool value) override;
    private:
        bool options[2];
    };


    template<typename T>
    class FolderValidator : public ConfigValidator<T>
    {
    public:
        bool validate(std::string value) override;
        std::string correct(std::string value) override;        
    };

    template<typename T>
    class FolderListValidator : public ConfigValidator<T>
    {
    public:
        bool validate(std::vector<std::string> value) override;
        std::vector<std::string> correct(std::vector<std::string> value) override;        
    };


    template<typename T>
    class ColorValidator : public ConfigValidator<T>
    {
    public:
        ColorValidator(std::string value);
        bool validate(std::string value) override;
        QColor correct(std::string value) override;
    private:
        QColor defaultColor;
    };


    //Config serializer
    class ConfigSerializer {
    public:
        //serialize config value
        QVariant serialize(QVariant value) {
            return value;
        }

        //deserialize config from config file's value
        QVariant deserialize(QVariant value) {
            return value;
        }
    };

    class MapSerializer : public ConfigSerializer {
    public:
        MapSerializer(std::map<std::string, std::string> value);
        std::string serialize(std::map<std::string, std::string> value);
        std::map<std::string, std::string> deserialize(std::string json);
    private:
        std::map<std::string, std::string> mapClass;
    };


    class ColorSerializer : public ConfigSerializer {
    public:
        std::string serialize(QColor value);
        QColor deserialize(std::string value);
    };

    */

    /*
    class ConfigItem : public QObject
    {
        Q_OBJECT
    public:
        ConfigItem(std::string group, std::string name, QVariant dValue, ConfigValidator<QVariant> validator, ConfigSerializer serializer, bool restart);
        QVariant getValue();
        void setValue(QVariant v);
        std::string key();
        std::string serialize();
        void deserializeFrom(std::string value);
        std::string getClassName() const;
        friend std::ostream& operator<<(std::ostream& os, const ConfigItem& obj) {
            os << obj.getClassName() << "[value=" << obj.value.String << "]";
            return os;
        }
    private:
        std::string group;
        std::string name;
        ConfigValidator<QVariant> validator;
        ConfigSerializer serializer;
        QVariant __value;
        QVariant value;
        bool restart;
        QVariant defaultValue;
    signals:
        void valueChanged(QVariant value);
    };
    */

   bool isDarkTheme();


//}





