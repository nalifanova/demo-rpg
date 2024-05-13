#ifndef WIZARD_H
#define WIZARD_H

#include "character.h"
#include "stat_block.h"

class Wizard final: public Character, public StatBlock
{
public:
    static constexpr hptype hp_growth = 10u;
    static constexpr stattype base_str = 1u;
    static constexpr stattype base_int = 4u;

    Wizard(): Character(
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

#endif //WIZARD_H
