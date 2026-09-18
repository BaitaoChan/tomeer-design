#include <QLabel>
#include <QPainterPath>
#include <QRegion>

#include "combo_box.h"
#include "combo_box_style.h"
#include "combo_box_item_delegate.h"
#include "combo_box_view.h"
#include "combo_box_private.h"

#define TOMEER_COMBOBOX_POPUP_ANIM_MODE 3
TOMEER_NAMESPACE_BEGIN()
TOMEER_Q_PROPERTY_IMPL(ComboBox, int, RotateAngle)
TOMEER_Q_PROPERTY_IMPL(ComboBox, int, PopupHeight)
TOMEER_Q_PROPERTY_IMPL(ComboBox, int, BorderRadius)
TOMEER_Q_PROPERTY_IMPL(ComboBox, int, LineHalfWidth)
TOMEER_Q_PROPERTY_IMPL(ComboBox, ThemeType::ThemeMode, ThemeMode)
ComboBox::ComboBox(QWidget *parent)
    : QComboBox(parent),
      _pBorderRadius(6),
      d_ptr(new ComboBoxPrivate(this)) {
    Q_D(ComboBox);
    setStyleSheet(R"(
        QComboBox::drop-down { border: none; background: transparent; }
        QComboBox QAbstractItemView { background: transparent; border: none; }
    )");
    d->_view = new ComboBoxView(this);
    d->_view->setItemDelegate(new ComboBoxItemDelegate(d->_view));
    d->_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    d->_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setView(d->_view);
    setStyle(new ComboBoxStyle(style()));
    d->_view->setSelectionMode(QAbstractItemView::SingleSelection);
    d->_rotateAnim = new QPropertyAnimation(this, "_pRotateAngle", this);
    d->_rotateAnim->setDuration(300);
    d->_rotateAnim->setEasingCurve(QEasingCurve::InOutSine);

    d->_lineAnim = new QPropertyAnimation(this, "_pLineHalfWidth", this);
    d->_lineAnim->setDuration(300);
    d->_lineAnim->setEasingCurve(QEasingCurve::InOutSine);

    d->_heightAnim = new QPropertyAnimation(this, "_pPopupHeight", this);
    d->_heightAnim->setDuration(300);
    d->_heightAnim->setEasingCurve(QEasingCurve::InOutSine);

    connect(this, &ComboBox::pBorderRadiusChanged, this, QOverload<>::of(&QWidget::update));
    connect(d->_rotateAnim, &QPropertyAnimation::valueChanged, this, QOverload<>::of(&QWidget::update));
    connect(d->_lineAnim, &QPropertyAnimation::valueChanged, this, QOverload<>::of(&QWidget::update));
    connect(TOMEER_THEME, &Theme::themeModeChanged, this, &ComboBox::onThemeChanged);
    connect(TOMEER_THEME, &Theme::themeColorChanged, this, QOverload<>::of(&QWidget::update));

    setMaxVisibleItems(4);
}

ComboBox::~ComboBox() = default;

void ComboBox::showPopup() {
    Q_D(ComboBox);
    if (d->getIsPopup())
        return;
    d->setIsPopup(true);
    // 禁用原生绘制
    qApp->setEffectEnabled(Qt::UI_AnimateCombo, false);
    QComboBox::showPopup();
    qApp->setEffectEnabled(Qt::UI_AnimateCombo, qApp->isEffectEnabled(Qt::UI_AnimateCombo));
    QWidget *container = view()->window();
    if (count() == 0 || !container)
        return;
    container->setMinimumWidth(width() + 6 * 2);
    container->move(container->pos().x() - 6, container->pos().y());

#if TOMEER_COMBOBOX_POPUP_ANIM_MODE == 1
    container->setFixedHeight(1);
    auto heightAnim = new QPropertyAnimation(container, "maximumHeight", this);
    heightAnim->setStartValue(1);
    heightAnim->setEndValue(qMin(count(), maxVisibleItems()) * 30 + 8);
    heightAnim->setDuration(350);
    heightAnim->setEasingCurve(QEasingCurve::InOutSine);
    connect(heightAnim, &QPropertyAnimation::valueChanged, this, [=](const QVariant &h) {
        container->setFixedHeight(h.toInt());
    });
    connect(heightAnim, &QPropertyAnimation::finished, this, [=]() {
        d->setIsPopup(false);
    });
    heightAnim->start(QAbstractAnimation::DeleteWhenStopped);

#elif TOMEER_COMBOBOX_POPUP_ANIM_MODE == 2
    container->setWindowOpacity(0);
    auto opacityAnim = new QPropertyAnimation(container, "windowOpacity", this);
    opacityAnim->setStartValue(0);
    opacityAnim->setEndValue(1);
    opacityAnim->setDuration(350);
    connect(opacityAnim, &QPropertyAnimation::finished, this, [=]() {
        d->setIsPopup(false);
    });
    opacityAnim->start(QAbstractAnimation::DeleteWhenStopped);

#elif TOMEER_COMBOBOX_POPUP_ANIM_MODE == 3
    const int popupHeight = qMin(count(), maxVisibleItems()) * 30 + 8;
    const QRect viewRect = view()->geometry();

    auto slideView = new QLabel(container);
    slideView->setPixmap(view()->grab());
    slideView->setGeometry(viewRect);
    slideView->setAttribute(Qt::WA_TransparentForMouseEvents);
    slideView->show();
    slideView->raise();

    view()->hide();

    container->setFixedHeight(1);
    slideView->move(viewRect.topLeft() - QPoint(0, popupHeight - 1));

    auto heightAnim = new QPropertyAnimation(container, "maximumHeight", this);
    heightAnim->setStartValue(1);
    heightAnim->setEndValue(popupHeight);
    heightAnim->setDuration(350);
    heightAnim->setEasingCurve(QEasingCurve::InOutSine);
    connect(heightAnim, &QPropertyAnimation::valueChanged, this, [=](const QVariant &height) {
        const int currentHeight = height.toInt();
        container->setFixedHeight(currentHeight);
        slideView->move(viewRect.topLeft() - QPoint(0, popupHeight - currentHeight));

        QRect clipRect = container->rect().adjusted(6, 0, -6, -6);
        if (clipRect.isEmpty()) {
            slideView->setMask(QRegion());
            return;
        }
        clipRect.translate(-slideView->pos());

        QPainterPath clipPath;
        clipPath.addRoundedRect(clipRect, getBorderRadius(), getBorderRadius());
        slideView->setMask(QRegion(clipPath.toFillPolygon().toPolygon()));
    });
    connect(heightAnim, &QPropertyAnimation::finished, this, [=]() {
        view()->show();
        slideView->deleteLater();
        d->setIsPopup(false);
    });
    heightAnim->start(QAbstractAnimation::DeleteWhenStopped);
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

void ComboBox::hidePopup() {
    Q_D(ComboBox);
    if (d->getIsPopup())
        return;
    d->setIsPopup(true);
    QWidget *container = view()->window();
    if (!container)
        return;

#if TOMEER_COMBOBOX_POPUP_ANIM_MODE == 1
    auto heightAnim = new QPropertyAnimation(container, "maximumHeight", this);
    heightAnim->setStartValue(container->height());
    heightAnim->setEndValue(1);
    heightAnim->setDuration(350);
    heightAnim->setEasingCurve(QEasingCurve::InOutSine);

    connect(heightAnim, &QPropertyAnimation::valueChanged, this,
            [=](const QVariant &h) {
                container->setFixedHeight(h.toInt());
            });

    connect(heightAnim, &QPropertyAnimation::finished, this, [=]() {
        QComboBox::hidePopup();
        d->setIsPopup(false);
    });

    heightAnim->start(QAbstractAnimation::DeleteWhenStopped);

#elif TOMEER_COMBOBOX_POPUP_ANIM_MODE == 2
    auto opacityAnim = new QPropertyAnimation(container, "windowOpacity", this);
    opacityAnim->setStartValue(container->windowOpacity());
    opacityAnim->setEndValue(0);
    opacityAnim->setDuration(350);
    connect(opacityAnim, &QPropertyAnimation::finished, this, [=]() {
        QComboBox::hidePopup();
        container->setWindowOpacity(1);
        d->setIsPopup(false);
    });
    opacityAnim->start(QAbstractAnimation::DeleteWhenStopped);

#elif TOMEER_COMBOBOX_POPUP_ANIM_MODE == 3
    const int popupHeight = container->height();
    const QRect viewRect = view()->geometry();

    auto slideView = new QLabel(container);
    slideView->setPixmap(view()->grab());
    slideView->setGeometry(viewRect);
    slideView->setAttribute(Qt::WA_TransparentForMouseEvents);
    slideView->show();
    slideView->raise();

    view()->hide();

    auto heightAnim = new QPropertyAnimation(container, "maximumHeight", this);
    heightAnim->setStartValue(popupHeight);
    heightAnim->setEndValue(1);
    heightAnim->setDuration(350);
    heightAnim->setEasingCurve(QEasingCurve::InOutSine);
    connect(heightAnim, &QPropertyAnimation::valueChanged, this, [=](const QVariant &height) {
        const int currentHeight = height.toInt();
        container->setFixedHeight(currentHeight);
        slideView->move(viewRect.topLeft() - QPoint(0, popupHeight - currentHeight));

        QRect clipRect = container->rect().adjusted(6, 0, -6, -6);
        if (clipRect.isEmpty()) {
            slideView->setMask(QRegion());
            return;
        }
        clipRect.translate(-slideView->pos());

        QPainterPath clipPath;
        clipPath.addRoundedRect(clipRect, getBorderRadius(), getBorderRadius());
        slideView->setMask(QRegion(clipPath.toFillPolygon().toPolygon()));
    });
    connect(heightAnim, &QPropertyAnimation::finished, this, [=]() {
        slideView->deleteLater();
        QComboBox::hidePopup();
        view()->show();
        container->setMinimumHeight(0);
        container->setMaximumHeight(QWIDGETSIZE_MAX);
        d->setIsPopup(false);
    });
    heightAnim->start(QAbstractAnimation::DeleteWhenStopped);

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

void ComboBox::paintEvent(QPaintEvent *event) {
    Q_D(ComboBox);
    QComboBox::paintEvent(event);

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    // 底部横线
    p.setPen(Qt::NoPen);
    p.setBrush(TOMEER_THEME->getThemeColor(ThemeType::Pattern));
    p.drawRoundedRect(QRectF(rect().left() + 4,
                             rect().bottom() * 0.9,
                             rect().right() - rect().left() - 8,
                             2),
                      2,
                      2);

    // 焦点指示
    p.setPen(Qt::NoPen);
    p.setBrush(TOMEER_THEME->getThemeColor(ThemeType::Check));
    p.drawRoundedRect(QRectF(rect().left() + 4 + (rect().right() - rect().left() - 8) / 2.0 - _pLineHalfWidth,
                             rect().bottom() * 0.9,
                             _pLineHalfWidth * 2,
                             3),
                      2,
                      2);

    // 箭头
    QPainterPath path;
    path.addText(QPointF(0, 0), QFont("tomeer"), QString(QChar(IconType::ChevronDown)));

    const QPointF center = QRectF(rect().right() - 20, rect().center().y() - rect().height() / 4.0, rect().height() / 2.0, rect().height() / 2.0).center();

    QTransform transform;
    transform.translate(center.x(), center.y());
    transform.rotate(_pRotateAngle);
    transform.translate(-path.boundingRect().center().x(), -path.boundingRect().center().y());

    p.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);

    p.setPen(Qt::NoPen);
    p.setBrush(TOMEER_THEME->getThemeColor(ThemeType::Text));
    p.setTransform(transform, true);
    p.drawPath(path);
}

void ComboBox::onThemeChanged(ThemeType::ThemeMode mode) {
    Q_D(ComboBox);
    setThemeMode(mode);
    update();
}

TOMEER_NAMESPACE_END