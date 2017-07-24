#include "cell.h"
#include <QPainter>


base::Cell::Cell(int row, int col, QObject* parent):
    QObject(parent),
    m_row(row),
    m_col(col)
{

}

void base::Cell::open(bool detonate)
{
    m_opened = true;
    if (m_mined && detonate) {
         m_detonated = true;
         detonation();
    }
    show();
}

bool base::Cell::empty() const
{
    return (!m_digit && !m_flagged && !m_mined);
}

bool base::Cell::setFlag()
{
    if (!m_opened && !m_flagged) {
        m_flagged = true;
        show();
        return true;
    }
    return false;
}

bool base::Cell::removeFlag()
{
    if (!m_opened && m_flagged) {
       m_flagged = false;
       show();
       return true;
    }

    return false;
}

void base::Cell::setDigit(int digit)
{
    m_digit = digit;
}

int base::Cell::digit() const
{
    return m_digit;
}

bool base::Cell::flagged() const
{
    return m_flagged;
}

bool base::Cell::opened() const
{
    return m_opened;
}

void base::Cell::setReadyOpen(bool _readyOpened)
{
    m_readyOpened = _readyOpened;
}

bool base::Cell::readyOpened() const
{
    return m_readyOpened;
}

int base::Cell::col() const
{
    return m_col;
}

int base::Cell::row() const
{
    return m_row;
}

void base::Cell::setMine()
{
    m_mined = true;
}

bool base::Cell::mined() const
{
    return m_mined;
}

bool base::Cell::detonated() const
{
    return m_detonated;
}
