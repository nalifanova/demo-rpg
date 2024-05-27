#include "headers/buff.h"

Buff::Buff()
{
    name = "undefined";
    duration = 2u;
    stats = CoreStats();
    is_debuff = false;
}

Buff::Buff (
    const char* name,
    const uint16_t duration,
    const CoreStats stats,
    const bool is_debuff
): name(name), duration(duration), stats(stats), is_debuff(is_debuff) {}

Buff::Buff(
    const char* name,
    const uint16_t duration,
    const stattype strength,
    const stattype intellect,
    const stattype agility,
    const stattype armor,
    const stattype resistance,
    const bool is_debuff
):
name(name),
duration(duration),
stats({strength, intellect, agility, armor, resistance}),
is_debuff(is_debuff) {}

Buff& Buff::operator=(const char* name)
{
    this->name = std::string(name);
    this->duration = 2u;
    this->stats = CoreStats(0);
    this->is_debuff = false;
    return *this;
}
