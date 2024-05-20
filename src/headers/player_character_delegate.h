#ifndef PLAYER_CHARACTER_DELEGATE_H
#define PLAYER_CHARACTER_DELEGATE_H

#include "ability.h"
#include "buff.h"
#include "character_stats.h"
#include "level_system.h"

class PlayerCharacterDelegate: public LevelSystem, public CharacterStats
{
public:
    explicit PlayerCharacterDelegate(
        const pointtype base_hp,
        const pointtype base_mp, // Note: maybe it makes sense to leave it?
        const stattype base_str,
        const stattype base_int,
        const stattype base_agi,
        const stattype base_arm,
        const stattype base_res
    ):
    base_hp(base_hp),
    base_mp(base_mp),
    base_str(base_str),
    base_int(base_int),
    base_agi(base_agi),
    base_arm(base_arm),
    base_res(base_res)
    {
        hp = std::make_unique<PointStack>();
        hp->set_max(base_hp);
        hp->increase(base_hp);

        if (base_mp)
        {
            mp = std::make_unique<PointStack>();
            mp->set_max(base_mp);
            mp->increase(base_mp);
        }

        increase_stats(
            base_str,
            base_int,
            base_agi
        );

        class_name = __func__;
    }
    ~PlayerCharacterDelegate() override = default;

    void apply_buff(Buff buff)
    {
        add_new_buff(buff);
    }

protected:
    void level_up() override
    {
        hp->set_max(division_by_2(base_hp) + hp->get_initial());
        hp->increase(division_by_2(base_hp));

        if (mp)
        {
            mp->set_max(division_by_2(base_mp) + mp->get_initial());
            mp->increase(division_by_2(base_mp));
        }

        increase_stats(
            division_by_2(static_cast<stattype>(base_str + 1)),
            division_by_2(static_cast<stattype>(base_int + 1)),
            division_by_2( static_cast<stattype>(base_agi + 1))
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

    static pointtype division_by_2(const pointtype value)
    {
        return static_cast<pointtype>(static_cast<float>(value) / 2.f);
    }

public:
    const char* class_name;
    std::unique_ptr<PointStack> hp;
    std::unique_ptr<PointStack> mp;
    std::vector<Ability> abilities;
    std::vector<Buff> buffs;

private:
    pointtype base_hp;
    pointtype base_mp;
    stattype base_str;
    stattype base_int;
    stattype base_agi;
    stattype base_arm;
    stattype base_res;
};

#endif //PLAYER_CHARACTER_DELEGATE_H
