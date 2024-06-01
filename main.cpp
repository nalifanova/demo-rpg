#include <iostream>

#include "game_play.h"
#include "tests.h"

void visual_testing()
{
    test_characters();
    test_level_up();
    test_buff();
    test_core_stats();
    test_equipment();
    test_potions();
    test_inventory();
    test_randm();
}


int main(int argc, char** argv)
{
    game_play_();
    // visual_testing();

    return EXIT_SUCCESS;
}
