#ifndef FACTORY_CORE_H
#define FACTORY_CORE_H
//#include "Core/cell.h"
#include <qobject.h>

namespace core {
class MineField;

}

namespace core {
class ICell;
}


namespace core {

class Factory {
public:
    virtual core::ICell* createCell(int row, int col, QObject* parent = nullptr) = 0;
    virtual MineField* createMineField(int rowCount, int colCount, int mineCount) = 0;
};

}


#endif // FACTORY_CORE_H
