#include <QPainter>
#include <QLayout>
#include <QMainWindow>

#include "CukeAppBar.h"

#include "CukeAppBarPrivate.h"
#include "CukeIcon.h"
#include "CukeLabel.h"
#include "CukeToolButton.h"

CUKE_NAMESPACE_BEGIN(pub)
    CUKE_Q_PROPERTY_IMPL(CukeAppBar, int, AppBarHeight)
CukeAppBar::CukeAppBar(QWidget *parent)
    : CukeContextMixin(parent),
      d_ptr(new CukeAppBarPrivate(this)) {
    _pAppBarHeight = 32;
    setFixedHeight(_pAppBarHeight);

    d_ptr->_layout = new QHBoxLayout(this);
    d_ptr->_layout->setContentsMargins(8, 0, 0, 0);
    d_ptr->_layout->setAlignment(Qt::AlignTop);

    // 图标
    d_ptr->_windowIcon = new QLabel(this);
    d_ptr->_windowIcon->setPixmap(parent->windowIcon().pixmap(18, 18));
    d_ptr->_layout->addWidget(d_ptr->_windowIcon);
    connect(parent, &QMainWindow::windowIconChanged, this, [this](const QIcon& icon) {
        d_ptr->_windowIcon->setPixmap(icon.pixmap(18, 18));
    });

    // 标题
    d_ptr->_windowTitle = new CukeLabel(this);
    d_ptr->_windowTitle->setText(parent->windowTitle());
    d_ptr->_layout->addWidget(d_ptr->_windowTitle);
    connect(parent, &QMainWindow::windowTitleChanged, this, [this](const QString& title) {
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
    d_ptr->_minimizeButton->setIcon(cIcon->getCukeIcon(CukeIconType::Subtract, cTheme->getThemeColor(_themeMode, CukeThemeType::Text)));
    d_ptr->_containerLayout->addWidget(d_ptr->_minimizeButton);

    // 最大化
    d_ptr->_maximizeButton = new CukeToolButton(this);
    d_ptr->_maximizeButton->setFixedSize(_pAppBarHeight, _pAppBarHeight);
    d_ptr->_maximizeButton->setIcon(cIcon->getCukeIcon(CukeIconType::Maximize, cTheme->getThemeColor(_themeMode, CukeThemeType::Text)));
    d_ptr->_containerLayout->addWidget(d_ptr->_maximizeButton);

    // 关闭
    d_ptr->_closeButton = new CukeToolButton(this);
    d_ptr->_closeButton->setFixedSize(_pAppBarHeight, _pAppBarHeight);
    d_ptr->_closeButton->setIcon(cIcon->getCukeIcon(CukeIconType::Dismiss, cTheme->getThemeColor(_themeMode, CukeThemeType::Text)));
    d_ptr->_containerLayout->addWidget(d_ptr->_closeButton);

    d_ptr->_layout->addWidget(d_ptr->_container);

}

CukeAppBar::~CukeAppBar() = default;

void CukeAppBar::onThemeChanged(const CukeThemeType::ThemeMode mode) {
    CukeContextMixin::onThemeChanged(mode);
    d_ptr->_minimizeButton->setIcon(cIcon->getCukeIcon(CukeIconType::Subtract, cTheme->getThemeColor(_themeMode, CukeThemeType::Text)));
    d_ptr->_maximizeButton->setIcon(cIcon->getCukeIcon(CukeIconType::Maximize, cTheme->getThemeColor(_themeMode, CukeThemeType::Text)));
    d_ptr->_closeButton->setIcon(cIcon->getCukeIcon(CukeIconType::Dismiss, cTheme->getThemeColor(_themeMode, CukeThemeType::Text)));
}

CUKE_NAMESPACE_END(pub)