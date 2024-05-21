#include "item.h"

static std::uint32_t equip_iterator = 0u; // move to .cpp

EquipmentDelegate::EquipmentDelegate(
    std::string name,
    const CoreStats stats
):
ItemDelegate(std::move(name)),
m_stats(stats),
unique_id(++equip_iterator) {}
