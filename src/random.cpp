#include "random.h"

int generate_number(const int low, const int high)
{
    srand(static_cast<int>(time(nullptr))); // Providing a seed value
    const double d = rand() / (static_cast<double>(RAND_MAX) + 1);
    const double s = d * (static_cast<double>(high) - low + 1);
    return static_cast<int>(floor(low + s));
}
