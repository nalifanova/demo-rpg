#include "gtest/gtest.h"

#include "item_manager.h"
#include "monster.h"
#include "player_character.h"
#include "rogue.h"

TEST(MonsterBattleSuiteTest, MonsterClass)
{
    const Monster monster(10, 2, 4);

    ASSERT_EQ(monster.hp.get_current(), 10);
    ASSERT_EQ(monster.get_min_damage(), 2);
    ASSERT_EQ(monster.get_max_damage(), 4);

    int rand_damage = 0;
    for (int i = 0; i < 10; ++i)
    {
        rand_damage = monster.attack();
        ASSERT_TRUE(rand_damage >= static_cast<int>(monster.get_min_damage()));
        ASSERT_TRUE(rand_damage <= static_cast<int>(monster.get_max_damage()));
    }
}

TEST(MonsterBattleSuiteTest, SimpleBattle)
{
    PlayerCharacter rogue(new Rogue());
    auto* weapon = ItemManager::create_weapon(
        "Dagger",
        CoreStats(),
        WeaponSlot::melee,
        1,
        3,
        false
    );
    ASSERT_TRUE(ItemManager::equip(weapon, &rogue));

    Monster monster(10, 1, 5);

    while(monster.hp.get_current() > 0 && rogue.get_current_hp() > 0)
    {
        monster.hp.reduce(rogue.melee_attack());
        rogue.take_damage(monster.attack());
    }
    ASSERT_TRUE(monster.hp.get_current() == 0 || rogue.get_current_hp() == 0);
}
