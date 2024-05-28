#include "monster.h"

#include "random.h"
#include "point_stack.h"

Monster::Monster(
    const pointtype hp,
    const damagetype min,
    const damagetype max
): hp(hp, hp), m_min_damage(min), m_max_damage(max) {}

damagetype Monster::get_min_damage() const noexcept
{
    return m_min_damage;
}

damagetype Monster::get_max_damage() const noexcept
{
    return m_max_damage;
}

damagetype Monster::attack() const noexcept
{
    return generate_number(m_min_damage, m_max_damage);
}