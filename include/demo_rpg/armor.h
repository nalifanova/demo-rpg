#ifndef ARMOR_H
#define ARMOR_H

#include <iostream>

#include "core_stats.h"
#include "item.h"

enum class ArmorSlot
{
    head,
    chest,
    gloves,
    legs,
    feet,
    ring1,
    ring2,
    neck,
    num_slots // to let compiler know the size of array
};

enum class ArmorType {heavy, medium, light, num_slots};


class Armor final: public EquipmentDelegate
{
public:
    Armor() = delete; // can't create an armor w/o parameters

    Armor(const Armor&) = delete; // can't copy armor

    Armor(const Armor&&) = delete; // can't move armor

    Armor(const std::string& name, CoreStats stats, ArmorSlot slot);

    [[nodiscard]] ArmorSlot get_slot() const;

    void set_slot(ArmorSlot slot_name);

private:
    ArmorSlot m_slot;
    friend class ItemManager;
};

#endif //ARMOR_H
