#ifndef TESTS_H
#define TESTS_H

#include <iostream>

#include "player_classes.h"

void separator(const std::string& func_name, const int& line);

void show_stats(const PlayerCharacter& char_);

void show_abilities(const PlayerCharacter& char_);

void test_characters();

void test_level_up();

void test_buff();

#endif //TESTS_H
