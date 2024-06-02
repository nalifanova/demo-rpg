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

void game_play_();
void open_inventory();
Item* drop_random_item();

#endif //GAME_PLAY_H
