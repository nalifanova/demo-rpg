#include "game_play.h"

#include <iostream>

#include "cleric.h"
#include "item_manager.h"
#include "random.h"
#include "rogue.h"
#include "warrior.h"
#include "wizard.h"

Player* main_character = nullptr;
Fightable* current_monster = nullptr;
int monsters_defeated = 0;

int get_scale_value(const AbilityScaler scaler)
{
    switch(scaler)
    {
    case AbilityScaler::strength:
        return static_cast<int>(main_character->character.get_strength() / 2.f);
    case AbilityScaler::intellect:
        return static_cast<int>(main_character->character.get_intellect() / 2.f);
    case AbilityScaler::agility:
        return static_cast<int>(main_character->character.get_agility() / 2.f);
    default:
        return 0;
    }
}

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

bool open_inventory(const bool in_combat)
{
    bool done = false;
    bool action_used = false;
    int selected_item_num = 0;

    while(!done)
    {
        system("clear");
        auto list_of_items = main_character->character.get_backpack_list();

        std::cout << "Current Inventory:\n------------------\n\n";
        int items_in_backpack_count = 0;
        for (const auto&item: list_of_items)
        {
            if (selected_item_num == items_in_backpack_count) std::cout << "> ";
            else std::cout << " ";
            std::cout << item->get_data()->name << '\n';

            if (ItemManager::is_item_potion(item))
            {
                Potion* potion = nullptr;
                ItemManager::cast_item_to_potion(item, potion);
                if (potion)
                    std::cout << "    Quantity: " << potion->quantity << "\n";
                items_in_backpack_count++;
            }
        }

        std::cin.ignore(100, '\n');
        std::cout << "\nd=done, w=up, s=down, u=use/equip current\n";
        // std::cin.get(); // for macos

        switch (char c = getchar())
        {
        case 'd':
            done = true;
            break;
        case 'w':
            selected_item_num--;
            if (selected_item_num < 0) selected_item_num = 0;
            break;
        case 's':
            selected_item_num++;
            if (selected_item_num > list_of_items.size() - 1)
                selected_item_num = static_cast<int>(list_of_items.size()) - 1;
            break;
        case 'u':
            if (list_of_items.empty()) continue;
            if (ItemManager::is_item_potion(list_of_items[selected_item_num]))
                action_used = ItemManager::use(
                    list_of_items[selected_item_num],
                    &(main_character->character)
                );
            else
                action_used = ItemManager::equip(
                    list_of_items[selected_item_num],
                    &(main_character->character)
                );
            break;
        default:
            break;
        }
        if (in_combat) // TODO: let's see if it works
            if (action_used) break;
    }
    return action_used;
}

bool combat_ability_selection()
{
    bool ability_done = false;
    bool action_used = false;
    int selected_ability = 0;

    while (!ability_done)
    {
        auto current_abilities = main_character->character.get_ability_list();
        system("clear");
        std::cout << "Current Abilities\n";

        int abilities_in_list_count = 0;
        for (const auto& abil: current_abilities)
        {
            std::cout << ((selected_ability == abilities_in_list_count) ? "> " : " ");
            std::cout << abil.name << '\n';
            // TODO: cooldowns and mp
            abilities_in_list_count++;
        }

        std::cin.ignore(100, '\n');
        std::cout << "\nd=done, w=up, s=down, u=use\n";
        switch(char c = getchar())
        {
        case 'd':
            ability_done = true;
            break;
        case 'w':
            selected_ability--;
            if (selected_ability < 0) selected_ability = 0;
            break;
        case 's':
            selected_ability++;
            if (selected_ability > current_abilities.size() - 1)
                selected_ability = static_cast<int>(current_abilities.size()) - 1;
            break;
        case 'u':
            {
                int total = 0;
                total += current_abilities[selected_ability].hp_effect;
                total+= get_scale_value(current_abilities[selected_ability].scaler);

                if (current_abilities[selected_ability].target == AbilityTarget::enemy)
                    current_monster->monster.hp.reduce(total);
                else
                    main_character->character.heal(total);

                action_used = true;
            }
            break;
        default:
            break;
        }
        if (action_used) break;
    }
    return action_used;
}

void display_charachter_sheet()
{
    system("clear");
    std::cout << "Character list:\n";
    std::cout << "---- :) ----\n";

    system("clear");
    std::cout
    << "Your Character\n" << "L: " <<
    main_character->character.get_level() << " XP: " <<
    main_character->character.get_current_exp() << " NEXT: " <<
    main_character->character.get_exp_to_next_level() << '\n' <<

    "Hit Points: " << main_character->character.get_current_hp() << "/" <<
    main_character->character.get_max_hp() << '\n' <<
    "Armor: " << main_character->character.get_armor() <<
    "  Resistance: " << main_character->character.get_resistance() << '\n' <<
    "STR: " << main_character->character.get_strength() <<
    " AGI: " << main_character->character.get_agility() <<
    " INT: " << main_character->character.get_intellect() << '\n'
    << "\n\nEquipped Gear\n";

    if (Weapon* p_weapon = main_character->character.get_equipped_weapon_at(static_cast<int>(WeaponSlot::melee))) {
    std::string weapon_name = p_weapon->name;
    std::cout << "MELEE: " << weapon_name << "  damage(" << p_weapon->get_min_damage() << '-' <<
        p_weapon->get_max_damage() << ")\n";
    }
    if (Weapon* p_weapon = main_character->character.get_equipped_weapon_at(static_cast<int>(WeaponSlot::ranged))) {
    std::string weapon_name = p_weapon->name;
    std::cout << "RANGED: " << weapon_name << "  damage(" << p_weapon->get_min_damage() << '-' <<
        p_weapon->get_max_damage() << ")\n";
    }
    if (Armor* p_armor = main_character->character.get_equipped_armor_at(static_cast<int>(ArmorSlot::head))) {
        std::cout << "HEAD: " << p_armor->name << '\n';
    }
    if (Armor* p_armor = main_character->character.get_equipped_armor_at(static_cast<int>(ArmorSlot::neck))) {
        std::cout << "NECK: " << p_armor->name << '\n';
    }
    if (Armor* p_armor = main_character->character.get_equipped_armor_at(static_cast<int>(ArmorSlot::chest))) {
        std::cout << "CHEST: " << p_armor->name << '\n';
    }
    if (Armor* p_armor = main_character->character.get_equipped_armor_at(static_cast<int>(ArmorSlot::hands))) {
        std::cout << "HANDS: " << p_armor->name << '\n';
    }
    if (Armor* p_armor = main_character->character.get_equipped_armor_at(static_cast<int>(ArmorSlot::ring1))) {
        std::cout << "RING1: " << p_armor->name << '\n';
    }
    if (Armor* p_armor = main_character->character.get_equipped_armor_at(static_cast<int>(ArmorSlot::ring2))) {
        std::cout << "RING2: " << p_armor->name << '\n';
    }
    if (Armor* p_armor = main_character->character.get_equipped_armor_at(static_cast<int>(ArmorSlot::legs))) {
        std::cout << "LESG: " << p_armor->name << '\n';
    }
    if (Armor* p_armor = main_character->character.get_equipped_armor_at(static_cast<int>(ArmorSlot::feet))) {
        std::cout << "FEET: " << p_armor->name << '\n';
    }
    
    std::cin.ignore(100, '\n');
    std::cout << "\npress enter to continue...\n";
    std::cin.get();
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
void fight_sequence(Player& player)
{
    if (!current_monster) return;

    // options available per turn
    enum class FightOptions {none, attack, inventory, ability};
    while(player.is_alive() && current_monster->is_alive())
    {
        auto action_taken = FightOptions::none;
        char action = '\0';

        while (action_taken == FightOptions::none)
        {
            system("clear"); // linux/macos
            // display fight interface
            std::cout << "Player        vs          Monster\n" <<
            "hp: " << player.character.get_current_hp() << '/' <<
            player.character.get_max_hp() << "               hp: " <<
            current_monster->monster.hp.get_current() << '/' <<
            current_monster->monster.hp.get_initial() << '\n' <<
            "action(a:attack, i:inventory, b:abilities): ";

            action = getchar();

            switch (action)
            {
            case 'a':
                action_taken = FightOptions::attack;
                current_monster->monster.hp.reduce(
                    player.character.melee_attack()
                );
                break;
            case 'i':
                action_taken = (open_inventory(true)) ?
                    FightOptions::inventory : FightOptions::none;
                break;
            case 'b':
                action_taken = (combat_ability_selection()) ?
                    FightOptions::ability : FightOptions::none;
                break;
            default:
                break;
            }
        }
        // monster hits when the player's turn is over
        if (current_monster->is_alive())
        {
            // monster attack every turn and min dmg exists despite of player's
            // armor - weird, huh?
            int damage_player_takes = current_monster->monster.attack();
            damage_player_takes -= player.character.get_armor();

            if (damage_player_takes < 1) damage_player_takes = 1;

            player.character.take_damage(damage_player_takes);
        }
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

    if (the_map[player.x][player.y] == 'M') fight_sequence(player);

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

void run_game()
{
    system("clear");
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

    // Get 2 random items to the backpack
    ItemManager::move_to_backpack(drop_random_item(), &main_character->character);
    ItemManager::move_to_backpack(drop_random_item(), &main_character->character);

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
            open_inventory(false);
            break;
        case 'c':
            display_charachter_sheet();
            break;
        case 'q':
            main_character->character.cleanup_backpack();
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