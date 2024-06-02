#ifndef RANDOM_H
#define RANDOM_H

#include <iostream>
#include <random>

void init_random_seed();
/*
 * Function: generate_number
 * Usage: std::uint16_t number = generate_number(low, high);
 * --------------------------------------------------
 * Retrieve a random number between offset and range
 * low - The starting point for the range of random numbers
 * high - The number of values between first and the last possible random
 *        number including the limits.
 */
int generate_number(int low, int high);

#endif //RANDOM_H
