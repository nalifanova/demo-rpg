#ifndef PLAYER_CHARACTER_DELEGATE_H
#define PLAYER_CHARACTER_DELEGATE_H

#include <memory>

#include "character_stats.h"
#include "level_system.h"

class PlayerCharacterDelegate: public LevelSystem, public CharacterStats
{
public:
    PlayerCharacterDelegate(
        const pointtype base_hp,
        const stattype base_str,
        const stattype base_int
    ): base_hp(base_hp), base_str(base_str), base_int(base_int)
    {
        hp = std::make_unique<PointStack>();
        hp->set_max(base_hp);
        hp->increase(base_hp);
        increase_stats(base_str, base_int);
    }
    ~PlayerCharacterDelegate() override = default;

    std::unique_ptr<PointStack> hp;

protected:
    void level_up() override
    {
        // static_cast<pointtype>(static_cast<float>(base_hp) / 2.f)
        hp->set_max(division_by_2(base_hp) + hp->get_initial());
        hp->increase(division_by_2(base_hp));

        increase_stats(
            division_by_2(1u + base_str),
            division_by_2(1u + base_int)
        );
    }

private:
    // Compiler/IDE shows warning and demands remove narrowing type conversion
    // >> "Clang-Tidy: Narrowing conversion from 'int' to 'float'"
    // by doing: static_cast<pointtype>(static_cast<float>(base_hp) / 2.f)

    // That's too much to type. Thus here we go.
    // Note: std::uint16_t is taken for explicity, because stattype and
    // pointtype are the same of type std::uint16_t which does not allow to do
    // override the method. So, this is a pitfall!
    static std::uint16_t division_by_2(const stattype value)
    {
        return static_cast<std::uint16_t>(static_cast<float>(value) / 2.f);
    }

    pointtype base_hp;
    stattype base_str;
    stattype base_int;
};

#endif //PLAYER_CHARACTER_DELEGATE_H
