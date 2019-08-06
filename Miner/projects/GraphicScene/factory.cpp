#include "GraphicScene/factory.h"
#include "Core/cell.h"
#include "GraphicScene/graphiccell.h"
#include "GraphicScene/minescene.h"
#include "Draw/cellpainter.h"
#include "Core/minefield.h"

gui::Factory::Factory(QObject* painter): m_painter(painter)
{
}

core::ICell* gui::Factory::createCell(int row, int col, QObject* parent)
{
    return new gui::GraphicCell(row, col, m_painter);
}

std::shared_ptr<core::MineField> gui::Factory::createMineField(int rowCount, int colCount, int mineCount)
{
    return std::make_shared<MineScene>(rowCount, colCount, mineCount);
}
