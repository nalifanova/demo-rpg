#include "gtest/gtest.h"

#include "item.h"
#include "item_manager.h"
#include <rogue.h>

TEST(EquipPlaterSuiteTest, ItemManagerClass)
{
    PlayerCharacter rogue(new Rogue());
    // equip full set of items
    ItemManager::equip(
        ItemManager::create_weapon(
            "Dagger", CoreStats(), WeaponSlot::melee, 1, 3, false),
        &rogue
    );

    ItemManager::equip(
        ItemManager::create_weapon(
            "Bow", CoreStats(), WeaponSlot::ranged, 2, 6, true),
        &rogue
    );

    ItemManager::equip(
        ItemManager::create_armor(
            "Hat", CoreStats(0, 0, 0, 1, 1), ArmorSlot::head),
        &rogue
    );

    ItemManager::equip(
        ItemManager::create_armor(
            "Jacket", CoreStats(0, 0, 0, 5, 5), ArmorSlot::chest),
        &rogue
    );

    ItemManager::equip(
        ItemManager::create_armor(
            "Pants", CoreStats(0, 0, 0, 2, 3), ArmorSlot::legs),
        &rogue
    );

    ItemManager::equip(
        ItemManager::create_armor(
            "Ruby", CoreStats(0, 1, 2, 0, 2), ArmorSlot::ring1),
        &rogue
    );

    ASSERT_NE(rogue.get_equipped_weapon_at(static_cast<int>(WeaponSlot::melee)), nullptr);
    ASSERT_NE(rogue.get_equipped_weapon_at(static_cast<int>(WeaponSlot::ranged)), nullptr);
    ASSERT_NE(rogue.get_equipped_armor_at(static_cast<int>(ArmorSlot::head)), nullptr);
    ASSERT_NE(rogue.get_equipped_armor_at(static_cast<int>(ArmorSlot::chest)), nullptr);
    ASSERT_NE(rogue.get_equipped_armor_at(static_cast<int>(ArmorSlot::legs)), nullptr);
    ASSERT_NE(rogue.get_equipped_armor_at(static_cast<int>(ArmorSlot::ring1)), nullptr);
    ASSERT_EQ(rogue.get_equipped_armor_at(static_cast<int>(ArmorSlot::hands)), nullptr);
    ASSERT_EQ(rogue.get_equipped_armor_at(static_cast<int>(ArmorSlot::neck)), nullptr);
    ASSERT_EQ(rogue.get_equipped_armor_at(static_cast<int>(ArmorSlot::ring2)), nullptr);

    ASSERT_EQ(rogue.get_armor(), 8); // armor thanks to equipment

    // equipping a potion should fail
    const auto armor_potion = ItemManager::create_potion(
        "Armor Potion", 0, 1,
        new Buff("Shiny Armor Buff", 6, CoreStats(0, 0, 0, 5, 5), false)
    );
    ASSERT_FALSE(ItemManager::equip(armor_potion, &rogue));

    const auto backpack = rogue.get_backpack_list();
    ASSERT_EQ(backpack.size(), 0); // TODO: think of why?
}
