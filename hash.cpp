#define _CRT_SECURE_NO_WARNINGS
#include "hash.h"
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

    for (int cur = 0; cur < MOD; cur++)
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

    unsigned h = table -> hash(string) % MOD;
	//fprintf(stderr, "%d\n", h);

    if (table -> list[h].status == InActive)
        listCtor(&(table -> list[h]));

    // fprintf(stderr, "!%d\n", h);

    if (isInList(&(table -> list[h]), string)) return EXIT_SUCCESS;

    Elem_t newElem = listElemCtor(string, h);
    // int err = EXIT_SUCCESS;
    listPushBack(&(table -> list[h]), newElem);

    table -> numOfElems += 1;
    
    return EXIT_SUCCESS;
}

uint64_t DumbHash(const char* inputString) {
    if (inputString == nullptr) return ERROR_HASH;
    return 1;
}

uint64_t FirstElemHash(const char* inputString) {
    if (inputString == nullptr) return ERROR_HASH;

    return inputString[0];
}

uint64_t StrLenHash(const char* inputString) {
    if (inputString == nullptr) return ERROR_HASH;

    return strlen(inputString);
}

uint64_t SumHash(const char* inputString) {
    if (inputString == nullptr) return ERROR_HASH;

    uint64_t sum =          0         ;
    uint64_t len = strlen(inputString);

    for (int cur = 0; cur < len; cur++) sum += inputString[cur];

    return sum;
}

uint64_t cycleL(uint64_t num);
uint64_t cycleR(uint64_t num);

uint64_t RotlHash(const char* inputString) {
    if (inputString == nullptr) return ERROR_HASH;

    uint64_t hash =         0          ;
    uint64_t len  = strlen(inputString);

    for (int cur = 0; cur < len; cur++) {
        hash ^= inputString[cur];
        hash  =   cycleL(hash)  ;
    }

    return hash;
}

uint64_t RotrHash(const char* inputString) {
    if (inputString == nullptr) return ERROR_HASH;

    uint64_t hash =         0          ;
    uint64_t len  = strlen(inputString);

    for (int cur = 0; cur < len; cur++) {
        hash ^= inputString[cur];
        hash  =   cycleR(hash)  ;
    }

    return hash;
}

uint64_t GnuHash(const char *string) {
    size_t totalBytes = strlen(string);

    uint64_t hash = 5381;

    char *pointer = (char *) string;
    for (size_t currentByte = 0; currentByte < totalBytes; currentByte++) {
        hash = hash * 33 + pointer[currentByte];
    }

    return hash;
}

uint64_t CRC32Hash(const char* data) {
	const int CRC32_CONST = 0xFFFFFFFFu;

	uint64_t hash = CRC32_CONST;

	for (size_t cur = 0; cur < data[cur]; cur++) {
		hash = (hash >> 8) ^ CRC32Table[(hash ^ data[cur]) & 0xFF];
	}

	return hash ^ CRC32_CONST;
}

uint64_t FastCRC32Hash(const char* data) {
	const size_t size = MAX_DATA_SIZE;
	uint64_t hash = 0;

	for (size_t cur = 0; cur < (size / sizeof(uint32_t)); cur++) {
		hash = _mm_crc32_u32(hash, *(const uint32_t*)data);
		data += sizeof(uint32_t);
	}

	if (size & sizeof(uint16_t)) {
		hash = _mm_crc32_u16(hash, *(const uint16_t*)data);
		data += sizeof(uint16_t);
	}

	if (size & sizeof(uint8_t)) {
		hash = _mm_crc32_u8(hash, *(const uint8_t*)data);
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
    if ( list  == nullptr) return false;
    if (string == nullptr) return false;

	if (list -> status == InActive) return false;
    
    // fprintf(stderr, "---------------\n");
    for (size_t cur = list -> next[list -> head]; cur != list -> head; cur = list -> next[cur]) {
        // fprintf(stderr, "%s - %s\n", list -> data[cur].data, string);
        if (!myStrcmp(list -> data[cur].data, string)) return true;
    }
    // fprintf(stderr, "---------------\n");

    return false;
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
//			dec ecx
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