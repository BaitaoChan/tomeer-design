#include <QPainter>

#include "CukeIcon.h"
#include "CukePainter.h"
#include "CukePushButton.h"
#include "CukePushButtonPrivate.h"

CUKE_NAMESPACE_BEGIN()
CUKE_Q_PROPERTY_IMPL(PushButton, int, BorderRadius)
CUKE_Q_PROPERTY_IMPL(PushButton, ThemeType::ThemeMode, ThemeMode)
CUKE_Q_PROPERTY_IMPL(PushButton, GeometryType::SideFlag, SideFlag)
PushButton::PushButton(QWidget *parent)
    : QAbstractButton(parent),
      d_ptr(new PushButtonPrivate(this)) {
    setBorderRadius(4);
    setSideFlag(GeometryType::All);

    connect(this, &PushButton::pBorderRadiusChanged, this, QOverload<>::of(&PushButton::update));
    connect(this, &PushButton::pSideFlagChanged, this, QOverload<>::of(&PushButton::update));
    connect(CUKE_THEME, &Theme::themeModeChanged, this, &PushButton::onThemeChanged);
    connect(CUKE_THEME, &Theme::themeColorChanged, this, QOverload<>::of(&QWidget::update));
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
    setCukeIcon(icon);
}

PushButton::~PushButton() = default;

void PushButton::setCukeIcon(IconType::Icon pCukeIcon) {
    if (_pCukeIcon != pCukeIcon) {
        _pCukeIcon = pCukeIcon;
        pCukeIconChanged();
        setIcon(CUKE_ICON->getCukeIcon(_pCukeIcon));
    }
}

IconType::Icon PushButton::getCukeIcon() const {
    return _pCukeIcon;
}

void PushButton::paintEvent(QPaintEvent *event) {
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
        painter.setBrush(CUKE_THEME->getThemeColor(ThemeType::PushButtonHover));
    else
        painter.setBrush(CUKE_THEME->getThemeColor(ThemeType::PushButton));
    CUKE_PAINTER->drawRoundedRect(rect().adjusted(1, 1, -1, -1), &painter, getBorderRadius(), getBorderRadius(), getSideFlag());

    if (!isEnabled())
        painter.setPen(QPen(CUKE_THEME->getThemeColor(ThemeType::TextDisable), 1));
    else
        painter.setPen(QPen(CUKE_THEME->getThemeColor(ThemeType::Text), 1));

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

void PushButton::onThemeChanged(ThemeType::ThemeMode mode) {
    Q_D(PushButton);
    setThemeMode(mode);
    update();
}

CUKE_NAMESPACE_END