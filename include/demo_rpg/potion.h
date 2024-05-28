#ifndef POTION_H
#define POTION_H

#include "item.h"

class Potion final: public ItemDelegate
{
public:
    ~Potion() override;

private:
    explicit Potion(
        std::string name,
        pointtype hp_heal = 1u,
        itemcount quantity = 1u,
        Buff* buff = nullptr
    );

public:
    Buff* buff;
    pointtype heal_amount;
    itemcount quantity;

private:
    friend class ItemManager;
};

#endif //POTION_H
