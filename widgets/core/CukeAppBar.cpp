#include <QPainter>
#include <QLayout>
#include <QMainWindow>
#include <QEvent>
#include <QWindow>

#include "CukeAppBar.h"
#include "CukeAppBarPrivate.h"
#include "CukeIcon.h"
#include "CukeLabel.h"
#include "CukeObjectMap.h"
#include "CukeAppBarButton.h"
#include "CukeToggleSwitch.h"
#include "CukeWindow.h"

CUKE_NAMESPACE_BEGIN(pub)
CUKE_Q_PROPERTY_IMPL(CukeAppBar, int, AppBarHeight)
CUKE_Q_PROPERTY_IMPL(CukeAppBar, CukeThemeType::ThemeMode, ThemeMode)
CukeAppBar::CukeAppBar(QWidget *parent)
    : QWidget(parent),
      d_ptr(new CukeAppBarPrivate(this)) {
    Q_D(CukeAppBar);
    _pAppBarHeight = 32;
    setFixedHeight(_pAppBarHeight);
    d->_objectMap = new CukeObjectMap(this);
    window()->setContentsMargins(0, height(), 0, 0);
    setGeometry(0, 0, window()->width(), height());
    window()->installEventFilter(this);

    d->_mainLayout = new QHBoxLayout(this);
    d->_mainLayout->setContentsMargins(8, 0, 0, 0);
    d->_mainLayout->setAlignment(Qt::AlignVCenter);

    // 图标
    d->_windowIcon = new QLabel(this);
    d->_windowIcon->setFixedSize(18, 18);
    d->_windowIcon->setScaledContents(true);
    if (!parent->windowIcon().isNull())
        d->_windowIcon->setPixmap(parent->windowIcon().pixmap(18, 18));
    else
        d->_windowIcon->setVisible(false);
    d->_mainLayout->addWidget(d->_windowIcon);
    d->_objectMap->add(CukeAppBarType::WindowIcon, d->_windowIcon);
    connect(parent, &QMainWindow::windowIconChanged, d, &CukeAppBarPrivate::onWindowIconChanged);

    // 标题
    d->_windowTitle = new CukeLabel(this);
    if (!parent->windowTitle().isEmpty())
        d->_windowTitle->setText(parent->windowTitle());
    else
        d->_windowTitle->setVisible(false);
    d->_mainLayout->addWidget(d->_windowTitle);
    d->_objectMap->add(CukeAppBarType::WindowTitle, d->_windowTitle);
    connect(parent, &QMainWindow::windowTitleChanged, d, &CukeAppBarPrivate::onWindowTitleChanged);

    // 自定义区域
    d->_widget = new QWidget(this);
    d->_layout = new QHBoxLayout(d->_widget);
    d->_layout->setContentsMargins(0, 0, 0, 0);
    d->_layout->setSpacing(0);
    d->_mainLayout->addWidget(d->_widget, Qt::AlignVCenter);

    d->_leftLayout = new QHBoxLayout;
    d->_middleLayout = new QHBoxLayout;
    d->_rightLayout = new QHBoxLayout;
    d->_layout->addLayout(d->_leftLayout);
    d->_layout->addStretch();
    d->_layout->addLayout(d->_middleLayout);
    d->_layout->addStretch();
    d->_layout->addLayout(d->_rightLayout);

    // 容器
    d->_container = new QWidget(this);
    d->_containerLayout = new QHBoxLayout(d->_container);
    d->_containerLayout->setContentsMargins(0, 0, 0, 0);
    d->_containerLayout->setSpacing(0);
    d->_containerLayout->setSizeConstraint(QLayout::SetFixedSize);
    d->_container->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    d->_container->setFixedWidth(d->_containerLayout->sizeHint().width());

    // 主题切换
    d->_themeButton = new CukeAppBarButton(this);
    d->_themeButton->setFixedSize(_pAppBarHeight, _pAppBarHeight);
    d->_themeButton->setIcon(CUKE_ICON->getCukeIcon(getThemeMode() ? CukeIconType::WeatherSunny : CukeIconType::WeatherMoon, CUKE_THEME->getThemeColor(getThemeMode(), CukeThemeType::Text)));
    d->_containerLayout->addWidget(d->_themeButton);
    d->_objectMap->add(CukeAppBarType::ThemeButton, d->_themeButton);
    connect(d->_themeButton, &CukeAppBarButton::clicked, d, &CukeAppBarPrivate::onThemeButtonClicked);

    // 最小化
    d->_minimizeButton = new CukeAppBarButton(this);
    d->_minimizeButton->setFixedSize(_pAppBarHeight, _pAppBarHeight);
    d->_minimizeButton->setIcon(CUKE_ICON->getCukeIcon(CukeIconType::Subtract, CUKE_THEME->getThemeColor(getThemeMode(), CukeThemeType::Text)));
    d->_containerLayout->addWidget(d->_minimizeButton);
    d->_objectMap->add(CukeAppBarType::MinimizeButton, d->_minimizeButton);
    connect(d->_minimizeButton, &CukeAppBarButton::clicked, d, &CukeAppBarPrivate::onMinimizeButtonClicked);

    // 最大化
    d->_maximizeButton = new CukeAppBarButton(this);
    d->_maximizeButton->setFixedSize(_pAppBarHeight, _pAppBarHeight);
    d->_maximizeButton->setIcon(CUKE_ICON->getCukeIcon(CukeIconType::Maximize, CUKE_THEME->getThemeColor(getThemeMode(), CukeThemeType::Text)));
    d->_containerLayout->addWidget(d->_maximizeButton);
    d->_objectMap->add(CukeAppBarType::MaximizeButton, d->_maximizeButton);
    connect(d->_maximizeButton, &CukeAppBarButton::clicked, d, &CukeAppBarPrivate::onMaximizeButtonClicked);

    // 关闭
    d->_closeButton = new CukeAppBarButton(this);
    if (qobject_cast<CukeWindow *>(window())) {
        d->_closeButton->setBorderRadius(qobject_cast<CukeWindow *>(window())->getBorderRadius());
    }
    d->_closeButton->setSideFlag(CukeGeometryType::None);
    d->_closeButton->bgColorFrom(CUKE_THEME->getThemeColor(getThemeMode(), CukeThemeType::Transparent));
    d->_closeButton->bgColorTo(CUKE_THEME->getThemeColor(getThemeMode(), CukeThemeType::Dismiss));
    d->_closeButton->setBgColorUsedFlag(true);
    d->_closeButton->setFixedSize(_pAppBarHeight, _pAppBarHeight);
    d->_closeButton->setIcon(CUKE_ICON->getCukeIcon(CukeIconType::Dismiss, CUKE_THEME->getThemeColor(getThemeMode(), CukeThemeType::Text)));
    d->_containerLayout->addWidget(d->_closeButton);
    d->_objectMap->add(CukeAppBarType::CloseButton, d->_closeButton);
    connect(d->_closeButton, &CukeAppBarButton::pHoverChanged, d, &CukeAppBarPrivate::onHoverChanged);
    connect(d->_closeButton, &CukeAppBarButton::clicked, d, &CukeAppBarPrivate::onCloseButtonClicked);
    connect(CUKE_THEME, &CukeTheme::themeModeChanged, this, &CukeAppBar::onThemeChanged);
    d->_mainLayout->addWidget(d->_container);
}

CukeAppBar::~CukeAppBar() = default;

void CukeAppBar::addCustomWidget(QWidget *widget, CukeAppBarType::CustomArea customArea) {
    Q_D(CukeAppBar);
    if (customArea == CukeAppBarType::LeftArea) {
        d->_leftLayout->addWidget(widget);
        d->_objectMap->add(CukeAppBarType::LeftWidget, widget);
    } else if (customArea == CukeAppBarType::MiddleArea) {
        d->_middleLayout->addWidget(widget);
        d->_objectMap->add(CukeAppBarType::MiddleWidget, widget);
    } else if (customArea == CukeAppBarType::RightArea) {
        d->_rightLayout->addWidget(widget);
        d->_objectMap->add(CukeAppBarType::RightWidget, widget);
    }
}

void *CukeAppBar::object(int key) {
    Q_D(CukeAppBar);
    return d->_objectMap->object(key);
}

QList<void *> CukeAppBar::objects() {
    Q_D(CukeAppBar);
    return d->_objectMap->objects();
}

void CukeAppBar::onThemeChanged(const CukeThemeType::ThemeMode mode) {
    Q_D(CukeAppBar);
    setThemeMode(mode);
    update();
    d->_themeButton->setIcon(CUKE_ICON->getCukeIcon(getThemeMode() ? CukeIconType::WeatherSunny : CukeIconType::WeatherMoon, CUKE_THEME->getThemeColor(getThemeMode(), CukeThemeType::Text)));
    d->_minimizeButton->setIcon(CUKE_ICON->getCukeIcon(CukeIconType::Subtract, CUKE_THEME->getThemeColor(getThemeMode(), CukeThemeType::Text)));
    d->_maximizeButton->setIcon(CUKE_ICON->getCukeIcon(CukeIconType::Maximize, CUKE_THEME->getThemeColor(getThemeMode(), CukeThemeType::Text)));
    d->_closeButton->setIcon(CUKE_ICON->getCukeIcon(CukeIconType::Dismiss, CUKE_THEME->getThemeColor(getThemeMode(), CukeThemeType::Text)));
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

void CukeAppBar::showEvent(QShowEvent *event) {
    Q_D(CukeAppBar);
    QWidget::showEvent(event);
    if (window()->windowHandle())
        connect(window()->windowHandle(), &QWindow::windowStateChanged, d, &CukeAppBarPrivate::onWindowStateChanged, Qt::UniqueConnection);
}

CUKE_NAMESPACE_END(pub)