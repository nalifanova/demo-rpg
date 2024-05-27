#ifndef ITEM_MANAGER_H
#define ITEM_MANAGER_H

#include <utility>

#include "armor.h"
#include "core_stats.h"
#include "item.h"
#include "player_character.h"
#include "potion.h"
#include "weapon.h"

class ItemManager
{
public:
    static Item* create_armor(
        std::string name,
        CoreStats core_stats,
        ArmorSlot slot
    );

    static void cast_item_to_armor(const Item* in, Armor*& out);

    static bool is_item_armor(const Item* in);

    static Item* create_weapon(
        std::string name,
        CoreStats core_stats,
        WeaponSlot slot,
        damagetype min_damage,
        damagetype max_damage,
        bool is_2handed = false
    );

    static void cast_item_to_weapon(const Item* in, Weapon*& out);

    static bool is_item_weapon(const Item* in);

    static Item* create_potion(
        std::string name,
        pointtype heal = 1u,
        itemcount quantity = 1u,
        Buff* buff = nullptr
    );

    static void cast_item_to_potion(const Item* in, Potion*& out);

    static bool is_item_potion(const Item* in);

    // modify when we have an inventory
    static bool equip(
        Item* item_to_equip,
        PlayerCharacter* p_player
    );

    static bool use(const Item* item_to_use, PlayerCharacter* p_player);

    static bool move_to_backpack(Item* item_to_move, PlayerCharacter* p_player);

    static void delete_item(Item*& item_to_delete);
};

#endif //ITEM_MANAGER_H
