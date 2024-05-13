#include <iostream>
#include <vector>

#include "cleric.h"
#include "rogue.h"
#include "warrior.h"
#include "wizard.h"

void show_stats(Character char_)
{
    std::cout << char_.name << ":\n" <<
    "-MaxHP: " << char_.get_initial_hp() << '\n' <<
    "-Strength: " << char_.get_strength() << '\n' <<
    "-Intellect: " << char_.get_intellect() << '\n' <<
    "-Luck: " << char_.get_luck() << '\n' <<
    // "-Resistance: " << char_.get_resistance() << '\n' <<
    std::endl;
}

int main()
{
    auto war = new Warrior;
    auto wiz = new Wizard;
    auto cler = new Cleric;
    auto rog = new Rogue;

    std::vector<Character*> chars {war, wiz, cler, rog};
    for (auto const c: chars)
    {
        show_stats(*c);
    }

    for (const auto c: chars) delete c;  // delete pointers
    return 0;
}
