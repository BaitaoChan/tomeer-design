#include <QHBoxLayout>
#include <QPainter>
#include <QPropertyAnimation>

#include "tool_tip.h"
#include "label.h"
#include "tool_tip_private.h"
#include "theme.h"

TOMEER_NAMESPACE_BEGIN()
TOMEER_Q_PROPERTY_IMPL(ToolTip, QString, ToolTip)
ToolTip::ToolTip(QWidget *parent)
    : QWidget(parent, Qt::ToolTip | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint),
      d_ptr(new ToolTipPrivate(this)) {
    Q_D(ToolTip);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_ShowWithoutActivating);
    setAttribute(Qt::WA_TransparentForMouseEvents);

    d->_layout = new QHBoxLayout(this);
    d->_label = new Label(this);
    d->_layout->setContentsMargins(8, 4, 8, 4);
    d->_layout->addWidget(d->_label, 0, Qt::AlignVCenter);

    d->_opacityAnimation = new QPropertyAnimation(this, "windowOpacity", this);
    d->_opacityAnimation->setDuration(100);
    d->_opacityAnimation->setEasingCurve(QEasingCurve::InOutSine);

    connect(this, &ToolTip::pToolTipChanged, this, [this, d] {
        d->_label->setText(getToolTip());
        adjustSize();
    });
    connect(d->_opacityAnimation, &QPropertyAnimation::finished, this, [this, d] {
        if (d->_opacityAnimation->endValue().toReal() == 0.0) {
            hide();
            setWindowOpacity(1.0);
        }
    });
    connect(TOMEER_THEME, &Theme::themeModeChanged, this, QOverload<>::of(&QWidget::update));
    connect(TOMEER_THEME, &Theme::themeColorChanged, this, QOverload<>::of(&QWidget::update));
}

ToolTip::~ToolTip() {
    if (ToolTipPrivate::_toolTip == this)
        ToolTipPrivate::_toolTip = nullptr;
}

void ToolTip::showText(const QPoint &pos, const QString &text, QWidget *widget) {
    Q_UNUSED(widget)
    if (text.isEmpty()) {
        hideText();
        return;
    }
    if (!ToolTipPrivate::_toolTip)
        ToolTipPrivate::_toolTip = new ToolTip();
    ToolTip *toolTip = ToolTipPrivate::_toolTip;
    const auto *const d = toolTip->d_func();

    const bool textChanged = toolTip->getToolTip() != text;
    if (textChanged)
        toolTip->setToolTip(text);

    const QPoint tPos = pos + QPoint(4, 16);

    if (textChanged || !toolTip->isVisible())
        toolTip->move(tPos);

    if (!toolTip->isVisible()) {
        d->_opacityAnimation->stop();
        toolTip->setWindowOpacity(0.0);
        toolTip->show();
        d->_opacityAnimation->setStartValue(0.0);
        d->_opacityAnimation->setEndValue(1.0);
        d->_opacityAnimation->start();
    } else if (d->_opacityAnimation->state() == QAbstractAnimation::Running &&
               d->_opacityAnimation->endValue().toReal() == 0.0) {
        d->_opacityAnimation->stop();
        d->_opacityAnimation->setStartValue(toolTip->windowOpacity());
        d->_opacityAnimation->setEndValue(1.0);
        d->_opacityAnimation->start();
    }
}

void ToolTip::hideText() {
    ToolTip *toolTip = ToolTipPrivate::_toolTip;
    if (!toolTip || !toolTip->isVisible())
        return;

    auto *const d = toolTip->d_func();
    if (d->_opacityAnimation->state() == QAbstractAnimation::Running &&
        d->_opacityAnimation->endValue().toReal() == 0.0)
        return;

    d->_opacityAnimation->stop();
    d->_opacityAnimation->setStartValue(toolTip->windowOpacity());
    d->_opacityAnimation->setEndValue(0.0);
    d->_opacityAnimation->start();
}

void ToolTip::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(TOMEER_THEME->getThemeColor(ThemeType::BorderAlpha));
    painter.setBrush(TOMEER_THEME->getThemeColor(ThemeType::ToolTip));
    painter.drawRoundedRect(QRectF(rect()).adjusted(1, 1, -1, -1), 4, 4);
}

TOMEER_NAMESPACE_END