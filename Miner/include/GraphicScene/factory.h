#ifndef FACTORY_H
#define FACTORY_H
#include <qobject.h>
#include "Core/factory_core.h"
#include <Global/graphic_scene_global.h>

namespace gui {

class GRAPHICSCENE_EXPORT Factory: public core::Factory {
public:
    core::ICell* createCell(int row, int col, QObject* parent = nullptr) override;
    //core::MineField* createMineField(int rowCount, int colCount, int mineCount) override;
    std::shared_ptr<core::MineField> createMineField(int rowCount, int colCount, int mineCount) override;
};

}


#endif // FACTORY_H
