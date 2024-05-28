#ifndef PLAYER_CLASSES_H
#define PLAYER_CLASSES_H

#include "player_character_delegate.h"
#include "types.h"

class Cleric final: public PlayerCharacterDelegate
{
public:
    static constexpr stattype kBaseHp = 15u;
    static constexpr stattype kBaseMp = 10u;
    static constexpr stattype kbaseStr = 2;
    static constexpr stattype kBaseInt = 3;
    static constexpr stattype kBaseAgl = 3;

    Cleric();

private:
    void level_up() override;
};

#endif //PLAYER_CLASSES_H
