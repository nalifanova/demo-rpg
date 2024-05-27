#include "headers/potion.h"

Potion::~Potion()
{
    if (buff)
    {
        delete buff;
        buff = nullptr;
    }
}

// PRIVATE
Potion::Potion(
    const std::string name,
    const pointtype hp_heal,
    const itemcount quantity,
    Buff* buff
):
ItemDelegate(name), buff(buff), heal_amount(hp_heal), quantity(quantity){}
