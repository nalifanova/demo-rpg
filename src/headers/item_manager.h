#ifndef ITEM_MANAGER_H
#define ITEM_MANAGER_H

#include <utility>

#include "core_stats.h"
#include "item.h"

class ItemManager
{
public:
    static Item* create_armor(
        std::string name,
        const CoreStats core_stats,
        const ArmorSlot slot
    )
    {
        return new Item(new Armor(name, core_stats, slot));
    }

    static Item* create_weapon(
        std::string name,
        const CoreStats core_stats,
        const WeaponSlot slot,
        const damagetype min,
        const damagetype max,
        const bool is_2handed
    )
    {
        return new Item(
            new Weapon(name, core_stats, slot, min, max, is_2handed)
        );
    }

    static Item* create_potion(
        std::string name,
        const pointtype heal = 1u,
        const itemcount quantity = 1u,
        Buff* buff = nullptr
    )
    {
        return new Item(
            new Potion(
                std::move(name),
                heal,
                (quantity == 0) ? 1 : quantity,
                buff
            )
        );
    }

    // void cast_item_to_armor(const Item* in, Armor*& out)
    // {
    //     if (!in) return;
    //
    //     out = static_cast<Armor*>(in->get_data());
    // }

};

#endif //ITEM_MANAGER_H
