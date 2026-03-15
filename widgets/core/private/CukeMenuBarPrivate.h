#ifndef CUKEMENUBARPRIVATE_H
#define CUKEMENUBARPRIVATE_H
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(widget)
class CukeMenuBar;
class CukeMenuBarPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(CukeMenuBar)
public:
    explicit CukeMenuBarPrivate(CukeMenuBar *q);
    ~CukeMenuBarPrivate() override;
};
CUKE_NAMESPACE_END(widget)

#endif // CUKEMENUBARPRIVATE_H
