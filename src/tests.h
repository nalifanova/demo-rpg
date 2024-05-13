#ifndef TESTS_H
#define TESTS_H

#include <iostream>

#include "character.h"

void separator(const std::string& func_name);

void show_stats(const Character& char_, const std::string& title);

void test_characters();

void test_level_up();

#endif //TESTS_H
