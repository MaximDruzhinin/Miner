#ifndef ICELL_H
#define ICELL_H

#include <QObject>
namespace core {
class ICell {
public:
    virtual ~ICell() {}
    virtual void show() = 0;
    virtual void open(bool detonate) = 0;
    virtual bool empty() const = 0;
    virtual bool setFlag() = 0;
    virtual bool removeFlag() = 0;
    virtual void setDigit(int _digit) = 0;
    virtual int digit() const = 0;
    virtual bool flagged() const = 0;
    virtual bool opened() const = 0;
    virtual void setReadyOpen(bool _readyOpened) = 0;
    virtual bool readyOpened() const = 0;
    virtual int col() const = 0;
    virtual int row() const = 0;
    virtual void setMine() = 0;
    virtual bool mined() const = 0;
    virtual bool detonated() const = 0;

signals:
    virtual void detonation() = 0;
};

}

Q_DECLARE_INTERFACE(core::ICell, "ICell")


#endif // ICELL_H
