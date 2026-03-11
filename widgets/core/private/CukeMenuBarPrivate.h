#ifndef CUKEMENUBARPRIVATE_H
#define CUKEMENUBARPRIVATE_H
#include "CukeProperty.h"

CUKE_BEGIN_NAMESPACE(widget)
class CukeMenuBar;
class CukeMenuBarPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(CukeMenuBar)
public:
    explicit CukeMenuBarPrivate(CukeMenuBar *q);
    ~CukeMenuBarPrivate() override;
};
CUKE_END_NAMESPACE(widget)

#endif // CUKEMENUBARPRIVATE_H
