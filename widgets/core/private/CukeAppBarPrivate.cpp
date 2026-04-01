#include "CukeAppBarPrivate.h"
#include "CukeAppBar.h"
#include "CukeLabel.h"
#include "CukeToolButton.h"
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
        cTheme->setThemeMode(CukeThemeType::Light);
    else
        cTheme->setThemeMode(CukeThemeType::Dark);
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
        _maximizeButton->setIcon(cIcon->getCukeIcon(CukeIconType::Maximize, cTheme->getThemeColor(q->getThemeMode(), CukeThemeType::Text)));
    } else {
        q->window()->showMaximized();
        _maximizeButton->setIcon(cIcon->getCukeIcon(CukeIconType::SquareMultiple, cTheme->getThemeColor(q->getThemeMode(), CukeThemeType::Text)));
    }
}

void CukeAppBarPrivate::onCloseButtonClicked() {
    Q_Q(CukeAppBar);
    q->window()->close();
}

void CukeAppBarPrivate::onHoverChanged() {
    Q_Q(CukeAppBar);
    if (cTheme->getThemeMode() == CukeThemeType::Dark)
        return;
    if (cTheme->getThemeMode() == CukeThemeType::Light) {
        if (_closeButton->getHover())
            _closeButton->setIcon(cIcon->getCukeIcon(CukeIconType::Dismiss,
                                                     cTheme->getThemeColor(
                                                         CukeThemeType::Dark, CukeThemeType::Text)));
        else
            _closeButton->setIcon(cIcon->getCukeIcon(CukeIconType::Dismiss,
                                                     cTheme->getThemeColor(
                                                         q->getThemeMode(), CukeThemeType::Text)));
    }
}

CUKE_NAMESPACE_END(pub)