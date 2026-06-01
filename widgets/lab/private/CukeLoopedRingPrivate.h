#ifndef CUKELOOPEDRINGPRIVATE_H
#define CUKELOOPEDRINGPRIVATE_H
#include "CukeProperty.h"
#include "CukeType.h"

class QPropertyAnimation;
class QFont;
CUKE_NAMESPACE_BEGIN(lab)
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
CUKE_NAMESPACE_END(lab)

#endif // CUKELOOPEDRINGPRIVATE_H
