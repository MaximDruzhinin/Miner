#include "gui/factory.h"
#include "core/cell.h"
#include "gui/graphic_cell.h"
#include "gui/mine_scene.h"
#include "draw/painter.h"
#include "core/minefield.h"

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
