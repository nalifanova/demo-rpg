#include "gtest/gtest.h"

#include "ability.h"
#include "buff.h"
#include "core_stats.h"

TEST(CoreCharacteristicsSuiteTest, AbilityClass_default)
{
    const Ability ability;
    EXPECT_EQ(ability.name, std::string("unnamed"));
    EXPECT_EQ(ability.hp_effect, 1u);
    EXPECT_TRUE(ability.given_buff == nullptr);
    EXPECT_EQ(ability.cost, 0u);
    EXPECT_EQ(ability.cooldown, 1u);
    EXPECT_EQ(ability.target, AbilityTarget::self);
    EXPECT_EQ(ability.scaler, AbilityScaler::none);
}

TEST(CoreCharacteristicsSuiteTest, AbilityClass_custom)
{
    const Ability ability(
        "custom_name", 1,
        new Buff("Super Buff", 5, 1, 1, 1, 1, 1, false),
        2, 3, AbilityTarget::enemy, AbilityScaler::intellect);
    EXPECT_EQ(ability.name, std::string("custom_name"));
    EXPECT_EQ(ability.hp_effect, 1u);
    EXPECT_TRUE(ability.given_buff != nullptr);
    EXPECT_EQ(ability.cost, 2u);
    EXPECT_EQ(ability.cooldown, 3u);
    EXPECT_EQ(ability.target, AbilityTarget::enemy);
    EXPECT_EQ(ability.scaler, AbilityScaler::intellect);
    EXPECT_EQ(ability.given_buff->name, "Super Buff");
}

TEST(CoreCharacteristicsSuiteTest, BuffClass_default)
{
    const Buff buff("undefined", 2u, CoreStats());
    EXPECT_EQ(buff.name, std::string("undefined"));
    EXPECT_EQ(buff.duration, 2u);
    EXPECT_EQ(buff.stats.strength, 0u);
    EXPECT_EQ(buff.stats.intellect, 0u);
    EXPECT_EQ(buff.stats.agility, 0u);
    EXPECT_EQ(buff.stats.armor, 0u);
    EXPECT_EQ(buff.stats.resistance, 0u);
    EXPECT_FALSE(buff.is_debuff);
}

TEST(CoreCharacteristicsSuiteTest, BuffClass_custom)
{
    const Buff buff("Custom Buff", 10, 9, 8, 7, 6, 5, true);
    EXPECT_EQ(buff.name, std::string("Custom Buff"));
    EXPECT_EQ(buff.duration, 10u);
    EXPECT_EQ(buff.stats.strength, 9u);
    EXPECT_EQ(buff.stats.intellect, 8u);
    EXPECT_EQ(buff.stats.agility, 7u);
    EXPECT_EQ(buff.stats.armor, 6u);
    EXPECT_EQ(buff.stats.resistance, 5u);
    EXPECT_TRUE(buff.is_debuff);
}

TEST(CoreCharacteristicsSuiteTest, CoreStatsClass)
{
    CoreStats default_stats;
    EXPECT_EQ(default_stats.strength, 0u);
    EXPECT_EQ(default_stats.intellect, 0u);
    EXPECT_EQ(default_stats.agility, 0u);
    EXPECT_EQ(default_stats.armor, 0u);
    EXPECT_EQ(default_stats.resistance, 0u);
        
    const CoreStats stats_one(4);
    EXPECT_EQ(stats_one.strength, 4u);
    EXPECT_EQ(stats_one.intellect, 4u);
    EXPECT_EQ(stats_one.agility, 4u);
    EXPECT_EQ(stats_one.armor, 4u);
    EXPECT_EQ(stats_one.resistance, 4u);

    const CoreStats stats_two(1, 2, 3, 4, 5);
    EXPECT_EQ(stats_two.strength, 1u);
    EXPECT_EQ(stats_two.intellect, 2u);
    EXPECT_EQ(stats_two.agility, 3u);
    EXPECT_EQ(stats_two.armor, 4u);
    EXPECT_EQ(stats_two.resistance, 5u);
    
    default_stats += stats_one;
    EXPECT_EQ(default_stats.strength, 4u);
    EXPECT_EQ(default_stats.intellect, 4u);
    EXPECT_EQ(default_stats.agility, 4u);
    EXPECT_EQ(default_stats.armor, 4u);
    EXPECT_EQ(default_stats.resistance, 4u);

    default_stats -= stats_two;
    EXPECT_EQ(default_stats.strength, 3u);
    EXPECT_EQ(default_stats.intellect, 2u);
    EXPECT_EQ(default_stats.agility, 1u);
    EXPECT_EQ(default_stats.armor, 0u);
    EXPECT_EQ(default_stats.resistance, 0u);

    default_stats = stats_two;
    EXPECT_EQ(default_stats.strength, 1u);
    EXPECT_EQ(default_stats.intellect, 2u);
    EXPECT_EQ(default_stats.agility, 3u);
    EXPECT_EQ(default_stats.armor, 4u);
    EXPECT_EQ(default_stats.resistance, 5u);
}
