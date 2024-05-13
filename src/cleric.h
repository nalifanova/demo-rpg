#ifndef CLERIC_H
#define CLERIC_H

#include "character.h"
#include "level_system.h"
#include "stat_block.h"

class Cleric final: public Character, public StatBlock, public LevelSystem
{
public:
    static constexpr hptype base_hp = 15u;
    static constexpr stattype base_str = 2u;
    static constexpr stattype base_int = 3u;
    static constexpr stattype base_luck = 7u;

    static constexpr hptype hp_growth = 7u;
    static constexpr stattype strength_growth = 1u;
    static constexpr stattype intellect_growth = 2u;


    Cleric():
    Character(base_hp, base_str, base_int),
    StatBlock(base_luck, 10)
    {
        name = __func__;
    }

private:
    void level_up() override
    {
        set_initial_hp(hp_growth + get_initial_hp());
        increase_stats(strength_growth, intellect_growth);
    }
};

#endif //CLERIC_H
