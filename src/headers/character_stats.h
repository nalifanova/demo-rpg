#ifndef CHARACTER_STATS_H
#define CHARACTER_STATS_H

#include <vector>
#include "buff.h"
#include "core_stats.h"
#include "types.h"

class CharacterStats
{
public:
    explicit CharacterStats(
        stattype strength = 0,
        stattype intellect = 0,
        stattype agility = 0,
        stattype armor = 0,
        stattype resistance = 0
    );

    virtual ~CharacterStats() = default;

    [[nodiscard]] stattype get_strength() const;

    [[nodiscard]] stattype get_intellect() const;

    [[nodiscard]] stattype get_agility() const;

    [[nodiscard]] stattype get_armor() const;

    [[nodiscard]] stattype get_resistance() const;

    [[nodiscard]] stattype get_base_strength() const;

    [[nodiscard]] stattype get_base_intellect() const;

    [[nodiscard]] stattype get_base_agility() const;

    [[nodiscard]] stattype get_base_armor() const;

    [[nodiscard]] stattype get_base_resistance() const;

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

    void increase_stats(CoreStats core_stats);

    void add_new_buff(const Buff& buff);

private:
    void m_recalculate_buff();

protected:
    std::vector<Buff> Buffs{};
    CoreStats base;

private:
    CoreStats m_buffed;
};

#endif //CHARACTER_STATS_H
