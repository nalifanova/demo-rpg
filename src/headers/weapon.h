#ifndef WEAPON_H
#define WEAPON_H

#include "item.h"

enum class WeaponSlot {melee, ranged, num_slots};

class Weapon final: public EquipmentDelegate
{
public:
    Weapon() = delete; // can't create an armor w/o parameters

    Weapon(const Weapon&) = delete; // can't copy armor

    Weapon(const Weapon&&) = delete; // can't move armor

    Weapon(
        const std::string& name,
        CoreStats stats,
        WeaponSlot slot,
        damagetype min,
        damagetype max,
        bool is_2handed = false
    );

    // getters
    [[nodiscard]] WeaponSlot get_slot() const;

    [[nodiscard]] damagetype get_min_damage() const;

    [[nodiscard]] damagetype get_max_damage() const;

    // setters
    void set_slot(const WeaponSlot* weapon);

    [[nodiscard]] bool is_two_handed() const;

private:
    WeaponSlot m_slot;
    damagetype m_min_damage;
    damagetype m_max_damage;
    bool is_2handed;

    friend class ItemManager;
};

#endif //WEAPON_H
