#ifndef BUFF_H
#define BUFF_H

#include <iostream>

#include "types.h"

struct Buff
{
    explicit Buff (
    const char* name,
    const uint16_t duration = 2u,
    const stattype strength = 0,
    const stattype intellect = 0,
    const stattype agility = 0,
    const stattype armor = 0,
    const stattype resistance = 0,
    const bool is_debuff = false) :
    name(name),
    duration(duration),
    strength(strength),
    intellect(intellect),
    agility(agility),
    armor(armor),
    resistance(resistance),
    is_debuff(is_debuff)
    {}

    std::string name;
    uint16_t duration;
    stattype strength;
    stattype intellect;
    stattype agility;
    stattype armor;
    stattype resistance;

    bool is_debuff;
};

#endif //BUFF_H
