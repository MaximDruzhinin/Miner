#include "GraphicScene/miner.h"
#include "GraphicScene/graphiccell.h"
#include "Draw/cellpainter.h"
#include <QDebug>
#include <GraphicScene/minescene.h>
#include <qgraphicsview.h>
#include <GraphicScene/factory.h>
#include <memory>
#include <logger.h>

Miner::Miner(QGraphicsView *view, QObject *parent): m_view(view)
{
    m_painter = new draw::CellPainter(parent);
    setFactory(std::make_shared<gui::Factory>(m_painter));
}

bool Miner::runGame(GameType type)
{
    if (!m_view) {
        LOG_ERROR("Graphics View is NULL");
        return false;
    }

    m_minefield = run(type);
    if (!m_minefield) {
        LOG_ERROR("Failed init minefield")
        return false;
    }

    std::shared_ptr<gui::MineScene> scene = std::dynamic_pointer_cast<gui::MineScene>(m_minefield);
    if (!scene) {
        LOG_ERROR("Invalid cast to gui::MineScene")
        return false;
    }
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
