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
    if (q->getThemeMode())
        CUKE_THEME->setThemeMode(CukeThemeType::Light);
    else
        CUKE_THEME->setThemeMode(CukeThemeType::Dark);
}

void CukeAppBarPrivate::onMinimizeButtonClicked() {
    Q_Q(CukeAppBar);
    if (!(q->window()->windowState() & Qt::WindowMinimized)) {
        q->window()->showMinimized();
    }
}

void CukeAppBarPrivate::onMaximizeButtonClicked() {
    Q_Q(CukeAppBar);
    if (q->window()->windowState() & Qt::WindowMaximized) {
        q->window()->showNormal();
        _maximizeButton->setIcon(CUKE_ICON->getCukeIcon(CukeIconType::Maximize, CUKE_THEME->getThemeColor(q->getThemeMode(), CukeThemeType::Text)));
    } else {
        q->window()->showMaximized();
        _maximizeButton->setIcon(CUKE_ICON->getCukeIcon(CukeIconType::SquareMultiple, CUKE_THEME->getThemeColor(q->getThemeMode(), CukeThemeType::Text)));
    }
}

void CukeAppBarPrivate::onCloseButtonClicked() {
    Q_Q(CukeAppBar);
    q->window()->close();
}

void CukeAppBarPrivate::onHoverChanged() {
    Q_Q(CukeAppBar);
    if (CUKE_THEME->getThemeMode() == CukeThemeType::Dark)
        return;
    if (CUKE_THEME->getThemeMode() == CukeThemeType::Light) {
        if (_closeButton->getHover())
            _closeButton->setIcon(CUKE_ICON->getCukeIcon(CukeIconType::Dismiss,
                                                     CUKE_THEME->getThemeColor(
                                                         CukeThemeType::Dark, CukeThemeType::Text)));
        else
            _closeButton->setIcon(CUKE_ICON->getCukeIcon(CukeIconType::Dismiss,
                                                     CUKE_THEME->getThemeColor(
                                                         q->getThemeMode(), CukeThemeType::Text)));
    }
}

void CukeAppBarPrivate::onWindowStateChanged() {
    Q_Q(CukeAppBar);
    if (q->window()->windowState() & Qt::WindowMaximized)
        _maximizeButton->setIcon(CUKE_ICON->getCukeIcon(CukeIconType::Maximize,
                                                    CUKE_THEME->getThemeColor(q->getThemeMode(), CukeThemeType::Text)));
    else
        _maximizeButton->setIcon(CUKE_ICON->getCukeIcon(CukeIconType::SquareMultiple,
                                                    CUKE_THEME->getThemeColor(q->getThemeMode(), CukeThemeType::Text)));
}

CUKE_NAMESPACE_END(pub)