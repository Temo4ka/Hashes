//-------------------------------------------------------------\\
//     Seven types of hashes are presented in this file        \\
//-------------------------------------------------------------\\

#pragma "once"
#include "config.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "list.h"

struct HashTable {
    List *list = (List *) calloc(MOD, sizeof(List));

    int numOfElems = 0;
};

int initHashTable(HashTable *table, char *text, uint64_t (*hash)(const char *));

int hashAddString(HashTable *table, char *string, uint64_t (*hash)(const char *));

uint64_t hash_1(const char* inputString);

uint64_t hash_2(const char* inputString);

uint64_t hash_3(const char* inputString);

uint64_t hash_4(const char* inputString);

uint64_t hash_5(const char* inputString);

uint64_t hash_6(const char* inputString);

uint64_t hash_7(const char* inputString);

