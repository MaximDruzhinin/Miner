#ifndef ICELL_H
#define ICELL_H

#include <qobject.h>

namespace core {
class ICell {
public:
    virtual ~ICell() {}
    virtual void changed() = 0;
    virtual void open(bool detonate) = 0;
    virtual bool empty() const = 0;
    virtual bool setFlag() = 0;
    virtual bool removeFlag() = 0;
    virtual void setDigit(int digit) = 0;
    virtual int digit() const = 0;
    virtual bool flagged() const = 0;
    virtual bool opened() const = 0;
    virtual uint col() const = 0;
    virtual uint row() const = 0;
    virtual void setMine() = 0;
    virtual bool mined() const = 0;
    virtual bool detonated() const = 0;

signals:
    virtual void detonation() = 0;
};

}

Q_DECLARE_INTERFACE(core::ICell, "ICell")


#endif // ICELL_H
