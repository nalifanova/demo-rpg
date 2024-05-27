#ifndef ITEM_MANAGER_H
#define ITEM_MANAGER_H

#include <utility>

#include "core_stats.h"
#include "item.h"
#include "potion.h"
#include "player_character.h"

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
        const damagetype min_damage,
        const damagetype max_damage,
        const bool is_2handed = false
    )
    {
        return new Item(
            new Weapon(
                name,
                core_stats,
                slot,
                min_damage,
                max_damage,
                is_2handed
            )
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

    // modify when we have an inventory
    static bool equip(
        Item* item_to_equip,
        PlayerCharacter* p_player
    )
    {
        if (!p_player || !item_to_equip || !item_to_equip->get_data())
            return false;

        if (const auto* armor = dynamic_cast<Armor*>(item_to_equip->get_data()))
        {
            const auto slot_num = static_cast<int>(armor->get_slot());
            if (p_player->m_equipped_armors[slot_num])
            {
                move_to_backpack(
                    p_player->m_equipped_armors[slot_num],
                    p_player
                );
            }
            p_player->m_equipped_armors[slot_num] = item_to_equip;
            return true;
        }

        if (const auto* weapon = dynamic_cast<Weapon*>(item_to_equip->get_data()))
        {
            const auto slot_num = static_cast<unsigned int>(weapon->get_slot());
            if (p_player->m_equipped_weapons[slot_num])
            {
                move_to_backpack(
                    p_player->m_equipped_weapons[slot_num],
                    p_player
                );
                p_player->m_equipped_weapons[slot_num] = nullptr;
            }
            p_player->m_equipped_weapons[slot_num] = item_to_equip;

            return true;
        }
        return false;
    }

    static bool use(const Item* item_to_use, PlayerCharacter* p_player)
    {
        if (!p_player || !item_to_use || !item_to_use->get_data())
            return false;

        if (auto* potion = dynamic_cast<Potion*>(item_to_use->get_data()))
        {
            // apply buff if it has one
            if (potion->buff)
                p_player->apply_buff(*potion->buff);

            // if max health and trying to use a heal potion, don't use it
            if (p_player->m_player_class->hp->is_full() && !potion->buff)
                return false; // don't use the potion

            // increase hp by the heal amount (could be 0 and that's fine)
            p_player->m_player_class->hp->increase(potion->heal_amount);
            // we used the potion, reduce quantity
            potion->quantity--;

            if (potion->quantity == 0)
            {
                item_to_use->mark_for_deletion();
                p_player->cleanup_backpack();
            }
            return true;
        }
        return false;
    }

    static bool move_to_backpack(Item* item_to_move, PlayerCharacter* p_player)
    {
        if (!p_player || !item_to_move || !item_to_move->get_data())
            return false;

        p_player->add_to_backpack(item_to_move);
        return true;
    }

    // void cast_item_to_armor(const Item* in, Armor*& out)
    // {
    //     if (!in) return;
    //
    //     out = static_cast<Armor*>(in->get_data());
    // }

};

#endif //ITEM_MANAGER_H
