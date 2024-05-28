#ifndef WARRIOR_H
#define WARRIOR_H

#include "player_character_delegate.h"
#include "types.h"

class Warrior final: public PlayerCharacterDelegate
{
public:
    static constexpr stattype kBaseHp = 18u;
    static constexpr stattype kBaseMp = 0u;
    static constexpr stattype kbaseStr = 4;
    static constexpr stattype kBaseInt = 1;
    static constexpr stattype kBaseAgl = 3;

    Warrior();

private:
    void level_up() override;
};

#endif //WARRIOR_H
