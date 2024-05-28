#include "weapon.h"

Weapon::Weapon(
    const std::string& name,
    const CoreStats stats,
    const WeaponSlot slot,
    const damagetype min,
    const damagetype max,
    const bool is_2handed
):
EquipmentDelegate(name, stats),
m_slot(slot),
m_min_damage(min),
m_max_damage(max),
is_2handed(is_2handed){}

// getters
[[nodiscard]] WeaponSlot Weapon::get_slot() const
{
    return m_slot;
}

[[nodiscard]] damagetype Weapon::get_min_damage() const
{
    return m_min_damage;
}

[[nodiscard]] damagetype Weapon::get_max_damage() const
{
    return m_max_damage;
}

// setters
void Weapon::set_slot(const WeaponSlot* weapon)
{
    m_slot = *weapon;
}

void Weapon::set_min_damage(damagetype amount)
{
    m_min_damage += amount;
}

void Weapon::set_max_damage(damagetype amount)
{
    m_max_damage += amount;
}

[[nodiscard]] bool Weapon::is_two_handed() const
{
    return is_2handed;
}
