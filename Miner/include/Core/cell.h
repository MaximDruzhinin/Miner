#ifndef CELL_H
#define CELL_H

#include <QObject>

#include "icell.h"
#include "Global/core_global.h"

namespace core {

class CORE_EXPORT Cell: public QObject, public ICell {
    Q_OBJECT
public:
    Cell(int col, int row, QObject* parent = 0);
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
    int col() const override;
    int row() const override;
    void setMine() override;
    bool mined() const override;
    bool detonated() const override;
signals:
    void detonation();
private:
    bool m_opened = false;
    bool m_flagged = false;
    int m_row;
    int m_col;
    int m_digit = 0;
    bool m_readyOpened = false;
    bool m_detonated = false;
    bool m_mined = false;
};

}



#endif // CELL_H
