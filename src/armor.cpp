#include "headers/armor.h"

Armor::Armor(
    const std::string& name,
    const CoreStats stats,
    const ArmorSlot slot
):
EquipmentDelegate(name, stats), m_slot(slot) {}

// getters
[[nodiscard]] ArmorSlot Armor::get_slot() const
{
    return m_slot;
}

// setters
void Armor::set_slot(const ArmorSlot* armor)
{
    m_slot = *armor;
}