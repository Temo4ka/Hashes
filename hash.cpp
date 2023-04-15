#include "headers/hash.h"

int hash_1(const char* inputString) {
    if (inputString == nullptr) return ERROR_HASH;
    return 1;
}

int hash_2(const char* inputString) {
    if (inputString == nullptr) return ERROR_HASH;

    return inputString[0];
}