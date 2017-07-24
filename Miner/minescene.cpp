#include "minescene.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "graphiccell.h"
#include <QGraphicsItem>
#include <QMessageBox>
#include <queue>
//#include <QGraphicsItem>

#include "cellpainter.h"
#include <QDebug>



gui::MineScene::MineScene(quint8 rowCount, quint8 colCount, quint8 mineCount, QObject* parent)

  : MineField(rowCount, colCount, mineCount, parent)
{
}

bool gui::MineScene::addCell(base::ICell *cell)
{
    if (!MineField::addCell(cell))
        return false;

    QGraphicsItem* item = dynamic_cast<QGraphicsItem*>(cell);

    if (item)
    {
        addItem(item);
        return true;
    }
    else
        return false;
}

void gui::MineScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!enabled())
    {
        QGraphicsScene::mousePressEvent(event);
        return;
    }

    QGraphicsItem* item = itemAt(event->scenePos(),QTransform());
    base::GraphicCell* cell = dynamic_cast<base::GraphicCell*>(item);
    if (cell)
    {
        if (event->button() == Qt::LeftButton) {
            openCell(cell);
        }

        if (event->button() == Qt::RightButton)
        {
            if (!cell->flagged())
                addFlagInCell(cell->row(), cell->col());
            else
                removeFlagFromCell(cell->row(), cell->col());
        }
    }
    QGraphicsScene::mousePressEvent(event);
}

quint8 gui::MineScene::cellWidth() const
{
    return m_cellWidth;
}

quint8 gui::MineScene::cellHeight() const
{
    return m_cellHeight;
}








