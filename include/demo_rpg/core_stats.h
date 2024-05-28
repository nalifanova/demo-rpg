#ifndef CORE_STATS_H
#define CORE_STATS_H

#include "types.h"

// We do get rid of huge pieces of duplications
struct CoreStats
{
    CoreStats();

    CoreStats(
        stattype strength,
        stattype intellect,
        stattype agility,
        stattype armor,
        stattype resistance
    );

    explicit CoreStats(stattype all);

    // return by _reference_
    CoreStats& operator+=(const CoreStats& rhs); // rhs = right hand side

    CoreStats& operator-=(const CoreStats& rhs); // rhs = right hand side

    CoreStats& operator=(const CoreStats& rhs);

    stattype strength;
    stattype intellect;
    stattype agility;
    stattype armor;
    stattype resistance;
};

#endif //CORE_STATS_H
