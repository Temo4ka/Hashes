#include "headers/hash.h"

int hashCtor(HashTable *hashTable, uint64_t (*hash)(const char *), size_t size) {
    catchNullptr(hashTable);
    catchNullptr(   hash  );

    hashTable ->  maxSize   = size;
    hashTable -> numOfElems =  0  ;
    hashTable ->   hash     = hash;

    hashTable ->   list     = (List *) calloc(size, sizeof(List));

    return EXIT_SUCCESS;
}

int initHashTable(HashTable *table, char *text) {
    catchNullptr(table);
    catchNullptr(text );

    char *curString = strtok(text, DELIM);
    while (curString != nullptr) {
        int err = hashAddString(table, curString);
        if (err) return err;
        fprintf(stderr, "%s\n", curString);

        curString = strtok(NULL, DELIM);
    }

    return EXIT_SUCCESS;
}

int hashAddString(HashTable *table, char *string) {
    catchNullptr(table );
    catchNullptr(string);

    int h = table -> hash(string) % MOD;

    // fprintf(stderr, "%d\n", table -> list[h].status);
    if (table -> list[h].status == InActive)
        listCtor(&(table -> list[h]));

    // fprintf(stderr, "%d\n", table -> list[h].status);

    Elem_t newElem = listElemCtor(string, h);

    int err = EXIT_SUCCESS;
    listPushBack(&(table -> list[h]), newElem, &err);
    fprintf(stderr, "%d\n", err);

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

int cycleL(int num);
int cycleR(int num);

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

uint64_t hash_7(const char *string) {
    size_t totalBytes = strlen(string);
    
    uint64_t hash = 5381;

    char *pointer = (char *) string;
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

bool isInList(List *list, const char* string) {
    if ( list  == nullptr) return 0;
    if (string == nullptr) return 0;

    if (list -> data[list -> head].data == string) return true;
    
    for (size_t cur = list -> next[list -> head]; cur != list -> head; cur = list -> next[cur])
        if (list -> data[cur].data == string) return true;

    return false;
}