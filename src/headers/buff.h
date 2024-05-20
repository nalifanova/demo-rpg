#ifndef BUFF_H
#define BUFF_H

#include <iostream>

#include "core_stats.h"
#include "types.h"

struct Buff
{
    explicit Buff (
        const char* name,
        const uint16_t duration = 2u,
        const bool is_debuff = false,
        const stattype strength = 0,
        const stattype intellect = 0,
        const stattype agility = 0,
        const stattype armor = 0,
        const stattype resistance = 0
    ): name(name), duration(duration), is_debuff(is_debuff)
    {
        stats.strength = strength;
        stats.intellect = intellect;
        stats.agility = agility;
        stats.armor = armor;
        stats.resistance = resistance;
    }

    explicit Buff(
        const char* name,
        const uint16_t duration = 2u,
        const bool is_debuff = false,
        const CoreStats core_stats = {0, 0, 0, 0, 0}
        ): name(name), duration(duration), is_debuff(is_debuff)
    {
        stats = core_stats;
    }

    std::string name;
    uint16_t duration;
    CoreStats stats;
    bool is_debuff;
};

#endif //BUFF_H
