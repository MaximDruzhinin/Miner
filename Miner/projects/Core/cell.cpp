#include "core/cell.h"
#include <QPainter>
#include <qdebug.h>

core::Cell::Cell(uint row, uint col, QObject* parent):
    QObject(parent),
    m_row(row),
    m_col(col)
{
}

void core::Cell::open(bool detonate)
{
    m_opened = true;
    if (m_mined && detonate) {
         m_detonated = true;
         detonation();
    }
    changed();
}

bool core::Cell::empty() const
{
    return (!m_digit && !m_flagged && !m_mined);
}

bool core::Cell::setFlag()
{
    if (!m_opened && !m_flagged) {
        m_flagged = true;
        changed();
        return true;
    }
    return false;
}

bool core::Cell::removeFlag()
{
    if (!m_opened && m_flagged) {
       m_flagged = false;
       changed();
       return true;
    }

    return false;
}

void core::Cell::setDigit(int digit)
{
    m_digit = digit;
}

int core::Cell::digit() const
{
    return m_digit;
}

bool core::Cell::flagged() const
{
    return m_flagged;
}

bool core::Cell::opened() const
{
    return m_opened;
}

uint core::Cell::col() const
{
    return m_col;
}

uint core::Cell::row() const
{
    return m_row;
}

void core::Cell::setMine()
{
    m_mined = true;
}

bool core::Cell::mined() const
{
    return m_mined;
}

bool core::Cell::detonated() const
{
    return m_detonated;
}
