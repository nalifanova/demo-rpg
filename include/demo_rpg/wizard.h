#ifndef WIZARD_H
#define WIZARD_H

#include "player_character_delegate.h"
#include "types.h"

class Wizard final: public PlayerCharacterDelegate
{
public:
    static constexpr stattype kBaseHp = 10u;
    static constexpr stattype kBaseMp = 14u;
    static constexpr stattype kBaseStr = 1;
    static constexpr stattype kBaseInt = 4;
    static constexpr stattype kBaseAgl = 3;

    Wizard();

private:
    void level_up() override;
};

#endif //WIZARD_H
