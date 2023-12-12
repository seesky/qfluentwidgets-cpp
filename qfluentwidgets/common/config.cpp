#include "config.h"

#include <algorithm>
#include <vector>
#include <stdexcept>

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
}