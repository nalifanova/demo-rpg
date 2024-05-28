#ifndef BUFF_H
#define BUFF_H

#include <iostream>

#include "core_stats.h"
#include "types.h"

struct Buff
{
    Buff();

    explicit Buff (
        const char* name = "undefined",
        uint16_t duration = 2u,
        CoreStats stats = CoreStats(),
        bool is_debuff = false
    );

    explicit Buff(
        const char* name,
        uint16_t duration = 2u,
        stattype strength = 0,
        stattype intellect = 0,
        stattype agility = 0,
        stattype armor = 0,
        stattype resistance = 0,
        bool is_debuff = false
    );

    Buff& operator=(const char* name);

    std::string name;
    uint16_t duration;
    CoreStats stats;
    bool is_debuff;
};

#endif //BUFF_H
