#ifndef ROGUE_H
#define ROGUE_H

#include "character.h"
#include "stat_block.h"

class Rogue final: public Character, public StatBlock
{
public:
    static constexpr hptype hp_growth = 14u;
    static constexpr stattype base_str = 5u;
    static constexpr stattype base_int = 2u;

    Rogue(): Character(
        hp_growth,
        hp_growth,
        base_str,
        base_int
    )
    {
        name = __func__;
    }

private:
};

#endif //ROGUE_H
