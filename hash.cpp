#include "headers/hash.h"

int hashCtor(HashTable *hashTable, HashFunc_t hash, size_t size) {
    catchNullptr(hashTable);
    catchNullptr(   hash  );

    hashTable ->  maxSize   = size;
    hashTable -> numOfElems =  0  ;
    hashTable ->   hash     = hash;

    hashTable ->   list     = (List *) calloc(size, sizeof(List));

    return EXIT_SUCCESS;
}

int hashDtor(HashTable *hashTable) {
    catchNullptr(hashTable);

    for (int cur = 0; cur < MOD; cur++)
        if (hashTable -> list[cur].status == Active && listDtor(&(hashTable -> list[cur]))) return EXIT_FAILURE;
        
    free(hashTable -> list);

    return EXIT_SUCCESS;
}

int initHashTable(HashTable *table, const char *text) {
    catchNullptr(table);
    catchNullptr(text );

    char *buffer = (char *) calloc(BUFFER_SZ, sizeof(char));
          buffer = strcpy(buffer, text);
    
    catchNullptr(buffer);

    char *curString = strtok(buffer, DELIM);
    while (curString != nullptr) {
        int err = hashAddString(table, curString);
        if (err) return err;

        curString = strtok(NULL, DELIM);
    }

    return EXIT_SUCCESS;
}

int hashAddString(HashTable *table, char *string) {
    catchNullptr(table );
    catchNullptr(string);

    int h = table -> hash(string) % MOD;

    if (table -> list[h].status == InActive)
        listCtor(&(table -> list[h]));

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

uint64_t cycleL(uint64_t num);
uint64_t cycleR(uint64_t num);

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

uint64_t cycleR(uint64_t num) {
    uint64_t lastS = num & 1;

    num = num >> (uint64_t) 1;

    num = ((lastS << SHIFT) | num);

    return num;
}

uint64_t cycleL(uint64_t num) {
    uint64_t mask = (uint64_t) 1 << SHIFT;

    bool k = (mask & num);

    num = num << (uint64_t) 1;
    num |= k;

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