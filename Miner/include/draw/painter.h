#ifndef MINERPAINTER_H
#define MINERPAINTER_H

#include "ipainter.h"
#include <QPainter>
#include "global/draw_global.h"
#include <qobject.h>

namespace draw {

class  DRAW_EXPORT CellPainter: public ICellPainter, public QObject {
public:
    CellPainter(QObject* parent = nullptr);
    void drawCell(QPainter* painter, const QRectF& rect, bool opened) const override;
    void drawColorDigit(QPainter* painter, const QRectF& rect, quint8 digit) const override;
    void drawCross(QPainter* painter, const QRectF& rect) const override;
    void drawFlag(QPainter* painter, const QRectF& rect) const override;
    void drawMine(QPainter* painter, const QRectF& rect, QColor backgroundColor = Qt::gray) const override;
};

}

#endif // MINERPAINTER_H
