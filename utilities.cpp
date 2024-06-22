#include "utilities.h"

void printState(const std::array<uint8_t, 16> &state) {
    for (const auto &val : state) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << int(val) << " ";
    }
    std::cout << std::endl;
}

void padMessage(std::string &message) {
    size_t originalSize = message.size();
    message.append(16 - originalSize % 16, '\0');
}

void addSizeInfo(std::array<uint8_t, 16> &data, size_t originalSize) {
    data[14] = (originalSize >> 8) & 0xFF;
    data[15] = originalSize & 0xFF;
}

size_t extractSizeInfo(const std::array<uint8_t, 16> &data) {
    return (data[14] << 8) | data[15];
}
