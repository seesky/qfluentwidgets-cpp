#pragma once

#include <map>
#include <string>

namespace qfluentwidgets{

    const static std::map<std::string, std::string> ThemeOptionsMap = {
        {"LIGHT", "LIGHT"},
        {"DARK", "DARK"},
        {"AUTO", "AUTO"}
    };

    // Config validator
    template<typename T>
    class ConfigValidator {
    public:
        //Verify whether the value is legal
        bool validate(T value) {
            return true;
        }

        //correct illegal value
        T correct(T value) {
            return value;
        }
    };

    //Range validator
    template<typename T>
    class RangeValidator : public ConfigValidator<T>
    {
    public:
        RangeValidator(int min, int max);
        ~RangeValidator();
        bool validate(int value) override;
        int correct(int value) override;

    private:
        int min_value;
        int max_value;
        int range_value[2];
    };



    template<typename T>
    class ThemeOptionValidator : public ConfigValidator<T>
    {
    public:
        ThemeOptionValidator(std::map<std::string, std::string> *options);
        ~ThemeOptionValidator();
        bool validate(std::string value) override;
        std::string correct(std::string value) override;

    private:
        std::map<std::string, std::string> *options;
    };

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
}





