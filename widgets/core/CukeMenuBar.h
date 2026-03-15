#ifndef CUKEMENUBAR_H
#define CUKEMENUBAR_H
#include <QMenuBar>

#include "CukeContextMixin.h"

CUKE_NAMESPACE_BEGIN(widget)
class CukeMenuBarPrivate;
class CUKE_EXPORT CukeMenuBar : public CukeContextMixin<QMenuBar> {
    Q_OBJECT
    CUKE_DECLARE_DPTR(CukeMenuBar)
public:
    explicit CukeMenuBar(QWidget* parent = nullptr);
    ~CukeMenuBar() override;
};
CUKE_NAMESPACE_END(widget)

#endif // CUKEMENUBAR_H
