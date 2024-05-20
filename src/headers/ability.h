#ifndef ABILITY_H
#define ABILITY_H

#include <iostream>

enum class AbilityTarget{self, ally, enemy};
enum class AbilityScaler{none, strength, agility, intellect};

struct Ability
{
    Ability(
        std::string name,
        const uint32_t cost,
        const uint32_t cooldown,
        const AbilityTarget target,
        const uint32_t hp_effect,
        const AbilityScaler scaler
    ):
    name(std::move(name)),
    cost(cost),
    cooldown(cooldown),
    target(target),
    hp_effect(hp_effect),
    scaler(scaler)
    {}

    std::string name = "unnamed";
    uint32_t cost = 0; // assume mp if there is a cost
    // number of rounds you have to wait befire using it again
    uint32_t cooldown = 1;
    AbilityTarget target = AbilityTarget::self;
    uint32_t hp_effect = 1;
    AbilityScaler scaler = AbilityScaler::none;
};

#endif //ABILITY_H
