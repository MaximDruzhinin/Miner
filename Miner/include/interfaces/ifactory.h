#ifndef FACTORY_CORE_H
#define FACTORY_CORE_H
#include <qobject.h>
#include <memory>

namespace core {
class MineField;
class ICell;
}

namespace core {

class Factory {
public:
    virtual ~Factory() {}
    virtual core::ICell* createCell(int row, int col, QObject* parent = nullptr) = 0;
    virtual std::shared_ptr<MineField> createMineField(int rowCount, int colCount, int mineCount) = 0;
};

}


#endif // FACTORY_CORE_H
