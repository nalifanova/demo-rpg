#ifndef POINT_STACK_H
#define POINT_STACK_H

#include "types.h"

class PointStack // I can't stand PointWell, aghrr
{
public:
    PointStack();

    PointStack(pointtype current, pointtype max);

    [[nodiscard]] pointtype get_initial() const;

    [[nodiscard]] pointtype get_current() const;

    [[nodiscard]] pointtype is_full() const;

    bool set_max(pointtype new_max_points);

    void reduce(pointtype amount);

    void increase(pointtype amount);

private:
    pointtype m_current;
    pointtype m_initial; // stands for Max Value;
};

#endif //POINT_STACK_H
