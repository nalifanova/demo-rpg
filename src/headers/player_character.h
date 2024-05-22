#ifndef PLAYER_CHARACTER_H
#define PLAYER_CHARACTER_H

#include <algorithm>

#include "item.h"
#include "player_character_delegate.h"

class PlayerCharacter
{
public:
    PlayerCharacter() = delete;

    /* error: call to implicitly-deleted copy constructor of
     * 'const PlayerCharacter' (src/tests.cpp:55:9: ... warrior, wizard..)
     * TODO: find a reason why?
     */
    // PlayerCharacter(const PlayerCharacter&) = delete; // no copy
    // PlayerCharacter(const PlayerCharacter&&) = delete; // no move

    explicit PlayerCharacter(PlayerCharacterDelegate* player)
    :m_player_class(player)
    {
        int i;
        for (i = 0; i < static_cast<unsigned int>(ArmorSlot::num_slots); i++)
            m_equipped_armors[i] = nullptr;

        for (i = 0; i < static_cast<unsigned int>(WeaponSlot::num_slots); i++)
            m_equipped_weapons[i] = nullptr;
    }

    ~PlayerCharacter()
    {
        // deletion of m_player_class leads to
        // memory violation issue - 139 (interrupted by signal 11:SIGSEGV)
        // delete m_player_class;
        m_player_class = nullptr;
        for (auto & equipped_armor : m_equipped_armors)
        {
            if (equipped_armor)
            {
                delete equipped_armor;
                equipped_armor = nullptr;
            }
        }

        for (auto & m_equipped_weapon : m_equipped_weapons)
        {
            if (m_equipped_weapon)
            {
                delete m_equipped_weapon;
                m_equipped_weapon = nullptr;
            }
        }
    }

    // Getters
    [[nodiscard]] PlayerCharacterDelegate* get_player() const
    {
        return &*m_player_class;
    }

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
        stattype str_from_armor = 0;
        for (const auto m_equipped_armor : m_equipped_armors)
        {
            if (m_equipped_armor)
            {
                const auto* armor = dynamic_cast<Armor*>(
                    m_equipped_armor->get_data()
                );
                str_from_armor += armor->get_stats().strength;
            }
        }
        return static_cast<stattype>(
            m_player_class->get_strength() + str_from_armor
        );
    }

    [[nodiscard]] stattype get_intellect() const
    {
        stattype int_from_armor = 0;
        for (const auto m_equipped_armor : m_equipped_armors)
        {
            if (m_equipped_armor)
            {
                const auto* armor = dynamic_cast<Armor*>(
                    m_equipped_armor->get_data()
                );
                int_from_armor += armor->get_stats().intellect;
            }
        }
        return static_cast<stattype>(
            m_player_class->get_intellect() + int_from_armor
        );
    }

    [[nodiscard]] stattype get_agility() const
    {
        stattype agi_from_armor = 0;
        for (const auto m_equipped_armor : m_equipped_armors)
        {
            if (m_equipped_armor)
            {
                const auto* armor = dynamic_cast<Armor*>(
                    m_equipped_armor->get_data()
                );
                agi_from_armor += armor->get_stats().agility;
            }
        }
        return static_cast<stattype>(
            m_player_class->get_agility() + agi_from_armor
        );
    }

    [[nodiscard]] stattype get_armor() const
    {
        stattype arm_from_armor = 0;
        for (const auto m_equipped_armor : m_equipped_armors)
        {
            if (m_equipped_armor)
            {
                const auto* armor = dynamic_cast<Armor*>(
                    m_equipped_armor->get_data()
                );
                arm_from_armor += armor->get_stats().armor;
            }
        }
        return static_cast<stattype>(
            m_player_class->get_armor() + arm_from_armor
        );
    }

    [[nodiscard]] stattype get_resistance() const
    {
        stattype resist_from_armor = 0;
        for (const auto m_equipped_armor : m_equipped_armors)
        {
            if (m_equipped_armor)
            {
                const auto* armor = dynamic_cast<Armor*>(
                    m_equipped_armor->get_data()
                );
                resist_from_armor += armor->get_stats().resistance;
            }
        }
        return static_cast<stattype>(
            m_player_class->get_resistance() + resist_from_armor
        );
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

    [[nodiscard]] std::vector<Buff> get_buff_list() const
    {
        return m_player_class->buffs;
    }

    [[nodiscard]] std::vector<Item*> get_backpack_list() const
    {
        return m_backpack;
    }

    [[nodiscard]] Armor* get_equipped_armor_at(const int index) const
    {
        if (!m_equipped_armors[index]) return nullptr;
        return dynamic_cast<Armor*>(m_equipped_armors[index]->get_data());
    }

    [[nodiscard]] Weapon* get_equipped_weapon_at(const int index) const
    {
        if (!m_equipped_weapons[index]) return nullptr;
        return dynamic_cast<Weapon*>(m_equipped_weapons[index]->get_data());
    }

    // Modifiers
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

    void apply_buff(const Buff& buff) const
    {
        m_player_class->apply_buff(buff);
    }

    void add_to_backpack(Item* item)
    {
        m_backpack.push_back(item);
    }

    void cleanup_backpack()
    {
        const auto to_remove = std::stable_partition(
            m_backpack.begin(),
            m_backpack.end(),
            [](const Item* item) -> bool
            {
                return !item->get_marked_for_deletion();
            } // this is a lambda function
        );
        std::for_each(
            to_remove,
            m_backpack.end(),
            [](const Item* item) {delete item;}
        );
        m_backpack.erase(to_remove, m_backpack.end());
    }

private:
    PlayerCharacterDelegate* m_player_class;
    // std::unique_ptr<PlayerCharacterDelegate> m_player_class;
    Item* m_equipped_armors[static_cast<unsigned int>(ArmorSlot::num_slots)];
    Item* m_equipped_weapons[static_cast<unsigned int>(WeaponSlot::num_slots)];
    std::vector<Item*> m_backpack;

    friend class ItemManager;
};

#endif //PLAYER_CHARACTER_H
