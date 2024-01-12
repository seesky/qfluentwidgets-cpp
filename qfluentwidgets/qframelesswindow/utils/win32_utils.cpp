#include "win32_utils.h"

bool _isMaximized(HWND hWnd)
{
    struct tagWINDOWPLACEMENT t;
    t.length = sizeof(tagWINDOWPLACEMENT);
    GetWindowPlacement(hWnd, &t);
    return t.showCmd == SW_MAXIMIZE;
}

bool getMonitorInfo(HWND hWnd, int dwFlags, MONITORINFO *lpmi)
{
    HMONITOR hMonitor;
    hMonitor = MonitorFromWindow(hWnd, dwFlags);
    if(hMonitor == nullptr)
    {
        return false;
    }
    MONITORINFO mi = {0};
    mi.cbSize = sizeof(MONITORINFO);
    GetMonitorInfo(hMonitor, &mi);
    return GetMonitorInfo(hMonitor, lpmi);
    /*
    if(GetMonitorInfo(hMonitor,lpmi)){
        return true;
    }else{
        return false;
    }
    */
}

bool _isFullScreen(HWND hWnd)
{
    if(!hWnd){
        return false;
    }

    RECT rect = {0};
    if(!GetWindowRect(hWnd,  &rect))
    {
        return false;
    }

    MONITORINFO monitorInfo = {0};
    monitorInfo.cbSize = sizeof(MONITORINFO);
    if(!getMonitorInfo(hWnd, MONITOR_DEFAULTTOPRIMARY, &monitorInfo))
    {
        return false;
    }

    RECT monitorRect;
    monitorRect.bottom = monitorInfo.rcMonitor.bottom;
    monitorRect.left = monitorInfo.rcMonitor.left;
    monitorRect.right = monitorInfo.rcMonitor.right;
    monitorRect.top = monitorInfo.rcMonitor.top;
    if(monitorRect.bottom == rect.bottom && monitorRect.left == rect.left && monitorRect.right == rect.right && monitorRect.top == rect.top)
    {
        return true;
    }else{
        return false;
    }
}


bool isCompositionEnabled()
{
    WINBOOL pfEnabled;
    if(DwmIsCompositionEnabled(&pfEnabled)){
        return pfEnabled;
    }else{
        return false;
    }
}

QWindow *findWindow(HWND hWnd)
{
    if(!hWnd){
        return nullptr;
    }

    QWindowList windows =  QGuiApplication::topLevelWindows();
    if(windows.isEmpty()){
        return nullptr;
    }
    
    QList<QWindow *>::iterator it;
    for (it = windows.begin(); it != windows.end(); ++it) {
        HWND _hWnd = reinterpret_cast<HWND>((*it)->winId());
        if((*it) != nullptr and _hWnd == _hWnd){
            return *it;
        }
    }
}

int getDpiForWindow(HWND hWnd, bool horizontal)
{
    HDC hdc = GetDC(hWnd);
    if(!hdc)
        return 96;
    
    int dpiX = GetDeviceCaps(hdc, LOGPIXELSX);
    int dpiY = GetDeviceCaps(hdc, LOGPIXELSY);

    ReleaseDC(hWnd, hdc);

    if(dpiX > 0 && horizontal){
        return dpiX;
    }else if(dpiY > 0 && horizontal){
        return dpiY;
    }

    return 96;
}

int getSystemMetrics(HWND hWnd, int index, bool borizontal)
{
    return GetSystemMetrics(index);
}

int getResizeBorderThickness(HWND hWnd, bool horizontal)
{
    QWindow *window = findWindow(hWnd);
    if(window == nullptr)
        return 0;
    
    int frame = horizontal ? SM_CXSIZEFRAME : SM_CYSIZEFRAME;
    int result = getSystemMetrics(hWnd, frame, horizontal) + getSystemMetrics(hWnd, 92, horizontal);
    if(result > 0)
        return result;

    int thickness = isCompositionEnabled() ? 8 : 4;
    return qRound(thickness * window->devicePixelRatio());
}

bool isGreaterEqualVersion(QOperatingSystemVersion version)
{
    return QOperatingSystemVersion::current() >= version;
}

bool isGreaterEqualWin8_1()
{
    return isGreaterEqualVersion(QOperatingSystemVersion::Windows8_1);
}

bool isGreaterEqualWin10()
{
    return isGreaterEqualVersion(QOperatingSystemVersion::Windows10);
}

bool isGreaterEqualWin11()
{
    OSVERSIONINFOEX osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
    if (!GetVersionEx((OSVERSIONINFO*)&osvi)) {
        return false;   
    }
    return isGreaterEqualVersion(QOperatingSystemVersion::Windows10) && osvi.dwBuildNumber >= 22000;
}

bool isWin7()
{
    return isGreaterEqualVersion(QOperatingSystemVersion::Windows7);
}

bool Taskbar::isAutoHide()
{
    RECT rect = {0};
    APPBARDATA appbarData;
    appbarData.cbSize = sizeof(APPBARDATA);
    appbarData.hWnd = 0;
    appbarData.uCallbackMessage = 0,
    appbarData.uEdge = 0,
    appbarData.rc = rect,
    appbarData.lParam = 0;

    UINT_PTR taskbarState = SHAppBarMessage(ABM_GETSTATE, &appbarData);

    return taskbarState == ABS_AUTOHIDE;
}

TASKBAR Taskbar::getPosition(HWND hWnd)
{
    if(isGreaterEqualWin8_1())
    {
        MONITORINFO monitorInfo;
        if(!getMonitorInfo(hWnd, MONITOR_DEFAULTTONEAREST, &monitorInfo))
            return TASKBAR::NO_POSITION;
        
        RECT monitor = monitorInfo.rcMonitor;
        APPBARDATA appbarData;
        appbarData.cbSize = sizeof(APPBARDATA);
        appbarData.hWnd = 0;
        appbarData.lParam = 0;
        appbarData.rc = monitor;
        appbarData.uCallbackMessage = 0;
        appbarData.uEdge = 0;

        TASKBAR positions[4] = {TASKBAR::LEFT, TASKBAR::TOP, TASKBAR::RIGHT, TASKBAR::BOTTOM};
        for(int i = 0; i < 4; i++){
            appbarData.uEdge = static_cast<int>(positions[i]);
            if(SHAppBarMessage(11, &appbarData)){
                return positions[i];
            }
        }
        return TASKBAR::NO_POSITION;
    }

    APPBARDATA appbarData;
    appbarData.cbSize = sizeof(APPBARDATA);
    appbarData.hWnd = FindWindow("Shell_TrayWnd", nullptr);
    appbarData.lParam = 0;
    appbarData.uCallbackMessage = 0;
    appbarData.uEdge = 0;
    RECT rect = {0};
    appbarData.rc = rect; 

    if(appbarData.hWnd){
        HMONITOR windowMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
        if(windowMonitor == nullptr){
            return TASKBAR::NO_POSITION;
        }

        HMONITOR taskbarMonitor = MonitorFromWindow(appbarData.hWnd, MONITOR_DEFAULTTONEAREST);
        if(taskbarMonitor == nullptr){
            return TASKBAR::NO_POSITION;
        }
        
        if(taskbarMonitor == windowMonitor){
            SHAppBarMessage(ABM_GETTASKBARPOS, &appbarData);
            if(appbarData.uEdge == 0){
                return TASKBAR::LEFT;
            }else if(appbarData.uEdge == 1){
                return TASKBAR::TOP;
            }else if(appbarData.uEdge == 2){
                return TASKBAR::RIGHT;
            }else if(appbarData.uEdge == 3){
                return TASKBAR::BOTTOM;
            }else{
                return TASKBAR::NO_POSITION;
            }
        }
    }
    return TASKBAR::NO_POSITION;
}

void WindowsMoveResize::startSystemMove(QWindow *window, QPoint globalPos)
{
    ReleaseCapture();
    SendMessage((HWND)(window->winId()), WM_SYSCOMMAND, SC_MOVE | HTCAPTION, 0);
}