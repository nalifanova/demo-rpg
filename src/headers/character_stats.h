#ifndef CHARACTER_STATS_H
#define CHARACTER_STATS_H

#include <vector>

#include "buff.h"
#include "types.h"

class CharacterStats
{
public:
    explicit CharacterStats(
        const stattype strength = 1,
        const stattype intellect = 1,
        const stattype agility = 1,
        const stattype armor = 0,
        const stattype resistance = 0
    ):
    m_base_strength(strength),
    m_base_intellect(intellect),
    m_base_agility(agility),
    m_base_armor(armor),
    m_base_resistance(resistance)
    {}

    virtual ~CharacterStats() = default;

    [[nodiscard]] stattype get_strength() const
    {
        return m_base_strength + m_strength;
    }

    [[nodiscard]] stattype get_intellect() const
    {
        return m_base_intellect + m_intellect;
    }

    [[nodiscard]] stattype get_agility() const
    {
        return m_base_agility + m_agility;
    }

    [[nodiscard]] stattype get_armor() const
    {
        return m_base_armor + m_armor;
    }

    [[nodiscard]] stattype get_resistance() const
    {
        return m_base_resistance + m_resistance;
    }

    [[nodiscard]] stattype get_base_strength() const
    {
        return m_base_strength;
    }

    [[nodiscard]] stattype get_base_intellect() const
    {
        return m_base_intellect;
    }

    [[nodiscard]] stattype get_base_agility() const
    {
        return m_base_agility;
    }

    [[nodiscard]] stattype get_base_armor() const
    {
        return m_base_armor;
    }

    [[nodiscard]] stattype get_base_resistance() const
    {
        return m_base_resistance;
    }

protected:
    void increase_stats(
        const stattype strength = 0,
        const stattype intellect = 0,
        const stattype agility = 0,
        const stattype armor = 0,
        const stattype resistance = 0
    )
    {
        m_base_strength += strength;
        m_base_intellect += intellect;
        m_base_agility += agility;
        m_base_armor += armor;
        m_base_resistance += resistance;
    }

    void add_new_buff(Buff buff) // we want to use a copy
    {
        for (auto& buff_: Buffs)
        {
            if (buff.name == buff_.name)
            {
                buff_.duration = buff.duration;
            }
        }
        Buffs.push_back(buff);
        m_recalculate_buff();
    }
private:
    void m_recalculate_buff()
    {
        stattype m_strength_with_buffs = 0;
        stattype m_intellect_with_buffs = 0;
        stattype m_agility_with_buffs = 0;
        stattype m_armor_with_buffs = 0;
        stattype m_resistance_with_buffs = 0;

        for (const auto& buff_: Buffs)
        {
            if (buff_.is_debuff)
            {
                m_strength_with_buffs -= buff_.strength;
                m_intellect_with_buffs -= buff_.intellect;
                m_agility_with_buffs -= buff_.agility;
                m_armor_with_buffs -= buff_.armor;
                m_resistance_with_buffs -= buff_.resistance;
            }
            else
            {
                m_strength_with_buffs += buff_.strength;
                m_intellect_with_buffs += buff_.intellect;
                m_agility_with_buffs += buff_.agility;
                m_armor_with_buffs += buff_.armor;
                m_resistance_with_buffs += buff_.resistance;
            }
        }
        m_strength = m_strength_with_buffs;
        m_intellect = m_intellect_with_buffs;
        m_agility = m_agility_with_buffs;
        m_armor = m_armor_with_buffs;
        m_resistance = m_resistance_with_buffs;

        if (m_strength < 0) m_strength = 0;
        if (m_intellect < 0) m_intellect = 0;
        if (m_agility < 0) m_agility = 0;
        if (m_armor < 0) m_armor = 0;
        if (m_resistance < 0) m_resistance = 0;
    }

protected:
    std::vector<Buff> Buffs;

private:
    stattype m_strength = 0;
    stattype m_intellect = 0;
    stattype m_agility = 0;
    stattype m_armor = 0;
    stattype m_resistance = 0;

    stattype m_base_strength;
    stattype m_base_intellect;
    stattype m_base_agility;
    stattype m_base_armor;
    stattype m_base_resistance;
};


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

#endif //CHARACTER_STATS_H
