#ifndef ABILITY_H
#define ABILITY_H

#include <iostream>

#include "buff.h"

enum class AbilityTarget{self, ally, enemy};
enum class AbilityScaler{none, strength, agility, intellect};

struct Ability
{
    explicit Ability(
        std::string name = "unnamed",
        uint32_t hp_effect = 1u,
        Buff* buff = nullptr,
        uint32_t cost = 0u,
        uint32_t cooldown = 1u,
        AbilityTarget target = AbilityTarget::self,
        AbilityScaler scaler = AbilityScaler::none
    );

    ~Ability();

    std::string name;
    Buff* given_buff;
    uint32_t cost; // assume mp if there is a cost
    // number of rounds you have to wait befire using it again
    uint32_t cooldown;
    uint32_t hp_effect;
    AbilityTarget target = AbilityTarget::self;
    AbilityScaler scaler = AbilityScaler::none;
};

#endif //ABILITY_H
