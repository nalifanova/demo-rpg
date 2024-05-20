#include "headers/tests.h"

#include <vector>

#include "headers/player_classes.h"

void separator(const std::string& func_name, const int& line)
{
    std::cout << std::string(10, '-') << ' ' <<
        func_name << " - line [" << line - 2 << "] " <<
        std::string(30, '-') << '\n';
}

void show_stats(const PlayerCharacter& char_)
{
    const std::string title =
            std::string(char_.get_class_name()) + " (level: " +
            std::to_string(char_.get_level()) + ", exp: " +
            std::to_string(char_.get_current_exp()) + "/" +
            std::to_string(char_.get_exp_to_next_level()) + "):";

    std::cout << title << '\n' <<
    "-HP: " << char_.get_current_hp() << '\n' <<
    "-MP: " << char_.get_current_mp() << '\n' <<
    "-Strength: " << char_.get_strength() << '\n' <<
    "-Intellect: " << char_.get_intellect() << '\n' <<
    "-Agility: " << char_.get_agility() << '\n' <<
    "-Armor: " << char_.get_armor() << '\n' <<
    "-Resistance: " << char_.get_resistance() << '\n';
    std::cout << '\n';
}

void show_abilities(const PlayerCharacter& char_)
{
    const auto all_abilities = char_.get_ability_list();

    std::cout << "-Abilities:\n";
    for (auto& ability: all_abilities)
    {
        std::cout << " -" << ability.name << '\n';
    }
    std::cout << '\n';
}

void test_characters()
{
    separator(__func__, __LINE__);

    const auto warrior = PlayerCharacter(new Warrior());
    const PlayerCharacter wizard(new Wizard());
    const PlayerCharacter cleric(new Cleric());
    const PlayerCharacter rogue(new Rogue());

    const std::vector<PlayerCharacter> charachters = {
        warrior, wizard, cleric, rogue
    };

    for (const auto& char_: charachters)
    {
        show_stats(char_);
        std::cout << '\n';
    }
}

void test_level_up()
{
    separator(__func__, __LINE__);

    const PlayerCharacter cleric(new Cleric());
    for (int i = 0; i <= 4; i++)
    {
        show_stats(cleric);
        show_abilities(cleric);
        cleric.gain_exp(100);
    }
}

void test_buff()
{
    separator(__func__, __LINE__);

    const PlayerCharacter warrior(new Warrior());
    for (int i = 0; i <= 1; i++)
    {
        show_stats(warrior);
        show_abilities(warrior);
        warrior.gain_exp(100);

        if (i < 1)
        {
            warrior.gain_exp(100u);
            const Buff armor_buff(
                "Stone Shield",
                10,
                0,
                0,
                0,
                5
            );
            warrior.apply_buff(armor_buff);
        }
    }
}
