#ifndef ROGUE_H
#define ROGUE_H

#include "character.h"
#include "level_system.h"

class Rogue final: public Character, public LevelSystem
{
public:
    static constexpr hptype base_hp = 12u;
    static constexpr stattype base_str = 3u;
    static constexpr stattype base_int = 2u;

    static constexpr hptype hp_growth = 6u;
    static constexpr stattype strength_growth = 2u;
    static constexpr stattype intellect_growth = 1u;

    Rogue(): Character(base_hp, base_str, base_int)
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

#endif //ROGUE_H
