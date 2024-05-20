#ifndef TYPES_H
#define TYPES_H

#include <iostream>

// Note: it's nice idea to define a desired type. Easy to change, but!
// It creates boundaries with flexibility in classes, like impossibility
// to override the method with different type.
typedef std::uint16_t leveltype; // 2^8 - 1 equals 255 (unsigned)
typedef std::uint64_t exptype; // 2^64 - 1 equals ooh! (unsigned)

typedef std::uint16_t pointtype;
typedef std::int16_t stattype;

typedef std::uint16_t damagetype;

#endif //TYPES_H
