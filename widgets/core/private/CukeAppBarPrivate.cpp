#include "CukeAppBarPrivate.h"
#include "CukeAppBar.h"
#include "CukeLabel.h"
#include "CukeAppBarButton.h"
#include "CukePainter.h"
#include "CukeIcon.h"

CUKE_NAMESPACE_BEGIN(pub)
CukeAppBarPrivate::CukeAppBarPrivate(CukeAppBar *q)
    : QObject(q),
      q_ptr(q) {
}

CukeAppBarPrivate::~CukeAppBarPrivate() = default;

void CukeAppBarPrivate::onWindowIconChanged(const QIcon &icon) const {
    if (icon.isNull())
        return;
    if (!_windowIcon->isVisible())
        _windowIcon->setVisible(true);
    _windowIcon->setPixmap(icon.pixmap(18, 18));
}

void CukeAppBarPrivate::onWindowTitleChanged(const QString& title) const {
    if (title.isEmpty())
        return;
    if (!_windowTitle->isVisible())
        _windowTitle->setVisible(true);
    _windowTitle->setText(title);
}

void CukeAppBarPrivate::onThemeButtonClicked() {
    Q_Q(CukeAppBar);

    CUKE_THEME->setThemeMode(CUKE_THEME->getThemeMode() == CukeThemeType::Dark
                                 ? CukeThemeType::Light
                                 : CukeThemeType::Dark);
}

void CukeAppBarPrivate::onMinimizeButtonClicked() {
    Q_Q(CukeAppBar);
    if (!(q->window()->windowState() & Qt::WindowMinimized)) {
        q->window()->showMinimized();
    }
}

void CukeAppBarPrivate::onMaximizeButtonClicked() {
    Q_Q(CukeAppBar);

    if (q->window()->windowState() & Qt::WindowMaximized)
        q->window()->showNormal();
    else
        q->window()->showMaximized();

    if (q->window()->windowState() & Qt::WindowMaximized)
        _maximizeButton->setIconType(CukeIconType::SquareMultiple);
    else
        _maximizeButton->setIconType(CukeIconType::Maximize);
}

void CukeAppBarPrivate::onCloseButtonClicked() {
    Q_Q(CukeAppBar);
    q->window()->close();
}

void CukeAppBarPrivate::onHoverChanged() {
    Q_Q(CukeAppBar);
    _closeButton->update();
}

void CukeAppBarPrivate::onWindowStateChanged() {
    Q_Q(CukeAppBar);
    if (q->window()->windowState() & Qt::WindowMaximized)
        _maximizeButton->setIconType(CukeIconType::SquareMultiple);
    else
        _maximizeButton->setIconType(CukeIconType::Maximize);
}

CUKE_NAMESPACE_END(pub)