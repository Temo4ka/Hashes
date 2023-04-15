#include "headers/hash.h"
#include <string.h>


int hash_1(const char* inputString) {
    if (inputString == nullptr) return ERROR_HASH;
    return 1;
}

int hash_2(const char* inputString) {
    if (inputString == nullptr) return ERROR_HASH;

    return inputString[0];
}

int hash_3(const char* inputString) {
    if (inputString == nullptr) return ERROR_HASH;

    return strlen(inputString);
}

int hash_4(const char* inputString) {
    if (inputString == nullptr) return ERROR_HASH;

    int sum =          0         ;
    int len = strlen(inputString);

    for (int cur = 0; cur < len; cur++) sum += inputString[cur];

    return sum;
}

int hash_5(const char* inputString) {
    if (inputString == nullptr) return ERROR_HASH;

    int hash =         0          ;
    int len  = strlen(inputString);

    for (int cur = 0; cur < len; cur++) {
        hash ^= inputString[cur];
        hash  =   cycleL(hash)  ;
    }

    return hash;
}

int hash_6(const char* inputString) {
    if (inputString == nullptr) return ERROR_HASH;

    int hash =         0          ;
    int len  = strlen(inputString);

    for (int cur = 0; cur < len; cur++) {
        hash ^= inputString[cur];
        hash  =   cycleR(hash)  ;
    }

    return hash;
}

int hash_7(const char* inputString) {
    if (inputString == nullptr) return ERROR_HASH;

    int hash =         0          ;
    int len  = strlen(inputString);

    for (int cur = 0; cur < len; cur++) {
        hash ^= inputString[cur];
        hash  =   cycleR(hash)  ;
    }

    return hash;
}

int cycleR(int num) {
    int lastS = num / 10;

    num = num / 10;

    int k = 1;
    while (num / k) k *= 10;
    num += k * lastS;

    return num;
}

int cycleL(int num) {
    int k = 1;
    while (num / k) k *= 10;
    k /= 10;

    int FirstS = num / k;
    num -= FirstS * k;

    num = num * 10 + FirstS;

    return num;
}