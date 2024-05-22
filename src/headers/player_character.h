#ifndef PLAYER_CHARACTER_H
#define PLAYER_CHARACTER_H

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
        stattype str_from_armor = 0;
        // Armor* armor = nullptr;
        for (int i = 0; i < static_cast<int>(ArmorSlot::num_slots); i++)
        // for (const auto m_equipped_armor : m_equipped_armors)
        {
            if (m_equipped_armors[i])
                str_from_armor += m_equipped_armors[i]->get_stats().strength;
        }
        return static_cast<stattype>(
            m_player_class->get_strength() + str_from_armor
        );
    }

    [[nodiscard]] stattype get_intellect() const
    {
        stattype int_from_armor = 0;
        // for (const auto m_equipped_armor : m_equipped_armors)
        // {
        //     if (m_equipped_armor)
        //         int_from_armor += m_equipped_armor->get_stats().intellect;
        // }
        return static_cast<stattype>(
            m_player_class->get_intellect() + int_from_armor
        );
    }

    [[nodiscard]] stattype get_agility() const
    {
        stattype agi_from_armor = 0;
        // for (const auto m_equipped_armor : m_equipped_armors)
        // {
        //     if (m_equipped_armor)
        //         agi_from_armor += m_equipped_armor->get_stats().agility;
        // }
        return static_cast<stattype>(
            m_player_class->get_agility() + agi_from_armor
        );
    }

    [[nodiscard]] stattype get_armor() const
    {
        stattype armor_from_armor = 0;
        // for (const auto m_equipped_armor : m_equipped_armors)
        // {
        //     if (m_equipped_armor)
        //         armor_from_armor += m_equipped_armor->get_stats().armor;
        // }
        return static_cast<stattype>(
            m_player_class->get_armor() + armor_from_armor
        );
    }

    [[nodiscard]] stattype get_resistance() const
    {
        stattype resist_from_armor = 0;
        // for (const auto m_equipped_armor : m_equipped_armors)
        // {
        //     if (m_equipped_armor)
        //         resist_from_armor += m_equipped_armor->get_stats().resistance;
        // }
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

    [[nodiscard]] EquipmentDelegate* get_equipped_armor_at(const int index) const
    {
        if (!m_equipped_armors[index])
            return nullptr;
        return dynamic_cast<Armor*>(m_equipped_armors[index]);
    }

    [[nodiscard]] EquipmentDelegate* get_equipped_weapon_at(const int index) const
    {
        return dynamic_cast<Weapon*>(m_equipped_weapons[index]);
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

    // modify when we have an inventory
    bool equip(const Item* equipment)
    {
        if (!equipment || !equipment->get_data()) return false;

        if (auto* armor = dynamic_cast<Armor*>(equipment->get_data()))
        {
            const auto slot_num = static_cast<unsigned int>(armor->get_slot());
            if (m_equipped_armors[slot_num])
            {
                // delete m_equipped_armors[slot_num]; // move to inventory
                m_equipped_armors[slot_num] = nullptr;
            }
            m_equipped_armors[slot_num] = armor;
            return true;
        }

        if (auto* weapon = dynamic_cast<Weapon*>(equipment->get_data()))
        {
            const auto slot_num = static_cast<unsigned int>(weapon->get_slot());
            if (m_equipped_weapons[slot_num])
            {
                // delete m_equipped_weapons[slot_num]; // move to inventory
                m_equipped_weapons[slot_num] = nullptr;
            }
            m_equipped_weapons[slot_num] = weapon;

            return true;
        }
        return false;
    }

    bool use(const Item* item_to_use)
    {
        if (!item_to_use || !item_to_use->get_data()) return false;

        Potion* potion = dynamic_cast<Potion*>(item_to_use->get_data());

        if (potion)
        {
            // apply buff if it has one
            if (potion->buff)
                apply_buff(*potion->buff);

            // if max health and trying to use a heal potion, don't use it
            if (m_player_class->hp->is_full() && !potion->buff)
                return false; // don't use the potion

            // increase hp by the heal amount (could be 0 and that's fine)
            m_player_class->hp->increase(potion->heal_amount);
            // we used the potion, reduce quantity
            potion->quantity--;

            if (potion->quantity == 0)
                delete potion;
            return true;
        }
        return false;
    }

private:
    PlayerCharacterDelegate* m_player_class = nullptr;
    // std::unique_ptr<PlayerCharacterDelegate> m_player_class;
    EquipmentDelegate* m_equipped_armors[
        static_cast<unsigned int>(ArmorSlot::num_slots)
    ]{};
    EquipmentDelegate* m_equipped_weapons[
        static_cast<unsigned int>(WeaponSlot::num_slots)
    ]{};
    std::vector<Item*> m_backpack;
};

#endif //PLAYER_CHARACTER_H
