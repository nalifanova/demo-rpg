#ifndef WIZARD_H
#define WIZARD_H

#include "character.h"
#include "level_system.h"

class Wizard final: public Character, public LevelSystem
{
public:
    static constexpr hptype base_hp = 10u;
    static constexpr stattype base_str = 1u;
    static constexpr stattype base_int = 4u;

    static constexpr hptype hp_growth = 5u;
    static constexpr stattype strength_growth = 1u;
    static constexpr stattype intellect_growth = 3u;

    Wizard(): Character(base_hp, base_str, base_int)
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

#endif //WIZARD_H
