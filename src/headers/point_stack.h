#ifndef POINT_STACK_H
#define POINT_STACK_H

#include "types.h"

class PointStack // I can't stand PointWell, aghrr
{
public:
    PointStack(): m_current(1u), m_initial(1u) {};

    PointStack(const pointtype current, const pointtype max)
    : m_current(current), m_initial(max)
    {
        if (current > max)
            m_current = max;
    };

    bool set_max(const pointtype new_max_points)
    {
        if (new_max_points < 1)
            return false;

        m_initial = new_max_points;

        if (m_current > m_initial)
            m_current = m_initial;

        return true;
    }

    [[nodiscard]] pointtype get_initial() const
    {
        return m_initial;
    }

    [[nodiscard]] pointtype get_current() const
    {
        return m_current;
    }

    [[nodiscard]] pointtype is_full() const
    {
        return m_current == m_initial;
    }

    void reduce(const pointtype amount)
    {
        if (amount > m_current)
        {
            m_current = 0;
            return;
        }
        m_current -= amount;
    }

    void increase(const pointtype amount)
    {
        if (amount + m_current > m_initial)
        {
            m_current = m_initial;
            return;
        }
        m_current += amount;
    }

private:
    pointtype m_current;
    pointtype m_initial; // stands for Max Value;
};

#endif //POINT_STACK_H
