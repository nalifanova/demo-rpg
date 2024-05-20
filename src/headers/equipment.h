#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <iostream>

#include "core_stats.h"
#include "types.h"

enum class ArmorSlot
{
    helmet,
    chest,
    gloves,
    legs,
    boots,
    ring1,
    ring2,
    neck,
    num_slots // to let compiler know the size of array
};

enum class ArmorType {heavy, medium, light, num_slots};

enum class WeaponSlot {melee, ranged, num_slots};

class Equipment
{
public:
    virtual const char* get_type() = 0;

    [[nodiscard]] std::string get_name() const
    {
        return m_name;
    }

    [[nodiscard]] CoreStats get_stats() const
    {
        return m_stats;
    }

protected:
    Equipment(std::string name, const CoreStats core_stats):
    m_name(std::move(name)), m_stats(core_stats) {}

    virtual ~Equipment() = default;

private:
    std::string m_name;
    CoreStats m_stats;
};

class Armor final: public Equipment
{
public:
    Armor() = delete; // can't create an armor w/o parameters

    Armor(const Armor&) = delete; // can't copy armor

    Armor(const Armor&&) = delete; // can't move armor

    Armor(const std::string& name, const CoreStats stats, const ArmorSlot slot):
    Equipment(name, stats), m_slot(slot){}

    ~Armor() override = default;

    const char* get_type() override { return typeid(*this).name(); }

    // getters
    [[nodiscard]] ArmorSlot get_slot() const
    {
        return m_slot;
    }

    // setters
    void set_slot(const ArmorSlot* armor)
    {
        m_slot = *armor;
    }

private:
    ArmorSlot m_slot;
};

class Weapon final: public Equipment
{
public:
    Weapon() = delete; // can't create an armor w/o parameters

    Weapon(const Weapon&) = delete; // can't copy armor

    Weapon(const Weapon&&) = delete; // can't move armor

    Weapon(
        const std::string& name,
        const CoreStats stats,
        const WeaponSlot slot,
        const damagetype min,
        const damagetype max,
        const bool is_2handed = false
    ):
    Equipment(name, stats),
    m_slot(slot),
    m_min_damage(min),
    m_max_damage(max),
    is_2handed(is_2handed){}

    ~Weapon() override = default;

    const char* get_type() override { return typeid(*this).name(); }

    // getters
    [[nodiscard]] WeaponSlot get_slot() const
    {
        return m_slot;
    }

    // setters
    void set_slot(const WeaponSlot* weapon)
    {
        m_slot = *weapon;
    }

private:
    WeaponSlot m_slot;
    damagetype m_min_damage;
    damagetype m_max_damage;
    bool is_2handed = false;
};

#endif //EQUIPMENT_H
