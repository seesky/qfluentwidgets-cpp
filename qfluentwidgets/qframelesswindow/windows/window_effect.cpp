#include "window_effect.h"

WindowsWindowEffect::WindowsWindowEffect(void *window)
{
    this->window = window;
    this->accentPolicy = ACCENT_POLICY();
    this->winCompAttrData = WINDOWCOMPOSITIONATTRIBDATA();
    this->winCompAttrData.Attrib = WINDOWCOMPOSITIONATTRIB::WCA_ACCENT_POLICY;
    this->winCompAttrData.cbData = sizeof(this->accentPolicy);
    this->winCompAttrData.pvData = &(this->accentPolicy);
}

void WindowsWindowEffect::setAcrylicEffect(HWND hWnd, QString gradientColor = QString("F2F2F299"), bool enableShadow = true, int animationId = 0)
{
    if(!isGreaterEqualWin10()){
        qWarning() << "The acrylic effect is only available on Win10+";
        return;
    }
    
    QString _gradientColor;
    for (int i = 6; i >= -1; i -= 2) {
        _gradientColor += gradientColor.mid(i, 2);
    }
    qDebug() << _gradientColor;
    bool ok;
    DWORD __gradientColor = DWORD(_gradientColor.toUInt(&ok, 16));
    qDebug() << __gradientColor;
    DWORD _animationId = DWORD(animationId);
    DWORD accentFlags = enableShadow ? DWORD(0x20 | 0x40 | 0x80 | 0x100) : DWORD(0);
    this->accentPolicy.AccentState = ACCENT_STATE::ACCENT_ENABLE_ACRYLICBLURBEHIND;
    this->accentPolicy.GradientColor = __gradientColor;
    this->accentPolicy.AccentFlags = accentFlags;
    this->accentPolicy.AnimationId = animationId;
    this->winCompAttrData.Attrib = WINDOWCOMPOSITIONATTRIB::WCA_ACCENT_POLICY;
    HRESULT hr = DwmSetWindowAttribute(hWnd, this->winCompAttrData.Attrib, this->winCompAttrData.pvData, this->winCompAttrData.cbData);
}

void WindowsWindowEffect::setMicaEffect(HWND hWnd, bool isDarkMode, bool isAlt)
{
    if(!isGreaterEqualWin11()){
        return;
    }
    MARGINS margins = {-1, -1, -1, -1};
    DwmExtendFrameIntoClientArea(hWnd, &margins);

    this->winCompAttrData.Attrib = WINDOWCOMPOSITIONATTRIB::WCA_ACCENT_POLICY;
    this->accentPolicy.AccentFlags = ACCENT_STATE::ACCENT_ENABLE_HOSTBACKDROP;
    DwmSetWindowAttribute(hWnd, this->winCompAttrData.Attrib, this->winCompAttrData.pvData, this->winCompAttrData.cbData);

    if(isDarkMode){
        this->winCompAttrData.Attrib = WINDOWCOMPOSITIONATTRIB::WCA_USEDARKMODECOLORS;
        DwmSetWindowAttribute(hWnd, this->winCompAttrData.Attrib, this->winCompAttrData.pvData, this->winCompAttrData.cbData);
    }

    OSVERSIONINFOEX osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
    if (!GetVersionEx((OSVERSIONINFO*)&osvi)) {
        return;
    }

    if(osvi.dwBuildNumber < 22523)
    {
        int c_ = 1;
        DwmSetWindowAttribute(hWnd, 1029, &c_, 4);
    }else{
        int c_ = 0;
        if(isAlt){
            c_ = 4;
        }else{
            c_ = 2;
        }
        DwmSetWindowAttribute(hWnd, 38, &c_, 4);
    }

    int c_ = 1 * isDarkMode;
    DwmSetWindowAttribute(hWnd, 20, &c_, 4);

}

void WindowsWindowEffect::setAeroEffect(HWND hWnd)
{
    this->winCompAttrData.Attrib = WINDOWCOMPOSITIONATTRIB::WCA_ACCENT_POLICY;
    this->accentPolicy.AccentState = ACCENT_STATE::ACCENT_ENABLE_BLURBEHIND;
    DwmSetWindowAttribute(hWnd, this->winCompAttrData.Attrib, this->winCompAttrData.pvData, this->winCompAttrData.cbData);
}

void WindowsWindowEffect::removeBackgroundEffect(HWND hWnd)
{
    this->accentPolicy.AccentState = ACCENT_STATE::ACCENT_DISABLED;
    DwmSetWindowAttribute(hWnd, this->winCompAttrData.Attrib, this->winCompAttrData.pvData, this->winCompAttrData.cbData);
}

void WindowsWindowEffect::addShadowEffect(HWND hWnd)
{
    if(!isCompositionEnabled())
        return;
    
    MARGINS margins = {-1, -1, -1, -1};
    DwmExtendFrameIntoClientArea(hWnd, &margins);
}

void WindowsWindowEffect::addMenuShadowEffect(HWND hWnd)
{
    if(!isCompositionEnabled())
        return;
    
    int c_ = 2;
    DwmSetWindowAttribute(
            hWnd,
            DWMWINDOWATTRIBUTE::DWMWA_NCRENDERING_POLICY,
            &c_, //DWMNCRENDERINGPOLICY::DWMNCRP_ENABLED
            4
    );
}

void WindowsWindowEffect::removeShadowEffect(HWND hWnd)
{ 
    int c_ = 1;
    DwmSetWindowAttribute(
            hWnd,
            DWMWINDOWATTRIBUTE::DWMWA_NCRENDERING_POLICY,
            &c_, //DWMNCRENDERINGPOLICY::DWMNCRP_DISABLED
            4
    );
}

void WindowsWindowEffect::removeMenuShadowEffect(HWND hWnd)
{
    DWORD style = GetClassLong(hWnd, GCL_STYLE);
    style &= ~0x00020000;
    SetClassLong(hWnd, GCL_STYLE, style);
}

void PrintLastError() {
    // 获取错误代码
    DWORD error = GetLastError();

    // 将错误代码转换为可读的文本形式
    LPVOID errorMessage;
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL,
        error,
        0, // 默认语言
        (LPSTR)&errorMessage,
        0,
        NULL
    );

    // 打印错误信息
    qDebug() << L"Error Code: " << error;
    qDebug() << L"Error Message: " << static_cast<LPCWSTR>(errorMessage);

    // 释放分配的内存
    LocalFree(errorMessage);
}

void WindowsWindowEffect::addWindowAnimation(HWND hWnd)
{
    LONG style = GetWindowLongA(hWnd, GWL_STYLE);
    DWORD _ok = SetWindowLongA(hWnd, GWL_STYLE, style | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_CAPTION | CS_DBLCLKS | WS_THICKFRAME);
    qDebug() << "WindowsWindowEffect::addWindowAnimation:" << _ok;

    //PrintLastError();
}

void WindowsWindowEffect::disableMaximizeButton(HWND hWnd)
{
    DWORD style = GetWindowLong(hWnd, GWL_STYLE);
    SetClassLong(hWnd, GWL_STYLE, style & ~WS_MAXIMIZEBOX);
}

void WindowsWindowEffect::enableBlurBehindWindow(HWND hWnd)
{
    DWM_BLURBEHIND blurBehind = {0};
    blurBehind.dwFlags = DWM_BB_ENABLE;
    blurBehind.fEnable = true;
    blurBehind.fTransitionOnMaximized = false;
    blurBehind.hRgnBlur = 0;
    HRESULT hr = DwmEnableBlurBehindWindow(hWnd, &blurBehind);
}