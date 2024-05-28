#include "gtest/gtest.h"

#include "player_character.h"
#include "cleric.h"
#include "rogue.h"
#include "warrior.h"
#include "wizard.h"

TEST(PlayerClassSuiteTest, RogueClass)
{
    const PlayerCharacter rogue(new Rogue());
    EXPECT_EQ(rogue.get_current_hp(), Rogue::kBaseHp);
    EXPECT_EQ(rogue.get_current_mp(), Rogue::kBaseMp);

    rogue.gain_exp(100u);
    EXPECT_EQ(rogue.get_current_hp(), (Rogue::kBaseHp + Rogue::kBaseHp/2.f));
    EXPECT_EQ(rogue.get_level(), 2);
    EXPECT_EQ(
        std::string("Precise Attack"), rogue.get_ability_list().front().name
    );
}

TEST(PlayerClassSuiteTest, WarriorClass)
{
    const PlayerCharacter warrior(new Warrior());
    EXPECT_EQ(warrior.get_current_hp(), Warrior::kBaseHp);
    EXPECT_EQ(warrior.get_current_mp(), Warrior::kBaseMp);

    warrior.gain_exp(100u);
    EXPECT_EQ(
        warrior.get_current_hp(), (Warrior::kBaseHp + Warrior::kBaseHp/2.f)
    );
    EXPECT_EQ(warrior.get_level(), 2);
    EXPECT_EQ(
        std::string("Power Attack"),
        warrior.get_ability_list().front().name
    );
}

TEST(PlayerClassSuiteTest, WizardClass)
{
    const PlayerCharacter wizard(new Wizard());
    EXPECT_EQ(wizard.get_current_hp(), Wizard::kBaseHp);
    EXPECT_EQ(wizard.get_current_mp(), Wizard::kBaseMp);

    wizard.gain_exp(100u);
    EXPECT_EQ(
        wizard.get_current_hp(), (Wizard::kBaseHp + Wizard::kBaseHp/2.f)
    );
    EXPECT_EQ(wizard.get_level(), 2);
    EXPECT_EQ(
        std::string("IceBolt"),
        wizard.get_ability_list().front().name
    );
}

TEST(PlayerClassSuiteTest, ClericClass)
{
    const PlayerCharacter cleric(new Cleric());
    EXPECT_EQ(cleric.get_current_hp(), Cleric::kBaseHp);
    EXPECT_EQ(cleric.get_current_mp(), Cleric::kBaseMp);
    EXPECT_EQ(std::string("Heal"), cleric.get_ability_list().front().name);

    cleric.gain_exp(100u);
    EXPECT_EQ(
        cleric.get_current_hp(),
        static_cast<int>(Cleric::kBaseHp + Cleric::kBaseHp / 2.f)
    );
    EXPECT_EQ(cleric.get_level(), 2);
    EXPECT_EQ(std::string("Smite"), cleric.get_ability_list()[1].name);
}
