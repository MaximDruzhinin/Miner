#include "GraphicScene/factory.h"
#include "Core/cell.h"
#include "GraphicScene/graphiccell.h"
#include "GraphicScene/minescene.h"
#include "Draw/cellpainter.h"
#include "Core/minefield.h"


core::ICell* gui::Factory::createCell(int row, int col, QObject *parent)
{
    return new gui::GraphicCell(row, col, new draw::CellPainter);
}

core::MineField* gui::Factory::createMineField(int rowCount, int colCount, int mineCount)
{
    auto scene =  new gui::MineScene(rowCount, colCount, mineCount);

    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < colCount; j++) {
            scene->addCell(new gui::GraphicCell(i,j, new draw::CellPainter));
        }
    }

    return scene;
}
