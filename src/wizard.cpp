#include "wizard.h"

Wizard::Wizard(): PlayerCharacterDelegate(
    kBaseHp,
    kBaseMp,
    kBaseStr,
    kBaseInt,
    kBaseAgl,
    0,
    0
)
{
    class_name = __func__;
    abilities.emplace_back(
        "IceBolt",
        4u,
        nullptr,
        2u,
        1u,
        AbilityTarget::enemy,
        AbilityScaler::intellect
    );
}

// PRIVATE
void Wizard::level_up()
{
    PlayerCharacterDelegate::level_up();
    if (current_level == 2)
    {
        abilities.emplace_back(
            "IceBolt",
            6u,
            nullptr,
            3u,
            1u,
            AbilityTarget::enemy,
            AbilityScaler::intellect
        );

        mp->set_max(1u + mp->get_initial());
        mp->increase(1u);

        increase_stats(0, 1);
    }
}
