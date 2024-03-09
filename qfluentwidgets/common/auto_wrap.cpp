#include "auto_wrap.h"


int TextWrap::east_asian_width(QString _char, QFont font)
{
    if(CHAR_ASAIN_WIDTH_TABLE.contains(_char))
    {
        return CHAR_ASAIN_WIDTH_TABLE.value(_char);
    }

    QFontMetrics metrics(font);
    int char_width = metrics.averageCharWidth();
    if(char_width == 0){
        CHAR_ASAIN_WIDTH_TABLE.insert(_char, EAST_ASAIN_WIDTH_TABLE.value(QString("N")));
        return EAST_ASAIN_WIDTH_TABLE.value(QString("N"));
    }else if(char_width == metrics.averageCharWidth()){
        CHAR_ASAIN_WIDTH_TABLE.insert(_char, EAST_ASAIN_WIDTH_TABLE.value(QString("A")));
        return EAST_ASAIN_WIDTH_TABLE.value(QString("A"));
    }else if(char_width <= metrics.averageCharWidth()){
        CHAR_ASAIN_WIDTH_TABLE.insert(_char, EAST_ASAIN_WIDTH_TABLE.value(QString("NA")));
        return EAST_ASAIN_WIDTH_TABLE.value(QString("NA"));
    }else if(char_width > metrics.averageCharWidth() && char_width <= metrics.averageCharWidth() * 2){
        CHAR_ASAIN_WIDTH_TABLE.insert(_char, EAST_ASAIN_WIDTH_TABLE.value(QString("A")));
        return EAST_ASAIN_WIDTH_TABLE.value(QString("A"));
    }else if(char_width > metrics.averageCharWidth() * 2 && char_width <= metrics.averageCharWidth() * 2.5){
        CHAR_ASAIN_WIDTH_TABLE.insert(_char, EAST_ASAIN_WIDTH_TABLE.value(QString("N")));
        return EAST_ASAIN_WIDTH_TABLE.value(QString("N"));
    }else if(char_width > metrics.averageCharWidth() * 2.5 && char_width <= metrics.averageCharWidth() * 3){
        CHAR_ASAIN_WIDTH_TABLE.insert(_char, EAST_ASAIN_WIDTH_TABLE.value(QString("H")));
        return EAST_ASAIN_WIDTH_TABLE.value(QString("H"));
    }else{
        CHAR_ASAIN_WIDTH_TABLE.insert(_char, EAST_ASAIN_WIDTH_TABLE.value(QString("F")));
        return EAST_ASAIN_WIDTH_TABLE.value(QString("F"));
    }
}

int TextWrap::get_width(QString _char, QFont font)
{
    return TextWrap::east_asian_width(_char, font);
}

int TextWrap::get_text_width(QString text, QFont font)
{
    int sum = 0;
    for(int i = 0; i < text.length(); i++){
        sum += TextWrap::get_width(text.at(i), font);
    }
    return sum;
}

CharType TextWrap::get_char_type(QString _char, QFont font)
{
    if(_char == QString(" ")){
        return CharType::LATIN;
    }

    if(TextWrap::get_width(_char, font) == 1){
        return CharType::LATIN;
    }

    return CharType::ASIAN;
}

QString TextWrap::process_text_whitespace(QString text)
{
    QRegularExpression re("\\s+");
    QString processedText = text;
    processedText.replace(re, " ");
    processedText = processedText.trimmed();
    return processedText;
}


QStringList TextWrap::split_long_token(QString token, int width)
{
    QStringList chunks;
    for (int i = 0; i < token.length(); i += width) {
        chunks.append(token.mid(i, width));
    }
    return chunks;
}


QStringList TextWrap::tokenizer(QString text, QFont font)
{
    QStringList tokens;
    QString buffer;
    CharType lastCharType = CharType::LATIN;

    for (int i = 0; i < text.length(); ++i) {
        QChar currentChar = text.at(i);
        CharType currentCharType = TextWrap::get_char_type(currentChar, font);

        if (!buffer.isEmpty() && (currentCharType != lastCharType || currentCharType != CharType::LATIN)) {
            tokens.append(buffer);
            buffer.clear();
        }

        buffer.append(currentChar);
        lastCharType = currentCharType;
    }

    if (!buffer.isEmpty()) {
        tokens.append(buffer);
    }

    return tokens;
}

std::tuple<QString, bool> TextWrap::wrap(QString text, int width, bool once, QFont font)
{
    QStringList lines = text.split('\n');
    bool isWrapped = false;
    QStringList wrappedLines;

    for (const QString& line : lines) {
        QString processedLine = TextWrap::process_text_whitespace(line);

        if (TextWrap::get_text_width(processedLine, font) > width) {
            QString wrappedLine;
            bool lineWrapped;
            std::tie(wrappedLine, lineWrapped) = TextWrap::_wrap_line(processedLine, width, once, font);
            wrappedLines.append(wrappedLine);
            isWrapped = isWrapped || lineWrapped;

            if (once) {
                wrappedLines.append(text.mid(wrappedLine.length()).trimmed());
                return std::make_tuple(wrappedLines.join(""), isWrapped);
            }
        } else {
            wrappedLines.append(processedLine);
        }
    }

    return std::make_tuple(wrappedLines.join("\n"), isWrapped);
}

std::tuple<QString, bool> TextWrap::_wrap_line(QString text, int width, bool once, QFont font)
{
    QString lineBuffer;
    QStringList wrappedLines;
    int currentWidth = 0;

    QStringList tokens = TextWrap::tokenizer(text, font);
    for (const QString& token : tokens) {
        int tokenWidth = TextWrap::get_text_width(token, font);

        if (token == " " && currentWidth == 0) {
            continue;
        }

        if (currentWidth + tokenWidth <= width) {
            lineBuffer += token;
            currentWidth += tokenWidth;

            if (currentWidth == width) {
                wrappedLines.append(lineBuffer.trimmed());
                lineBuffer.clear();
                currentWidth = 0;
            }
        } else {
            if (currentWidth != 0) {
                wrappedLines.append(lineBuffer.trimmed());
            }

            QStringList chunks = TextWrap::split_long_token(token, width);

            for (int i = 0; i < chunks.size() - 1; ++i) {
                wrappedLines.append(chunks[i].trimmed());
            }

            lineBuffer = chunks[chunks.size() - 1];
            currentWidth = TextWrap::get_text_width(chunks[chunks.size() - 1], font);
        }
    }

    if (!lineBuffer.isEmpty()) {
        wrappedLines.append(lineBuffer.trimmed());
    }

    if (once && !wrappedLines.isEmpty()) {
        QString firstLine = wrappedLines.takeFirst();
        QString remainingLines = wrappedLines.join(" ");
        return std::make_tuple(firstLine + "\n" + remainingLines, true);
    }

    return std::make_tuple(wrappedLines.join("\n"), true);
}