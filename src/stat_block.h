#ifndef STAT_BLOCK_H
#define STAT_BLOCK_H

#include "stat_types.h"

class StatBlock
{
public:
    StatBlock()
    {
        m_luck = 1u;
        m_resitrance = 1u;
    }

    explicit StatBlock(const stattype luck, const stattype resitrance)
    {
        m_luck = luck;
        m_resitrance = resitrance;
    }

    void set_luck(const stattype luck)
    {
        m_luck = luck;
    }

    [[nodiscard]] stattype get_luck() const
    {
        return m_luck;
    }

    [[nodiscard]] stattype get_resistance() const
    {
        return m_resitrance;
    }

private:
    stattype m_luck;  // 0xFF
    stattype m_resitrance;  // 0xFF
};

#endif //STAT_BLOCK_H
