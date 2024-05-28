#include "item_manager.h"

[[nodiscard]] Item* ItemManager::create_armor(
    std::string name,
    const CoreStats core_stats,
    const ArmorSlot slot
)
{
    return new Item(new Armor(name, core_stats, slot));
}

// out will be nullptr if this cast fails
void ItemManager::cast_item_to_armor(const Item* in, Armor*& out)
{
    out = dynamic_cast<Armor*>(in->get_data());
}

bool ItemManager::is_item_armor(const Item* in)
{
    if (dynamic_cast<Armor*>(in->get_data())) return true;
    return false;
}

Item* ItemManager::create_weapon(
    std::string name,
    const CoreStats core_stats,
    const WeaponSlot slot,
    const damagetype min_damage,
    const damagetype max_damage,
    const bool is_2handed
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

// out will be nullptr if this cast fails
void ItemManager::cast_item_to_weapon(const Item* in, Weapon*& out)
{
    out = dynamic_cast<Weapon*>(in->get_data());
}

bool ItemManager::is_item_weapon(const Item* in)
{
    if (dynamic_cast<Weapon*>(in->get_data())) return true;
    return false;
}

Item* ItemManager::create_potion(
    std::string name,
    const pointtype heal,
    const itemcount quantity,
    Buff* buff
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

// out will be nullptr if this cast fails
void ItemManager::cast_item_to_potion(const Item* in, Potion*& out)
{
    out = dynamic_cast<Potion*>(in->get_data());
}

bool ItemManager::is_item_potion(const Item* in)
{
    if (dynamic_cast<Potion*>(in->get_data())) return true;
    return false;
}

// modify when we have an inventory
bool ItemManager::equip(Item* item_to_equip, PlayerCharacter* p_player)
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
    // if item fails to equip, move it to the backback
    move_to_backpack(item_to_equip, p_player);
    return false;
}

bool ItemManager::use(const Item* item_to_use, PlayerCharacter* p_player)
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

bool ItemManager::move_to_backpack(
    Item* item_to_move,
    PlayerCharacter* p_player
)
{
    if (!p_player || !item_to_move || !item_to_move->get_data())
        return false;

    p_player->add_to_backpack(item_to_move);
    return true;
}

void ItemManager::delete_item(Item*& item_to_delete)
{
    delete item_to_delete;
    item_to_delete = nullptr;
}
