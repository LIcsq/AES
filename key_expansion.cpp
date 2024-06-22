#include "key_expansion.h"

void KeyExpansion(const std::array<uint8_t, 16> &key, std::array<uint8_t, 176> &roundKeys) {
    std::array<uint8_t, 4> temp{};
    uint8_t k;
    int i = 0;

    while (i < 16) {
        roundKeys[i] = key[i];
        i++;
    }

    i = 16;
    while (i < 176) {
        for (int j = 0; j < 4; j++) {
            temp[j] = roundKeys[(i - 4) + j];
        }
        if (i % 16 == 0) {
            k = temp[0];
            temp[0] = sbox[temp[1]] ^ rcon[(i / 16) - 1];
            temp[1] = sbox[temp[2]];
            temp[2] = sbox[temp[3]];
            temp[3] = sbox[k];
        }
        for (int j = 0; j < 4; j++) {
            roundKeys[i] = roundKeys[i - 16] ^ temp[j];
            i++;
        }
    }
}
