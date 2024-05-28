#ifndef ROGUE_H
#define ROGUE_H

#include "player_character_delegate.h"
#include "types.h"

class Rogue final: public PlayerCharacterDelegate
{
public:
    static constexpr stattype kBaseHp = 12u;
    static constexpr stattype kBaseMp = 0u;
    static constexpr stattype kbaseStr = 3;
    static constexpr stattype kBaseInt = 2;
    static constexpr stattype kBaseAgl = 3;

    Rogue();

private:
    void level_up() override;
};

#endif //ROGUE_H
