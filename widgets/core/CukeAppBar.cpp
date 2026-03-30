#include <QPainter>
#include <QLayout>
#include <QMainWindow>
#include <QEvent>

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
      CukeScope(this),
      d_ptr(new CukeAppBarPrivate(this)) {
    Q_D(CukeAppBar);
    _pAppBarHeight = 32;
    setFixedHeight(_pAppBarHeight);
    window()->setContentsMargins(0, height(), 0, 0);
    setGeometry(0, 0, window()->width(), height());
    window()->installEventFilter(this);

    d->_layout = new QHBoxLayout(this);
    d->_layout->setContentsMargins(8, 0, 0, 0);
    d->_layout->setAlignment(Qt::AlignVCenter);

    // 图标
    d->_windowIcon = new QLabel(this);
    if (!parent->windowIcon().isNull())
        d->_windowIcon->setPixmap(parent->windowIcon().pixmap(18, 18));
    else
        d->_windowIcon->setVisible(false);
    d->_layout->addWidget(d->_windowIcon);
    addElem(CukeElemType::WindowIcon, d->_windowIcon);
    connect(parent, &QMainWindow::windowIconChanged, d, &CukeAppBarPrivate::onWindowIconChanged);

    // 标题
    d->_windowTitle = new CukeLabel(this);
    if (!parent->windowTitle().isEmpty())
        d->_windowTitle->setText(parent->windowTitle());
    else
        d->_windowTitle->setVisible(false);
    d->_layout->addWidget(d->_windowTitle);
    addElem(CukeElemType::WindowTitle, d->_windowTitle);
    connect(parent, &QMainWindow::windowTitleChanged, d, &CukeAppBarPrivate::onWindowTitleChanged);

    d->_layout->addStretch();

    d->_container = new QWidget(this);
    d->_containerLayout = new QHBoxLayout(d->_container);
    d->_containerLayout->setContentsMargins(0, 0, 0, 0);
    d->_containerLayout->setSpacing(0);
    d->_containerLayout->setSizeConstraint(QLayout::SetFixedSize);
    d->_container->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    d->_container->setFixedWidth(d->_containerLayout->sizeHint().width());

    // 最小化
    d->_minimizeButton = new CukeToolButton(this);
    d->_minimizeButton->setFixedSize(_pAppBarHeight, _pAppBarHeight);
    d->_minimizeButton->setIcon(cIcon->getCukeIcon(CukeIconType::Subtract, cTheme->getThemeColor(getThemeMode(), CukeThemeType::Text)));
    d->_containerLayout->addWidget(d->_minimizeButton);
    addElem(CukeElemType::MinimizeButton, d->_minimizeButton);
    connect(d->_minimizeButton, &CukeToolButton::clicked, d, &CukeAppBarPrivate::onMinimizeButtonClicked);

    // 最大化
    d->_maximizeButton = new CukeToolButton(this);
    d->_maximizeButton->setFixedSize(_pAppBarHeight, _pAppBarHeight);
    d->_maximizeButton->setIcon(cIcon->getCukeIcon(CukeIconType::Maximize, cTheme->getThemeColor(getThemeMode(), CukeThemeType::Text)));
    d->_containerLayout->addWidget(d->_maximizeButton);
    addElem(CukeElemType::MaximizeButton, d->_maximizeButton);
    connect(d->_maximizeButton, &CukeToolButton::clicked, d, &CukeAppBarPrivate::onMaximizeButtonClicked);

    // 关闭
    d->_closeButton = new CukeToolButton(this);
    if (qobject_cast<CukeWindow *>(window())) {
        d->_closeButton->setBorderRadius(qobject_cast<CukeWindow *>(window())->getBorderRadius());
    }
    d->_closeButton->setSideFlag(CukeGeometryType::None);
    d->_closeButton->bgColorFrom(cTheme->getThemeColor(getThemeMode(), CukeThemeType::Transparent));
    d->_closeButton->bgColorTo(cTheme->getThemeColor(getThemeMode(), CukeThemeType::Dismiss));
    d->_closeButton->setBgColorUsedFlag(true);
    d->_closeButton->setFixedSize(_pAppBarHeight, _pAppBarHeight);
    d->_closeButton->setIcon(cIcon->getCukeIcon(CukeIconType::Dismiss, cTheme->getThemeColor(getThemeMode(), CukeThemeType::Text)));
    d->_containerLayout->addWidget(d->_closeButton);
    addElem(CukeElemType::CloseButton, d->_closeButton);
    connect(d->_closeButton, &CukeToolButton::pHoverChanged, d, &CukeAppBarPrivate::onHoverChanged);
    connect(d->_closeButton, &CukeToolButton::clicked, d, &CukeAppBarPrivate::onCloseButtonClicked);
    d->_layout->addWidget(d->_container);
}

CukeAppBar::~CukeAppBar() = default;

void CukeAppBar::onThemeChanged(const CukeThemeType::ThemeMode mode) {
    Q_D(CukeAppBar);
    CukeScope::onThemeChanged(mode);
    d->_minimizeButton->setIcon(cIcon->getCukeIcon(CukeIconType::Subtract, cTheme->getThemeColor(getThemeMode(), CukeThemeType::Text)));
    d->_maximizeButton->setIcon(cIcon->getCukeIcon(CukeIconType::Maximize, cTheme->getThemeColor(getThemeMode(), CukeThemeType::Text)));
    d->_closeButton->setIcon(cIcon->getCukeIcon(CukeIconType::Dismiss, cTheme->getThemeColor(getThemeMode(), CukeThemeType::Text)));
}

bool CukeAppBar::eventFilter(QObject *watched, QEvent *event) {
    if (watched == window()) {
        if (event->type() == QEvent::Resize)
            if (const auto window = qobject_cast<QWidget *>(watched)) {
                setGeometry(0, 0, window->width(), height());
            }
    }
    return QWidget::eventFilter(watched, event);
}

CUKE_NAMESPACE_END(pub)