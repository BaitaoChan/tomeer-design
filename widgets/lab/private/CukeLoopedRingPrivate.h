#ifndef CUKELOOPEDRINGPRIVATE_H
#define CUKELOOPEDRINGPRIVATE_H
#include "CukeProperty.h"

class QPropertyAnimation;
class QFont;
CUKE_BEGIN_NAMESPACE(widget)
CUKE_BEGIN_NAMESPACE(lab)
class CukeLoopedRing;
class CukeLoopedRingPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(CukeLoopedRing)
public:
    explicit CukeLoopedRingPrivate(CukeLoopedRing *q);
    ~CukeLoopedRingPrivate() override;

private:
    QPropertyAnimation *_animation = nullptr;
    QString _text = "Loading...";
    QFont *_font = nullptr;
};
CUKE_END_NAMESPACE(lab)
CUKE_END_NAMESPACE(widget)

#endif // CUKELOOPEDRINGPRIVATE_H
