#pragma once

#include <QtCore/Qt>
#include <QtGui/QCloseEvent>
#include <QtGui/QCursor>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QDialog>
#include <QtWidgets/QMainWindow>

#include "../titlebar/titlebar.h"
#include "../utils/win32_utils.h"
#include "window_effect.h"

class WindowsFramelessWindow : public QWidget{
    Q_OBJECT
public:
    WindowsFramelessWindow(QWidget *parent);
    void updateFrameless();
    void setTitleBar(TitleBar *titleBar);
    void setResizeEnabled(bool isEnabled);
    void resizeEvent(QResizeEvent *event);
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
    void __onScreenChanged();

    int BORDER_WIDTH = 5;
    WindowsWindowEffect *windowEffect;
    TitleBar *titleBar;
    bool _isResizeEnabled;
private:
};

class AcrylicWindow : public WindowsFramelessWindow{
    Q_OBJECT
public:
    AcrylicWindow(QWidget *parent);
    void updateFrameless();
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
    void closeEvent(QCloseEvent *event);

    bool __closeByKey;
private:
};

class FramelessDialog : public QDialog, public WindowsFramelessWindow{
public:
    FramelessDialog(QWidget *parent);
private:
};

class FramelessMainWindow : public QMainWindow, public WindowsFramelessWindow{
public:
    FramelessMainWindow(QWidget *parent);
private:
};