#include <QHBoxLayout>
#include <QPainter>

#include "CukeSettingsCard.h"
#include "CukeLabel.h"
#include "CukeTheme.h"

CUKE_NAMESPACE_BEGIN(pub)
CUKE_Q_PROPERTY_IMPL(SettingsCard, QString, Header)
SettingsCard::SettingsCard(QWidget *parent)
    : QWidget(parent) {
    const auto layout = new QHBoxLayout(this);
    const auto label = new Label(this);
    layout->setContentsMargins(16, 8, 16, 8);
    layout->setSpacing(12);
    layout->addWidget(label);
    layout->addStretch();

    setMinimumHeight(68);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    setAttribute(Qt::WA_TranslucentBackground);

    connect(this, &SettingsCard::pHeaderChanged, label, [this, label] {
        label->setText(getHeader());
    });
    connect(CUKE_THEME, &Theme::themeModeChanged, this, QOverload<>::of(&QWidget::update));
    connect(CUKE_THEME, &Theme::themeColorChanged, this, QOverload<>::of(&QWidget::update));
}

SettingsCard::SettingsCard(const QString &header, QWidget *content, QWidget *parent)
    : SettingsCard(parent) {
    setHeader(header);
    setContent(content);
}

void SettingsCard::setContent(QWidget *pContent) {
    if (_pContent == pContent)
        return;
    if (_pContent) {
        layout()->removeWidget(_pContent);
        _pContent->setParent(nullptr);
    }
    _pContent = pContent;
    if (_pContent) {
        layout()->addWidget(_pContent);
        layout()->setAlignment(_pContent, Qt::AlignRight | Qt::AlignVCenter);
    }
    emit pContentChanged();
}

QWidget *SettingsCard::getContent() const {
    return _pContent;
}

void SettingsCard::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event)
    QColor borderColor = CUKE_THEME->getThemeColor(ThemeType::Text);
    borderColor.setAlpha(20);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(borderColor);
    painter.setBrush(CUKE_THEME->getThemeColor(ThemeType::PanelAlpha));
    painter.drawRoundedRect(QRectF(rect()).adjusted(0.5, 0.5, -0.5, -0.5), 6, 6);
}
CUKE_NAMESPACE_END(pub)