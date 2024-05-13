#ifndef HP_H
#define HP_H

#include "stat_types.h"

class Character
{
public:
    Character()
    {
        m_current_hp = 1;
        m_initial_hp = 1;
        m_strength = 1;
        m_intellect = 1;

        name = __func__;
    }

    Character(
        const hptype current_hp,
        const hptype initial_hp,
        const stattype strength,
        const stattype intellect
    )
    {
        m_current_hp = current_hp;
        m_initial_hp = initial_hp;
        if (m_current_hp > m_initial_hp)
            m_current_hp = m_initial_hp;
        m_strength = strength;
        m_intellect = intellect;

        name = __func__;
    }
    virtual ~Character() = default;

    bool set_initial_hp(const hptype new_max_hp)
    {
        if (new_max_hp < 1)
            return false;

        m_initial_hp = new_max_hp;

        if (m_current_hp > m_initial_hp)
            m_current_hp = m_initial_hp;

        return true;
    }

    [[nodiscard]] hptype get_initial_hp() const
    {
        return m_initial_hp;
    }

    [[nodiscard]] hptype get_current_hp() const
    {
        return m_current_hp;
    }

    [[nodiscard]] hptype get_strength() const
    {
        return m_strength;
    }

    [[nodiscard]] hptype get_intellect() const
    {
        return m_intellect;
    }

    void take_damage(const hptype damage)
    {
        if (damage > m_current_hp)
        {
            m_current_hp = 0;
            return;
        }
        m_current_hp -= damage;
    }

    void heal(const hptype hit_points)
    {
        if (hit_points + m_current_hp > m_initial_hp)
        {
            m_current_hp = m_initial_hp;
            return;
        }
        m_current_hp += hit_points;
    }

protected:
    void increase_stats(const stattype strength, const stattype intellect)
    {
        m_strength += strength;
        m_intellect += intellect;
    }

public:
    const char* name;

private:
    hptype m_current_hp;
    hptype m_initial_hp; // stands for MaxHP;
    stattype m_strength;
    stattype m_intellect;
};

#endif //HP_H
