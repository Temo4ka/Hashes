//-------------------------------------------------------------\\
//     Seven types of hashes are presented in this file        \\
//-------------------------------------------------------------\\

#pragma "once"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "list.h"

struct HashTable {
    List *list = (List *) calloc(MOD, sizeof(List));

    size_t numOfElems = 0;
    size_t   maxSize  = 0;

    HashFunc_t hash = nullptr;
};

int hashCtor(HashTable *hashTable, HashFunc_t hash, size_t size = MOD);

int hashDtor(HashTable *hashTable);

int initHashTable(HashTable *table, const char *text);

int hashAddString(HashTable *table, char *string);

bool isInList(List *list, const char* string);

uint64_t hash_1(const char* inputString);

uint64_t hash_2(const char* inputString);

uint64_t hash_3(const char* inputString);

uint64_t hash_4(const char* inputString);

uint64_t hash_5(const char* inputString);

uint64_t hash_6(const char* inputString);

uint64_t hash_7(const char* inputString);

