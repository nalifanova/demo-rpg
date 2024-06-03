#ifndef GAME_PLAY_H
#define GAME_PLAY_H

#include <monster.h>
#include <player_character.h>
#include <player_character_delegate.h>

inline char the_map[12][13] = // last 0 character
{
    "XXXXXXXXXXXX",
    "X          X",
    "X          X",
    "X          X",
    "X          X",
    "X          X",
    "X          X",
    "X          X",
    "X          X",
    "X          X",
    "X          X",
    "XXXXXXXXXXXX"
};

struct Player
{
    explicit Player(PlayerCharacterDelegate* char_class): character(char_class){}
    Player() = delete;
    [[nodiscard]] bool is_alive() const
    {
        return character.get_current_hp() > 0;
    }

    PlayerCharacter character;
    int prev_x = 3;
    int prev_y = 3;
    int x = 3;
    int y = 3;
};

struct Fightable
{
    Fightable(const int hp, const int min, const int max): monster(hp, min, max)
    {
        xp_worth = (hp + min + max) * 2;
    }

    Fightable() = delete;

    [[nodiscard]] bool is_alive() const
    {
        return monster.hp.get_current() > 0;
    }
    Monster monster;
    int x = 3;
    int y = 3;
    int xp_worth;
};

void create_monster(Fightable* in_out, const Player* base_calc);
Item* drop_random_item();
bool open_inventory(bool in_combat = false);
bool combat_ability_selection();
void fight_sequence(Player& player);
void move_player_on_map(Player& player);
void show_map();
void run_game();
void display_charachter_sheet();

#endif //GAME_PLAY_H
