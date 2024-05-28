#ifndef PLAYER_CHARACTER_H
#define PLAYER_CHARACTER_H

#include <algorithm>

#include "armor.h"
#include "item.h"
#include "player_character_delegate.h"
#include "weapon.h"

class PlayerCharacter final
{
public:
    PlayerCharacter() = delete;

    /* error: call to implicitly-deleted copy constructor of
     * 'const PlayerCharacter' (src/tests.cpp:55:9: ... warrior, wizard..)
     * TODO: find a reason why?
     */
    // PlayerCharacter(const PlayerCharacter&) = delete; // no copy
    // PlayerCharacter(const PlayerCharacter&&) = delete; // no move

    explicit PlayerCharacter(PlayerCharacterDelegate* player);

    ~PlayerCharacter();

    // Getters
    [[nodiscard]] PlayerCharacterDelegate* get_player() const;

    [[nodiscard]] std::string get_class_name() const;

    [[nodiscard]] leveltype get_level() const;

    [[nodiscard]] exptype get_current_exp() const;

    [[nodiscard]] exptype get_exp_to_next_level() const;

    [[nodiscard]] pointtype get_current_hp() const;

    [[nodiscard]] pointtype get_max_hp() const;

    [[nodiscard]] pointtype get_current_mp() const;

    [[nodiscard]] pointtype get_max_mp() const;

    [[nodiscard]] stattype get_strength() const;

    [[nodiscard]] stattype get_intellect() const;

    [[nodiscard]] stattype get_agility() const;

    [[nodiscard]] stattype get_armor() const;

    [[nodiscard]] stattype get_resistance() const;

    [[nodiscard]] stattype get_base_strength() const;

    [[nodiscard]] stattype get_base_intellect() const;

    [[nodiscard]] stattype get_base_agility() const;

    [[nodiscard]] stattype get_base_armor() const;

    [[nodiscard]] stattype get_base_resistance() const;

    [[nodiscard]] std::vector<Ability> get_ability_list() const;

    [[nodiscard]] std::vector<Buff> get_buff_list() const;

    [[nodiscard]] std::vector<Item*> get_backpack_list() const;

    [[nodiscard]] Armor* get_equipped_armor_at(int index) const;

    [[nodiscard]] Weapon* get_equipped_weapon_at(int index) const;

    // Modifiers
    void gain_exp(exptype points) const;

    void take_damage(pointtype points) const;

    void heal(pointtype points) const;

    void apply_buff(const Buff& buff) const;

    void add_to_backpack(Item* item);

    void cleanup_backpack();

private:
    PlayerCharacterDelegate* m_player_class;
    // std::unique_ptr<PlayerCharacterDelegate> m_player_class;
    Item* m_equipped_armors[static_cast<unsigned int>(ArmorSlot::num_slots)];
    Item* m_equipped_weapons[static_cast<unsigned int>(WeaponSlot::num_slots)];
    std::vector<Item*> m_backpack;

    friend class ItemManager;
};

#endif //PLAYER_CHARACTER_H
