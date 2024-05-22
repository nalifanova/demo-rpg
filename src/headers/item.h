#ifndef ITEM_H
#define ITEM_H

#include <utility>

#include "buff.h"
#include "core_stats.h"

#define GET_TYPE const char* get_type() override {return typeid(*this).name();};

class ItemDelegate
{
public:
    std::string name;
    virtual const char* get_type() = 0;
    virtual ~ItemDelegate() = default;
protected:
    // for some reason virtual is protected
    explicit ItemDelegate(std::string name): name(std::move(name)) {}

    friend class Item;
};

class EquipmentDelegate: public ItemDelegate
{
public:
    ~EquipmentDelegate() override = default;

    [[nodiscard]] CoreStats get_stats() const
    {
        return m_stats;
    }

protected:
    EquipmentDelegate(std::string name, CoreStats stats);

public:
    const std::uint32_t unique_id;

private:
    CoreStats m_stats;
};

// ------------------ from Equipment
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

class Armor final: public EquipmentDelegate
{
public:
    Armor() = delete; // can't create an armor w/o parameters

    Armor(const Armor&) = delete; // can't copy armor

    Armor(const Armor&&) = delete; // can't move armor

    Armor(const std::string& name, const CoreStats stats, const ArmorSlot slot):
    EquipmentDelegate(name, stats), m_slot(slot) {}

    GET_TYPE

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
    friend class ItemManager;
};

class Weapon final: public EquipmentDelegate
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
    EquipmentDelegate(name, stats),
    m_slot(slot),
    m_min_damage(min),
    m_max_damage(max),
    is_2handed(is_2handed){}

    GET_TYPE

    // getters
    [[nodiscard]] WeaponSlot get_slot() const
    {
        return m_slot;
    }

    [[nodiscard]] damagetype get_min_damage() const
    {
        return m_min_damage;
    }

    [[nodiscard]] damagetype get_max_damage() const
    {
        return m_max_damage;
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

    friend class ItemManager;
};

class Potion final: public ItemDelegate
{
public:
    ~Potion() override
    {
        if (buff)
        {
            delete buff;
            buff = nullptr;
        }
    }
    GET_TYPE

private:
    explicit Potion(
        const std::string name,
        const pointtype hp_heal = 1u,
        const itemcount quantity = 1u,
        Buff* buff = nullptr
    ):
    ItemDelegate(name), buff(buff), heal_amount(hp_heal), quantity(quantity){}

public:
    Buff* buff;
    pointtype heal_amount;
    itemcount quantity;

private:
    friend class ItemManager;
};

class Item final
{
public:
    [[nodiscard]] ItemDelegate* get_data() const
    {
        return m_data;
    }

    [[nodiscard]] bool get_marked_for_deletion() const
    {
        return m_marked_for_deletion;
    }

    void mark_for_deletion() const
    {
        m_marked_for_deletion = true;
    }

private:
    explicit Item(ItemDelegate* item): m_data(item) {}

    ~Item()
    {
        if (m_data)
        {
            delete m_data;
            m_data = nullptr;
        }
    }

    friend class ItemManager;
    ItemDelegate* m_data = nullptr;
    mutable bool m_marked_for_deletion = false;

    friend class ItemManager;
    friend class PlayerCharacter;

    // nice methods
    friend std::ostream& operator<<(std::ostream& os, const Item& t)
    {
        if (const auto* tmp_cast1 = dynamic_cast<Armor*>(t.get_data()))
            return os << tmp_cast1->name << " (Armor: " <<
                tmp_cast1->get_stats().armor << ')';

        if (const auto* tmp_cast2 = dynamic_cast<Weapon*>(t.get_data()))
            return os << tmp_cast2->name << " (Damage: " <<
                tmp_cast2->get_min_damage() << '-' <<
                tmp_cast2->get_max_damage() << ')';

        if (const auto* tmp_cast3 = dynamic_cast<Potion*>(t.get_data()))
            return os << tmp_cast3->name << '(' << tmp_cast3->quantity << ')';

        return os;
    }
};

#endif //ITEM_H
