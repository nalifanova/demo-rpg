#ifndef PLAYER_CHARACTER_DELEGATE_H
#define PLAYER_CHARACTER_DELEGATE_H

#include <memory>

#include "character_stats.h"
#include "level_system.h"

class PlayerCharacterDelegate: public LevelSystem, public CharacterStats
{
public:
    PlayerCharacterDelegate(
        const stattype base_hp,
        const stattype base_str,
        const stattype base_int,
        const stattype base_agl
    ):
    base_hp(base_hp),
    base_str(base_str),
    base_int(base_int),
    base_agl(base_agl)
    {
        hp = std::make_unique<PointStack>();
        hp->set_max(base_hp);
        hp->increase(base_hp);
        increase_stats(base_str, base_int, base_agl);

        class_name = __func__;
    }
    ~PlayerCharacterDelegate() override = default;

    std::unique_ptr<PointStack> hp;

protected:
    void level_up() override
    {
        hp->set_max(division_by_2(base_hp) + hp->get_initial());
        hp->increase(division_by_2(base_hp));

        increase_stats(
            division_by_2(1u + base_str),
            division_by_2(1u + base_int),
            division_by_2(1u + base_agl)
        );
    }

private:
    // Compiler/IDE shows warning and demands remove narrowing type conversion
    // >> "Clang-Tidy: Narrowing conversion from 'int' to 'float'"
    // by doing: static_cast<stattype>(static_cast<float>(base_hp) / 2.f)

    // That's too much to type. Thus here we go.
    static stattype division_by_2(const stattype value)
    {
        return static_cast<stattype>(static_cast<float>(value) / 2.f);
    }

public:
    const char* class_name;

private:
    stattype base_hp;
    stattype base_str;
    stattype base_int;
    stattype base_agl;
};

#endif //PLAYER_CHARACTER_DELEGATE_H
