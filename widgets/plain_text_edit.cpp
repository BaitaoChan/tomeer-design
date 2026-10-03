#include <QKeySequence>
#include <QPropertyAnimation>

#include "action.h"
#include "menu.h"
#include "scroll_bar.h"
#include "plain_text_edit.h"
#include "plain_text_edit_style.h"
#include "plain_text_edit_private.h"

TOMEER_NAMESPACE_BEGIN()
TOMEER_Q_PROPERTY_IMPL(PlainTextEdit, int, BorderRadius)
TOMEER_Q_PROPERTY_IMPL(PlainTextEdit, int, LineHalfWidth)
TOMEER_Q_PROPERTY_IMPL(PlainTextEdit, ThemeType::ThemeMode, ThemeMode)
PlainTextEdit::PlainTextEdit(QWidget *parent)
    : QPlainTextEdit(parent),
      _pBorderRadius(6),
      d_ptr(new PlainTextEditPrivate(this)) {
    Q_D(PlainTextEdit);
    setHorizontalScrollBar(new ScrollBar(this));
    setVerticalScrollBar(new ScrollBar(this));
    setStyle(new PlainTextEditStyle(style()));
    setAttribute(Qt::WA_TranslucentBackground);
    viewport()->setAutoFillBackground(false);
    viewport()->setAttribute(Qt::WA_TranslucentBackground);

    document()->setDocumentMargin(8);

    d->_lineAnim = new QPropertyAnimation(this, "_pLineHalfWidth", this);
    d->_lineAnim->setDuration(300);
    d->_lineAnim->setEasingCurve(QEasingCurve::InOutSine);

    connect(d->_lineAnim, &QPropertyAnimation::valueChanged, this, QOverload<>::of(&QWidget::update));
    connect(this, &PlainTextEdit::pBorderRadiusChanged, this, QOverload<>::of(&QWidget::update));
    connect(TOMEER_THEME, &Theme::themeModeChanged, this, &PlainTextEdit::onThemeChanged);
    connect(TOMEER_THEME, &Theme::themeColorChanged, this, QOverload<>::of(&QWidget::update));
}

PlainTextEdit::PlainTextEdit(const QString &text, QWidget *parent)
    : PlainTextEdit(parent) {
    setPlainText(text);
}

PlainTextEdit::~PlainTextEdit() = default;

void PlainTextEdit::contextMenuEvent(QContextMenuEvent *event) {
    const auto menu = new Menu(this);
    menu->setAttribute(Qt::WA_DeleteOnClose);
    Action *action = nullptr;

    if (!isReadOnly()) {
        action = new Action(IconType::ArrowUndo, tr("Undo"), menu);
        action->setShortcut(QKeySequence::Undo);
        action->setEnabled(isUndoRedoEnabled() && document()->isUndoAvailable());
        connect(action, &QAction::triggered, this, &QPlainTextEdit::undo);
        menu->addAction(action);

        action = new Action(IconType::ArrowRedo, tr("Redo"), menu);
        action->setShortcut(QKeySequence::Redo);
        action->setEnabled(isUndoRedoEnabled() && document()->isRedoAvailable());
        connect(action, &QAction::triggered, this, &QPlainTextEdit::redo);
        menu->addAction(action);
        menu->addSeparator();

        action = new Action(IconType::Cut, tr("Cut"), menu);
        action->setShortcut(QKeySequence::Cut);
        action->setEnabled(textCursor().hasSelection());
        connect(action, &QAction::triggered, this, &QPlainTextEdit::cut);
        menu->addAction(action);
    }

    action = new Action(IconType::Copy, tr("Copy"), menu);
    action->setShortcut(QKeySequence::Copy);
    action->setEnabled(textCursor().hasSelection());
    connect(action, &QAction::triggered, this, &QPlainTextEdit::copy);
    menu->addAction(action);

    if (!isReadOnly()) {
        action = new Action(IconType::ClipboardPaste, tr("Paste"), menu);
        action->setShortcut(QKeySequence::Paste);
        action->setEnabled(canPaste());
        connect(action, &QAction::triggered, this, &QPlainTextEdit::paste);
        menu->addAction(action);

        action = new Action(IconType::Delete, tr("Delete"), menu);
        action->setShortcut(QKeySequence::Delete);
        action->setEnabled(textCursor().hasSelection());
        connect(action, &QAction::triggered, this, [this] { textCursor().removeSelectedText(); });
        menu->addAction(action);
    }

    menu->addSeparator();

    action = new Action(IconType::SelectAllOn, tr("Select All"), menu);
    action->setShortcut(QKeySequence::SelectAll);
    action->setEnabled(!document()->isEmpty());
    connect(action, &QAction::triggered, this, &QPlainTextEdit::selectAll);
    menu->addAction(action);

    menu->popup(event->globalPos());
    setFocus();
}

void PlainTextEdit::onThemeChanged(ThemeType::ThemeMode mode) {
    setThemeMode(mode);
    style()->polish(this);
    viewport()->update();
    update();
}

void PlainTextEdit::focusInEvent(QFocusEvent *event) {
    Q_D(PlainTextEdit);
    d->_isFocused = true;

    d->_lineAnim->stop();
    d->_lineAnim->setStartValue(_pLineHalfWidth);
    d->_lineAnim->setEndValue(qMax(0, (rect().width() - 8) / 2));
    d->_lineAnim->start();

    QPlainTextEdit::focusInEvent(event);
}

void PlainTextEdit::focusOutEvent(QFocusEvent *event) {
    Q_D(PlainTextEdit);
    d->_isFocused = false;

    d->_lineAnim->stop();
    d->_lineAnim->setStartValue(_pLineHalfWidth);
    d->_lineAnim->setEndValue(0);
    d->_lineAnim->start();

    QPlainTextEdit::focusOutEvent(event);
}

void PlainTextEdit::resizeEvent(QResizeEvent *event) {
    Q_D(PlainTextEdit);
    QPlainTextEdit::resizeEvent(event);

    d->_lineAnim->stop();
    setLineHalfWidth(d->_isFocused ? qMax(0, (rect().width() - 8) / 2) : 0);
}

void PlainTextEdit::paintEvent(QPaintEvent *event) {
    QPlainTextEdit::paintEvent(event);

    QPalette pal = palette();
    pal.setColor(QPalette::Text, TOMEER_THEME->getThemeColor(ThemeType::Text));
    setPalette(pal);
}

TOMEER_NAMESPACE_END
