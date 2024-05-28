#ifndef ITEM_H
#define ITEM_H

#include <utility>

#include "buff.h"
#include "core_stats.h"

class ItemDelegate
{
public:
    std::string name;

protected:
    // for some reason virtual is protected
    virtual ~ItemDelegate() = default;
    explicit ItemDelegate(std::string name): name(std::move(name)) {}

    friend class Item;
};

class EquipmentDelegate: public ItemDelegate
{
public:
    ~EquipmentDelegate() override = default;

    [[nodiscard]] CoreStats get_stats() const;

protected:
    EquipmentDelegate(std::string name, CoreStats stats);

public:
    const std::uint32_t unique_id;

private:
    CoreStats m_stats;
};

class Item final
{
public:
    [[nodiscard]] ItemDelegate* get_data() const;

    [[nodiscard]] bool get_marked_for_deletion() const;

    void mark_for_deletion() const;

private:
    explicit Item(ItemDelegate* item): m_data(item) {}

    ~Item() // only ItemManager can clean this up
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
    // friend std::ostream& operator<<(std::ostream& os, const Item& t)
    // {
    //     if (const auto* tmp_cast1 = dynamic_cast<Armor*>(t.get_data()))
    //         return os << tmp_cast1->name << " (Armor: " <<
    //             tmp_cast1->get_stats().armor << ')';
    //
    //     if (const auto* tmp_cast2 = dynamic_cast<Weapon*>(t.get_data()))
    //         return os << tmp_cast2->name << " (Damage: " <<
    //             tmp_cast2->get_min_damage() << '-' <<
    //             tmp_cast2->get_max_damage() << ')';
    //
    //     if (const auto* tmp_cast3 = dynamic_cast<Potion*>(t.get_data()))
    //         return os << tmp_cast3->name << '(' << tmp_cast3->quantity << ')';
    //
    //     return os;
    // }
};

#endif //ITEM_H
