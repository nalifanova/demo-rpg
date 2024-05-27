#include "headers/warrior.h"

Warrior::Warrior(): PlayerCharacterDelegate(
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

void Warrior::level_up()
{
    PlayerCharacterDelegate::level_up();
    if (current_level == 2)
    {
        abilities.emplace_back(
            "Power Attack",
            4u,
            nullptr,
            0u,
            3u,
            AbilityTarget::enemy,
            AbilityScaler::strength
        );
    }
}
