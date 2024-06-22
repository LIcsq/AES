#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <iomanip>
#include <array>
#include <string>
#include <cstdint>

void printState(const std::array<uint8_t, 16> &state);
void padMessage(std::string &message);
void addSizeInfo(std::array<uint8_t, 16> &data, size_t originalSize);
size_t extractSizeInfo(const std::array<uint8_t, 16> &data);

#endif // UTILITIES_H
