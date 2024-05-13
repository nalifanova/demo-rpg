#include "tests.h"

#include <vector>

#include "cleric.h"
#include "rogue.h"
#include "warrior.h"
#include "wizard.h"


void separator(const std::string& func_name)
{
    std::cout << std::string(30, '-') <<
        func_name << std::string(30, '-') << '\n';
}

void show_stats(const Character& char_, const std::string& title)
{
    std::cout << title << '\n' <<
    "-HP: " << char_.get_initial_hp() << '\n' <<
    "-Strength: " << char_.get_strength() << '\n' <<
    "-Intellect: " << char_.get_intellect() << '\n';
}

void test_characters()
{
    separator(__func__);

    auto const war = new Warrior;
    auto const wiz = new Wizard;
    auto const cler = new Cleric;
    auto const rog = new Rogue;

    std::vector<Character*> const chars {war, wiz, cler, rog};
    for (auto const c: chars)
    {
        const std::string title = std::string(c->name) + ":\n";
        show_stats(*c, "" + std::string(c->name));
        std::cout << '\n';
    }

    // Dev Note: Cleric class has extra inheritance from StatBlock
    std::cout << "Cleric's resistance: " << cler->get_resistance() << '\n';
    std::cout << "Cleric's luck: " << cler->get_luck() << '\n';
    std::cout << "Cleric exp: " << cler->get_level() << '\n';

    for (const auto c: chars) delete c;  // delete pointers
}

void test_level_up()
{
    separator(__func__);

    Cleric cleric;
    for (int i = 0; i < 4; i++)
    {
        std::cout << '\n';
        const std::string title =
            std::string(cleric.name) + " (level: " +
            std::to_string(cleric.get_level()) + ", exp: " +
            std::to_string(cleric.get_exp()) + "/" +
            std::to_string(cleric.get_exp_to_next_level()) + "):";

        show_stats(cleric, title);
        cleric.gain_exp(100);
    }
}
