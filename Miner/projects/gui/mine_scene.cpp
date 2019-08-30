#include "gui/mine_scene.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "gui/graphic_cell.h"
#include <QGraphicsItem>
#include <QMessageBox>
#include <queue>
#include <QGraphicsItem>
#include <QGraphicsView>
#include "logger.h"

gui::MineScene::MineScene(uint rowCount, uint colCount, uint mineCount, QObject* parent):
    MineField(rowCount, colCount, mineCount, parent)
{
}

bool gui::MineScene::addCell(core::ICell* cell)
{
    if (!MineField::addCell(cell))
        return false;

    QGraphicsItem* item = dynamic_cast<QGraphicsItem*>(cell);
    Q_ASSERT(item);

    addItem(item);

    return true;
}

void gui::MineScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!enabled()) {
        QGraphicsScene::mousePressEvent(event);
        return;
    }

    QGraphicsItem* item = itemAt(event->scenePos(), QTransform());
    Q_ASSERT(item);

    gui::GraphicCell* cell = dynamic_cast<gui::GraphicCell*>(item);
    Q_ASSERT(cell);

    if (event->button() == Qt::LeftButton) {
        if (m_firstClick) {
            init(cell);
            m_firstClick = false;
        }
        openCell(cell);
    }

    if (event->button() == Qt::RightButton) {
        if (!cell->flagged())
            addFlagInCell(cell->row(), cell->col());
        else
            removeFlagFromCell(cell->row(), cell->col());
    }

    QGraphicsScene::mousePressEvent(event);
}

void gui::MineScene::setView(QGraphicsView* view)
{
    m_graphicsView = view;

    Q_ASSERT(m_graphicsView);

    m_graphicsView->setScene(this);

    GraphicCell* cell = dynamic_cast<GraphicCell*>(at(0,0));
    Q_ASSERT(cell);

    m_graphicsView->setGeometry(0, 0, static_cast<int>(cell->width() * colCount()) + 1, static_cast<int>(cell->height() * rowCount()) + 1);
}
