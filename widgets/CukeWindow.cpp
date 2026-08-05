#include <QPainter>
#include <QVBoxLayout>
#include <QWindow>
#include <QMouseEvent>
#include <QGuiApplication>
#include <QStyleHints>

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

CUKE_NAMESPACE_BEGIN()
CUKE_Q_PROPERTY_IMPL(Window, int, BorderRadius)
CUKE_Q_PROPERTY_IMPL(Window, ThemeType::ThemeMode, ThemeMode)
Window::Window(QWidget *parent)
    : QMainWindow(parent),
      d_ptr(new WindowPrivate(this)) {
    Q_D(Window);
    setDisplayMode(WindowType::Normal);
    d->_appBar = new AppBar(this);
    setAttribute(Qt::WA_TranslucentBackground);
    // 保留窗口系统功能
    setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);
    resize(1280, 720);
    setStyle(new WindowStyle(style()));
    setStyleSheet("QMainWindow { background: transparent; }");
    connect(CUKE_THEME, &Theme::themeModeChanged, this, &Window::onThemeChanged);
    connect(CUKE_THEME, &Theme::themeColorChanged, this, QOverload<>::of(&QWidget::update));
}

Window::~Window() = default;

void Window::setDisplayMode(WindowType::DisplayMode pDisplayMode) {
    Q_D(Window);
    if (_pDisplayMode != pDisplayMode) {
        _pDisplayMode = pDisplayMode;
        Q_EMIT pDisplayModeChanged();
    }

    bool isApplied = false;
#ifdef Q_OS_WIN
    if (windowHandle()) {
        DWM_SYSTEMBACKDROP_TYPE backdropType = DWMSBT_NONE;
        switch (pDisplayMode) {
            case WindowType::Mica:
                backdropType = DWMSBT_MAINWINDOW;
                break;
            case WindowType::MicaAlt:
                backdropType = DWMSBT_TABBEDWINDOW;
                break;
            case WindowType::Acrylic:
                backdropType = DWMSBT_TRANSIENTWINDOW;
                break;
            default:
                break;
        }

        auto themeMode = CUKE_THEME->getThemeMode();
        if (themeMode == ThemeType::System) {
            if (QGuiApplication::styleHints()->colorScheme() == Qt::ColorScheme::Dark)
                themeMode = ThemeType::Dark;
            else
                themeMode = ThemeType::Light;
        }

        const auto hwnd = reinterpret_cast<HWND>(winId());
        const BOOL mode = themeMode == ThemeType::Dark;
        DwmSetWindowAttribute(hwnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &mode, sizeof(mode));

        const HRESULT result = DwmSetWindowAttribute(hwnd, DWMWA_SYSTEMBACKDROP_TYPE, &backdropType, sizeof(backdropType));
        isApplied = SUCCEEDED(result) && backdropType != DWMSBT_NONE;

        const MARGINS margins = backdropType != DWMSBT_NONE
                                    ? MARGINS{-1, -1, -1, -1}
                                    : MARGINS{0, 0, 0, 0};
        DwmExtendFrameIntoClientArea(hwnd, &margins);

        struct AccentPolicy {
            int state;
            int flags;
            DWORD color;
            int animationId;
        };
        struct WindowCompositionAttributeData {
            int attribute;
            PVOID data;
            SIZE_T size;
        };
        using SetWindowCompositionAttribute = BOOL(WINAPI *)(HWND, WindowCompositionAttributeData *);

        const auto user32 = GetModuleHandleW(L"user32.dll");
        if (const auto setWindowCompositionAttribute = reinterpret_cast<SetWindowCompositionAttribute>(GetProcAddress(user32, "SetWindowCompositionAttribute"))) {
            const QColor color = CUKE_THEME->getThemeColor(themeMode, ThemeType::DwmBlur);
            AccentPolicy accent = {
                pDisplayMode == WindowType::DwmBlur ? 4 : 0,
                0,
                (static_cast<DWORD>(color.alpha()) << 24) | (static_cast<DWORD>(color.blue()) << 16) |
                (static_cast<DWORD>(color.green()) << 8) | static_cast<DWORD>(color.red()),
                0
            };
            WindowCompositionAttributeData data = {19, &accent, sizeof(accent)};
            const BOOL result = setWindowCompositionAttribute(hwnd, &data);
            if (pDisplayMode == WindowType::DwmBlur)
                isApplied = result;
        }
    }
#endif

    d->setIsApplied(isApplied);
    update();
}

WindowType::DisplayMode Window::getDisplayMode() const {
    return _pDisplayMode;
}


AppBar *Window::appBar() {
    Q_D(Window);
    return d->_appBar;
}

bool Window::nativeEvent(const QByteArray &eventType, void *message, qintptr *result) {
    Q_D(Window);
    d->setIsResize(false);
    d->setIsDrag(false);
#ifdef Q_OS_WIN
    const auto pMsg = static_cast<MSG *>(message);
    // 获取当前窗口所在显示器对应的 DPI
    const UINT dpi = GetDpiForWindow(pMsg->hwnd);
    // 获取逻辑像素到物理像素的缩放倍率
    const qreal hDpr = windowHandle() ? windowHandle()->devicePixelRatio() : 1.0;
    // 获取标准可缩放窗口顶部或底部的完整框架厚度
    const int frameY = GetSystemMetricsForDpi(SM_CYSIZEFRAME, dpi) + GetSystemMetricsForDpi(SM_CXPADDEDBORDER, dpi);
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
                qRect.top += frameY;
            }
            return true;
        }
    }
    if (pMsg->message == WM_NCHITTEST) {
        const POINT hCursor = {GET_X_LPARAM(pMsg->lParam), GET_Y_LPARAM(pMsg->lParam)};

        RECT hRect;
        GetWindowRect(pMsg->hwnd, &hRect);

        // 获取客户区左上角对应的屏幕坐标
        POINT cTopLeft{0, 0};
        ClientToScreen(pMsg->hwnd, &cTopLeft);

        RECT hMargin = {0, 0, 0, 0};
        // 查询系统建议的窗口边框
        AdjustWindowRectExForDpi(&hMargin, WS_OVERLAPPEDWINDOW & ~WS_CAPTION, FALSE, 0, dpi);

        uchar hRow = 1, hCol = 1;

        // 最大化取消窗口边缘缩放
        if (!IsZoomed(pMsg->hwnd)) {
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
        const int appBarHeight = qRound(d->_appBar->getAppBarHeight() * hDpr);
        if (hCursor.y >= cTopLeft.y && hCursor.y <= cTopLeft.y + appBarHeight) {
            for (const auto &child : d->_appBar->objects()) {
                const auto widget = static_cast<QWidget *>(child);
                if (!widget || !widget->isVisible()) {
                    continue;
                }
                // 坐标映射
                // 获取 widget 左上角在 window 内的位置
                const QPoint qCursor = widget->mapTo(window(), QPoint(0, 0));

                int cTop = hRect.top;
                if (IsZoomed(pMsg->hwnd)) {
                    cTop += frameY;
                }
                const auto qRect = QRect(
                    QPoint(
                        cTopLeft.x + qRound(qCursor.x() * hDpr),
                        cTopLeft.y + qRound(qCursor.y() * hDpr)
                    ),
                    QSize(
                        qRound(widget->width() * hDpr),
                        qRound(widget->height() * hDpr)
                    )
                );
                if (qRect.contains(QPoint(hCursor.x, hCursor.y))) {
                    d->setIsDrag(false);
                    if (widget == static_cast<ToolButton *>(d->_appBar->object(AppBarType::MaximizeButton))) {
                        *result = HTMAXBUTTON;
                        return true;
                    }
                    *result = HTCLIENT;
                    return true;
                }
            }
            d->setIsDrag(true);
            *result = HTCAPTION;
            return true;
        }
    }
    // 非客户区光标事件
    if (pMsg->message == WM_NCMOUSEMOVE) {
        if (pMsg->wParam == HTMAXBUTTON) {
            if ((d->_widget = static_cast<ToolButton *>(d->_appBar->object(AppBarType::MaximizeButton)))) {
                QEvent enterEvent(QEvent::Enter);
                QCoreApplication::sendEvent(static_cast<ToolButton *>(d->_widget), &enterEvent);
                *result = NULL;
                return true;
            }
        }
        if (d->_widget) {
            QEvent leaveEvent(QEvent::Leave);
            QCoreApplication::sendEvent(static_cast<QWidget *>(d->_widget), &leaveEvent);
            d->_widget = nullptr;
            *result = NULL;
            return true;
        }
    }
    // 客户区光标事件
    if (pMsg->message == WM_MOUSEMOVE) {
        if (d->_widget) {
            QEvent leaveEvent(QEvent::Leave);
            QCoreApplication::sendEvent(static_cast<ToolButton *>(d->_widget), &leaveEvent);

            d->_widget = nullptr;
        }
    }
    if (pMsg->message == WM_NCLBUTTONDOWN) {
        if (pMsg->wParam == HTMAXBUTTON) {
            if (d->_widget) {
                // QCursor::pos() 全局坐标
                QMouseEvent pressEvent(
                    QEvent::MouseButtonPress,
                    static_cast<ToolButton *>(d->_widget)->mapFromGlobal(QCursor::pos()),
                    QCursor::pos(),
                    Qt::LeftButton,
                    Qt::LeftButton,
                    Qt::NoModifier
                );

                QCoreApplication::sendEvent(static_cast<ToolButton *>(d->_widget), &pressEvent);

                *result = NULL;
                return true;
            }
        }
    }
    if (pMsg->message == WM_NCLBUTTONUP) {
        if (pMsg->wParam == HTMAXBUTTON) {
            if (d->_widget) {
                QMouseEvent releaseEvent(
                    QEvent::MouseButtonRelease,
                    static_cast<ToolButton *>(d->_widget)->mapFromGlobal(QCursor::pos()),
                    QCursor::pos(),
                    Qt::LeftButton,
                    Qt::NoButton,
                    Qt::NoModifier
                );

                QCoreApplication::sendEvent(static_cast<ToolButton *>(d->_widget), &releaseEvent);

                *result = NULL;
                return true;
            }
        }
    }
    if (pMsg->message == WM_GETMINMAXINFO) {
        const auto info = reinterpret_cast<MINMAXINFO *>(pMsg->lParam);

        qreal width = 80;
        for (const auto &child : d->_appBar->objects()) {
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

void Window::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);
}


void Window::paintEvent(QPaintEvent *event) {
    Q_D(Window);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    if (d->getIsApplied() && getDisplayMode() != WindowType::Normal) {
    } else
        painter.fillRect(rect(), CUKE_THEME->getThemeColor(ThemeType::Window));

    QMainWindow::paintEvent(event);
}

void Window::showEvent(QShowEvent *event) {
    QMainWindow::showEvent(event);
    setDisplayMode(getDisplayMode());
    update();
}

void Window::onThemeChanged(ThemeType::ThemeMode mode) {
    Q_D(Window);
    setThemeMode(mode);
    setDisplayMode(getDisplayMode());
}

CUKE_NAMESPACE_END