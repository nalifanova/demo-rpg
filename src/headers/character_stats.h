#ifndef CHARACTER_STATS_H
#define CHARACTER_STATS_H

#include <vector>

#include "core_stats.h"
#include "types.h"

class CharacterStats
{
public:
    explicit CharacterStats(
        const stattype strength = 0,
        const stattype intellect = 0,
        const stattype agility = 0,
        const stattype armor = 0,
        const stattype resistance = 0
    )
    {
        m_base = {strength, intellect, agility, armor, resistance};
    }

    virtual ~CharacterStats() = default;

    [[nodiscard]] stattype get_strength() const
    {
        return static_cast<stattype>(m_base.strength + m_buffed.strength);
    }

    [[nodiscard]] stattype get_intellect() const
    {
        return static_cast<stattype>(m_base.intellect + m_buffed.intellect);
    }

    [[nodiscard]] stattype get_agility() const
    {
        return static_cast<stattype>(m_base.agility + m_buffed.agility);
    }

    [[nodiscard]] stattype get_armor() const
    {
        return static_cast<stattype>(m_base.armor + m_buffed.armor);
    }

    [[nodiscard]] stattype get_resistance() const
    {
        return static_cast<stattype>(m_base.resistance + m_buffed.resistance);
    }

    [[nodiscard]] stattype get_base_strength() const
    {
        return m_base.strength;
    }

    [[nodiscard]] stattype get_base_intellect() const
    {
        return m_base.intellect;
    }

    [[nodiscard]] stattype get_base_agility() const
    {
        return m_base.agility;
    }

    [[nodiscard]] stattype get_base_armor() const
    {
        return m_base.armor;
    }

    [[nodiscard]] stattype get_base_resistance() const
    {
        return m_base.resistance;
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
        m_base = {strength, intellect, agility, armor, resistance};
    }

    void increase_stats(const CoreStats core_stats)
    {
        m_base += core_stats;
    }

    void add_new_buff(const Buff& buff)
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
        CoreStats with_buffs;

        for (const auto& buff_: Buffs)
        {
            if (buff_.is_debuff)
                with_buffs -= buff_.stats;
            else
                with_buffs += buff_.stats;
        }
        m_buffed = with_buffs;
    }

protected:
    std::vector<Buff> Buffs;

private:
    CoreStats m_buffed;
    CoreStats m_base;
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
