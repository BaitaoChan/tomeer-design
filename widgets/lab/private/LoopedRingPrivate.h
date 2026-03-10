#ifndef LOOPEDRINGPRIVATE_H
#define LOOPEDRINGPRIVATE_H
#include "Property.h"

class QPropertyAnimation;
class QFont;
CUKE_BEGIN_NAMESPACE(widget)
CUKE_BEGIN_NAMESPACE(lab)
class LoopedRing;
class LoopedRingPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(LoopedRing)
public:
    explicit LoopedRingPrivate(LoopedRing *q);
    ~LoopedRingPrivate() override;

private:
    QPropertyAnimation *_animation = nullptr;
    QString _text = "Loading...";
    QFont *_font = nullptr;
};
CUKE_END_NAMESPACE(lab)
CUKE_END_NAMESPACE(widget)

#endif // LOOPEDRINGPRIVATE_H
