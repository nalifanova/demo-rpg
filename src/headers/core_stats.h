#ifndef CORE_STATS_H
#define CORE_STATS_H

#include "types.h"

// We do get rid of huge pieces of duplications
struct CoreStats
{
    stattype strength = 1;
    stattype intellect = 1;
    stattype agility = 1;
    stattype armor = 0;
    stattype resistance = 0;

    // return by _reference_
    CoreStats& operator+=(const CoreStats& rhs) // rhs = right hand side
    {
        this->strength += rhs.strength;
        this->intellect += rhs.intellect;
        this->agility += rhs.agility;
        this->armor += rhs.armor;
        this->resistance += rhs.resistance;
        return *this;
    }

    CoreStats& operator-=(const CoreStats& rhs) // rhs = right hand side
    {
        const CoreStats tmp = *this; // create a temporary current copy of CS

        this->strength -= rhs.strength;
        this->intellect -= rhs.intellect;
        this->agility -= rhs.agility;
        this->armor -= rhs.armor;
        this->resistance -= rhs.resistance;

        if (this->strength > tmp.strength) this->strength = 0;
        if (this->intellect > tmp.intellect) this->intellect = 0;
        if (this->agility > tmp.agility) this->agility = 0;
        if (this->armor > tmp.armor) this->armor = 0;
        if (this->resistance > tmp.resistance) this->resistance = 0;

        return *this;
    }
};

#endif //CORE_STATS_H
