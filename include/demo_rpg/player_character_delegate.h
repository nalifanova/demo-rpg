#ifndef PLAYER_CHARACTER_DELEGATE_H
#define PLAYER_CHARACTER_DELEGATE_H

#include "ability.h"
#include "buff.h"
#include "character_stats.h"
#include "level_system.h"
#include "point_stack.h"

class PlayerCharacterDelegate: public LevelSystem, public CharacterStats
{
public:
     explicit PlayerCharacterDelegate(
        pointtype base_hp = 1u,
        pointtype base_mp = 0u,
        stattype base_str = 1u,
        stattype base_int = 1u,
        stattype base_agi = 1u,
        stattype base_arm = 0u,
        stattype base_res = 0u
    );
    ~PlayerCharacterDelegate() override = default;

    void apply_buff(const Buff& buff);

protected:
    void level_up() override;

private:
    // Compiler/IDE shows warning and demands remove narrowing type conversion
    // >> "Clang-Tidy: Narrowing conversion from 'int' to 'float'"
    // by doing: static_cast<stattype>(static_cast<float>(base_hp) / 2.f)

    // That's too much to type. Thus here we go.
    static stattype division_by_2(stattype value);

    static pointtype division_by_2_(pointtype value);

public:
    const char* class_name;
    std::unique_ptr<PointStack> hp;
    std::unique_ptr<PointStack> mp;
    std::vector<Ability> abilities;
    std::vector<Buff> buffs;

private:
    pointtype m_base_hp;
    pointtype m_base_mp;
};

#endif //PLAYER_CHARACTER_DELEGATE_H
