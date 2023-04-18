#include "headers/hash.h"

int initHashTable(HashTable *table, char *text, uint64_t (*hash)(const char *)) {
    catchNullptr(table);
    catchNullptr(text );

    char *curString = strtok(text, DELIM);
    while (curString != nullptr) {
        curString = strtok(nullptr, DELIM);

        int err = hashAddString(table, curString, hash);
        if (err) return err;
    }

    return EXIT_SUCCESS;
}

int hashAddString(HashTable *table, char *string, uint64_t (*hash)(const char *)) {
    catchNullptr(table );
    catchNullptr(string);

    int h = hash(string) % MOD;

    Elem_t newElem = listElemCtor(string, h);

    int err = EXIT_SUCCESS;
    listPushBack(&(table -> list[h]), newElem, &err);

    table -> numOfElems += 1;

    return err;
}

uint64_t hash_1(const char* inputString) {
    if (inputString == nullptr) return ERROR_HASH;
    return 1;
}

uint64_t hash_2(const char* inputString) {
    if (inputString == nullptr) return ERROR_HASH;

    return inputString[0];
}

uint64_t hash_3(const char* inputString) {
    if (inputString == nullptr) return ERROR_HASH;

    return strlen(inputString);
}

uint64_t hash_4(const char* inputString) {
    if (inputString == nullptr) return ERROR_HASH;

    uint64_t sum =          0         ;
    uint64_t len = strlen(inputString);

    for (int cur = 0; cur < len; cur++) sum += inputString[cur];

    return sum;
}

uint64_t hash_5(const char* inputString) {
    if (inputString == nullptr) return ERROR_HASH;

    uint64_t hash =         0          ;
    uint64_t len  = strlen(inputString);

    for (int cur = 0; cur < len; cur++) {
        hash ^= inputString[cur];
        hash  =   cycleL(hash)  ;
    }

    return hash;
}

uint64_t hash_6(const char* inputString) {
    if (inputString == nullptr) return ERROR_HASH;

    uint64_t hash =         0          ;
    uint64_t len  = strlen(inputString);

    for (int cur = 0; cur < len; cur++) {
        hash ^= inputString[cur];
        hash  =   cycleR(hash)  ;
    }

    return hash;
}

uint64_t hash_7(const void *memPointer, size_t totalBytes) {
    uint64_t hash = 5381;

    char *pointer = (char *) memPointer;
    for (size_t currentByte = 0; currentByte < totalBytes; currentByte++) {
        hash = hash * 33 + pointer[currentByte];
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