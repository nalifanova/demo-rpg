#ifndef LEVEL_SYSTEM_H
#define LEVEL_SYSTEM_H

#include "types.h"

class LevelSystem
{
public:
    LevelSystem();

    virtual ~LevelSystem() = default;

    void gain_exp(exptype gained_exp);

    [[nodiscard]] leveltype get_level() const;

    [[nodiscard]] exptype get_current_exp() const;

    [[nodiscard]] exptype get_exp_to_next_level() const;

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
