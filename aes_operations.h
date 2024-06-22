#ifndef AES_OPERATIONS_H
#define AES_OPERATIONS_H

#include <array>
#include <cstdint>
#include "constants.h"

void SubBytes(std::array<uint8_t, 16> &state);
void InvSubBytes(std::array<uint8_t, 16> &state);
void ShiftRows(std::array<uint8_t, 16> &state);
void InvShiftRows(std::array<uint8_t, 16> &state);
uint8_t gmul(uint8_t a, uint8_t b);
void MixColumns(std::array<uint8_t, 16> &state);
void InvMixColumns(std::array<uint8_t, 16> &state);
void AddRoundKey(std::array<uint8_t, 16> &state, const std::array<uint8_t, 176> &roundKeys, int round);
void AES_Encrypt(std::array<uint8_t, 16> &plaintext, const std::array<uint8_t, 16> &key);
void AES_Decrypt(std::array<uint8_t, 16> &ciphertext, const std::array<uint8_t, 16> &key);

#endif // AES_OPERATIONS_H
