#ifndef PLAYER_CLASSES_H
#define PLAYER_CLASSES_H

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
            nullptr,
            1u,
            2u,
            AbilityTarget::ally,
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
            nullptr,
            1u,
            2u,
            AbilityTarget::enemy,
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
                nullptr,
                3u,
                6u,
                AbilityTarget::enemy,
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
                nullptr,
                3u,
                4u,
                AbilityTarget::enemy,
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
                nullptr,
                1u,
                6u,
                AbilityTarget::enemy,
                AbilityScaler::intellect
            );

            mp->set_max(1u + mp->get_initial());
            mp->increase(1u);

            increase_stats(0, 1);
        }
    }
};

#endif //PLAYER_CLASSES_H
