<<<<<<< HEAD
#include "config.h"
#include "hash.h"
#include "in.h"

int test_diagrams(Text *text, const char* outputFileName);

=======
#include "config.h"
#include "hash.h"
#include "in.h"

int test_diagrams(HashFunc_t hashFuncs[HASH_FUNC_NUM], Text *text, const char* outputFileName, size_t hashNum);

>>>>>>> 4a0a211e26fa9b71d07de0bc5cf7e43c6228120f
int test_speed(HashFunc_t hash, Text *text);