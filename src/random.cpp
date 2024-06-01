#include "random.h"

void init_random_seed()
{
    static bool initialized = false;
    if (!initialized)
    {
        srand(static_cast<int>(time(nullptr)));
        initialized = true;
    }
}

int generate_number(const int low, const int high)
{
    init_random_seed();
    const double d = rand() / (static_cast<double>(RAND_MAX) + 1);
    const double s = d * (static_cast<double>(high) - low + 1);
    return static_cast<int>(floor(low + s));
}
