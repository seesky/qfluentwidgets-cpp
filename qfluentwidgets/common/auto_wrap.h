#pragma once
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtGui/QFont>
#include <QtGui/QFontMetrics>
#include <QtCore/QRegularExpression>

enum class CharType{
    SPACE,
    ASIAN,
    LATIN
};

const static QMap<QString, int> EAST_ASAIN_WIDTH_TABLE = {
    {"F", 2}, //F（全角） - 全角字母数字
    {"H", 1}, //（半角） - 所谓的半角假名(ｱｲｳｴｵ)等
    {"W", 2}, //（宽） - 上述字符以外的字符，在传统字符代码中称为全角字符。 汉字、日语假名字符和描述符号（例如标点符号），这些符号仅用于东亚的组版本
    {"A", 1}, //（模糊） - 字符宽度因上下文而异的字符。 它甚至不能用简单的中文和日语的全半角去理解。 比如希腊语、西里尔文等。 在东亚的传统字符代码中可以被视为所谓的全角
    {"N", 1}, //（中性） - 不属于上述任何字符的字符。 它通常不出现在东亚的组版本中，也不是全角的或半角的。 阿拉伯字母等
    {"Na", 1} //（窄） - 上述字符以外的字符，在传统字符代码中存在相应的所谓全角字符。 所谓的半角字母数字等。
};

static QMap<QString, int> CHAR_ASAIN_WIDTH_TABLE = {};


class TextWrap{
public:
    static int east_asian_width(QString _char, QFont font);
    static int get_width(QString _char, QFont font);
    static int get_text_width(QString text, QFont font);
    static CharType get_char_type(QString _char, QFont font);
    static QString process_text_whitespace(QString text);
    static QStringList split_long_token(QString token, int width);
    static QStringList tokenizer(QString text, QFont font);
    static std::tuple<QString, bool> wrap(QString text, int width, bool once, QFont font);
    static std::tuple<QString, bool> _wrap_line(QString text, int width, bool once, QFont font);
};