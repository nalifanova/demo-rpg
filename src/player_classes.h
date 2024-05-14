#ifndef PLAYER_CLASSES_H
#define PLAYER_CLASSES_H

#include "player_character_delegate.h"

class Cleric final: public PlayerCharacterDelegate
{
public:
    static constexpr pointtype kBaseHp = 15u;
    static constexpr stattype kbaseStr = 2u;
    static constexpr stattype kBaseInt = 3u;

    Cleric(): PlayerCharacterDelegate(kBaseHp, kbaseStr, kBaseInt)
    {
        name = __func__;
    }
};

class Rogue final: public PlayerCharacterDelegate
{
public:
    static constexpr pointtype kBaseHp = 12u;
    static constexpr stattype kbaseStr = 3u;
    static constexpr stattype kBaseInt = 2u;

    Rogue(): PlayerCharacterDelegate(kBaseHp, kbaseStr, kBaseInt)
    {
        name = __func__;
    }
};

class Warrior final: public PlayerCharacterDelegate
{
public:
    static constexpr pointtype kBaseHp = 18u;
    static constexpr stattype kbaseStr = 4u;
    static constexpr stattype kBaseInt = 1u;

    Warrior(): PlayerCharacterDelegate(kBaseHp, kbaseStr, kBaseInt)
    {
        name = __func__;
    }
};

class Wizard final: public PlayerCharacterDelegate
{
public:
    static constexpr pointtype kBaseHp = 10u;
    static constexpr stattype kbaseStr = 1u;
    static constexpr stattype kBaseInt = 4u;

    Wizard(): PlayerCharacterDelegate(kBaseHp, kbaseStr, kBaseInt)
    {
        name = __func__;
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
        return m_player_class->name;
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

    [[nodiscard]] stattype get_strength() const
    {
        return m_player_class->get_strength();
    }

    [[nodiscard]] stattype get_intellect() const
    {
        return m_player_class->get_intellect();
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


private:
    PlayerCharacterDelegate* m_player_class = nullptr;
    // std::unique_ptr<PlayerCharacterDelegate> m_player_class;
};

#endif //PLAYER_CLASSES_H
