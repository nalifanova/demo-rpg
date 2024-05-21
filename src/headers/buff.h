#ifndef BUFF_H
#define BUFF_H

#include <iostream>

#include "core_stats.h"
#include "types.h"

struct Buff
{
    explicit Buff (
        const char* name = "undefined",
        const uint16_t duration = 2u,
        const CoreStats stats = CoreStats(),
        const bool is_debuff = false
    ): name(name), duration(duration), stats(stats), is_debuff(is_debuff) {}

    explicit Buff(
        const char* name,
        const uint16_t duration = 2u,
        const stattype strength = 0,
        const stattype intellect = 0,
        const stattype agility = 0,
        const stattype armor = 0,
        const stattype resistance = 0,
        const bool is_debuff = false
    ):
    name(name),
    duration(duration),
    stats({strength, intellect, agility, armor, resistance}),
    is_debuff(is_debuff) {}

    Buff& operator=(const char* name)
    {
        this->name = std::string(name);
        this->duration = 2u;
        this->stats = CoreStats(0);
        this->is_debuff = false;
        return *this;
    }

    std::string name;
    uint16_t duration;
    CoreStats stats;
    bool is_debuff;
};

#endif //BUFF_H
