#include "level_system.h"

LevelSystem::LevelSystem()
{
    current_level = 1u;
    current_exp = 0u;
    exp_to_next_level = kLevel2At;
}

void LevelSystem::gain_exp(const exptype gained_exp)
{
    current_exp += gained_exp;
    check_if_leveled();
}

[[nodiscard]] leveltype LevelSystem::get_level() const
{
    return current_level;
}

[[nodiscard]] exptype LevelSystem::get_current_exp() const
{
    return current_exp;
}

[[nodiscard]] exptype LevelSystem::get_exp_to_next_level() const
{
    return exp_to_next_level;
}