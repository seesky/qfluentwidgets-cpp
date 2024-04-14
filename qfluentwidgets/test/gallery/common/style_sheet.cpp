#include "style_sheet.h"

StyleSheet::StyleSheet() : StyleSheetBase()
{

}

QString StyleSheet::path(QString ThemeOptionsName, QString FluentStyleSheetName, Theme theme)
{
    return "source/gallery_resource/qss/" + ThemeOptionsMap.value(ThemeOptionsName) + "/" + StyleSheetMap.value(FluentStyleSheetName) + ".qss";    
}
