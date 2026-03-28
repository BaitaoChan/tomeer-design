#include <QPainter>
#include <QPainterPath>
#include <QVBoxLayout>
#include <QWindow>
#include <QMouseEvent>

#include "CukeWindow.h"
#include "CukeToolButton.h"
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
      CukeScope(this),
      d_ptr(new CukeWindowPrivate(this)) {
    d_ptr->_appBar = new CukeAppBar(this);
    setAttribute(Qt::WA_TranslucentBackground);
    // 保留窗口系统功能
    setWindowFlags(Qt::Window | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint | Qt::WindowSystemMenuHint);
    resize(1280, 720);
    setStyle(new CukeWindowStyle(style()));
    setStyleSheet("QMainWindow { background: transparent; }");

}

CukeWindow::~CukeWindow() = default;

bool CukeWindow::nativeEvent(const QByteArray &eventType, void *message, qintptr *result) {
    Q_D(CukeWindow);
    d->setIsResize(false);
    d->setIsDrag(false);
#ifdef Q_OS_WIN
    const auto pMsg = static_cast<MSG *>(message);
    // 隐藏非客户区
    if (pMsg->message == WM_NCCALCSIZE) {
        if (pMsg->wParam == TRUE) {
            // 获取客户区参数信息
            auto params = reinterpret_cast<NCCALCSIZE_PARAMS *>(pMsg->lParam);
            RECT &qRect = params->rgrc[0];
            const RECT pRect = qRect;

            // 先按标准窗口规则去计算客户区
            *result = DefWindowProcW(pMsg->hwnd, WM_NCCALCSIZE, pMsg->wParam, pMsg->lParam);
            qRect.top = pRect.top;
            // 恢复最大化的顶部安全边界
            if (IsZoomed(pMsg->hwnd)) {
                const int frameY = GetSystemMetrics(SM_CYSIZEFRAME) + GetSystemMetrics(SM_CXPADDEDBORDER);
                qRect.top += frameY;
            }
            return true;
        }
    }
    if (pMsg->message == WM_NCHITTEST) {
        const POINT hCursor = {GET_X_LPARAM(pMsg->lParam), GET_Y_LPARAM(pMsg->lParam)};

        RECT hRect;
        GetWindowRect(pMsg->hwnd, &hRect);

        RECT hMargin = {0, 0, 0, 0};
        // 查询系统建议的窗口边框
        AdjustWindowRectEx(&hMargin, WS_OVERLAPPEDWINDOW & ~WS_CAPTION, FALSE, NULL);

        uchar hRow = 1, hCol = 1;

        // left 区域
        if (hCursor.x >= hRect.left && hCursor.x <= hRect.left - hMargin.left) {
            d->setIsResize(true);
            hCol = 0;
        }
        // top 区域
        if (hCursor.y > hRect.top && hCursor.y <= hRect.top - hMargin.top) {
            d->setIsResize(true);
            hRow = 0;
        }
        // right 区域
        if (hCursor.x > hRect.right - hMargin.right && hCursor.x <= hRect.right) {
            d->setIsResize(true);
            hCol = 2;
        }
        // bottom 区域
        if (hCursor.y > hRect.bottom - hMargin.bottom && hCursor.y <= hRect.bottom) {
            d->setIsResize(true);
            hRow = 2;
        }

        // 返回 resize 命中
        if (d->getIsResize()) {
            static constexpr LRESULT hitArea[3][3] = {
                {HTTOPLEFT, HTTOP, HTTOPRIGHT},
                {HTLEFT, HTCLIENT, HTRIGHT},
                {HTBOTTOMLEFT, HTBOTTOM, HTBOTTOMRIGHT},
            };

            *result = hitArea[hRow][hCol];
            return true;
        }

        // appBar 区域
        if (hCursor.y > hRect.top - hMargin.top && hCursor.y <= hRect.top - hMargin.top + d->_appBar->getAppBarHeight()) {
            for (const auto &child : d->_appBar->findElems()) {
                const auto widget = static_cast<QWidget *>(child);
                if (!widget || !widget->isVisible()) {
                    continue;
                }
                // 坐标映射
                // 获取当前窗口的 DPI 缩放倍率
                const qreal hDpr = windowHandle() ? windowHandle()->devicePixelRatio() : 1.0;
                // 获取 widget 左上角在 window 内的位置
                const QPoint qCursor = widget->mapTo(window(), QPoint(0, 0));
                const auto qRect = QRect(
                    QPoint(
                        hRect.left + qRound(qCursor.x() * hDpr),
                        hRect.top + qRound(qCursor.y() * hDpr)
                    ),
                    QSize(
                        qRound(widget->width() * hDpr),
                        qRound(widget->height() * hDpr)
                    )
                );
                if (qRect.contains(QPoint(hCursor.x, hCursor.y))) {
                    d->setIsDrag(false);
                    *result = HTCLIENT;
                    return true;
                }
            }
            d->setIsDrag(true);
            *result = HTCAPTION;
            return true;
        }
    }
    if (pMsg->message == WM_GETMINMAXINFO) {
        const auto info = reinterpret_cast<MINMAXINFO *>(pMsg->lParam);
        const qreal hDpr = windowHandle() ? windowHandle()->devicePixelRatio() : 1.0;

        qreal width = 80;
        for (const auto &child : d->_appBar->findElems()) {
            const auto widget = static_cast<QWidget *>(child);
            width += widget->sizeHint().width();
        }

        info->ptMinTrackSize.x = qRound((d->_appBar ? width : minimumWidth()) * hDpr);
        *result = NULL;
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
    path.addRect(rect());

    painter.fillPath(path, cTheme->getThemeColor(getThemeMode(), CukeThemeType::Window));

    QMainWindow::paintEvent(event);
}

CUKE_NAMESPACE_END(pub)