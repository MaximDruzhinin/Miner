#include "minecell.h"
#include <QPainter>

MineCell::MineCell(int row, int col, ICellPainter* cell_painter,
                   unsigned width, unsigned height)
  : GraphicCell(row, col, cell_painter, width, height),
    detonated_(false)
{
}
//---------------------------------------------------------------------------

void MineCell::open()
{
    CellCore::open();
    detonated_ = true;
   // minefield()->blow();
    show();
}

void MineCell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    GraphicCell::paint(painter, option, widget);
    QRectF rect = boundingRect();
    if (detonated_)
        cellPainter()->drawMine(painter, rect, Qt::red);
    else
        cellPainter()->drawMine(painter, rect);
}
//---------------------------------------------------------------------------

void MineCell::show()
{
    //GraphicCell::show();
    if (opened())
        if (!flagged())
            update();
            //drawMine();
}
//---------------------------------------------------------------------------




