#include "config.h"

#include <algorithm>
#include <vector>
#include <stdexcept>
#include <experimental/filesystem>
#include <string>
#include <QColor>
#include "json/json.h"

namespace qfluentwidgets{

    //Range validator
    template<typename T>
    RangeValidator<T>::RangeValidator(int min, int max)
    {
        this->min_value = min;
        this->max_value = max;
        this->range_value[0] = min;
        this->range_value[1] = max;
    }

    template<typename T>
    RangeValidator<T>::~RangeValidator(){}

    template<typename T>
    bool RangeValidator<T>::validate(int value)
    {
        return (this->min_value <= value) && (value <= this->max_value);
    }

    template<typename T>
    int RangeValidator<T>::correct(int value)
    {
        return std::min(std::max(this->min_value, value), this->max_value);
    }


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
    bool FolderValidator<T>::validate(std::string value)
    {
        std::experimental::filesystem::path filePath = value;
        if (std::experimental::filesystem::exists(filePath)) {
            return true;
        } else {
            return false;
        }
    }

    
    template<typename T>
    std::string FolderValidator<T>::correct(std::string value)
    {
        std::experimental::filesystem::path filePath = value;
        std::experimental::filesystem::create_directories(filePath);
        return filePath.string();
    }
    
    template<typename T>
    bool FolderListValidator<T>::validate(std::vector<std::string> value)
    {
        for (std::string path : value) {
            std::experimental::filesystem::path filePath = path;
            if (std::experimental::filesystem::exists(filePath)) {
                continue;
            } else {
                return false;
            }
        }
        return true;
    }

    template<typename T>
    std::vector<std::string> FolderListValidator<T>::correct(std::vector<std::string> value)
    {
        std::vector<std::string> folders;
        for (std::string path : value) {
            std::experimental::filesystem::path filePath = path;
            if (std::experimental::filesystem::exists(filePath)) {
                folders.push_back(path);
            }
        }
        return folders;
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
    
    template<typename T>
    MapSerializer<T>::MapSerializer(std::map<std::string, std::string> value)
    {
        this->mapClass = value;
    }

    template<typename T>
    std::string MapSerializer<T>::serialize(std::map<std::string, std::string> value)
    {
        Json::Value jObject;
        for(std::map<std::string, std::string>::const_iterator iter = value.begin(); iter != value.end(); ++iter)
        {
            jObject[iter->first] = iter->second;
        }
        return jObject.toStyledString();
    }

    std::string itoa_self(int i)
    {
        std::stringstream ss;
        ss << i;
        return ss.str();
    }

    template<typename T>
    std::map<std::string, std::string> MapSerializer<T>::deserialize(std::string json)
    {
        Json::Reader reader;
        Json::Value value;
        std::map<std::string, std::string> maps;

        if (json.length() > 0)
        {
            if (reader.parse(json, value))
            {
                Json::Value::Members members = value.getMemberNames();
                for (Json::Value::Members::iterator it = members.begin(); it != members.end(); it++)
                { 
                    Json::ValueType vt = value[*it].type();
                    switch (vt)
                    {
                    case Json::stringValue:
                        {
                            maps.insert(std::pair<std::string, std::string>(*it, value[*it].asString()));
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
}