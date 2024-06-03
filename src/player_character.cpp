#include "player_character.h"

#include "random.h"

PlayerCharacter::PlayerCharacter(PlayerCharacterDelegate* player)
:m_player_class(player)
{
    int i;
    for (i = 0; i < static_cast<unsigned int>(ArmorSlot::num_slots); i++)
        m_equipped_armors[i] = nullptr;

    for (i = 0; i < static_cast<unsigned int>(WeaponSlot::num_slots); i++)
        m_equipped_weapons[i] = nullptr;
}

PlayerCharacter::~PlayerCharacter()
{
    delete m_player_class;
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
[[nodiscard]] PlayerCharacterDelegate* PlayerCharacter::get_player() const
{
    return &*m_player_class;
}

[[nodiscard]] std::string PlayerCharacter::get_class_name() const
{
    return m_player_class->class_name;
}

[[nodiscard]] leveltype PlayerCharacter::get_level() const
{
    return m_player_class->get_level();
}

[[nodiscard]] exptype PlayerCharacter::get_current_exp() const
{
    return m_player_class->get_current_exp();
}

[[nodiscard]] exptype PlayerCharacter::get_exp_to_next_level() const
{
    return m_player_class->get_exp_to_next_level();
}

[[nodiscard]] pointtype PlayerCharacter::get_current_hp() const
{
    return m_player_class->hp->get_current();
}

[[nodiscard]] pointtype PlayerCharacter::get_max_hp() const
{
    return m_player_class->hp->get_initial();
}

[[nodiscard]] pointtype PlayerCharacter::get_current_mp() const
{
    if (m_player_class->mp)
        return m_player_class->mp->get_current();
    return 0;
}

[[nodiscard]] bool PlayerCharacter::is_max_hp() const
{
    return m_player_class->hp->get_initial() ==
           m_player_class->hp->get_current();
}

[[nodiscard]] pointtype PlayerCharacter::get_max_mp() const
{
    if (m_player_class->mp)
        return m_player_class->hp->get_initial();
    return 0;
}

[[nodiscard]] stattype PlayerCharacter::get_strength() const
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

[[nodiscard]] stattype PlayerCharacter::get_intellect() const
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

[[nodiscard]] stattype PlayerCharacter::get_agility() const
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

[[nodiscard]] stattype PlayerCharacter::get_armor() const
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

[[nodiscard]] stattype PlayerCharacter::get_resistance() const
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

[[nodiscard]] stattype PlayerCharacter::get_base_strength() const
{
    return m_player_class->get_base_strength();
}

[[nodiscard]] stattype PlayerCharacter::get_base_intellect() const
{
    return m_player_class->get_base_intellect();
}

[[nodiscard]] stattype PlayerCharacter::get_base_agility() const
{
    return m_player_class->get_base_agility();
}

[[nodiscard]] stattype PlayerCharacter::get_base_armor() const
{
    return m_player_class->get_base_armor();
}

[[nodiscard]] stattype PlayerCharacter::get_base_resistance() const
{
    return m_player_class->get_base_resistance();
}

[[nodiscard]] std::vector<Ability> PlayerCharacter::get_ability_list() const
{
    return m_player_class->abilities;
}

[[nodiscard]] std::vector<Buff> PlayerCharacter::get_buff_list() const
{
    return m_player_class->buffs;
}

[[nodiscard]] std::vector<Item*> PlayerCharacter::get_backpack_list() const
{
    return m_backpack;
}

[[nodiscard]] Armor*
PlayerCharacter::get_equipped_armor_at(const int index) const
{
    if (!m_equipped_armors[index]) return nullptr;
    return dynamic_cast<Armor*>(m_equipped_armors[index]->get_data());
}

[[nodiscard]] Weapon*
PlayerCharacter::get_equipped_weapon_at(const int index) const
{
    if (!m_equipped_weapons[index]) return nullptr;
    return dynamic_cast<Weapon*>(m_equipped_weapons[index]->get_data());
}

damagetype PlayerCharacter::melee_attack() const noexcept
{
    damagetype damage_done = 0; // unarmed

    const Weapon* equipped_weapon = get_equipped_weapon_at(
        static_cast<damagetype>(WeaponSlot::melee)
    );
    if (equipped_weapon)
    {
        damage_done = generate_number(
           equipped_weapon->get_min_damage(),
           equipped_weapon->get_max_damage()
       );
    }
    // Add super formula to calculate total damage
    // 1/4 of strength as a bonus of melee damage
    damage_done += static_cast<damagetype>(
        static_cast<float>(get_strength()) / 4.f
    );

    return damage_done;
}

damagetype PlayerCharacter::ranged_attack() const noexcept
{
    const Weapon* equipped_weapon = get_equipped_weapon_at(
        static_cast<damagetype>(WeaponSlot::ranged)
    );
    if (!equipped_weapon) return 0;

    damagetype damage_done = generate_number(
        equipped_weapon->get_min_damage(),
        equipped_weapon->get_max_damage()
    );
    // 1/4 of agility as a bonus of melee damage
    damage_done += static_cast<damagetype>(
        static_cast<float>(get_agility()) / 4.f
    );

    return damage_done;
}


// Modifiers
void PlayerCharacter::gain_exp(const exptype points) const
{
    m_player_class->gain_exp(points);
}

void PlayerCharacter::take_damage(const pointtype points) const
{
    m_player_class->hp->reduce(points);
}

void PlayerCharacter::heal(const pointtype points) const
{
    m_player_class->hp->increase(points);
}

void PlayerCharacter::apply_buff(const Buff& buff) const
{
    m_player_class->apply_buff(buff);
}

void PlayerCharacter::add_to_backpack(Item* item)
{
    m_backpack.push_back(item);
}

void PlayerCharacter::cleanup_backpack()
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

    // updated
    const auto to_remove_ref = std::stable_partition(
        m_backpack.begin(),
        m_backpack.end(),
        [](const Item* item) -> bool
        {
            return !item->get_marked_as_backback_ref_gone();
        } // this is a lambda function
    );
    m_backpack.erase(to_remove_ref, m_backpack.end());
}
