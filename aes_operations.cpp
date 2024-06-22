#include "aes_operations.h"
#include "key_expansion.h"
#include <cstring>

void SubBytes(std::array<uint8_t, 16> &state) {
    for (int i = 0; i < 16; i++) {
        state[i] = sbox[state[i]];
    }
}

void InvSubBytes(std::array<uint8_t, 16> &state) {
    for (int i = 0; i < 16; i++) {
        state[i] = rsbox[state[i]];
    }
}

void ShiftRows(std::array<uint8_t, 16> &state) {
    std::array<uint8_t, 16> temp;
    memcpy(temp.data(), state.data(), 16);

    state[0] = temp[0];
    state[1] = temp[5];
    state[2] = temp[10];
    state[3] = temp[15];

    state[4] = temp[4];
    state[5] = temp[9];
    state[6] = temp[14];
    state[7] = temp[3];

    state[8] = temp[8];
    state[9] = temp[13];
    state[10] = temp[2];
    state[11] = temp[7];

    state[12] = temp[12];
    state[13] = temp[1];
    state[14] = temp[6];
    state[15] = temp[11];
}

void InvShiftRows(std::array<uint8_t, 16> &state) {
    std::array<uint8_t, 16> temp;
    memcpy(temp.data(), state.data(), 16);

    state[0] = temp[0];
    state[1] = temp[13];
    state[2] = temp[10];
    state[3] = temp[7];

    state[4] = temp[4];
    state[5] = temp[1];
    state[6] = temp[14];
    state[7] = temp[11];

    state[8] = temp[8];
    state[9] = temp[5];
    state[10] = temp[2];
    state[11] = temp[15];

    state[12] = temp[12];
    state[13] = temp[9];
    state[14] = temp[6];
    state[15] = temp[3];
}

uint8_t gmul(uint8_t a, uint8_t b) {
    uint8_t p = 0;
    uint8_t hi_bit_set;
    for (int i = 0; i < 8; i++) {
        if (b & 1) {
            p ^= a;
        }
        hi_bit_set = (a & 0x80);
        a <<= 1;
        if (hi_bit_set) {
            a ^= 0x1b; // XOR with the irreducible polynomial
        }
        b >>= 1;
    }
    return p;
}

void MixColumns(std::array<uint8_t, 16> &state) {
    uint8_t Tmp, Tm, t;
    for (int i = 0; i < 4; i++) {
        t = state[i * 4];
        Tmp = state[i * 4] ^ state[i * 4 + 1] ^ state[i * 4 + 2] ^ state[i * 4 + 3];
        Tm = state[i * 4] ^ state[i * 4 + 1];
        Tm = gmul(Tm, 0x02);
        state[i * 4] ^= Tm ^ Tmp;
        Tm = state[i * 4 + 1] ^ state[i * 4 + 2];
        Tm = gmul(Tm, 0x02);
        state[i * 4 + 1] ^= Tm ^ Tmp;
        Tm = state[i * 4 + 2] ^ state[i * 4 + 3];
        Tm = gmul(Tm, 0x02);
        state[i * 4 + 2] ^= Tm ^ Tmp;
        Tm = state[i * 4 + 3] ^ t;
        Tm = gmul(Tm, 0x02);
        state[i * 4 + 3] ^= Tm ^ Tmp;
    }
}

void InvMixColumns(std::array<uint8_t, 16> &state) {
    uint8_t a, b, c, d;
    for (int i = 0; i < 4; i++) {
        a = state[i * 4];
        b = state[i * 4 + 1];
        c = state[i * 4 + 2];
        d = state[i * 4 + 3];
        state[i * 4] = gmul(a, 0x0e) ^ gmul(b, 0x0b) ^ gmul(c, 0x0d) ^ gmul(d, 0x09);
        state[i * 4 + 1] = gmul(a, 0x09) ^ gmul(b, 0x0e) ^ gmul(c, 0x0b) ^ gmul(d, 0x0d);
        state[i * 4 + 2] = gmul(a, 0x0d) ^ gmul(b, 0x09) ^ gmul(c, 0x0e) ^ gmul(d, 0x0b);
        state[i * 4 + 3] = gmul(a, 0x0b) ^ gmul(b, 0x0d) ^ gmul(c, 0x09) ^ gmul(d, 0x0e);
    }
}

void AddRoundKey(std::array<uint8_t, 16> &state, const std::array<uint8_t, 176> &roundKeys, int round) {
    for (int i = 0; i < 16; i++) {
        state[i] ^= roundKeys[round * 16 + i];
    }
}

void AES_Encrypt(std::array<uint8_t, 16> &plaintext, const std::array<uint8_t, 16> &key) {
    std::array<uint8_t, 176> roundKeys;
    std::array<uint8_t, 16> state;
    memcpy(state.data(), plaintext.data(), 16);

    KeyExpansion(key, roundKeys);
    AddRoundKey(state, roundKeys, 0);

    for (int round = 1; round <= 9; round++) {
        SubBytes(state);
        ShiftRows(state);
        MixColumns(state);
        AddRoundKey(state, roundKeys, round);
    }

    SubBytes(state);
    ShiftRows(state);
    AddRoundKey(state, roundKeys, 10);

    memcpy(plaintext.data(), state.data(), 16);
}

void AES_Decrypt(std::array<uint8_t, 16> &ciphertext, const std::array<uint8_t, 16> &key) {
    std::array<uint8_t, 176> roundKeys;
    std::array<uint8_t, 16> state;
    memcpy(state.data(), ciphertext.data(), 16);

    KeyExpansion(key, roundKeys);
    AddRoundKey(state, roundKeys, 10);

    for (int round = 9; round >= 1; round--) {
        InvShiftRows(state);
        InvSubBytes(state);
        AddRoundKey(state, roundKeys, round);
        InvMixColumns(state);
    }

    InvShiftRows(state);
    InvSubBytes(state);
    AddRoundKey(state, roundKeys, 0);

    memcpy(ciphertext.data(), state.data(), 16);
}
