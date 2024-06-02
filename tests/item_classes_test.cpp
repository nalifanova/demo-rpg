#include "gtest/gtest.h"

#include "core_stats.h"
#include "item_manager.h"

TEST(ItemSuiteTest, WeaponClass)
{
    const Item* magic_weapon = ItemManager::create_weapon(
        "Magic Wand", CoreStats(5), WeaponSlot::ranged, 1, 3, false
    );

    EXPECT_TRUE(magic_weapon != nullptr);
    EXPECT_TRUE(ItemManager::is_item_weapon(magic_weapon));
    EXPECT_FALSE(ItemManager::is_item_armor(magic_weapon));
    EXPECT_FALSE(ItemManager::is_item_potion(magic_weapon));

    {
        auto* weapon = dynamic_cast<const Weapon*>(magic_weapon->get_data());
        EXPECT_TRUE(weapon != nullptr); // make sure cast doesn't fail
        EXPECT_EQ(weapon->name, "Magic Wand");
        EXPECT_EQ(weapon->get_stats().strength, 5);
        EXPECT_EQ(weapon->get_stats().intellect, 5);
        EXPECT_EQ(weapon->get_stats().agility, 5);
        EXPECT_EQ(weapon->get_stats().armor, 5);
        EXPECT_EQ(weapon->get_min_damage(), 1u);
        EXPECT_EQ(weapon->get_max_damage(), 3u);
        EXPECT_FALSE(weapon->is_two_handed());
        // delete weapon; // compiler error
    }
    {
        Weapon* copied_weapon = nullptr;
        ItemManager::cast_item_to_weapon(magic_weapon, copied_weapon);
        EXPECT_NE(copied_weapon, nullptr);
        EXPECT_EQ(copied_weapon->name, "Magic Wand");
        EXPECT_EQ(copied_weapon->get_stats().strength, 5);
        EXPECT_EQ(copied_weapon->get_stats().intellect, 5);
        EXPECT_EQ(copied_weapon->get_stats().agility, 5);
        EXPECT_EQ(copied_weapon->get_stats().armor, 5);
        EXPECT_EQ(copied_weapon->get_min_damage(), 1u);
        EXPECT_EQ(copied_weapon->get_max_damage(), 3u);
        EXPECT_FALSE(copied_weapon->is_two_handed());

        // change things
        copied_weapon->name = "Corrupted Magic Wand";
        copied_weapon->set_min_damage(2);
        copied_weapon->set_max_damage(1);

        EXPECT_EQ(copied_weapon->name, "Corrupted Magic Wand");
        EXPECT_EQ(copied_weapon->get_min_damage(), 3u);
        EXPECT_EQ(copied_weapon->get_max_damage(), 4u);
    }
}

TEST(ItemSuiteTest, ArmorClass)
{
    const Item* armor_item = ItemManager::create_armor(
        "Gauntlets", CoreStats(2), ArmorSlot::hands
    );

    EXPECT_TRUE(armor_item != nullptr);
    EXPECT_FALSE(ItemManager::is_item_weapon(armor_item));
    EXPECT_TRUE(ItemManager::is_item_armor(armor_item));
    EXPECT_FALSE(ItemManager::is_item_potion(armor_item));

    {
        auto* armor = dynamic_cast<const Armor*>(armor_item->get_data());
        EXPECT_TRUE(armor != nullptr); // make sure cast doesn't fail
        EXPECT_EQ(armor->name, "Gauntlets");
        EXPECT_EQ(armor->get_stats().strength, 2);
        EXPECT_EQ(armor->get_stats().intellect, 2);
        EXPECT_EQ(armor->get_stats().agility, 2);
        EXPECT_EQ(armor->get_stats().armor, 2);
        EXPECT_EQ(armor->get_slot(), ArmorSlot::hands);
        // delete armor; // compiler error
    }
    {
        Armor* copied_armor = nullptr;
        ItemManager::cast_item_to_armor(armor_item, copied_armor);
        EXPECT_NE(copied_armor, nullptr);
        EXPECT_EQ(copied_armor->name, "Gauntlets");
        EXPECT_EQ(copied_armor->get_stats().strength, 2);
        EXPECT_EQ(copied_armor->get_stats().intellect, 2);
        EXPECT_EQ(copied_armor->get_stats().agility, 2);
        EXPECT_EQ(copied_armor->get_stats().armor, 2);
        EXPECT_EQ(copied_armor->get_slot(), ArmorSlot::hands);

        // change things
        copied_armor->name = "Corrupted Boots";
        copied_armor->set_slot(ArmorSlot::feet);

        EXPECT_EQ(copied_armor->name, "Corrupted Boots");
        EXPECT_EQ(copied_armor->get_slot(), ArmorSlot::feet);
    }
}

TEST(ItemSuiteTest, PotionClass)
{
    Item* potion_item = ItemManager::create_potion(
        "Ravage Stone Skin Potion", 2, 1, nullptr
    );

    EXPECT_TRUE(potion_item != nullptr);
    EXPECT_FALSE(ItemManager::is_item_weapon(potion_item));
    EXPECT_FALSE(ItemManager::is_item_armor(potion_item));
    EXPECT_TRUE(ItemManager::is_item_potion(potion_item));

    {
        auto* potion = dynamic_cast<const Potion*>(potion_item->get_data());
        EXPECT_TRUE(potion != nullptr); // make sure cast doesn't fail
        EXPECT_EQ(potion->name, "Ravage Stone Skin Potion");
        EXPECT_EQ(potion->heal_amount, 2);
        EXPECT_EQ(potion->quantity, 1);
        EXPECT_TRUE(potion->buff == nullptr);
        // delete potion; // compiler error
    }
    {
        Potion* casted_potion = nullptr;
        ItemManager::cast_item_to_potion(potion_item, casted_potion);
        EXPECT_NE(casted_potion, nullptr);
        EXPECT_EQ(casted_potion->name, "Ravage Stone Skin Potion");
        EXPECT_EQ(casted_potion->heal_amount, 2);
        EXPECT_EQ(casted_potion->quantity, 1);
        EXPECT_TRUE(casted_potion->buff == nullptr);

        // update potion
        auto buff = Buff("Stone Skin", 5, CoreStats(0, 0, 0, 5, 5));

        casted_potion->name = "Stone Skin Potion";
        casted_potion->heal_amount = 5;
        casted_potion->quantity = 2;
        casted_potion->buff = &buff;

        EXPECT_EQ(casted_potion->name, "Stone Skin Potion");
        EXPECT_EQ(casted_potion->heal_amount, 5);
        EXPECT_EQ(casted_potion->quantity, 2);
        EXPECT_TRUE(casted_potion->buff != nullptr);
        EXPECT_EQ(casted_potion->buff->stats.strength, 0);
        EXPECT_EQ(casted_potion->buff->stats.intellect, 0);
        EXPECT_EQ(casted_potion->buff->stats.agility, 0);
        EXPECT_EQ(casted_potion->buff->stats.armor, 5);
        EXPECT_EQ(casted_potion->buff->stats.resistance, 5);

        // turn potion to poison
        casted_potion->name = "Corrupted Skin Poison";
        casted_potion->heal_amount = 0;
        casted_potion->quantity = 1;
        casted_potion->buff = new Buff("Skin Poison", 3, CoreStats(1), true);

        EXPECT_EQ(casted_potion->name, "Corrupted Skin Poison");
        EXPECT_EQ(casted_potion->heal_amount, 0);
        EXPECT_EQ(casted_potion->quantity, 1);
        EXPECT_TRUE(casted_potion->buff != nullptr);
        EXPECT_EQ(casted_potion->buff->stats.strength, 1);
        EXPECT_EQ(casted_potion->buff->stats.intellect, 1);
        EXPECT_EQ(casted_potion->buff->stats.agility, 1);
        EXPECT_EQ(casted_potion->buff->stats.armor, 1);
        EXPECT_EQ(casted_potion->buff->stats.resistance, 1);
        EXPECT_TRUE(casted_potion->buff->is_debuff);
    }
    ItemManager::delete_item(potion_item);
    EXPECT_TRUE(potion_item == nullptr);
}
