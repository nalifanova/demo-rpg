#ifndef WARRIOR_H
#define WARRIOR_H

#include "character.h"
#include "stat_block.h"

class Warrior final: public Character, public StatBlock
{
public:
    static constexpr hptype hp_growth = 20u;
    static constexpr stattype base_str = 4u;
    static constexpr stattype base_int = 1u;

    Warrior(): Character(
        hp_growth,
        hp_growth,
        base_str,
        base_int
    ), StatBlock()
    {
        name = __func__;
    }

private:
};

#endif //WARRIOR_H
