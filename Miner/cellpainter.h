#ifndef MINERPAINTER_H
#define MINERPAINTER_H
#include "icellpainter.h"
#include <QPainter>

namespace draw {

    class CellPainter: public ICellPainter
    {
    public:
        void drawCell(QPainter* painter, const QRectF& rect, bool opened) const override;
        void drawColorDigit(QPainter* painter, const QRectF& rect, quint8 digit) const override;
        void drawCross(QPainter* painter, const QRectF& rect) const override;
        void drawFlag(QPainter* painter, const QRectF& rect) const override;
        void drawMine(QPainter* painter, const QRectF& rect, QColor backgroundColor = Qt::gray) const override;
    };

}


#endif // MINERPAINTER_H
