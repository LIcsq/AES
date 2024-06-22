#include <iostream>
#include <string>
#include <array>
#include "aes_operations.h"
#include "utilities.h"

int main() {
    std::array<uint8_t, 16> key = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x09, 0xcf, 0x4f, 0x3c, 0x4f, 0x3c};

    std::cout << "Enter a message: ";
    std::string input;
    std::getline(std::cin, input);

    size_t originalSize = input.size();
    padMessage(input);

    std::array<uint8_t, 16> plaintext;
    memcpy(plaintext.data(), input.data(), 16);
    addSizeInfo(plaintext, originalSize);

    std::cout << "Plaintext: ";
    printState(plaintext);

    AES_Encrypt(plaintext, key);

    std::cout << "Ciphertext: ";
    printState(plaintext);

    AES_Decrypt(plaintext, key);

    std::cout << "Decrypted: ";
    printState(plaintext);

    size_t decryptedSize = extractSizeInfo(plaintext);
    std::cout << "Decrypted message: " << std::string(reinterpret_cast<char*>(plaintext.data()), decryptedSize) << std::endl;

    return 0;
}
