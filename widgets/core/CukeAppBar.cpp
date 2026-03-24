#include <QPainter>
#include <QLayout>
#include <QMainWindow>

#include "CukeAppBar.h"
#include "CukeAppBarPrivate.h"
#include "CukeIcon.h"
#include "CukeLabel.h"
#include "CukeToolButton.h"
#include "CukeWindow.h"

CUKE_NAMESPACE_BEGIN(pub)
CUKE_Q_PROPERTY_IMPL(CukeAppBar, int, AppBarHeight)
CukeAppBar::CukeAppBar(QWidget *parent)
    : QWidget(parent),
      CukeContext(this),
      d_ptr(new CukeAppBarPrivate(this)) {
    _pAppBarHeight = 32;
    setFixedHeight(_pAppBarHeight);

    d_ptr->_layout = new QHBoxLayout(this);
    d_ptr->_layout->setContentsMargins(8, 0, 0, 0);
    d_ptr->_layout->setAlignment(Qt::AlignTop);

    // 图标
    d_ptr->_windowIcon = new QLabel(this);
    if (!parent->windowIcon().isNull())
        d_ptr->_windowIcon->setPixmap(parent->windowIcon().pixmap(18, 18));
    else
        d_ptr->_windowIcon->setVisible(false);
    d_ptr->_layout->addWidget(d_ptr->_windowIcon);
    connect(parent, &QMainWindow::windowIconChanged, this, [this](const QIcon &icon) {
        if (icon.isNull())
            return;
        if (!d_ptr->_windowIcon->isVisible())
            d_ptr->_windowIcon->setVisible(true);
        d_ptr->_windowIcon->setPixmap(icon.pixmap(18, 18));
    });

    // 标题
    d_ptr->_windowTitle = new CukeLabel(this);
    if (!parent->windowTitle().isEmpty())
        d_ptr->_windowTitle->setText(parent->windowTitle());
    else
        d_ptr->_windowTitle->setVisible(false);
    d_ptr->_layout->addWidget(d_ptr->_windowTitle);
    connect(parent, &QMainWindow::windowTitleChanged, this, [this](const QString& title) {
        if (title.isEmpty())
            return;
        if (!d_ptr->_windowTitle->isVisible())
            d_ptr->_windowTitle->setVisible(true);
        d_ptr->_windowTitle->setText(title);
    });

    d_ptr->_layout->addStretch();

    d_ptr->_container = new QWidget(this);
    d_ptr->_containerLayout = new QHBoxLayout(d_ptr->_container);
    d_ptr->_containerLayout->setContentsMargins(0, 0, 0, 0);
    d_ptr->_containerLayout->setSpacing(0);

    // 最小化
    d_ptr->_minimizeButton = new CukeToolButton(this);
    d_ptr->_minimizeButton->setFixedSize(_pAppBarHeight, _pAppBarHeight);
    d_ptr->_minimizeButton->setIcon(cIcon->getCukeIcon(CukeIconType::Subtract, cTheme->getThemeColor(getThemeMode(), CukeThemeType::Text)));
    d_ptr->_containerLayout->addWidget(d_ptr->_minimizeButton);
    connect(d_ptr->_minimizeButton, &CukeToolButton::clicked, this, [this]() {
        if (!(window()->windowState() & Qt::WindowMinimized)) {
            window()->showMinimized();
        }
    });

    // 最大化
    d_ptr->_maximizeButton = new CukeToolButton(this);
    d_ptr->_maximizeButton->setFixedSize(_pAppBarHeight, _pAppBarHeight);
    d_ptr->_maximizeButton->setIcon(cIcon->getCukeIcon(CukeIconType::Maximize, cTheme->getThemeColor(getThemeMode(), CukeThemeType::Text)));
    d_ptr->_containerLayout->addWidget(d_ptr->_maximizeButton);
    connect(d_ptr->_maximizeButton, &CukeToolButton::clicked, this, [this]() {
        if (window()->windowState() & Qt::WindowMaximized) {
            window()->showNormal();
            d_ptr->_maximizeButton->setIcon(cIcon->getCukeIcon(CukeIconType::Maximize, cTheme->getThemeColor(getThemeMode(), CukeThemeType::Text)));
        } else {
            window()->showMaximized();
            d_ptr->_maximizeButton->setIcon(cIcon->getCukeIcon(CukeIconType::SquareMultiple, cTheme->getThemeColor(getThemeMode(), CukeThemeType::Text)));
        }
    });

    // 关闭
    d_ptr->_closeButton = new CukeToolButton(this);
    if (auto w = qobject_cast<CukeWindow *>(window())) {
        d_ptr->_closeButton->setBorderRadius(qobject_cast<CukeWindow *>(window())->getBorderRadius());
    }
    d_ptr->_closeButton->setSideFlag(CukeGeometryType::TopRight);
    d_ptr->_closeButton->bgColorFrom(cTheme->getThemeColor(getThemeMode(), CukeThemeType::Transparent));
    d_ptr->_closeButton->bgColorTo(cTheme->getThemeColor(getThemeMode(), CukeThemeType::Dismiss));
    d_ptr->_closeButton->setBgColorUsedFlag(true);
    d_ptr->_closeButton->setFixedSize(_pAppBarHeight, _pAppBarHeight);
    d_ptr->_closeButton->setIcon(cIcon->getCukeIcon(CukeIconType::Dismiss, cTheme->getThemeColor(getThemeMode(), CukeThemeType::Text)));
    d_ptr->_containerLayout->addWidget(d_ptr->_closeButton);
    connect(d_ptr->_closeButton, &CukeToolButton::pHoverChanged, this, [this]() {
        if (cTheme->getThemeMode() == CukeThemeType::Dark)
            return;
        if (cTheme->getThemeMode() == CukeThemeType::Light) {
            if (d_ptr->_closeButton->getHover())
                d_ptr->_closeButton->setIcon(cIcon->getCukeIcon(CukeIconType::Dismiss,
                                                                cTheme->getThemeColor(
                                                                    CukeThemeType::Dark, CukeThemeType::Text)));
            else
                d_ptr->_closeButton->setIcon(cIcon->getCukeIcon(CukeIconType::Dismiss,
                                                                cTheme->getThemeColor(
                                                                    getThemeMode(), CukeThemeType::Text)));
        }
    });
    connect(d_ptr->_closeButton, &CukeToolButton::clicked, this, [this]() {
        window()->close();
    });
    d_ptr->_layout->addWidget(d_ptr->_container);
    connect(cTheme, &CukeTheme::themeModeChanged, this, onThemeChanged);
}

CukeAppBar::~CukeAppBar() = default;

void CukeAppBar::onThemeChanged(const CukeThemeType::ThemeMode mode) {
    CukeContext::onThemeChanged(mode);
    d_ptr->_minimizeButton->setIcon(cIcon->getCukeIcon(CukeIconType::Subtract, cTheme->getThemeColor(getThemeMode(), CukeThemeType::Text)));
    d_ptr->_maximizeButton->setIcon(cIcon->getCukeIcon(CukeIconType::Maximize, cTheme->getThemeColor(getThemeMode(), CukeThemeType::Text)));
    d_ptr->_closeButton->setIcon(cIcon->getCukeIcon(CukeIconType::Dismiss, cTheme->getThemeColor(getThemeMode(), CukeThemeType::Text)));
}

CUKE_NAMESPACE_END(pub)