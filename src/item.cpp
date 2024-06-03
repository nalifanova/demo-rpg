#include "item.h"

// -- EquipmentDelegate --
static std::uint32_t equip_iterator = 0u; // move to .cpp

EquipmentDelegate::EquipmentDelegate(
    std::string name,
    const CoreStats stats
):
ItemDelegate(std::move(name)),
m_stats(stats),
unique_id(++equip_iterator) {}

[[nodiscard]] CoreStats EquipmentDelegate::get_stats() const
{
    return m_stats;
}

// -- Item --
[[nodiscard]] ItemDelegate* Item::get_data() const
{
    return m_data;
}

[[nodiscard]] bool Item::get_marked_for_deletion() const
{
    return m_marked_for_deletion;
}

[[nodiscard]] bool Item::get_marked_as_backback_ref_gone() const
{
    return m_marked_as_backback_ref_gone;
}

void Item::mark_for_deletion() const
{
    m_marked_for_deletion = true;
}

void Item::mark_as_backback_ref_gone() const
{
    m_marked_as_backback_ref_gone = true;
}

void Item::remove_for_deletion() const
{
    m_marked_for_deletion = false;
}

void Item::remove_as_backback_ref_gone() const
{
    m_marked_as_backback_ref_gone = false;
}
