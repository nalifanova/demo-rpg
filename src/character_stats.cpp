#include "headers/character_stats.h"

CharacterStats::CharacterStats(
    const stattype strength,
    const stattype intellect,
    const stattype agility,
    const stattype armor,
    const stattype resistance
)
{
    base = {strength, intellect, agility, armor, resistance};
}

[[nodiscard]] stattype CharacterStats::get_strength() const
{
    return static_cast<stattype>(base.strength + m_buffed.strength);
}

[[nodiscard]] stattype CharacterStats::get_intellect() const
{
    return static_cast<stattype>(base.intellect + m_buffed.intellect);
}

[[nodiscard]] stattype CharacterStats::get_agility() const
{
    return static_cast<stattype>(base.agility + m_buffed.agility);
}

[[nodiscard]] stattype CharacterStats::get_armor() const
{
    return static_cast<stattype>(base.armor + m_buffed.armor);
}

[[nodiscard]] stattype CharacterStats::get_resistance() const
{
    return static_cast<stattype>(base.resistance + m_buffed.resistance);
}

[[nodiscard]] stattype CharacterStats::get_base_strength() const
{
    return base.strength;
}

[[nodiscard]] stattype CharacterStats::get_base_intellect() const
{
    return base.intellect;
}

[[nodiscard]] stattype CharacterStats::get_base_agility() const
{
    return base.agility;
}

[[nodiscard]] stattype CharacterStats::get_base_armor() const
{
    return base.armor;
}

[[nodiscard]] stattype CharacterStats::get_base_resistance() const
{
    return base.resistance;
}

// PROTECTED
void CharacterStats::increase_stats(const CoreStats core_stats)
{
    base += core_stats;
}

void CharacterStats::add_new_buff(const Buff& buff)
{
    for (auto& buff_: Buffs)
    {
        if (buff.name == buff_.name)
            buff_.duration = buff.duration;
    }
    Buffs.push_back(buff);
    m_recalculate_buff();
}

// PRIVATE
void CharacterStats::m_recalculate_buff()
{
    CoreStats with_buffs;

    for (const auto& buff_: Buffs)
    {
        if (buff_.is_debuff)
            with_buffs -= buff_.stats;
        else
            with_buffs += buff_.stats;
    }
    m_buffed = with_buffs;
}
