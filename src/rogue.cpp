#include "headers/rogue.h"

Rogue::Rogue(): PlayerCharacterDelegate(
    kBaseHp,
    kBaseMp,
    kbaseStr,
    kBaseInt,
    kBaseAgl,
    0,
    0
)
{
    class_name = __func__;
}

void Rogue::level_up()
{
    PlayerCharacterDelegate::level_up();

    if (current_level == 2)
    {
        abilities.emplace_back(
            "Precise Attack",
            6u,
            nullptr,
            0u,
            3u,
            AbilityTarget::enemy,
            AbilityScaler::agility
        );
    }
}
