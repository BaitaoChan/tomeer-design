#include <QGuiApplication>
#include <QStyleHints>

#include "CukeAppBarPrivate.h"
#include "CukeAppBar.h"
#include "CukeLabel.h"
#include "CukeAppBarButton.h"
#include "CukePainter.h"
#include "CukeIcon.h"

CUKE_NAMESPACE_BEGIN(pub)
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
    auto mode = CUKE_THEME->getThemeMode();

    if (mode == ThemeType::System)
        mode = QGuiApplication::styleHints()->colorScheme() == Qt::ColorScheme::Dark ? ThemeType::Dark : ThemeType::Light;
    CUKE_THEME->setThemeMode(mode == ThemeType::Dark ? ThemeType::Light : ThemeType::Dark);
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
        _maximizeButton->setIconType(IconType::SquareMultiple);
    else
        _maximizeButton->setIconType(IconType::Maximize);
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
        _maximizeButton->setIconType(IconType::SquareMultiple);
    else
        _maximizeButton->setIconType(IconType::Maximize);
}

CUKE_NAMESPACE_END(pub)