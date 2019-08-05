#include "GraphicScene/minescene.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "GraphicScene/graphiccell.h"
#include <QGraphicsItem>
#include <QMessageBox>
#include <queue>
#include <QGraphicsItem>
#include <QGraphicsView>


gui::MineScene::MineScene(quint8 rowCount, quint8 colCount, quint8 mineCount, QObject* parent):
    MineField(rowCount, colCount, mineCount, parent)
{
}

bool gui::MineScene::addCell(core::ICell* cell)
{
    if (!MineField::addCell(cell))
        return false;

    QGraphicsItem* item = dynamic_cast<QGraphicsItem*>(cell);

    if (item) {
        addItem(item);
        return true;
    }
    else
        return false;
}

void gui::MineScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!enabled()) {
        QGraphicsScene::mousePressEvent(event);
        return;
    }

    QGraphicsItem* item = itemAt(event->scenePos(), QTransform());
    gui::GraphicCell* cell = dynamic_cast<gui::GraphicCell*>(item);
    if (cell) {
        if (event->button() == Qt::LeftButton) {
            openCell(cell);
        }

        if (event->button() == Qt::RightButton) {
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

void gui::MineScene::setView(QGraphicsView* view)
{
    m_graphicsView = view;
    if (!m_graphicsView)
        return;

    m_graphicsView->setScene(this);

    m_graphicsView->setGeometry(0,0, cellWidth() * colCount() + 1, cellHeight() * rowCount() + 1);

}








