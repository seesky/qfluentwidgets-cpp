#pragma once


#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <boost/any.hpp>
#include <QtGui/QColor>
#include <QtCore/QString>
#include <QtCore/QObject>
#include <QtCore/QVariant>
#include <QtCore/QFile>
#include <QtCore/QVariant>
#include <QtGui/QColor>
#include <QtCore/QDir>
#include <QtCore/QDebug>

#include <QSettings>
#include <QSharedPointer>
#include <QTextCodec>
#include <QCoreApplication>


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

const static QList<QString> ThemeOptionsList = {"light", "dark", "auto"};


class  IniSettings
{
public:
	QSharedPointer<QSettings> m_iniFile;

public:
    static IniSettings* getInstance();
	void settings_init(const QString &path); //初始化QSettings对象，并读取ini配置文件,如果不存在配置文件，则创建
	void setValue(const QString &section, const QString &key, const QVariant &value); //写入配置项（section:节点，key:键名，value:键值）
	void removeNode(const QString &section);                           //移除节点(包括其中所有的键值)
	void removeKey(const QString &section, const QString &key);               //移除节点中的某个键值
	QVariant getValue(const QString &section, const QString &key, const QVariant &defaultValue);  //读配置项

private:
    IniSettings();
    IniSettings(const IniSettings&) = delete;
    IniSettings& operator=(const IniSettings&) = delete;
    static IniSettings* instance;
};



/*
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
    ConfigItem(QString group, QString name, QVariant *default_, bool restart);
    QVariant *getValue();
    void setValue(QVariant *value);
    QString key();
    QString __str__();

    QString group;
    QString name;
    ConfigValidator *validator;
    QVariant *__value;
    QVariant *defaultValue;
    bool restart;
    QVariant *defaultValue;
private:
    
signals:
    void valueChanged(QVariant *value);
};

*/

class RangeConfigItem : public QObject
{
    Q_OBJECT
public:
    RangeConfigItem(QString group, QString name, int default_, int min, int max, bool restart);
    int getValue();
    void setValue(int value);
    QString key();
    QString __str__();
    bool validate(int value);
    int correct(int value);
    int *range();


    int min_value;
    int max_value;
    int range_value[2];
    QString group;
    QString name;
    int __value;
    int defaultValue;
    bool restart;
private:
    
signals:
    void valueChanged(int value);
};


Q_DECLARE_METATYPE(RangeConfigItem*)

class OptionsConfigItem : public QObject
{
    Q_OBJECT
public:
    
    OptionsConfigItem(QString group, QString name, QString default_, const QList<QString> options, bool restart);
    QString getValue();
    void setValue(QString value);
    QString key();
    QString __str__();
    bool validate(QString value);
    QString correct(QString value);
    QList<QString> options();

    QString group;
    QString name;
    QList<QString> _options;
    QString __value;
    QString defaultValue;
    bool restart;
private:
    
signals:
    void valueChanged(QString value);
};

Q_DECLARE_METATYPE(OptionsConfigItem*)


class ColorConfigItem : public QObject
{
    Q_OBJECT
public:
    ColorConfigItem(QString group, QString name, QColor default_, bool restart);
    QColor getValue();
    void setValue(QColor value);
    QString key();
    QString __str__();
    bool validate(QColor value);
    QColor correct(QColor value);

    QString group;
    QString name;
    QColor __value;
    QColor defaultValue;
    bool restart;
private:
    
signals:
    void valueChanged(QColor value);
};

Q_DECLARE_METATYPE(ColorConfigItem*)

class QConfig : public QObject{
    Q_OBJECT
public:
    static QConfig* getInstance();
    QVariant get(QVariant item);
    void set(QVariant item, QVariant value, bool save, bool copy);
    Theme getTheme();
    void setTheme(Theme t);

    Theme _theme;
    OptionsConfigItem *themeMode;
    ColorConfigItem *themeColor;
    QList<QString> _themeOptionsList;

private:
    QConfig(QObject *parent);
    QConfig(const QConfig&) = delete;
    QConfig& operator=(const QConfig&) = delete;
    static QConfig* instance;

signals:
    void appRestartSig();
    void themeChanged(Theme theme);
    void themeChangedFinished();
    void themeColorChanged(QColor);
};



/*

class RangeConfigItem : public ConfigItem{
public:
    int* range();
    
    QString getClassName() const;
    friend std::ostream& operator<<(std::ostream& os, const RangeConfigItem& obj) {
        os << obj.getClassName().toStdString() << "[range=[" << obj.value->String << "]";
        
        return os;
    }
    
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
    void themeColorChanged(QColor);
};
*/


//static QConfig *qconfig = new QConfig();

bool isDarkTheme();

static IniSettings *iniSettings = IniSettings::getInstance();
static QConfig *qconfig = QConfig::getInstance();
//}





