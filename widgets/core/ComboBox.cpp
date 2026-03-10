#include "ComboBox.h"
#include "SingleArrow.h"
#include "ComboBoxStyle.h"
#include "ComboBoxItemDelegate.h"
#include "ComboBoxView.h"
#include "ComboBoxPrivate.h"

#define CUKE_COMBOBOX_POPUP_ANIM_MODE 0
CUKE_BEGIN_NAMESPACE(widget)
CUKE_Q_PROPERTY_IMPL(ComboBox, int, RotateAngle)
CUKE_Q_PROPERTY_IMPL(ComboBox, int, LineHalfWidth)
CUKE_Q_PROPERTY_IMPL(ComboBox, int, BorderRadius)
CUKE_Q_PROPERTY_IMPL(ComboBox, int, PopupHeight)

ComboBox::ComboBox(QWidget *parent)
    : ContextMixin(parent),
      _pBorderRadius(6),
      d_ptr(new ComboBoxPrivate(this)) {
    setStyleSheet(R"(
        QComboBox::drop-down { border: none; background: transparent; }
        QComboBox QAbstractItemView { background: transparent; border: none; }
    )");
    const auto view = new ComboBoxView(this);
    view->setItemDelegate(new ComboBoxItemDelegate(view));
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setView(view);
    setStyle(new ComboBoxStyle(style()));
    view->setSelectionMode(QAbstractItemView::SingleSelection);
    d_ptr->_rotateAnim = new QPropertyAnimation(this, "_pRotateAngle", this);
    d_ptr->_rotateAnim->setDuration(300);
    d_ptr->_rotateAnim->setEasingCurve(QEasingCurve::InOutSine);

    d_ptr->_lineAnim = new QPropertyAnimation(this, "_pLineHalfWidth", this);
    d_ptr->_lineAnim->setDuration(300);
    d_ptr->_lineAnim->setEasingCurve(QEasingCurve::InOutCubic);

    d_ptr->_heightAnim = new QPropertyAnimation(this, "_pPopupHeight", this);
    d_ptr->_heightAnim->setDuration(300);
    d_ptr->_heightAnim->setEasingCurve(QEasingCurve::InOutCubic);

    connect(this, &ComboBox::pBorderRadiusChanged, this, QOverload<>::of(&QWidget::update));
    connect(d_ptr->_rotateAnim, &QPropertyAnimation::valueChanged, this, QOverload<>::of(&QWidget::update));
    connect(d_ptr->_lineAnim, &QPropertyAnimation::valueChanged, this, QOverload<>::of(&QWidget::update));

    setMaxVisibleItems(4);
}

ComboBox::~ComboBox() = default;

void ComboBox::showPopup() {
    // 禁用原生绘制
    qApp->setEffectEnabled(Qt::UI_AnimateCombo, false);
    QComboBox::showPopup();
    qApp->setEffectEnabled(Qt::UI_AnimateCombo, qApp->isEffectEnabled(Qt::UI_AnimateCombo));
    QWidget* container = this->findChild<QFrame*>();
    if (count() == 0 || !container)
        return;

#if CUKE_COMBOBOX_POPUP_ANIM_MODE == 1
    container->setFixedHeight(1);
    auto *heightAnim = new QPropertyAnimation(container, "maximumHeight", this);
    heightAnim->setStartValue(1);
    heightAnim->setEndValue(qMin(count(), maxVisibleItems()) * 30 + 8);
    heightAnim->setDuration(350);
    heightAnim->setEasingCurve(QEasingCurve::OutCubic);
    connect(heightAnim, &QPropertyAnimation::valueChanged, this,
            [=](const QVariant &h) {
                container->setFixedHeight(h.toInt());
            });
    heightAnim->start(QAbstractAnimation::DeleteWhenStopped);

#else

    auto *effect = new QGraphicsOpacityEffect(view());
    view()->setGraphicsEffect(effect);
    auto *opacityAnim = new QPropertyAnimation(effect, "opacity");
    opacityAnim->setStartValue(0);
    opacityAnim->setEndValue(1);
    opacityAnim->setDuration(350);
    opacityAnim->start(QAbstractAnimation::DeleteWhenStopped);
#endif

    // 箭头向上
    d_ptr->_rotateAnim->stop();
    d_ptr->_rotateAnim->setStartValue(_pRotateAngle);
    d_ptr->_rotateAnim->setEndValue(-180);
    d_ptr->_rotateAnim->start();

    // 焦点展开
    d_ptr->_lineAnim->stop();
    d_ptr->_lineAnim->setStartValue(0);
    d_ptr->_lineAnim->setEndValue((rect().right() - rect().left() - 8) / 2.0);
    d_ptr->_lineAnim->start();
}

void ComboBox::hidePopup() {
    QWidget *container = this->findChild<QFrame *>();
    if (!container)
        return;

#if CUKE_COMBOBOX_POPUP_ANIM_MODE == 1
    auto *heightAnim = new QPropertyAnimation(container, "maximumHeight", this);
    heightAnim->setStartValue(container->height());
    heightAnim->setEndValue(1);
    heightAnim->setDuration(350);
    heightAnim->setEasingCurve(QEasingCurve::InCubic);

    connect(heightAnim, &QPropertyAnimation::valueChanged, this,
            [=](const QVariant &h) {
                container->setFixedHeight(h.toInt());
            });

    connect(heightAnim, &QPropertyAnimation::finished, this, [=]() {
        QComboBox::hidePopup();
    });

    heightAnim->start(QAbstractAnimation::DeleteWhenStopped);

#else
    auto *effect =
            qobject_cast<QGraphicsOpacityEffect *>(view()->graphicsEffect());
    if (!effect) {
        QComboBox::hidePopup();
        return;
    }
    auto *opacityAnim = new QPropertyAnimation(effect, "opacity", this);
    opacityAnim->setStartValue(effect->opacity());
    opacityAnim->setEndValue(0);
    opacityAnim->setDuration(350);
    connect(opacityAnim, &QPropertyAnimation::finished, this, [=]() {
        effect->deleteLater();
        QComboBox::hidePopup();
    });
    opacityAnim->start(QAbstractAnimation::DeleteWhenStopped);

#endif
    // 箭头向下
    d_ptr->_rotateAnim->stop();
    d_ptr->_rotateAnim->setStartValue(_pRotateAngle);
    d_ptr->_rotateAnim->setEndValue(0);
    d_ptr->_rotateAnim->start();

    // 焦点收起
    d_ptr->_lineAnim->stop();
    d_ptr->_lineAnim->setStartValue(_pLineHalfWidth);
    d_ptr->_lineAnim->setEndValue(0);
    d_ptr->_lineAnim->start();
}

void ComboBox::paintEvent(QPaintEvent *event) {
    QComboBox::paintEvent(event);

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    // 底部横线
    p.setPen(Qt::NoPen);
    p.setBrush(pThemeColor(_themeMode, ThemeType::Pattern));
    p.drawRect(QRectF(rect().left() + 4,
                      rect().bottom() * 0.82,
                      rect().right() - rect().left() - 8,
                      2));

    // 焦点指示
    p.setPen(Qt::NoPen);
    p.setBrush(pThemeColor(_themeMode, ThemeType::Check));
    p.drawRoundedRect(QRectF(rect().left() + 4 + (rect().right() - rect().left() - 8) / 2.0 - _pLineHalfWidth,
                             rect().bottom() * 0.82,
                             _pLineHalfWidth * 2,
                             3),
                      2,
                      2);

    // 箭头
    p.translate(QRectF(rect().right() - 20,
                       rect().center().y() - rect().height() / 4.0,
                       rect().height() / 2.0,
                       rect().height() / 2.0).center());
    p.rotate(_pRotateAngle);
    p.translate(-rect().height() / 4.0, -rect().height() / 4.0);
    p.setTransform(QTransform().scale(rect().height() / 2.0 / 1024.0,
                                      rect().height() / 2.0 / 1024.0), true);
    p.setBrush(pThemeColor(_themeMode, Text));
    p.setPen(QPen(pThemeColor(_themeMode, Text), 1));
    p.drawPath(SingleArrow());
}

CUKE_END_NAMESPACE(widget)