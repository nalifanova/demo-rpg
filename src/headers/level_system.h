#ifndef LEVEL_SYSTEM_H
#define LEVEL_SYSTEM_H

#include "types.h"

class LevelSystem
{
public:
    LevelSystem()
    {
        current_level = 1u;
        current_exp = 0u;
        exp_to_next_level = kLevel2At;
    }

    virtual ~LevelSystem() = default;

    void gain_exp(const exptype gained_exp)
    {
        current_exp += gained_exp;
        check_if_leveled();
    }

    [[nodiscard]] leveltype get_level() const
    {
        return current_level;
    }

    [[nodiscard]] exptype get_current_exp() const
    {
        return current_exp;
    }

    [[nodiscard]] exptype get_exp_to_next_level() const
    {
        return exp_to_next_level;
    }

    virtual void level_up() = 0;

protected:
    bool check_if_leveled()
    {
        static constexpr leveltype kLevelScaler = 2u;
        if (current_exp >= exp_to_next_level)
        {
            current_level++;
            level_up();
            exp_to_next_level *= kLevelScaler;
            return true;
        }
        return false;
    }

public:
    // gaining exp has exponential growth
    static constexpr exptype kLevel2At = 100u;

protected:
    leveltype current_level = 0u;
    exptype current_exp;
    exptype exp_to_next_level;
};

#endif //LEVEL_SYSTEM_H
