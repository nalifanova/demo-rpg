#include "headers/cleric.h"

Cleric::Cleric(): PlayerCharacterDelegate(
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
    abilities.emplace_back(
        "Heal",
        2u,
        nullptr,
        2u,
        1u,
        AbilityTarget::ally,
        AbilityScaler::intellect
    );
}

// PRIVATE
void Cleric::level_up()
{
    PlayerCharacterDelegate::level_up();
    if (current_level == 2)
    {
        abilities.emplace_back(
        "Smite",
        2u,
        nullptr,
        2u,
        1u,
        AbilityTarget::enemy,
        AbilityScaler::intellect
        );
    }
}
