#include <QPainter>
#include <QLayout>
#include <QMainWindow>
#include <QEvent>
#include <QWindow>
#include <QStyleHints>

#include "app_bar.h"
#include "app_bar_private.h"
#include "icon.h"
#include "label.h"
#include "widget_register.h"
#include "app_bar_button.h"
#include "toggle_switch.h"
#include "window.h"

TOMEER_NAMESPACE_BEGIN()
TOMEER_Q_PROPERTY_IMPL(AppBar, int, AppBarHeight)
TOMEER_Q_PROPERTY_IMPL(AppBar, ThemeType::ThemeMode, ThemeMode)
AppBar::AppBar(QWidget *parent)
    : QWidget(parent),
      d_ptr(new AppBarPrivate(this)) {
    Q_D(AppBar);
    _pAppBarHeight = 32;
    setFixedHeight(_pAppBarHeight);
    d->_widgetRegister = new WidgetRegister(this);
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
    d->_widgetRegister->add(AppBarType::WindowIcon, d->_windowIcon);
    connect(parent, &QMainWindow::windowIconChanged, d, &AppBarPrivate::onWindowIconChanged);

    // 标题
    d->_windowTitle = new Label(this);
    if (!parent->windowTitle().isEmpty())
        d->_windowTitle->setText(parent->windowTitle());
    else
        d->_windowTitle->setVisible(false);
    d->_mainLayout->addWidget(d->_windowTitle);
    d->_widgetRegister->add(AppBarType::WindowTitle, d->_windowTitle);
    connect(parent, &QMainWindow::windowTitleChanged, d, &AppBarPrivate::onWindowTitleChanged);

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
    d->_themeButton = new AppBarButton(this);
    d->_themeButton->setFixedSize(_pAppBarHeight, _pAppBarHeight);
    d->_themeButton->setIcon(getThemeMode() ? IconType::WeatherSunny : IconType::WeatherMoon);
    d->_containerLayout->addWidget(d->_themeButton);
    d->_widgetRegister->add(AppBarType::ThemeButton, d->_themeButton);
    connect(d->_themeButton, &AppBarButton::clicked, d, &AppBarPrivate::onThemeButtonClicked);

    // 最小化
    d->_minimizeButton = new AppBarButton(this);
    d->_minimizeButton->setFixedSize(_pAppBarHeight, _pAppBarHeight);
    d->_minimizeButton->setIcon(IconType::Subtract);
    d->_containerLayout->addWidget(d->_minimizeButton);
    d->_widgetRegister->add(AppBarType::MinimizeButton, d->_minimizeButton);
    connect(d->_minimizeButton, &AppBarButton::clicked, d, &AppBarPrivate::onMinimizeButtonClicked);

    // 最大化
    d->_maximizeButton = new AppBarButton(this);
    d->_maximizeButton->setFixedSize(_pAppBarHeight, _pAppBarHeight);
    d->_maximizeButton->setIcon(IconType::Maximize);
    d->_containerLayout->addWidget(d->_maximizeButton);
    d->_widgetRegister->add(AppBarType::MaximizeButton, d->_maximizeButton);
    connect(d->_maximizeButton, &AppBarButton::clicked, d, &AppBarPrivate::onMaximizeButtonClicked);

    // 关闭
    d->_closeButton = new AppBarButton(this);
    if (qobject_cast<Window *>(window())) {
        d->_closeButton->setBorderRadius(qobject_cast<Window *>(window())->getBorderRadius());
    }
    d->_closeButton->setSideFlag(GeometryType::None);
    d->_closeButton->bgColorFrom(TOMEER_THEME->getThemeColor(ThemeType::Transparent));
    d->_closeButton->bgColorTo(TOMEER_THEME->getThemeColor(ThemeType::Dismiss));
    d->_closeButton->setBgColorUsedFlag(true);
    d->_closeButton->setFixedSize(_pAppBarHeight, _pAppBarHeight);
    d->_closeButton->setIcon(IconType::Dismiss);
    d->_containerLayout->addWidget(d->_closeButton);
    d->_widgetRegister->add(AppBarType::CloseButton, d->_closeButton);
    connect(d->_closeButton, &AppBarButton::pHoverChanged, d, &AppBarPrivate::onHoverChanged);
    connect(d->_closeButton, &AppBarButton::clicked, d, &AppBarPrivate::onCloseButtonClicked);
    connect(TOMEER_THEME, &Theme::themeModeChanged, this, &AppBar::onThemeChanged);
    connect(TOMEER_THEME, &Theme::themeColorChanged, this, QOverload<>::of(&QWidget::update));
    d->_mainLayout->addWidget(d->_container);
}

AppBar::~AppBar() = default;

void AppBar::addCustomWidget(QWidget *widget, AppBarType::CustomArea customArea) {
    Q_D(AppBar);
    if (customArea == AppBarType::LeftArea) {
        d->_leftLayout->addWidget(widget);
        d->_widgetRegister->add(AppBarType::LeftWidget, widget);
    } else if (customArea == AppBarType::MiddleArea) {
        d->_middleLayout->addWidget(widget);
        d->_widgetRegister->add(AppBarType::MiddleWidget, widget);
    } else if (customArea == AppBarType::RightArea) {
        d->_rightLayout->addWidget(widget);
        d->_widgetRegister->add(AppBarType::RightWidget, widget);
    }
}

void *AppBar::object(int key) {
    Q_D(AppBar);
    return d->_widgetRegister->object(key);
}

QList<void *> AppBar::objects() {
    Q_D(AppBar);
    return d->_widgetRegister->objects();
}

void AppBar::onThemeChanged(ThemeType::ThemeMode mode) {
    Q_D(AppBar);
    setThemeMode(mode);
    if (mode == ThemeType::System) {
        if (QGuiApplication::styleHints()->colorScheme() == Qt::ColorScheme::Dark)
            mode = ThemeType::Dark;
        else
            mode = ThemeType::Light;
    }

    if (mode == ThemeType::Light)
        d->_themeButton->setIcon(IconType::WeatherMoon);
    else if (mode == ThemeType::Dark)
        d->_themeButton->setIcon(IconType::WeatherSunny);
    update();
}

bool AppBar::eventFilter(QObject *watched, QEvent *event) {
    if (watched == window()) {
        if (event->type() == QEvent::Resize)
            if (const auto window = qobject_cast<QWidget *>(watched)) {
                setGeometry(0, 0, window->width(), height());
            }
    }
    return QWidget::eventFilter(watched, event);
}

void AppBar::showEvent(QShowEvent *event) {
    Q_D(AppBar);
    QWidget::showEvent(event);
    if (window()->windowHandle())
        connect(window()->windowHandle(), &QWindow::windowStateChanged, d, &AppBarPrivate::onWindowStateChanged, Qt::UniqueConnection);
}

TOMEER_NAMESPACE_END