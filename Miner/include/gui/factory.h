#ifndef FACTORY_H
#define FACTORY_H

#include <qobject.h>
#include "core/factory_core.h"
#include "global/gui_global.h"

namespace gui {

class GRAPHICSCENE_EXPORT Factory: public core::Factory {
public:
    Factory(QObject* painter);
    core::ICell* createCell(int row, int col, QObject* parent = nullptr) override;
    std::shared_ptr<core::MineField> createMineField(int rowCount, int colCount, int mineCount) override;
private:
    QObject* m_painter = nullptr;
};

}

#endif // FACTORY_H
