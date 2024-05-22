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
        base = {strength, intellect, agility, armor, resistance};
    }

    virtual ~CharacterStats() = default;

    [[nodiscard]] stattype get_strength() const
    {
        return static_cast<stattype>(base.strength + m_buffed.strength);
    }

    [[nodiscard]] stattype get_intellect() const
    {
        return static_cast<stattype>(base.intellect + m_buffed.intellect);
    }

    [[nodiscard]] stattype get_agility() const
    {
        return static_cast<stattype>(base.agility + m_buffed.agility);
    }

    [[nodiscard]] stattype get_armor() const
    {
        return static_cast<stattype>(base.armor + m_buffed.armor);
    }

    [[nodiscard]] stattype get_resistance() const
    {
        return static_cast<stattype>(base.resistance + m_buffed.resistance);
    }

    [[nodiscard]] stattype get_base_strength() const
    {
        return base.strength;
    }

    [[nodiscard]] stattype get_base_intellect() const
    {
        return base.intellect;
    }

    [[nodiscard]] stattype get_base_agility() const
    {
        return base.agility;
    }

    [[nodiscard]] stattype get_base_armor() const
    {
        return base.armor;
    }

    [[nodiscard]] stattype get_base_resistance() const
    {
        return base.resistance;
    }

protected:
    void increase_stats(
        stattype strength = 0,
        stattype intellect = 0,
        stattype agility = 0,
        stattype armor = 0,
        stattype resistance = 0
    )
    {
        base += {strength, intellect, agility, armor, resistance};
    }

    void increase_stats(const CoreStats core_stats)
    {
        base += core_stats;
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
    CoreStats base;

private:
    CoreStats m_buffed;
};

#endif //CHARACTER_STATS_H
