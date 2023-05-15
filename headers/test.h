#include "config.h"
#include "hash.h"
#include "in.h"

int test_diagrams(HashFunc_t hashFuncs[HASH_FUNC_NUM], Text *text, const char* outputFileName, size_t hashNum);

int test_speed(HashFunc_t hash, Text *text);