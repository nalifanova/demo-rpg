#ifndef CLERIC_H
#define CLERIC_H

#include "character.h"
#include "stat_block.h"

class Cleric final: public Character, public StatBlock
{
public:
    static constexpr hptype hp_growth = 15u;
    static constexpr stattype base_str = 2u;
    static constexpr stattype base_int = 3u;
    static constexpr stattype base_luck = 7u;

    Cleric(): Character(
        hp_growth,
        hp_growth,
        base_str,
        base_int
    ), StatBlock(base_luck, 10)
    {
        name = __func__;
    }

private:
};

#endif //CLERIC_H
