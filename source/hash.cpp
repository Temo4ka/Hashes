#define _CRT_SECURE_NO_WARNINGS
#include "../headers/hash.h"
#include <cstdio>
#include <cstdlib>
#include <immintrin.h>

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

    for (int cur = 0; cur < MODULE; cur++)
        if (hashTable -> list[cur].status == Active && listDtor(&(hashTable -> list[cur]))) return EXIT_FAILURE;
        
    free(hashTable -> list);

    return EXIT_SUCCESS;
}

int initHashTable(HashTable *table, WordsArray *words) {
    catchNullptr(table);
    catchNullptr(words);

    for (int curWord = 0; curWord < words -> numOfWords; curWord++)
        hashAddString(table, words -> array[curWord]);
    return EXIT_SUCCESS;
}

int hashAddString(HashTable *table, char *string) {
    catchNullptr(table );
    catchNullptr(string);

    unsigned h = table -> hash(string) % MODULE;

    if (table -> list[h].status == InActive)
        listCtor(&(table -> list[h]));


    if (isInList(&(table -> list[h]), string) != NOT_FOUND) return EXIT_SUCCESS;

    Elem_t newElem = listElemCtor(string, h);
    listPushBack(&(table -> list[h]), newElem);

    table -> numOfElems += 1;
    
    return EXIT_SUCCESS;
}

uint64_t DumbHash(const char* inputString) {
    if (inputString == nullptr) return ERROR_HASH;
    return 1;
}

uint64_t FirstByteHash(const char* inputString) {
    if (inputString == nullptr) return ERROR_HASH;

    return inputString[0];
}

uint64_t StrLenHash(const char* inputString) {
    if (inputString == nullptr) return ERROR_HASH;

    return strlen(inputString);
}

uint64_t SumHash(const char* inputString) {
    if (inputString == nullptr) return ERROR_HASH;

    uint64_t sum = 0;

    for (int cur = 0; inputString[cur]; cur++) sum += inputString[cur];

    return sum;
}

uint64_t cycleL(uint64_t num);
uint64_t cycleR(uint64_t num);

uint64_t RotlHash(const char* inputString) {
    if (inputString == nullptr) return ERROR_HASH;

    uint64_t hash = 0;

    for (int cur = 0; inputString[cur]; cur++) {
        hash ^= inputString[cur];
        hash  =   cycleL(hash)  ;
    }

    return hash;
}

uint64_t RotrHash(const char* inputString) {
    if (inputString == nullptr) return ERROR_HASH;

    uint64_t hash = 0;

    for (int cur = 0; inputString[cur]; cur++) {
        hash ^= inputString[cur];
        hash  =   cycleR(hash)  ;
    }

    return hash;
}

uint64_t GnuHash(const char *inputString) {
	if (inputString == nullptr) return ERROR_HASH;

    uint64_t hash = 5381;

    for (size_t currentByte = 0; inputString[currentByte]; currentByte++) {
        hash = hash * 33 + inputString[currentByte];
    }

    return hash;
}

uint64_t CRC32Hash(const char* inputString) {
    if (inputString == nullptr) return ERROR_HASH;

    const int CRC32_CONST = 0xFFFFFFFFu;

    uint64_t hash = CRC32_CONST;

    for (size_t cur = 0; cur < inputString[cur]; cur++) {
        hash = (hash >> 8) ^ CRC32Table[(hash ^ inputString[cur]) & 0xFF];
    }

    return hash ^ CRC32_CONST;
}

uint64_t FastCRC32Hash(const char* inputString) {
    if (inputString == nullptr) return ERROR_HASH;

    const size_t size = MAX_DATA_SIZE;
    uint64_t hash = 0;

    for (size_t cur = 0; cur < (size / sizeof(uint64_t)); cur++) {
        hash = _mm_crc32_u64(hash, *(const uint64_t*) inputString);
        inputString += sizeof(uint64_t);
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

Elem_t* isInHashTable(HashTable* table, const char* string) {
    if (table == nullptr) return nullptr;
    if (string == nullptr) return nullptr;

    unsigned h = table -> hash(string) % MODULE;

    if (table -> list[h].status == InActive) return nullptr;

    int pos = isInList(&(table->list[h]), string);
    if (pos == NOT_FOUND) return nullptr;

    return &(table -> list[h].data[pos]);
}

extern "C" int strcmpAsm(const char *str1, const char *str2);

int isInList(List *list, const char* string) {
    if ( list  == nullptr) return NOT_FOUND;
    if (string == nullptr) return NOT_FOUND;

    if (list -> status == InActive) return NOT_FOUND;

    for (size_t cur = list -> next[list -> head]; cur != list -> head; cur = list -> next[cur]) {
        if (!strcmpAsm(list -> data[cur].data, string)) return cur;
    }

    return NOT_FOUND;
}

//------------------------------------
// strcpy written with inline asm
//	   in order to optimize it
// -----------------------------------
// compile only with x86 configuration
//====================================
//int myStrcmp(const char* str1, const char* str2) {
//	__asm {
//		push ecx
//		push ebx
//		push esi
//		push edi
//
//		mov esi, str1
//		mov edi, str2
//		
//		mov ecx, 8d
//		
//		lp1:
//			mov ebx, dword ptr [esi]
//			cmp ebx, dword ptr [edi]
//			jne not_equal
//
//			lea esi, [esi + 4]
//			lea edi, [edi + 4]
//			lea ecx, [ecx - 1]
//
//
//		cmp ecx, 0d
//		jne lp1
//		
//		xor eax, eax //str1 == str2
//		jmp end_func
//		
//		not_equal:
//		or eax, 1
//		
//		end_func:
//		pop edi
//		pop esi
//		pop ebx
//		pop ecx
//	}
//}

int myStrcmp(const char* str1, const char* str2) {
    return strcmp(str1, str2);
}

inline int myFastStrcmp(const char* str1, const char* str2) {
    __m256i str1_ = _mm256_load_si256((__m256i*) (str1));
    __m256i str2_ = _mm256_load_si256((__m256i*) (str2));

    __m256i cmp_ = _mm256_cmpeq_epi8(str1_, str2_);

    int mask = _mm256_movemask_epi8(cmp_);

    return (~mask != 0);
}