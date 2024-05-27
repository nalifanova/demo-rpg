#include "headers/ability.h"

Ability::Ability(
        std::string name,
        const uint32_t hp_effect,
        Buff* buff,
        const uint32_t cost,
        const uint32_t cooldown,
        const AbilityTarget target,
        const AbilityScaler scaler
    ):
    name(std::move(name)),
    hp_effect(hp_effect),
    given_buff(buff),
    cost(cost),
    cooldown(cooldown),
    target(target),
    scaler(scaler)
{}

Ability::~Ability()
{
    if (given_buff)
    {
        delete given_buff;
        given_buff = nullptr;
    }
}
