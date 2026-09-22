#include <QPainter>

#include "icon.h"
#include "painter.h"
#include "push_button.h"
#include "push_button_private.h"

TOMEER_NAMESPACE_BEGIN()
TOMEER_Q_PROPERTY_IMPL(PushButton, int, BorderRadius)
TOMEER_Q_PROPERTY_IMPL(PushButton, ThemeType::ThemeMode, ThemeMode)
TOMEER_Q_PROPERTY_IMPL(PushButton, GeometryType::SideFlag, SideFlag)
PushButton::PushButton(QWidget *parent)
    : QAbstractButton(parent),
      d_ptr(new PushButtonPrivate(this)) {
    setBorderRadius(4);
    setSideFlag(GeometryType::All);

    connect(this, &PushButton::pBorderRadiusChanged, this, QOverload<>::of(&PushButton::update));
    connect(this, &PushButton::pSideFlagChanged, this, QOverload<>::of(&PushButton::update));
    connect(TOMEER_THEME, &Theme::themeModeChanged, this, &PushButton::onThemeChanged);
    connect(TOMEER_THEME, &Theme::themeColorChanged, this, QOverload<>::of(&QWidget::update));
}

PushButton::PushButton(const QString &text, QWidget *parent)
    : PushButton(parent) {
    setText(text);
}

PushButton::PushButton(const QIcon &icon, const QString &text, QWidget *parent)
    : PushButton(text, parent) {
    setIcon(icon);
}

PushButton::PushButton(const IconType::Icon &icon, const QString &text, QWidget *parent)
    : PushButton(text, parent) {
    setIcon(icon);
}

PushButton::~PushButton() = default;

void PushButton::setIcon(IconType::Icon pIcon) {
    if (_pIcon != pIcon) {
        _pIcon = pIcon;
        pIconChanged();
        setIcon(TOMEER_ICON->getIcon(_pIcon));
    }
}

IconType::Icon PushButton::getIcon() const {
    return _pIcon;
}

void PushButton::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);

    painter.setPen(QPen(TOMEER_THEME->getThemeColor(ThemeType::BorderAlpha), 1));
    if (!isEnabled())
        painter.setBrush(TOMEER_THEME->getThemeColor(ThemeType::Disable));
    else if (isDown() && !isChecked())
        painter.setBrush(TOMEER_THEME->getThemeColor(ThemeType::Press));
    else if (isChecked())
        painter.setBrush(TOMEER_THEME->getThemeColor(ThemeType::Check));
    else if (underMouse())
        painter.setBrush(TOMEER_THEME->getThemeColor(ThemeType::ButtonHover));
    else
        painter.setBrush(TOMEER_THEME->getThemeColor(ThemeType::Button));
    TOMEER_PAINTER->drawRoundedRect(rect().adjusted(1, 1, -1, -1), &painter, getBorderRadius(), getBorderRadius(), getSideFlag());

    if (!isEnabled())
        painter.setPen(QPen(TOMEER_THEME->getThemeColor(ThemeType::TextDisable), 1));
    else
        painter.setPen(QPen(TOMEER_THEME->getThemeColor(ThemeType::Text), 1));

    constexpr int spacing = 4;
    if (icon().isNull()) {
        painter.drawText(rect(), Qt::AlignCenter, text());
    } else if (text().isEmpty()) {
        QRect iRect(rect().center() - QPoint(iconSize().width() / 2, iconSize().height() / 2), iconSize());
        if (getIcon() != IconType::None) {
            QFont font("tomeer");
            font.setPixelSize(iconSize().height());
            painter.setFont(font);
            painter.drawText(iRect, Qt::AlignCenter, QString(QChar(getIcon())));
        } else
            icon().paint(&painter, iRect, Qt::AlignCenter);
    } else {
        QSize tSize = QFontMetrics(painter.font()).size(Qt::TextSingleLine, text()), iSize = iconSize();
        QRect lRect(rect().center().x() - (iSize.width() + spacing + tSize.width()) / 2,
                    rect().center().y() - tSize.height() / 2,
                    iSize.width() + spacing + tSize.width(), tSize.height());
        QRect iRect(lRect.left(), lRect.center().y() - iSize.height() / 2, iSize.width(), iSize.height());
        QRect tRect(iRect.right() + spacing, lRect.top(), tSize.width(), lRect.height());
        if (getIcon() != IconType::None) {
            painter.save();
            QFont font("tomeer");
            font.setPixelSize(iconSize().height());
            painter.setFont(font);
            painter.drawText(iRect, Qt::AlignCenter, QString(QChar(getIcon())));
            painter.restore();
        } else
            icon().paint(&painter, iRect, Qt::AlignCenter);
        painter.drawText(tRect, Qt::AlignVCenter | Qt::AlignLeft, text());
    }
}

void PushButton::onThemeChanged(ThemeType::ThemeMode mode) {
    Q_D(PushButton);
    setThemeMode(mode);
    update();
}

TOMEER_NAMESPACE_END
