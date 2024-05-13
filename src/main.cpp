#include <iostream>
#include <vector>

#include "cleric.h"
#include "rogue.h"
#include "warrior.h"
#include "wizard.h"

void show_stats(const Character& char_)
{
    std::cout << char_.name << ":\n" <<
    "-MaxHP: " << char_.get_initial_hp() << '\n' <<
    "-Strength: " << char_.get_strength() << '\n' <<
    "-Intellect: " << char_.get_intellect() << '\n' <<
    std::endl;
}

int main()
{
    auto const war = new Warrior;
    auto const wiz = new Wizard;
    auto const cler = new Cleric;
    auto const rog = new Rogue;

    std::vector<Character*> const chars {war, wiz, cler, rog};
    for (auto const c: chars)
        show_stats(*c);

    // Dev Note: Cleric class has extra inheritance from StatBlock
    std::cout << "Cleric's resistance: " << cler->get_resistance() << '\n';
    std::cout << "Cleric's luck: " << cler->get_luck() << '\n';
    std::cout << "Cleric exp: " << cler->get_level() << '\n';

    for (const auto c: chars) delete c;  // delete pointers

    return 0;
}
