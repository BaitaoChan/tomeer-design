#include <QPainter>
#include <QPainterPath>
#include <QVBoxLayout>
#include <QWidget>

#include "CukeWindow.h"
#include "CukeWindowStyle.h"
#include "CukeWindowPrivate.h"
#include "CukeAppBar.h"

#ifdef Q_OS_WIN
#include <windows.h>
#include <windowsx.h>
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")
#endif

CUKE_NAMESPACE_BEGIN(pub)
CUKE_Q_PROPERTY_IMPL(CukeWindow, int, BorderRadius)
CukeWindow::CukeWindow(QWidget *parent)
    : QMainWindow(parent),
      CukeHub(this),
      d_ptr(new CukeWindowPrivate(this)) {
    _pBorderRadius = 8;
    d_ptr->_appBar = new CukeAppBar(this);
    // 禁止绘制系统标题栏以及边框
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
    resize(1280, 720);
    setStyle(new CukeWindowStyle(style()));
    setStyleSheet("QMainWindow { background: transparent; }");

    d_ptr->_widget = new QWidget(this);
    d_ptr->_layout = new QVBoxLayout(d_ptr->_widget);
    d_ptr->_layout->setContentsMargins(0, 0, 0, 0);

    d_ptr->_layout->addWidget(d_ptr->_appBar);
    d_ptr->_layout->addStretch();

    setCentralWidget(d_ptr->_widget);
}

CukeWindow::~CukeWindow() = default;

void CukeWindow::resize(int w, int h) {
    QMainWindow::resize(w, h + d_ptr->_appBar->getAppBarHeight());
}

bool CukeWindow::nativeEvent(const QByteArray &eventType, void *message, qintptr *result) {
    Q_D(CukeWindow);
    d->setIsResize(false);
    d->setIsDrag(false);
#ifdef Q_OS_WIN
    MSG *pMsg = static_cast<MSG *>(message);
    if (pMsg->message == WM_NCHITTEST) {
        const POINT ptMouse = {GET_X_LPARAM(pMsg->lParam), GET_Y_LPARAM(pMsg->lParam)};

        RECT hRect;
        GetWindowRect(pMsg->hwnd, &hRect);

        RECT hMargin = {0, 0, 0, 0};
        // 查询系统建议的窗口边框
        AdjustWindowRectEx(&hMargin, WS_OVERLAPPEDWINDOW & ~WS_CAPTION, FALSE, NULL);

        uchar hRow = 1, hCol = 1;

        // left 区域
        if (ptMouse.x >= hRect.left && ptMouse.x <= hRect.left - hMargin.left) {
            d->setIsResize(true);
            hCol = 0;
        }
        // top 区域
        if (ptMouse.y > hRect.top && ptMouse.y <= hRect.top - hMargin.top) {
            d->setIsResize(true);
            hRow = 0;
        } else if (ptMouse.y > hRect.top - hMargin.top && ptMouse.y <= hRect.top + d->_appBar->getAppBarHeight()) {
            d->setIsDrag(true);
            hRow = 0;
        }
        // right 区域
        if (ptMouse.x > hRect.right - hMargin.right && ptMouse.x <= hRect.right) {
            d->setIsResize(true);
            hCol = 2;
        }
        // bottom 区域
        if (ptMouse.y > hRect.bottom - hMargin.bottom && ptMouse.y <= hRect.bottom) {
            d->setIsResize(true);
            hRow = 2;
        }

        const LRESULT hitArea[3][3] = {
            {HTTOPLEFT, d->getIsDrag() ? HTCAPTION : HTTOP, HTTOPRIGHT},
            {HTLEFT, HTNOWHERE, HTRIGHT},
            {HTBOTTOMLEFT, HTBOTTOM, HTBOTTOMRIGHT},
        };

        *result = hitArea[hRow][hCol];
        return true;
    }
#endif
    return QMainWindow::nativeEvent(eventType, message, result);
}

void CukeWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);
}


void CukeWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    QPainterPath path;
    path.addRoundedRect(rect(), _pBorderRadius, _pBorderRadius);

    painter.fillPath(path, cTheme->getThemeColor(getThemeMode(), CukeThemeType::Window));

    QMainWindow::paintEvent(event);
}

CUKE_NAMESPACE_END(pub)