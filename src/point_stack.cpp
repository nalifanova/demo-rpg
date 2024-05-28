#include "point_stack.h"

PointStack::PointStack(): m_current(1u), m_initial(1u) {};

PointStack::PointStack(const pointtype current, const pointtype max)
: m_current(current), m_initial(max)
{
    if (current > max)
        m_current = max;
};

[[nodiscard]] pointtype PointStack::get_initial() const
{
    return m_initial;
}

[[nodiscard]] pointtype PointStack::get_current() const
{
    return m_current;
}

[[nodiscard]] pointtype PointStack::is_full() const
{
    return m_current == m_initial;
}

bool PointStack::set_max(const pointtype new_max_points)
{
    if (new_max_points < 1)
        return false;

    m_initial = new_max_points;

    if (m_current > m_initial)
        m_current = m_initial;

    return true;
}

void PointStack::reduce(const pointtype amount)
{
    if (amount > m_current)
    {
        m_current = 0;
        return;
    }
    m_current -= amount;
}

void PointStack::increase(const pointtype amount)
{
    if (amount + m_current > m_initial)
    {
        m_current = m_initial;
        return;
    }
    m_current += amount;
}
