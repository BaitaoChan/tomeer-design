#include <QPainter>
#include <QLayout>
#include <QMainWindow>

#include "CukeAppBar.h"

#include "CukeAppBarPrivate.h"
#include "CukeIcon.h"
#include "CukeLabel.h"

CUKE_NAMESPACE_BEGIN(widget)
    CUKE_Q_PROPERTY_IMPL(CukeAppBar, int, AppBarHeight)
CukeAppBar::CukeAppBar(QWidget *parent)
    : CukeContextMixin(parent),
      d_ptr(new CukeAppBarPrivate(this)) {
    _pAppBarHeight = 32;
    setFixedHeight(_pAppBarHeight);

    d_ptr->_layout = new QHBoxLayout(this);
    d_ptr->_layout->setContentsMargins(5, 2, 5, 0);
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

}

CukeAppBar::~CukeAppBar() = default;

CUKE_NAMESPACE_END(widget)