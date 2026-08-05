#include "CukeAppBarPrivate.h"
#include "CukeAppBar.h"
#include "CukeLabel.h"
#include "CukeAppBarButton.h"
#include "CukePainter.h"
#include "CukeIcon.h"

CUKE_NAMESPACE_BEGIN()
AppBarPrivate::AppBarPrivate(AppBar *q)
    : QObject(q),
      q_ptr(q) {
}

AppBarPrivate::~AppBarPrivate() = default;

void AppBarPrivate::onWindowIconChanged(const QIcon &icon) const {
    if (icon.isNull())
        return;
    if (!_windowIcon->isVisible())
        _windowIcon->setVisible(true);
    _windowIcon->setPixmap(icon.pixmap(18, 18));
}

void AppBarPrivate::onWindowTitleChanged(const QString& title) const {
    if (title.isEmpty())
        return;
    if (!_windowTitle->isVisible())
        _windowTitle->setVisible(true);
    _windowTitle->setText(title);
}

void AppBarPrivate::onThemeButtonClicked() {
    if (_themeButton->getCukeIcon() == IconType::WeatherMoon)
        CUKE_THEME->setThemeMode(ThemeType::Dark);
    else
        CUKE_THEME->setThemeMode(ThemeType::Light);
    CUKE_THEME->setThemeMode(ThemeType::System);
}

void AppBarPrivate::onMinimizeButtonClicked() {
    Q_Q(AppBar);
    if (!(q->window()->windowState() & Qt::WindowMinimized)) {
        q->window()->showMinimized();
    }
}

void AppBarPrivate::onMaximizeButtonClicked() {
    Q_Q(AppBar);

    if (q->window()->windowState() & Qt::WindowMaximized)
        q->window()->showNormal();
    else
        q->window()->showMaximized();

    if (q->window()->windowState() & Qt::WindowMaximized)
        _maximizeButton->setCukeIcon(IconType::SquareMultiple);
    else
        _maximizeButton->setCukeIcon(IconType::Maximize);
}

void AppBarPrivate::onCloseButtonClicked() {
    Q_Q(AppBar);
    q->window()->close();
}

void AppBarPrivate::onHoverChanged() {
    Q_Q(AppBar);
    _closeButton->update();
}

void AppBarPrivate::onWindowStateChanged() {
    Q_Q(AppBar);
    if (q->window()->windowState() & Qt::WindowMaximized)
        _maximizeButton->setCukeIcon(IconType::SquareMultiple);
    else
        _maximizeButton->setCukeIcon(IconType::Maximize);
}

CUKE_NAMESPACE_END