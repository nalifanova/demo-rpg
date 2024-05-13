#ifndef HITPOINTTYPES_H
#define HITPOINTTYPES_H

typedef std::uint16_t hptype;  // 2^16 - 1 equals 65,535 (unsigned)
typedef std::uint16_t stattype; //
typedef std::uint16_t leveltype; // 2^8 - 1 equals 255 (unsigned)
typedef std::uint64_t exptype; // 2^64 - 1 equals ooh! (unsigned)

// DevNote: for some reason, std::uint8_t prints weird symbols in console

#endif //HITPOINTTYPES_H
