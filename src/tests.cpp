#include "tests.h"

#include <vector>

#include "cleric.h"
#include "item_manager.h"
#include "random.h"
#include "rogue.h"
#include "warrior.h"
#include "wizard.h"

void separator(const std::string& func_name, const int& line)
{
    std::cout << std::string(10, '-') << ' ' <<
        func_name << " - line [" << line - 2 << "] " <<
        std::string(30, '-') << '\n';
}

void show_hps(const PlayerCharacter& char_)
{
    std::cout <<  "HP: (" << std::to_string(char_.get_current_hp()) +
            "/" + std::to_string(char_.get_max_hp()) + ")\n";
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

    auto warrior = PlayerCharacter(new Warrior());
    auto wizard = PlayerCharacter(new Wizard());
    auto cleric = PlayerCharacter(new Cleric());
    auto rogue = PlayerCharacter(new Rogue());
    // PlayerCharacter rogue(new Rogue()); - gives an error

    const std::vector<PlayerCharacter*> characters = {
        &warrior, &wizard, &cleric, &rogue
    };

    for (const auto char_: characters)
    {
        show_stats(*char_);
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

    const auto full_plate_armor = ItemManager::create_armor(
        "Shiny Plate Armor",
        CoreStats(0,0,0,5, 5),
        ArmorSlot::chest
    );
    const auto leather_helmet_armor = ItemManager::create_armor(
        "Leather Helmet",
        CoreStats(0,0,0, 3, 2),
        ArmorSlot::head
    );
    Item* long_sword = ItemManager::create_weapon(
        "Long Sword",
        CoreStats(),
        WeaponSlot::melee,
        3,
        9,
        true
    );

    { // full_plate_armor code block
        if(ItemManager::equip(full_plate_armor, &warrior))
            std::cout << "Shiny Plate Armor equip success!\n";
        else
            std::cout << "Shiny Plate Armor equip failed!\n";
    } // full_plate_armor

    { // leather_helmet_armor code block
        if(ItemManager::equip(leather_helmet_armor, &warrior))
            std::cout << "Leather Helmet equip success!\n";
        else
            std::cout << "Leather Helmet equip failed!\n";
    } // leather_helmet_armor

    { // long_sword code block
        if(ItemManager::equip(long_sword, &warrior))
            std::cout << "Long Sword equip success!\n";
        else
            std::cout << "Long Sword equip failed!\n";
    } // long_sword

    std::cout << "Armor\n";

    for (int i = 0; i < static_cast<int>(ArmorSlot::num_slots); i++)
    {
        if (const Armor* armor = warrior.get_equipped_armor_at(i))
        {
            std::cout << " - " <<  armor->name <<
                " - Arm: (" << armor->get_stats().armor << "), Res: (" <<
                armor->get_stats().resistance << ")\n";
        }
    }

    std::cout << "Weapon\n";

    for (int i = 0; i < static_cast<int>(WeaponSlot::num_slots); i++)
    {
        if (const Weapon* weapon = warrior.get_equipped_weapon_at(i))
        {
            std::cout << " - " <<  weapon->name <<
            " Dmg:(" << weapon->get_min_damage() <<
            "-" << weapon->get_max_damage() << ")\n";
        }
    }

    // checking stats
    show_stats(warrior);
}

void test_potions()
{
    separator(__func__, __LINE__);

    PlayerCharacter rogue(new Rogue());

    std::cout << "HP before taking damage " << rogue.get_current_hp() << "/" <<
        rogue.get_max_hp() << '\n';
    rogue.take_damage(1);
    std::cout << "HP after taking damage " << rogue.get_current_hp() << "/" <<
        rogue.get_max_hp() << '\n';

    Item* heal_potion = ItemManager::create_potion(
        "Minor Heal Potion", 3u, 3u
    );

    ItemManager::use(heal_potion, &rogue);
    std::cout << "HP after using potion " << rogue.get_current_hp() << "/" <<
        rogue.get_max_hp() << '\n';
}

void test_inventory()
{
    separator(__func__, __LINE__);

    PlayerCharacter wizard(new Wizard());

    const auto light_armor = ItemManager::create_armor(
        "Robe of Magician",
        CoreStats(0,0,0,1, 5),
        ArmorSlot::chest
    );
    Item* magic_wand = ItemManager::create_weapon(
        "Magic Wand",
        CoreStats(),
        WeaponSlot::ranged,
        3,
        6,
        true
    );

    const auto rusty_hand_axe = ItemManager::create_weapon(
        "Rusty Hand Axe",
        CoreStats(),
        WeaponSlot::melee,
        2,
        4
    );
    ItemManager::move_to_backpack(light_armor, &wizard);
    ItemManager::move_to_backpack(magic_wand, &wizard);
    ItemManager::move_to_backpack(rusty_hand_axe, &wizard);

    Item* minor_heal_potion = ItemManager::create_potion(
        "Minor Heal Potion", 3u, 3u
    );

    Item* great_heal_potion = ItemManager::create_potion(
        "Great Heal Potion", 10u, 1u
    );
    ItemManager::move_to_backpack(minor_heal_potion, &wizard);
    ItemManager::move_to_backpack(great_heal_potion, &wizard);

    {
        const auto inventory = wizard.get_backpack_list();
        std::cout << "Inventory: ";
        for (const auto it: inventory)
            // std::cout << *it << ", ";
            std::cout << it->get_data() << ", ";
        std::cout << "\n\n";
    }

    // checking hp
    show_hps(wizard);
    std::cout << "Wizard take damage: -4HP\n";
    wizard.take_damage(4);

    // checking hp
    show_hps(wizard);

    std::cout << "Wizard uses minor heal potion: +3HP\n";
    ItemManager::use(minor_heal_potion, &wizard);
    // checking hp
    show_hps(wizard);

    std::cout << "Wizard take damage: -5HP\n";
    wizard.take_damage(5);
    std::cout << "Wizard uses great heal potion: +10HP\n";
    ItemManager::use(great_heal_potion, &wizard);
    show_hps(wizard);

    {
        const auto inventory = wizard.get_backpack_list();
        std::cout << "\nInventory after healing: ";
        for (const auto it: inventory)
            // std::cout << *it << ", ";
            std::cout << it->get_data() << ", ";
        std::cout << '\n';
    }
}

void test_randm()
{
    std::cout << generate_number(1, 11) << '\n';
    std::cout << generate_number(1, 11) << '\n';
    std::cout << generate_number(1, 11) << '\n';
    std::cout << generate_number(1, 11) << '\n';
}
