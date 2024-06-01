#include "game_play.h"

#include <iostream>

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

    const int lowest_hp = base_calc->player_character.get_level() *  2;
    const int max_hp = base_calc->player_character.get_level() *  8;

    const int lowest_dmg = base_calc->player_character.get_level();
    const int max_dmg = base_calc->player_character.get_level() *  2;

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

// returns true on win, false otherwise
void enter_fight_sequence(const Player& player)
{
    if (!current_monster) return;

    while(player.is_alive() && current_monster->is_alive())
    {
        system("clear"); // linux/macos

        // display fight interface
        std::cout << "Player        vs          Monster\n" <<
        "hp: " << player.player_character.get_current_hp() << '/' <<
        player.player_character.get_max_hp() << "               hp: " <<
        current_monster->monster.hp.get_current() << '/' <<
        current_monster->monster.hp.get_initial() << '\n' <<
        "action(a: attack): ";

        char action = '1';
        while (action != 'a') action = getchar();

        current_monster->monster.hp.reduce(
            player.player_character.melee_attack()
        );

        if (current_monster->is_alive())
            player.player_character.take_damage(
                current_monster->monster.attack()
            );
    }

    if (player.is_alive())
    {
        std::cout << "You won vs the Monster!\n";
        std::cout << "xp gained: " << current_monster->xp_worth << '\n';

        player.player_character.gain_exp(current_monster->xp_worth);
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
        std::cout << "\nmove(wasd): \n";

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