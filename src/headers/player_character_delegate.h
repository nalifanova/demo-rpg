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
        const pointtype base_hp = 1u,
        const pointtype base_mp = 0u,
        const stattype base_str = 1u,
        const stattype base_int = 1u,
        const stattype base_agi = 1u,
        const stattype base_arm = 0u,
        const stattype base_res = 0u
    ): CharacterStats(
        base_str,
        base_int,
        base_agi,
        base_arm,
        base_res),
        m_base_hp(base_hp),
        m_base_mp(base_mp)
    {
        hp = std::make_unique<PointStack>();
        hp->set_max(m_base_hp);
        hp->increase(m_base_hp);

        if (m_base_mp)
        {
            mp = std::make_unique<PointStack>();
            mp->set_max(m_base_mp);
            mp->increase(m_base_mp);
        }

        increase_stats(
            base.strength,
            base.intellect,
            base.agility
        );

        class_name = __func__;
    }
    ~PlayerCharacterDelegate() override = default;

    void apply_buff(const Buff& buff)
    {
        add_new_buff(buff);
    }

protected:
    void level_up() override
    {
        hp->set_max(division_by_2_(m_base_hp) + hp->get_initial());
        hp->increase(division_by_2_(m_base_hp));

        if (mp)
        {
            mp->set_max(division_by_2_(m_base_mp) + mp->get_initial());
            mp->increase(division_by_2_(m_base_mp));
        }

        increase_stats(
            division_by_2(static_cast<stattype>(base.strength + 1)),
            division_by_2(static_cast<stattype>(base.intellect + 1)),
            division_by_2( static_cast<stattype>(base.agility + 1))
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

    static pointtype division_by_2_(const pointtype value)
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
    pointtype m_base_hp;
    pointtype m_base_mp;
};

#endif //PLAYER_CHARACTER_DELEGATE_H
