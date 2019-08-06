#ifndef CELL_H
#define CELL_H

#include <qobject.h>
#include "icell.h"
#include "global/core_global.h"

namespace core {

class CORE_EXPORT Cell: public QObject, public ICell {
    Q_OBJECT
public:
    Cell(uint col, uint row, QObject* parent = nullptr);
    void open(bool detonate) override;
    bool empty() const override;
    bool setFlag() override;
    bool removeFlag() override;
    void setDigit(int digit) override;
    int digit() const override;
    bool flagged() const override;
    bool opened() const override;
    void setReadyOpen(bool ready_opened) override;
    bool readyOpened() const override;
    uint col() const override;
    uint row() const override;
    void setMine() override;
    bool mined() const override;
    bool detonated() const override;
signals:
    void detonation() override;
private:
    bool m_opened = false;
    bool m_flagged = false;
    uint m_row;
    uint m_col;
    int m_digit = 0;
    bool m_readyOpened = false;
    bool m_detonated = false;
    bool m_mined = false;
};

}



#endif // CELL_H
