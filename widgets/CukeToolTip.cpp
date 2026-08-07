#include <QHBoxLayout>
#include <QPainter>

#include "CukeToolTip.h"
#include "CukeLabel.h"
#include "CukeToolTipPrivate.h"
#include "CukeTheme.h"

CUKE_NAMESPACE_BEGIN()
CUKE_Q_PROPERTY_IMPL(ToolTip, QString, ToolTip)
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

    connect(this, &ToolTip::pToolTipChanged, this, [this, d] {
        d->_label->setText(getToolTip());
        adjustSize();
    });
    connect(CUKE_THEME, &Theme::themeModeChanged, this, QOverload<>::of(&QWidget::update));
    connect(CUKE_THEME, &Theme::themeColorChanged, this, QOverload<>::of(&QWidget::update));
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

    const bool textChanged = toolTip->getToolTip() != text;
    if (textChanged)
        toolTip->setToolTip(text);

    const QPoint tPos = pos + QPoint(4, 16);

    if (textChanged || !toolTip->isVisible())
        toolTip->move(tPos);

    if (!toolTip->isVisible())
        toolTip->show();
}

void ToolTip::hideText() {
    if (ToolTipPrivate::_toolTip)
        ToolTipPrivate::_toolTip->hide();
}

void ToolTip::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(CUKE_THEME->getThemeColor(ThemeType::BorderAlpha));
    painter.setBrush(CUKE_THEME->getThemeColor(ThemeType::Window));
    painter.drawRoundedRect(QRectF(rect()).adjusted(1, 1, -1, -1), 4, 4);
}

CUKE_NAMESPACE_END