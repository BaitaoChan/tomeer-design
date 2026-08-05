#include <QPainter>

#include "CukeIcon.h"
#include "CukePainter.h"
#include "CukeToggleButton.h"
#include "CukeToggleButtonPrivate.h"

CUKE_NAMESPACE_BEGIN()
CUKE_Q_PROPERTY_IMPL(ToggleButton, int, BorderRadius)
CUKE_Q_PROPERTY_IMPL(ToggleButton, ThemeType::ThemeMode, ThemeMode)
CUKE_Q_PROPERTY_IMPL(ToggleButton, GeometryType::SideFlag, SideFlag)

ToggleButton::ToggleButton(QWidget *parent)
    : QAbstractButton(parent),
      d_ptr(new ToggleButtonPrivate(this)) {
    setBorderRadius(4);
    setSideFlag(GeometryType::All);
    setCheckable(true);

    connect(this, &ToggleButton::pBorderRadiusChanged, this, QOverload<>::of(&ToggleButton::update));
    connect(this, &ToggleButton::pSideFlagChanged, this, QOverload<>::of(&ToggleButton::update));
    connect(CUKE_THEME, &Theme::themeModeChanged, this, &ToggleButton::onThemeChanged);
    connect(CUKE_THEME, &Theme::themeColorChanged, this, QOverload<>::of(&QWidget::update));
}

ToggleButton::ToggleButton(const QString &text, QWidget *parent)
    : ToggleButton(parent) {
    setText(text);
}

ToggleButton::ToggleButton(const QIcon &icon, const QString &text, QWidget *parent)
    : ToggleButton(text, parent) {
    setIcon(icon);
}

ToggleButton::ToggleButton(const IconType::Icon &icon, const QString &text, QWidget *parent)
    : ToggleButton(text, parent) {
    setCukeIcon(icon);
}

ToggleButton::~ToggleButton() = default;

void ToggleButton::setCukeIcon(IconType::Icon pCukeIcon) {
    if (_pCukeIcon != pCukeIcon) {
        _pCukeIcon = pCukeIcon;
        pCukeIconChanged();
        setIcon(CUKE_ICON->getCukeIcon(_pCukeIcon));
    }
}

IconType::Icon ToggleButton::getCukeIcon() const {
    return _pCukeIcon;
}

void ToggleButton::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);

    painter.setPen(QPen(CUKE_THEME->getThemeColor(ThemeType::BorderAlpha), 1));
    if (!isEnabled())
        painter.setBrush(CUKE_THEME->getThemeColor(ThemeType::Disable));
    else if (isDown() && !isChecked())
        painter.setBrush(CUKE_THEME->getThemeColor(ThemeType::Press));
    else if (isChecked())
        painter.setBrush(CUKE_THEME->getThemeColor(ThemeType::Check));
    else if (underMouse())
        painter.setBrush(CUKE_THEME->getThemeColor(ThemeType::ButtonHover));
    else
        painter.setBrush(CUKE_THEME->getThemeColor(ThemeType::Button));
    CUKE_PAINTER->drawRoundedRect(rect().adjusted(1, 1, -1, -1), &painter, getBorderRadius(), getBorderRadius(), getSideFlag());

    if (!isEnabled())
        painter.setPen(QPen(CUKE_THEME->getThemeColor(ThemeType::TextDisable), 1));
    else {
        if (isChecked())
            painter.setPen(QPen(CUKE_THEME->getThemeColor(ThemeType::Dark, ThemeType::Text), 1));
        else
            painter.setPen(QPen(CUKE_THEME->getThemeColor(ThemeType::Text), 1));
    }

    constexpr int spacing = 4;
    if (icon().isNull()) {
        painter.drawText(rect(), Qt::AlignCenter, text());
    } else if (text().isEmpty()) {
        QRect iRect(rect().center() - QPoint(iconSize().width() / 2, iconSize().height() / 2), iconSize());
        if (getCukeIcon() != IconType::None) {
            QFont font("Cuke");
            font.setPixelSize(iconSize().height());
            painter.setFont(font);
            painter.drawText(iRect, Qt::AlignCenter, QString(QChar(getCukeIcon())));
        } else
            icon().paint(&painter, iRect, Qt::AlignCenter);
    } else {
        QSize tSize = QFontMetrics(painter.font()).size(Qt::TextSingleLine, text()), iSize = iconSize();
        QRect lRect(rect().center().x() - (iSize.width() + spacing + tSize.width()) / 2,
                    rect().center().y() - tSize.height() / 2,
                    iSize.width() + spacing + tSize.width(), tSize.height());
        QRect iRect(lRect.left(), lRect.center().y() - iSize.height() / 2, iSize.width(), iSize.height());
        QRect tRect(iRect.right() + spacing, lRect.top(), tSize.width(), lRect.height());
        if (getCukeIcon() != IconType::None) {
            painter.save();
            QFont font("Cuke");
            font.setPixelSize(iconSize().height());
            painter.setFont(font);
            painter.drawText(iRect, Qt::AlignCenter, QString(QChar(getCukeIcon())));
            painter.restore();
        } else
            icon().paint(&painter, iRect, Qt::AlignCenter);
        painter.drawText(tRect, Qt::AlignVCenter | Qt::AlignLeft, text());
    }
}

void ToggleButton::onThemeChanged(ThemeType::ThemeMode mode) {
    setThemeMode(mode);
    update();
}

CUKE_NAMESPACE_END