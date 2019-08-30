#include "gui/miner.h"
#include "gui/graphic_cell.h"
#include "draw/painter.h"
#include <QDebug>
#include <gui/mine_scene.h>
#include <qgraphicsview.h>
#include <gui/factory.h>
#include <memory>
#include <logger.h>

Miner::Miner(QGraphicsView *view, QObject *parent): m_view(view)
{
    m_painter = new draw::CellPainter(parent);
    setFactory(std::make_shared<gui::Factory>(m_painter));
}

bool Miner::runGame(GameType type)
{
    Q_ASSERT(m_view);

    m_minefield = run(type);
    Q_ASSERT(m_minefield);

    std::shared_ptr<gui::MineScene> scene = std::dynamic_pointer_cast<gui::MineScene>(m_minefield);
    Q_ASSERT(scene);

    scene->setView(m_view);

    return true;
}

uint Miner::flagCount()
{
    return m_minefield ? m_minefield->flagCount() : 0;
}

uint Miner::mineCount()
{
    return m_minefield ? m_minefield->mineCount() : 0;
}

void Miner::onTimeout()
{

}
