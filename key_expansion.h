#ifndef KEY_EXPANSION_H
#define KEY_EXPANSION_H

#include <array>
#include <cstdint>
#include "constants.h"

void KeyExpansion(const std::array<uint8_t, 16> &key, std::array<uint8_t, 176> &roundKeys);

#endif // KEY_EXPANSION_H
