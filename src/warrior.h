#ifndef WARRIOR_H
#define WARRIOR_H

#include "character.h"
#include "level_system.h"

class Warrior final: public Character, public LevelSystem
{
public:
    static constexpr hptype base_hp = 20u;
    static constexpr stattype base_str = 4u;
    static constexpr stattype base_int = 1u;

    static constexpr hptype hp_growth = 9u;
    static constexpr stattype strength_growth = 2u;
    static constexpr stattype intellect_growth = 1u;

    Warrior(): Character(base_hp, base_str, base_int)
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

#endif //WARRIOR_H
