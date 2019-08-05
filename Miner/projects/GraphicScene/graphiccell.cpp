#include "GraphicScene/graphiccell.h"
//#include "logger.h"
#include <qdebug.h>

gui::GraphicCell::GraphicCell(int row, int col, QObject* painter,
                         quint8 width, quint8 height):
    Cell(row, col),
    m_painter(painter),
    m_width(width),
    m_height(height)
{

}


void gui::GraphicCell::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    if (m_painter) {
        draw::ICellPainter* myPainter = dynamic_cast<draw::ICellPainter*>(m_painter);
        if (!myPainter) {
            qDebug () << "Can't cast to draw::IPainter";
            return;
        }
        myPainter->drawCell(painter, boundingRect(), opened());
        if (opened()) {
            if (mined()) {
                if (detonated())
                    myPainter->drawMine(painter, boundingRect(), Qt::red);
                else
                    myPainter->drawMine(painter, boundingRect());
            } else {
                if (!flagged())
                    myPainter->drawColorDigit(painter, boundingRect(),digit() );
                else {
                    myPainter->drawMine(painter, boundingRect());
                    myPainter->drawCross(painter, boundingRect());
                }
            }
        } else {
            if (flagged())
               drawFlag(painter);
        }
    }
}

QRectF gui::GraphicCell::boundingRect() const
{
    return QRectF(col() * width(), row() * height(), width(), height());
}

void gui::GraphicCell::changed()
{
    update();
}

quint8 gui::GraphicCell::width() const
{
    return m_width;
}

quint8 gui::GraphicCell::height() const
{
    return m_height;
}

QObject* gui::GraphicCell::cellPainter() const
{
    return m_painter;
}

void gui::GraphicCell::drawFlag(QPainter* painter) const
{

    draw::ICellPainter* myPainter = dynamic_cast<draw::ICellPainter*>(m_painter);
    if (!myPainter) {
        qDebug () << "Can't cast to draw::IPainter";
        return;
    }
    const int distance = 4;

    QRectF rect = boundingRect();
    int x = rect.x() + distance;
    int y = rect.y() + distance;
    int width = rect.width() - 2 * distance;
    int height = rect.height() - 2 * distance;

    if (myPainter)
        myPainter->drawFlag(painter, QRectF(x, y, width, height));
}


