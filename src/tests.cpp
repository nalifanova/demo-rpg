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

    const std::vector<PlayerCharacter> characters = {
        warrior, wizard, cleric, rogue
    };

    for (const auto& char_: characters)
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

void test_core_stats()
{
    separator(__func__, __LINE__);

    CoreStats core_stats = {22, 24, 10, 1, 10};
    std::cout << "Core Stats:\n" << "\tstrength: " <<
        core_stats.strength << '\n' << "\tintellect: " <<
        core_stats.intellect << '\n' << "\tagility: " <<
        core_stats.agility << '\n' << "\tarmor: " <<
        core_stats.armor << '\n' << "\tresistance: " <<
        core_stats.resistance << '\n';

    std::cout << "\nAdd intellect and agility +2\n";
    core_stats.agility += 2;
    core_stats.intellect += 2;

    std::cout << "Updated Core Stats:\n" << "\tstrength: " <<
        core_stats.strength << '\n' << "\tintellect: " <<
        core_stats.intellect << '\n' << "\tagility: " <<
        core_stats.agility << '\n' << "\tarmor: " <<
        core_stats.armor << '\n' << "\tresistance: " <<
        core_stats.resistance << '\n';
}

void test_equipment()
{
    separator(__func__, __LINE__);

    PlayerCharacter warrior(new Warrior());
    show_stats(warrior);
    { // just a code block
        CoreStats plate_armor_stats;
        plate_armor_stats.armor = 5;
        plate_armor_stats.resistance = 5;

        const auto full_plate_armor = new Armor(
            "Shiny Plate Armor",
            plate_armor_stats,
            ArmorSlot::chest
        );
        if(warrior.equip(full_plate_armor))
        {
            std::cout << "equip success!\n";
        }
        else
        {
            std::cout << "equip failed!\n";
        }
    } // end of code block

    { // just a code block
        CoreStats leather_helmet_stats;
        leather_helmet_stats.armor = 3;
        leather_helmet_stats.resistance = 2;

        const auto leather_helmet_armor = new Armor(
            "Leather Helmet",
            leather_helmet_stats,
            ArmorSlot::helmet
        );
        if(warrior.equip(leather_helmet_armor))
        {
            std::cout << "equip success!\n";
        }
        else
        {
            std::cout << "equip failed!\n";
        }
    } // end of code block

    std::cout << "Armor\n";

    for (int i = 0; i < static_cast<int>(ArmorSlot::num_slots); i++)
    {
        if (const Armor* tmp = dynamic_cast<Armor*>(
            warrior.get_equipped_armor_at(i))
        )
            std::cout << " - " <<  tmp->name << '\n';
    }
    // checking stats
    show_stats(warrior);
}
