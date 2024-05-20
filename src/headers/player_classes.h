#ifndef PLAYER_CLASSES_H
#define PLAYER_CLASSES_H

#include <utility>

#include "player_character_delegate.h"

class Cleric final: public PlayerCharacterDelegate
{
public:
    static constexpr stattype kBaseHp = 15u;
    static constexpr stattype kBaseMp = 10u;
    static constexpr stattype kbaseStr = 2;
    static constexpr stattype kBaseInt = 3;
    static constexpr stattype kBaseAgl = 3;

    Cleric(): PlayerCharacterDelegate(
        kBaseHp,
        kBaseMp,
        kbaseStr,
        kBaseInt,
        kBaseAgl,
        0,
        0
    )
    {
        class_name = __func__;

        abilities.emplace_back(
            "Heal",
            2u,
            1u,
            AbilityTarget::ally,
            2u,
            AbilityScaler::intellect
        );
    }

private:
    void level_up() override
    {
        PlayerCharacterDelegate::level_up();
        if (current_level == 2)
        {
            abilities.emplace_back(
            "Smite",
            2u,
            1u,
            AbilityTarget::enemy,
            2u,
            AbilityScaler::intellect
            );
        }
    }
};

class Rogue final: public PlayerCharacterDelegate
{
public:
    static constexpr stattype kBaseHp = 12u;
    static constexpr stattype kBaseMp = 0u;
    static constexpr stattype kbaseStr = 3;
    static constexpr stattype kBaseInt = 2;
    static constexpr stattype kBaseAgl = 3;

    Rogue(): PlayerCharacterDelegate(
        kBaseHp,
        kBaseMp,
        kbaseStr,
        kBaseInt,
        kBaseAgl,
        0,
        0
    )
    {
        class_name = __func__;
    }

private:
    void level_up() override
    {
        PlayerCharacterDelegate::level_up();
        if (current_level == 2)
        {
            abilities.emplace_back(
                "Precise Attack",
                0u,
                3u,
                AbilityTarget::enemy,
                6u,
                AbilityScaler::agility
            );
        }
    }
};

class Warrior final: public PlayerCharacterDelegate
{
public:
    static constexpr stattype kBaseHp = 18u;
    static constexpr stattype kBaseMp = 0u;
    static constexpr stattype kbaseStr = 4;
    static constexpr stattype kBaseInt = 1;
    static constexpr stattype kBaseAgl = 3;

    Warrior(): PlayerCharacterDelegate(
        kBaseHp,
        kBaseMp,
        kbaseStr,
        kBaseInt,
        kBaseAgl,
        0,
        0
    )
    {
        class_name = __func__;
    }
private:
    void level_up() override
    {
        PlayerCharacterDelegate::level_up();
        if (current_level == 2)
        {
            abilities.emplace_back(
                "Power Attack",
                0u,
                3u,
                AbilityTarget::enemy,
                4u,
                AbilityScaler::strength
            );
        }
    }
};

class Wizard final: public PlayerCharacterDelegate
{
public:
    static constexpr stattype kBaseHp = 10u;
    static constexpr stattype kBaseMp = 14u;
    static constexpr stattype kbaseStr = 1;
    static constexpr stattype kBaseInt = 4;
    static constexpr stattype kBaseAgl = 3;

    Wizard(): PlayerCharacterDelegate(
        kBaseHp,
        kBaseMp,
        kbaseStr,
        kBaseInt,
        kBaseAgl,
        0,
        0
    )
    {
        class_name = __func__;
    }
private:
    void level_up() override
    {
        PlayerCharacterDelegate::level_up();
        if (current_level == 2)
        {
            abilities.emplace_back(
                "IceBolt",
                3u,
                1u,
                AbilityTarget::enemy,
                6u,
                AbilityScaler::intellect
            );

            mp->set_max(1u + mp->get_initial());
            mp->increase(1u);

            increase_stats(0, 1);
        }
    }
};


class PlayerCharacter
{
public:
    PlayerCharacter() = delete;

    explicit PlayerCharacter(PlayerCharacterDelegate* player):
    m_player_class(player) {}

    ~PlayerCharacter()
    {
        // delete m_player_class;
        m_player_class = nullptr;
    }

    // ----------
    [[nodiscard]] std::string get_class_name() const
    {
        return m_player_class->class_name;
    }

    [[nodiscard]] leveltype get_level() const
    {
        return m_player_class->get_level();
    }

    [[nodiscard]] exptype get_current_exp() const
    {
        return m_player_class->get_current_exp();
    }

    [[nodiscard]] exptype get_exp_to_next_level() const
    {
        return m_player_class->get_exp_to_next_level();
    }

    [[nodiscard]] pointtype get_current_hp() const
    {
        return m_player_class->hp->get_current();
    }

    [[nodiscard]] pointtype get_max_hp() const
    {
        return m_player_class->hp->get_initial();
    }

    [[nodiscard]] pointtype get_current_mp() const
    {
        if (m_player_class->mp)
            return m_player_class->mp->get_current();
        return 0;
    }

    [[nodiscard]] pointtype get_max_mp() const
    {
        if (m_player_class->mp)
            return m_player_class->hp->get_initial();
        return 0;
    }

    [[nodiscard]] stattype get_strength() const
    {
        return m_player_class->get_strength();
    }

    [[nodiscard]] stattype get_intellect() const
    {
        return m_player_class->get_intellect();
    }

    [[nodiscard]] stattype get_agility() const
    {
        return m_player_class->get_agility();
    }

    [[nodiscard]] stattype get_armor() const
    {
        return m_player_class->get_armor();
    }

    [[nodiscard]] stattype get_resistance() const
    {
        return m_player_class->get_resistance();
    }

    [[nodiscard]] stattype get_base_strength() const
    {
        return m_player_class->get_base_strength();
    }

    [[nodiscard]] stattype get_base_intellect() const
    {
        return m_player_class->get_base_intellect();
    }

    [[nodiscard]] stattype get_base_agility() const
    {
        return m_player_class->get_base_agility();
    }

    [[nodiscard]] stattype get_base_armor() const
    {
        return m_player_class->get_base_armor();
    }

    [[nodiscard]] stattype get_base_resistance() const
    {
        return m_player_class->get_base_resistance();
    }

    [[nodiscard]] std::vector<Ability> get_ability_list() const
    {
        return m_player_class->abilities;
    }

    void gain_exp(const exptype points) const
    {
        m_player_class->gain_exp(points);
    }

    void take_damage(const pointtype points) const
    {
        m_player_class->hp->reduce(points);
    }

    void heal(const pointtype points) const
    {
        m_player_class->hp->increase(points);
    }

    void apply_buff(Buff buff) const
    {
        m_player_class->apply_buff(std::move(buff));
    }

private:
    PlayerCharacterDelegate* m_player_class = nullptr;
    // std::unique_ptr<PlayerCharacterDelegate> m_player_class;
};

#endif //PLAYER_CLASSES_H
