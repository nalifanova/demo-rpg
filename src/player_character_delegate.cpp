#include "headers/player_character_delegate.h"

PlayerCharacterDelegate::PlayerCharacterDelegate(
    const pointtype base_hp,
    const pointtype base_mp,
    const stattype base_str,
    const stattype base_int,
    const stattype base_agi,
    const stattype base_arm,
    const stattype base_res
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

void PlayerCharacterDelegate::apply_buff(const Buff& buff)
{
    add_new_buff(buff);
}

// PROTECTED
void PlayerCharacterDelegate::level_up()
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

// PRIVATE
stattype PlayerCharacterDelegate::division_by_2(const stattype value)
{
    return static_cast<stattype>(static_cast<float>(value) / 2.f);
}

pointtype PlayerCharacterDelegate::division_by_2_(const pointtype value)
{
    return static_cast<pointtype>(static_cast<float>(value) / 2.f);
}
