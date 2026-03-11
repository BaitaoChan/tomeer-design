#ifndef CUKEMENUBAR_H
#define CUKEMENUBAR_H
#include <QMenuBar>

#include "CukeContextMixin.h"

CUKE_BEGIN_NAMESPACE(widget)
class CukeMenuBarPrivate;
class CUKE_EXPORT CukeMenuBar : public CukeContextMixin<QMenuBar> {
    Q_OBJECT
    CUKE_DECLARE_DPTR(CukeMenuBar)
public:
    explicit CukeMenuBar(QWidget* parent = nullptr);
    ~CukeMenuBar() override;
};
CUKE_END_NAMESPACE(widget)

#endif // CUKEMENUBAR_H
