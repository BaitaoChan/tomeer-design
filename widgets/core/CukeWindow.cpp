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
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")
#endif

CUKE_NAMESPACE_BEGIN(pub)
CUKE_Q_PROPERTY_IMPL(CukeWindow, int, BorderRadius)
CukeWindow::CukeWindow(QWidget *parent)
    : QMainWindow(parent),
      CukeContext(this),
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
#ifdef Q_OS_WIN
    auto msg = static_cast<MSG *>(message);
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

    painter.fillPath(path, cTheme->getThemeColor(_themeMode, CukeThemeType::Window));

    QMainWindow::paintEvent(event);
}

CUKE_NAMESPACE_END(pub)