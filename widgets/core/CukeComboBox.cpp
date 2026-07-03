#include <QPainterPath>

#include "CukeComboBox.h"
#include "CukeComboBoxStyle.h"
#include "CukeComboBoxItemDelegate.h"
#include "CukeComboBoxView.h"
#include "CukeComboBoxPrivate.h"

#define CUKE_COMBOBOX_POPUP_ANIM_MODE 1
CUKE_NAMESPACE_BEGIN(pub)
CUKE_Q_PROPERTY_IMPL(CukeComboBox, int, RotateAngle)
CUKE_Q_PROPERTY_IMPL(CukeComboBox, int, LineHalfWidth)
CUKE_Q_PROPERTY_IMPL(CukeComboBox, int, BorderRadius)
CUKE_Q_PROPERTY_IMPL(CukeComboBox, int, PopupHeight)
CUKE_Q_PROPERTY_IMPL(CukeComboBox, CukeThemeType::ThemeMode, ThemeMode)
CUKE_NAMESPACE_END(pub)
inline QPainterPath SingleArrow() {
    QPainterPath path;

    path.moveTo(992, 288);
    path.cubicTo(984.6, 288, 977.1, 290.6, 971.1, 295.8);
    path.lineTo(554.1, 655.6);
    path.cubicTo(530.1, 676.6, 493.8, 676.6, 469.8, 655.6);
    path.lineTo(469.7, 655.5);
    path.lineTo(52.9, 295.6);
    path.cubicTo(39.5, 284, 19.3, 285.5, 7.8, 299);
    path.cubicTo(-3.8, 312.4, -2.3, 332.6, 11.1, 344.1);
    path.lineTo(427.8, 704.7);
    path.cubicTo(451.1, 725.1, 481, 736.3, 512, 736.3);
    path.cubicTo(543, 736.3, 573.9, 725.1, 597.2, 704.7);
    path.lineTo(1012.9, 344);
    path.cubicTo(1026.3, 332.4, 1027.7, 312.2, 1016.3, 299);
    path.cubicTo(1010, 291.6, 1001.1, 287.8, 992, 287.8);

    return path;
}

CUKE_NAMESPACE_BEGIN(pub)

CukeComboBox::CukeComboBox(QWidget *parent)
    : QComboBox(parent),
      _pBorderRadius(6),
      d_ptr(new CukeComboBoxPrivate(this)) {
    Q_D(CukeComboBox);
    setStyleSheet(R"(
        QComboBox::drop-down { border: none; background: transparent; }
        QComboBox QAbstractItemView { background: transparent; border: none; }
    )");
    const auto view = new CukeComboBoxView(this);
    view->setItemDelegate(new CukeComboBoxItemDelegate(view));
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setView(view);
    setStyle(new CukeComboBoxStyle(style()));
    view->setSelectionMode(QAbstractItemView::SingleSelection);
    d->_rotateAnim = new QPropertyAnimation(this, "_pRotateAngle", this);
    d->_rotateAnim->setDuration(300);
    d->_rotateAnim->setEasingCurve(QEasingCurve::InOutSine);

    d->_lineAnim = new QPropertyAnimation(this, "_pLineHalfWidth", this);
    d->_lineAnim->setDuration(300);
    d->_lineAnim->setEasingCurve(QEasingCurve::InOutCubic);

    d->_heightAnim = new QPropertyAnimation(this, "_pPopupHeight", this);
    d->_heightAnim->setDuration(300);
    d->_heightAnim->setEasingCurve(QEasingCurve::InOutCubic);

    connect(this, &CukeComboBox::pBorderRadiusChanged, this, QOverload<>::of(&QWidget::update));
    connect(d->_rotateAnim, &QPropertyAnimation::valueChanged, this, QOverload<>::of(&QWidget::update));
    connect(d->_lineAnim, &QPropertyAnimation::valueChanged, this, QOverload<>::of(&QWidget::update));
    connect(CUKE_THEME, &CukeTheme::themeModeChanged, this, &CukeComboBox::onThemeChanged);

    setMaxVisibleItems(4);
}

CukeComboBox::~CukeComboBox() = default;

void CukeComboBox::showPopup() {
    Q_D(CukeComboBox);
    // 禁用原生绘制
    qApp->setEffectEnabled(Qt::UI_AnimateCombo, false);
    QComboBox::showPopup();
    qApp->setEffectEnabled(Qt::UI_AnimateCombo, qApp->isEffectEnabled(Qt::UI_AnimateCombo));
    QWidget *container = this->findChild<QFrame *>();
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
    d->_rotateAnim->stop();
    d->_rotateAnim->setStartValue(_pRotateAngle);
    d->_rotateAnim->setEndValue(-180);
    d->_rotateAnim->start();

    // 焦点展开
    d->_lineAnim->stop();
    d->_lineAnim->setStartValue(0);
    d->_lineAnim->setEndValue((rect().right() - rect().left() - 8) / 2.0);
    d->_lineAnim->start();
}

void CukeComboBox::hidePopup() {
    Q_D(CukeComboBox);
    QWidget *container = this->findChild<QFrame *>();
    if (!container)
        return;

#if CUKE_COMBOBOX_POPUP_ANIM_MODE == 1
    auto *heightAnim = new QPropertyAnimation(container, "maximumHeight", this);
    heightAnim->setStartValue(container->height());
    heightAnim->setEndValue(1);
    heightAnim->setDuration(350);
    heightAnim->setEasingCurve(QEasingCurve::OutCubic);

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
    d->_rotateAnim->stop();
    d->_rotateAnim->setStartValue(_pRotateAngle);
    d->_rotateAnim->setEndValue(0);
    d->_rotateAnim->start();

    // 焦点收起
    d->_lineAnim->stop();
    d->_lineAnim->setStartValue(_pLineHalfWidth);
    d->_lineAnim->setEndValue(0);
    d->_lineAnim->start();
}

void CukeComboBox::paintEvent(QPaintEvent *event) {
    Q_D(CukeComboBox);
    QComboBox::paintEvent(event);

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    // 底部横线
    p.setPen(Qt::NoPen);
    p.setBrush(CUKE_THEME->getThemeColor(getThemeMode(), CukeThemeType::Pattern));
    p.drawRoundedRect(QRectF(rect().left() + 4,
                             rect().bottom() * 0.9,
                             rect().right() - rect().left() - 8,
                             2),
                      2,
                      2);

    // 焦点指示
    p.setPen(Qt::NoPen);
    p.setBrush(CUKE_THEME->getThemeColor(getThemeMode(), CukeThemeType::Check));
    p.drawRoundedRect(QRectF(rect().left() + 4 + (rect().right() - rect().left() - 8) / 2.0 - _pLineHalfWidth,
                             rect().bottom() * 0.9,
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
    p.setBrush(CUKE_THEME->getThemeColor(getThemeMode(), CukeThemeType::Text));
    p.setPen(QPen(CUKE_THEME->getThemeColor(getThemeMode(), CukeThemeType::Text), 1));
    p.drawPath(SingleArrow());
}

void CukeComboBox::onThemeChanged(CukeThemeType::ThemeMode mode) {
    Q_D(CukeComboBox);
    setThemeMode(mode);
    update();
}

CUKE_NAMESPACE_END(pub)