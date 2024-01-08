#pragma once

#include <windows.h>
#include <winuser.h>
#include <dwmapi.h>
#include "swcadef.h"
#include <QtCore/Qt>
#include <QtCore/QDebug>

#include "../utils/win32_utils.h"


class WindowsWindowEffect{
public:
    WindowsWindowEffect(void *window);
    void setAcrylicEffect(HWND hWnd, QString gradientColor, bool enableShadow, int animationId);
    void setMicaEffect(HWND hWnd, bool isDarkMode, bool isAlt);
    void setAeroEffect(HWND hWnd);
    void removeBackgroundEffect(HWND hWnd);
    void addShadowEffect(HWND hWnd);
    void addMenuShadowEffect(HWND hWnd);
    void removeShadowEffect(HWND hWnd);
    static void removeMenuShadowEffect(HWND hWnd);
    static void addWindowAnimation(HWND hWnd);
    static void disableMaximizeButton(HWND hWnd);
    void enableBlurBehindWindow(HWND hWnd);

    void *window;
    ACCENT_POLICY accentPolicy;
    WINDOWCOMPOSITIONATTRIBDATA winCompAttrData;
private:
};