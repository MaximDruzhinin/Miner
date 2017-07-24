#ifndef ICELL_PAINTER_H
#define ICELL_PAINTER_H
#include <QRectF>
#include <QColor>
#include <QObject>

class QPainter;



namespace draw {

    class ICellPainter
    {
    public:
        virtual ~ICellPainter() { }
        virtual void drawCell(QPainter* painter, const QRectF& rect, bool opened) const = 0;
        virtual void drawColorDigit(QPainter* painter, const QRectF& rect, quint8 digit) const = 0;
        virtual void drawCross(QPainter* painter, const QRectF& rect) const = 0;
        virtual void drawFlag(QPainter* painter, const QRectF& rect) const = 0;
        virtual void drawMine(QPainter* painter, const QRectF& rect, QColor backgroundColor = Qt::gray) const = 0;
    };
}

Q_DECLARE_INTERFACE(draw::ICellPainter, "ICellPainter")

#endif // ICELL_PAINTER_H
