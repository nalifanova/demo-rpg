#ifndef TESTS_H
#define TESTS_H

#include <iostream>

#include "player_character.h"

void separator(const std::string& func_name, const int& line);

void show_stats(const PlayerCharacter& char_);

void show_abilities(const PlayerCharacter& char_);

void test_characters();

void test_level_up();

void test_buff();

void test_core_stats();

void test_equipment();

void test_potions();

#endif //TESTS_H
