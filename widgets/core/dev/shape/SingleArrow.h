#ifndef SINGLEARROW_H
#define SINGLEARROW_H
#include <QPainterPath>

CUKE_BEGIN_NAMESPACE(widget)
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

CUKE_END_NAMESPACE(widget)

#endif // SINGLEARROW_H