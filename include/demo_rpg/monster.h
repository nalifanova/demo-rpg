#ifndef MONSTER_H
#define MONSTER_H

#include "types.h"
#include "point_stack.h"

class Monster
{
public:
    Monster(pointtype hp, damagetype min, damagetype max);

    [[nodiscard]] damagetype get_min_damage() const noexcept;

    [[nodiscard]] damagetype get_max_damage() const noexcept;

    [[nodiscard]] damagetype attack() const noexcept;

private:
    Monster() = delete;
    Monster(const Monster&) = delete;
    Monster(const Monster&&) = delete;

public:
    PointStack hp;

private:
    damagetype m_min_damage, m_max_damage;
};

#endif //MONSTER_H
