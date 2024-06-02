#include "game_play.h"

#include <iostream>
#include <item_manager.h>

#include "cleric.h"
#include "random.h"
#include "rogue.h"
#include "warrior.h"
#include "wizard.h"

Player* main_character = nullptr;
Fightable* current_monster = nullptr;
int monsters_defeated = 0;

void create_monster(Fightable* in_out, const Player* base_calc)
{
    if (!base_calc) return;

    if (in_out)
    {
        delete in_out;
        in_out = nullptr;
    }

    const int lowest_hp = base_calc->character.get_level() *  2;
    const int max_hp = base_calc->character.get_level() *  8;

    const int lowest_dmg = base_calc->character.get_level();
    const int max_dmg = base_calc->character.get_level() *  2;

    in_out = new Fightable(
        generate_number(lowest_hp, max_hp),
        lowest_dmg,
        max_dmg
    );
    in_out->x = generate_number(1, 10);
    in_out->y = generate_number(1, 10);

    while(
        the_map[in_out->x][in_out->y] == 'P' ||
        the_map[in_out->x][in_out->y] == 'X'
    )
    {
        in_out->x = generate_number(1, 10);
        in_out->y = generate_number(1, 10);
    }

    the_map[in_out->x][in_out->y] = 'M';
    current_monster = in_out;
}

void open_inventory()
{
    system("clear");
    auto list_of_items = main_character->character.get_backpack_list();

    std::cout << "Current Inventory:\n------------------\n\n";
    for (const auto&item: list_of_items)
        std::cout << "> " << item->get_data()->name << '\n';

    std::cin.ignore(100, '\n');
    std::cout << "\n\nPress enter to continue\n";
    // char c = getchar();
}
Item* drop_random_item()
{
    // 8 armor items, 2 weapon types, 1 potion: 11 different drop types
    const int drop_seed = generate_number(1, 100);
    if (drop_seed < 6)
    {
        std::string name;
        CoreStats local_stats;

        int magical_power = generate_number(0, 2);

        switch(magical_power)
        {
        case 0:
            name = "Helmet";
            local_stats = CoreStats(0, 0, 0, 1, 0);
            break;
        case 1:
            name = "+1 Helmet";
            local_stats = CoreStats(1, 1, 1, 2, 1);
            break;
        case 2:
            name = "+2 Helmet";
            local_stats = CoreStats(2, 2, 2, 3, 2);
            break;
        default:
            break;
        }
        return ItemManager::create_armor(name, local_stats, ArmorSlot::head);
    }
    if (drop_seed < 12)
    {
        return ItemManager::create_armor(
            "Cyrasa",
            CoreStats(0, 0, 0, 1, 0),
            ArmorSlot::chest
        );
    }
    if (drop_seed < 18)
    {
        return ItemManager::create_armor(
            "Leg Guards",
            CoreStats(0, 0, 0, 1, 0),
            ArmorSlot::legs
        );
    }
    if (drop_seed < 24)
    {
        return ItemManager::create_armor(
            "Boots",
            CoreStats(0, 0, 0, 1, 0),
            ArmorSlot::feet
        );
    }
    if (drop_seed < 30)
    {
        return ItemManager::create_armor(
            "Gloves",
            CoreStats(0, 0, 0, 1, 0),
            ArmorSlot::hands
        );
    }
    if (drop_seed < 36)
    {
        return ItemManager::create_armor(
            "Ring1",
            CoreStats(1, 1, 1, 0, 0),
            ArmorSlot::ring1
        );
    }
    if (drop_seed < 42)
    {
        return ItemManager::create_armor(
            "Ring2",
            CoreStats(1, 1, 1, 0, 0),
            ArmorSlot::ring2
        );
    }
    if (drop_seed < 48)
    {
        return ItemManager::create_armor(
            "Necklace",
            CoreStats(0, 1, 0, 1, 1),
            ArmorSlot::neck
        );
    }
    if (drop_seed < 54)
    {
        return ItemManager::create_weapon(
            "1H Sword",
            CoreStats(0),
            WeaponSlot::melee,
            2,
            3
        );
    }
    if (drop_seed < 60)
    {
        return ItemManager::create_weapon(
            "Bow",
            CoreStats(0),
            WeaponSlot::ranged,
            2,
            3,
            true
        );
    }
    if (drop_seed < 90)
    {
        return ItemManager::create_potion(
            "Healing potion",
            generate_number(2, 5),
            generate_number(1, 2)
        );
    }
    return nullptr;
}


// returns true on win, false otherwise
void enter_fight_sequence(Player& player)
{
    if (!current_monster) return;

    while(player.is_alive() && current_monster->is_alive())
    {
        system("clear"); // linux/macos

        // display fight interface
        std::cout << "Player        vs          Monster\n" <<
        "hp: " << player.character.get_current_hp() << '/' <<
        player.character.get_max_hp() << "               hp: " <<
        current_monster->monster.hp.get_current() << '/' <<
        current_monster->monster.hp.get_initial() << '\n' <<
        "action(a: attack): ";

        char action = '1';
        while (action != 'a') action = getchar();

        current_monster->monster.hp.reduce(
            player.character.melee_attack()
        );

        if (current_monster->is_alive())
            player.character.take_damage(
                current_monster->monster.attack()
            );
    }

    if (player.is_alive())
    {
        std::cout << "You won vs the Monster!\n";
        std::cout << "xp gained: " << current_monster->xp_worth << '\n';
        player.character.gain_exp(current_monster->xp_worth);

        // drop a random item
        if (Item* item_drop = drop_random_item())
        {
            ItemManager::move_to_backpack(item_drop, &player.character);
            std::cout << "item received: " <<
            item_drop->get_data()->name << '\n';
        }

        monsters_defeated++;
        create_monster(current_monster, &player);
    }
    else
    {
        std::cout << "You were defeated by the Monster!\n";
    }
    std::cin.ignore(100, '\n');
    std::cout << "\nPress enter to continue\n";
}

void move_player_on_map(Player& player)
{
    if (player.x == player.prev_x && player.y == player.prev_y) return;

    if (the_map[player.x][player.y] == 'M') enter_fight_sequence(player);

    // check that the player hasn't moved into a wall
    if (the_map[player.x][player.y] != 'X')
    {
        // draw the character at new location
        the_map[player.x][player.y] = 'P';
        // make old location a black area
        the_map[player.prev_x][player.prev_y] = ' ';
        // update current location to be previous before next update
        player.prev_x = player.x;
        player.prev_y = player.y;
    }
    else
    {
        // hit a wall, move back to prev location
        player.x = player.prev_x;
        player.y = player.prev_y;
    }
}

void show_map()
{
    system("clear");
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 12; j++) std::cout << the_map[i][j];
        std::cout << '\n';
    }
}

void game_play_()
{
    std::cout << "Choose a class: \n" <<
    "1 = Cleric     2 = Warrior     3 = Rogue       4 = Wizard\n";
    int choice = 0;
    while (choice == 0)
    {
        std::cin >> choice;
        std::cout << "Chose: " << choice << '\n';
        if (choice < 1 || choice > 4) choice = 0;
    }

    switch(choice)
    {
    case 1:
        {main_character = new Player(new Cleric());}
        break;
    case 2:
        {main_character = new Player(new Warrior());}
        break;
    case 3:
        {main_character = new Player(new Rogue());}
        break;
    case 4:
        {main_character = new Player(new Wizard());}
        break;
    default:
        return; // failed to make a player character
    }

    create_monster(current_monster, main_character);

    the_map[main_character->x][main_character->y] = 'P';
    the_map[current_monster->x][current_monster->y] = 'M';

    show_map();

    for (;;)
    {
        std::cout << "\nmove(wasd), inventory(i): \n";

        switch(char c = getchar())
        {
        case 'w':
            main_character->x--;
            break;
        case 's':
            main_character->x++;
            break;
        case 'a':
            main_character->y--;
            break;
        case 'd':
            main_character->y++;
            break;
        case 'i':
            open_inventory();
            break;
        default:
            break;
        }
        std::cin.clear();

        move_player_on_map(*main_character);

        if (main_character->is_alive()) show_map();
        else break;
    }

    std::cout << "Total monsters defeated: " << monsters_defeated << '\n';
}