/*
 * @Description: 
 * @Version: 1.0
 * @Autor: Xuelong Ba
 * @Date: 2024-01-13 08:31:04
 * @LastEditors: Xuelong Ba
 * @LastEditTime: 2024-01-13 09:54:23
 */
#pragma once

#include <windows.h>
#include <winuser.h>
#include <dwmapi.h>
#include <QtCore/Qt>
#include <QtCore/QDebug>
#include <QtCore/QOperatingSystemVersion>
#include <QtGui/QGuiApplication>
#include <QtGui/QWindow>
#include <QtWidgets/QWidget>
#include <QtGui/QWindowList>



bool _isMaximized(HWND hWnd);
bool getMonitorInfo(HWND hWnd, int dwFlags, LPMONITORINFO lpmi);
bool _isFullScreen(HWND hWnd);
bool isCompositionEnabled();
int getResizeBorderThickness(HWND hWnd, bool horizontal);
QWindow *findWindow(HWND hWnd);
int getDpiForWindow(HWND hWnd, bool horizontal);
int getSystemMetrics(HWND hWnd, int index, bool borizontal);
bool isGreaterEqualVersion(QOperatingSystemVersion version);
bool isGreaterEqualWin8_1();
bool isGreaterEqualWin10();
bool isGreaterEqualWin11();
bool isWin7();

enum class TASKBAR{
    LEFT = 0,
    TOP = 1,
    RIGHT = 2,
    BOTTOM = 3,
    NO_POSITION = 4
};

class Taskbar{
public:
    static bool isAutoHide();
    TASKBAR getPosition(HWND hWnd);
private:
};

class WindowsMoveResize{
public:
    static void startSystemMove(QWidget *window, QPoint globalPos);
    void startSystemResize(QWindow *window, QPoint globalPos, Qt::Edges edges){}
private:
};