#include "qframe_less_window.h"


WindowsFramelessWindow::WindowsFramelessWindow(QWidget *parent) 
{
    this->windowEffect = new WindowsWindowEffect(this);
    this->titleBar = new TitleBar(this);
    this->_isResizeEnabled = true;
    WId id = this->winId();
    this->updateFrameless();
    connect(this->windowHandle(), &QWindow::screenChanged, this, &WindowsFramelessWindow::__onScreenChanged);
    resize(500, 500);
    this->titleBar->raise();
}


void WindowsFramelessWindow::updateFrameless()
{
    if(!isWin7())
    {
        this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    }else if(this->parent()){
        this->setWindowFlags(((QWidget *)(this->parent()))->windowFlags() | Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint); //TODO:特殊关注
    }else{
        this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
    }


    HWND id = (HWND)this->winId();
    this->windowEffect->addWindowAnimation(HWND(this->winId()));    
    
    if(dynamic_cast<AcrylicWindow*>(this) != nullptr){
        this->windowEffect->addShadowEffect(HWND(this->winId()));
    }
    
}

void WindowsFramelessWindow::setTitleBar(TitleBar *titleBar)
{
    this->titleBar->deleteLater();
    this->titleBar->hide();
    this->titleBar = titleBar;
    this->titleBar->setParent(this);
    this->titleBar->raise();
}

void WindowsFramelessWindow::setResizeEnabled(bool isEnabled)
{
    this->_isResizeEnabled = isEnabled;
}

void WindowsFramelessWindow::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    this->titleBar->resize(this->width(), this->titleBar->height());
}

bool WindowsFramelessWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    
    MSG *msg = reinterpret_cast<MSG *>(message);
    qDebug() << msg->message;
    if(!msg->hwnd){
        return QWidget::nativeEvent(eventType, message, result);
    }

    
    if(msg->message == WM_NCHITTEST && this->_isResizeEnabled)
    {
        QPoint pos = QCursor().pos();
        int xPos = pos.x() - this->x();
        int yPos = pos.y() - this->y();
        int w = this->width();
        int h = this->height();

        int bw;
        if(_isMaximized(msg->hwnd) || _isFullScreen(msg->hwnd)){
            bw = 0;
        }else{
            bw = this->BORDER_WIDTH;
        }

        bool lx = xPos < bw;
        bool rx = xPos > w - bw;
        bool ty = yPos < bw;
        bool by = yPos > h - bw;

        if(lx && ty){
            *result = HTTOPLEFT;
            return true;
        }else if(rx && by){
            *result = HTBOTTOMRIGHT;
            return true;
        }else if(rx && ty){
            *result = HTTOPRIGHT;
            return true;
        }else if(lx && by){
            *result = HTBOTTOMLEFT;
            return true;
        }else if(ty){
            *result = HTTOP;
            return true;
        }else if(by){
            *result = HTBOTTOM;
            return true;
        }else if(lx){
            *result = HTLEFT;
            return true;
        }else if(rx){
            *result = HTRIGHT;
            return true;
        }
    }
    else if(msg->message == WM_NCCALCSIZE){
        RECT rect = {0};

        
        if(msg->wParam){
            LPNCCALCSIZE_PARAMS params = reinterpret_cast<LPNCCALCSIZE_PARAMS>(msg->lParam);
            rect = params->rgrc[0];
        }else{
            rect.bottom = reinterpret_cast<LPRECT>(msg->lParam)->bottom;
            rect.left = reinterpret_cast<LPRECT>(msg->lParam)->left;  
            rect.right = reinterpret_cast<LPRECT>(msg->lParam)->right; 
            rect.top = reinterpret_cast<LPRECT>(msg->lParam)->top; 
        }
        
        bool isMax = _isMaximized(msg->hwnd);
        bool isFull = _isFullScreen(msg->hwnd);
        
        if(isMax && !isFull){
            int ty = getResizeBorderThickness(msg->hwnd, false);
            rect.top +=  ty;
            rect.bottom -= ty;

            int tx = getResizeBorderThickness(msg->hwnd, true);
            rect.left += tx;
            rect.right -= tx;
        }

        
        
        if((isMax || isFull) && Taskbar::isAutoHide()){
            TASKBAR position = Taskbar().getPosition(msg->hwnd);
            if(position == TASKBAR::TOP){
                rect.top += 2; //AUTO_HIDE_THICKNESS = 2
            }else if(position == TASKBAR::BOTTOM){
                rect.bottom -= 2;
            }else if(position == TASKBAR::LEFT){
                rect.left += 2;
            }else if(position == TASKBAR::RIGHT){
                rect.right -= 2;
            }
        }

        int _result = !msg->wParam ? 0 : WVR_REDRAW;
        *result = _result;
        return true;
        
    }


    return QWidget::nativeEvent(eventType, message, result);
}


FramelessDialog::FramelessDialog(QWidget *parent) : QDialog(parent), WindowsFramelessWindow(parent)
{
    this->titleBar->minBtn->hide();
    this->titleBar->maxBtn->hide();
    this->titleBar->setDoubleClickEnabled(false);
    this->windowEffect->disableMaximizeButton(HWND(((QWindow *)(this))->winId()));
}

FramelessMainWindow::FramelessMainWindow(QWidget *parent) : QMainWindow(parent), WindowsFramelessWindow(parent)
{
    
}



void WindowsFramelessWindow::__onScreenChanged()
{
    HWND hWnd = HWND(windowHandle()->winId());
    SetWindowPos(hWnd, nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
}

AcrylicWindow::AcrylicWindow(QWidget *parent) : WindowsFramelessWindow(parent)
{
    this->__closeByKey = false;
    setStyleSheet(QString("AcrylicWindow{background:transparent}"));
}



void AcrylicWindow::updateFrameless()
{
    WindowsFramelessWindow::updateFrameless();
    this->windowEffect->enableBlurBehindWindow(HWND(this->winId()));

    if(isWin7() && this->parent()){
        this->setWindowFlags(((QWidget *)(this->parent()))->windowFlags() | Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);
    }else{
        this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);
    }

    this->windowEffect->addWindowAnimation(HWND(this->winId()));

    if(isWin7()){
        this->windowEffect->addShadowEffect(HWND(this->winId()));
        this->windowEffect->setAeroEffect(HWND(this->winId()));
    }else{
        this->windowEffect->setAcrylicEffect(HWND(this->winId()), QString("F2F2F299"), true, 0);
        if(isGreaterEqualWin11()){
            this->windowEffect->addShadowEffect(HWND(this->winId()));
        }
    }
}


bool AcrylicWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    MSG *msg = reinterpret_cast<MSG *>(message);
    if(msg->message == WM_SYSKEYDOWN){
        if(msg->wParam == VK_F4){
            this->__closeByKey = true;
            QApplication::sendEvent(this, new QCloseEvent());
            *result = 0;
            return false;
        }
    }

    return WindowsFramelessWindow::nativeEvent(eventType, message, result);
}

void AcrylicWindow::closeEvent(QCloseEvent *event)
{
    if(!this->__closeByKey || QApplication::quitOnLastWindowClosed()){
        this->__closeByKey = false;
        return WindowsFramelessWindow::closeEvent(event);
    }

    this->__closeByKey = false;
    this->hide();
}
